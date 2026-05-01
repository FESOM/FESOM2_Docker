#ifndef __XIOS_CMaximum__
#define __XIOS_CMaximum__

/// XIOS headers ///
#include "functor.hpp"
#include "array_new.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class CMaximum : public CFunctor
      {
         /// Définition de type ///
         typedef CFunctor SuperClass;

         public :

            /// Constructeurs ///
            //CMaximum(void);                             // Not implemented.
            //CMaximum(const CFunData & data);
            CMaximum(CArray<double,1>& doutput);
            CMaximum(CArray<double,1>& doutput, double missingValue);
            //CMaximum(const CMaximum & Maximum);         // Not implemented.
            //CMaximum(const CMaximum * const Maximum);   // Not implemented.

            /// Traitement ///
            virtual void apply(const CArray<double,1>& dinput, CArray<double,1>& doutput);
            virtual ETimeType timeType(void) { return centered ; }

            /// Destructeur ///
            virtual ~CMaximum(void);

      }; // class CMaximum

   } // namespace func
} // namespace xios

#endif //__XIOS_CMaximum__
