#ifndef CATTolerance_H
#define CATTolerance_H

// COPYRIGHT DASSAULT SYSTEMES  2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"
#include "YN000MAT.h"
#include "CATCGMVirtual.h"

#include "CATMathInline.h"
#include "CATMathDef.h"
#include "CATMathConstant.h"

#include "CATCGMScaleCategoryDef.h"
#include "CATCGMExclusive.h"

#if defined CATIAR418 || defined CATIAV5R26
#else
#include "CATThrowForNullPointer.h"
#endif

class CATCGMOwner;
/**
 * 
 * Class representing a set of geometric and mathematical values associated to a CATGeoFactory and related to its scale. 
 * Each CATGeoFactory has a scale, which is set at its creation and cannot be changed afterwards. 
 * It determines a set of values such as the model resolution and model size.
 * By default a CATGeoFactory is in Normal Scale, which means that the model resolution is 0.001; 
 * alternatively it can be in Large Scale (model resolution 0.1) or Small Scale (model resolution 0.00001).
 * An instance of CATTolerance must be retrieved from a CATGeoFactory or one of the CATICGMObject it contains through the method GetToleranceObject (defined in the base class CATICGMUnknown).
 * It must not be created through the default constructor or the global method CATGetDefaultTolerance, as these methods return a CATTolerance that is always in Normal Scale
 * and do not take into account the one or several CATGeoFactory that may exist in the session, and which may be in different scales.
 */
//----------------------------------------------------------------
class ExportedByYN000MAT CATTolerance:  public CATCGMExclusive
{
public:
  /** @nodoc  */
  CATCGMNewClassArrayDeclare;

public:
  /** @nodoc */
  CATTolerance& operator=(const CATTolerance &iCopy);

private:
  friend class CATRootSharedDataCGM;
  friend class CATTolerancePrivate;

  /** @nodoc */
  INLINE CATTolerance(const CATTolerance &iCopy);

public:

/** 
 * This default constructor should not be used. See class comments.
 */
  CATTolerance(); 

