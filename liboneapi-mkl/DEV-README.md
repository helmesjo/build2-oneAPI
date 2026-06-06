# liboneapi-mkl

## Versions

  Platform  Component ID                       Version
  --------  ------------                       -------
  linux     intel.oneapi.lin.mkl.runtime       2026.0.0+908
  linux     intel.oneapi.lin.mkl.devel         2026.0.0+908
  windows   intel.oneapi.win.mkl.runtime       2026.0.0+901
  windows   intel.oneapi.win.mkl.devel         2026.0.0+901

Content manifest basename:
  linux:   intel.oneapi.lin.onemkl.content
  windows: intel.oneapi.win.onemkl.content

## Tarball layout

### mkl.runtime  ->  extract{mkl-runtime}

_installdir/mkl/<ver>/ maps to mkl-runtime/ after the version-segment strip.

Computation / dispatch (linux .so.3, windows .3.dll; mkl_cdft_core windows .2.dll):
  mkl_rt, mkl_core, mkl_cdft_core
  mkl_avx2, mkl_avx512, mkl_avx10 (new in 2026.0), mkl_def, mkl_mc3
  mkl_vml_avx2, mkl_vml_avx512, mkl_vml_avx10 (new in 2026.0), mkl_vml_def,
  mkl_vml_mc3, mkl_vml_cmpt

Interface (linux .so.3, windows import-lib only):
  mkl_intel_lp64, mkl_intel_ilp64
  mkl_gf_lp64, mkl_gf_ilp64     (linux only, GNU Fortran interface)

Threading (linux .so.3, windows .2.dll):
  mkl_sequential, mkl_intel_thread, mkl_tbb_thread
  mkl_gnu_thread                 (linux only, requires -lgomp)

SYCL (linux .so.6, windows .6.dll):
  mkl_sycl_blas, mkl_sycl_data_fitting, mkl_sycl_dft, mkl_sycl_lapack,
  mkl_sycl_rng, mkl_sycl_sparse, mkl_sycl_stats, mkl_sycl_vm
  mkl_sycl_distributed_dft      (linux .so.2, absent on windows)

Cluster / ScaLAPACK (linux .so.2, windows .2.dll):
  mkl_scalapack_lp64, mkl_scalapack_ilp64
  mkl_blacs_intelmpi_lp64/ilp64
  mkl_blacs_openmpi_lp64/ilp64   (linux only)
  mkl_blacs_msmpi_lp64/ilp64     (windows only)

Windows only: libimalloc.dll

### mkl.devel  ->  extract{mkl-devel}

  mkl-devel/include/            - public headers
  mkl-devel/lib/*.a             - static libs  (linux)
  mkl-devel/lib/*.lib           - import libs  (windows)
  mkl-devel/lib/cmake/mkl/
  mkl-devel/lib/pkgconfig/

## build2 targets

  Target                   Linux depends          Windows depends
  ------                   -------------          ---------------
  mkl-rt                   []                     mkl-core, mkl-dispatch,
                                                  mkl-imalloc, mkl-thread-seq,
                                                  mkl-thread-intel
  mkl-core                 mkl-lp64               mkl-dispatch
  mkl-dispatch             []                     []
  mkl-lp64                 []                     []  (import-lib only on windows)
  mkl-ilp64                []                     []  (import-lib only on windows)
  mkl-imalloc              (absent)               []
  mkl-thread-seq           mkl-core               mkl-core
  mkl-thread-intel         mkl-core               mkl-core
  mkl-thread-gnu           mkl-core               (absent, GNU OpenMP not on windows)
  mkl-thread-tbb           mkl-core               mkl-core
  mkl-sycl                 mkl-core               mkl-core
  mkl-cluster-lp64         mkl-lp64               mkl-lp64
  mkl-cluster-ilp64        mkl-ilp64              mkl-ilp64
  mkl-cluster-lp64-intelmpi  mkl-cluster-lp64     mkl-cluster-lp64
  mkl-cluster-lp64-openmpi   mkl-cluster-lp64     (absent)
  mkl-cluster-lp64-msmpi     (absent)             mkl-cluster-lp64
  mkl-cluster-ilp64-intelmpi mkl-cluster-ilp64    mkl-cluster-ilp64
  mkl-cluster-ilp64-openmpi  mkl-cluster-ilp64    (absent)
  mkl-cluster-ilp64-msmpi    (absent)             mkl-cluster-ilp64

mkl-thread-intel also has an inter-package dependency on
liboneapi-openmp{openmp-rt} declared in buildfile (not package.json).

## Linking notes

Two valid strategies; do NOT mix them:

  SDL:     link only mkl-rt  (-lmkl_rt); it dlopen's everything at runtime.
  Layered: link interface + threading + core in that order
             e.g. -lmkl_intel_lp64 -lmkl_sequential -lmkl_core

On Linux, mkl_core.so.3 externalizes the DFTI symbol
mkl_dft_dfti_error_class_external to the interface layer (lp64/ilp64);
mkl-core therefore depends on mkl-lp64. On Windows mkl_core.2.dll
self-contains this symbol so no such dependency is needed there.

mkl_cdft_core (cluster FFT) is bundled inside mkl-core on Windows
(mkl_cdft_core.2.dll ships alongside mkl_core.2.dll). On Linux it is
NOT part of mkl-core; linking it causes circular undefined references
with mkl_core.so.3 and it is not included in any pkg-config link line.

Dispatch libs (avx2, avx512, avx10, def, mc3, vml_*) are dlopen'd by
mkl_core at runtime on Linux (no unversioned .so symlinks exist for them).
On Windows they are explicit DLL dependencies of mkl-rt and mkl-core.
