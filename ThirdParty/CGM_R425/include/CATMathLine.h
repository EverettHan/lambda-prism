#ifndef CATMathLine_H
#define CATMathLine_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
* @CAA2Level L1
* @CAA2Usage U1
*/ 

#include "CATMathematics.h"
#include "IUnknown.h"
#include "CATIACGMLevel.h"



class CATMathPlane;
class CATMathCircle;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "CATMathBox.h"

#include "CATMathCurve.h"
#include "CATMathPoint.h"
#include "CATMathVector.h"
#include "CATMathDirection.h"
#include "CATMathPlane.h"


class CATMathLine;
/** @nodoc */
ExportedByCATMathematics double Distance(const CATMathLine & iLine1,
					   const CATMathLine & iLine2,
					   double & oParamOnLine1, double & oParamOnLine2,
					   CATLONG32 & oDiagnosis);


/** @nodoc */
ExportedByCATMathematics double Distance(const CATMathPoint & iPoint,
					   const CATMathLine &iLine);

/** @nodoc */
ExportedByCATMathematics int Intersect(const CATMathLine & iLine1,
					 const CATMathLine & iLine2,
					 double iStartParam1, double iEndParam1,
					 double iStartParam2, double iEndParam2,
					 double iTol,
					 double & oParamOnLine1, double & oParamOnLine2);

/** @nodoc */
ExportedByCATMathematics int Intersect(const CATMathLine & iLine,
					 const CATMathCircle & iCircle,
					 double iStartParam1, double iEndParam1,
					 double iStartParam2, double iEndParam2,
					 double iTol,
					 double oParamOnLine[2], double oParamOnCircle[2]);

/** @nodoc */
ExportedByCATMathematics void Projection(const CATMathPoint & iPointToProject,
					   const CATMathLine & iOnLine,
					   double & oParamOnLine);


/** @nodoc */
ExportedByCATMathematics CATMathPoint Projection(const CATMathPoint & iPointToProject,
							   const CATMathLine & iOnLine);





/**
* Class representing an untrimmed 3D mathematical line.
* <br>It is composed of an <tt>_Origin</tt> (CATMathPoint),
* a normalized vector <tt>_Direction</tt> (CATMathVector),
* and a scale <tt>_Scale</tt>.
* The parameterization of the CATMathMathLine is defined as follows:
* <tt>Line(Param) = Line._Origin + <b>Param</b> * Line._Scale * Line._Direction</tt>,
* where <tt>Param</tt> is the parameter.
*/
class ExportedByCATMathematics CATMathLine : public CATMathCurve
{
public:
	//============================================================================
	//- Constructor
	//============================================================================
	/**
	* Constructs a CATMathLine passing through (0,0,0), with (1,0,0)
	* direction .
	*/
	CATMathLine ();

	/**
   * @nodoc
	* @deprecated V5R15 Set
	* Constructs from a CATMathPoint and a CATMathVector.
	* <br>Throws an error if the vector is null.
	*/
	CATMathLine (const CATMathPoint & iOrigin, const CATMathVector & iVector);

	/**
   * @nodoc
	* @deprecated V5R15 Set
	* Constructs from two CATMathPoints.
	* <br>Throws an error if the two points are confused.
	*/
	CATMathLine (const CATMathPoint & iOrigin,
		                    const CATMathPoint & iSecondPoint);


	/**
	* Copy constructor.
	*/
	CATMathLine (const CATMathLine & iLineToCopy);

	//============================================================================
	//- Get/Set
	//============================================================================
	/**
	* Returns the class name: <tt>CATMathLine</tt>.
	*/
	CATMathClassId IsA () const;

	/**
	* Returns the mathematical type.
	* @return
	* The CATMathematicType. 
	*/
	CATMathematicType GetMathType() const;

	/**
	* Set from a CATMathPoint and a CATMathVector.
	* @return 
	* <tt>E_FAIL</tt> if the vector is null, <tt>S_OK</tt> otherwise.
	*/
	HRESULT Set(const CATMathPoint & iOrigin, const CATMathVector & iVector);

