//===================================================================
// COPYRIGHT Dassault Systemes 2013
//===================================================================
//
// Usage notes:
//   These templates are specialized by CATExpDynamic.
//
//===================================================================
//  06/12/2016 : RNO : Ajout Produit Scalaire 4x4
//  May 2013 - T6L : Creation
//===================================================================
//

#ifndef CATExpNumbersOperators_H
#define CATExpNumbersOperators_H

#include "CATExpEnums.h"

#include <array>

template <typename NT>
inline CATExpSign_t SignOf(const NT &a) { return a.Sign(); }

template <typename NT>
inline double ToDouble(const NT &a) { return a.Estimate(); }

template <typename NT>
inline double LowerBound(const NT &a) { return a.LowerBound(); }

template <typename NT>
inline double UpperBound(const NT &a) { return a.UpperBound(); }


template <typename NT>
inline NT CATExpMakeVarFromDiff (double a, double b)
{ return NT(a) - NT(b); }

template <typename NT>
inline NT CATExpMakeVar (double a)
{ return NT(a); }

/// a constant is representable iff it is exactly represented as a double (like 0, 0.5, 1, 2 etc.)
template <typename NT>
inline NT CATExpMakeRepresentableConstant (double a)
{ return NT(a); }

template <typename NT>
inline NT CATExpMakeConstant (double a)
{ return NT(a); }


//Four Dim Dot Product
//One Define to check for the availability of the Advanced Var Maker
#define CATEXPADVMAKEVAR_LEVEL 1 


#if CATEXPADVMAKEVAR_LEVEL >= 1
//===============================================================================================================
//                                         AVANCED MAKE FROM HIGHER LEVEL ALGEBRAIC EQUATIONS
//                                    (Mots of them are optimised for CATExpDynamicType
//===============================================================================================================
template <typename NT>
struct CATExpAdvMakeVar
{
  //===============================================================================================================
  //                                         SHORTCUTS FOR 4-DIM DOT PRODUCTS
  //                                                (ax+by)+(cz+dw)
  //  These implementations are overloaded by template specialization
  //===============================================================================================================
  template<size_t DIM>
  static inline NT FromDotProduct(const std::array<double, DIM>& v1, const std::array<double, DIM> & v2 )
  {
    static_assert(DIM >= 1, "CATExpAdvMakeVar::FromDotProduct Requires DIM>=1");
    NT a = CATExpMakeVar<NT>(v1[0])* CATExpMakeVar<NT>(v2[0]);
    for(size_t i = 1; i < DIM; i++)
    {
      a += CATExpMakeVar<NT>(v1[i])* CATExpMakeVar<NT>(v2[i]);
    }
    return a;
  }

  template<size_t DIM>
  static inline NT FromDotProduct(const std::array<NT, DIM> & v1, const std::array<double, DIM>& v2)
  {
    static_assert(DIM >= 1, "CATExpAdvMakeVar::DotProduct Requires DIM>=1");
    NT a = v1[0] * CATExpMakeVar<NT>(v2[0]);
    for(size_t i = 1; i < DIM; i++)
    {
      a += v1[i] * CATExpMakeVar<NT>(v2[i]);
    }
    return a;
  }
  template<size_t DIM>
  static inline NT FromDotProduct(const std::array<double, DIM> & v1, const std::array<NT, DIM>& v2)
  {
    return FromDotProduct<DIM>(v2, v1);
  }

  //===============================================================================================================
  //                                         SHORTCUTS FOR PLANE EQUATION
  //                                                (ax+by)+(cz+d)
  //===============================================================================================================

  static inline NT FromPlaneEval(const std::array<double, 4>& iPlane, const std::array<double, 3> & iPoint)
  {
    return NT((CATExpMakeVar<NT>(iPlane[0]) * CATExpMakeVar<NT>(iPoint[0]) + CATExpMakeVar<NT>(iPlane[1])*CATExpMakeVar<NT>(iPoint[1]))
              + (CATExpMakeVar<NT>(iPlane[2]) * CATExpMakeVar<NT>(iPoint[2]) + CATExpMakeVar<NT>(iPlane[3])));
  }


  //===============================================================================================================
  //                                         SHORTCUTS FOR SMALL DETERMINANT
  //                                                (ax+by)+(cz+d)
  //===============================================================================================================

  static inline NT From2x2Determinant(const std::array<double, 2> &v1, const std::array<double, 2> &v2)
  {
    return NT(CATExpMakeVar<NT>(v1[0])*CATExpMakeVar<NT>(v2[1]) - CATExpMakeVar<NT>(v1[1])*CATExpMakeVar<NT>(v2[0]));//return value optimization
  }

  static inline NT From2x2Determinant(double x1, double y1, double x2, double y2)
  {
    return NT(CATExpMakeVar<NT>(x1)*CATExpMakeVar<NT>(y2) - CATExpMakeVar<NT>(y1)*CATExpMakeVar<NT>(x2));//return value optimization
  }

  static inline NT From3x3Determinant(const std::array<double, 3> &v1, const std::array<double, 3> &v2, const std::array<double, 3> &v3)
  {

    NT SubM1(CATExpMakeVar<NT>(v2[1])*CATExpMakeVar<NT>(v3[2]) - CATExpMakeVar<NT>(v2[2])*CATExpMakeVar<NT>(v3[1]));
    NT SubM2(CATExpMakeVar<NT>(v2[2])*CATExpMakeVar<NT>(v3[0]) - CATExpMakeVar<NT>(v2[0])*CATExpMakeVar<NT>(v3[2]));
    NT SubM3(CATExpMakeVar<NT>(v2[0])*CATExpMakeVar<NT>(v3[1]) - CATExpMakeVar<NT>(v2[1])*CATExpMakeVar<NT>(v3[0]));
    //TReal ToReturn(CATExpMakeVar<TReal>(v1[0])*SubM1 + CATExpMakeVar<TReal>(v1[1])*SubM2 + CATExpMakeVar<TReal>(v1[2])*SubM3);

    return NT(CATExpMakeVar<NT>(v1[0])*SubM1 + CATExpMakeVar<NT>(v1[1])*SubM2 + CATExpMakeVar<NT>(v1[2])*SubM3);//return value optimization
  }

};

#endif






#endif //CATExpDynamic_H

