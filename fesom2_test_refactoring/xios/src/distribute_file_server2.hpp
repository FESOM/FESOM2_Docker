#ifndef __XIOS_DISTRIBUTE_FILE_SERVER2_HPP__
#define __XIOS_DISTRIBUTE_FILE_SERVER2_HPP__

#include <cstddef>
#include <string>

namespace xios
{


struct SDistServer ;
struct SDistFiles ;
struct SDistGrid ;

struct SDistFile
{
  SDistServer* servers_ ;
  std::string id_;
  
  double bandwith_ ;
  int nbGrids_ ;
  int* assignedGrid_ ;
  int assignedServer_ ;

} ;
 
struct SDistServer
{
  SDistFile* files_ ;
  SDistGrid* grids_ ;
  
  double energy_ ;
  double bandwith_ ;
  double memory_ ;
  int  nMaxGrid_ ;
  int* assignedGrid_ ;
  int num_ ;
  
  void initialize(int num, int nMaxGrid, SDistGrid* grids, int nMaxFile, SDistFile* files) ;
  void finalize(void) ;
  
  double addFile(int numFile) ;
  double removeFile(int numFile) ;
} ;  
  
struct SDistGrid
{
  double size_ ;
} ;

void distributeFileOverServer2(int nbServers, int nGrids, SDistGrid* grids, int nFiles, SDistFile* files);
}
#endif
