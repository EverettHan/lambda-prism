#ifndef CATMathLine2D_H
#define CATMathLine2D_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 


#include "CATBaseUnknown.h"

#include "CATMathematics.h"

#include "CATMathPoint2D.h"
#include "CATMathDirection2D.h"

class CATMathPlane;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif


class CATMathLine2D;
/** @nodoc */
ExportedByCATMathematics  int Intersect(const CATMathLine2D & iLine1, 
                      const CATMathLine2D & iLine2,
                      double & oParamOnLine1,
                      double & oParamOnLine2);

/** @nodoc */
ExportedByCATMathematics double Distance(const CATMathPoint2D & iPoint,
                       const CATMathLine2D & iLine);

/** @nodoc */
ExportedByCATMathematics void Projection(const CATMathPoint2D & iPoint,
                       const CATMathLine2D & iLine,
                       double & oParamOnLine);

/** @nodoc */
ExportedByCATMathematics CATMathPoint2D Projection(const CATMathPoint2D & iPoint,
                                 const CATMathLine2D & iLine);




/**
 * Class representing an untrimmed 2D mathematical line.
 * <br>It is composed of an <tt>Origin</tt> (CATMathPoint2D), 
 * and a normalized vector <tt>Direction</tt> (CATMathDirection2D). 
 */
class ExportedByCATMathematics CATMathLine2D
{
 public:
//=============================================================================
//- Constructor
//=============================================================================
/**
 * Constructs a CATMathLine2D, passing through (0,0), with (1,0)
 * direction.
 */
  CATMathLine2D ();
 
/**
 * @nodoc
 * @deprecated V5R15 Set
 * Constructs from a CATMathPoint2D and a CATMathVector2D.
 * <br>Throws an error if the vector is null.
 */
  CATMathLine2D (const CATMathPoint2D & iOrigin,
                               const CATMathVector2D & iVector);

/**
  * @nodoc
  * @deprecated V5R15 Set
  * Constructs from two CATMathPoint2D.
  * <br>Throws an error if the two points are confused.
 */
  CATMathLine2D (const CATMathPoint2D & iOrigin,
                               const CATMathPoint2D & iSecondPoint);

/**
 * Copy constructor.
 */
  CATMathLine2D (const CATMathLine2D & iLineToCopy);

//=============================================================================
//- Get/Set
//=============================================================================

/**
 * Set from a CATMathPoint2D and a CATMathVector2D.
.* @return 
 * <tt>E_FAIL</tt> if the vector is null, <tt>S_OK</tt> otherwise.
 */
  HRESULT Set(const CATMathPoint2D & iOrigin,const CATMathVector2D & iVector);

/**
 * Set from two CATMathPoint2D.
.* @return 
 * <tt>E_FAIL</tt> if the two points are confused, <tt>S_OK</tt> otherwise.
 */
  HRESULT Set(const CATMathPoint2D & iOrigin,const CATMathPoint2D & iSecondPoint);

