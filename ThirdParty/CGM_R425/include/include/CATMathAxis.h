#ifndef CATMathAxis_H
#define CATMathAxis_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 
#include "CATErrorDef.h"
#include "CATMathematics.h"


#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathInline.h"

#include "CATIACGMLevel.h"

#include "CATMathDirection.h"
#include "CATMath3x3Matrix.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif



/**
* Class representing a mathematical axis system in dimension 3.
* <b>Role</b>:
* <br>It is composed of an <tt>Origin</tt>, and of three directions 
* (normalized vectors) <tt>FirstDirection</tt>, <tt>SecondDirection</tt>,
* <tt>ThirdDirection</tt>. If the three directions are not directly
* orthogonal or normalized, it will be done internally.
*/ 
class ExportedByCATMathematics CATMathAxis
{
public:
	//============================================================================
	//- Constructors
	//============================================================================

	/**
	* Constructs a canonical CATMathAxis.
	* <br><tt>Origin= (0,0,0)</tt>, <tt>FirstDirection = (1,0,0)</tt>, 
	* <tt>SecondDirection = (0,1,0)</tt>, <tt>ThirdDirection= (0,0,1)</tt>.
	*/ 
	CATMathAxis ();

	/**
	* Constructs a CATMathAxis from a CATMathPoint and the three CATMathVector: CATMathI, CATMathJ and CATMathK.
	* <p><tt>CATMathI</tt> is the (1,0,0) CATMathVector
	* <br><tt>CATMathJ</tt> is the (0,1,0) CATMathVector
	* <br><tt>CATMathK</tt> is the (0,0,1) CATMathVector
	* @param P 
	* The point used as the axis origin.
	*/
	CATMathAxis ( const CATMathPoint & P );

	/**
   * @nodoc
	* @deprecated V5R20 Set
	* Constructs a CATMathAxis from a CATMathPoint and a CATMathVector specified as the first direction.
	* <p>The second and third directions are: CATMathJ and CATMathK.
	* @param P 
	* The point used as the axis origin.
	* @param I 
	* The CATMathVector used as the first direction.
	*/
	CATMathAxis ( const CATMathPoint & P, const CATMathVector & I ) ;

	/**
   * @nodoc
	* @deprecated V5R20 Set
	* Constructs a CATMathAxis from a CATMathPoint and two CATMathVector specified as the first and second directions.
	* <p>The third direction is CATMathK. 
	* @param P 
	* The point used as the axis origin.
	* @param I 
	* The CATMathVector used as the first direction.
	* @param J 
	* The CATMathVector used as the second direction.
	*/
	CATMathAxis ( const CATMathPoint & P, const CATMathVector & I, const CATMathVector & J );

	/**
   * @nodoc
	* @deprecated V5R20 Set
	* Constructs a CATMathAxis from a CATMathPoint and three CATMathVector.
	* <p>The three vectors must define
	* an axis system (vector null, colinear vectors), but the constructor does not test whether this 
	* condition is fulfilled.<br>
	* The first direction is normalized (if needed) to become the axis first
	* direction. <br>The axis second direction belongs to the
	* plane defined by the first and second directions. 
	* <br>The third direction is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* <br>Throws an error if the three vectors do not define
	* an axis system (vector null, colinear vectors).
	* @param P 
	* The point used as the axis origin.
	* @param I 
	* The CATMathVector used as the first direction.
	* @param J 
	* The CATMathVector used as the second direction.
	* @param K
	* The CATMathVector used as the third direction.
	*/ 
	CATMathAxis ( const CATMathPoint & P, const CATMathVector & I, const CATMathVector & J, const CATMathVector & K );

	/**
	* Copy constructor.
	*/
	CATMathAxis (const CATMathAxis &iAxisToCopy);

	//============================================================================
	//- Get/Set
	//============================================================================

