#ifndef __XIOS_OPERATOR_EXPR_HPP__
#define __XIOS_OPERATOR_EXPR_HPP__

#include <map>
#include <string>
#include <cmath>
#include "exception.hpp"
#include "array_new.hpp"
#include "utils.hpp"

using namespace std;

namespace xios
{
  class COperatorExpr
  {
    public:
    typedef double (*functionScalar)(double);
    typedef double (*functionScalarScalar)(double, double);
    typedef double (*functionScalarScalarScalar)(double, double,double);
    typedef CArray<double,1> (*functionField)(const CArray<double,1>&);
    typedef CArray<double,1> (*functionFieldField)(const CArray<double,1>&, const CArray<double,1>&);
    typedef CArray<double,1> (*functionFieldScalar)(const CArray<double,1>&, double);
    typedef CArray<double,1> (*functionScalarField)(double, const CArray<double,1>&);
    typedef CArray<double,1> (*functionScalarScalarField)(double, double, const CArray<double,1>&);
    typedef CArray<double,1> (*functionScalarFieldScalar)(double, const CArray<double,1>&, double);
    typedef CArray<double,1> (*functionScalarFieldField)(double, const CArray<double,1>&, const CArray<double,1>&);
    typedef CArray<double,1> (*functionFieldScalarScalar)(const CArray<double,1>&, double, double);
    typedef CArray<double,1> (*functionFieldScalarField)(const CArray<double,1>&, double, const CArray<double,1>&);
    typedef CArray<double,1> (*functionFieldFieldScalar)(const CArray<double,1>&,  const CArray<double,1>&, double);
    typedef CArray<double,1> (*functionFieldFieldField)(const CArray<double,1>&,  const CArray<double,1>&, const CArray<double,1>&);
    
    COperatorExpr(void)
    {
      opScalar[string("neg")] = neg_s;
      opScalar[string("cos")] = cos_s;
      opScalar[string("sin")] = sin_s;
      opScalar[string("tan")] = tan_s;
      opScalar[string("exp")] = exp_s;
      opScalar[string("log")] = log_s;
      opScalar[string("log10")] = log10_s;
      opScalar[string("sqrt")] = sqrt_s;

      opScalarScalar[string("add")] = add_ss;
      opScalarScalar[string("minus")] = minus_ss;
      opScalarScalar[string("mult")] = mult_ss;
      opScalarScalar[string("div")] = div_ss;
      opScalarScalar[string("pow")] = pow_ss;
      opScalarScalar[string("eq")] = eq_ss;
      opScalarScalar[string("lt")] = lt_ss;
      opScalarScalar[string("gt")] = gt_ss;
      opScalarScalar[string("le")] = le_ss;
      opScalarScalar[string("ge")] = ge_ss;
      opScalarScalar[string("ne")] = ne_ss;
      opScalarScalarScalar[string("cond")] = cond_sss;
      
      opField[string("neg")] = neg_f;
      opField[string("cos")] = cos_f;
      opField[string("sin")] = sin_f;
      opField[string("tan")] = tan_f;
      opField[string("exp")] = exp_f;
      opField[string("log")] = log_f;
      opField[string("log10")] = log10_f;
      opField[string("sqrt")] = sqrt_f;

      opFieldField[string("add")] = add_ff;
      opFieldField[string("minus")] = minus_ff;
      opFieldField[string("mult")] = mult_ff;
      opFieldField[string("div")] = div_ff;
      opFieldField[string("pow")] = pow_ff;
      opFieldField[string("eq")] = eq_ff;
      opFieldField[string("lt")] = lt_ff;
      opFieldField[string("gt")] = gt_ff;
      opFieldField[string("le")] = le_ff;
      opFieldField[string("ge")] = ge_ff;
      opFieldField[string("ne")] = ne_ff;

      opFieldScalar[string("add")] = add_fs;
      opFieldScalar[string("minus")] = minus_fs;
      opFieldScalar[string("mult")] = mult_fs;
      opFieldScalar[string("div")] = div_fs;
      opFieldScalar[string("pow")] = pow_fs;
      opFieldScalar[string("eq")] = eq_fs;
      opFieldScalar[string("lt")] = lt_fs;
      opFieldScalar[string("gt")] = gt_fs;
      opFieldScalar[string("le")] = le_fs;
      opFieldScalar[string("ge")] = ge_fs;
      opFieldScalar[string("ne")] = ne_fs;

      opScalarField[string("add")] = add_sf;
      opScalarField[string("minus")] = minus_sf;
      opScalarField[string("mult")] = mult_sf;
      opScalarField[string("div")] = div_sf;
      opScalarField[string("eq")] = eq_sf;
      opScalarField[string("lt")] = lt_sf;
      opScalarField[string("gt")] = gt_sf;
      opScalarField[string("le")] = le_sf;
      opScalarField[string("ge")] = ge_sf;
      opScalarField[string("ne")] = ne_sf;

      opScalarScalarField[string("cond")] = cond_ssf;
      opScalarFieldScalar[string("cond")] = cond_sfs;
      opScalarFieldField[string("cond")] = cond_sff;
      opFieldScalarScalar[string("cond")] = cond_fss;
      opFieldScalarField[string("cond")] = cond_fsf;
      opFieldFieldScalar[string("cond")] = cond_ffs;
      opFieldFieldField[string("cond")] = cond_fff;


    }

