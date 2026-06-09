// ifort-rt smoke test: verifies linking and dynamic loading of the ifort
// runtime libraries by exercising two distinct runtime entry points.
#undef NDEBUG
#include <cassert>

// Fortran core runtime init from libifcoremd.dll (Windows) / libifcore.so (Linux).
// Must be called before any Fortran routines in mixed C++/Fortran programs.
extern "C" void for_rtl_init_ (int*, char**);

#ifndef _WIN32
// GETPID portability intrinsic from libifport.so (Linux).
// Returns the current process ID, always a positive integer.
extern "C" int getpid_ ();
#endif

int main (int argc, char* argv[])
{
  for_rtl_init_ (&argc, argv);
#ifndef _WIN32
  assert (getpid_ () > 0);
#endif
}
