// mkl-thread-tbb smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  int prev = MKL_Set_Threading_Layer(MKL_THREADING_TBB);
  assert(prev == MKL_THREADING_TBB || prev == MKL_THREADING_INTEL);
}
