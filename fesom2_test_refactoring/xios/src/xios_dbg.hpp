#ifndef XIOS_DBG_HPP
#define XIOS_DBG_HPP
#include <cstdio>
#include <cstdlib>
#include <mpi.h>

namespace xios_dbg {
  inline FILE* fp() {
    static FILE* f = nullptr;
    if (!f) {
      int r = -1, inited = 0;
      MPI_Initialized(&inited);
      if (inited) MPI_Comm_rank(MPI_COMM_WORLD, &r);
      char name[128];
      std::snprintf(name, sizeof(name), "xios_dbg_%06d.log", r);
      f = std::fopen(name, "w");
      if (f) std::setvbuf(f, nullptr, _IONBF, 0);
    }
    return f;
  }
}

#define XDBG(...) do { FILE* _f = xios_dbg::fp(); if (_f) { std::fprintf(_f, __VA_ARGS__); std::fflush(_f); } } while(0)

#endif
