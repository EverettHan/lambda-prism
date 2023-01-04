//===================================================================
// COPYRIGHT Dassault Systemes 2013-2016
//===================================================================
//
// Usage notes:
//   Underflow and overflow must be checked by the user (see <cfenv>).
//
//===================================================================
//
// 03/06/2019 : RNO : NOEXCEPT
// 20.10.2016 : NUA/MMO : Correction des erreurs de compilation VS2015 (_MSC_VER = 1900)
// 24.06.2015 : RAQ : migration fabs en ternaire + constructeur rvalue de CATExpDynamic
//  May 2013 - T6L : Creation
//===================================================================
//

#ifndef CATExpDynamic_H
#define CATExpDynamic_H


#include "CATExpNumbersOperators.h"


#include <cmath>
#include <cfloat>
#include <algorithm>
#include <array>
//template <typename NT> NT CATExpMakeVarFromDiff (double a, double b);
//template <typename NT> NT CATExpMakeVar (double a);
//template <typename NT> NT CATExpMakeRepresentableConstant (double a);
//template <typename NT> NT CATExpMakeConstant (double a);

class CATExpDynamic;
CATExpDynamic CATExpDynamicMakeVarFromDiff (double a, double b);
CATExpDynamic CATExpDynamicMakeVar (double x);
CATExpDynamic CATExpDynamicMakeRepresentableConstant (double x);
CATExpDynamic CATExpDynamicMakeConstant (double x);
template <size_t DIM>
CATExpDynamic CATExpDynamicMakeVarFromDotProduct(const std::array<double, DIM>& v1, const std::array<double, DIM> & v2);

CATExpDynamic CATExpDynamicMakeVarFromPlaneEval(const std::array<double, 4>& iPlane, const std::array<double, 3> & iPoint);
CATExpDynamic CATExpDynamicMakeVarFrom2x2Determinant(const std::array<double, 2> &v1, const std::array<double, 2> &v2);
CATExpDynamic CATExpDynamicMakeVarFrom2x2Determinant(double x1, double y1, double x2, double y2);
CATExpDynamic CATExpDynamicMakeVarFrom3x3Determinant(const std::array<double, 3> &v1, const std::array<double, 3> &v2, const std::array<double, 3> &v3);



#ifndef __EXPNOEXCEPT__
#if defined(CATIAR421) ||  defined(CATIAV5R30)
#define __EXPNOEXCEPT__ noexcept
#else
#define __EXPNOEXCEPT__
#endif
#endif

/**
* A Dynamic is a double and a measure of error on it used to determine its sign exactly.
* The error on x is upper-bounded by (d+2) * 2**(-53) * m.
* @see Mehlhorn/Osbild/Sagraloff 2010 and Mehlhorn's course.
* @pre Underflow and overflow must be checked.
*/
class CATExpDynamic
{
  /* =========== Numbers factory functions ================= */

  inline friend CATExpDynamic CATExpDynamicMakeVarFromDiff (double a, double b)
  { double diff = a - b; return CATExpDynamic(diff, diff>=0.0 ? diff : -diff, 1); }

  inline friend CATExpDynamic CATExpDynamicMakeVar (double x)
  { return CATExpDynamic(x, x>=0.0 ? x : -x, 1); }

  inline friend CATExpDynamic CATExpDynamicMakeRepresentableConstant (double x)
  { return CATExpDynamic(x, x>=0.0 ? x : -x, 0); }

  inline friend CATExpDynamic CATExpDynamicMakeConstant (double x)
  { return CATExpDynamic(x, x>=0.0 ? x : -x, 1); }


