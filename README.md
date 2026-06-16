# oneAPI - build2 amalgamation of the Intel oneAPI family

> **NOTE:**  
These packages are not open source and do not contain any source code. Instead,
in order to "build" the exported target(s) they download (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for these packages are disabled due to the above.  
Supported platforms/compilers are Windows/MSVC & Linux. MacOS is (officially)
not supported.

`oneAPI` is a build2 amalgamation of packages for Intel oneAPI components
(proprietary only), enabling unified programming across heterogeneous
architectures.

Currently packaged:
- oneMKL (Math Kernel Library)
- oneTBB (Threading Building Blocks)
- OpenMP runtime (libiomp5)
- Fortran compiler runtime (ifort/ifx)
- Compiler common runtime (libimf, libsvml, libintlc, xpti, qkmalloc)

Not yet packaged:
- DPC++/C++ Compiler + runtime
- MPI Library
- IPP (Integrated Performance Primitives)
- VTune Profiler

This file contains setup instructions and other details that are more
appropriate for package development rather than consumption. If you want to use
`oneAPI` in your `build2`-based project, import the relevant target(s) directly.

The development setup uses the standard `bdep`-based workflow:

```
git clone https://github.com/build2-packaging/oneAPI.git
cd oneAPI

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```

See [DEV-README.md](DEV-README.md) for the download mechanism, per-package
layout, and instructions for updating to a new upstream release.
