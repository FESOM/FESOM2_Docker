#ifndef __XIOS_CAccumulate__
#define __XIOS_CAccumulate__

/// XIOS headers ///
#include "functor.hpp"
#include "array_new.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class CAccumulate : public CFunctor
      {
         /// Définition de type ///
         typedef CFunctor SuperClass;

         public :

            /// Constructeurs ///
            //CAccumulate(void);                             // Not implemented.
            //CAccumulate(const CFunData & data);
            CAccumulate(CArray<double,1>& doutput);
            CAccumulate(CArray<double,1>& doutput, double missingValue);
            //CAccumulate(const CAccumulate & accumulate);         // Not implemented.
            //CAccumulate(const CAccumulate * const accumulate);   // Not implemented.

            /// Traitement ///
            virtual void apply(const CArray<double,1>& dinput, CArray<double,1>& doutput);
            virtual void final(void) ;
            virtual ETimeType timeType(void) { return centered ; }
            
            /// Destructeur ///
            virtual ~CAccumulate(void);

      }; // class CAccumulate

   } // namespace func
} // namespace xios

#endif //__XIOS_CAccumulate__