  template <size_t DIM>
  inline friend CATExpDynamic CATExpDynamicMakeVarFromDotProduct(const std::array<double, DIM>& v1, const std::array<double, DIM> & v2)
  {
    static_assert(DIM >= 1, "CATExpDynamicMakeVarFromDotProduct requires DIM>=1");
    std::array<double, DIM> v1m, v2m;
    for(size_t i = 0; i < DIM; i++)
    {
      v1m[i] = v1[i] >= 0.0 ? v1[i] : -v1[i];
      v2m[i] = v2[i] >= 0.0 ? v2[i] : -v2[i];
    }
    double x = v1[0] * v2[0];
    double m = v1m[0] * v2m[0];
    for(size_t i = 1; i < DIM; i++)
    {
      x += v1[i] * v2[i];
      m += v1m[i] * v2m[i];
    }
    return CATExpDynamic(x, m, DIM + 1);
  }
  inline friend CATExpDynamic CATExpDynamicMakeVarFromDotProduct(const std::array<double, 4>& v1, const std::array<CATExpDynamic, 4> & v2)
  {
    const std::array<double, 4> v1m = { v1[0] >= 0.0 ? v1[0] : -v1[0] , v1[1] >= 0.0 ? v1[1] : -v1[1] , v1[2] >= 0.0 ? v1[2] : -v1[2] , v1[3] >= 0.0 ? v1[3] : -v1[3] };
    
    const double x = ((v1[0] * v2[0].x_) + (v1[1] * v2[1].x_)) + ((v1[2] * v2[2].x_) + (v1[3] * v2[3].x_));
    const double m = ((v1m[0] * v2[0].m_) + (v1m[1] * v2[1].m_)) + ((v1m[2] * v2[2].m_) + (v1m[3] * v2[3].m_));

    const unsigned d = 4 + std::max<unsigned>(std::max<unsigned>(v2[0].d_,  v2[1].d_), std::max<unsigned>(v2[2].d_, v2[3].d_));
    return CATExpDynamic(x, m, d);
  }

  inline friend CATExpDynamic CATExpDynamicMakeVarFromPlaneEval(const std::array<double, 4>& v1, const std::array<double, 3> & v2)
  {
    
    std::array<double, 4> v1m = { v1[0] >= 0.0 ? v1[0] : -v1[0] , v1[1] >= 0.0 ? v1[1] : -v1[1] , v1[2] >= 0.0 ? v1[2] : -v1[2] , v1[3] >= 0.0 ? v1[3] : -v1[3] };
    /*
    // [16/12/2016 RNO] : It seems to be 10% faster to do a fake 4-Dim DOT Product (at least on intel with Visual Studio 2012)
    // ... and i don't know why so i don't change it
    std::array<double, 4> v2x = { v2[0],v2[1],v2[2],1. };
    std::array<double, 4> v2m = { v2[0] >= 0.0 ? v2[0] : -v2[0] , v2[1] >= 0.0 ? v2[1] : -v2[1] , v2[2] >= 0.0 ? v2[2] : -v2[2],1.  };
    double x = ((v1[0] * v2x[0]) + (v1[1] * v2x[1])) + ((v1[2] * v2x[2]) + (v1[3]*v2x[3]) );
    double m = ((v1m[0] * v2m[0]) + (v1m[1] * v2m[1])) + ((v1m[2] * v2m[2]) + (v1m[3]*v2x[3]) );*/
    const std::array<double, 3> v2m = { v2[0] >= 0.0 ? v2[0] : -v2[0] , v2[1] >= 0.0 ? v2[1] : -v2[1] , v2[2] >= 0.0 ? v2[2]: -v2[2] };
    const double x = ((v1[0] * v2[0]) + (v1[1] * v2[1])) + ((v1[2] * v2[2]) + (v1[3] ));
    const double m = ((v1m[0] * v2m[0]) + (v1m[1] * v2m[1])) + ((v1m[2] * v2m[2]) + (v1m[3]));
    
    return CATExpDynamic(x, m, 5);
  }

  inline friend CATExpDynamic CATExpDynamicMakeVarFrom2x2Determinant(const std::array<double, 2> &v1, const std::array<double, 2> &v2)
  {
    std::array<double, 2> v1m = { v1[0] >= 0.0 ? v1[0] : -v1[0] , v1[1] >= 0.0 ? v1[1] : -v1[1] };
    std::array<double, 2> v2m = { v2[0] >= 0.0 ? v2[0] : -v2[0] , v2[1] >= 0.0 ? v2[1] : -v2[1] };
    const double x = v1[0] * v2[1] - v1[1] * v2[0];
    const double m = v1m[0] * v2m[1] + v1m[1] * v2m[0];
    return CATExpDynamic(x, m, 4);
  }

  inline friend CATExpDynamic CATExpDynamicMakeVarFrom2x2Determinant(double x1, double y1, double x2, double y2)
  {
    std::array<double, 2> v1m = { x1 >= 0.0 ? x1 : -x1 , y1 >= 0.0 ? y1 : -y1 };
    std::array<double, 2> v2m = { x2 >= 0.0 ? x2 : -x2 , y2 >= 0.0 ? y2 : -y2 };
    const double x = x1 * y2 - x2 * y1;
    const double m = v1m[0] * v2m[1] + v1m[1] * v2m[0];
    return CATExpDynamic(x, m, 4);
  }

