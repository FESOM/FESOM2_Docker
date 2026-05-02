#include "average.hpp"
#include "array_new.hpp"
#include "utils.hpp"

namespace xios
{
   namespace func
   {
      /// ////////////////////// Définitions ////////////////////// ///

      CAverage::CAverage(CArray<double,1>& doutput)
         : SuperClass(StdString("average"), doutput)
      { /* Ne rien faire de plus */ }

      CAverage::CAverage(CArray<double,1>& doutput, double missingValue)
         : SuperClass(StdString("average"), doutput, missingValue)
      { /* Ne rien faire de plus */ }

      CAverage::~CAverage(void)
      { /* Ne rien faire de plus */ }

      //---------------------------------------------------------------

      void CAverage::apply(const CArray<double,1>& _dinput,
                                 CArray<double,1>& _doutput)
      {
        if (hasMissingValue)
        {
          if (nbcalls.numElements()==0) 
          {
             nbcalls.resize(_dinput.numElements()) ;
             nbcalls=0 ;
          }
        }
        
        if (this->nbcall == 1) 
        {
          _doutput=_dinput ;
          if (hasMissingValue) 
          {
            int i, n =_dinput.numElements() ;
            const double * in=_dinput.dataFirst() ;
            int* nc=nbcalls.dataFirst() ;
            for (i=0; i<n; ++i,++nc,++in) 
              if (!NumTraits<double>::isNan(*in)) (*nc) ++;
          }
        }
        else
        {
          if (hasMissingValue)
          {
            int i, n =_dinput.numElements() ;
            const double * in=_dinput.dataFirst() ;
            double* out=_doutput.dataFirst();
            int* nc=nbcalls.dataFirst() ;
            for (i=0; i<n; ++i,++in,++out,++nc) 
              if (!NumTraits<double>::isNan(*in)) 
              {
                if (*nc != 0) (*out)  += *in;
                else *out = *in ;
                (*nc) ++;
              } 
          }
          else _doutput+=_dinput ;
        }
      
      }
      
      void CAverage::final(void)
      {
        if (hasMissingValue)
        {
          int i, n = nbcalls.numElements() ;
          double* out= doutput.dataFirst();
          int* nc=nbcalls.dataFirst() ;
          for (i=0; i<n; ++i, ++out,++nc) 
            if (*nc!=0) 
            {
              *out  /= *nc;
              *nc = 0 ;
            }
        
        }  
        else doutput/=this->nbcall; 
        this->nbcall = 0; 

      }
   } // namespace func
} // namespace xios
