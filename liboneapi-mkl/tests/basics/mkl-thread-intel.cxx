// mkl-thread-intel smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  (void)MKL_Set_Threading_Layer(MKL_THREADING_INTEL);
  int prev = MKL_Set_Threading_Layer(MKL_THREADING_INTEL);
  assert(prev == MKL_THREADING_INTEL);
  double a = 2.0;
  MKL_INT n = 1, inc = 1;
  cblas_dscal(n, 3.0, &a, inc);
  assert(a == 6.0);
}
