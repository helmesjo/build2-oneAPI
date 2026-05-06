// tbb-malloc-proxy smoke test

#include <oneapi/tbb/tbbmalloc_proxy.h>
#undef NDEBUG
#include <cassert>

int main() {
  char **log = nullptr;
  int status = TBB_malloc_replacement_log(&log);
  assert(status == 0 || status == 1); // 0 = success, 1 = no replacement
}
