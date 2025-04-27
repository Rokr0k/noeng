#pragma once

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
} // namespace nanbou