	/**
	* Modifies the origin and the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* <tt>iFirstDirection</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane (<tt>iFirstDirection</tt>, <tt>CATMathJ</tt>). 
	* <tt>CATMathK</tt> is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
	HRESULT Set( const CATMathPoint & P, const CATMathVector & I );

	/**
	* Modifies the origin and the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* <tt>iFirstDirection</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane (<tt>iFirstDirection</tt>, <tt>iSecondDirection</tt>). 
	* <tt>CATMathK</tt> is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
	HRESULT Set(const CATMathPoint & P,
	                       	 const CATMathVector & DV1,
		                     const CATMathVector & DV2);


	/**
	* Modifies the origin and the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* <tt>iFirstDirection</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane (<tt>iFirstDirection</tt>, <tt>iSecondDirection</tt>). 
	* <tt>iThirdDirection</tt> is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
	HRESULT Set(const CATMathPoint & P,
       		                 const CATMathVector & DV1,
		                     const CATMathVector & DV2,
		                     const CATMathVector & DV3);

	/**
	* Modifies the origin and the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* The first column of <tt>iMatrix</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane generated by the first and the second column of <tt>iMatrix</tt>.
	* The third column of <tt>iMatrix</tt> is used to give the orientation of the
	* axis system. Although the input vectors composing <tt>iMatrix</tt> can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors  do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
    HRESULT Set( const CATMathPoint & iP, const CATMath3x3Matrix & i3x3Matrix );

	/** 
	* Retrieves the three directions of <tt>this</tt> CATMathAxis.
	*<br>The returned vectors are normalized.
	*/
#ifdef CATIACGMV5R21
	INLINE void GetDirections (CATMathVector & ioFirstDirection,
		                       CATMathVector & ioSecondDirection,
		                       CATMathVector & ioThirdDirection) const;
#else
	void GetDirections (CATMathVector & ioFirstDirection,
		                             CATMathVector & ioSecondDirection,
		                             CATMathVector & ioThirdDirection) const;
#endif

	/** 
	* Retrieves the three directions of <tt>this</tt> CATMathAxis in matrix form.
	* The first (normalized) direction of <tt>this</tt> CATMathAxis is stored in the first column of <tt>o3x3Matrix</tt>
	* The second (normalized) direction of <tt>this</tt> CATMathAxis is stored in the second column of <tt>o3x3Matrix</tt>
	* The third (normalized) direction of <tt>this</tt> CATMathAxis is stored in the third column of <tt>o3x3Matrix</tt>
	*/
	INLINE void GetDirections (CATMath3x3Matrix & o3x3Matrix) const;

	/**
   * @nodoc
	* @deprecated V5R15 SetVectors
	* Modifies the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* <tt>iFirstDirection</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane (<tt>iFirstDirection</tt>, <tt>iSecondDirection</tt>). 
	* <tt>iThirdDirection</tt> is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>FALSE</tt> if the three vectors do not define
	* an axis system (vector null, colinear vectors), <tt>TRUE</tt> otherwise.
	*/
	CATBoolean SetDirections (const CATMathVector & iFirstDirection,
		                                          const CATMathVector & iSecondDirection,
		                                          const CATMathVector & iThirdDirection);

	/**
	* Modifies the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* <tt>iFirstDirection</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane (<tt>iFirstDirection</tt>, <tt>iSecondDirection</tt>). 
	* <tt>iThirdDirection</tt> is used to give the orientation of the
	* axis system. Although the input vectors can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetVectors(const CATMathVector & DV1,
		                                  const CATMathVector & DV2,
		                                  const CATMathVector & DV3);

	/**
	* Modifies the directions  of <tt>this</tt> CATMathAxis.
	*<br>
	* The first column of <tt>iMatrix</tt> is normalized (if needed) to become the axis first
	* direction. The axis second direction belongs to the
	* plane generated by the first and the second column of <tt>iMatrix</tt>.
	* The third column of <tt>iMatrix</tt> is used to give the orientation of the
	* axis system. Although the input vectors composing <tt>iMatrix</tt> can be not normalized, the
	* resulting axis has three normalized directions.
	* @return <tt>E_FAIL</tt> if the three vectors  do not define
	* an axis system (vector null, colinear vectors), <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetVectors(const CATMath3x3Matrix & i3x3Matrix); 

	/** 
	* Returns the origin of <tt>this</tt> CATMathAxis.
	*/
#ifdef CATIACGMV5R21
	INLINE void GetOrigin (CATMathPoint & ioOrigin) const;
#else
	void GetOrigin (CATMathPoint & ioOrigin) const;
#endif

	/**
	* Modifies the origin  of <tt>this</tt> CATMathAxis.
	*/
	void SetOrigin (const CATMathPoint & iOrigin);

