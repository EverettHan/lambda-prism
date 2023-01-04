#ifndef CATMathPlane_H
#define CATMathPlane_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATTolerance.h"
#include "CATMathematics.h"
#include "CATIACGMLevel.h"

#include "CATMathLine.h"
#include "CATMathDirection.h"
#include "CATMathLimits.h"

#include "CATMath3x3Matrix.h"

#ifdef CATIAR418 
#include "CATErrorDef.h"
#else
#include "CATMathInputError.h"
#endif

class CATMathLine;
class CATMathBox;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

class CATMathPlane;
/** @nodoc */
ExportedByCATMathematics int Intersect(const CATMathLine & iLine,
                                       const CATMathPlane & iPlane,
                                       double & oParamOnLine, 
                                       double & oFirstParamOnPlane,
                                       double & oSecondParamOnPlane, 
                                       double iTol=CATGetDefaultTolerance().EpsgForRelativeTest());
/** @nodoc */
ExportedByCATMathematics int Intersect(const CATMathPlane & iPlane,
                                       const CATMathLine & iLine,
                                       double & oFirstParamOnPlane,
                                       double & oSecondParamOnPlane, 
                                       double & oParamOnLine, 
                                       double iTol=CATGetDefaultTolerance().EpsgForRelativeTest());

/** @nodoc */
ExportedByCATMathematics int Intersect(const CATMathPlane & iPlane1,
                                       const CATMathPlane &iPlane2,
                                       CATMathLine & oIntersectionLine);
/** @nodoc */
ExportedByCATMathematics double Distance(const CATMathPoint & iPoint,
                                         const CATMathPlane & iPlane);
/** @nodoc */
ExportedByCATMathematics void Projection(const CATMathPoint & iPoint,
                                         const CATMathPlane & iPlane,
                                         double &FirstParamOnPlane,
                                         double & SecondParamOnPLane);
/** @nodoc */
ExportedByCATMathematics CATMathPoint Projection(const CATMathPoint & iPoint,
                                                 const CATMathPlane & iPlane);
/** @nodoc */
ExportedByCATMathematics ostream& operator << (ostream& s,const CATMathPlane & iPlane);


/** 
 * Defines the canonical plane.
 * @param CATPlaneOIJ
 * The XOY canonical plane. 
 * @param CATPlaneOJK
 * The YOZ canonical plane. 
 * @param CATPlaneOKI
 * The XOZ canonical plane. 
 */
enum CATCanonicalPlane{CATPlaneOIJ, CATPlaneOJK, CATPlaneOKI};

/**
 * Class representing a mathematical plane in 3D.
 * <br>It is composed of an <tt>Origin</tt> and of two normalized vectors
 * <tt>FirstDirection</tt> and <tt>SecondDirection</tt>.  
 */
