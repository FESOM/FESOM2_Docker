#include "accumulate.hpp"
#include "array_new.hpp"
#include "utils.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Définitions ////////////////////// ///

      CAccumulate::CAccumulate(CArray<double,1>& doutput)
         : SuperClass(StdString("accumulate"), doutput)
      { /* Ne rien faire de plus */ }

      CAccumulate::CAccumulate(CArray<double,1>& doutput, double missingValue)
         : SuperClass(StdString("accumulate"), doutput, missingValue)
      { /* Ne rien faire de plus */ }

      CAccumulate::~CAccumulate(void)
      { /* Ne rien faire de plus */ }

      //---------------------------------------------------------------

      void CAccumulate::apply(const CArray<double,1>& _dinput,
                                 CArray<double,1>& _doutput)
      {
        if (this->nbcall == 1) _doutput=_dinput ;
        else 
        {
          if (hasMissingValue)
          {
            int i, n =_dinput.numElements() ;
            const double * in=_dinput.dataFirst() ;
            double* out=_doutput.dataFirst();
            for (i=0; i<n; ++i,++in,++out) 
              if (!NumTraits<double>::isNan(*in))
              {
                if(!NumTraits<double>::isNan(*out)) *out  += *in;
                else *out=*in ;
              }
          }
          else _doutput+=_dinput ;
        }
      }
      
      
      void CAccumulate::final(void)
      {
        this->nbcall = 0; 
      }
   } // namespace func
} // namespace xios
