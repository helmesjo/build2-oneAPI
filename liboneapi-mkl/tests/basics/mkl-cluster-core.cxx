// mkl-cluster-core smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() { assert(MKL_Get_Cpu_Frequency() > 0.0); }
