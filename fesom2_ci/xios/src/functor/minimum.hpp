#ifndef __XIOS_CMinimum__
#define __XIOS_CMinimum__

/// XIOS headers ///
#include "functor.hpp"
#include "array_new.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class CMinimum : public CFunctor
      {
         /// Définition de type ///
         typedef CFunctor SuperClass;

         public :

            /// Constructeurs ///
            //CMinimum(void);                             // Not implemented.
            //CMinimum(const CFunData & data);
            CMinimum(CArray<double,1>& doutput);
            CMinimum(CArray<double,1>& doutput, double missingValue);
            //CMinimum(const CMinimum & Minimum);         // Not implemented.
            //CMinimum(const CMinimum * const Minimum);   // Not implemented.

            /// Traitement ///
            virtual void apply(const CArray<double,1>& dinput, CArray<double,1>& doutput);
            virtual ETimeType timeType(void) { return centered ; }

            /// Destructeur ///
            virtual ~CMinimum(void);

      }; // class CMinimum

   } // namespace func
} // namespace xios

#endif //__XIOS_CMinimum__
