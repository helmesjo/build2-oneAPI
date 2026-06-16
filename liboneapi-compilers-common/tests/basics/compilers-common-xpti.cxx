// compilers-common-xpti smoke test
#undef NDEBUG
#include <cassert>

extern "C" unsigned long long xptiGetUniqueId (); // libxptifw.so

int main ()
{
  unsigned long long a = xptiGetUniqueId ();
  unsigned long long b = xptiGetUniqueId ();
  assert (b != a);
}
