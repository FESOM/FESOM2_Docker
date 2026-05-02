#include "nc4_data_input.hpp"

#include "context.hpp"
#include "context_server.hpp"
#include "context_client.hpp"
#include "domain.hpp"
#include "axis.hpp"
#include "scalar.hpp"

namespace xios
{
  CNc4DataInput::CNc4DataInput(const StdString& filename, MPI_Comm comm_file, bool multifile, bool isCollective /*= true*/,
                               bool readMetaDataPar /*= false*/, bool ugridConvention /*= false*/, const StdString& timeCounterName /*= "time_counter"*/)
    : SuperClass()
    , SuperClassWriter(filename, &comm_file, multifile, readMetaDataPar, timeCounterName)
    , comm_file(comm_file)
    , filename(filename)
    , isCollective(isCollective)
    , ugridConvention(ugridConvention)
    , readMetaDataDomains_(), readValueDomains_()
    , readMetaDataAxis_(), readValueAxis_()
    , readMetaDataScalar_(), readValueScalar_()
  {
    SuperClass::type = multifile ? MULTI_FILE : ONE_FILE;
  }

  CNc4DataInput::~CNc4DataInput(void)
  { /* Nothing more to do */ }

  StdSize CNc4DataInput::getFieldNbRecords_(CField* field)
  TRY
  {
    StdString fieldId = field->getFieldOutputName();

    if (SuperClassWriter::isTemporal(fieldId))
    {
      return SuperClassWriter::getDimensions(&fieldId)[SuperClassWriter::getTimeCounterName()];
    }

    return 1;
  }
  CATCH

  void CNc4DataInput::readFieldData_(CField* field)
  TRY
  {
    CContext* context = CContext::getCurrent();
    CContextServer* server = context->server;

    CGrid* grid = field->grid;

    if (!grid->doGridHaveDataToWrite())
      if (SuperClass::type==MULTI_FILE || !isCollective) return;

    StdString fieldId = field->getFieldOutputName();

    CArray<double,1> fieldData(grid->getWrittenDataSize());
    if (!field->default_value.isEmpty()) fieldData = field->default_value;

    switch (SuperClass::type)
    {
      case MULTI_FILE:
        SuperClassWriter::getData(fieldData, fieldId, isCollective, (field->getNStep() - 1)%field->nstepMax );
        break;
      case ONE_FILE:
      {
        std::vector<StdSize> start, count;

        CArray<int,1> axisDomainOrder = grid->axis_domain_order;
        std::vector<StdString> domainList = grid->getDomainList();
        std::vector<StdString> axisList   = grid->getAxisList();
        int numElement = axisDomainOrder.numElements();
        int idxDomain = domainList.size() - 1, idxAxis = axisList.size() - 1;
        int idx = domainList.size() * 2 + axisList.size() - 1;

        start.reserve(idx+1);
        count.reserve(idx+1);

        for (int i = numElement - 1; i >= 0; --i)
        {
          if (2 == axisDomainOrder(i))
          {
            CDomain* domain = CDomain::get(domainList[idxDomain]);
            if ((domain->type) != CDomain::type_attr::unstructured)
            {
              start.push_back(domain->jbegin);
              count.push_back(domain->nj);
            }
            start.push_back(domain->ibegin);
            count.push_back(domain->ni);
            --idxDomain;
          }
          else if (1 == axisDomainOrder(i))
          {
            CAxis* axis = CAxis::get(axisList[idxAxis]);
            start.push_back(axis->begin);
            count.push_back(axis->n);
            --idxAxis ;
          }
          else
          {
            if (1 == axisDomainOrder.numElements())
            {
              start.push_back(0);
              count.push_back(1);
            }
          }
        }

        SuperClassWriter::getData(fieldData, fieldId, isCollective, (field->getNStep() - 1)%field->nstepMax, &start, &count);
        break;
      }
    }

    field->inputField(fieldData);

    if (!field->scale_factor.isEmpty() || !field->add_offset.isEmpty())
    {
      double scaleFactor = 1.0, addOffset = 0.0;
      if (!field->scale_factor.isEmpty()) scaleFactor = field->scale_factor;
      if (!field->add_offset.isEmpty()) addOffset = field->add_offset;
      field->invertScaleFactorAddOffset(scaleFactor, addOffset);
    }
  }
  CATCH

