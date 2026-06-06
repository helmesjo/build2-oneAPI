// mkl-lp64 smoke test: layered mode, link against mkl-lp64 import lib directly
#include <mkl.h>

#undef NDEBUG
#include <cassert>

static_assert(sizeof(MKL_INT) == 4, "MKL_INT must be 4 bytes in LP64 mode");

int main() {
  double a = 2.0;
  MKL_INT n = 1, inc = 1;
  cblas_dscal(n, 3.0, &a, inc);
  assert(a == 6.0);
}
