#ifndef CATFrFCCvParam_H
#define CATFrFCCvParam_H

/** @CAA2Required */ 
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES 1998
//==========================================================================
//
// CATFrFCCvParam:
// Class representing a location on a CATFrFCompositeCurve. The CATFrFCCvParam
// is not related to CATFrFCompositeCurve. The user of a CATFrFCCvParam has
// to know to which CATFrFCompositeCurve a CATFrFCCvParam belongs.
// This class contains  :
//    an index (a CATLONG32) which should correspond to the index of a CATCurve
// of a CATFrFCompositeCurve,
//    a curve parameter (a CATCrvParam) on this curve. As a CATCrvParam
// is related to a CATCurve, one can find the curve given by the index
// BUT not the CompositeCurve,
//    a parameter (a double) which may represent a parameter from a
// mapping or a coupling and be used to sort out CATFrFCCvParams
// and whose value and life cycle are not guaranteed in any way.
//
// CATFrFCCvParam_EqualityRemoved JSX020608
#define CATFrFCCvParam_EqualityRemoved
//==========================================================================
#include "CATGMOperatorsInterfaces.h"
#include "CATCrvParam.h"
#include "CATCGMVirtual.h"
#include "CATIAV5Level.h"

class CATFrFCCvParam;

//-----------------------------------------------------------------------------
class ExportedByCATGMOperatorsInterfaces CATFrFCCvParam : public CATCGMVirtual
{
 public :
//=============================================================================
// Constructors and Destructors
//=============================================================================
//
// Default constructor : constructs an empty CATFrFCCvParam
//
  CATFrFCCvParam ();

//
// Constructs a CATFrFCCvParam from a CATLONG32, a CATCrvParam and
// a double (set to 0. if not given).
//
  CATFrFCCvParam (const CATLONG32 iCrvIndex,
                  const CATCrvParam& iCrvParam,
                        double iParameter = 0.);

//
// Copy Constructor.
//
  CATFrFCCvParam (const CATFrFCCvParam &);

//
// Destructor
//
  virtual ~CATFrFCCvParam();

//=============================================================================
// Set and Get Methods
//=============================================================================
//
// Get CrvIndex
//
  CATLONG32 GetCrvIndex() const
    {
     return _CrvIndex;
    }
//
// Get CrvParam
//
  CATCrvParam GetCrvParam() const
    {
     return _CrvParam;
    }
//
// Get Parameter
//
  double GetParameter() const
    {
     return _Parameter;
    }
//
// Set CrvIndex
//
  void SetCrvIndex(CATLONG32 iCrvIndex)
    {
     if (iCrvIndex >= 0)
        _CrvIndex = iCrvIndex;
    }
//
// Set CrvParam
//
  void SetCrvParam(const CATCrvParam& iCrvParam)
    {
     _CrvParam = iCrvParam;
    }
//
// Set Parameter
//
  void SetParameter(double iParameter)
    {
     _Parameter = iParameter;
    }

//=============================================================================
// Overloaded operators
//=============================================================================
#ifndef CATFrFCCvParam_EqualityRemoved
//
// Defines the equality test of two CATFrFCCvParams.
//
  CATLONG32 operator == (const CATFrFCCvParam &) const ;
#endif
//
// Defines the equality of two CATFrFCCvParams.
//
  const CATFrFCCvParam& operator = (const CATFrFCCvParam &);
/**
 * Defines the greater than or equal to operator.
 * <br>Let <tt>n=iP.GetCrvIndex, p=iP.GetCrvParam<br>
 * (iP1 >= iP2)<=>( (n1 > n2) or (n1 == n2 and p1 >= p2) </tt>
 */
  CATLONG32 operator >= (const CATFrFCCvParam & iOtherCCvParam) const;

 protected :
//=============================================================================
// Datas
//=============================================================================
 CATLONG32           _CrvIndex;
 CATCrvParam         _CrvParam;
 double              _Parameter;
 
};
#endif


