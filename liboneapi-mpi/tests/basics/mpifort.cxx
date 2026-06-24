#include <mpi.h>
#undef NDEBUG
#include <cassert>

int
main (int argc, char** argv)
{
  int rc = MPI_Init (&argc, &argv);
  assert (rc == MPI_SUCCESS);
  int rank = 0;
  MPI_Comm_rank (MPI_COMM_WORLD, &rank);
  assert (rank == 0);
  MPI_Finalize ();
}