  /** @nodoc */
  virtual ~CATTolerance();

/**
 * Set of methods for Mathematical Tolerances compliant wtih Extreme Scale behavior (ie Large/Small Scale behavior). 
 */
public:
/**
 * Returns the maximum float value (non-scaled value).
 */
  INLINE double Infinite() const;

//==========================================================================================
// The methods called xxxForLengthTest() define numerical tolerances to do absolute tests 
// homogeneous to a LENGTH.
// Each method return SCALED values, i.e values DEPENDANT from the scale 
//==========================================================================================
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a length.
 * For standard scale, it is equal to CATEpsilon = 1.e-15
 * In general it is equal to CATEpsilon * scale
 */ 
  INLINE double EpsilonForLengthTest() const;
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a length.
 * homogeneous to a length.
 * For standard scale, it is equal to CATEpsg = 1.e-12
 * In general it is equal to CATEpsg * scale
 */ 
  INLINE double EpsgForLengthTest() const;
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to a length.
 * For standard scale, it is equal to 1.e-6 (that corresponds to CATSqrtEpsg in CATMathLimits.h)
 * In general it is equal to  1.e-6 * scale
 */ 
  INLINE double LargeEpsgForLengthTest() const;

//==========================================================================================
// The methods called xxxForSquareLengthTest() define numerical tolerances to do absolute tests 
// homogeneous to a SQUARE OF A LENGTH.
// Each method return SCALED values, i.e values DEPENDANT from the square of the scale 
//==========================================================================================
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to a square length.
 * For standard scale, it is equal to CATEpsg **2 = 1.e-24  (equal to CATSquareEpsg in CATMathlimits)
 * In general it is equal to (CATEpsg * scale)**2
 */ 
  INLINE double EpsgForSquareLengthTest() const;
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to a square length.
 * For standard scale, it is equal to CATEpsilon **2 = 1.e-30 (equal to CATSquareEpsilon in CATMathlimits)
 * In general it is equal to (CATEpsilon * scale)**2
 */ 
  INLINE double EpsilonForSquareLengthTest() const;

//==========================================================================================
// The methods called xxxForAngleTest() define numerical tolerances to do absolute tests 
// homogeneous to an angle.
// Each method return NON-Scaled values, i.e values INDEPENDANT from the scale 
//========================================================================================== 
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to an angle.
 * For all scales, it is equal to CATEpsilon = 1.e-15
 */ 
  INLINE CATAngle EpsilonForAngleTest() const; // Radian
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to an angle.
 * For all scales, it is equal to CATEpsg = 1.e-12
 */ 
  INLINE CATAngle EpsgForAngleTest() const; // Radian
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to an angle.
 * For all scales, it is equal to 1.e-6
 */ 
  INLINE CATAngle LargeEpsgForAngleTest() const; // Radian
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to the square of an angle.
 * For all scales, it is equal to CATEpsilon **2 = 1.e-30 (equal to CATSquareEpsilon in CATMathlimits)
 */ 
  INLINE double EpsilonForSquareAngleTest() const;
/**
 * Returns a  numerical tolerance used to perform absolute tests homogeneous to the square of an angle.
 * For all scales, it is equal to CATEpsg **2 = 1.e-24 (equal to CATSquareEpsg in CATMathlimits)
 */ 
  INLINE double EpsgForSquareAngleTest() const; 
  
  
//==========================================================================================
// The methods called xxxForRelativeTest() define numerical tolerances to do Relative Tests.
// Each method return NON-Scaled values, i.e values INDEPENDANT from the scale 
//==========================================================================================
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to CATEpsg=1.e-12 (You can refer to CATMathLimits.h)
 */ 
  INLINE double EpsgForRelativeTest() const;
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to 1.e-6 
 */ 
  INLINE double LargeEpsgForRelativeTest() const;
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to CATEpsilon=1.e-15 (You can refer to CATMathLimits.h)
 */ 
  INLINE double EpsilonForRelativeTest() const;
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to CATSquareEpsg=1.e-24 (You can refer to CATMathLimits.h)
 */ 
  INLINE double SquareEpsgForRelativeTest() const;
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to CATSquareEpsilon=1.e-30 (You can refer to CATMathLimits.h)
 */ 
  INLINE double SquareEpsilonForRelativeTest() const;
/**
 * The numerical tolerance returned by SqrtEpsgForRelativeTest()is the same for all scales.
 * It is equal to CATSqrtEspg=1.e-6 (You can refer to CATMathLimits.h)
 */ 
  INLINE double SqrtEpsgForRelativeTest() const;
/**
 * Returns a numerical tolerance which is the same for all scales.
 * It is equal to CATSqrtEspilon=sqrt(1.e-15) (You can refer to CATMathLimits.h)
 */ 
  INLINE double SqrtEpsilonForRelativeTest() const;

/**
 * Returns a numerical tolerance (float) which is the same for all scales.
 * It is equal to CATEpsilonf=1.e-14 (You can refer to CATMathLimitsf.h)
 */ 
  INLINE float EpsilonfForRelativeTest() const;

//===================================================================================================
// Take care of the use of the two following methods. There are homogeneous to the SQRT of the scale
// Before using these two methods, you must check that the value to check is also homogeneous 
// to the SQRT of the scale. 
// 
// The methods called xxxForSqrtLengthTest() define numerical tolerances to do absolute tests 
// homogeneous to a Sqrt of a length.
// Each method return SCALED values, i.e values DEPENDANT from the SQRT OF THE SCALE
//==================================================================================================
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a sqrt of length.
 * For standard scale, it is equal to sqrt(CATEpsg) = 1.e-6
 * In general it is equal to sqrt(CATEpsg * scale)
 */   
  INLINE double EpsgForSqrtLengthTest() const;
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a sqrt of length.
 * For standard scale, it is equal to sqrt(CATEpsilon) = sqrt(1.e-15)
 * In general it is equal to sqrt(CATEpsilon * scale)
 */ 
  INLINE double EpsilonForSqrtLengthTest() const;

//===================================================================================================
// The methods called xxxForSqrtLengthTest() define numerical tolerances to do absolute tests 
// homogeneous to a Sqrt of an angle.
// Each method return NON-SCALED values, i.e values INDEPENDANT from the scale 
//==================================================================================================
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a sqrt of length.
 * For all scales, it is equal to sqrt(CATEpsg) = 1.e-6
 */   
  INLINE double EpsgForSqrtAngleTest() const;  
/**
 * Returns a numerical tolerance used to perform absolute tests homogeneous to a sqrt of length.
 * For all scales, it is equal to sqrt(CATEpsilon) = sqrt(1.e-15)
 */   
  INLINE double EpsilonForSqrtAngleTest() const;

/**
 * Set of methods for Geometric Tolerances compliant wtih Large/Small Scale behavior.
 */
public:
/**
 * Same definition as in CATGeoFactory.h
 */ 
  enum ResolutionType
  { CatC0, CatC1, CatC2 };

public:
/**
 * Retrieves the model size.
 */  
  INLINE double ModelSize() const;

/**
 * @nodoc
 */  
  void SetModelSize(double iModelSize);

/**
 * Retrieves the infinite value.
 */
  INLINE double ModelInfinite() const;

/**
 * @nodoc
 */  
  void SetModelInfinite(double iModelInfinite);

/**
 * The definition of Resolution is the same as in CATGeoFactory.h
 */
  /**
  * @nodoc
  */
  INLINE CATAngle ResolutionForAngleTest() const; // Radian
/**
  * @nodoc
  */
  INLINE CATPositiveLength ResolutionForLengthTest() const;