	/**
	* Constructs from two CATMathPoints.
	* @return 
	* <tt>E_FAIL</tt> if the two points are confused, <tt>S_OK</tt> otherwise.
	*/
	HRESULT Set(const CATMathPoint & iOrigin,const CATMathPoint & iSecondPoint);


	/**
	* Returns the direction of <tt>this</tt> CATMathLine. 
	*/
	void GetDirection (CATMathVector & ioDirection) const;


	/**
   * @nodoc
	* @deprecated V5R15 SetLineDirection
	* Modifies the (normalized) direction of <tt>this</tt> CATMathLine. 
	* <br>Throws an error if the new direction is null.
	* @return 
	* <tt>FALSE</tt> if the new direction is null, <tt>TRUE</tt> otherwise.
	*/
	CATBoolean SetDirection (const CATMathVector & iVector);


   /**
   * @nodoc
	* @deprecated V5R20 SetLineDirection
	* Modifies the (normalized) direction of <tt>this</tt> CATMathLine. 
	* @return 
	* <tt>E_FAIL</tt> if the new direction is null, <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetVector(const CATMathVector & iVector);
 
	/**
	* Modifies the (normalized) direction of <tt>this</tt> CATMathLine. 
	* @return 
	* <tt>E_FAIL</tt> if the new direction is null, <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetLineDirection(const CATMathVector & iVector);

	/**
	* Returns the origin of <tt>this</tt> CATMathLine. 
	*/
	void GetOrigin (CATMathPoint & ioOrigin) const;

	/**
	* Modifies the origin of <tt>this</tt> CATMathLine. 
	*/
	void SetOrigin (const CATMathPoint & iOrigin);

	/**
	* Returns the scale of <tt>this</tt> CATMathLine. 
	*/
	double GetScale () const;

	/**
   * @nodoc
	* @deprecated V5R20 SetLineScale
	* Modifies the scale of <tt>this</tt> CATMathLine. 
	* @param iScale.
	* The new scale.
	* <br>Throws an error if the new scale is null.
	* @return 
	* <tt>FALSE</tt> if the new scale is null, <tt>TRUE</tt> otherwise.
	*/
	CATBoolean SetScale (double  iScale);

	/**
	* Modifies the scale of <tt>this</tt> CATMathLine. 
	* @param iScale.
	* The new scale.
	* @return 
	* <tt>E_FAIL</tt> if the new scale is null, <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetLineScale (double  iScale);

	/**
	* Returns the point of <tt>this</tt> CATMathLine corresponding to a given parameter.
	* @return 
	* <tt>ioResult=Line._Origin + <b>iParam</b> * Line._Scale * Line._Direction</tt>
	*/
	void EvalPoint (const double iParam, CATMathPoint & ioResult) const;

	/**
	* Changes the parameter orientation of <tt>this</tt> CATMathLine. 
	*/   
	void ReverseDirection() ;

	/**
	* Retrieves the param on <tt>this</tt> CATMathLine corresponding to a CATMathPoint
	* inside limitations.
	* 
	* @param iPoint
	* The CATMathPoint which coordinates are to be transformed as a param.
	* @param ioParam
	* The param on <tt>this</tt> corresponding to <tt>iPoint</tt>. 
	* @param iTol
	* The 3D tolerance, defining a tube along the line with two hemispheres at each end.
	* If the input point is not inside this tube, no parameter is retrieved.
	* @param iStartParam, iEndParam
	* The limits, expressed as parameters, to take into account for trimming <tt>this</tt> CATMathLine.
	* @return
	* The number of parameters that can be evaluated on this point.
	* <dl><dt> 0  <dd>No parameter corresponds to this point.
	*     <dt> 1  <dd>Only one parameter corresponds to this point.
	*     <dt> 2  <dd>Two parameters correspond to this point.
	*</dl>
	*/
	int GetParam(const CATMathPoint &iPoint,
		                   double *ioParam, const double iTol,
		                   const double iStartParam, const double iEndParam) const;

