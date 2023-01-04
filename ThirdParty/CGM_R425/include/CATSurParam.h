#ifndef CATSURPARAM_H
#define CATSURPARAM_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16

#include "ExportedByCATCGMGeoMath.h"
#include "CATMathInline.h"

#include "CATParamData.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATMathVector2D;
class CATMathPoint2D;
class CATSurLimits;
class CATSurParamReference;
class CATMathTransformation2D;

/**
 * Class representing the global parameter of a point on a CATSurface.
 *<br> The parameter of a point on a surface is
 * defined by two values, one in each direction of the surface: each value is the value of the isoparametric
 * curve along a surface direction passing through the point.
 * The global parameter value in one direction corresponds to a local parameter and a patch
 * number in this direction.
 * The local parameters are managed by the geometrical
 * elements.
 *<br>Note that you also can create CATSurParams by using the
 *<tt>CreateParam</tt> method of the <tt>CATSurface</tt> interface.
 * @see CATSurface
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSurParam
/*
#else
class ExportedByYP00IMPL CATSurParam
#endif  
*/
{
 public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//=============================================================================
//- CONSTRUCTORS
//=============================================================================
/**
 * Default constructor.
 *<br>Avoids this as much as possible, because no CATSurface is related to.
 */
  CATSurParam ();

//
//    (0, 1)   (0.5, 1)     P2
//      *---------*---------*
//      |                   |
//      |                   |
//      |                   |
//    (0, 0.5)              |
//      |                   |
//      |                   |
//      |                   |
//      P1------------------(1, 0)

/**
 * Constructs the CATSurParam whose U (resp. V) coordinate is the barycenter of 
 * the U (resp. V) coordinate of two CATSurParams.
 *<br>This allows you to reach each parameter of the rectangle defined by to points.
 * @param iLamdaU
 * The weigth used on the first U direction.
 * @param iLamdaV
 * The weigth used on the second V direction.
 * @param iP1
 * The fisrt CATSurParam <tt>(iP1(U),iP1(V))</tt>.
 * @param iP2
 * The second CATSurParam <tt>(iP2(U),iP2(V))</tt>.
 * @return
 * The CATSurParam of parameter 
 *<br>
 *<tt>((1-iLambdaU)*iP1(U) + iLambdaU*iP2(U),(1-iLambdaV)*iP1(V) + iLambdaV*iP2(V)) 
 *</tt>
 */
#ifdef CATIACGMV5R23
  INLINE CATSurParam (double iLambdaU, double iLambdaV, 
	       const CATSurParam & iP1, const CATSurParam & iP2);
#else
  CATSurParam (double iLambdaU, double iLambdaV,
	       const CATSurParam & iP1, const CATSurParam & iP2);
#endif

/**
 * Constructs the CATSurParam whose U (resp. V) coordinate is the barycenter of 
 * the U (resp. V) coordinate of the limits of a CATSurLimits.
 *<br>Check before that the CATSurLimits is not empty.
 *<br>This allows you to reach each parameter of the rectangle defined by to points.
 * @param iLamdaU
 * The weigth used on the first U direction.
 * @param iLamdaV
 * The weigth used on the second V direction.
 * @param iBoxUV
 * The limits of parameters <tt>{(iP1(U),iP1(V)),(iP2(U),iP2(V))}</tt>.
 * @return
 * The CATSurParam of parameters 
 *<br>
 *<tt>((1-iLambdaU)*iP1(U) + iLambdaU*iP2(U),(1-iLambdaV)*iP1(V) + iLambdaV*iP2(V)) 
 *</tt>
 */

#ifdef CATIACGMV5R23
  INLINE CATSurParam (double iLambdaU, double iLambdaV,
	       const CATSurLimits & iBoxUV);
#else
  CATSurParam (double iLambdaU, double iLambdaV,
	       const CATSurLimits & iBoxUV);
#endif

/**
 * Copy constructor.
 */
  CATSurParam (const CATSurParam & iSurParamToCopy);


//=============================================================================
//- READING METHODS
//=============================================================================
/**
 * Returns the global parameter in the first direction of <tt>this</tt> CATSurParam. 
 * @return
 * The parameter value.
 */
  double GetParamU () const;

/**
 * Returns the global parameter in the second direction of <tt>this</tt> CATSurParam.
 * @return
 * The parameter value.
 */
  double GetParamV () const;

/**
 * Returns the global parameter in each direction of <tt>this</tt> CATSurParam. 
 * @param ioGlobalParamU
 * The parameter value in the first direction.
 * @param ioGlobalParamV
 * The parameter value in the second direction.
 */
  void GetParams (double & ioGlobalParamU, double & ioGlobalParamV) const;

/**
 * Returns the patch number in the first direction of <tt>this</tt> CATSurParam.
 * @return
 * The patch number.
 */
  INLINE CATLONG32   GetPatchNumberU () const;

/**
 * Returns the patch number in the second direction of <tt>this</tt> CATSurParam.
 * @return
 * The patch number.
 */
  INLINE CATLONG32   GetPatchNumberV () const;

/**
 * Returns the local parameter in the first direction of <tt>this</tt> CATSurParam.
 * @return
 * The parameter value.
 */
  INLINE double GetLocalParamU () const;

/**
 * Returns the local parameter in the second direction of <tt>this</tt> CATSurParam. 
 * @return
 * The parameter value.
 */
  INLINE double GetLocalParamV () const;

//=============================================================================
//- SETTTING METHODS
//=============================================================================
/**
 * Modifies the global parameter in the first direction of <tt>this</tt> CATSurParam.
 * @param iGlobalParamU
 * The new parameter value.
 */
  void SetParamU (double iGlobalParamU);

/**
 * Modifies the global parameter in the second direction of <tt>this</tt> CATSurParam.
 * @param iGlobalParamU
 * The new parameter value.
 */
  void SetParamV (double iGlobalParamV);

/**
 * Affects a CATSurParam.
 * @param iCopiedSurParam
 * The surface parameter to copy.
 */
  void SetParam(const CATSurParam & iCopiedSurParam);

/**
 * Modifies <tt>this</tt> CATSurParam with a barycentric method on two CATSurParams.
 *<br>This allows to reach each parameter of the rectangle defined by to points. 
 * <tt>this</tt> becomes the following parameter:
 *<br>
 *<tt>((1-iLambdaU)*iP1(U) + iLambdaU*iP2(U),(1-iLambdaV)*iP1(V) + iLambdaV*iP2(V)) 
 *</tt>
 * @param iLamdaU
 * The weigth used on the first U direction.
 * @param iLamdaV
 * The weigth used on the second V direction.
 * @param iP1
 * The fisrt CATSurParam <tt>(iP1(U),iP1(V))</tt>.
 * @param iP2
 * The second CATSurParam <tt>(iP2(U),iP2(V))</tt>.
 */
  void SetParam(double      iLambdaU,
		double              iLambdaV,
		const CATSurParam & iP1,
		const CATSurParam & iP2);

/**
 * Modifies <tt>this</tt> CATSurParam with a barycentric method on a CATSurLimits.
 *<br>Check before that the CATSurLimits is not empty.
 *<br>This allows to reach each parameter of the rectangle defined by to points.
 * <tt>this</tt> becomes the following parameter: 
 *<br>
 *<tt>((1-iLambdaU)*iP1(U) + iLambdaU*iP2(U),(1-iLambdaV)*iP1(V) + iLambdaV*iP2(V)) 
 *</tt>
 * @param iLamdaU
 * The weigth used on the first U direction.
 * @param iLamdaV
 * The weigth used on the second V direction.
 * @param iBoxUV
 * The limits of parameters <tt>{(iP1(U),iP1(V)),(iP2(U),iP2(V))}</tt>.
 */
  void SetParam(double iLambdaU, double iLambdaV,
		const CATSurLimits & iBoxUV);

/**
 * Modifies the global parameters.
 * @param iGlobalParameterU
 * The new value of the parameter in the first direction of the surface.
 * @param iGlobalParameterV
 * The new value of the parameter in the second direction of the surface.
 */
  void SetParam(double iGlobalParameterU,
		double iGlobalParameterV);

/**
 * Modifies the patch number in the first direction of <tt>this</tt> CATSurParam.
 * @param iPatchNumberU
 * The new patch number.
 */
  INLINE void SetPatchNumberU (CATLONG32 iPatchNumberU);

/**
 * Modifies the patch number in the second direction of <tt>this</tt> CATSurParam.
 * @param iPatchNumberV
 * The new patch number.
 */
  INLINE void SetPatchNumberV (CATLONG32 iPatchNumberV);

/**
 * Modifies the local parameter in the first direction of <tt>this</tt> CATSurParam.
 * @param iPatchNumberU
 * The new parameter value.
 */
  INLINE void SetLocalParamU (double iLocalParamU);

/**
 * Modifies the local parameter in the second direction of <tt>this</tt> CATSurParam.
 * @param iPatchNumberV
 * The new parameter value.
 */
  INLINE void SetLocalParamV (double iLocalParamV);

//=============================================================================
// METHODS THAT RETURN A VALUE
//=============================================================================
/**
 * Returns the square distance to another CATSurParam.
 * @param iOtherParam
 * The other parameter.
 */
  double SquareDistanceTo (const CATSurParam & iOtherParam) const;

/**
 * Returns the distance to another CATSurParam.
 * @param iOtherParam
 * The other parameter.
 */
  double DistanceTo (const CATSurParam & iOtherParam) const;

//=============================================================================  
// OVERLOADED OPERATORS
//=============================================================================
/**
 * Equality operator.
 * <br>Let <tt>nu=iP.GetPatchNumberU, pu=iP.GetLocalParamU<br>
 * nv=iP.GetPatchNumberV, pv=iP.GetLocalParamV<br>
 * (iP1 == iP2)<=>( nu1 == nu2 and pu1 == pu2 and nv1 == nv2 and pv1 == pv2) </tt>
 */
  CATLONG32 operator == (const CATSurParam &iSurParamToCompare) const;

/**
 * Inequality operator.
 * <br>Let <tt>nu=iP.GetPatchNumberU, pu=iP.GetLocalParamU<br>
 * nv=iP.GetPatchNumberV, pv=iP.GetLocalParamV<br>
 * (iP1 != iP2)<=>( nu1 != nu2 or pu1 != pu2 or nv1 != nv2 or pv1 != pv2) </tt>
 */
  CATLONG32 operator != (const CATSurParam &iSurParamToCompare) const;

/**
 * Subtraction operator.
 * @return
 * The CATSurParam whose global parameters are the difference of the
 * corresponding global parameters of the two CATSurParams and whose surface
 * reference is the first CATSurParam one.
 */
  CATMathVector2D operator - (const CATSurParam & iOtherParam) const;
  
/**
 * Addition operator.
 * @return
 * The CATSurParam whose global parameters are the sum of the
 * corresponding global parameters of the CATSurParam and the CATMathVector2D
 * and whose surface
 * reference is the CATSurParam one.
 */
  CATSurParam operator + (const CATMathVector2D & iGlobalVector) const;

/**
 * Addition assignment operator.
 */
  void operator += (const CATMathVector2D & iGlobalVector);

/**
 * Move a CATSurParam with a CATMathTransformation2D.
 */
  CATSurParam operator * (const CATMathTransformation2D &iTransfo2D) const;



  








  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Use @href CATSurface#CreateParam.
 * Constructs a CATSurParam from the global parameters U and V, and a
 * reference.
 */
  CATSurParam (double iGlobalParamU,
	       double iGlobalParamV,
	       const CATSurParamReference * iReference);

/**
 * @nodoc
 * Use @href CATSurface#CreateParam.
 * Constructs a CATSurParam from a 2D point, whose coordinates are the 
 * parameters values, and a reference.
 */
  CATSurParam (const CATMathPoint2D & iPointUV,
	       const CATSurParamReference * iReference);

/**
 * @nodoc
 * Use @href CATSurface#CreateParam.
 * Constructs a CATSurParam from local parameters and a reference.
 */ 
  CATSurParam (const CATParamData & iPositionU,
	       const CATParamData & iPositionV,
	       const CATSurParamReference * iReference);

/**
 * @nodoc
 * Constructs a CATSurParam from local parameters and a reference.
 * Use @href CATSurface#CreateParam.
 */ 
  CATSurParam(const CATLONG32 iPatchNumberU, const double iLocalParamU,
              const CATLONG32 iPatchNumberV, const double iLocalParamV,
		      const CATSurParamReference * iReference);

//=============================================================================
// REFERENCE MANAGEMENT
//=============================================================================
/**
 * @nodoc
 * Returns a pointer to the reference of a CATSurParam.
 * @return
 * The constant pointer to the surface on which <tt>this</tt> is defined. To be used to compare
 * the surfaces on which parameters are defined.
 */
  INLINE const CATSurParamReference * GetReference() const;

/**
 * @nodoc
 * Changes the reference of a CATSurParam.
 */
  INLINE void SetReference(const CATSurParamReference * iReference);


/**
 * @nodoc
 * Modifies the global parameters and the reference of <tt>this</tt> CATSurParam.
 */
  void SetParam(double iGlobalParameterU,
		double iGlobalParameterV,
		const CATSurParamReference * iReference);

/**
 * @nodoc
 * Modifies <tt>this</tt> CATSurParam with local parameters and a reference.
 */
  void SetParam(const CATParamData & iPositionU,
		const CATParamData & iPositionV,
		const CATSurParamReference * iReference);

/**
 * @nodoc
 * Modifies <tt>this</tt> CATSurParam with local parameters and a reference.
 */
  INLINE void SetParam(const CATLONG32 iPatchNumberU, const double iLocalParamU,
                       const CATLONG32 iPatchNumberV, const double iLocalParamV,
		               const CATSurParamReference * iReference);





//=============================================================================
// FRIENDS
//=============================================================================
// Streaming method for debug
/** @nodoc  */
//#if defined ( CATIAV5R10 )
friend ExportedByCATCGMGeoMath ostream& operator << (ostream& s,
						const CATSurParam & P);
/*
#else
friend ExportedByYP00IMPL ostream& operator << (ostream& s,
						const CATSurParam & P);
#endif  
*/
/** @nodoc */
friend class CATSurLimits;
/** @nodoc */
friend class CATSetOfSurParams;

//------------------------------------------------------------
// ************* These methods will disappear ****************
//------------------------------------------------------------
/**
 * @nodoc
 * Use now @href CATSurface#CreateParam.
 */
  CATSurParam (double              iGlobalParamU,
	       double              iGlobalParamV,
	       const CATSurParam & iReference);

/**
 * @nodoc
 * Use now @href CATSurface#CreateParam.
 */
  CATSurParam (CATLONG32                iPatchNumberU,
	       const double      & iLocalParamU,
	       CATLONG32                iPatchNumberV,
	       const double      & iLocalParamV,
	       const CATSurParam & iReference);


protected:
//=============================================================================
// INTERNAL DATAS
//=============================================================================

// Position in u and v
  /** @nodoc */ 
  double  _U_param,  _V_param;
  /** @nodoc */ 
  CATLONG32    _U_number, _V_number;
  /** @nodoc */

// Pointer on the objects that manages the conversion Global-Local parameters
  /** @nodoc */
  const CATSurParamReference *_Reference;

/** @nodoc */
  CATSurParam(const CATParamData & iPositionU,
	      const CATParamData & iPositionV,
	      void               * iImplementation,
	      const CATSurParamReference * iReference);

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATLONG32 CATSurParam::GetPatchNumberU () const
{
  return _U_number;
}

INLINE CATLONG32 CATSurParam::GetPatchNumberV () const
{
  return _V_number;
}

INLINE double CATSurParam::GetLocalParamU () const
{
  return _U_param;
}

INLINE double CATSurParam::GetLocalParamV () const
{
  return _V_param;
}

INLINE void CATSurParam::SetParam( const CATLONG32 iPatchNumberU, const double iLocalParamU,
                                   const CATLONG32 iPatchNumberV, const double iLocalParamV,
		                           const CATSurParamReference * iReference)
{
  _U_param   = iLocalParamU;
  _U_number  = iPatchNumberU;
  _V_param   = iLocalParamV;
  _V_number  = iPatchNumberV;
  _Reference = iReference   ;
}

INLINE void CATSurParam::SetPatchNumberU (CATLONG32 iPatchNumberU)
{
  _U_number  = iPatchNumberU;
}

INLINE void CATSurParam::SetPatchNumberV (CATLONG32 iPatchNumberV)
{
  _V_number  = iPatchNumberV;
}

INLINE void CATSurParam::SetLocalParamU(double iLocalParamU)
{
  _U_param   = iLocalParamU;
}

INLINE void CATSurParam::SetLocalParamV(double iLocalParamV)
{
  _V_param   = iLocalParamV;
}

INLINE CATSurParam::CATSurParam(const CATParamData & iPositionU,
				const CATParamData & iPositionV,
				void               * iImplementation,
				const CATSurParamReference * iReference)
{
  _U_param   = iPositionU.LocalParam;
  _U_number  = iPositionU.PartNumber;
  _V_param   = iPositionV.LocalParam;
  _V_number  = iPositionV.PartNumber;
  _Reference      =iReference;
}

#ifdef CATIACGMV5R23
INLINE CATSurParam::CATSurParam (double lambdaU, double lambdaV,
                          const CATSurParam & SurParam1, const CATSurParam & SurParam2)
{
  SetParam(lambdaU, lambdaV, SurParam1, SurParam2);
}

INLINE CATSurParam::CATSurParam (double lambdaU, double lambdaV, const CATSurLimits & UVBox)
{
  SetParam(lambdaU, lambdaV, UVBox);
}
#endif

INLINE const CATSurParamReference * CATSurParam::GetReference() const
{
  return _Reference;
}

INLINE void CATSurParam::SetReference(const CATSurParamReference * Reference)
{
  _Reference= Reference;
}

#endif
