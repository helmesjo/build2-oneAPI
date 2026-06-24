# liboneapi-openmp - Intel OpenMP runtime (libiomp5)

> **NOTE:**  
This package is not open source and does not contain any source code. Instead,
in order to "build" the exported target(s) it downloads (potentially large)
pre-built binaries provided by Intel for the target platform.
>
> CI for this package is disabled due to the above.  
Supported platforms/compilers are Windows/MSVC and Linux.

This is a `build2` package for the [Intel oneAPI OpenMP
Runtime](https://www.intel.com/content/www/us/en/developer/tools/oneapi/openmp.html)
C++ library. It provides Intel's OpenMP runtime library (libiomp5) for
OpenMP 5.x shared-memory parallelism in code compiled with Intel compilers,
and the OpenMP target-offload runtime (omptarget) for device programming via
OpenMP offload directives.


## Usage

To start using `liboneapi-openmp` in your project, add the following `depends`
value to your `manifest`, adjusting the version constraint as appropriate:

```
depends: liboneapi-openmp ^2026.0.0-
```

Then import the library in your `buildfile`:

```
import libs = liboneapi-openmp%libs{openmp}
```


## Importable targets

This package provides the following importable targets:

```
libs{openmp}
libs{openmp-omptarget}
```


## Configuration variables

This package provides the following configuration variables:

```
[dir_path] config.liboneapi_openmp.cache ?= $out_root
```

The directory used to cache downloaded binary archives between builds. If
`config.liboneapi.cache` is set (a shared project-wide cache directory), it
takes precedence over the per-package default of `$out_root`.
