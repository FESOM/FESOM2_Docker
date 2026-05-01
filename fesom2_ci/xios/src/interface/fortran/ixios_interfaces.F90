#include "xios_fortran_prefix.hpp"

MODULE XIOS_INTERFACES

USE icontext, ONLY : xios(get_context_handle)

USE icontext_attr, ONLY : xios(set_context_attr_hdl), xios(get_context_attr_hdl), xios(is_defined_context_attr_hdl)

USE idata, ONLY : xios(send_field_r8_0d), xios(send_field_r8_1d), xios(send_field_r8_2d), xios(send_field_r8_3d), &
                  xios(send_field_r8_4d), xios(send_field_r8_5d), xios(send_field_r8_6d), xios(send_field_r8_7d), &
                  xios(send_field_r4_0d), xios(send_field_r4_1d), xios(send_field_r4_2d), xios(send_field_r4_3d), &
                  xios(send_field_r4_4d), xios(send_field_r4_5d), xios(send_field_r4_6d), xios(send_field_r4_7d), &
                  xios(send_field_r8_0d_hdl), xios(send_field_r8_1d_hdl), xios(send_field_r8_2d_hdl), xios(send_field_r8_3d_hdl), &
                  xios(send_field_r8_4d_hdl), xios(send_field_r8_5d_hdl), xios(send_field_r8_6d_hdl), xios(send_field_r8_7d_hdl), &
                  xios(send_field_r4_0d_hdl), xios(send_field_r4_1d_hdl), xios(send_field_r4_2d_hdl), xios(send_field_r4_3d_hdl), &
                  xios(send_field_r4_4d_hdl), xios(send_field_r4_5d_hdl), xios(send_field_r4_6d_hdl), xios(send_field_r4_7d_hdl), &
                  xios(send_field_tiled_r8_1d), xios(send_field_tiled_r8_2d), &
                  xios(send_field_tiled_r8_3d), xios(send_field_tiled_r8_4d), &
                  xios(send_field_tiled_r8_5d), xios(send_field_tiled_r8_6d), xios(send_field_tiled_r8_7d), &
                  xios(send_field_tiled_r4_1d), xios(send_field_tiled_r4_2d), &
                  xios(send_field_tiled_r4_3d), xios(send_field_tiled_r4_4d), &
                  xios(send_field_tiled_r4_5d), xios(send_field_tiled_r4_6d), xios(send_field_tiled_r4_7d), &
                  xios(recv_field_r8_0d), xios(recv_field_r8_1d), xios(recv_field_r8_2d), xios(recv_field_r8_3d), &
                  xios(recv_field_r8_4d), xios(recv_field_r8_5d), xios(recv_field_r8_6d), xios(recv_field_r8_7d), &
                  xios(recv_field_r4_0d), xios(recv_field_r4_1d), xios(recv_field_r4_2d), xios(recv_field_r4_3d), &
                  xios(recv_field_r4_4d), xios(recv_field_r4_5d), xios(recv_field_r4_6d), xios(recv_field_r4_7d), &
                  xios(recv_field_r8_0d_hdl), xios(recv_field_r8_1d_hdl), xios(recv_field_r8_2d_hdl), xios(recv_field_r8_3d_hdl), &
                  xios(recv_field_r8_4d_hdl), xios(recv_field_r8_5d_hdl), xios(recv_field_r8_6d_hdl), xios(recv_field_r8_7d_hdl), &
                  xios(recv_field_r4_0d_hdl), xios(recv_field_r4_1d_hdl), xios(recv_field_r4_2d_hdl), xios(recv_field_r4_3d_hdl), &
                  xios(recv_field_r4_4d_hdl), xios(recv_field_r4_5d_hdl), xios(recv_field_r4_6d_hdl), xios(recv_field_r4_7d_hdl), &
                  xios(getVar_k8), xios(getVar_k4), xios(getVar_int), xios(getVar_logic), xios(getVar_char),      &
                  xios(setVar_k8), xios(setVar_k4), xios(setVar_int), xios(setVar_logic), xios(setVar_char)

USE idomain, ONLY : xios(get_domain_handle), xios(get_domaingroup_handle)

USE idomain_attr, ONLY : xios(set_domain_attr_hdl), xios(get_domain_attr_hdl), xios(is_defined_domain_attr_hdl)

