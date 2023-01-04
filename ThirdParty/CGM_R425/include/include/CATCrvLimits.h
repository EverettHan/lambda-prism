#ifndef CATCRVLIMITS_H
#define CATCRVLIMITS_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIAV5Level.h"
#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATCrvParam.h"
#include "CATParamData.h"
#include "CATIsoParameter.h"
#include "CATVerificationMode.h"
#include "CATMathInline.h"

class CATCrvParamReference;
class CATSurParam;
class CATSurLimits;
class CATMathTransformation1D;

/**
 * Class representing the limitations of a CATCurve.
 *<br>The CATCrvLimits contains the two arc numbers and two local parameters
 * on these arcs of the limiting points. 
 *<br>The CATCrvLimits defines a closed interval. It can be empty (if
 * the high limit is smaller than the low one, or if some of them 
 * is not defined): in this case, it does not contain any point.
 * @see CATCurve, CATCrvParam
 */
//#if defined ( CATIAV5R10 )
class  ExportedByCATCGMGeoMath CATCrvLimits
/*
#else
class ExportedByYP00IMPL CATCrvLimits
#endif  
*/
{
 public:
/**
 * Constructs an empty CATCrvLimits.
 */
  CATCrvLimits ();

/**
 * Constructs a CATCrvLimits from two CATCrvParams.
 * @param iLowParam
 * The first limitation of the curve.
 * @param iHighParam
 * The last limitation of the curve.
 * @param iMode
 * Only use with the default value.
 */
  CATCrvLimits (const CATCrvParam & iLowParam, 
		const CATCrvParam & iHighParam,
		CATVerificationMode iMode = CATVerify);

/**
 * @nodoc
 * Constructs a CATCrvLimits from two CATParamDatas and a reference to
 * a CATCurve.
 *<br>If the last argument is set to <tt>DontVerify</tt>,
 * the two CATCrvParams are assumed to be the low one and the high one,
 * else it creates the smallest CATCrvLimits that contains the two 
 * CATCrvParams.
 */
  CATCrvLimits (const CATParamData         & iLowParam, 
		const CATParamData         & iHighParam,
		const CATCrvParamReference * iReference,
		CATVerificationMode          iMode = CATVerify);

/**
 * @nodoc
 * Constructs a CATCrvlimits from two global parameters and a reference
 * to a CATCurve.
 *<br>The verification of the low and high parameters is always performed.
 */
  CATCrvLimits (double               iLowGlobalParam, 
		double                       iHighGlobalParam,
		const CATCrvParamReference * iReference);

/**
 * Copy Constructor.
 */
  CATCrvLimits (const CATCrvLimits & iCrvLimitsToCopy);

//=============================================================================
// SET AND GET THE EXTREMITIES
//=============================================================================
//- Read : should not be used, check before if the CrvLimits is empty
/**
 * @nodoc
 * Use now the GetLow method.
 */
  CATCrvParam GetStartParam () const;
/**
 * @nodoc
 * Use now the GetHigh method.
 */
  CATCrvParam GetEndParam   () const;

/**
 * Retrieves the two CATCrvParam delimiting <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param ioLowParam
 * The first limitation of the curve.
 * @param ioHighParam
 * The last limitation of the curve.
 */
  void GetExtremities(CATCrvParam &ioLowParam, CATCrvParam &ioHighParam) const;

/**
 * Retrieves the extremities of a 1D box corresponding to the global parameters of <tt>this</tt> 
 * CATCrvLimits. <br>Check before that the CATCrvLimits is not empty.
 * @param ioGlobalLow
 * The global parameter value of the first limitation of the curve.
 * @param ioGlobalHigh
 * The global parameter value of the last limitation of the curve.
 */
  void GetExtremities(double &ioGlobalLow, double &ioGlobalHigh) const;

  /**
 * Retrieves the extremities of a 1D box corresponding to the global parameters of <tt>this</tt> 
 * CATCrvLimits. <br>Check before that the CATCrvLimits is not empty.
 * @param ioLocalLow
 * The local parameter value of the first limitation of the curve.
 * @param ioLocalHigh
 * The local parameter value of the last limitation of the curve.
  * @param ioLowPartNumber
 * The arc number of the first limitation of the curve.
 * @param ioHighPartNumber
 * The arc number of the last limitation of the curve.
 */
  void GetLocalExtremities(double &ioLocalLow     , double &ioLocalHigh     , 
			   CATLONG32   &ioLowPartNumber, CATLONG32   &ioHighPartNumber) const;

/**
 * Retrieves the low limitation of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param ioLowParam
 * The first limitation of the curve.
 */
  void GetLow(CATCrvParam &ioLowParam) const;

/**
 * Retrieves the high CATCrvParam of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param ioHighParam
 * The last limitation of the curve.
 */
  void GetHigh(CATCrvParam &ioHighParam) const;

/**
 * @nodoc
 */
  void SetStartParam (const CATCrvParam & Param);
/**
 * @nodoc
 */
  void SetEndParam   (const CATCrvParam & Param);

/**
 * Modifies the low CATCrvParam of <tt>this</tt> CATCrvLimits.
 *<br>Check before that <tt>iLowParam</tt> is lower than <tt>iHighParam</tt>.
 * @param iLowParam
 * The first limitation of the curve.
 */ 
  void SetLow(const CATCrvParam & iLowParam);

/**
 * Modifies the high CATCrvParam of <tt>this</tt> CATCrvLimits.
 *<br>Check before that <tt>iHighParam</tt> is higher than <tt>iLowParam</tt>.
 * @param oHighParam
 * The last limitation of the curve.
 */ 
  void SetHigh(const CATCrvParam & iHighParam);


  /**
 * @nodoc
 * To be used from V5R21.
 * Modifies the parameters and the reference of <tt>this</tt> CATCrvLimits.
 *<br>Check before that <tt>iLowParam</tt> is lower than <tt>iHighParam</tt>.
 */
  INLINE void SetExtremities(const CATParamData         & iLowParam,
		                     const CATParamData         & iHighParam,
		                     const CATCrvParamReference * iReference);

		  /** @nodoc  */    
  void SetExtremities(const double                 iLowParam,
		      const double                 iHighParam,
		      const CATCrvParamReference * iReference);

#ifdef CATIACGMV5R23
/**
 * Modify the parameters and the reference from two CATCrvParams.
 * If the fist CATCrvParam is greater than the second one , they will be inverted.
 * @param iLowParam
 * The first limitation of the curve.
 * @param iHighParam
 * The last limitation of the curve.
 */
  void SetExtremities( const CATCrvParam & iLowParam, 
                       const CATCrvParam & iHighParam);
#endif
		      
/**
 * Sets <tt>this</tt> CATCrvLimits to an empty one.
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
 * Returns the distance of a parameter to the nearest point of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @param iParam
 * The parameter of the point.
 * @return
 * The distance between <tt>iParam</tt> and the nearest point of <tt>this</tt>.
 */
  double DistanceTo(const CATCrvParam & iParam) const;


/**
 * @nodoc
 * Returns a pointer to the reference of <tt>this</tt> CATCrvLimits.
 */ 
  INLINE const CATCrvParamReference * GetReference() const;

/**
 * @nodoc
 * Changes the reference of <tt>this</tt> CATCrvLimits.
 */
  INLINE void SetReference(const CATCrvParamReference * iReference);

//=============================================================================
// READ THE INTERNAL LIMITS
//=============================================================================

/**
 * Returns the global parameter of the low limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The parameter value of the first limitation.
 */
  double GetLowParam() const;

/**
 * Returns the global parameter of the high limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The parameter value of the last limitation.
 */
  double GetHighParam() const;

/**
 * Returns the arc number of the low limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The arc number of the first limitation.
 */
  INLINE CATLONG32 GetLowArcNumber()const ;

/**
 * Returns the arc number of the high limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The arc number of the last limitation.
 */
  INLINE CATLONG32 GetHighArcNumber()const ;

/**
 * Returns the local parameter of the low limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The local parameter (on the arc) of the first limitation.
 */
  INLINE double GetLowLocalParam() const;

/**
 * Returns the local parameter of the high limit of <tt>this</tt> CATCrvLimits.
 *<br>Check before that the CATCrvLimits is not empty.
 * @return
 * The local parameter (on the arc) of the last limitation.
 */
  INLINE double GetHighLocalParam() const;

//=============================================================================
// COMPUTATIONS THAT MODIFIES THE CrvLimits
//=============================================================================
/**
 * Replaces <tt>this</tt> CATCrvLimits by the intersection of two other one.
 * <br>The result can be an empty CATCrvLimits.
 * @param iLimits1
 * The first limitation to operate.
 * @param iLimits21
 * The second limitation to operate.
 */
  void SetToIntersection(const CATCrvLimits &iLimits1,
			 const CATCrvLimits &iLimits2);

/**
 * Replaces <tt>this</tt> CATCrvLimits by the union of two other one.
 * <tt>this</tt> is replaced by the CATCrvLimits of low limit the lowest limit of the two CATCrvlimits and
 * of high limit the highest limit, even the two CATCrvLimits are not 
 * intersecting each other.
 * @param iLimits1
 * The first limitation to operate.
 * @param iLimits21
 * The second limitation to operate.
 */
  void SetToUnion(const CATCrvLimits &iLimits1,
		  const CATCrvLimits &iLimits2);

/**
 * Replaces <tt>this</tt> by a CATCrvLimits that also contains a given CATCrvParam.
 * @param iParam
 * The parameter to take into account.
 */
  void AddInside(const CATCrvParam &iParam);

/**
 * Replaces <tt>this</tt> by a CATCrvLimits that also contains a given global parameter.
  * @param iGlobalParam
 * The parameter value to take into account.
 */
  void AddInside(double iGlobalParam);

/**
 * Replaces <tt>this</tt> CATCrvLimits by its union with another CATCrvLimits.
 * @param iLimits
 * The limitations to union with <tt>this</tt>
*/
  void AddInside(const CATCrvLimits &iLimits);

//======================================================================
// COMPUTATION WITH A CrvLimits THAT RETURNS A RESULT
//======================================================================
/**
 * Tests whether <tt>this</tt> CATCrvLimits is intersecting another one.
 * @param iBoxToCompare
 * The limitations to compare with >tt<this</tt>.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if there is no intersection.
 *     <dt><tt>1</tt>  <dd> if there is an intersection (this is also the case
 * when there is just a point in common).
 * </dl>
 */
  CATLONG32 IsIntersecting(const CATCrvLimits &iBoxToCompare) const;

/**
 * Use preferably the signature which takes as an input argument the tolerance.
 * Tests whether <tt>this</tt> CATCrvParam is inside a CATCrvLimits.
 * @param iParamToCompare
 * The parameter to take into account.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATCrvLimits does not contain the 
 * CATCrvParam.
 *     <dt><tt>1</tt>  <dd> if the CATCrvLimits contains the CATCrvParam.
 * </dl>
 */
  CATLONG32 IsContaining(const CATCrvParam &iParamToCompare) const;

/**
 * Tests whether <tt>this</tt> CATCrvParam is inside a CATCrvLimits at a given tolerance.
 * @param iParamToCompare
 * The parameter to take into account.
 * @param iTol
 * The tolerance for the test.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATCrvLimits does not contain the 
 * CATCrvParam.
 *     <dt><tt>1</tt>  <dd> if the CATCrvLimits contains the CATCrvParam.
 * </dl>
 */
  CATLONG32 IsContaining(const CATCrvParam &iParamToCompare, double iTol) const;

/**
 * Use preferably the signature which takes as an input argument the tolerance.
 * Tests whether <tt>this</tt> CATCrvParam is inside a CATCrvLimits.
 * @param iParamToCompare
 * The parameter to take into account.
 * @param iTol
 * The tolerance for the test.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATCrvLimits does not contain the 
 * CATCrvParam.
 *     <dt><tt>1</tt>  <dd> if the CATCrvLimits contains the CATCrvParam.
 * </dl>
*/
  CATLONG32 IsContaining(const CATCrvLimits &iOtherBox) const;

	/**
 * Tests whether <tt>this</tt> CATCrvLimits is including another CATCrvLimits.
 * @param iOtherBox
 * The limitationa to take into account.
 * @param iTol
 * The tolerance for the test.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>0</tt>  <dd> if the CATCrvLimits is not containing 
 * <tt>iOtherBox</tt>.
 *     <dt><tt>1</tt>  <dd> if the CATCrvLimits is containing
 * <tt>iOtherBox</tt>.
 *</dl>
 */
  CATLONG32 IsContaining(const CATCrvLimits &iOtherBox, double iTol) const;

  //---------------------------------------------------------------
  // Tests if T(iBox) is included in this and calculate the 
  // new Transfo1D if necessary
  // Period = 0 if not periodic
  //---------------------------------------------------------------
	/**
	 * @nodoc
	 */
  CATLONG32 IsContaining(const CATCrvLimits            & iBox,
		          CATMathTransformation1D & ioTransfo1D,
		          double                    iPeriod = 0,
		          double                    iTol = 0   ) const;

/**
 * Retrieves the CATCrvLimits having the same relative positioning
 * to <tt>this</tt> CATCrvLimits than <tt>iRefLim</tt> in <tt>iRefAll</tt>.
 * @param iRefAll
 * The reference CATCrvLimits of global parameters <tt>(A1,A2)</tt>.
 * @param iRefLim
 * The compared CATCrvLimits of global parameters <tt>(B1,B2)</tt>.
 * @param ioResultLimit
 * The resulting CATCrvLimits of global parameters <tt>(R1,R2)</tt> 
 * such that (with <tt>(T1,T2)</tt> the global
 * parameters of <tt>this</tt>):<br>
 *<tt> (R1-T1)*(A2-A1) = (B1-A1)*(T2-T1)
 *     (R2-T1)*(A2-A1) = (B2-A1)*(T2-T1)</tt> 
 */
  void GetEquivalentLimits(const CATCrvLimits & iRefAll, 
			   const CATCrvLimits & iRefLim,
			   CATCrvLimits       & ioResultLimit) const ;

/**
 * Retrieves the global parameter having the same relative position
 * to <tt>this</tt> CATCrvLimits than <tt>iRefParam</tt> in <tt>iRefAll</tt>.
 * @param iRefAll
 * The reference CATCrvLimits of global parameters <tt>(A1,A2)</tt>.
 * @param iRefParam
 * The compared CATCrvParam of global parameters <tt>(B1,B2)</tt>.
 * @param ioResultParam
 * The resulting CATCrvParam of global parameters <tt>R</tt> 
 * verifying the following equation (with <tt>(T1,T2)</tt> the global
 * parameters of <tt>this</tt>):
 *<tt> (R1-T1)*(A2-A1) = (B1-A1)*(T2-T1) </tt> 
 */
  void GetEquivalentParam(const CATCrvLimits & iRefAll, 
			  const CATCrvParam  & iRefParam,
			  CATCrvParam        & ioResultParam) const ;


/**
 * Retrieves the global parameter having the same relative position
 * to <tt>this</tt> CATSurLimits than iRefPart in an isoparametric curve of <tt>iRefAll</tt>.
 * @param iRefAll
 * The limits of a CATSurface.
 * @param iRefPoint
 * The global parameter of a point on <tt>iRefAll</tt>.
 * @param iIsoParameter
 * The direction of the isoparameter (IsoParameterU or 
 * IsoParameterV). On this direction, <tt>iRefPoint</tt> has a global
 * parameter of value <tt>B</tt> and the isoparameter line passing
 * through this point has <tt>(A1,A2)</tt> limits.
 * @param ioResultParam
 * The global parameter  <tt>R</tt> verifying the following equation
 * (with <tt>(T1,T2)</tt> the global parameters of <tt>this</tt>):
 * <tt> (R-T1)*(A2-A1) = (B-A1)*(T2-T1) </tt> 
 */
  void GetEquivalentParam(const CATSurLimits    & iRefAll,
			  const CATSurParam     & iRefPart,
			  const CATIsoParameter   iIsoParameter,
			        CATCrvParam     & ioResultParam   ) const; 
  

/**
 * Retrieves the CATCrvLimits having the same relative position
 * to <tt>this</tt> CATSurLimits than iRefPart in an isoparametric curve of RefAll.
 * <br>Same as above for the two extreme parameters of the CATCrvLimits.
 * @param iRefAll
 * The limits of a CATSurface.
 * @param iRefPart
 * The limits on <tt>iRefAll</tt>.
 * @param iIsoParameter
 * The direction of the isoparameter (IsoParameterU or 
 * IsoParameterV). On this direction, <tt>iRefPoint</tt> has a global
 * parameter of value <tt>B</tt> and the isoparameter line passing
 * through this point has <tt>(A1,A2)</tt> limits.
 * @param ioResultLimit
 * The limit of extremal parameters defined in the following manner:
 * global parameter of value <tt>R</tt> verifying the equation
 * (with <tt>(T1,T2)</tt> the global parameters of <tt>this</tt>):
 * <tt> (R-T1)*(A2-A1) = (B-A1)*(T2-T1) </tt> 
 */
  void GetEquivalentLimits(const CATSurLimits    & iRefAll,
			   const CATSurLimits    & iRefPart,
			   const CATIsoParameter   iIsoParameter,
			         CATCrvLimits    & ioResultLimit  ) const; 
  
  /** @nodoc */
  void ApplyTransformation1D(const CATMathTransformation1D &iTransfo1D,
			           CATCrvLimits            &oLimits   ) const;
//=============================================================================
// Overloaded operators
//=============================================================================
/**
 * Equality operator.
 * <br><pre>( Lim1 == Lim2 ) <=> (Lim1.GetLowParam == Lim2GetLowParam) and
 *                          (Lim1.GetHighParam == Lim2.GetHighParam) 
 *                         </pre>
 */
  CATLONG32 operator == (const CATCrvLimits & iLimits) const;

/**
 * Inequality operator.
 * <br><pre>( Lim1 != Lim2 ) <=> (Lim1.GetLowParam != Lim2GetLowParam) or
 *                          (Lim1.GetHighParam != Lim2.GetHighParam)
 *                          </pre>
 */
  CATLONG32 operator != (const CATCrvLimits & iLimits) const;

//=============================================================================
// FRIENDS
//=============================================================================
/**
 * @nodoc
 */
//#if defined ( CATIAV5R10 )
  friend ExportedByCATCGMGeoMath ostream& operator << (ostream& iS,
						const CATCrvLimits & iLimits);
/*
#else
  friend ExportedByYP00IMPL ostream& operator << (ostream& iS,
						const CATCrvLimits & iLimits);
#endif  
*/
//=============================================================================
// INTERNAL DATAS
//=============================================================================

protected:
  // Extrem position on the curve
  /** @nodoc */ 
  double  _LowLocalParam,_HighLocalParam;
  /** @nodoc */ 
  CATLONG32    _LowLocalNumber,_HighLocalNumber;

// Its value is 1 if the CrvLimits is empty
  /** @nodoc */
  CATLONG32 _IsEmpty;

// Function that manages the Pamameters
  /** @nodoc */
  const CATCrvParamReference *_Reference;

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================

// Setting the extremities
INLINE void CATCrvLimits::SetExtremities(const CATParamData & LowParam,const CATParamData & HighParam,const CATCrvParamReference * Reference)
{
  _Reference = Reference;
  
  _LowLocalNumber  = LowParam.PartNumber;
  _LowLocalParam   = LowParam.LocalParam;
  _HighLocalNumber = HighParam.PartNumber;
  _HighLocalParam  = HighParam.LocalParam;
  
  _IsEmpty   = 0;
}


INLINE void CATCrvLimits::SetToEmpty()
{
  _IsEmpty=1;
}
INLINE CATLONG32 CATCrvLimits::IsEmpty() const
{
  return _IsEmpty;
}

INLINE CATLONG32 CATCrvLimits::GetLowArcNumber() const
{
  return _LowLocalNumber;
}

INLINE CATLONG32 CATCrvLimits::GetHighArcNumber() const
{
  return _HighLocalNumber;
}

INLINE double CATCrvLimits::GetLowLocalParam() const 
{
  return _LowLocalParam;
}

INLINE double CATCrvLimits::GetHighLocalParam() const
{
  return _HighLocalParam;
}

INLINE const CATCrvParamReference * CATCrvLimits::GetReference() const
{
  return _Reference;
}

INLINE void CATCrvLimits::SetReference(const CATCrvParamReference *Reference)
{
  _Reference = Reference;
}

#endif

