# liboneapi-compilers-common

## Versions

  Platform  Component ID                                 Version
  --------  ------------                                 -------
  linux     intel.oneapi.lin.compilers-common.runtime    2026.0.0+947
  windows   intel.oneapi.win.compilers-common.runtime    2026.0.0+944

Content manifest basename:
  linux:   intel.oneapi.lin.compiler.content
  windows: intel.oneapi.win.compiler.content

The compilers-common component ships as a single runtime payload (no separate
devel). The build2 package uses one extract group: extract{compilers-common-runtime}.

Note: unlike intel.oneapi.lin.openmp whose component ID is bare (no type
suffix), the compilers-common component ID ends in '.runtime'. The buildfile
therefore uses json{intel.oneapi.$(package_infix).$(name).runtime...} as the
JSON target so that the content manifest package ID match is correct.

## Tarball layout

Tarballs extract under _installdir/compiler/<ver>/ which maps to
compilers-common-runtime/ after the version-segment strip in redist.build.

### Linux (verified 2026.0.0+947)

  compilers-common-runtime/lib/libimf.so         - Intel Math Functions
  compilers-common-runtime/lib/libsvml.so        - Short Vector Math Library
  compilers-common-runtime/lib/libirng.so        - Intel Random Number Generator
  compilers-common-runtime/lib/libintlc.so.5     - Intel C++ runtime (libintlc.so is a linker stub)
  compilers-common-runtime/lib/libirc.so         - Intel compiler support library

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

  No licensing files ship with this component (no share/doc/ directory).

### Windows (verify paths after probing)

  compilers-common-runtime/bin/imf.dll           - Intel Math Functions
  compilers-common-runtime/bin/svml_dispmd.dll   - Short Vector Math Library
  compilers-common-runtime/bin/libmmt.dll        - Intel memory management
  compilers-common-runtime/bin/intlc.dll         - Intel C++ runtime

## build2 targets

  Target                   Linux libs                        Windows libs
  ------                   ----------                        ------------
  compilers-common-rt      lib/libimf.so                     bin/imf.dll      (unverified)
                           lib/libsvml.so                    bin/svml_dispmd.dll
                           lib/libirng.so                    bin/libmmt.dll
                           lib/libintlc.so.5                 bin/intlc.dll
                           lib/libirc.so

## Usage

This package is a runtime dependency of liboneapi-openmp{openmp-omptarget}
on Linux. See liboneapi-openmp/DEV-README.md.