class ExportedByCATMathematics CATMathPlane
{
public:
//============================================================================
//- Constructor
//============================================================================

/**
 * Constructs a plane where <tt>Origin=(0,0,0)</tt>,
 * <tt>FirstDirection=(1,0,0)</tt> and <tt>SecondDirection=(0,1,0)</tt> .
 */
    CATMathPlane ();

/**
* Constructs one of the three canonical plane with <tt>Origin=(0,0,0)</tt>,
* <tt>FirstDirection=(1,0,0)</tt> and <tt>SecondDirection=(0,1,0)</tt> for CATMathPlaneOIJ .
* <tt>FirstDirection=(0,1,0)</tt> and <tt>SecondDirection=(0,0,1)</tt> for  CATMathPlaneOJK.
* <tt>FirstDirection=(0,0,1)</tt> and <tt>SecondDirection=(1,0,0)</tt> for  CATMathPlaneOKI.
 */
    CATMathPlane (CATCanonicalPlane Plane);

/**
 * @nodoc
 * @deprecated V5R15 Set
 * Constructs a plane from a point and two vectors.
 * <br>Throws an error if the input vectors are colinear.
 * The input vectors are used to compute the normalized and orthogonal directions of
 * the plane.
 */
    CATMathPlane (const CATMathPoint & iOrigin,
                  const CATMathVector & iFirstDirection,
                  const CATMathVector & iSecondDirection);


/**
 * Constructs a plane from a point and a normal.
 * <br>The normal must not be null, but this is not checked. 
 */
    CATMathPlane (const CATMathPoint & iOrigin,
                  const CATMathVector & iNormal);

/**
 * @nodoc
 * @deprecated V5R15 Set
 * Constructs a plane passing through three points.
 * <br>Throws an error if the three points are aligned.
 */
    CATMathPlane (const CATMathPoint & iOrigin,
                  const CATMathPoint & iSecondPoint,
                  const CATMathPoint & iThirdPoint);

/**
 * Copy constructor.
 */
   CATMathPlane (const CATMathPlane & iPlaneToCopy);

//============================================================================
//- Get/Set
//============================================================================

/**
 * Constructs a plane from a point and two vectors.
 * The input vectors are used to compute the normalized and orthogonal directions of
 * the plane.
 * @return 
 * <tt>E_FAIL</tt> if the input vectors are colinear, <tt>S_OK</tt> otherwise.
 */
   HRESULT Set(const CATMathPoint & iOrigin,
               const CATMathVector & iFirstDirection,
               const CATMathVector & iSecondDirection);

/**
 * Constructs a plane passing through three points.
 * @return 
 * <tt>E_FAIL</tt> if the three points are aligned, <tt>S_OK</tt> otherwise.
 */
   HRESULT Set(const CATMathPoint & iOrigin,
               const CATMathPoint & iSecondPoint,
               const CATMathPoint & iThirdPoint);


/**
 * Retrieves the orthonormalized directions of <tt>this</tt> CATMathPlane.
 */
    void GetDirections (CATMathVector & ioFirstDirection,
                        CATMathVector & ioSecondDirection) const;

/**
 * @nodoc
 * @deprecated V5R15 SetVectors
 * Modifies the directions of <tt>this</tt> CATMathPlane.
 * <br>Throws an error if the new directions are colinear.
 * @return 
 * <tt>FALSE</tt> if the new directions are colinear, <tt>TRUE</tt> otherwise.
 */
    CATBoolean SetDirections (const CATMathVector & iFirstDirection,
                              const CATMathVector & iSecondDirection);


/**
 * Modifies the directions of <tt>this</tt> CATMathPlane.
 * @return 
 * <tt>E_FAIL</tt> if the new directions are colinear, <tt>S_OK</tt> otherwise.
 */
    HRESULT SetVectors(const CATMathVector & iFirstDirection,
                       const CATMathVector & iSecondDirection);

/**
 * Retrieves the origin of <tt>this</tt> CATMathPlane.
 */
    void GetOrigin (CATMathPoint & ioOrigin) const; 

/**
 * Modifies the origin of <tt>this</tt> CATMathPlane.
 */
    void SetOrigin (const CATMathPoint & iOrigin);

/**
 * Retrieves the first (normalized) direction of <tt>this</tt> CATMathPlane.
 */
    void GetFirstDirection (CATMathVector & ioFirstDirection) const;

/**
 * Retrieves the second (normalized) direction of <tt>this</tt> CATMathPlane.
 */
    void GetSecondDirection (CATMathVector & ioSecondDirection) const;

/**
 * Retrieves the (normalized) normal to <tt>this</tt> CATMathPlane.
 */
    void GetNormal (CATMathVector & ioNormal) const;

/**
 * Returns the point of <tt>this</tt> CATMathPlane corresponding to given parameters.
 * @return
 * <tt>ioResult=Plane.Origin + <b>iParam1</b> * Plane.FirstDirection
 * + <b>iParam2</b> * Plane.SecondDirection</tt>
 */
    void EvalPoint(const double iParam1, const double iParam2, CATMathPoint & ioResult) const;

/**
 * Intersects <tt>this</tt> CATMathPlane with a CATMathLine.
 * @param iLine
 *   The CATMathLine to intersect. 
 * @param ioParamOnLine 
 *   The parameter of the intersection on the line. 
 * @param ioFirstParamOnThis 
 *   The parameter of the intersection on <tt>this</tt> CATMathPlane. 
 * @param ioSecondParamOnThis 
 *   The parameter of the intersection on the second direction of <tt>this</tt> CATMathPlane. 
  * @param iTol 
 *   The default tolerance. 
 * @return
 * <dl>
 * <dt><tt>0</tt>        <dd>if there is no intersection
 * <dt><tt>1</tt>        <dd>if there is an intersection
 * <dt><tt>2</tt>        <dd>if the line is included in the plane
 * </dl>
 */
     int Intersect(const CATMathLine & iLine,
                   double & ioParamOnLine, 
                   double & ioFirstParamOnPlane,
                   double & ioSecondParamOnPlane, 
                   double iTol=CATGetDefaultTolerance().EpsgForRelativeTest()) const;

/**
 *  Intersects <tt>this</tt> CATMathPlane with another one. 
 * @param iOtherPlane 
 *   The other CATMathPlane to intersect.
 * @param ioIntersectionLine
 *   The resulting CATMathLine. 
 * @return
 * <dl>
 * <dt><tt>0</tt>        <dd>if there is no intersection
 * <dt><tt>1</tt>        <dd>if there is an intersection
 * <dt><tt>2</tt>        <dd>if they are identical
 * </dl>
 */
    int Intersect(const CATMathPlane & iOtherPlane,
                  CATMathLine & ioIntersectionLine) const;

/**
 * Returns the distance between <tt>this</tt> CATMathPlane and a CATMathPoint.
 */
    double DistanceTo(const CATMathPoint & iPoint) const;

/**
 * Retrieves the projection of a CATMathPoint on a CATMathPlane.
 * @param ioFirstParamOnPlane 
 *   The parameter of the projection on the first direction of the plane.
 * @param ioSecondParamOnPlane 
 *   The parameter of the projection on second direction of the plane.  
 */
    void Project(const CATMathPoint & iPointToProject,
                 double & ioFirstParamOnPlane,
                 double & ioSecondParamOnPLane) const;

/**
 * Returns the projection of a CATMathPoint on a CATMathPlane.
 */
    void Project(const CATMathPoint & iPointToProject,
                 CATMathPoint & ioResult) const;

//============================================================================
//- Friend Functions
//============================================================================
/**
 * @nodoc
 * @deprecated V5R20 Intersect
 */
    ExportedByCATMathematics friend int Intersect(const CATMathLine & iLine,
                                                  const CATMathPlane & iPlane,
                                                  double & oParamOnLine, 
                                                  double & oFirstParamOnPlane,
                                                  double & oSecondParamOnPlane, double iTol);
    
/**
 * @nodoc
 * @deprecated V5R20  Intersect
 */
    ExportedByCATMathematics friend int Intersect(const CATMathPlane & iPlane,
                                                  const CATMathLine & iLine,
                                                  double & oFirstParamOnPlane,
                                                  double & oSecondParamOnPlane, 
                                                  double & oParamOnLine, double iTol);

/**
 * @nodoc
 * @deprecated V5R20  Intersect
 */
    ExportedByCATMathematics friend int Intersect(const CATMathPlane & iPlane1,
                                                  const CATMathPlane &iPlane2,
                                                  CATMathLine & oIntersectionLine);

/**
 * @nodoc
 * @deprecated V5R20 DistanceTo
 */
    ExportedByCATMathematics friend double Distance(const CATMathPoint & iPoint,
                                                    const CATMathPlane & iPlane);

/**
 * @nodoc
 * @deprecated V5R20 Project
 */
    ExportedByCATMathematics friend void Projection(const CATMathPoint & iPoint,
                                                    const CATMathPlane & iPlane,
                                                    double &FirstParamOnPlane,
                                                    double & SecondParamOnPLane);

/**
 * @nodoc
 * @deprecated V5R20 Project
 */
    ExportedByCATMathematics friend CATMathPoint Projection(const CATMathPoint & iPoint,
                                                            const CATMathPlane & iPlane);
/**
 * @nodoc
 * @deprecated V5R20 IsIntersecting (see CATMathBox)
 */
    int Cross(const CATMathBox & iBox) const;


/**
 * @nodoc
 * @deprecated V5R20 EvalPoint
 * Returns the point of <tt>this</tt> CATMathPlane corresponding to given parameters.
 * You should use preferably the <pre>EvalPoint(const double iParam1, const double iParam2, CATMathPoint & ioResult</pre>
 * signature.
 */
    CATMathPoint EvalPoint(const double iBid1, const double iBid2) const;

/**
 * @nodoc
 * @deprecated V5R20 GetFirstDirection
 * Retrieves the first (normalized) direction of <tt>this</tt> CATMathPlane. 
 * You should use preferably the <pre>GetFirstDirection (CATMathVector & ioFirstDirection) </pre> signature.
 */
    CATMathDirection GetFirstDirection () const;

/**
 * @deprecated V5R20 GetSecondDirection
 * Retrieves the fisecondrst (normalized) direction of <tt>this</tt> CATMathPlane. 
 * You should use preferably the <pre>GetSecondDirection (CATMathVector & ioFirstDirection) </pre> signature.
 */
    CATMathDirection GetSecondDirection () const;

/**
 * @deprecated V5R20 GetOrigin
 * Retrieves the origin of <tt>this</tt> CATMathPlane.
 * You should use preferably the <pre>GetOrigin (CATMathPoint & ioOrigin)  </pre> signature.
 */
    CATMathPoint GetOrigin () const;

/**
 * @nodoc
 * @deprecated V5R20 GetNormal
 * Retrieves the (normalized) normal to <tt>this</tt> CATMathPlane.
 * You should use preferably the <pre>GetNormal (CATMathVector & ioNormal)  </pre> signature.
 */
    CATMathDirection GetNormal () const;

/**
 * @nodoc
 * @deprecated V5R20.
 */
    ExportedByCATMathematics friend ostream& operator << (ostream& s,const CATMathPlane & iPlane);

/**
 * Dumps <tt>this</tt> CATMathPlane.
 * <br>This writes the following lines on the ostream:
 *<pre>
 * Origin    = ( OriginFirstCoord    , OriginSecondCoord    , OriginThirdCoord )
 * FirstDir  = ( FirstDirFirstCoord  , FirstDirSecondCoord  , FirstDirThirdCoord )
 * SecondDir = ( SecondDirFirstCoord , SecondDirSecondCoord , SecondDirThirdCoord )
 *</pre>
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;

//============================================================================
//- Private data
//============================================================================
 private :
   // normalized vectors
    CATMathVector _FirstAxis, _SecondAxis;
    CATMathPoint _Origin;
};
/**
 * Defines the OIJ canonical plane.
 */
extern ExportedByCATMathematics const CATMathPlane CATMathOIJ;
/**
 * Defines the OJK canonical plane.
 */
extern ExportedByCATMathematics const CATMathPlane CATMathOJK;
/**
 * Defines the OKI canonical plane.
 */
extern ExportedByCATMathematics const CATMathPlane CATMathOKI;

#endif
