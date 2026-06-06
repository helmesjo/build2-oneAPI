// openmp-rt smoke test
#include <omp.h>
#undef NDEBUG
#include <cassert>

int main() {
  assert(omp_get_max_threads() > 0);
  int count = 0;
  #pragma omp parallel
  {
    #pragma omp atomic
    ++count;
  }
  assert(count > 0);
}
