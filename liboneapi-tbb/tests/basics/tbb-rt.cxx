// tbb-rt smoke test

#include <oneapi/tbb/info.h>
#undef NDEBUG
#include <cassert>

int main() { assert(oneapi::tbb::info::default_concurrency() > 0); }
