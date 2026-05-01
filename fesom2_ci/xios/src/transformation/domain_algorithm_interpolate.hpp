/*!
   \file domain_algorithm_interpolate_from_file.hpp
   \author Ha NGUYEN
   \since 09 July 2015
   \date 09 Sep 2015

   \brief Algorithm for interpolation on a domain.
 */
#ifndef __XIOS_DOMAIN_ALGORITHM_INTERPOLATE_HPP__
#define __XIOS_DOMAIN_ALGORITHM_INTERPOLATE_HPP__

#include "domain_algorithm_transformation.hpp"
#include "transformation.hpp"
#include "nc4_data_output.hpp"

namespace xios {

class CDomain;
class CInterpolateDomain;


/*!
  \class CDomainAlgorithmInterpolate
  Reading interpolation from file then apply on a domain
*/
class CDomainAlgorithmInterpolate : public CDomainAlgorithmTransformation
{
public:
  CDomainAlgorithmInterpolate(CDomain* domainDestination, CDomain* domainSource, CInterpolateDomain* interpDomain);

  virtual ~CDomainAlgorithmInterpolate() {}

  virtual void apply(const std::vector<std::pair<int,double> >& localIndex,
                     const double* dataInput,
                     CArray<double,1>& dataOut,
                     std::vector<bool>& flagInitial,                     
                     bool ignoreMissingValue, bool firstPass);
  virtual void updateData(CArray<double,1>& dataOut);

  static bool registerTrans();

  virtual StdString getName() {return "interpolate_domain";}

protected:
  void computeIndexSourceMapping_(const std::vector<CArray<double,1>* >& dataAuxInputs);

private:
  void readInterpolationInfo(std::string& filename, std::map<int,std::vector<std::pair<int,double> > >& interpMapValue);
  void writeInterpolationInfo(std::string& filename, std::map<int,std::vector<std::pair<int,double> > >& interpMapValue);
  void processPole(std::map<int,std::vector<std::pair<int,double> > >& interMapValuePole,
                   int nbGlobalPointOnPole);
  void computeRemap();
  void readRemapInfo();
  void writeRemapInfo(std::map<int,std::vector<std::pair<int,double> > >&);
  void exchangeRemapInfo(std::map<int,std::vector<std::pair<int,double> > >& interpMapValue);
  void convertRemapInfo(std::map<int,std::vector<std::pair<int,double> > >& interpMapValue);

private:
  CArray<double,1> renormalizationFactor ;
  CArray<bool,1> allMissing ;
  bool detectMissingValue ;
  bool renormalize ;
  bool quantity ;
  
  CInterpolateDomain* interpDomain_;
  bool writeToFile_;
  bool readFromFile_;
  StdString fileToReadWrite_;
  bool fortranConvention ;

  // class WriteNetCdf;
  class WriteNetCdf : public CNc4DataOutput
  {
  public:
    WriteNetCdf(const StdString& filename, const MPI_Comm comm);
    int addDimensionWrite(const StdString& name, const StdSize size = UNLIMITED_DIM);
    int addVariableWrite(const StdString& name, nc_type type,
                         const std::vector<StdString>& dim);
    void endDefinition();
    void writeDataIndex(const CArray<int,1>& data, const StdString& name,
                        bool collective, StdSize record,
                        const std::vector<StdSize>* start = NULL,
                        const std::vector<StdSize>* count = NULL);
    void writeDataIndex(const CArray<double,1>& data, const StdString& name,
                        bool collective, StdSize record,
                        const std::vector<StdSize>* start = NULL,
                        const std::vector<StdSize>* count = NULL);
  };


private:

  static CGenericAlgorithmTransformation* create(CGrid* gridDst, CGrid* gridSrc,
                                                CTransformation<CDomain>* transformation,
                                                int elementPositionInGrid,
                                                std::map<int, int>& elementPositionInGridSrc2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridSrc2AxisPosition,
                                                std::map<int, int>& elementPositionInGridSrc2DomainPosition,
                                                std::map<int, int>& elementPositionInGridDst2ScalarPosition,
                                                std::map<int, int>& elementPositionInGridDst2AxisPosition,
                                                std::map<int, int>& elementPositionInGridDst2DomainPosition);
};

}
#endif // __XIOS_DOMAIN_ALGORITHM_INTERPOLATE_HPP__
