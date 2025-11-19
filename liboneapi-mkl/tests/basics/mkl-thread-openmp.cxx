// mkl-thread-seq smoke test
#include <mkl.h>
#undef NDEBUG
#include <cassert>

int main() { assert(MKL_Get_Max_Threads() >= 1); }
