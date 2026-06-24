#include <mpi.h>
#undef NDEBUG
#include <cassert>

int
main (int argc, char** argv)
{
  int rc = MPI_Init (&argc, &argv);
  assert (rc == MPI_SUCCESS);
  int initialized = 0;
  MPI_Initialized (&initialized);
  assert (initialized);
  MPI_Finalize ();
}
