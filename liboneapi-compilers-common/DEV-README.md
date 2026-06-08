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

  Target                   Linux libs                        Windows libs / libi
  ------                   ----------                        -------------------
  compilers-common-rt      lib/libimf.so                     bin/libmmd.dll
                           lib/libsvml.so                    bin/svml_dispmd.dll
                           lib/libirng.so                    bin/libirngmd.dll
                           lib/libintlc.so.5                 libi: lib/libmmd.lib
                           lib/libirc.so                     libi: lib/svml_dispmd.lib
                                                             libi: lib/libirngmd.lib

## Usage

This package is a runtime dependency of `liboneapi-openmp{openmp-omptarget}`
on both Linux and Windows. See `liboneapi-openmp/DEV-README.md`.
