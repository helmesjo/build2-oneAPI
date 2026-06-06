// mkl-ilp64 smoke test: layered mode, link against mkl-ilp64 import lib directly
#define MKL_ILP64
#include <mkl.h>

#undef NDEBUG
#include <cassert>

static_assert(sizeof(MKL_INT) == 8, "MKL_INT must be 8 bytes in ILP64 mode");

int main() {
  double a = 2.0;
  MKL_INT n = 1, inc = 1;
  cblas_dscal(n, 3.0, &a, inc);
  assert(a == 6.0);
}