  /**
  * @nodoc
  */
  INLINE double GetResolution(CATTolerance::ResolutionType iResolutionType = CATTolerance::CatC0) const;

  /**
  * @nodoc
  */
  INLINE double ResolutionForSquareLengthTest() const;

  /**
  * @nodoc
  */
  INLINE double ResolutionForSqrtLengthTest() const;

  /**
  * @nodoc
  */
  INLINE CATAngle LargeResolutionForAngleTest() const; // Radian
  /**
  * @nodoc
  */
  INLINE CATPositiveLength LargeResolutionForLengthTest() const;
  /**
  * @nodoc
  */
  INLINE double LargeResolutionForSquareLengthTest() const;
  /**
  * @nodoc
  */
  INLINE double LargeResolutionForSqrtLengthTest() const;


  // Scale
  //=======
public:
/**
 * You should avoid using of the 3 following methods.
 * The Scale corresponds to the order of magnitude of the model.
 * In standard models, the value of the scale is 1. It corresponds to models
 * for which smaller element is 1.e-3 and bigger element is 1.e+6
 */
/**
  * @nodoc
  */
  INLINE double GetScale() const;
/**
  * @nodoc
  */
  INLINE double GetSquareScale() const;
/**
  * @nodoc
  */
  INLINE double GetSqrtScale() const;

// 
public:
/**
  * @nodoc
  */
  void SetScale(double iScale);
/**
  * @nodoc
  */  
  static CATCGMScaleCategory GetScaleCategoryFromResolution(double iResolutionC0);
/**
  * @nodoc
  */  
  static CATCGMScaleCategory ConvertScaleToScaleCategory(double &ioScale);
/**
  * @nodoc
  */  
  static double ConvertScaleCategoryToScale(CATCGMScaleCategory iScaleCategory);
/**
  * @nodoc
  */  
#ifdef CATIACGMR216CAA
  CATCGMScaleCategory GetScaleCategory() const;
#else
  CATCGMScaleCategory GetScaleCategory();
#endif
/**
  * @nodoc
  */  
  void SetScaleCategory(CATCGMScaleCategory iScaleCategory);
/**
  * @nodoc
  */  
#ifdef CATIACGMR216CAA
  CATCGMScaleRange GetRange() const;
#else
  CATCGMScaleRange GetRange();
#endif
  
  /** @nodoc  */
  void SetToleranceOwner( CATCGMOwner * iOwner );
  
private:
  /** @nodoc  */
  void SetScaleCategoryInternal (CATCGMScaleCategory iScaleCategory);
  /** @nodoc  */
  void SetScaleInternal         (CATCGMScaleCategory iScaleCategory, double iScale);
  /** @nodoc  */
  void SetRange                 (CATCGMScaleRange iRange);
  /** @nodoc  */
#ifdef CATIACGMR216CAA
  CATCGMScaleRange GetRangeFromModelSize()const;
#else
  CATCGMScaleRange GetRangeFromModelSize();
#endif
  /** @nodoc  */
  CATBoolean  ChecksBeforeModification () const;
//--------------------------------------------------------------------------------------------------------  
private:
  double _Scale;
  double _SquareScale;
  double _SqrtScale;
  CATCGMScaleCategory _ScaleCategory;
  CATCGMScaleRange    _Range;