USE idomaingroup_attr, ONLY : xios(set_domaingroup_attr_hdl), xios(get_domaingroup_attr_hdl), xios(is_defined_domaingroup_attr_hdl)

USE ifield, ONLY : xios(get_field_handle), xios(get_fieldgroup_handle), xios(field_is_active_id), xios(field_is_active_hdl), &
                   xios(field_get_domain_handle), xios(field_get_axis_handle), xios(field_get_scalar_handle), &
                   xios(field_id_get_domain_handle), xios(field_id_get_axis_handle), xios(field_id_get_scalar_handle)

USE ifield_attr, ONLY : xios(set_field_attr_hdl), xios(get_field_attr_hdl), xios(is_defined_field_attr_hdl)

USE ifieldgroup_attr, ONLY : xios(set_fieldgroup_attr_hdl), xios(get_fieldgroup_attr_hdl), xios(is_defined_fieldgroup_attr_hdl)

USE ivariable, ONLY : xios(get_variable_handle), xios(get_variablegroup_handle)

USE ivariable_attr, ONLY : xios(set_variable_attr_hdl), xios(get_variable_attr_hdl), xios(is_defined_variable_attr_hdl)

USE ivariablegroup_attr, ONLY : xios(set_variablegroup_attr_hdl), xios(get_variablegroup_attr_hdl), &
                                xios(is_defined_variablegroup_attr_hdl)

USE ifile, ONLY : xios(get_file_handle), xios(get_filegroup_handle)

USE ifile_attr, ONLY : xios(set_file_attr_hdl), xios(get_file_attr_hdl), xios(is_defined_file_attr_hdl)

USE ifilegroup_attr, ONLY : xios(set_filegroup_attr_hdl), xios(get_filegroup_attr_hdl), xios(is_defined_filegroup_attr_hdl)

USE igrid, ONLY : xios(get_grid_handle), xios(get_gridgroup_handle)

USE igrid_attr, ONLY : xios(set_grid_attr_hdl), xios(get_grid_attr_hdl), xios(is_defined_grid_attr_hdl)

USE igridgroup_attr, ONLY : xios(set_gridgroup_attr_hdl), xios(get_gridgroup_attr_hdl), xios(is_defined_gridgroup_attr_hdl)

USE iaxis, ONLY : xios(get_axis_handle), xios(get_axisgroup_handle)

USE iaxis_attr, ONLY : xios(set_axis_attr_hdl), xios(get_axis_attr_hdl), xios(is_defined_axis_attr_hdl)

USE iaxisgroup_attr, ONLY : xios(set_axisgroup_attr_hdl), xios(get_axisgroup_attr_hdl), xios(is_defined_axisgroup_attr_hdl)

USE iscalar, ONLY : xios(get_scalar_handle), xios(get_scalargroup_handle)

USE iscalar_attr, ONLY : xios(set_scalar_attr_hdl), xios(get_scalar_attr_hdl), xios(is_defined_scalar_attr_hdl)

USE iscalargroup_attr, ONLY : xios(set_scalargroup_attr_hdl), xios(get_scalargroup_attr_hdl), xios(is_defined_scalargroup_attr_hdl)

!-------------------------------------------------------------------------------
!!! Transformation INTERFACES
!-------------------------------------------------------------------------------
!!! DOMAIN TRANSFORMATIONS
USE izoom_domain, ONLY : xios(get_zoom_domain_handle)

USE izoom_domain_attr, ONLY : xios(set_zoom_domain_attr_hdl), xios(get_zoom_domain_attr_hdl), xios(is_defined_zoom_domain_attr_hdl)

USE iinterpolate_domain, ONLY : xios(get_interpolate_domain_handle)

USE iinterpolate_domain_attr, ONLY : xios(set_interpolate_domain_attr_hdl), xios(get_interpolate_domain_attr_hdl), &
                                     xios(is_defined_interpolate_domain_attr_hdl)

USE igenerate_rectilinear_domain, ONLY : xios(get_generate_rectilinear_domain_handle)

USE igenerate_rectilinear_domain_attr, ONLY : xios(set_generate_rectilinear_domain_attr_hdl), &
                                              xios(get_generate_rectilinear_domain_attr_hdl), &
                                              xios(is_defined_generate_rectilinear_domain_attr_hdl)

USE icompute_connectivity_domain, ONLY : xios(get_compute_connectivity_domain_handle)