  void CNc4DataInput::readFieldAttributes_(CField* field, bool readAttributeValues)
  TRY
  {
    StdString fieldId = field->getFieldOutputName();

    CGrid* grid = field->grid;

    std::vector<CDomain*> domainP = grid->getDomains();
    std::vector<CAxis*> axisP = grid->getAxis();
    std::vector<CScalar*> scalarP = grid->getScalars();
    int gridDim = domainP.size() * 2 + axisP.size();

    // Nothing to do with scalar without timestep
    if ((0 == gridDim) && (!SuperClassWriter::isTemporal(fieldId))) 
      return;

    // Verify the compatibility of dimension of declared grid and real grid in file
    int realGridDim = 1;
    bool isUnstructuredGrid = ((gridDim < 2) ? false :  SuperClassWriter::isUnstructured(fieldId));
    std::map<StdString, StdSize> dimSizeMap = SuperClassWriter::getDimensions(&fieldId);
    std::list<StdString> dimList = SuperClassWriter::getDimensionsList(&fieldId);

    realGridDim = SuperClassWriter::isTemporal(fieldId) ? dimSizeMap.size() - 1 : dimSizeMap.size();
    if (isUnstructuredGrid) ++realGridDim;

    if (gridDim != realGridDim)
       ERROR("CNc4DataInput::readFieldAttributes_(CField* field, bool readAttributeValues)",
        << "Field '" << fieldId << "' has incorrect dimension " << std::endl
        << "Verify dimension of grid defined by 'grid_ref' or 'domain_ref'/'axis_ref' and dimension of grid in read file.");

    // Remove unlimited dimension from the map, we dont need it anymore
    if (SuperClassWriter::isTemporal(fieldId))
    {
      dimSizeMap.erase(SuperClassWriter::getTimeCounterName());
      dimList.pop_front() ;  // assume time dimension is first
    }

    std::list<std::pair<StdString, StdSize> > listDimSize;
/*
    for (std::map<StdString, StdSize>::const_iterator itMap = dimSizeMap.begin(); itMap != dimSizeMap.end(); ++itMap)
      listDimSize.push_front(*itMap);
*/

//    if (!SuperClassWriter::isRectilinear(fieldId))
    if (true)
    {
      for (std::list<StdString>::const_iterator it = dimList.begin(); it != dimList.end(); ++it)
        listDimSize.push_front(*dimSizeMap.find(*it));
    }
    else
    {
       std::list<StdString> coords = SuperClassWriter::getCoordinatesIdList(fieldId);
       std::list<StdString>::const_iterator itCoord = coords.begin();
       for (; itCoord != coords.end(); itCoord++)
       {
         const StdString& coord = *itCoord;
         if (SuperClassWriter::hasVariable(coord) && !SuperClassWriter::isTemporal(coord))
         {
           std::map<StdString, StdSize> dimsTmp = SuperClassWriter::getDimensions(&coord);
           StdString dimNameTmp = dimsTmp.begin()->first;
           StdSize dimSizeTmp = dimsTmp.begin()->second;
           listDimSize.push_front(make_pair(coord, dimSizeTmp));
           dimSizeMap.erase(dimNameTmp);
           dimList.remove(dimNameTmp);
         }
       }
       for (std::list<StdString>::const_iterator it = dimList.begin(); it != dimList.end(); ++it)
        listDimSize.push_front(*dimSizeMap.find(*it));
    }
    
    // read specific field attribute
    if (field->add_offset.isEmpty())
    {
      if (SuperClassWriter::hasAttribute<float>("add_offset",&fieldId)) 
        field->add_offset =  SuperClassWriter::getAttributeValue<float>("add_offset",&fieldId)[0] ;
      else if (SuperClassWriter::hasAttribute<double>("add_offset",&fieldId))
        field->add_offset =  SuperClassWriter::getAttributeValue<double>("add_offset",&fieldId)[0] ;
    }

    if (field->scale_factor.isEmpty())
    {
      if (SuperClassWriter::hasAttribute<float>("scale_factor",&fieldId)) 
        field->scale_factor =  SuperClassWriter::getAttributeValue<float>("scale_factor",&fieldId)[0] ;
      else if (SuperClassWriter::hasAttribute<double>("scale_factor",&fieldId))
        field->scale_factor =  SuperClassWriter::getAttributeValue<double>("scale_factor",&fieldId)[0] ;
    }

    // Now process domain and axis
    CArray<int,1> axisDomainOrder = grid->axis_domain_order;
    int numElement = domainP.size() + axisP.size() + scalarP.size();
    int elementPosition = 0;
    int idxDomain = 0, idxAxis = 0, idxScalar = 0;

    std::pair<std::set<StdString>::iterator,bool> it;
    for (int i = 0; i < numElement; ++i)
    {
      if(2 == axisDomainOrder(i))
      {
        if (readAttributeValues)
        {
           it = readValueDomains_.insert(domainP[idxDomain]->getId());
           if (it.second) readDomainAttributeValueFromFile(domainP[idxDomain], listDimSize, elementPosition, fieldId);
        }
        else
        {
          it = readMetaDataDomains_.insert(domainP[idxDomain]->getId());
          if (it.second) readDomainAttributesFromFile(domainP[idxDomain], listDimSize, elementPosition, fieldId);
        }
        ++idxDomain;
        if (isUnstructuredGrid) ++elementPosition;
        else elementPosition += 2;
      }
      else if (1 == axisDomainOrder(i))
      {
        if (readAttributeValues)
        {
          it = readValueAxis_.insert(axisP[idxAxis]->getId());
          if (it.second) readAxisAttributeValueFromFile(axisP[idxAxis], listDimSize, elementPosition, fieldId);
        }
        else
        {
          it = readMetaDataAxis_.insert(axisP[idxAxis]->getId());
          if (it.second) readAxisAttributesFromFile(axisP[idxAxis], listDimSize, elementPosition, fieldId);
        }
        ++idxAxis;
        ++elementPosition;
      }
      else
      {
        if (readAttributeValues)
        {
          it = readValueScalar_.insert(scalarP[idxScalar]->getId());
          if (it.second) readScalarAttributeValueFromFile(scalarP[idxScalar], listDimSize, elementPosition, fieldId);
        }
        else
        {
          it = readMetaDataScalar_.insert(scalarP[idxScalar]->getId());
          if (it.second) readScalarAttributesFromFile(scalarP[idxScalar], listDimSize, elementPosition, fieldId);
        }
        ++idxScalar;
        ++elementPosition;
      }
    }
  }
  CATCH