  // Mathematic
  // Not-scaled values
  double _Infinite;

  double _EpsgForRelativeTest;
  double _EpsilonForRelativeTest;

  double _SquareEpsgForRelativeTest;
  double _SquareEpsilonForRelativeTest;

  double _SqrtEpsgForRelativeTest;
  double _SqrtEpsilonForRelativeTest;

  //
  CATAngle _EpsgForAngleTest; // Radian
  CATAngle _EpsilonForAngleTest; // Radian

  double _EpsgForSquareAngleTest; 
  double _EpsilonForSquareAngleTest;

  double _EpsgForSqrtAngleTest;
  double _EpsilonForSqrtAngleTest;

  double _EpsgForLengthTest;
  double _EpsilonForLengthTest;

  double _EpsgForSquareLengthTest;
  double _EpsilonForSquareLengthTest;

  double _EpsgForSqrtLengthTest;
  double _EpsilonForSqrtLengthTest;

  double _LargeEpsgForLengthTest;
  CATAngle _LargeEpsgForAngleTest;
  double _LargeEpsgForRelativeTest;

  float _EpsilonfForRelativeTest;

  // Geometric
private:
  double _ModelSize;
  double _ModelInfinite;

  // Pow 1
  CATAngle _ResolutionForAngleTest; // Radian

  CATPositiveLength _ResolutionForLengthTest;

  double _Curvature;

  // Pow 2
  double _ResolutionForSquareLengthTest;

  // Pow 0.5
  double _ResolutionForSqrtLengthTest;

  // Large
  CATAngle _LargeResolutionForAngleTest; // Radian

  CATPositiveLength _LargeResolutionForLengthTest;

  double _LargeResolutionForSquareLengthTest;

  double _LargeResolutionForSqrtLengthTest;

  int    _DefaultToleranceStatus;

};
//--------------------------------------------------------------------------------------------
// Default Tolerance
//--------------------------------------------------------------------------------------------
/**
 * @nodoc
 * Should not be used. See class comments.
 **/
ExportedByYN000MAT const CATTolerance & CATGetDefaultTolerance();

/** @nodoc  */
ExportedByYN000MAT void CATToleranceError(const CATTolerance * iPtr) ;
#define CATToleranceCheckDefault if ( _DefaultToleranceStatus>0) CATToleranceError(this);

//--------------------------------------------------------------------------------------------
// XScale Checks
//--------------------------------------------------------------------------------------------
/** @nodoc **/
#define CATToleranceCheckStandard //

// INLINE methods implementation
INLINE 
CATTolerance::CATTolerance(const CATTolerance &iTolerance) {
  *this = iTolerance; 
}

//
INLINE double
CATTolerance::GetScale() const
{
  CATToleranceCheckDefault
  return _Scale;
}
//
INLINE double
CATTolerance::GetSquareScale() const
{
  CATToleranceCheckDefault
  return _SquareScale;
}

INLINE double
CATTolerance::GetSqrtScale() const
{
  CATToleranceCheckDefault
  return _SqrtScale;
}

// Mathematic
// Not-scaled values
INLINE double
CATTolerance::Infinite() const
{
  CATToleranceCheckStandard
  return _Infinite;
}

INLINE double
CATTolerance::EpsgForRelativeTest() const
{
  CATToleranceCheckStandard
  return _EpsgForRelativeTest;
}
INLINE double
CATTolerance::EpsilonForRelativeTest() const
{
  CATToleranceCheckStandard
  return _EpsilonForRelativeTest;
}

INLINE double
CATTolerance::SquareEpsgForRelativeTest() const
{
  CATToleranceCheckStandard
  return _SquareEpsgForRelativeTest;
}
INLINE double
CATTolerance::SquareEpsilonForRelativeTest() const
{
  CATToleranceCheckStandard
  return _SquareEpsilonForRelativeTest;
}

INLINE double
CATTolerance::SqrtEpsgForRelativeTest() const
{
  CATToleranceCheckStandard
  return _SqrtEpsgForRelativeTest;
}
INLINE double
CATTolerance::SqrtEpsilonForRelativeTest() const
{
  CATToleranceCheckStandard
  return _SqrtEpsilonForRelativeTest;
}
//
INLINE CATAngle
CATTolerance::EpsgForAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsgForAngleTest;
} // Radian
INLINE CATAngle
CATTolerance::EpsilonForAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsilonForAngleTest;
} // Radian

