#pragma once

#include <utility>

namespace nanbou
{
template <typename Deferred> class Defer
{
  public:
    Defer(Deferred &&deferred) : deferred(deferred), b_cancelled(false)
    {
    }

    Defer(Defer &&rhs) : deferred(rhs.deferred), b_cancelled(rhs.b_cancelled)
    {
        rhs.b_cancelled = true;
    }

    ~Defer()
    {
        deferred();
    }

    void Cancel()
    {
        b_cancelled = true;
    }

  private:
    Deferred deferred;
    bool b_cancelled;
};

template <typename Deferred> Defer<Deferred> MakeDefer(Deferred &&deferred)
{
    return std::forward<Deferred>(deferred);
}
} // namespace nanbou
