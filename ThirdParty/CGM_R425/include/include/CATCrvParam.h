#ifndef CATCRVPARAM_H
#define CATCRVPARAM_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"
#include "ExportedByCATCGMGeoMath.h"
#include "CATMathInline.h"

#include "CATParamData.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATCrvLimits;
class CATCrvParamReference;
class CATSetOfCrvParams;
class CATMathTransformation1D;

/**
 * Class representing the global parameter of a point on a CATCurve.
 *<br>The value of
 * the global parameter is defined as the following way:
 * Let be a curve with two arcs. On the first arc, the local parameter goes
 * from <tt>0</tt> to <tt>L1 > 0</tt>; on the second arc, the local parameter
 * goes from <tt>0</tt> to <tt>L2 > 0</tt>. Let be a point of local parameter
 * <tt>L</tt> on the second arc of the curve.
 * The global parameter associated to this point is
 *<tt>L1 + L</tt>. The local parameters are managed by the geometric
 * elements. The first and last arc number are given by
 * the CATCurve::GetMaxLimits method.
 *<br>Note that you also can create CATCrvParams by using the
 *<tt>CreateParam</tt> method of the <tt>CATCurve</tt> interface.
 *@see CATCurve
 */
class  ExportedByCATCGMGeoMath CATCrvParam
{
 public:
//=============================================================================
//- CONSTRUCTORS
//=============================================================================
// Construct from a global parameter and a reference

/**
 * Constructs the <tt>iP1 + iLambda * (iP2-iP1)</tt> parameter.
 *<br>The created CATCrvParam has the reference of <tt>iP1</tt>.
 * @param iLambda
 * The barycentric coefficient.
 * @param iP1
 * The first parameter.
 * @param iP2
 * The second parameter.
 */
#ifdef CATIACGMV5R22
  INLINE CATCrvParam(double  iLambda, const CATCrvParam & iP1,  const CATCrvParam & iP2);
#else
  CATCrvParam(double  iLambda, const CATCrvParam & iP1,  const CATCrvParam & iP2);
#endif

/**
 * Constructs the parameter corresponding to a fraction of 
 * the length of <tt>this</tt> CATCurve.
 * @param iLambda 
 * The fraction of the curve.
 * @param iLimits
 * The limits to take into account.
 * @return
 * The global parameter associated with <tt>this</tt> CATCurve referenced by 
 * <tt>iLimits</tt>, of value 
 * <tt> iStartLimit + iLambda *(iEndLimit-iStartLimit)</tt>.
 */
#ifdef CATIACGMV5R22
  INLINE CATCrvParam(double  iLambda, const CATCrvLimits & iLimits);
#else
  CATCrvParam(double  iLambda, const CATCrvLimits & iLimits);
#endif

/**
 * Copy constructor.
 */
  CATCrvParam(const CATCrvParam & iCrvParamToCopy);

//=============================================================================
//- READING METHODS
//=============================================================================
/**
 * Returns the value of the CATCrvParam on <tt>this</tt> CATCurve.
 * @param 
 * The parameter value.
 */
  double GetParam () const;

/**
 * Returns the arc number of the CATCrvParam on <tt>this</tt> CATCurve.
 * @return
 * The arc number.
 */
  INLINE CATLONG32   GetArcNumber () const;

/**
 * Returns the local parameter value of the CATCrvParam on <tt>this</tt> CATCurve.
 * The local parameter.
 */
  INLINE double GetLocalParam () const;

//=============================================================================
//- SETTTING METHODS
//=============================================================================
/**
 * Modifies the value of a CATCrvParam.
 *<br>Performances will be better if you use the affectation operator =.
 *@param iGlobalParameter
 * The new value of the global parameter.
 */
  void SetParam (double iGlobalParmeter);

/**
 * Affects the data of another CATCrvParam.
 * @param iParamToCopy
 * The values to copy (parameter and reference).
 */
  void SetParam (const CATCrvParam & iParamToCopy);

/**
 * Affects the <tt>iP1 + iLambda (iP2-iP1)</tt> parameter.
 * *<br><tt>this</tt> CATCrvParam has the reference of <tt>iP1</tt>.
 * @param iLambda
 * The barycentric coefficient.
 * @param iP1
 * The first parameter.
 * @param iP2
 * The seond parameter.
 */
  void SetParam (double  iLambda, const CATCrvParam & iP1, const CATCrvParam & iP2);

/**
 * Affects the parameter of a fraction of a trimmed CATCurve.
 * <tt>this</tt> becomes the global parameter associated with the CATCurve referenced by 
 * <tt>iLimits</tt>, of value 
 * <tt> iStartLimit + iLambda *(iEndLimit-iStartLimit)</tt>.
 * @param iLambda 
 * The fraction of the curve.
 * @param iLimits
 * The limits to take into account.
 */
  void SetParam (double  iLambda, const CATCrvLimits & iLimits);

/**
 * Modifies the arc number of <tt>this</tt> CATCrvParam.
 *<br>The associated parameter remains the same.
 * @param
 * The new arc number. To have the beginning and end arc, use CATCurve::GetMaxLimits.
 */
#ifdef CATIACGMV5R22
  INLINE void SetArcNumber (CATLONG32  iNewArcNumber);
#else
  void SetArcNumber (CATLONG32  iNewArcNumber);
#endif

/**
 * Modifies the local parameter of <tt>this</tt> CATCrvParam.
 *<br>The associated arc number remains the same.
 * @param iLocalParam
 * The new value of the local parameter.
 */
#ifdef CATIACGMV5R22
  INLINE void SetLocalParam (double iLobalParam);
#else
  void SetLocalParam (double iLobalParam);
#endif

//=============================================================================
//- OVERLOADED OPERATORS TO COMPARE THE PARAMETERS
//=============================================================================
/**
 * Less-than or equal operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 <= iP2)<=>( (n1 < n2) or (n1 == n2 and p1 <= p2) </tt>
 */
  CATLONG32 operator <= (const CATCrvParam & iOtherParam) const;

/**
 * Less-than operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 < iP2)<=>( (n1 < n2) or (n1 == n2 and p1 < p2) </tt>
 */
  CATLONG32 operator <  (const CATCrvParam & iOtherParam) const;

/**
 * Greater-than or equal operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 >= iP2)<=>( (n1 > n2) or (n1 == n2 and p1 >= p2) </tt>
 */
  CATLONG32 operator >= (const CATCrvParam & iOtherParam) const;

/**
 * Greater-than operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 > iP2)<=>( (n1 > n2) or (n1 == n2 and p1 > p2) </tt>
 */
  CATLONG32 operator >  (const CATCrvParam & iOtherParam) const;

/**
 * Equality operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 == iP2)<=>( n1 == n2 and p1 == p2) </tt>
 */
  CATLONG32 operator == (const CATCrvParam & iOtherParam) const;

/**
 * Inequality operator.
 * <br>Let <tt>n=iP.GetArcNumber, p=iP.GetLocalParam<br>
 * (iP1 != iP2)<=>( n1 != n2 or  p1 != p2) </tt>
 */
  CATLONG32 operator != (const CATCrvParam & iOtherParam) const;

/**
 * Subtraction operator.
 * @return
 * The value of the difference of two global parameters.
 */
  double operator- (const CATCrvParam & iParamToSubstrct) const;

// Add a value to the global parameter
/**
 * Addition assignment operator.
 */
  void operator +=(double iGlobalParamToAdd);

/**
 * Moves a CATCrvParam with a CATMathTransformation1D.
 */
   CATCrvParam operator * (const CATMathTransformation1D &iTransfo1D) const;

//=============================================================================
// *****************    These methods will soon disappear    ******************
//=============================================================================

/**
 * @nodoc
 * Use CATCurve::CreateParam
 */
  CATCrvParam(double  iGlobalParameter, const   CATCrvParamReference * iReference);

/**
 * @nodoc
 * Use CATCurve::CreateParam
 */
  CATCrvParam(const CATParamData &iLocalParam, const CATCrvParamReference * iReference); 

/**
 * @nodoc
 * Use now CATCrvParam(double, const CATCrvParamReference *).
 */
  CATCrvParam(double iGlobalParameter,  const CATCrvParam & iReferenceParameter);

