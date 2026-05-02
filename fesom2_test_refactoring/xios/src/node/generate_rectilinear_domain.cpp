#include "generate_rectilinear_domain.hpp"
#include "type.hpp"

namespace xios {

  /// ////////////////////// Définitions ////////////////////// ///

  CGenerateRectilinearDomain::CGenerateRectilinearDomain(void)
    : CObjectTemplate<CGenerateRectilinearDomain>(), CGenerateRectilinearDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CGenerateRectilinearDomain::CGenerateRectilinearDomain(const StdString & id)
    : CObjectTemplate<CGenerateRectilinearDomain>(id), CGenerateRectilinearDomainAttributes(), CTransformation<CDomain>()
  { /* Ne rien faire de plus */ }

  CGenerateRectilinearDomain::~CGenerateRectilinearDomain(void)
  {}

  CTransformation<CDomain>* CGenerateRectilinearDomain::create(const StdString& id, xml::CXMLNode* node)
  {
    CGenerateRectilinearDomain* genDomain = CGenerateRectilinearDomainGroup::get("generate_rectilinear_domain_definition")->createChild(id);
    if (node) genDomain->parse(*node);
    return static_cast<CTransformation<CDomain>*>(genDomain);
  }

  bool CGenerateRectilinearDomain::_dummyRegistered = CGenerateRectilinearDomain::registerTrans();
  bool CGenerateRectilinearDomain::registerTrans()
  {
    return registerTransformation(TRANS_GENERATE_RECTILINEAR_DOMAIN, create);
  }

  //----------------------------------------------------------------

  StdString CGenerateRectilinearDomain::GetName(void)    { return StdString("generate_rectilinear_domain"); }
  StdString CGenerateRectilinearDomain::GetDefName(void) { return StdString("generate_rectilinear_domain"); }
  ENodeType CGenerateRectilinearDomain::GetType(void)    { return eGenerateRectilinearDomain; }