USE icompute_connectivity_domain_attr, ONLY : xios(set_compute_connectivity_domain_attr_hdl), &
                                              xios(get_compute_connectivity_domain_attr_hdl), &
                                              xios(is_defined_compute_connectivity_domain_attr_hdl)

USE iexpand_domain, ONLY : xios(get_expand_domain_handle)

USE iexpand_domain_attr, ONLY : xios(set_expand_domain_attr_hdl), &
                                xios(get_expand_domain_attr_hdl), &
                                xios(is_defined_expand_domain_attr_hdl)

!!! AXIS TRANSFORMATIONS
USE izoom_axis, ONLY : xios(get_zoom_axis_handle)

USE izoom_axis_attr, ONLY : xios(set_zoom_axis_attr_hdl), xios(get_zoom_axis_attr_hdl), xios(is_defined_zoom_axis_attr_hdl)

USE iinterpolate_axis, ONLY : xios(get_interpolate_axis_handle)

USE iinterpolate_axis_attr, ONLY : xios(set_interpolate_axis_attr_hdl), &
                                   xios(get_interpolate_axis_attr_hdl), &
                                   xios(is_defined_interpolate_axis_attr_hdl)

USE iinverse_axis, ONLY : xios(get_inverse_axis_handle)

USE iinverse_axis_attr, ONLY : xios(set_inverse_axis_attr_hdl), &
                               xios(get_inverse_axis_attr_hdl), &
                               xios(is_defined_inverse_axis_attr_hdl)

USE ireduce_domain_to_axis, ONLY : xios(get_reduce_domain_to_axis_handle)

USE ireduce_domain_to_axis_attr, ONLY : xios(set_reduce_domain_to_axis_attr_hdl), &
                                        xios(get_reduce_domain_to_axis_attr_hdl), &
                                        xios(is_defined_reduce_domain_to_axis_attr_hdl)

USE iextract_domain_to_axis, ONLY : xios(get_extract_domain_to_axis_handle)

USE iextract_domain_to_axis_attr, ONLY : xios(set_extract_domain_to_axis_attr_hdl), &
                                         xios(get_extract_domain_to_axis_attr_hdl), &
                                         xios(is_defined_extract_domain_to_axis_attr_hdl)

!!! SCALAR TRANSFORMATIONS


USE ireduce_axis_to_scalar, ONLY : xios(get_reduce_axis_to_scalar_handle)

USE ireduce_axis_to_scalar_attr, ONLY : xios(set_reduce_axis_to_scalar_attr_hdl), &
                                        xios(get_reduce_axis_to_scalar_attr_hdl), &
                                        xios(is_defined_reduce_axis_to_scalar_attr_hdl)

USE ireduce_domain_to_scalar, ONLY : xios(get_reduce_domain_to_scalar_handle)

USE ireduce_domain_to_scalar_attr, ONLY : xios(set_reduce_domain_to_scalar_attr_hdl), &
                                          xios(get_reduce_domain_to_scalar_attr_hdl), &
                                          xios(is_defined_reduce_domain_to_scalar_attr_hdl)

USE iextract_axis_to_scalar, ONLY : xios(get_extract_axis_to_scalar_handle)

USE iextract_axis_to_scalar_attr, ONLY : xios(set_extract_axis_to_scalar_attr_hdl), &
                                         xios(get_extract_axis_to_scalar_attr_hdl), &
                                         xios(is_defined_extract_axis_to_scalar_attr_hdl)

USE ixml_tree, ONLY : xios(add_axis), xios(add_file), xios(add_grid), xios(add_field), xios(add_domain),   &
                      xios(add_fieldtofile), xios(add_variabletofile), xios(add_variabletofield),          &
                      xios(add_axisgroup), xios(add_filegroup), xios(add_gridgroup), xios(add_fieldgroup), &
                      xios(add_domaingroup), xios(add_fieldgrouptofile), xios(add_variablegrouptofile),    &
                      xios(add_variablegrouptofield), xios(add_axistogrid), xios(add_domaintogrid),        &
                      xios(add_zoomdomaintodomain), xios(add_interpolatedomaintodomain),                   &
                      xios(add_generatedomaintodomain), xios(add_zoomaxistoaxis),                          &
                      xios(add_interpolateaxistoaxis), xios(add_inverseaxistoaxis), xios(add_scalar),      &
                      xios(add_scalargroup), xios(add_scalartogrid), xios(add_reduceaxistoscalartoscalar), &
                      xios(add_computeconnectivitydomaintodomain), xios(add_reducedomaintoaxistoaxis),     &
                      xios(add_extractdomaintoaxistoaxis), xios(add_reducedomaintoscalartoscalar),         &
                      xios(add_extractaxistoscalartoscalar), xios(add_expanddomaintodomain)