  /*!
    Read attributes of a domain from a file
    \param [in] domain domain whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of domain in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readDomainAttributeValueFromFile(CDomain* domain, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                       int elementPosition, const StdString& fieldId)
  TRY
  {
    // There are some optional attributes of a domain to retrieve from file    // + lon lat?
    std::list<std::pair<StdString, StdSize> >::const_iterator itMapNi = dimSizeMap.begin(), itMapNj,
                                                              iteMap  = dimSizeMap.end();

    for (int i = 0; i < elementPosition; ++i, ++itMapNi) {}
    itMapNj = itMapNi; ++itMapNj;

    if ((CDomain::type_attr::rectilinear == domain->type))
    {
      // Ok, try to read some attributes such as longitude and latitude
      bool hasLat = SuperClassWriter::hasVariable(itMapNj->first);
      if (hasLat)
      {
        domain->latvalue_rectilinear_read_from_file.resize(itMapNj->second);
        std::vector<StdSize> nBeginLat(1, 0), nSizeLat(1, itMapNj->second);
        readFieldVariableValue(domain->latvalue_rectilinear_read_from_file, itMapNj->first, nBeginLat, nSizeLat, true);
      }

      bool hasLon = SuperClassWriter::hasVariable(itMapNi->first);
      if (hasLon)
      {
        domain->lonvalue_rectilinear_read_from_file.resize(itMapNi->second);
        std::vector<StdSize> nBeginLon(1, 0), nSizeLon(1, itMapNi->second);
        readFieldVariableValue(domain->lonvalue_rectilinear_read_from_file, itMapNi->first, nBeginLon, nSizeLon, true);
      }      
    }
    else if ((CDomain::type_attr::curvilinear == domain->type))
    {
      // Make sure that if there is no local domain defined on a process, the process still reads just one value.
      int ni, nj, ibegin, jbegin;
      if (domain->ni == 0)
      {
        ni = 1;
        ibegin = 0;
      }
      else
      {
        ni = domain->ni;
        ibegin = domain->ibegin;
      }
      if (domain->nj == 0)
      {
        nj = 1;
        jbegin = 0;
      }
      else
      {
        nj = domain->nj;
        jbegin = domain->jbegin;
      }

      std::vector<StdSize> nBeginLatLon(2), nSizeLatLon(2);
      nBeginLatLon[0] = jbegin; nBeginLatLon[1] = ibegin;
      nSizeLatLon[0]  = nj; nSizeLatLon[1] = ni;

      StdString latName = this->getLatCoordName(fieldId);
      if (SuperClassWriter::hasVariable(latName))
      {
        domain->latvalue_curvilinear_read_from_file.resize(ni, nj);
        readFieldVariableValue(domain->latvalue_curvilinear_read_from_file, latName, nBeginLatLon, nSizeLatLon);
      }
      StdString lonName = this->getLonCoordName(fieldId);
      if (SuperClassWriter::hasVariable(lonName))
      {
        domain->lonvalue_curvilinear_read_from_file.resize(ni, nj);
        readFieldVariableValue(domain->lonvalue_curvilinear_read_from_file, lonName, nBeginLatLon, nSizeLatLon);
      }

      StdString boundsLatName = this->getBoundsId(latName);
      StdString boundsLonName = this->getBoundsId(lonName);

      int nbVertex = 4; //this->getNbVertex(fieldId);
      if (!domain->nvertex.isEmpty() && (domain->nvertex != nbVertex))
      {
        ERROR("void CNc4DataInput::readDomainAttributeValueFromFile(...)",
          << "The domain " << domain->getDomainOutputName()
          << " has nvertex read from file " << this->filename << " and nvertex provided from model"
          << " are not coherent. They should be the same." << std::endl 
          << " nvertex read from file: "<< nbVertex
          << " nvertex from model: "<< domain->nvertex << std::endl);
      } 

      if (SuperClassWriter::hasVariable(boundsLatName) || SuperClassWriter::hasVariable(boundsLonName)) 
        domain->nvertex.setValue(nbVertex);

      std::vector<StdSize> nBeginBndsLatLon(3), nSizeBndsLatLon(3);
      nBeginBndsLatLon[0] = jbegin; nSizeBndsLatLon[0] = nj;
      nBeginBndsLatLon[1] = ibegin; nSizeBndsLatLon[1] = ni;
      nBeginBndsLatLon[2] = 0; nSizeBndsLatLon[2] = nbVertex;

      if (SuperClassWriter::hasVariable(boundsLatName))
      {
        domain->bounds_latvalue_curvilinear_read_from_file.resize(nbVertex, ni, nj);
        readFieldVariableValue(domain->bounds_latvalue_curvilinear_read_from_file, boundsLatName, nBeginBndsLatLon, nSizeBndsLatLon);

      }
      if (SuperClassWriter::hasVariable(boundsLonName)) 
      {
        domain->bounds_lonvalue_curvilinear_read_from_file.resize(nbVertex, ni, nj);
        readFieldVariableValue(domain->bounds_lonvalue_curvilinear_read_from_file, boundsLonName, nBeginBndsLatLon, nSizeBndsLatLon);
      }      
    }
    else if ((CDomain::type_attr::unstructured == domain->type))// || (this->isUnstructured(fieldId)))
    {
      // Make sure that if there is no local domain defined on a process, the process still reads just one value.
      int ni, ibegin;
      if (domain->ni == 0)
      {
        ni = 1;
        ibegin = 0;
      }
      else
      {
        ni = domain->ni;
        ibegin = domain->ibegin;
      }

      std::vector<StdSize> nBeginLatLon(1,0), nSizeLatLon(1,0);
      nBeginLatLon[0] = ibegin;
      nSizeLatLon[0]  = ni;

      StdString latName = this->getLatCoordName(fieldId);
      if (SuperClassWriter::hasVariable(latName))
      {
        domain->latvalue_unstructured_read_from_file.resize(ni);
        readFieldVariableValue(domain->latvalue_unstructured_read_from_file, latName, nBeginLatLon, nSizeLatLon);  
      }

      StdString lonName = this->getLonCoordName(fieldId);
      if (SuperClassWriter::hasVariable(lonName)) //(0 != lonName.compare(""))
      {
        domain->lonvalue_unstructured_read_from_file.resize(ni);
        readFieldVariableValue(domain->lonvalue_unstructured_read_from_file, lonName, nBeginLatLon, nSizeLatLon);
      }

      StdString boundsLatName = this->getBoundsId(latName);
      StdString boundsLonName = this->getBoundsId(lonName);

      if (ugridConvention && domain->nvertex.isEmpty())
      {
        ERROR("void CNc4DataInput::readDomainAttributeValueFromFile(...)",
          << " Attribute nvertex must be specified for domain " << domain->getDomainOutputName()
          << " read from UGRID file " << this->filename << " ."<< std::endl);
      }
//      int nbVertex = this->getNbVertex(fieldId);
      int nbVertex = (ugridConvention) ? domain->nvertex : this->getNbVertex(fieldId);
      if (!domain->nvertex.isEmpty() && (domain->nvertex != nbVertex))
      {
        ERROR("void CNc4DataInput::readDomainAttributeValueFromFile(...)",
          << "The domain " << domain->getDomainOutputName()
          << " has nvertex read from file " << this->filename << " and nvertex provided from model"
          << " are not coherent. They should be the same." << std::endl 
          << " nvertex read from file: "<< nbVertex
          << " nvertex from model: "<< domain->nvertex << std::endl);
      } 
      
      if (SuperClassWriter::hasVariable(boundsLatName) || SuperClassWriter::hasVariable(boundsLonName)) 
        domain->nvertex.setValue(nbVertex);

      std::vector<StdSize> nBeginBndsLatLon(2), nSizeBndsLatLon(2);
      nBeginBndsLatLon[0] = ibegin; nSizeBndsLatLon[0] = ni;
      nBeginBndsLatLon[1] = 0; nSizeBndsLatLon[1] = nbVertex;

      if (SuperClassWriter::hasVariable(boundsLatName)) 
      {
        domain->bounds_latvalue_unstructured_read_from_file.resize(nSizeBndsLatLon[1], nSizeBndsLatLon[0]);
        readFieldVariableValue(domain->bounds_latvalue_unstructured_read_from_file, boundsLatName, nBeginBndsLatLon, nSizeBndsLatLon);
      }

      if (SuperClassWriter::hasVariable(boundsLonName)) 
      {
        domain->bounds_lonvalue_unstructured_read_from_file.resize(nSizeBndsLatLon[1], nSizeBndsLatLon[0]);
        readFieldVariableValue(domain->bounds_lonvalue_unstructured_read_from_file, boundsLonName, nBeginBndsLatLon, nSizeBndsLatLon);
      }      
    }
    domain->fillInLonLat();
  }
  CATCH

  /*!
    Read attribute value of a domain from a file
    \param [in] domain domain whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of domain in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readDomainAttributesFromFile(CDomain* domain, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                   int elementPosition, const StdString& fieldId)
  TRY
  {
    // There are some mandatory attributes of a domain to retrieve from file
    // + ni_glo, nj_glo
    std::list<std::pair<StdString, StdSize> >::const_iterator itMapNi = dimSizeMap.begin(), itMapNj,
                                                              iteMap  = dimSizeMap.end();
    for (int i = 0; i < elementPosition; ++i, ++itMapNi) {}
    itMapNj = itMapNi; ++itMapNj;

    if (CDomain::type_attr::rectilinear == domain->type || CDomain::type_attr::curvilinear == domain->type ||
        this->isRectilinear(fieldId) || this->isCurvilinear(fieldId))
    {
      if (!domain->nj_glo.isEmpty() && (domain->nj_glo != itMapNj->second))
      {
        ERROR("void CNc4DataInput::readDomainAttributesFromFile(...)",
          << "The domain " << domain->getDomainOutputName()
          << " has nj_glo read from file " << this->filename << " and nj_glo provided from model"
          << " are not coherent. They should be the same." << std::endl 
          << " nj_glo read from file: "<< itMapNj->second
          << " nj_glo from model: "<< domain->nj_glo << std::endl);
      } 
      domain->nj_glo.setValue(itMapNj->second);

      if (!domain->ni_glo.isEmpty() && (domain->ni_glo != itMapNi->second))
      {
        ERROR("void CNc4DataInput::readDomainAttributesFromFile(...)",
          << "The domain " << domain->getDomainOutputName()
          << " has ni_glo read from file " << this->filename << " and ni_glo provided from model"
          << " are not coherent. They should be the same." << std::endl 
          << " ni_glo read from file: "<< itMapNi->second
          << " ni_glo from model: "<< domain->ni_glo << std::endl);
      } 
      domain->ni_glo.setValue(itMapNi->second);
    }
    else if (CDomain::type_attr::unstructured == domain->type|| this->isUnstructured(fieldId))
    {
      domain->nj_glo.setValue(1);

      if (!domain->ni_glo.isEmpty() && (domain->ni_glo != itMapNi->second))
      {
        ERROR("void CNc4DataInput::readDomainAttributesFromFile(...)",
          << "The domain " << domain->getDomainOutputName()
          << " has ni_glo read from file " << this->filename << " and ni_glo provided from model"
          << " are not coherent. They should be the same." << std::endl 
          << " ni_glo read from file: "<< itMapNi->second
          << " ni_glo from model: "<< domain->ni_glo << std::endl);
      }       
      domain->ni_glo.setValue(itMapNi->second);
    }

// determine if coordinates values are present in file
    if ((CDomain::type_attr::rectilinear == domain->type))
    {
      // Ok, try to read some attributes such as longitude and latitude
      domain->hasLatInReadFile_ = SuperClassWriter::hasVariable(itMapNj->first);
      domain->hasLonInReadFile_  = SuperClassWriter::hasVariable(itMapNi->first);
    }
    else if ((CDomain::type_attr::curvilinear == domain->type) || (CDomain::type_attr::unstructured == domain->type) )
    {
      StdString latName = this->getLatCoordName(fieldId);
      domain->hasLatInReadFile_ = SuperClassWriter::hasVariable(latName) ;
      StdString lonName = this->getLonCoordName(fieldId);        
      domain->hasLonInReadFile_ = SuperClassWriter::hasVariable(lonName) ; 
      StdString boundsLatName = this->getBoundsId(latName);
      domain->hasBoundsLatInReadFile_ = SuperClassWriter::hasVariable(boundsLatName) ; 
      StdString boundsLonName = this->getBoundsId(lonName);
      domain->hasBoundsLonInReadFile_ = SuperClassWriter::hasVariable(boundsLonName) ;
    }
  }
  CATCH

  /*!
    Read attributes of an axis from a file
    \param [in] axis axis whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of axis in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readAxisAttributesFromFile(CAxis* axis, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                 int elementPosition, const StdString& fieldId)
  TRY
  {
    std::list<std::pair<StdString, StdSize> >::const_iterator itMapN = dimSizeMap.begin(),
                                                              iteMap = dimSizeMap.end();
    for (int i = 0; i < elementPosition; ++i, ++itMapN) {}

    if (!axis->n_glo.isEmpty() && (axis->n_glo != itMapN->second))
    {
      ERROR("void CNc4DataInput::readAxisAttributesFromFile(...)",
        << "The axis " << axis->getAxisOutputName()
        << " has n_glo read from file " << this->filename << " and n_glo provided from model"
        << " are not coherent. They should be the same." << std::endl 
        << " n_glo read from file: "<< itMapN->second
        << " n_glo from model: "<< axis->n_glo << std::endl);
    }    
    axis->n_glo.setValue(itMapN->second);
  }
  CATCH

  /*!
    Read attribute value of an axis from a file
    \param [in] axis axis whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of axis in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readAxisAttributeValueFromFile(CAxis* axis, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                    int elementPosition, const StdString& fieldId)
  TRY
  {
    std::list<std::pair<StdString, StdSize> >::const_iterator itMapN = dimSizeMap.begin(),
                                                              iteMap = dimSizeMap.end();
    for (int i = 0; i < elementPosition; ++i, ++itMapN) {}

    { // Read axis value
      bool hasValue = SuperClassWriter::hasVariable(itMapN->first);
      if (hasValue)
      {
        std::vector<StdSize> nBegin(1, 0), nSize(1, itMapN->second);
        CArray<double,1> readAxisValue(itMapN->second);
        readFieldVariableValue(readAxisValue, itMapN->first, nBegin, nSize, true);
        int begin = 0, n = itMapN->second;
        if (!axis->begin.isEmpty()) begin = axis->begin.getValue();
        if (!axis->n.isEmpty()) n = axis->n.getValue();
        axis->value.resize(n);
        double convertFromFactor=1.0 ;
        if (!axis->convert_from_factor.isEmpty()) convertFromFactor = axis->convert_from_factor ;
        for (int i = 0; i < n; ++i) axis->value(i) = readAxisValue(begin + i)*convertFromFactor;
      }
    }
  }
  CATCH

  /*!
    Read attributes of a scalar from a file
    \param [in] scalar scalar whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of scalar in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readScalarAttributesFromFile(CScalar* scalar, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                  int elementPosition, const StdString& fieldId)
  {
    /*Nothing to do */
  }

  /*!
    Read attribute value of an axis from a file
    \param [in] axis axis whose attributes are read from the file
    \param [in] dimSizeMap Dimensions and and their corresponding names and size read from file
    \param [in] emelentPosition position of axis in grid
    \param [in] fieldId id (or name) associated with the grid
  */
  void CNc4DataInput::readScalarAttributeValueFromFile(CScalar* scalar, std::list<std::pair<StdString, StdSize> >& dimSizeMap,
                                                      int elementPosition, const StdString& fieldId)
  {
    /*Nothing to do */
  }

  void CNc4DataInput::closeFile_(void)
  TRY
  {
    SuperClassWriter::close();
  }
  CATCH
} // namespace xios