  inline friend CATExpDynamic CATExpDynamicMakeVarFrom3x3Determinant(const std::array<double, 3> &v1, 
                                                                     const std::array<double, 3> &v2, 
                                                                     const std::array<double, 3> &v3)
  {
    const std::array<double, 3> v1m = { v1[0] >= 0.0 ? v1[0] : -v1[0] , v1[1] >= 0.0 ? v1[1] : -v1[1] , v1[2] >= 0.0 ? v1[2] : -v1[2]  };
    const std::array<double, 3> v2m = { v2[0] >= 0.0 ? v2[0] : -v2[0] , v2[1] >= 0.0 ? v2[1] : -v2[1] , v2[2] >= 0.0 ? v2[2] : -v2[2]  };
    const std::array<double, 3> v3m = { v3[0] >= 0.0 ? v3[0] : -v3[0] , v3[1] >= 0.0 ? v3[1] : -v3[1] , v3[2] >= 0.0 ? v3[2] : -v3[2]  };
  
    const double SubM1_x= ((v2[1])*(v3[2]) - (v2[2])*(v3[1]));
    const double SubM2_x= ((v2[2])*(v3[0]) - (v2[0])*(v3[2]));
    const double SubM3_x= ((v2[0])*(v3[1]) - (v2[1])*(v3[0]));
    //TReal ToReturn(CATExpMakeVar<TReal>(v1[0])*SubM1 + CATExpMakeVar<TReal>(v1[1])*SubM2 + CATExpMakeVar<TReal>(v1[2])*SubM3);

    const double x = (v1[0])*SubM1_x + (v1[1])*SubM2_x + (v1[2])*SubM3_x;

    const double SubM1_m= ((v2m[1])*(v3m[2]) + (v2m[2])*(v3m[1]));
    const double SubM2_m= ((v2m[2])*(v3m[0]) + (v2m[0])*(v3m[2]));
    const double SubM3_m= ((v2m[0])*(v3m[1]) + (v2m[1])*(v3m[0]));
    //TReal ToReturn(CATExpMakeVar<TReal>(v1m[0])*SubM1 + CATExpMakeVar<TReal>(v1m[1])*SubM2 + CATExpMakeVar<TReal>(v1m[2])*SubM3);

    const double m = (v1m[0])*SubM1_m + (v1m[1])*SubM2_m + (v1m[2])*SubM3_m;

    return CATExpDynamic(x, m, 8);

  }
public:

  CATExpDynamic() __EXPNOEXCEPT__ = default;
  ~CATExpDynamic() = default;
  CATExpDynamic(const CATExpDynamic & iOther) __EXPNOEXCEPT__ = default;
  CATExpDynamic & operator = (const CATExpDynamic & iOther) __EXPNOEXCEPT__ = default;
  CATExpDynamic(CATExpDynamic && iOther) __EXPNOEXCEPT__ = default;
  CATExpDynamic & operator = (CATExpDynamic && iOther) __EXPNOEXCEPT__  = default;

  CATExpDynamic operator- () const
  { return CATExpDynamic(- x_, m_, d_); }

  CATExpDynamic &operator+= (const CATExpDynamic &b) __EXPNOEXCEPT__
  { x_ += b.x_; m_ += b.m_; d_ = 1 + std::max<unsigned>(d_, b.d_); return *this; }

  CATExpDynamic &operator-= (const CATExpDynamic &b) __EXPNOEXCEPT__
  { x_ -= b.x_; m_ += b.m_; d_ = 1 + std::max<unsigned>(d_, b.d_); return *this; }

  CATExpDynamic &operator*= (const CATExpDynamic &b) __EXPNOEXCEPT__
  { x_ *= b.x_; m_ *= b.m_; d_ += 1 + b.d_; return *this; }

  CATExpSign_t Sign() const
  {
    const double error = Error();
    const double value = x_;
    if (value > error ) return CATExpPOSITIVE;
    else if (value < - error) return CATExpNEGATIVE;
    else if (error == 0.) return CATExpZERO; // because value == error == 0.
    else return CATExpSIGNUNDEF; // including the case where a.m() is NaN (all comparisons becoming false)
  }

  double Estimate() const __EXPNOEXCEPT__  { return x_; }
  double LowerBound() const __EXPNOEXCEPT__ { return Estimate() - Error(); }
  double UpperBound() const __EXPNOEXCEPT__ { return Estimate() + Error(); }

private:
  CATExpDynamic(double x, double m, unsigned d) : x_(x), m_(m), d_(d) {}

