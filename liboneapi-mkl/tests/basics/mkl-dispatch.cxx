// mkl-dispatch smoke test
#include <mkl_cblas.h>
#undef NDEBUG
#include <cassert>

int main() {
  double a = 1.0;
  assert(cblas_dnrm2(1, &a, 1) == 1.0);
}
