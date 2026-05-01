#include "xios.hpp"
#include "generate_interface.hpp"
#include "indent.hpp"
#include "attribute_template.hpp"
#include "object_template.hpp"
#include "group_template.hpp"
#include "node_type.hpp"

int main (int argc, char ** argv, char ** UNUSED (env))
{
//  string path="./src/attr_interface/";
  string path="./interface/";

  CContext* context=CContext::create("interface");
  CCalendarWrapper calendarWrapper;
  CScalar scalar;
  CScalarGroup scalargroup;
  CAxis axis;
  CAxisGroup axisgroup;
  CField field;
  CFieldGroup fieldgroup;
  CVariable variable;
  CVariableGroup variablegroup;
  CDomain domain;
  CDomainGroup domaingroup;
  CGrid grid;
  CGridGroup gridgroup;

  CFile afile;
  CFileGroup filegroup;

  CInterpolateDomain interpolateDomain;
  CZoomDomain zoomDomain;
  CGenerateRectilinearDomain genDomain;
  CComputeConnectivityDomain compConDomain;
  CExpandDomain expandDomain;
  CReorderDomain reorderDomain;
  CExtractDomain extractDomain;

  CInterpolateAxis interpolateAxis;
  CZoomAxis zoomAxis;
  CInverseAxis inverseAxis;
  CExtractAxis extractAxis;

  CReduceDomainToAxis reduceDomainToAxis;
  CReduceAxisToAxis reduceAxisToAxis;
  CExtractDomainToAxis extractDomainToAxis;
  CTemporalSplitting temporalSplitting;

  CReduceAxisToScalar reduceAxisToScalar;
  CExtractAxisToScalar extractAxisToScalar;
  CReduceDomainToScalar reduceDomainToScalar;
  CDuplicateScalarToAxis duplicateScalarToAxis;
  CReduceScalarToScalar reduceScalarToScalar;
  
  ostringstream oss;
  ofstream file;

  file.open((path+"scalar_interface_attr.F90").c_str());
  scalar.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icscalar_attr.cpp").c_str());
  scalar.generateCInterface(file);
  file.close();

  file.open((path+"iscalar_attr.F90").c_str());
  scalar.generateFortranInterface(file);
  file.close();

  file.open((path+"scalargroup_interface_attr.F90").c_str());
  scalargroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icscalargroup_attr.cpp").c_str());
  scalargroup.generateCInterface(file);
  file.close();

  file.open((path+"iscalargroup_attr.F90").c_str());
  scalargroup.generateFortranInterface(file);
  file.close();

  file.open((path+"axis_interface_attr.F90").c_str());
  axis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icaxis_attr.cpp").c_str());
  axis.generateCInterface(file);
  file.close();

  file.open((path+"iaxis_attr.F90").c_str());
  axis.generateFortranInterface(file);
  file.close();

  file.open((path+"axisgroup_interface_attr.F90").c_str());
  axisgroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icaxisgroup_attr.cpp").c_str());
  axisgroup.generateCInterface(file);
  file.close();

  file.open((path+"iaxisgroup_attr.F90").c_str());
  axisgroup.generateFortranInterface(file);
  file.close();

  file.open((path+"domain_interface_attr.F90").c_str());
  domain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icdomain_attr.cpp").c_str());
  domain.generateCInterface(file);
  file.close();

  file.open((path+"idomain_attr.F90").c_str());
  domain.generateFortranInterface(file);
  file.close();

  file.open((path+"domaingroup_interface_attr.F90").c_str());
  domaingroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icdomaingroup_attr.cpp").c_str());
  domaingroup.generateCInterface(file);
  file.close();

  file.open((path+"idomaingroup_attr.F90").c_str());
  domaingroup.generateFortranInterface(file);
  file.close();


  file.open((path+"grid_interface_attr.F90").c_str());
  grid.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icgrid_attr.cpp").c_str());
  grid.generateCInterface(file);
  file.close();

  file.open((path+"igrid_attr.F90").c_str());
  grid.generateFortranInterface(file);
  file.close();

  file.open((path+"gridgroup_interface_attr.F90").c_str());
  gridgroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icgridgroup_attr.cpp").c_str());
  gridgroup.generateCInterface(file);
  file.close();

  file.open((path+"igridgroup_attr.F90").c_str());
  gridgroup.generateFortranInterface(file);
  file.close();


  file.open((path+"field_interface_attr.F90").c_str());
  field.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icfield_attr.cpp").c_str());
  field.generateCInterface(file);
  file.close();

  file.open((path+"ifield_attr.F90").c_str());
  field.generateFortranInterface(file);
  file.close();

  file.open((path+"fieldgroup_interface_attr.F90").c_str());
  fieldgroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icfieldgroup_attr.cpp").c_str());
  fieldgroup.generateCInterface(file);
  file.close();

  file.open((path+"ifieldgroup_attr.F90").c_str());
  fieldgroup.generateFortranInterface(file);
  file.close();



  file.open((path+"variable_interface_attr.F90").c_str());
  variable.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icvariable_attr.cpp").c_str());
  variable.generateCInterface(file);
  file.close();

  file.open((path+"ivariable_attr.F90").c_str());
  variable.generateFortranInterface(file);
  file.close();

  file.open((path+"variablegroup_interface_attr.F90").c_str());
  variablegroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icvariablegroup_attr.cpp").c_str());
  variablegroup.generateCInterface(file);
  file.close();

  file.open((path+"ivariablegroup_attr.F90").c_str());
  variablegroup.generateFortranInterface(file);
  file.close();



  file.open((path+"file_interface_attr.F90").c_str());
  afile.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icfile_attr.cpp").c_str());
  afile.generateCInterface(file);
  file.close();

  file.open((path+"ifile_attr.F90").c_str());
  afile.generateFortranInterface(file);
  file.close();

  file.open((path+"filegroup_interface_attr.F90").c_str());
  filegroup.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icfilegroup_attr.cpp").c_str());
  filegroup.generateCInterface(file);
  file.close();

  file.open((path+"ifilegroup_attr.F90").c_str());
  filegroup.generateFortranInterface(file);
  file.close();


  file.open((path+"calendar_wrapper_interface_attr.F90").c_str());
  calendarWrapper.generateFortran2003Interface(file);
  file.close();

  file.open((path+"iccalendar_wrapper_attr.cpp").c_str());
  calendarWrapper.generateCInterface(file);
  file.close();

  file.open((path+"icalendar_wrapper_attr.F90").c_str());
  calendarWrapper.generateFortranInterface(file);
  file.close();

  /*!
    Domain transformations
  */
  file.open((path+"zoom_domain_interface_attr.F90").c_str());
  zoomDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"iczoom_domain_attr.cpp").c_str());
  zoomDomain.generateCInterface(file);
  file.close();

  file.open((path+"izoom_domain_attr.F90").c_str());
  zoomDomain.generateFortranInterface(file);
  file.close();

  file.open((path+"interpolate_domain_interface_attr.F90").c_str());
  interpolateDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icinterpolate_domain_attr.cpp").c_str());
  interpolateDomain.generateCInterface(file);
  file.close();

  file.open((path+"iinterpolate_domain_attr.F90").c_str());
  interpolateDomain.generateFortranInterface(file);
  file.close();

  file.open((path+"generate_rectilinear_domain_interface_attr.F90").c_str());
  genDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icgenerate_rectilinear_domain_attr.cpp").c_str());
  genDomain.generateCInterface(file);
  file.close();

  file.open((path+"igenerate_rectilinear_domain_attr.F90").c_str());
  genDomain.generateFortranInterface(file);
  file.close();

  file.open((path+"compute_connectivity_domain_interface_attr.F90").c_str());
  compConDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"iccompute_connectivity_domain_attr.cpp").c_str());
  compConDomain.generateCInterface(file);
  file.close();

  file.open((path+"icompute_connectivity_domain_attr.F90").c_str());
  compConDomain.generateFortranInterface(file);
  file.close();

  file.open((path+"expand_domain_interface_attr.F90").c_str());
  expandDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icexpand_domain_attr.cpp").c_str());
  expandDomain.generateCInterface(file);
  file.close();

  file.open((path+"iexpand_domain_attr.F90").c_str());
  expandDomain.generateFortranInterface(file);
  file.close();

  file.open((path+"reorder_domain_interface_attr.F90").c_str());
  reorderDomain.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icreorder_domain_attr.cpp").c_str());
  reorderDomain.generateCInterface(file);
  file.close();

  file.open((path+"ireorder_domain_attr.F90").c_str());
  reorderDomain.generateFortranInterface(file);
  file.close();
  
  /*!
    Axis transformations
  */
  file.open((path+"zoom_axis_interface_attr.F90").c_str());
  zoomAxis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"iczoom_axis_attr.cpp").c_str());
  zoomAxis.generateCInterface(file);
  file.close();

  file.open((path+"izoom_axis_attr.F90").c_str());
  zoomAxis.generateFortranInterface(file);
  file.close();

  file.open((path+"interpolate_axis_interface_attr.F90").c_str());
  interpolateAxis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icinterpolate_axis_attr.cpp").c_str());
  interpolateAxis.generateCInterface(file);
  file.close();

  file.open((path+"iinterpolate_axis_attr.F90").c_str());
  interpolateAxis.generateFortranInterface(file);
  file.close();

  file.open((path+"inverse_axis_interface_attr.F90").c_str());
  inverseAxis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"extract_axis_interface_attr.F90").c_str());
  extractAxis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icinverse_axis_attr.cpp").c_str());
  inverseAxis.generateCInterface(file);
  file.close();

  file.open((path+"iinverse_axis_attr.F90").c_str());
  inverseAxis.generateFortranInterface(file);
  file.close();

  file.open((path+"reduce_domain_to_axis_interface_attr.F90").c_str());
  reduceDomainToAxis.generateFortran2003Interface(file);
  file.close();
 
  file.open((path+"icreduce_domain_to_axis_attr.cpp").c_str());
  reduceDomainToAxis.generateCInterface(file);
  file.close();

  file.open((path+"ireduce_domain_to_axis_attr.F90").c_str());
  reduceDomainToAxis.generateFortranInterface(file);
  file.close();

  file.open((path+"reduce_axis_to_axis_interface_attr.F90").c_str());
  reduceAxisToAxis.generateFortran2003Interface(file);
  file.close();
 
  file.open((path+"icreduce_axis_to_axis_attr.cpp").c_str());
  reduceAxisToAxis.generateCInterface(file);
  file.close();

  file.open((path+"ireduce_axis_to_axis_attr.F90").c_str());
  reduceAxisToAxis.generateFortranInterface(file);
  file.close();
  
  file.open((path+"extract_domain_to_axis_interface_attr.F90").c_str());
  extractDomainToAxis.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icextract_domain_to_axis_attr.cpp").c_str());
  extractDomainToAxis.generateCInterface(file);
  file.close();

  file.open((path+"iextract_domain_to_axis_attr.F90").c_str());
  extractDomainToAxis.generateFortranInterface(file);
  file.close();


  file.open((path+"temporal_splitting_interface_attr.F90").c_str());
  temporalSplitting.generateFortran2003Interface(file);
  file.close();

  file.open((path+"ictemporal_splitting_attr.cpp").c_str());
  temporalSplitting.generateCInterface(file);
  file.close();

  file.open((path+"itemporal_splitting_attr.F90").c_str());
  temporalSplitting.generateFortranInterface(file);
  file.close();


  file.open((path+"duplicate_scalar_to_axis_interface_attr.F90").c_str());
  duplicateScalarToAxis.generateFortran2003Interface(file);
  file.close();
  
  file.open((path+"icduplicate_scalar_to_axis_attr.cpp").c_str());
  duplicateScalarToAxis.generateCInterface(file);
  file.close();
  
  file.open((path+"iduplicate_scalar_to_axis_attr.F90").c_str());
  duplicateScalarToAxis.generateFortranInterface(file);
  file.close();
  /*!
    Scalar transformations
  */
  file.open((path+"reduce_axis_to_scalar_interface_attr.F90").c_str());
  reduceAxisToScalar.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icreduce_axis_to_scalar_attr.cpp").c_str());
  reduceAxisToScalar.generateCInterface(file);
  file.close();

  file.open((path+"ireduce_axis_to_scalar_attr.F90").c_str());
  reduceAxisToScalar.generateFortranInterface(file);
  file.close();

  file.open((path+"extract_axis_to_scalar_interface_attr.F90").c_str());
  extractAxisToScalar.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icextract_axis_to_scalar_attr.cpp").c_str());
  extractAxisToScalar.generateCInterface(file);
  file.close();

  file.open((path+"iextract_axis_to_scalar_attr.F90").c_str());
  extractAxisToScalar.generateFortranInterface(file);
  file.close();


  file.open((path+"reduce_domain_to_scalar_interface_attr.F90").c_str());
  reduceDomainToScalar.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icreduce_domain_to_scalar_attr.cpp").c_str());
  reduceDomainToScalar.generateCInterface(file);
  file.close();

  file.open((path+"ireduce_domain_to_scalar_attr.F90").c_str());
  reduceDomainToScalar.generateFortranInterface(file);
  file.close();


  file.open((path+"reduce_scalar_to_scalar_interface_attr.F90").c_str());
  reduceScalarToScalar.generateFortran2003Interface(file);
  file.close();

  file.open((path+"icreduce_scalar_to_scalar_attr.cpp").c_str());
  reduceScalarToScalar.generateCInterface(file);
  file.close();

  file.open((path+"ireduce_scalar_to_scalar_attr.F90").c_str());
  reduceScalarToScalar.generateFortranInterface(file);
  file.close();





  file.open((path+"context_interface_attr.F90").c_str());
  context->generateFortran2003Interface(file);
  file.close();

  file.open((path+"iccontext_attr.cpp").c_str());
  context->generateCInterface(file);
  file.close();

  file.open((path+"icontext_attr.F90").c_str());
  context->generateFortranInterface(file);
  file.close();
}
