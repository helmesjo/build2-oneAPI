// mkl-thread-openmp smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  int prev = MKL_Set_Threading_Layer(MKL_THREADING_GNU);
  assert(prev == MKL_THREADING_GNU || prev == MKL_THREADING_INTEL);
}
