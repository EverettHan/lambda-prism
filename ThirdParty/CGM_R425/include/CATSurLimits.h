#ifndef CATSURLIMITS_H
#define CATSURLIMITS_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATMathDef.h"
#include "CATParamData.h"
#include "CATSurParam.h"
#include "CATIsoParameter.h"
#include "CATVerificationMode.h"
#include "CATMathInline.h"

class CATSurParamReference;
class CATCrvLimits;
class CATCrvParam;
class CATMathBox2D;
class CATMathPoint2D;
class CATMathTransformation2D;
class CATCGMStreamImpl;

/**
 * Class representing the limitations of a CATSurface.
 *<br>The CATSurLimits contains the two CATSurParams of the limiting points.
 *<br>The CATSurLimits defines a closed interval of R&sup2;.
 * It can be empty (if
 * the high limit is smaller than the low one, or if some of them 
 * are not defined): in this case, it does not contain any point.
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSurLimits
/*
#else
class ExportedByYP00IMPL CATSurLimits
#endif  
*/
{
public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//======================================================================
//  CONSTRUCTORS AND DESTRUCTOR
//======================================================================
/**
 * Constructs an empty CATSurLimits.
 * <br>Do not use it.
 */
  CATSurLimits ();

/**
 * Constructs a CATSurLimits from two CATSurParams.
 * @param iLowSurParam
 * The first limitation.
 * @param iHighSurParam
 * The last limitation.
 * @param iMode
 * Only use with the default mode.
 */
  CATSurLimits (const CATSurParam & iLowSurParam,
		const CATSurParam & iHighSurParam,
		CATVerificationMode iMode=CATVerify);

/**
 * Copy constructor.
 */
  CATSurLimits (const CATSurLimits & iSurLimitsToCopy);
//======================================================================
// SET AND GET THE EXTREMITIES
//======================================================================
/**
 * Sets <tt>this</tt> CATSurLimits to an empty one.
 */
  INLINE void SetToEmpty();

/**
 * Tests whether <tt>this</tt> CATCrvLimits is empty.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if it is not empty.
 *     <dt><tt>1</tt>  <dd> if it is empty.
 * </dl>
 */
  INLINE CATLONG32 IsEmpty() const;

/**
 * Modifies the low CATSurParam of <tt>this</tt> CATCrvLimits.
 *<br>Check before that <tt>iLowParam</tt> is lower than <tt>iHighParam</tt>.
 * @param iLowParam
 * The new low limit.
 */ 
  void SetLow (const CATSurParam & iLowParam);

/**
 * Modifies the high CATSurParam of <tt>this</tt> CATCrvLimits.
 *<br>Check before that <tt>iHighParam</tt> is higher than <tt>iLowParam</tt>.
 * @param iLowParam
 * The new last limit.
 */ 
  void SetHigh(const CATSurParam & iHighParam);
/**
 * Retrieves the CATSurParams that delimit <tt>this</tt> CATSurLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param ioLowParam
 * The first limit.
 * @param ioHighParam
 * The last limit.
 */
  void GetExtremities(CATSurParam & ioLowParam, CATSurParam & ioHighParam) const;

/**
 * Retrieves the low CATSurParam of <tt>this</tt> CATSurLimits.
 *<br>Check before that the CATSurLimits is not empty.
 * @param ioLowParam
 * The first limit.
 */
  void GetLow (CATSurParam & ioLowParam) const;

/**
 * Retrieves the high CATSurParam of <tt>this</tt> CATSurLimits.
 *<br>Check before that the CATSurLimits is not empty.
 * @param ioHighParam
 * The last limit.
 */
  void GetHigh(CATSurParam & ioHighParam) const;

/**
 * Computes a 2D box corresponding to the global parameters of <tt>this</tt>
 * CATSurLimits. 
 * @param ioGlobalBox
 * The corresponding 2D box.
 * The result is empty if the CATSurLimits is empty.
 */
  void Get2DBox(CATMathBox2D & ioGlobalBox) const;

/**
 * Retrieves the extremities of a 2D box corresponding to the global parameters of <tt>this</tt>
 * CATSurLimits. <br>Check before that the CATSurLimits is not empty.
 * @param ioUmin
 * The low limit in the first direction.
 * @param ioVmin
 * The low limit in the second direction.
 * @param ioUmax
 * The last limit in the first direction.
 * @param ioVmax
 * The last limit in the second direction.
 */
  void GetExtremities(double &ioUmin, double &ioVmin, double &ioUmax, double &ioVmax) const;

	/**
	 * Retrieves the center of <tt>this</tt> CATSurLimits. 
	 * @param ioUmiddle
	 * The parameter of the center in the first direction.
	 * @param ioVmiddle
	 * The parameter of the center in the second direction.
	 */
  void GetMiddle(double &ioUmiddle, double &ioVmiddle) const;

/** 
  *    Retrieves the extremities of a 2D box corresponding to the local parameters of <tt>this</tt>
  * CATSurLimits. <br> Check before that the CATSurLimits is not empty.
	* @param ioLocalUmin
	* The local parameter value in the first direction of the first limit.
	* @param ioLocalVmin
	* The local parameter value in the second direction of the first limit.
	* @param ioLocalUmax
	* The local parameter value in the first direction of the last limit.
	* @param ioLocalVmax
	* The local parameter value in the second direction of the last limit.
	*	@param ioUMinPartNumber
	* The patch number in the first direction of the first limit.
	* @param ioVMinPartNumber
	* The patch number in the second direction of the first limit.
	* @param ioUMaxPartNumber
	* The patch number in the first direction of the last limit.
	* @param ioVMaxPartNumber
	* The patch number in the second direction of the last limit. 
  */
  void GetLocalExtremities(double &ioLocalUmin     , double &ioLocalVmin     , 
			   double &ioLocalUmax     , double &ioLocalVmax     , 
			   CATLONG32   &ioUMinPartNumber, CATLONG32   &ioVMinPartNumber, 
			   CATLONG32   &ioUMaxPartNumber, CATLONG32   &ioVMaxPartNumber) const;

//=====================================================================
// COMPUTATIONS THAT MODIFIES THE BOX
//======================================================================
/**
 * Replaces <tt>this</tt> CATSurLimits by the intersection of two other ones.
 *<br>The result may be an empty CATSurLimits.
 * @param iBox1
 * The first CATSurLimits to intersect.
 * @param iBox2
 * The second CATSurLimits to intersect.
 */
  void SetToIntersection(const CATSurLimits &iBox1, const CATSurLimits &iBox2);

/**
 * Replaces <tt>this</tt> CATSurLimits by the union of two other one.
 * <br><tt>this</tt> becomes
 * the CATSurLimits of low limit the lowest limit of the two CATSurlimits and
 * of high limit the highest limit, even the two CATSurLimits are not 
 * intersecting each other.
 * @param iBox1
 * The first CATSurLimits to union.
 * @param iBox2
 * The second CATSurLimits to union.
 */
  void SetToUnion(const CATSurLimits &iBox1, const CATSurLimits &iBox2);

/**
 * Replaces <tt>this</tt> by a CATSurLimits that also contains a given CATSurParam.
 * @param iPointOnSurface
 * The point that must be contained by <tt>this</tt>.
 */
  void AddInside(const CATSurParam &iPointOnSurface);

/**
 * Replaces <tt>this</tt> by the union with an other CATSurLimits.
 * @param iOtherBox
 * The box to union with <tt>this</tt>.
 */
  void AddInside(const CATSurLimits &iOtherBox); 

/**
 * Replaces <tt>this</tt> by a CATCrvLimits that also contains a given CATMathPoint2D.
 * @param iPointOnSurface
 * The point that must be contained by <tt>this</tt>.
 */
  void AddInside(const CATMathPoint2D & iPointUV);

//======================================================================
// COMPUTATION WITH A BOX THAT RETURNS A RESULT
//======================================================================
/**
 * Tests whether <tt>this</tt> CATSurLimits is intersecting another one.
 * @param iBoxToCompare
 * The box to compare.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if there is no intersection.
 *     <dt><tt>1</tt>  <dd> if there is an intersection (this is also the case
 * when there is just a point or a line in common).
 * </dl>
 */
  CATLONG32 IsIntersecting(const CATSurLimits &iBoxToCompare) const;

	/**
 * Tests whether <tt>this</tt> CATSurLimits is intersecting another one at a given tolerance.
 * @param iBoxToCompare
 * The box to compare.
 * @param iTol
 * The tolerance to take into account.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if there is no intersection.
 *     <dt><tt>1</tt>  <dd> if there is an intersection (this is also the case
 * when there is just a point or a line in common).
 * </dl>
 */
  CATLONG32 IsIntersecting(const CATSurLimits &iBoxToCompare, double iTol) const;
/**
 * Tests wether <tt>this</tt> CATSurParam is inside a CATSurLimits.
 * @param iPointToCompare
 * The point to test.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATSurLimits does not contain the 
 * CATCrvParam.
 *     <dt><tt>1</tt>  <dd> if the CATSurLimits contains the CATSurParam.
 * </dl>
 */
  CATLONG32 IsContaining(const CATSurParam &iPointToCompare) const;

/**
 * Tests wether <tt>this</tt> CATSurParam is inside a CATSurLimits at a given tolerance.
 * @param iPointToCompare
 * The point to test.
 * @param iTol
 * The tolerance to take into account.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATSurLimits does not contain the 
 * CATCrvParam.
 *     <dt><tt>1</tt>  <dd> if the CATSurLimits contains the CATSurParam.
 * </dl>
 */
  CATLONG32 IsContaining(const CATSurParam &iPointToCompare, double iTol) const;

/**
 * Tests whether <tt>this</tt> CATSurLimits is including another CATSurLimits.
 * @param iOtherBox
 * The box to test.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATSurLimits is not containing 
 * <tt>iOtherBox</tt>.
 *     <dt><tt>1</tt>  <dd> if the CATSurLimits is containing
 * <tt>iOtherBox</tt>.
 *</dl>
 */
  CATLONG32 IsContaining(const CATSurLimits &iOtherBox) const;

	/**
 * Tests whether <tt>this</tt> CATSurLimits is including another CATSurLimits at a given tolerance.
 * @param iOtherBox
 * The box to test.
 * @param iTol
 * The tolerance to take into account.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATSurLimits is not containing 
 * <tt>iOtherBox</tt>.
 *     <dt><tt>1</tt>  <dd> if the CATSurLimits is containing
 * <tt>iOtherBox</tt>.
 *</dl>
 */
  CATLONG32 IsContaining(const CATSurLimits &iOtherBox, double iTol) const;

  //---------------------------------------------------------------
  // Tests if T(iBox) is included in this and calculate the 
  // new Transfo2D if necessary
  // PeriodX = 0 if not periodic in the X direction
  //---------------------------------------------------------------
/**
 * Tests whether the transformation of a CATSurLimits belongs to <tt>this</tt>.
 * @param iBox
 * The box which transformation is tested.
 * @param ioTransfo2D
 * The transformation to apply to <tt>iBox</tt>. In case of the transformed box belongs
 * to <tt>this</tt>, and in case
 * of a periodicity in one direction, the minimal corresponding transformation is returned.
 * @param iPeriodU
 * The periodicity in the first direction.
 * <br><b>Legal values</b>:
 * <dl><dt>1</dt><dd> The surface is periodic in the first direction.
 * <dt>0</dt><dd>Otherwise.
 * </dl>
 * @param iPeriodV
 * The periodicity in the second direction.
 * <br><b>Legal values</b>:
 * <dl><dt>1</dt><dd> The surface is periodic in the second direction.
 * <dt>0</dt><dd>Otherwise.
 * </dl>
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>1</tt>  <dd> if <tt>ioTranfo2D(iBox)</tt> belongs to <tt>this</tt>.
 *     <dt><tt>0</tt>  <dd> otherwise.
 *</dl> 
 */
  CATLONG32 IsContaining(const CATSurLimits            & iBox,
		          CATMathTransformation2D & ioTransfo2D,
		          double                    iPeriodU = 0,
		          double                    iPeriodV = 0,
		          double                    iTol = 0    ) const;

/**
 * Retrieves the CATSurParam of the point that has the same relative position to <tt>this</tt>
 * than RefPoint in RefBox.
 * @param iRefAll
 * The reference CATSurLimits of global parameters <tt>((A1u,A1v),(A2u,A2v))</tt>.
 * @param iRefPoint
 * The compared CATSurParam of global parameters <tt>(Bu,Bv)</tt>.
 * @param ioResult
 * The resulting CATSurParam of global parameter <tt>(Ru,Rv)</tt> 
 *  following the equation (with <tt>((T1u,T1v),(T2u,T2v))</tt> the global
 * parameters of <tt>this</tt>):
 *<tt>(Ru-Tu)*(A2u-A1u) = (Bu-A1u)*(T2u-T1u) </tt> 
 * <br><tt>(Rv-Tv)*(A2v-A1v) = (Bv-A1v)*(T2v-T1v) </tt>
 */
  void GetEquivalentParam(const CATSurLimits & iRefBox,
                          const CATSurParam  & iRefPoint,
	                        CATSurParam  & ioResult) const; 

/**  
 * Retrieves the CATSurParam of the point that has the same relative position to <tt>this</tt>
 * than RefPoint in RefCrvLimits along an isoparametric curve.
 *<br>The isoparametric curve is in the <tt>iIsoParameter</tt> direction
 * passing through <tt>iIsoParamUV</tt>.
 * @param iRefCrvLimits
 * The reference CATCrvLimits of global parameters <tt>(A1,A2)</tt>.
 * @param iRefPoint
 * The compared CATCrvParam of global parameters <tt>(B)</tt> on the the iso-parametric curve defined by
 * <tt>iIsoParamUV</tt> and <tt>iIsoParameter</tt>.
 * @param iIsoParameter
 * The type of isoparametric curve.
 * @param iIsoParamUV
 * The point belonging to the iso parametric curve.
 * @param ioResult
 * The resulting CATSurParam of global parameter  
 * such that (with <tt>(T1,T2)</tt> the global
 * parameters of <tt>this</tt>):
 *<dl> <dt> if <tt>iIsoParameter=CATIsoParamU</tt></dt><dd>
 *<tt> (iIsoParamUV(U),  T1v + (T2v-T1v)*(B-A1)/(A2-A1))</tt> 
 * <dt> if <tt>iIsoParameter=CATIsoParamV</tt></dt><dd>
 *<tt> ( T1u + (T2u-T1u)*(B-A1)/(A2-A1),   iIsoParamUV(V) )</tt> 
 *</dl>
 */
  void GetEquivalentParam(const CATCrvLimits    & iRefCrvLimits,
			  const CATCrvParam     & iRefPoint,
			  const CATIsoParameter   iIsoParameter,
			  const CATSurParam     & iIsoParamUV,     
			        CATSurParam     & ioResult       ) const; 
  
/**  
 * Tests whether two CATSurLimits are equal (logically, no tolerance) with regards to the first coordinate.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt></dt> <dd>The first coodinates are logically equal.
 * <dt><tt>FALSE</tt></dt> <dd>Otherwise.
 * </dl>
 */
  CATBoolean IsEqualU(const CATSurLimits & iComparedBox) const ;

/**  
 * Tests whether two CATSurLimits are equal (logically, no tolerance) with regards to second coordinate.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>TRUE</tt></dt> <dd>The second coodinates are logically equal.
 * <dt><tt>FALSE</tt></dt> <dd>Otherwise.
 * </dl>
 */
  CATBoolean IsEqualV(const CATSurLimits & iComparedBox) const ;

  /**
	 * Applies a 2D transformation to <tt>this</tt> CATSurLimits.
	 * @param iTransfo2D
	 * The transformation to apply.
	 * @param ioLimits
	 * The resulting limits.
	 */
  void ApplyTransformation2D(const CATMathTransformation2D &iTransfo2D,
			           CATSurLimits            &ioLimits   ) const;

//=============================================================================
// OVERLOADED OPERATORS
//=============================================================================
/**
 * Equality operator.
 * <br><pre>( Lim1 == Lim2 ) <=> (Lim1.GetLow == Lim2GetLow) and
 *                          (Lim1.GetHigh == Lim2.GetHigh) 
 *                         </pre>
 */
  CATLONG32 operator == (const CATSurLimits & iComparedBox) const;

/**
 * Inequality operator.
 * <br><pre>( Lim1 != Lim2 ) <=> (Lim1.GetLow != Lim2GetLow) or
 *                          (Lim1.GetHigh != Lim2.GetHigh)
 *                          </pre>
 */
  CATLONG32 operator != (const CATSurLimits & iComparedBox) const;

  








  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * @nodoc
 * Constructs a CATSurLimits from the extremities on each direction.
 *<br>If the last argument is set to <tt>DontVerify</tt>,
 * the two CATSurParams are assumed to be the low one and the high one,
 * else it creates the smallest CATSurLimits that contains the two 
 * CATSurParams.
 * @param iMode
 * Only use with the default mode.
 */
  CATSurLimits (const CATParamData & iLowU,
		const CATParamData & iLowV,
		const CATParamData & iHighU,
		const CATParamData & iHighV,
		const CATSurParamReference *iReference,
		CATVerificationMode iMode=CATVerify);

/**
 * @nodoc
 * Constructs from two CATMathPoint2Ds and a reference.
 *<br>If the last argument is set to <tt>DontVerify</tt>,
 * the two CATSurParams are assumed to be the low one and the high one,
 * else it creates the smallest CATSurLimits that contains the two 
 * CATSurParams.
 */
  CATSurLimits (const CATMathPoint2D       & iLowPointUV,
		const CATMathPoint2D       & iHighPointUV,
		const CATSurParamReference * iReference,
		CATVerificationMode          iMode = CATVerify);


//=============================================================================
// FRIENDS
//=============================================================================
	/** @nodoc */
//#if defined ( CATIAV5R10 )
friend ExportedByCATCGMGeoMath ostream& operator << (ostream& s,
						const CATSurLimits & p);
/*
#else
friend ExportedByYP00IMPL ostream& operator << (ostream& s,
						const CATSurLimits & p);
#endif  
*/
//=============================================================================
//******************** OTHER METHODS : WILL DISAPPEAR SOON ********************
//=============================================================================
/**
 * @nodoc
 * Use now the IsContaining method.
 */
  CATBoolean Contains(const CATSurParam & P) const;
/**
 * @nodoc
 * Use now the SetLow method
 */
  void SetStartParam (const CATSurParam & P);
/**
 * @nodoc
 * Use now the SetHigh method
 */
  void SetEndParam   (const CATSurParam & P);
/**
 * @nodoc
 * Use now the GetLow method
 */
  CATSurParam GetStartParam () const;
/**
 * @nodoc
 * Use now the GetHigh method
 */
  CATSurParam GetEndParam   () const;


//=============================================================================
//  SETTING AND GETTING THE REFERENCE
//=============================================================================
/**
 * @nodoc
 * Returns a pointer to the reference of <tt>this</tt> CATSurLimits.
 * @return
 * The constant pointer to the reference of the surface.
 */ 
  INLINE const CATSurParamReference * GetReference() const;

/**
 * @nodoc
 * Changes the reference of <tt>this</tt> CATSurLimits.
 */
  INLINE void SetReference(const CATSurParamReference * Reference);


/**
 * @nodoc
 * Modifies the parameters and the reference of a CATSurLimits.
 *<br>Check before that <tt>iLowParam</tt> is lower than <tt>iHighParam</tt>.
 * WARNING : No verification is performed : if you want a verification, use the method
 * AddInside after SetToEmpty().
 */
  void SetExtremities(const CATParamData & iLowU , const CATParamData & iLowV,
		              const CATParamData & iHighU, const CATParamData & iHighV,
		              const CATSurParamReference * iReference);

  /** 
 * @nodoc 
 * WARNING : No verification is performed : if you want a verification, use the method
 * AddInside after SetToEmpty().
	*/
  INLINE void SetExtremities(const double LowU , const double LowV,
		      const double HighU, const double HighV,
		      const CATSurParamReference * Reference ) ;

 /**
  * @nodoc 
 * Retrieves the CATSurParams that delimit <tt>this</tt> CATSurLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param ioLowParam
 * The first limit.
 * @param ioHighParam
 * The last limit.
 */
  void GetExtremitiesForStream(CATSurParam & ioLowParam, CATSurParam & ioHighParam, CATCGMStreamImpl &iStream) const;


protected:
//=============================================================================
// INTERNAL DATAS
//=============================================================================
// Position of the extermities
//  CATParamData _LowU, _LowV, _HighU, _HighV;
  double _minGlobalU, _maxGlobalU, _minGlobalV, _maxGlobalV;

// Flag which is not null if the box is empty
  CATLONG32                 _IsEmpty;

// Management of the datas
  const CATSurParamReference * _Reference;

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE void CATSurLimits::SetToEmpty()
{
  _IsEmpty=1;
}

INLINE CATLONG32 CATSurLimits::IsEmpty() const
{
  return _IsEmpty;
}

INLINE const CATSurParamReference * CATSurLimits::GetReference() const
{
  return _Reference;
}

INLINE void CATSurLimits::SetReference(const CATSurParamReference * Reference)
{
  _Reference = Reference;
}

// Setting the extremities
INLINE void CATSurLimits::SetExtremities(const double LowU , const double LowV,
                                         const double HighU, const double HighV,
                                         const CATSurParamReference * Reference)
{
  _Reference = Reference;
  _minGlobalU    = LowU;
  _minGlobalV    = LowV;
  _maxGlobalU    = HighU;
  _maxGlobalV    = HighV;
  _IsEmpty = 0;
}


#endif
