// mkl-lp64 smoke test
#include <mkl.h>

#undef NDEBUG
#include <cassert>

int main() {
  int layer = mkl_set_interface_layer(MKL_INTERFACE_LP64);
  assert(layer == MKL_INTERFACE_LP64);
  double a = 2.0;
  MKL_INT n = 1, inc = 1;
  cblas_dscal(n, 3.0, &a, inc);
  assert(a == 6.0);
}
