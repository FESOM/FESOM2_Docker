# fesom2_ci

CI build-test image for [FESOM/fesom2](https://github.com/FESOM/fesom2). Provides:

- Ubuntu 22.04 base
- GCC, OpenMPI, NetCDF, HDF5, LAPACK
- OASIS3-MCT prebuilt at `/oasis` (CMake, position-independent)
- XIOS 2.5 prebuilt at `/xios` (`make_xios --arch GCC_LINUX --netcdf_lib netcdf4_seq`)

Published by this repo's `docker-publish.yml` to
`ghcr.io/fesom/fesom2_docker:fesom2_ci-<version>`.

FESOM/fesom2's `.github/workflows/fesom2_build_tests.yml` runs inside this image and
copies `/oasis` and `/xios` into the workspace before configuring CMake. XIOS is
built with sequential NetCDF since CI only build-and-link-tests the XIOS path; it
does not run XIOS at runtime.
