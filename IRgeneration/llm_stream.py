"""Chat-completion helper that always streams.

Some OpenAI-compatible relays (e.g. the a.fe8.cn proxy serving
``gpt-5.6-luna``) return an empty ``message.content`` for non-streaming
``/chat/completions`` requests even when the call succeeds, but reliably
deliver the full text over ``stream=True``.  The pipeline routes every chat
call through :func:`create`, which forces streaming and accumulates the deltas
into an object shaped like the non-streaming ``ChatCompletion`` response so
existing ``resp.choices[0].message.content`` call sites keep working without
further changes.
"""

from types import SimpleNamespace

try:
    import openai as _openai
except Exception:  # noqa: BLE001  (openai import optional for unit tests)
    _openai = None

# Transient transport/server failures worth retrying.  These are the errors the
# a.fe8.cn relay raises while overloaded ("Our servers are currently
# overloaded", "Upstream request failed"); retrying the whole request is safe
# because completion requests are idempotent reads.
_MAX_ATTEMPTS = 6
_BACKOFF_SECONDS = [2, 4, 8, 16, 30]


def _is_transient(exc):
    if _openai is None:
        return False
    if isinstance(exc, (_openai.APIConnectionError, _openai.APITimeoutError,
                        _openai.RateLimitError)):
        return True
    # APIError is the base for relay-side failures ("upstream request failed",
    # "server overloaded"); do not retry client 4xx errors or auth issues.
    if isinstance(exc, _openai.APIStatusError):
        return False
    if isinstance(exc, _openai.APIError):
        return True
    return False


def _run(client, kwargs):
    stream = client.chat.completions.create(**kwargs)
    # Most endpoints honour ``stream=True`` and return an iterable.  A few
    # OpenAI-compatible gateways (and lightweight test doubles) instead
    # return an already assembled ChatCompletion.  Accept that shape as a
    # compatibility fallback without changing the real streaming path.
    choices = getattr(stream, "choices", None)
    if choices and getattr(choices[0], "message", None) is not None:
        return stream

    content_parts = []
    response_id = None
    response_model = None
    finish_reason = None
    for chunk in stream:
        if response_id is None:
            response_id = getattr(chunk, "id", None)
        if response_model is None:
            response_model = getattr(chunk, "model", None)
        if not chunk.choices:
            continue
        choice = chunk.choices[0]
        delta = getattr(choice, "delta", None)
        if delta is not None:
            piece = getattr(delta, "content", None)
            if piece:
                content_parts.append(piece)
        if getattr(choice, "finish_reason", None):
            finish_reason = choice.finish_reason

    message = SimpleNamespace(content="".join(content_parts), role="assistant")
    choice = SimpleNamespace(message=message, finish_reason=finish_reason,
                             index=0)
    return SimpleNamespace(choices=[choice], id=response_id,
                           model=response_model, usage=None)


def create(client, *, model, messages, temperature=None, max_tokens=None,
           **kwargs):
    """Force a streaming chat completion and return a response-like object.

    Only the fields the codebase actually reads are populated: ``choices[0]
    .message.content``, ``choices[0].finish_reason``, ``id``, ``model`` and
    ``usage`` (``None`` unless the relay reports it).

    Transient relay/server failures are retried with a short backoff so a
    single overloaded upstream request does not abort a whole generation.
    """
    kwargs["model"] = model
    kwargs["messages"] = messages
    if temperature is not None:
        kwargs["temperature"] = temperature
    kwargs["max_tokens"] = max_tokens
    kwargs["stream"] = True

    last_exc = None
    for attempt in range(_MAX_ATTEMPTS):
        try:
            return _run(client, kwargs)
        except Exception as exc:  # noqa: BLE001 - filter below
            if not _is_transient(exc):
                raise
            last_exc = exc
            delay = _BACKOFF_SECONDS[attempt] if attempt < len(
                _BACKOFF_SECONDS) else _BACKOFF_SECONDS[-1]
            import time
            time.sleep(delay)
    raise last_exc
