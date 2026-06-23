# liboneapi-mkl - A C++ library

> **NOTE:**  
This package is not open source and does not contain any source code. Instead,
in order to "build" the exported target(s) it downloads (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for this package is disabled due to the above.  
Supported platforms/compilers are Windows/MSVC and Linux.

This is a `build2` package for the [Intel oneAPI Math Kernel Library
(oneMKL)](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html)
C++ library. It provides highly optimized routines for linear algebra (BLAS,
LAPACK), discrete Fourier transforms, vector mathematics, and sparse solvers,
shipped as dynamically dispatched shared libraries that select the best
computational kernel for the detected hardware at runtime.


## Usage

To start using `liboneapi-mkl` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: liboneapi-mkl ^2026.0.0-
```

Then import the library in your `buildfile`:

```
import libs = liboneapi-mkl%libs{mkl}
```


## Importable targets

This package provides the following importable targets:

```
libs{mkl}
libs{mkl-core}
libs{mkl-dispatch}
libs{mkl-lp64}
libs{mkl-ilp64}
libs{mkl-gf-lp64}
libs{mkl-gf-ilp64}
libs{mkl-imalloc}
libs{mkl-thread-seq}
libs{mkl-thread-intel}
libs{mkl-thread-gnu}
libs{mkl-thread-tbb}
libs{mkl-sycl}
libs{mkl-cluster-lp64}
libs{mkl-cluster-lp64-intelmpi}
libs{mkl-cluster-lp64-openmpi}
libs{mkl-cluster-lp64-msmpi}
libs{mkl-cluster-ilp64}
libs{mkl-cluster-ilp64-intelmpi}
libs{mkl-cluster-ilp64-openmpi}
libs{mkl-cluster-ilp64-msmpi}
```


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.liboneapi_mkl.cache ?= $out_root
```

The directory used to cache downloaded binary archives between builds. If
`config.liboneapi.cache` is set (a shared project-wide cache directory), it
takes precedence over the per-package default of `$out_root`.
