// tbb-malloc smoke test

#include <oneapi/tbb/scalable_allocator.h>
#undef NDEBUG
#include <cassert>

int main() {
  void *p = scalable_malloc(4096);
  assert(p != nullptr);
  scalable_free(p);
}