PRIVATE

INTERFACE xios(set_attr)
  MODULE PROCEDURE xios(set_domaingroup_attr_hdl), xios(set_domain_attr_hdl), xios(set_fieldgroup_attr_hdl), &
                   xios(set_field_attr_hdl),xios(set_variable_attr_hdl), xios(set_variablegroup_attr_hdl),   &
                   xios(set_file_attr_hdl), xios(set_filegroup_attr_hdl),                                    &
                   xios(set_grid_attr_hdl), xios(set_gridgroup_attr_hdl), xios(set_axis_attr_hdl) ,          &
                   xios(set_axisgroup_attr_hdl), xios(set_context_attr_hdl), xios(set_zoom_axis_attr_hdl),   &
                   xios(set_zoom_domain_attr_hdl), xios(set_interpolate_axis_attr_hdl),                      &
                   xios(set_interpolate_domain_attr_hdl), xios(set_inverse_axis_attr_hdl),                   &
                   xios(set_generate_rectilinear_domain_attr_hdl), xios(set_scalar_attr_hdl),                &
                   xios(set_scalargroup_attr_hdl), xios(set_reduce_axis_to_scalar_attr_hdl),                 &
                   xios(set_compute_connectivity_domain_attr_hdl), xios(set_reduce_domain_to_scalar_attr_hdl), &
                   xios(set_reduce_domain_to_axis_attr_hdl), xios(set_extract_domain_to_axis_attr_hdl),        &
                   xios(set_extract_axis_to_scalar_attr_hdl), xios(set_expand_domain_attr_hdl)
END INTERFACE xios(set_attr)


INTERFACE xios(get_attr)
  MODULE PROCEDURE xios(get_domaingroup_attr_hdl), xios(get_domain_attr_hdl), xios(get_fieldgroup_attr_hdl), &
                   xios(get_field_attr_hdl), xios(get_variable_attr_hdl), xios(get_variablegroup_attr_hdl),  &
                   xios(get_file_attr_hdl), xios(get_filegroup_attr_hdl),                                    &
                   xios(get_grid_attr_hdl), xios(get_gridgroup_attr_hdl), xios(get_axis_attr_hdl) ,          &
                   xios(get_axisgroup_attr_hdl), xios(get_context_attr_hdl), xios(get_zoom_axis_attr_hdl),   &
                   xios(get_zoom_domain_attr_hdl), xios(get_interpolate_axis_attr_hdl),                      &
                   xios(get_interpolate_domain_attr_hdl), xios(get_inverse_axis_attr_hdl),                   &
                   xios(get_generate_rectilinear_domain_attr_hdl), xios(get_scalar_attr_hdl),                &
                   xios(get_scalargroup_attr_hdl), xios(get_reduce_axis_to_scalar_attr_hdl),                 &
                   xios(get_compute_connectivity_domain_attr_hdl), xios(get_reduce_domain_to_scalar_attr_hdl), &
                   xios(get_reduce_domain_to_axis_attr_hdl), xios(get_extract_domain_to_axis_attr_hdl),        &
                   xios(get_extract_axis_to_scalar_attr_hdl), xios(get_expand_domain_attr_hdl)
END INTERFACE xios(get_attr)

