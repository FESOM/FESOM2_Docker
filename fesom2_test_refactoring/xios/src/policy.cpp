/*!
   \file policy.cpp
   \author Ha NGUYEN
   \since 06 Oct 2015
   \date 06 Oct 2015

   \brief Some useful policies for templated classes
 */

#include "policy.hpp"
#include <cmath>

namespace xios
{
///*!
//  Calculate MPI communicator for each level of hierarchy.
//  \param[in] mpiCommRoot MPI communicator of the level 0 (usually communicator of all clients)
//  \param[in] levels number of level in hierarchy
//*/
//void DivideCommByTwo::computeMPICommLevel(const MPI_Comm& mpiCommRoot, int levels)
//{
//  int nbProc;
//  MPI_Comm_size(mpiCommRoot,&nbProc);
//  if (levels > nbProc) levels = std::log10(nbProc) * 3.3219; // log2(x) = log2(10) * log10(x); stupid C++98
//  else if (1 > levels) levels = 1;
//
//  commLevel_.push_back(mpiCommRoot);
//  divideMPICommLevel(mpiCommRoot, levels);
//}
//
///*!
//  Divide each MPI communicator into sub-communicator. Recursive function
//  \param [in] mpiCommLevel MPI communicator of current level
//  \param [in] level current level
//*/
//void DivideCommByTwo::divideMPICommLevel(const MPI_Comm& mpiCommLevel, int level)
//{
//  int clientRank;
//  MPI_Comm_rank(mpiCommLevel,&clientRank);
//
//   --level;
//  if (0 < level)
//  {
//   int color = clientRank % 2;
//   commLevel_.push_back(MPI_Comm());
//   MPI_Comm_split(mpiCommLevel, color, 0, &(commLevel_.back()));
//   divideMPICommLevel(commLevel_.back(), level);
//  }
//}

DivideAdaptiveComm::DivideAdaptiveComm(const MPI_Comm& mpiComm)
  : internalComm_(mpiComm), level_(0), groupBegin_(), nbInGroup_(), computed_(false)
{

}

void DivideAdaptiveComm::computeMPICommLevel()
{
  if (computed_) return;
  computed_ = true;

  int mpiSize, mpiRank;
  MPI_Comm_size(internalComm_,&mpiSize);
  MPI_Comm_rank(internalComm_,&mpiRank);

  int maxChild=1;
  int m;
  do
  {
    m=1;
    ++maxChild;
    for(int i=0;i<maxChild;++i) m *= maxChild;
   } while(m<mpiSize);

  int maxLevel=0;
  for(int size=1; size<=mpiSize; size*=maxChild) ++maxLevel;

  int pos, n, idx;
  level_=0;
  int begin=0;
  int end=mpiSize-1;
  int nb=end-begin+1;

  nbInGroup_ = groupBegin_= std::vector<int>(maxLevel);
  nbInGroupParents_ = groupParentsBegin_= std::vector<std::vector<int> >(maxLevel,std::vector<int>(maxChild));

  groupBegin_[level_] = begin;
  nbInGroup_[level_] = nb;
  ++level_;
  while (nb>2 && (level_<maxLevel))
  {
    n = 0; idx = 0;
    pos = begin;
    for(int i=0;i<maxChild && i<nb;i++)
    {
      if (i<nb%maxChild) n = nb/maxChild + 1;
      else n = nb/maxChild;

      if (mpiRank>=pos && mpiRank<pos+n)
      {
        begin=pos;
        end=pos+n-1;
      }
      groupParentsBegin_[level_-1][idx] = pos;
      nbInGroupParents_[level_-1][idx] = n;
      ++idx;
      pos=pos+n;
    }
    groupBegin_[level_] = begin;
    nbInGroup_[level_] = nb = end-begin+1;

    ++level_;
  }

  for (int i = 0; i < nbInGroup_[level_-1];++i)
  {
    groupParentsBegin_[level_-1][i] = groupBegin_[level_-1]+i;
    nbInGroupParents_[level_-1][i] = 1;
  }



//  parent=vector<int>(maxLevel+1);
//  child=vector<vector<int> >(maxLevel+1,vector<int>(maxChild));
//  nbChild=vector<int> (maxLevel+1);

//  do
//  {
//    n=0;
//    pos=begin;
//    nbChild[level_]=0;
//    parent[level_+1]=begin;
//    for(int i=0;i<maxChild && i<nb;i++)
//    {
//      if (i<nb%maxChild) n = nb/maxChild + 1;
//      else n = nb/maxChild;
//
//      if (mpiRank>=pos && mpiRank<pos+n)
//      {
//        begin=pos;
//        end=pos+n-1;
//      }
//      child[level_][i]=pos;
//      pos=pos+n;
//      nbChild[level_]++;
//    }
//    nb=end-begin+1;
//    level_=level_+1;
//  } while (nb>1);
}

//void DivideAdaptiveComm::divideMPICommLevel(const MPI_Comm& mpiCommLevel, int color, int level)
//{
////  int clientRank;
////  MPI_Comm_rank(mpiCommLevel,&clientRank);
//
//   --level;
//  if (0 < level)
//  {
//   int color = clientRank % 2;
//   commLevel_.push_back(MPI_Comm());
//   MPI_Comm_split(mpiCommLevel, color, 0, &(commLevel_.back()));
//   divideMPICommLevel(commLevel_.back(), level);
//  }
//}


}

