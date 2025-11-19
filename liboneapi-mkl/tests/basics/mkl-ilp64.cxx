// mkl-ilp64 smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() {
  int prev = MKL_Set_Interface_Layer(MKL_INTERFACE_ILP64);
  assert(prev == MKL_INTERFACE_ILP64);
}