	/** 
	* Returns the first (normalized) direction of <tt>this</tt> CATMathAxis.
	*/
#ifdef CATIACGMV5R21
	INLINE void GetFirstDirection (CATMathVector & ioFirstDirection) const;
#else
	void GetFirstDirection (CATMathVector & ioFirstDirection) const;
#endif

	/** 
	* Returns the second (normalized) direction of <tt>this</tt> CATMathAxis.
	*/
#ifdef CATIACGMV5R21
	INLINE void GetSecondDirection (CATMathVector & ioSecondDirection) const;
#else
	void GetSecondDirection (CATMathVector & ioSecondDirection) const;
#endif

	/** 
	* Returns the third (normalized) direction of <tt>this</tt> CATMathAxis.
	*/
#ifdef CATIACGMV5R21
	INLINE void GetThirdDirection (CATMathVector & ioThirdDirection) const;
#else
	void GetThirdDirection (CATMathVector & ioThirdDirection) const;
#endif

	/**
	* Dumps <tt>this</tt> CATMathAxis.
	* <br>This writes the following lines on the ostream:
	*<pre>
	* Origin    = ( OriginFirstCoord    , OriginSecondCoord    , OriginThirdCoord )
	* FirstDir  = ( FirstDirFirstCoord  , FirstDirSecondCoord  , FirstDirThirdCoord )
	* SecondDir = ( SecondDirFirstCoord , SecondDirSecondCoord , SecondDirThirdCoord )
	* ThirdDir  = ( ThirdDirFirstCoord  , ThirdDirSecondCoord  , ThirdDirThirdCoord )
	*</pre>
	* @param iStream  
	* A pointer to the output. If <tt>0L</tt>, the method dumps the 
	* coordinates on the <tt>cout</tt> output.
	*/
	void Dump(ostream * iStream=0L) const;

	/** 
	* @deprecated V5R20 GetSecondDirection
	* Returns the second (normalized) direction of <tt>this</tt> CATMathAxis. The signature which returns the
	* CATMathDirection as an output argument should be preferably used.
	*/
	CATMathDirection GetSecondDirection () const;

	/** 
	* @deprecated V5R20 GetThirdDirection
	* Returns the third (normalized) direction of <tt>this</tt> CATMathAxis. The signature which returns the
	* CATMathDirection as an output argument should be preferably used.
	*/
	CATMathDirection GetThirdDirection () const;

	/** 
	* @deprecated V5R20 GetFirstDirection
	* Returns the first (normalized) direction of <tt>this</tt> CATMathAxis. The signature which returns the
	* CATMathDirection as an output argument should be preferably used.
	*/
	CATMathDirection GetFirstDirection () const;

	/** 
	* @deprecated V5R20 GetOrigin
	* Returns the origin of <tt>this</tt> CATMathAxis.  The signature which returns the
	* CATMathPoint as an output argument should be preferably used.
	*/
	CATMathPoint GetOrigin () const;


	//===========================================================================
	//- Private data
	//===========================================================================
private :
	// normalized vectors
	CATMathVector _FirstAxis, _SecondAxis, _ThirdAxis;
	CATMathPoint   _Origin;

  friend class CATMathTools;
};
/**
* Defines the canonical axis system.
*/
extern ExportedByCATMathematics const CATMathAxis CATMathOIJK;

#ifdef CATIACGMV5R21
//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================

INLINE void CATMathAxis::GetDirections (CATMathVector & D1,
                                        CATMathVector & D2,
                                        CATMathVector & D3) const
{
  D1 = _FirstAxis;
  D2 = _SecondAxis;
  D3 = _ThirdAxis; 
}

INLINE void CATMathAxis::GetFirstDirection (CATMathVector & Vec) const
{
  Vec=_FirstAxis;
}

INLINE void CATMathAxis::GetSecondDirection (CATMathVector & Vec) const
{
  Vec=_SecondAxis;
}

INLINE void CATMathAxis::GetThirdDirection (CATMathVector & Vec) const
{
  Vec=_ThirdAxis;
}

INLINE void CATMathAxis::GetOrigin (CATMathPoint & Pt) const
{
  Pt=_Origin;
}
#endif

INLINE void CATMathAxis::GetDirections (CATMath3x3Matrix & oM) const
{
 oM.SetMatrix (_FirstAxis,_SecondAxis,_ThirdAxis) ;
}

#endif