INTERFACE xios(is_defined_attr)
  MODULE PROCEDURE xios(is_defined_domaingroup_attr_hdl), xios(is_defined_domain_attr_hdl), xios(is_defined_fieldgroup_attr_hdl), &
                   xios(is_defined_field_attr_hdl), xios(is_defined_variable_attr_hdl), xios(is_defined_variablegroup_attr_hdl),  &
                   xios(is_defined_file_attr_hdl), xios(is_defined_filegroup_attr_hdl),                                           &
                   xios(is_defined_grid_attr_hdl), xios(is_defined_gridgroup_attr_hdl), xios(is_defined_axis_attr_hdl) ,          &
                   xios(is_defined_axisgroup_attr_hdl), xios(is_defined_context_attr_hdl),                                        &
                   xios(is_defined_zoom_axis_attr_hdl), xios(is_defined_zoom_domain_attr_hdl),                                    &
                   xios(is_defined_interpolate_axis_attr_hdl), xios(is_defined_interpolate_domain_attr_hdl),                      &
                   xios(is_defined_inverse_axis_attr_hdl), xios(is_defined_generate_rectilinear_domain_attr_hdl),                 &
                   xios(is_defined_scalar_attr_hdl), xios(is_defined_scalargroup_attr_hdl),                                       &
                   xios(is_defined_reduce_axis_to_scalar_attr_hdl), xios(is_defined_compute_connectivity_domain_attr_hdl),        &
                   xios(is_defined_reduce_domain_to_scalar_attr_hdl), xios(is_defined_reduce_domain_to_axis_attr_hdl),            &
                   xios(is_defined_extract_domain_to_axis_attr_hdl), xios(is_defined_extract_axis_to_scalar_attr_hdl),            &
                   xios(is_defined_expand_domain_attr_hdl)
END INTERFACE xios(is_defined_attr)

INTERFACE xios(get_handle)
  MODULE PROCEDURE xios(get_context_handle), xios(get_domain_handle), xios(get_domaingroup_handle),                  &
                   xios(get_file_handle), xios(get_filegroup_handle), xios(get_grid_handle),                         &
                   xios(get_gridgroup_handle), xios(get_axis_handle), xios(get_axisgroup_handle),                    &
                   xios(get_field_handle), xios(get_fieldgroup_handle),xios(get_variable_handle),                    &
                   xios(get_variablegroup_handle), xios(get_zoom_axis_handle),                                       &
                   xios(get_zoom_domain_handle), xios(get_interpolate_axis_handle),                                  &
                   xios(get_interpolate_domain_handle), xios(get_inverse_axis_handle),                               &
                   xios(get_generate_rectilinear_domain_handle), xios(get_scalar_handle),                            &
                   xios(get_scalargroup_handle), xios(get_reduce_axis_to_scalar_handle),                             &
                   xios(get_compute_connectivity_domain_handle), xios(get_reduce_domain_to_scalar_handle),           &
                   xios(get_reduce_domain_to_axis_handle), xios(get_extract_domain_to_axis_handle),                  &
                   xios(get_extract_axis_to_scalar_handle), xios(get_expand_domain_handle)
END INTERFACE xios(get_handle)

INTERFACE xios(add_child)
  MODULE PROCEDURE xios(add_axis), xios(add_file), xios(add_grid), xios(add_field), xios(add_domain),                &
                   xios(add_fieldtofile), xios(add_variabletofile), xios(add_variabletofield), xios(add_axisgroup),  &
                   xios(add_filegroup), xios(add_gridgroup), xios(add_fieldgroup), xios(add_domaingroup),            &
                   xios(add_fieldgrouptofile), xios(add_variablegrouptofile),xios(add_variablegrouptofield),         &
                   xios(add_axistogrid), xios(add_domaintogrid), xios(add_zoomdomaintodomain),                       &
                   xios(add_interpolatedomaintodomain), xios(add_generatedomaintodomain),                            &
                   xios(add_zoomaxistoaxis), xios(add_interpolateaxistoaxis), xios(add_inverseaxistoaxis),           &
                   xios(add_scalar), xios(add_scalartogrid), xios(add_reduceaxistoscalartoscalar),                   &
                   xios(add_computeconnectivitydomaintodomain), xios(add_reducedomaintoscalartoscalar),              &
                   xios(add_reducedomaintoaxistoaxis), xios(add_extractdomaintoaxistoaxis),                          &
                   xios(add_extractaxistoscalartoscalar), xios(add_expanddomaintodomain)
END INTERFACE xios(add_child)