    functionScalar getOpScalar(const string& id)
    {
      map<string,double (*)(double)>::iterator it;
      it = opScalar.find(id);
      if (it == opScalar.end()) ERROR("functionScalar COperatorExpr::getOpScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarScalar getOpScalarScalar(const string& id)
    {
      map<string,double (*)(double,double)>::iterator it;
      it = opScalarScalar.find(id);
      if (it == opScalarScalar.end()) ERROR("functionScalarScalar COperatorExpr::getOpScalarScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarScalarScalar getOpScalarScalarScalar(const string& id)
    {
      map<string,double (*)(double,double,double)>::iterator it;
      it = opScalarScalarScalar.find(id);
      if (it == opScalarScalarScalar.end()) ERROR("functionScalarScalarScalar getOpScalarScalarScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionField getOpField(const string& id)
    {
      map<string,functionField>::iterator it;
      it = opField.find(id);
      if (it == opField.end()) ERROR("functionField COperatorExpr::getOpField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldField getOpFieldField(const string& id)
    {
      map<string,functionFieldField>::iterator it;
      it = opFieldField.find(id);
      if (it == opFieldField.end()) ERROR("dfunctionFieldField COperatorExpr::getOpFieldField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldScalar getOpFieldScalar(const string& id)
    {
      map<string,functionFieldScalar>::iterator it;
      it = opFieldScalar.find(id);
      if (it == opFieldScalar.end()) ERROR("functionFieldScalar COperatorExpr::getOpFieldScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarField getOpScalarField(const string& id)
    {
      map<string,functionScalarField>::iterator it;
      it = opScalarField.find(id);
      if (it == opScalarField.end()) ERROR("functionScalarField COperatorExpr::getOpFieldField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarScalarField getOpScalarScalarField(const string& id)
    {
      map<string,functionScalarScalarField>::iterator it;
      it = opScalarScalarField.find(id);
      if (it == opScalarScalarField.end()) ERROR("functionScalarScalarField getOpScalarScalarField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarFieldScalar getOpScalarFieldScalar(const string& id)
    {
      map<string,functionScalarFieldScalar>::iterator it;
      it = opScalarFieldScalar.find(id);
      if (it == opScalarFieldScalar.end()) ERROR("functionScalarFieldScalar getOpScalarScalarField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionScalarFieldField getOpScalarFieldField(const string& id)
    {
      map<string,functionScalarFieldField>::iterator it;
      it = opScalarFieldField.find(id);
      if (it == opScalarFieldField.end()) ERROR("functionScalarFieldField getOpScalarFieldField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldScalarScalar getOpFieldScalarScalar(const string& id)
    {
      map<string,functionFieldScalarScalar>::iterator it;
      it = opFieldScalarScalar.find(id);
      if (it == opFieldScalarScalar.end()) ERROR("functionFieldScalarScalar getOpFieldScalarScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldScalarField getOpFieldScalarField(const string& id)
    {
      map<string,functionFieldScalarField>::iterator it;
      it = opFieldScalarField.find(id);
      if (it == opFieldScalarField.end()) ERROR("functionFieldScalarField getOpFieldScalarField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldFieldScalar getOpFieldFieldScalar(const string& id)
    {
      map<string,functionFieldFieldScalar>::iterator it;
      it = opFieldFieldScalar.find(id);
      if (it == opFieldFieldScalar.end()) ERROR("functionFieldFieldScalar getOpFieldFieldScalar(const string& id)", << "unknown operator : " << id)
      return it->second;
    }

    functionFieldFieldField getOpFieldFieldField(const string& id)
    {
      map<string,functionFieldFieldField>::iterator it;
      it = opFieldFieldField.find(id);
      if (it == opFieldFieldField.end()) ERROR("functionFieldFieldField getOpFieldFieldField(const string& id)", << "unknown operator : " << id)
      return it->second;
    }
    
    
    map<string,functionScalar> opScalar;
    map<string,functionScalarScalar> opScalarScalar;
    map<string,functionScalarScalarScalar> opScalarScalarScalar;
    map<string,functionField> opField;
    map<string,functionFieldField> opFieldField;
    map<string,functionFieldScalar> opFieldScalar;
    map<string,functionScalarField> opScalarField;
    map<string,functionScalarScalarField> opScalarScalarField;
    map<string,functionScalarFieldScalar> opScalarFieldScalar;
    map<string,functionScalarFieldField> opScalarFieldField;
    map<string,functionFieldScalarScalar> opFieldScalarScalar;
    map<string,functionFieldScalarField> opFieldScalarField;
    map<string,functionFieldFieldScalar> opFieldFieldScalar;
    map<string,functionFieldFieldField> opFieldFieldField;



    static inline double neg_s(double x)   { return -x; }
    static inline double cos_s(double x)   { return std::cos(x); }
    static inline double sin_s(double x)   { return std::sin(x); }
    static inline double tan_s(double x)   { return std::tan(x); }
    static inline double exp_s(double x)   { return std::exp(x); }
    static inline double log_s(double x)   { return std::log(x); }
    static inline double log10_s(double x) { return std::log10(x); }
    static inline double sqrt_s(double x)  { return std::sqrt(x); }

    static inline double add_ss(double x, double y)   { return x + y; }
    static inline double minus_ss(double x, double y) { return x - y; }
    static inline double mult_ss(double x, double y)  { return x * y; }
    static inline double div_ss(double x, double y)   { return x / y; }
    static inline double pow_ss(double x, double y)   { return std::pow(x,y); }

    static inline double eq_ss(double x, double y) // specific check for NaN
    {
       bool xNan=NumTraits<double>::isNan(x) ;
       bool yNan=NumTraits<double>::isNan(y) ;
       if (xNan && yNan) return true ;
       else if (xNan) return false ;
       else if (yNan) return false ;
       else return x == y;
    }
    
    static inline double lt_ss(double x, double y)    { return x < y; }
    static inline double gt_ss(double x, double y)    { return x > y; }
    static inline double le_ss(double x, double y)    { return x <= y; }
    static inline double ge_ss(double x, double y)    { return x >= y; }

    static inline double ne_ss(double x, double y) // specific check for NaN
    {
       bool xNan=NumTraits<double>::isNan(x) ;
       bool yNan=NumTraits<double>::isNan(y) ;
       if (xNan && yNan) return false ;
       else if (xNan) return true ;
       else if (yNan) return true ;      
       else return x != y;
    }
    
    static inline CArray<double,1> neg_f(const CArray<double,1>& x)   { return Array<double,1>(-x); }
    static inline CArray<double,1> cos_f(const CArray<double,1>& x)   { return Array<double,1>(cos(x)); }
    static inline CArray<double,1> sin_f(const CArray<double,1>& x)   { return Array<double,1>(sin(x)); }
    static inline CArray<double,1> tan_f(const CArray<double,1>& x)   { return Array<double,1>(tan(x)); }
    static inline CArray<double,1> exp_f(const CArray<double,1>& x)   { return Array<double,1>(exp(x)); }
    static inline CArray<double,1> log_f(const CArray<double,1>& x)   { return Array<double,1>(log(x)); }
    static inline CArray<double,1> log10_f(const CArray<double,1>& x) { return Array<double,1>(log10(x)); }
    static inline CArray<double,1> sqrt_f(const CArray<double,1>& x)  { return Array<double,1>(sqrt(x)); }

    static inline CArray<double,1> add_ff(const CArray<double,1>& x, const CArray<double,1>& y)   { return Array<double,1>(x + y); }
    static inline CArray<double,1> minus_ff(const CArray<double,1>& x, const CArray<double,1>& y) { return Array<double,1>(x - y); }
    static inline CArray<double,1> mult_ff(const CArray<double,1>& x, const CArray<double,1>& y)  { return Array<double,1>(x * y); }
    static inline CArray<double,1> div_ff(const CArray<double,1>& x, const CArray<double,1>& y)   { return Array<double,1>(x / y); }
    static inline CArray<double,1> pow_ff(const CArray<double,1>& x, const CArray<double,1>& y)   { return Array<double,1>(pow(x,y)); }
    static inline CArray<double,1> eq_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x == y); }
    static inline CArray<double,1> lt_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x < y); }
    static inline CArray<double,1> gt_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x > y); }
    static inline CArray<double,1> le_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x <= y); }
    static inline CArray<double,1> ge_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x >= y); }
    static inline CArray<double,1> ne_ff(const CArray<double,1>& x, const CArray<double,1>& y)    { return Array<double,1>(x != y); }

    static inline CArray<double,1> add_fs(const CArray<double,1>& x, double y)   { return Array<double,1>(x + y); }
    static inline CArray<double,1> minus_fs(const CArray<double,1>& x, double y) { return Array<double,1>(x - y); }
    static inline CArray<double,1> mult_fs(const CArray<double,1>& x, double y)  { return Array<double,1>(x * y); }
    static inline CArray<double,1> div_fs(const CArray<double,1>& x, double y)   { return Array<double,1>(x / y); }
    static inline CArray<double,1> pow_fs(const CArray<double,1>& x, double y)   { return Array<double,1>(pow(x,y)); }

    static inline CArray<double,1> eq_fs(const CArray<double,1>& x, double y) // specific check for NaN
    {
      if (NumTraits<double>::isNan(y))
      {
        CArray<double,1> ret(x.numElements()) ;
        Array<double,1>::const_iterator itx=x.begin(),itxe=x.end();
        Array<double,1>::iterator itret=ret.begin() ;
        for(;itx!=itxe;++itx,++itret) *itret=NumTraits<double>::isNan(*itx) ;
        return ret ;
      }
      else return Array<double,1>(x == y); 
    }
    
    static inline CArray<double,1> lt_fs(const CArray<double,1>& x, double y)    { return Array<double,1>(x < y); }
    static inline CArray<double,1> gt_fs(const CArray<double,1>& x, double y)    { return Array<double,1>(x > y); }
    static inline CArray<double,1> le_fs(const CArray<double,1>& x, double y)    { return Array<double,1>(x <= y); }
    static inline CArray<double,1> ge_fs(const CArray<double,1>& x, double y)    { return Array<double,1>(x >= y); }

    static  inline CArray<double,1> ne_fs(const CArray<double,1>& x, double y) // specific check for NaN
    {
      if (NumTraits<double>::isNan(y))
      {
        CArray<double,1> ret(x.numElements()) ;
        Array<double,1>::const_iterator itx=x.begin(),itxe=x.end();
        Array<double,1>::iterator itret=ret.begin() ;
        for(;itx!=itxe;++itx,++itret) *itret = !NumTraits<double>::isNan(*itx) ;
        return ret ;
      }
      else return Array<double,1>(x != y); 
    }

    static inline CArray<double,1> add_sf(double x, const CArray<double,1>& y)   { return Array<double,1>(x + y); }
    static inline CArray<double,1> minus_sf(double x, const CArray<double,1>& y) { return Array<double,1>(x - y); }
    static inline CArray<double,1> mult_sf(double x, const CArray<double,1>& y)  { return Array<double,1>(x * y); }
    static inline CArray<double,1> div_sf(double x, const CArray<double,1>& y)   { return Array<double,1>(x / y); }

    static inline CArray<double,1> eq_sf(double x, const CArray<double,1>& y) // specific check for NaN
    {
      if (NumTraits<double>::isNan(x))
      {
        CArray<double,1> ret(y.numElements()) ;
        Array<double,1>::const_iterator ity=y.begin(),itye=y.end();
        Array<double,1>::iterator itret=ret.begin() ;
        for(;ity!=itye;++ity,++itret) *itret=NumTraits<double>::isNan(*ity) ;
        return ret ;
      }
      else return Array<double,1>(x == y); 
    }
    static inline CArray<double,1> lt_sf(double x, const CArray<double,1>& y)    { return Array<double,1>(x < y); }
    static inline CArray<double,1> gt_sf(double x, const CArray<double,1>& y)    { return Array<double,1>(x > y); }
    static inline CArray<double,1> le_sf(double x, const CArray<double,1>& y)    { return Array<double,1>(x <= y); }
    static inline CArray<double,1> ge_sf(double x, const CArray<double,1>& y)    { return Array<double,1>(x >= y); }

    static inline CArray<double,1> ne_sf(double x, const CArray<double,1>& y) // specific check for NaN
    {
      if (NumTraits<double>::isNan(x))
      {
        CArray<double,1> ret(y.numElements()) ;
        Array<double,1>::const_iterator ity=y.begin(),itye=y.end();
        Array<double,1>::iterator itret=ret.begin() ;
        for(;ity!=itye;++ity,++itret) *itret=!NumTraits<double>::isNan(*ity) ;
        return ret ;
      }
      else return Array<double,1>(x != y);
    }
    static inline double cond_sss(double x, double y, double z)   { return (x==0) ? z : y ; }

    static inline CArray<double,1> cond_ssf(double x, double y, const CArray<double,1>& z)
    {
      CArray<double,1> ret(z.numElements()) ;
      if (x==0) ret=z ;
      else ret=y ;
      return ret ;
    }

    static inline CArray<double,1> cond_sfs(double x, const CArray<double,1>& y, double z)
    {
      CArray<double,1> ret(y.numElements()) ;
     if (x==0) ret=z ;
      else ret=y ;
      return ret ;
    }

    static inline CArray<double,1> cond_sff(double x, const CArray<double,1>& y, const CArray<double,1>& z)
    {
      CArray<double,1> ret(y.numElements()) ;
      if (x==0) ret=z ;
      else ret=y ;
      return ret ;
    }
    
    static inline CArray<double,1> cond_fss(const CArray<double,1>& x, double y, double z)
    {
      CArray<double,1> ret(x.numElements()) ;
      Array<double,1>::const_iterator itx=x.begin(),itxe=x.end();
      Array<double,1>::iterator itret=ret.begin() ;
      
      for(;itx!=itxe;++itx,++itret) *itret=( (*itx==0)?z:y) ;
      return ret ;
    }

    static inline CArray<double,1> cond_fsf(const CArray<double,1>& x, double y, const CArray<double,1>& z)
    {
      CArray<double,1> ret(x.numElements()) ;
      Array<double,1>::const_iterator itx=x.begin(), itxe=x.end(), itz=z.begin();
      Array<double,1>::iterator itret=ret.begin() ;
      for(;itx!=itxe;++itx,++itz,++itret) *itret=( (*itx==0)?*itz:y) ;
      return ret ;
    }

    static inline CArray<double,1> cond_ffs(const CArray<double,1>& x, const CArray<double,1>& y, double z)
    {
      CArray<double,1> ret(x.numElements()) ;
      Array<double,1>::const_iterator itx=x.begin(), itxe=x.end(), ity=y.begin() ;
      Array<double,1>::iterator itret=ret.begin() ;
      for(;itx!=itxe;++itx,++ity,++itret) *itret=( (*itx==0)?z:*ity) ;
      return ret ;
    }

    static inline CArray<double,1> cond_fff(const CArray<double,1>& x, const CArray<double,1>& y, const CArray<double,1>&  z)
    {
      CArray<double,1> ret(x.numElements()) ;
      Array<double,1>::const_iterator itx=x.begin(), itxe=x.end(), ity=y.begin(), itz=z.begin() ;
      Array<double,1>::iterator itret=ret.begin() ;
      for(;itx!=itxe;++itx,++ity,++itz,++itret) *itret=( (*itx==0)?*itz:*ity) ;
      return ret ;
    }

  };

  extern COperatorExpr operatorExpr;
}

#endif

