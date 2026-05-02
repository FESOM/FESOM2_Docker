/*!
   \file policy.hpp
   \author Ha NGUYEN
   \since 06 Oct 2015
   \date 06 Oct 2015

   \brief Some useful policies for templated classes
 */

#ifndef __XIOS_POLICY_HPP__
#define __XIOS_POLICY_HPP__

#include <vector>
#include "mpi.hpp"

namespace xios
{
//class DivideCommByTwo
//{
//protected:
//  void computeMPICommLevel(const MPI_Comm& mpiCommRoot, int levels);
//
//protected:
//  std::vector<MPI_Comm> commLevel_;
//private:
//  // Divide MPI communicator on each level recursively
//  void divideMPICommLevel(const MPI_Comm& mpiCommLevel, int level);
//};

class DivideAdaptiveComm
{
protected:
  DivideAdaptiveComm(const MPI_Comm& mpiComm);

  void computeMPICommLevel();
  const std::vector<int>& getGroupBegin() { return groupBegin_; }
  const std::vector<int>& getNbInGroup() { return nbInGroup_; }
  const std::vector<std::vector<int> >& getGroupParentsBegin() { return groupParentsBegin_; }
  const std::vector<std::vector<int> >& getNbInGroupParents() { return nbInGroupParents_; }
  int getNbLevel() { return level_; }

protected:
  const MPI_Comm& internalComm_;
  std::vector<std::vector<int> > groupParentsBegin_;
  std::vector<std::vector<int> > nbInGroupParents_;

  int level_;
  std::vector<int> groupBegin_;  //! Rank beginning of a group
  std::vector<int> nbInGroup_; //! Number of process in each group
  bool computed_;
//  std::vector<std::vector<int> > child_; /*!< List of child rank for each level */
//  std::vector<int> nbChild_;         /*!< Number of child for each level */
};

}

#endif // __XIOS_POLICY_HPP__
