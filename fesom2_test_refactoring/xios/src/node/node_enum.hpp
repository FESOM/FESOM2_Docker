#ifndef __XIOS_NODE_ENUM__
#define __XIOS_NODE_ENUM__

//#define DECLARE_NODE(Name_, name_)     ,e##Name_, g##Name_
//#define DECLARE_NODE_PAR(Name_, name_) ,e##Name_, g##Name_

namespace xios
{
      /// ////////////////////// Définitions ////////////////////// ///
      typedef enum _node_type
      {
         Unknown = 0,
         eAxis,gAxis,
         eDomain,gDomain,
         eField,gField,
         eFile,gFile,
         eGrid,gGrid,
         eVariable,gVariable,
         eContext,gContext,
         eCalendarWrapper,
         eTransformation,
         eInverseAxis,
         eZoomAxis,
         eInterpolateAxis,
         eExtractAxis,
         eZoomDomain,
         eInterpolateDomain,
         eGenerateRectilinearDomain,
         eScalar,
         eReduceAxisToScalar,
         eReduceDomainToAxis,
         eReduceAxisToAxis,
         eExtractDomainToAxis,
         eComputeConnectivityDomain,
         eExpandDomain,
         eExtractAxisToScalar,
         eReduceDomainToScalar,
         eTemporalSplitting,
         eDuplicateScalarToAxis,
         eReduceScalarToScalar,
         eReorderDomain,
         eExtractDomain
       } ENodeType;

} // namespace xios

#endif // __XIOS_NODE_ENUM__