INTERFACE xios(send_field)
  MODULE PROCEDURE xios(send_field_r8_0d), xios(send_field_r8_1d), xios(send_field_r8_2d), xios(send_field_r8_3d), &
                   xios(send_field_r8_4d), xios(send_field_r8_5d), xios(send_field_r8_6d), xios(send_field_r8_7d), &
                   xios(send_field_r4_0d), xios(send_field_r4_1d), xios(send_field_r4_2d), xios(send_field_r4_3d), &
                   xios(send_field_r4_4d), xios(send_field_r4_5d), xios(send_field_r4_6d), xios(send_field_r4_7d), &
                   xios(send_field_r8_0d_hdl), xios(send_field_r8_1d_hdl), xios(send_field_r8_2d_hdl), xios(send_field_r8_3d_hdl), &
                   xios(send_field_r8_4d_hdl), xios(send_field_r8_5d_hdl), xios(send_field_r8_6d_hdl), xios(send_field_r8_7d_hdl), &
                   xios(send_field_r4_0d_hdl), xios(send_field_r4_1d_hdl), xios(send_field_r4_2d_hdl), xios(send_field_r4_3d_hdl), &
                   xios(send_field_r4_4d_hdl), xios(send_field_r4_5d_hdl), xios(send_field_r4_6d_hdl), xios(send_field_r4_7d_hdl), &
                   xios(send_field_tiled_r8_1d), xios(send_field_tiled_r8_2d), &
                   xios(send_field_tiled_r8_3d), xios(send_field_tiled_r8_4d), &
                   xios(send_field_tiled_r8_5d), xios(send_field_tiled_r8_6d), xios(send_field_tiled_r8_7d), &
                   xios(send_field_tiled_r4_1d), xios(send_field_tiled_r4_2d), &
                   xios(send_field_tiled_r4_3d), xios(send_field_tiled_r4_4d), &
                   xios(send_field_tiled_r4_5d), xios(send_field_tiled_r4_6d), xios(send_field_tiled_r4_7d)
END INTERFACE xios(send_field)

INTERFACE xios(recv_field)
  MODULE PROCEDURE xios(recv_field_r8_0d), xios(recv_field_r8_1d), xios(recv_field_r8_2d), xios(recv_field_r8_3d), &
                   xios(recv_field_r8_4d), xios(recv_field_r8_5d), xios(recv_field_r8_6d), xios(recv_field_r8_7d), &
                   xios(recv_field_r4_0d), xios(recv_field_r4_1d), xios(recv_field_r4_2d), xios(recv_field_r4_3d), &
                   xios(recv_field_r4_4d), xios(recv_field_r4_5d), xios(recv_field_r4_6d), xios(recv_field_r4_7d), &
                   xios(recv_field_r8_0d_hdl), xios(recv_field_r8_1d_hdl), xios(recv_field_r8_2d_hdl), xios(recv_field_r8_3d_hdl), &
                   xios(recv_field_r8_4d_hdl), xios(recv_field_r8_5d_hdl), xios(recv_field_r8_6d_hdl), xios(recv_field_r8_7d_hdl), &
                   xios(recv_field_r4_0d_hdl), xios(recv_field_r4_1d_hdl), xios(recv_field_r4_2d_hdl), xios(recv_field_r4_3d_hdl), &
                   xios(recv_field_r4_4d_hdl), xios(recv_field_r4_5d_hdl), xios(recv_field_r4_6d_hdl), xios(recv_field_r4_7d_hdl)
END INTERFACE xios(recv_field)

INTERFACE xios(field_is_active)
  MODULE PROCEDURE xios(field_is_active_id),xios(field_is_active_hdl)
END INTERFACE xios(field_is_active)

INTERFACE xios(field_get_domain)
  MODULE PROCEDURE xios(field_get_domain_handle), xios(field_id_get_domain_handle)
END INTERFACE xios(field_get_domain)

INTERFACE xios(field_get_axis)
  MODULE PROCEDURE xios(field_get_axis_handle),xios(field_id_get_axis_handle)
END INTERFACE xios(field_get_axis)

INTERFACE xios(field_get_scalar)
  MODULE PROCEDURE xios(field_get_scalar_handle),xios(field_id_get_scalar_handle)
END INTERFACE xios(field_get_scalar)

INTERFACE xios(getVar)
  MODULE PROCEDURE xios(getVar_k8), xios(getVar_k4), xios(getVar_int), xios(getVar_logic), xios(getVar_char)
END INTERFACE xios(getVar)

INTERFACE xios(setVar)
  MODULE PROCEDURE xios(setVar_k8), xios(setVar_k4), xios(setVar_int), xios(setVar_logic), xios(setVar_char)
END INTERFACE xios(setVar)

PUBLIC :: xios(set_attr), xios(get_attr), xios(is_defined_attr), xios(get_handle), xios(add_child), &
          xios(send_field), xios(recv_field), xios(field_is_active), xios(getVar), xios(setVar), &
          xios(field_get_domain),xios(field_get_axis),xios(field_get_scalar)

END MODULE XIOS_INTERFACES
