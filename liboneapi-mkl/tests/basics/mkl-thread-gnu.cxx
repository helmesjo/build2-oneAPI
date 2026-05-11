// mkl-thread-openmp smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  (void)MKL_Set_Threading_Layer(MKL_THREADING_GNU);
  int prev = MKL_Set_Threading_Layer(MKL_THREADING_SEQUENTIAL);
  assert(prev == MKL_THREADING_GNU);
}
