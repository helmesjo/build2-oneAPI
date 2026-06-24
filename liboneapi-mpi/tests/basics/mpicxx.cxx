#include <mpi.h>
#undef NDEBUG
#include <cassert>

int
main (int argc, char** argv)
{
  int rc = MPI_Init (&argc, &argv);
  assert (rc == MPI_SUCCESS);
  int size = 0;
  MPI_Comm_size (MPI_COMM_WORLD, &size);
  assert (size >= 1);
  MPI_Finalize ();
}
