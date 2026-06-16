// tbb-malloc-proxy smoke test

#include <oneapi/tbb/tbbmalloc_proxy.h>

#if _MSC_VER
extern "C" void __TBB_malloc_proxy();
#endif

int main() {
  __TBB_malloc_proxy();
}