INLINE double
CATTolerance::EpsgForSquareAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsgForSquareAngleTest;
}
INLINE double
CATTolerance::EpsilonForSquareAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsilonForSquareAngleTest;
}

INLINE double
CATTolerance::EpsgForSqrtAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsgForSqrtAngleTest;
}
INLINE double
CATTolerance::EpsilonForSqrtAngleTest() const
{
  CATToleranceCheckStandard
  return _EpsilonForSqrtAngleTest;
}

INLINE double
CATTolerance::EpsgForLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsgForLengthTest;
}
INLINE double
CATTolerance::EpsilonForLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsilonForLengthTest;
}

INLINE double
CATTolerance::EpsgForSquareLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsgForSquareLengthTest;
}
INLINE double
CATTolerance::EpsilonForSquareLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsilonForSquareLengthTest;
}

INLINE double
CATTolerance::EpsgForSqrtLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsgForSqrtLengthTest;
}
INLINE double
CATTolerance::EpsilonForSqrtLengthTest() const
{
  CATToleranceCheckDefault
  return _EpsilonForSqrtLengthTest;
}

// Geometric
INLINE double
CATTolerance::ModelSize() const
{
  CATToleranceCheckDefault
  return _ModelSize;
}
INLINE double
CATTolerance::ModelInfinite() const
{
  CATToleranceCheckDefault
  return _ModelInfinite;
}

// Pow 1
INLINE CATAngle
CATTolerance::ResolutionForAngleTest() const
{
  CATToleranceCheckStandard
  return _ResolutionForAngleTest;
}

INLINE CATPositiveLength
CATTolerance::ResolutionForLengthTest() const
{
  CATToleranceCheckDefault
  return _ResolutionForLengthTest;
}
/**
  * @nodoc
  */
INLINE double
CATTolerance::GetResolution(CATTolerance::ResolutionType iResolutionType) const
{
  if (iResolutionType == CATTolerance::CatC0)
    return ResolutionForLengthTest();
  else if (iResolutionType == CATTolerance::CatC1)
    return ResolutionForAngleTest();
  CATToleranceCheckDefault
  return _Curvature;
}

// Pow 2
INLINE double
CATTolerance::ResolutionForSquareLengthTest() const
{
  CATToleranceCheckDefault
  return _ResolutionForSquareLengthTest;
}

// Pow 0.5
INLINE double
CATTolerance::ResolutionForSqrtLengthTest() const
{
  CATToleranceCheckDefault
  return _ResolutionForSqrtLengthTest;
}

/**
  * @nodoc
  */
INLINE CATAngle
CATTolerance::LargeResolutionForAngleTest() const
{
  CATToleranceCheckStandard
  return _LargeResolutionForAngleTest;
}
/**
  * @nodoc
  */
INLINE CATPositiveLength
CATTolerance::LargeResolutionForLengthTest() const
{
  CATToleranceCheckDefault
  return _LargeResolutionForLengthTest;
}
/**
  * @nodoc
  */
INLINE double
CATTolerance::LargeResolutionForSquareLengthTest() const
{
  CATToleranceCheckDefault
  return _LargeResolutionForSquareLengthTest;
}
/**
  * @nodoc
  */
INLINE double
CATTolerance::LargeResolutionForSqrtLengthTest() const
{
  CATToleranceCheckDefault
  return _LargeResolutionForSqrtLengthTest;
}
/**
  * @nodoc
  */
INLINE double
CATTolerance::LargeEpsgForLengthTest() const
{
  CATToleranceCheckDefault
  return _LargeEpsgForLengthTest;
}
/**
  * @nodoc
  */
INLINE CATAngle
CATTolerance::LargeEpsgForAngleTest() const
{
  CATToleranceCheckStandard
  return _LargeEpsgForAngleTest;
}
/**
  * @nodoc
  */
INLINE float
CATTolerance::EpsilonfForRelativeTest() const
{
  CATToleranceCheckStandard
  return _EpsilonfForRelativeTest;
}

/**
  * @nodoc
  */
INLINE double CATTolerance::LargeEpsgForRelativeTest() const
{
  CATToleranceCheckStandard
  return _LargeEpsgForRelativeTest;
}

#endif // !CATTolerance_H