	/**
	* Projects a CATMathPoint on <tt>this</tt> CATMathLine.
	*/
	void Project(const CATMathPoint &iPointToProject,
		                CATMathPoint &ioProjectedPoint) const;

	/**
	* Projects a CATMathPoint on <tt>this</tt> CATMathLine.
	*/
	void Project(const CATMathPoint &iPointToProject,
		                double &ioParam) const;

	/**
	* Returns the distance between two CATMathLines.
	* @param ioParamOnOtherLine
	*   The parameter of the point of <tt>iOtherLine</tt> closest to <tt>this</tt> CATMathLine.
	* @param ioParamOnThisLine
	*   Parameter of the point of <tt>this</tt> CATMathLine closest to <tt>iOtherLine</tt>.
	* @param ioDiagnosis 
	* <dl>
	* <dt><tt>0</tt>        <dd>if the lines are parallel (in this case,
	*                       <tt>oParamOnLine1</tt> and <tt>oParamOnLine2</tt>
	*                       are null).
	* <dt><tt>1</tt>        <dd>if the lines are not parallel.
	* <dt><tt>2</tt>        <dd>if the lines are identical (in this case,
	*                       <tt>oParamOnLine1</tt> and <tt>oParamOnLine2</tt>
	*                       are null).
	* </dl> 
	*/
	double DistanceTo(const CATMathLine & iOtherLine,
		                            double & ioParamOnOtherLine, double & ioParamOnThisLine,
		                            int & ioDiagnosis) const;

#ifdef CATIACGMV5R21
	/**
	* Returns the square distance between <tt>this</tt> CATMathLine and a CATMathPoint. 
	*/
	double SquareDistanceTo(const CATMathPoint & iPoint) const;
#endif

	/**
	* Returns the distance between <tt>this</tt> CATMathLine and a CATMathPoint. 
	*/
	double DistanceTo(const CATMathPoint & iPoint) const;

	/**
	* Intersects <tt>this</tt> CATMathLine with another one. 
	* @param iOtherLine 
	*   The other CATMathLine to intersect. 
	* @param iStartParamOnOtherLine, iEndParamOnOtherLine
	*   The limits to take into account for <tt>iOtherLine</tt>.
	* @param iStartParamOnThis, iEndParamOnThis
	*   The limits to take into account for <tt>this</tt> CATMathLine.
	* @param ioParamOnLine1 
	*   The parameter of the intersection on <tt>iOtherLine</tt>. 
	* @param ioParamOnLine2
	*   The parameter of the intersection on <tt>this</tt> CATMathLine. 
	* @return
	* <dl>
	* <dt><tt>0</tt>        <dd>if there is no intersection
	* <dt><tt>1</tt>        <dd>if there is an intersection
	* </dl>
	*/
	int Intersect(const CATMathLine & iOtherLine,
		                double iStartParamOnOtherLine, double iEndParamOnOtherLine,
						double iStartParamOnThis, double iEndParamOnThis,
						double iTol,
						double & ioParamOnOtherLine, double & ioParamOnThisLine) const;

	//============================================================================
	//- friend function
	//============================================================================
	/**
	* @nodoc
	* @deprecated V5R20 DistanceTo
	*/
	ExportedByCATMathematics friend double Distance(
		const CATMathLine & iLine1,
		const CATMathLine & iLine2,
		double & oParamOnLine1, double & oParamOnLine2,
		CATLONG32 & oDiagnosis);

	/**
	* @nodoc
	* @deprecated V5R20 DistanceTo
	*/
	ExportedByCATMathematics friend double Distance(
		const CATMathPoint & iPoint,
		const CATMathLine &iLine);


	/**
	* @nodoc
	* @deprecated V5R20 Intersect
	*/
	ExportedByCATMathematics friend int Intersect(
		const CATMathPlane & iPlane1,
		const CATMathPlane & iPlane2,
		CATMathLine & oIntersectionLine);

