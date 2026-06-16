# liboneapi-compilers-common

## Versions

  Platform  Component ID                                   Version
  --------  ------------                                   -------
  linux     `intel.oneapi.lin.compilers-common`            2026.0.0+947  (devel)
  linux     `intel.oneapi.lin.compilers-common.runtime`    2026.0.0+947  (runtime)
  windows   `intel.oneapi.win.compilers-common`            2026.0.0+944  (devel)
  windows   `intel.oneapi.win.compilers-common-runtime`    2026.0.0+944  (runtime)

Note: the Windows runtime ID uses a hyphen (`compilers-common-runtime`)
whereas Linux uses a dot (`compilers-common.runtime`). The `runtime_id` and
`devel_id` fields in `manifest.json` capture this explicitly.

Content manifest basename:
  linux:   `intel.oneapi.lin.compiler.content`
  windows: `intel.oneapi.win.compiler.content`

## Tarball layout

Tarballs extract under `_installdir/compiler/<ver>/` which maps to
`compilers-common-runtime/` or `compilers-common-devel/` after the
version-segment strip in `redist.build`.

### runtime  ->  `extract{compilers-common-runtime}`

  compilers-common-runtime/lib/libimf.so         - Intel Math Functions       (linux)
  compilers-common-runtime/lib/libsvml.so        - Short Vector Math Library  (linux)
  compilers-common-runtime/lib/libirng.so        - Intel Random Number Gen.   (linux)
  compilers-common-runtime/lib/libintlc.so.5     - Intel C++ runtime          (linux)
  compilers-common-runtime/lib/libirc.so         - Intel compiler support     (linux)

  compilers-common-runtime/bin/libmmd.dll        - Intel Math Functions       (windows)
  compilers-common-runtime/bin/svml_dispmd.dll   - Short Vector Math Library  (windows)
  compilers-common-runtime/bin/libirngmd.dll     - Intel Random Number Gen.   (windows)

  Also present but not packaged as separate targets:
    lib/libcommon_clang.so.2026.21.3.0
    lib/libintelocl.so.2026.21.3.0 + libOpenCL.so.1.0.0 (OpenCL ICD)
    lib/libxptifw.so                (XPTI tracing framework)
    lib/libqkmalloc.so              (Intel memory allocator)
    lib/libze_trace_collector.so    (Level Zero trace collector)
    lib/icx-lto.so                  (ICX LTO plugin)
    lib/libocl_svml_*.so            (OCL SVML dispatch variants)
    lib/libistrconv.so              (Intel string/number conversion)
    lib/*.rtl, *.o, *.cfg           (compiler toolchain internals)
    bin/libircmd.dll                (Intel C++ runtime, windows - no import lib)

  No licensing files ship with this component (no `share/doc/` directory).

### devel  ->  `extract{compilers-common-devel}`

  compilers-common-devel/lib/libmmd.lib       - import lib for libmmd.dll       (windows)
  compilers-common-devel/lib/svml_dispmd.lib  - import lib for svml_dispmd.dll  (windows)
  compilers-common-devel/lib/libirngmd.lib    - import lib for libirngmd.dll     (windows)

  compilers-common-devel/lib/libimf.a         - static math functions  (linux)
  compilers-common-devel/lib/libsvml.a        - static SVML            (linux)
  compilers-common-devel/lib/libirng.a        - static RNG             (linux)
  compilers-common-devel/lib/libirc.a         - static compiler rt     (linux)

  Also ships compiler toolchain binaries (`bin/icx-cc`, `bin/compiler/ld.lld`,
  etc.) on both platforms; these are not used by this package.

## build2 targets

  Target                   Linux libs                        Windows libs / libi / liba
  ------                   ----------                        --------------------------
  compilers-common         lib/libimf.so                     bin/libmmd.dll
                           lib/libsvml.so                    bin/svml_dispmd.dll
                           lib/libirng.so                    bin/libirngmd.dll
                           lib/libintlc.so.5                 libi: lib/libmmd.lib
                           lib/libirc.so                     libi: lib/svml_dispmd.lib
                                                             libi: lib/libirngmd.lib

  compilers-common-icx     liba: lib/libbfp754.a              liba: lib/libbfp754.lib
                           liba: lib/libdecimal.a             liba: lib/libdecimal.lib
                           liba: lib/libimf.a                 liba: lib/libicaio.lib
                           liba: lib/libipgo.a                liba: lib/libipgo.lib
                           liba: lib/libirc.a                 liba: lib/libirc.lib
                           liba: lib/libirc_s.a               liba: lib/libircmt.lib
                           liba: lib/libirng.a                liba: lib/libirng.lib
                           liba: lib/libistrconv.a            liba: lib/libistrconv.lib
                           liba: lib/libmatmul.a              liba: lib/libm.lib
                           liba: lib/libsvml.a                liba: lib/libmatmul.lib
                                                              liba: lib/libmmds.lib
                                                              liba: lib/libmmt.lib
                                                              liba: lib/svml_dispmt.lib

  compilers-common-xpti    lib/libxptifw.so                  bin/xptifw.dll
                           liba: lib/libxpti.a                libi: lib/xptifw.lib
                           depends: compilers-common          liba: lib/xpti.lib
                                                              depends: compilers-common

  compilers-common-ur      (absent on linux)                  bin/ur_loader.dll
                                                              bin/ur_adapter_level_zero.dll
                                                              bin/ur_adapter_level_zero_v2.dll
                                                              bin/ur_adapter_opencl.dll
                                                              libi: lib/ur_loader.lib
                                                              depends: compilers-common

  compilers-common-malloc  lib/libqkmalloc.so                bin/qkmalloc.dll
                           depends: compilers-common          libi: lib/qkmalloc.lib

## Usage

`compilers-common` is a runtime dependency of `liboneapi-openmp{openmp-omptarget}`
on both Linux and Windows. See `liboneapi-openmp/DEV-README.md`.

`compilers-common-icx` provides static archives for code compiled with Intel's
icx/icpx compiler that needs the compiler support libraries baked into the binary.
It is distinct from `compilers-common` (shared): some archives have shared
counterparts there, others (`libbfp754`, `libdecimal`, `libipgo`) do not.

`compilers-common-ur` provides the Unified Runtime loader and adapters needed
for SYCL/oneAPI GPU offload.
