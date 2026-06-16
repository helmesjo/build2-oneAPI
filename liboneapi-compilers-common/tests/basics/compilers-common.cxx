// compilers-common smoke test
#undef NDEBUG
#include <cassert>

// libimf.so: Intel Math Functions - inverse square root (Intel extension, not in libm).
extern "C" double invsqrt(double);

int main()
{
  // 1/sqrt(x); verify against exact IEEE-754 representable results.
  assert(invsqrt(1.0) == 1.0);
  assert(invsqrt(4.0) == 0.5);
  assert(invsqrt(0.25) == 2.0);
}
