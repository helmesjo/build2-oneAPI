// compilers-common-malloc smoke test: verify that linking against libqkmalloc.so
// causes malloc to resolve from that library rather than from libc.
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#undef NDEBUG
#include <cassert>

int main ()
{
  Dl_info info;
  assert (dladdr (reinterpret_cast<void*> (std::malloc), &info) != 0);
  assert (std::strstr (info.dli_fname, "qkmalloc") != nullptr);
}