 /**
 * Retrieves the (normalized) direction of <tt>this</tt> CATMathLine2D.
 */
  void GetDirection (CATMathVector2D & ioNormalizedVector) const;

/**
 * @nodoc
 * @deprecated V5R15 SetVector
 * Modifies the direction of <tt>this</tt> CATMathLine2D.
 * <br>Throws an error if the vector is null.
 * @return 
 * <tt>FALSE</tt> if the new direction is null, <tt>TRUE</tt> otherwise.
 */
  CATBoolean SetDirection (const CATMathVector2D & iVector);


/**
 * @nodoc
 * @deprecated V5R20 SetLineDirection
 * Modifies the direction of <tt>this</tt> CATMathLine2D.
 * <br> and the Length of <tt>this</tt> CATMathLine2D.
.* @return 
 * <tt>E_FAIL</tt> if the new direction is null, <tt>S_OK</tt> otherwise.
 */
  HRESULT SetVector(const CATMathVector2D & iVector);
  
/**
 * Modifies the direction of <tt>this</tt> CATMathLine2D.
 * <br> and the Length of <tt>this</tt> CATMathLine2D.
.* @return 
 * <tt>E_FAIL</tt> if the new direction is null, <tt>S_OK</tt> otherwise.
 */
  HRESULT SetLineDirection(const CATMathVector2D & iVector);


/**
 * Returns the origin of <tt>this</tt> CATMathVector2D.
 */
  void GetOrigin (CATMathPoint2D & ioOrigin ) const;

/**
 * Modifies the origin of <tt>this</tt> CATMathLine2D.
 */
  void SetOrigin (const CATMathPoint2D & iOrigin);

/**
 * Modifies the scale of <tt>this</tt> CATMathLine2D. 
 *@param iScale.
 *The new scale.
 * @return 
 * <tt>FALSE</tt> if the new scale is null, <tt>TRUE</tt> otherwise.
 */
  CATBoolean SetScale (const double iScale);

/**
 * Returns the scale of <tt>this</tt> CATMathLine2D. 
 */
   double GetScale () const;


/**
 * Returns the CATMathPoint2D of <tt>this</tt> CATMathLine2D corresponding to a given 
 * parameter.
 */
   void EvalPoint (const double iParam,CATMathPoint2D & ioResult) const;

/**
 * Intersects <tt>this</tt> CATMathLine2D with another one.
 * @param ioParamOnOtherLine
 *   Parameter of the intersection point on <tt>iLine</tt>.
 * @param ioParamOnThis
 *   Parameter of the intersection point on <tt>this</tt> CATMathLine2D.
 * @return
 * <dl>
 * <dt><tt>0</tt>        <dd>if there is no intersection
 * <dt><tt>1</tt>        <dd>if there is an intersection
 * <dt><tt>2</tt>        <dd>if they are identical
 * </dl>
 */ 
	 int Intersect(const CATMathLine2D & iOtherLine, 
																double & ioParamOnOtherLine,
                                  double & ioParamOnThis) const;

/**
 * Returns the distance between <tt>this</tt> CATMathLine2D and a CATMathPoint2D.
 */
  double DistanceTo(const CATMathPoint2D & iPoint) const;

/**
 * Retrieves the projection of a CATMathPoint2D on <tt>this</tt> CATMathLine2D.
 * @param iPoint
 *   The point to project.
 * @param ioParamOnLine
 *   The parameter of the projected point on <tt>this</tt> CATMathLine2D. 
 */
   void Project(const CATMathPoint2D & iPoint, double & ioParamOnLine) const;

/**
 * Retrieves the projection of a CATMathPoint2D on <tt>this</tt> CATMathLine2D. 
 * @param iPoint
 *   The point to project.
 * @param ioResult 
 *   The projected point as a CATMathPoint2D. 
 */
   void Project( const CATMathPoint2D & iPoint, CATMathPoint2D & ioResult) const;


//=============================================================================
//- friend function
//=============================================================================
/**
 * @nodoc
 * @deprecated V5R20 Intersect
 */ 
  ExportedByCATMathematics friend int Intersect(const CATMathLine2D & iLine1, 
					   const CATMathLine2D & iLine2,
					   double & oParamOnLine1,
                                           double & oParamOnLine2);

/**
 * @nodoc
 * @deprecated V5R20 DistanceTo
 */
  ExportedByCATMathematics friend double Distance(const CATMathPoint2D & iPoint,
					    const CATMathLine2D & iLine);

/**
 * @nodoc
 * @deprecated V5R20 Project
 */
  ExportedByCATMathematics friend void Projection(const CATMathPoint2D & iPoint,
					    const CATMathLine2D & iLine,
					    double & oParamOnLine);

/**
 * @nodoc
 * @deprecated V5R20 Project
 */
  ExportedByCATMathematics friend CATMathPoint2D Projection(
                            const CATMathPoint2D & iPoint,
			    const CATMathLine2D & iLine);

/**
 * @nodoc
 * @deprecated V5R20
 */
  CATMathLine2D (const CATMathPoint2D & iOrigin,
                 const CATMathDirection2D & iDirection);

/**
 * @nodoc
 * @deprecated V5R20 GetScale
 */
   double GetLength () const;

  /**
 * @nodoc
 * @deprecated V5R15 SetLineLength
 */
  void SetLength (const double iLength);

 /**
 * @nodoc
 * @return 
 * <tt>E_FAIL</tt> if the new length is null, <tt>S_OK</tt> otherwise.
 */
  HRESULT SetLineLength(const double iLength);

/**
 * @nodoc
 * @deprecated V5R20 GetDirection
 * Use the signature which returns  a CATMathVector2D as an output argument. 
 * Retrieves the (normalized) direction of <tt>this</tt> CATMathLine2D. 
 */
  CATMathDirection2D GetDirection () const;

/**
 * @nodoc
 * @deprecated V5R20 GetOrigin
 * Use the signature which returns a CATMathPoint2D as an output argument.
 * Returns the origin of <tt>this</tt> CATMathVector2D. 
 */
  CATMathPoint2D GetOrigin () const;

/**
 * @nodoc
 * @deprecated V5R20 EvalPoint
 * Use the  signature which returns a CATMathPoint2D as an output argument.
 * Returns the CATMathPoint2D of <tt>this</tt> CATMathLine2D corresponding to a given 
 * parameter. 
 */
  CATMathPoint2D EvalPoint (const double iParam) const;

 /**
 * @nodoc
 * @deprecated V5R20 SetLineDirection
 * Modifies the direction of <tt>this</tt> CATMathLine2D.
 */
  void SetDirection (const CATMathDirection2D & iDirection);

 /**
 * Dumps <tt>this</tt> CATMathLine2D.
 * <br>This writes the following lines on the ostream:
 *<pre>
 * Origin    = ( OriginFirstCoord , OriginSecondCoord )
 * Direction = ( DirFirstCoord    , DirSecondCoord )
 * </pre>
 * @param iStream  
 * A pointer to the output. If <tt>0L</tt>, the method dumps the 
 * coordinates on the <tt>cout</tt> output.
 */
    void Dump(ostream * iStream=0L) const;


//=============================================================================
//- Private data
//=============================================================================
 private :
	 // normalized vector
  CATMathVector2D _FirstAxis;
  CATMathPoint2D _Origin;
  double _Scale;

};

#endif