  void CGenerateRectilinearDomain::checkValid(CDomain* domainDst)
  {
    const double defaultBndsLonStart = 0;
    const double defaultBndsLonEnd = 360;

    const double defaultBndsLatStart = -90;
    const double defaultBndsLatEnd = 90;


    int niGlo = domainDst->ni_glo;
    int njGlo = domainDst->nj_glo;


    double deltaLon=(defaultBndsLonEnd-defaultBndsLonStart)/niGlo ; 
    if (!lon_start.isEmpty() && !lon_end.isEmpty() ) deltaLon=(lon_end-lon_start)/(niGlo-1) ;
    if (!bounds_lon_start.isEmpty() && !bounds_lon_end.isEmpty()) deltaLon=(bounds_lon_end-bounds_lon_start)/niGlo ;
    if (!lon_start.isEmpty() && !bounds_lon_end.isEmpty()) deltaLon=(bounds_lon_end-bounds_lon_start)/(niGlo-0.5) ;
    if (!bounds_lon_start.isEmpty() && !lon_end.isEmpty()) deltaLon=(bounds_lon_end-bounds_lon_start)/(niGlo-0.5) ;

    if (lon_start.isEmpty())
    {
      if (!bounds_lon_start.isEmpty())      domainDst->lon_start=bounds_lon_start+0.5*deltaLon ;
      else if (!lon_end.isEmpty())          domainDst->lon_start= lon_end-(niGlo-1.)*deltaLon ;
      else if (!bounds_lon_end.isEmpty())   domainDst->lon_start=bounds_lon_end-(niGlo-0.5)*deltaLon ;
      else                                  domainDst->lon_start=defaultBndsLonStart+0.5*deltaLon ;
    }
    else domainDst->lon_start=lon_start ;

    if (bounds_lon_start.isEmpty())
    {
      if (!lon_start.isEmpty())           domainDst->bounds_lon_start=lon_start-0.5*deltaLon ;
      else if (!lon_end.isEmpty())        domainDst->bounds_lon_start= lon_end-(niGlo-0.5)*deltaLon ;
      else if (!bounds_lon_end.isEmpty()) domainDst->bounds_lon_start=bounds_lon_end-niGlo*deltaLon ;
      else                                domainDst->bounds_lon_start=defaultBndsLonStart ;
    } 
    else domainDst->bounds_lon_start=bounds_lon_start ;

    if (lon_end.isEmpty())
    {
      if (!bounds_lon_end.isEmpty())        domainDst->lon_end=bounds_lon_end-0.5*deltaLon ;
      else if (!bounds_lon_start.isEmpty()) domainDst->lon_end=bounds_lon_start+(niGlo-0.5)*deltaLon ;
      else if (!lon_start.isEmpty())        domainDst->lon_end=lon_start+(niGlo-1.)*deltaLon ;
      else                                  domainDst->lon_end=defaultBndsLonEnd-0.5*deltaLon ;
    }
    else domainDst->lon_end=lon_end ;    

    if (bounds_lon_end.isEmpty())
    {
      if (!lon_end.isEmpty())               domainDst->bounds_lon_end=lon_end+0.5*deltaLon ;
      else if (!bounds_lon_start.isEmpty()) domainDst->bounds_lon_end=bounds_lon_start+niGlo*deltaLon ;
      else if (!lon_start.isEmpty())        domainDst->bounds_lon_end=lon_start+(niGlo-0.5)*deltaLon ;
      else                                  domainDst->bounds_lon_end=defaultBndsLonEnd ;
    }
    else domainDst->bounds_lon_end=bounds_lon_end;




    double deltaLat=(defaultBndsLatEnd-defaultBndsLatStart)/njGlo ; 
    if (!lat_start.isEmpty() && !lat_end.isEmpty() ) deltaLat=(lat_end-lat_start)/(njGlo-1) ;
    if (!bounds_lat_start.isEmpty() && !bounds_lat_end.isEmpty()) deltaLat=(bounds_lat_end-bounds_lat_start)/njGlo ;
    if (!lat_start.isEmpty() && !bounds_lat_end.isEmpty()) deltaLat=(bounds_lat_end-bounds_lat_start)/(njGlo-0.5) ;
    if (!bounds_lat_start.isEmpty() && !lat_end.isEmpty()) deltaLat=(bounds_lat_end-bounds_lat_start)/(njGlo-0.5) ;

    if (lat_start.isEmpty())
    {
      if (!bounds_lat_start.isEmpty())      domainDst->lat_start=bounds_lat_start+0.5*deltaLat ;
      else if (!lat_end.isEmpty())          domainDst->lat_start= lat_end-(njGlo-1.)*deltaLat ;
      else if (!bounds_lat_end.isEmpty())   domainDst->lat_start=bounds_lat_end-(njGlo-0.5)*deltaLat ;
      else                                  domainDst->lat_start=defaultBndsLatStart+0.5*deltaLat ;
    }
    else domainDst->lat_start=lat_start;

    if (bounds_lat_start.isEmpty())
    {
      if (!lat_start.isEmpty())           domainDst->bounds_lat_start=lat_start-0.5*deltaLat ;
      else if (!lat_end.isEmpty())        domainDst->bounds_lat_start= lat_end-(njGlo-0.5)*deltaLat ;
      else if (!bounds_lat_end.isEmpty()) domainDst->bounds_lat_start=bounds_lat_end-njGlo*deltaLat ;
      else                                domainDst->bounds_lat_start=defaultBndsLatStart ;
    } 
    else domainDst->bounds_lat_start=bounds_lat_start;
    
    if (lat_end.isEmpty())
    {
      if (!bounds_lat_end.isEmpty())        domainDst->lat_end=bounds_lat_end-0.5*deltaLat ;
      else if (!bounds_lat_start.isEmpty()) domainDst->lat_end=bounds_lat_start+(njGlo-0.5)*deltaLat ;
      else if (!lat_start.isEmpty())        domainDst->lat_end=lat_start+(njGlo-1.)*deltaLat ;
      else                                  domainDst->lat_end=defaultBndsLatEnd-0.5*deltaLat ;
    }    
    else domainDst->lat_end=lat_end;
    
    if (bounds_lat_end.isEmpty())
    {
      if (!lat_end.isEmpty())               domainDst->bounds_lat_end=lat_end+0.5*deltaLat ;
      else if (!bounds_lat_start.isEmpty()) domainDst->bounds_lat_end=bounds_lat_start+njGlo*deltaLat ;
      else if (!lat_start.isEmpty())        domainDst->bounds_lat_end=lat_start+(njGlo-0.5)*deltaLat ;
      else                                  domainDst->bounds_lat_end=defaultBndsLatEnd ;
    }
    else domainDst->bounds_lat_end=bounds_lat_end;

  }

}
