#ifndef __XIOS_CAverage__
#define __XIOS_CAverage__

/// XIOS headers ///
#include "functor.hpp"
#include "array_new.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Déclarations ////////////////////// ///
      class CAverage : public CFunctor
      {
         /// Définition de type ///
         typedef CFunctor SuperClass;

         public :

            /// Constructeurs ///
            //CAverage(void);                             // Not implemented.
            //CAverage(const CFunData & data);
            CAverage(CArray<double,1>& doutput);
            CAverage(CArray<double,1>& doutput, double missingValue);
            //CAverage(const CAverage & average);         // Not implemented.
            //CAverage(const CAverage * const average);   // Not implemented.

            /// Traitement ///
            virtual void apply(const CArray<double,1>& dinput, CArray<double,1>& doutput);
            virtual void final(void) ;
            virtual ETimeType timeType(void) { return centered ; }

            /// Destructeur ///
            virtual ~CAverage(void);

      }; // class CAverage

   } // namespace func
} // namespace xios

#endif //__XIOS_CAverage__
