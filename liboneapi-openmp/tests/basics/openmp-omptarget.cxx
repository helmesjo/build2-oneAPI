// openmp-omptarget smoke test
#undef NDEBUG
#include <cassert>
#include <omp.h>

int main() {
  // omp_target_alloc/omp_target_free live in omptarget.
  void *p = omp_target_alloc(128, 0);
  assert(p);
  if (p)
    omp_target_free(p, 0);
  return 0;
}
