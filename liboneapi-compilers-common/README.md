# liboneapi-compilers-common - A C++ library

> **NOTE:**  
This package is not open source and does not contain any source code. Instead,
in order to "build" the exported target(s) it downloads (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for this package is disabled due to the above.  
Supported platforms/compilers are Windows/MSVC and Linux.

This is a `build2` package for the [Intel oneAPI DPC++/C++
Compiler](https://www.intel.com/content/www/us/en/developer/tools/oneapi/dpc-compiler.html)
C++ library. It provides the shared runtime libraries required by Intel's oneAPI
C++ (icx) and Fortran (ifx) compilers, including the math and vector math
libraries (libimf, libsvml), the Unified Profiling Transport framework (XPTI),
the Unified Runtime loader (UR), and the scalable memory allocator (qkmalloc).


## Usage

To start using `liboneapi-compilers-common` in your project, add the following
`depends` value to your `manifest`, adjusting the version constraint as
appropriate:

```
depends: liboneapi-compilers-common ^2026.0.0-
```

Then import the library in your `buildfile`:

```
import libs = liboneapi-compilers-common%libs{compilers-common}
```


## Importable targets

This package provides the following importable targets:

```
libs{compilers-common}
libs{compilers-common-icx}
libs{compilers-common-xpti}
libs{compilers-common-ur}
libs{compilers-common-malloc}
```


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.liboneapi_compilers_common.cache ?= $out_root
```

The directory used to cache downloaded binary archives between builds. If
`config.liboneapi.cache` is set (a shared project-wide cache directory), it
takes precedence over the per-package default of `$out_root`.
