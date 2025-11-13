# oneAPI - build2 amalgamation of the Intel oneAPI family

`oneAPI` is a build2 amalgamation of packages for Intel oneAPI components,
enabling unified programming across heterogeneous architectures.

This file contains setup instructions and other details that are more
appropriate for development rather than consumption. If you want to use
`oneAPI` libraries/tools in your `build2`-based project, then instead
see the accompanying package [`README.md`](liboneapi-mkl/README.md) file.

The development setup for `oneAPI` uses the standard `bdep`-based workflow.
For example:

```
git clone https://github.com/build2-packaging/oneAPI.git
cd oneAPI

bdep init -C @gcc cc config.cxx=g++
bdep update
bdep test
```
