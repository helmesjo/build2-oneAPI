// ifort-rt smoke test: exercises libifport.so via the GETPID intrinsic
// to verify linking and dynamic loading work correctly.
#undef NDEBUG
#include <cassert>

// Fortran GETPID() portability intrinsic, exported by libifport.so.
extern "C" int getpid_ ();

int main ()
{
  assert (getpid_ () > 0);
}