  double Error() const __EXPNOEXCEPT__  { return (static_cast<std::uint64_t>(d_) + 2) * DBL_EPSILON * m_ * 0.5; }// Correction overflow VS2017 Code Analysis[6/3/2019 RNO]

  ///The estimate value of the number.
  double x_ = 666.;
  
  ///An upper bound on the absolute value of the number.
  double m_ = 666.;

  ///The error index of the number, used for the semi-static filtering.
  unsigned d_ = 666;
};

inline CATExpDynamic CATExpDynamicMakeVarFromDotProduct(const std::array<CATExpDynamic, 4>& v1, const std::array<double, 4> & v2) { return CATExpDynamicMakeVarFromDotProduct(v2, v1); }


inline CATExpDynamic operator+ (CATExpDynamic x1, const CATExpDynamic &x2)
{ 
  x1 += x2;
  return x1; // do not write "return x1 += x2;"
}

inline CATExpDynamic operator- (CATExpDynamic x1, const CATExpDynamic &x2)
{ 
  x1 -= x2;
  return x1;
}

inline CATExpDynamic operator* (CATExpDynamic x1, const CATExpDynamic &x2)
{
  x1 *= x2;
  return x1;
}


/* =========== Numbers factory functions ================= */
//Template Specialization
template <> inline CATExpDynamic CATExpMakeVarFromDiff<CATExpDynamic> (double a, double b)
{ return CATExpDynamicMakeVarFromDiff(a, b); }

template <> inline CATExpDynamic CATExpMakeVar<CATExpDynamic> (double x)
{ return CATExpDynamicMakeVar(x); }

/// a constant is representable iff it is exactly represented as a double (like 0, 0.5, 1, 2 etc.)
template <> inline CATExpDynamic CATExpMakeRepresentableConstant<CATExpDynamic> (double x)
{ return CATExpDynamicMakeRepresentableConstant(x); }

template <> inline CATExpDynamic CATExpMakeConstant<CATExpDynamic> (double x)
{ return CATExpDynamicMakeConstant(x); }



#if CATEXPADVMAKEVAR_LEVEL >= 1

template <>
struct CATExpAdvMakeVar<CATExpDynamic>
{
  template<size_t DIM>
  static inline CATExpDynamic FromDotProduct(const std::array<double, DIM> & v1, const std::array<double, DIM> & v2)
  {
    return CATExpDynamicMakeVarFromDotProduct<DIM>(v1, v2);
  }
  template<size_t DIM>
  static inline CATExpDynamic FromDotProduct(const std::array<CATExpDynamic, DIM> & v1, const std::array<double, DIM>& v2)
  {
    static_assert(DIM >= 1, "CATExpAdvMakeVar::DotProduct Requires DIM>=1");
    if(DIM==4)
    {
      return CATExpDynamicMakeVarFromDotProduct(v2,v1);
    }
    else
    {
      CATExpDynamic a = v1[0] * CATExpMakeVar<CATExpDynamic>(v2[0]);
      for(size_t i = 1; i < DIM; i++)
      {
        a += v1[i] * CATExpMakeVar<CATExpDynamic>(v2[i]);
      }
      return a;
    }
  }
  template<size_t DIM>
  static inline CATExpDynamic FromDotProduct(const std::array<double, DIM> & v1, const std::array<CATExpDynamic, DIM>& v2)
  {
    return FromDotProduct<DIM>(v2, v1);
  }

  static inline CATExpDynamic FromPlaneEval(const std::array<double, 4> &v1, const std::array<double, 3> &v2)
  {
    return  CATExpDynamicMakeVarFromPlaneEval(v1, v2);
  }
  static inline CATExpDynamic From2x2Determinant(const std::array<double, 2> &v1, const std::array<double, 2> &v2)
  {
    return  CATExpDynamicMakeVarFrom2x2Determinant(v1, v2);
  }

  static inline CATExpDynamic From2x2Determinant(double x1, double y1, double x2, double y2)
  {
    return  CATExpDynamicMakeVarFrom2x2Determinant(x1, y1, x2, y2);
  }

  static inline CATExpDynamic From3x3Determinant(const std::array<double, 3> &v1, const std::array<double, 3> &v2, const std::array<double, 3> &v3)
  {
    return  CATExpDynamicMakeVarFrom3x3Determinant(v1,v2,v3);
  }

};

#endif



#endif //CATExpDynamic_H

