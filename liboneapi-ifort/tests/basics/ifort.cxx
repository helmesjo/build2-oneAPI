// ifort smoke test: verifies linking and dynamic loading of the ifort
// runtime libraries by exercising two distinct runtime entry points.
#undef NDEBUG
#include <cassert>

extern "C" void for_rtl_init_ (int*, char**); // libifcoremd.dll / libifcore.so.5
#ifndef _WIN32
extern "C" int getpid_ ();                    // libifport.so.5
#endif

int main (int argc, char* argv[])
{
  for_rtl_init_ (&argc, argv);
#ifndef _WIN32
  assert (getpid_ () > 0);
#endif
}
