#ifndef __XIOS_COnce__
#define __XIOS_COnce__

/// XIOS headers ///
#include "functor.hpp"
#include "array_new.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class COnce : public CFunctor
      {
         /// Définition de type ///
         typedef CFunctor SuperClass;

         public :

            /// Constructeurs ///
            //COnce(void);                       // Not implemented.
            COnce(CArray<double,1>& doutput);
            COnce(CArray<double,1>& doutput, double missingValue);
            //COnce(const COnce & once);         // Not implemented.
            //COnce(const COnce * const once);   // Not implemented.

            /// Traitement ///
            virtual void apply(const CArray<double,1>& dinput, CArray<double,1>& doutput);
            virtual ETimeType timeType(void) { return once ; }

            /// Destructeur ///
            virtual ~COnce(void);

      }; // class COnce

   } // namespace func
} // namespace xios

#endif //__XIOS_COnce__