  // Same, with a local parameter definition.
/**
 * @nodoc
 * Use now CATCrvParam(CATParamData &, CATCrvParamReference *).
 */
  CATCrvParam(CATLONG32 iArcNumber, const double & iLocalParameter, const CATCrvParam & iReference);

/**
 * @nodoc 
 */
  CATCrvParam(); 
  
/**
 * @nodoc
 * Returns the reference to the CATCurve with which the CATCrvParam
 * is associated.
 * @return
 * A pointer to the curve reference.
 */
  INLINE const CATCrvParamReference * GetReference() const;


/**
 * @nodoc
 * Use CATCurve::CreateParam
 */
  void SetParam(double iGlobalParmeter, const CATCrvParamReference * iReference);


  /**
 * @nodoc
 * Use CATCurve::CreateParam
 */
 INLINE void SetParam(const CATParamData & iLocalParameter, const CATCrvParamReference * iReference);


/** @nodoc */
  INLINE void SetReference(const CATCrvParamReference * iReference);

/**
 * @nodoc
 * Use now GetReference.
 */
  void * GetCurve() const;

//=============================================================================
// FRIENDS
//=============================================================================
/**
 * @nodoc
 * Dumps a CATCrvParam.
 */
  friend ExportedByCATCGMGeoMath ostream& operator << (ostream& iS,
						const CATCrvParam & iParam);
/** @nodoc */
friend class CATCrvLimits;
/** @nodoc */
friend class CATSetOfCrvParams;

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:

