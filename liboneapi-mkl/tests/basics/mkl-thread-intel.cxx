// mkl-thread-intel smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  (void)MKL_Set_Threading_Layer(MKL_THREADING_INTEL);
  int prev = MKL_Set_Threading_Layer(MKL_THREADING_INTEL);
  assert(prev == MKL_THREADING_INTEL);
}
