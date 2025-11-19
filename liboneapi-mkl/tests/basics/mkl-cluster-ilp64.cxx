// mkl-cluster-ilp64 smoke test
#include <mkl_blacs.h>
#undef NDEBUG
#include <cassert>

int main() {
  int zero = 0, info = 0;
  blacs_pinfo_(&info, &zero); // safe init
  blacs_exit_(&zero);         // safe cleanup
  assert(info == 0);          // proves BLACS initialized
}