  /** @nodoc */ 
  double  _PositionLocalParam;
  /** @nodoc */ 
  CATLONG32    _PositionLocalNumber;
  /** @nodoc */
  const CATCrvParamReference *_Reference;

// Constructor to build the object from all its datas, for inherited objects
  /** @nodoc */
  INLINE CATCrvParam(const CATParamData & iPosition, void * iImplementation, const CATCrvParamReference * iReference);

  /** @nodoc */
  CATCrvParam(const CATCrvParamReference * iReference, CATLONG32 iArcNumber, const double & iLocalParameter);
};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATCrvParam::GetArcNumber () const
{
  return _PositionLocalNumber;
}

INLINE double CATCrvParam::GetLocalParam () const
{
  return _PositionLocalParam;
}

INLINE CATCrvParam::CATCrvParam(const CATParamData & iPosition,
				void               * iImplementation,
				const CATCrvParamReference * iReference)
{
  _PositionLocalParam  = iPosition.LocalParam;
  _PositionLocalNumber = iPosition.PartNumber;
  _Reference           = iReference;
}

INLINE const CATCrvParamReference * CATCrvParam::GetReference() const
{
  return _Reference;
}

INLINE void CATCrvParam::SetParam(const CATParamData & iPosition,  const CATCrvParamReference * Reference)
{
  _Reference           = Reference;
  _PositionLocalParam  = iPosition.LocalParam;
  _PositionLocalNumber = iPosition.PartNumber;
}


INLINE void CATCrvParam::SetReference(const CATCrvParamReference *Reference)
{
  _Reference = Reference;
}

#ifdef CATIACGMV5R22
INLINE CATCrvParam::CATCrvParam( double lambda, const CATCrvParam & P1, const CATCrvParam & P2)
{
  SetParam(lambda, P1, P2);
}

INLINE CATCrvParam::CATCrvParam(double lambda, const CATCrvLimits & Box)
{
  SetParam(lambda, Box);
}

INLINE void CATCrvParam::SetArcNumber (CATLONG32  Arc)
{
  _PositionLocalNumber = Arc;
}

INLINE void CATCrvParam::SetLocalParam (double Param)
{
  _PositionLocalParam = Param;
}
#endif

#endif