	/**	
	* @nodoc
	* @deprecated V5R20 Intersect
	*/
	ExportedByCATMathematics friend int Intersect(
		const CATMathLine & iLine1,
		const CATMathLine & iLine2,
		double iStartParam1, double iEndParam1,
		double iStartParam2, double iEndParam2,
		double iTol,
		double & oParamOnLine1, double & oParamOnLine2);

	/**
	* @nodoc
	* @deprecated V5R20 Intersect
	*/
	ExportedByCATMathematics friend int Intersect(
		const CATMathLine & iLine,
		const CATMathCircle & iCircle,
		double iStartParam1, double iEndParam1,
		double iStartParam2, double iEndParam2,
		double iTol,
		double oParamOnLine[2], double oParamOnCircle[2]);

	/**
	* @nodoc 
	* @deprecated V5R20 IsIntersecting (see CATMathBox)
	*/
	int Cross (const CATMathBox & iBox) const;

	/**
	* @nodoc
	* @deprecated V5R20 Project
	*/
	ExportedByCATMathematics friend void Projection(
		const CATMathPoint & iPointToProject,
		const CATMathLine & iOnLine,
		double & oParamOnLine);

	/**
	* @nodoc
	* @deprecated V5R20 Project 
	*/
	ExportedByCATMathematics friend CATMathPoint Projection(
		const CATMathPoint & iPointToProject,
		const CATMathLine & iOnLine);

	/**
	* @nodoc
	* @deprecated V5R20. 
	*/
	//CATMathLine (const CATMathPoint & iOrigin,
	//	const CATMathDirection & iDirection);

	/**
   * @nodoc
	* @deprecated V5R20 GetOrigin
	* Returns the origin of <tt>this</tt> CATMathLine. 
	* The signature which returns a CATMathPoint in output argument should be preferably used.
	*/
	CATMathPoint GetOrigin () const;

	/**
   * @nodoc
	* @deprecated V5R20 GetDirection
	* Returns the direction of <tt>this</tt> CATMathLine.
	* The signature which returns a CATMathDirection in output argument should be preferably used.
	*/
	CATMathDirection GetDirection () const;

	/**
	* @nodoc
	* @deprecated V5R20 GetScale
	*/
	double GetLength () const;

	/**
	* @nodoc
	* @deprecated V5R15 SetLineLength
	* <br>Throws an error if the new length is null.
	*/
	void SetLength (const double iLength);


	/**
	* @nodoc
	* @deprecated V5R20 SetLineScale
	* @return 
	* <tt>E_FAIL</tt> if the new length is null, <tt>S_OK</tt> otherwise.
	*/
	HRESULT SetLineLength(const double iLength);

	/**
   * @nodoc
	* @deprecated V5R20 EvalPoint
	* Returns the point of <tt>this</tt> CATMathLine corresponding to a given parameter.
	* The signature which returns the CATMathPoint as an output argument should be preferably used.
	*/
	CATMathPoint EvalPoint (const double iBid) const;


	/**
	* @nodoc
	* @deprecated V5R20. 
	*/
	void SetDirection (const CATMathDirection & iDirection);


	/**
	* @nodoc
	*  @deprecated V5R20
	* Dumps <tt>this</tt> CATMathLine.
	* <br>This writes the following lines on the ostream:
	*<pre>
	* Origin    = ( OriginFirstCoord , OriginSecondCoord , OriginThirdCoord )
	* Direction = ( DirFirstCoord    , DirSecondCoord    , DirThirdCoord )
	* </pre>
	* @param iStream  
	* A pointer to the output. If <tt>0L</tt>, the method dumps the 
	* coordinates on the <tt>cout</tt> output.
	*/
	void Dump(ostream * iStream=0L) const;

private :
	// normalized vectors
	CATMathVector _FirstAxis;
	CATMathPoint _Origin;
	double _Scale;

};

#endif


