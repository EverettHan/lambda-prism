#ifndef CATCone_h
#define CATCone_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATMathDef.h"
class    CATMathPoint;
class    CATMathAxis;
#include "CATElementarySurface.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCone ;
#else
extern "C" const IID IID_CATCone ;
#endif

/**
 * Interface representing a geometric cone. Only right circular cones are supported.
 * <br> The CATCone is created by the <tt>CreateCone</tt>
 * method of the <tt>CATGeoFactory</tt> interface and deleted with the <tt>Remove</tt> method.
 * <br>A cone is defined by:
 * <ul>
 * <li>a CATMathAxis in which:
 * <ul>
 * <li>the third direction is the cone direction
 * <li>the first and second directions define the P plane on which relies the base radius.   
 * </ul>
 * <li>an external cone angle (CATAngle) expressed in radians. Legal values: <tt>0 < ConeAngle < Pi/2</tt>.
 * <li>a start angle in radians measured from the first direction of the cone axis. 
 * <li>an end angle in radians  measured from the first direction of the cone axis. 
 * This end angle must be greater than the start angle.
 * <li>a low limit of the cone length. This limit is the <b>slant height</b> counted from the 
 * P plane on which relies the base radius. Note that this 
 * limit is not counted along the cone axis.
 * <li>a high limit of the cone length. This limit is the <b>slant height</b> counted from the 
 * P plane on which relies the base radius. Note that this 
 * limit is not counted along the cone axis. The values of the low and high limits
 * must be such that the generated surface remains bounded by the apex. Double cones (two cones
 * placed apex to apex) are not supported.
 * </ul>
 * Note: <br>
 * The CATCone is parameterized by the arc length (first direction U) of the
 * mean circular section and the chord length (second direction V) along a 
 * ruling.
 * <pre>
 * C(U,V) = Origin +
 *  (StartRadius + L * cos(ConeAngle))*(cos(theta)*OX + sin(theta)*OY)
 *  +  L * sin(ConeAngle) * OZ 
 *  where U = UScale * theta and L is the rule-length, L = LenScale*V.
 * </pre>
 */
class ExportedByCATGMGeometricInterfaces CATCone : public CATElementarySurface
{
  CATDeclareInterface;

public:

/**
 * Returns the angle of <tt>this</tt> CATCone.
 * @return
 * The external cone angle.
 */
  virtual CATAngle    GetConeAngle() const = 0;

/**
 * Returns the radius in the plane defined by the first and second 
 * directions of the cone axis. 
 * @return 
 * The base radius on the plane defined by the first and second 
 * directions of the cone axis. 
 */
  virtual double   GetStartRadius() const = 0;

/**
 * Returns the low limit of the circle arc of <tt>this</tt> CATCone.
 * @return
 * The low limit of the circle arc.
 */
  virtual CATAngle    GetStartAngle() const = 0;

/**
 * Returns the high limit of the circle arc of <tt>this</tt> CATCone.
 * @return
 * The high limit of the circle arc.
 */
  virtual CATAngle    GetEndAngle() const = 0;

/**
 * Returns the low limit of the <b>slant height</b> of <tt>this</tt> CATCone.
 * @return
 * The low limit of the <b>slant height</b>. Note that this 
 * limit is not counted along the cone axis.
 */
  virtual double   GetStartRuleLength() const = 0;

/**
 * Returns the high limit of the <b>slant height</b> of <tt>this</tt> CATCone.
 * @return
 * The high limit of the <b>slant height</b>. Note that this 
 * limit is not counted along the cone axis.
 */
  virtual double   GetEndRuleLength() const = 0;

/**
 * Retrieves the scale on the circular direction of <tt>this</tt> CATCone.
 * @return 
 * The scale: <tt>U = UScale * theta</tt>, in which <tt>theta</tt> is the angle measured
 * on the MeanCircularSection, with theta(OX)=0 and theta(OY)=Pi/2.
 */
  virtual double      GetUScale() const = 0;

/**
 * Modifies the scale on the circular direction of <tt>this</tt> CATCone.
 * @param iNewUScale
 * The scale.
 */
  virtual void        SetUScale(const double iNewUScale) = 0;

/**
 * Retrieves the scale along the rule-lines of <tt>this</tt> CATCone.
 * @return
 * The scale. This starts as 1.0, so that V measures rule-length.  However,
 * to preserve parametrization under dilations, it may be changed.
 */
  virtual double      GetVScale() const = 0;

/**
 * Modifies the scale along the rule-lines of <tt>this</tt> CATCone.
 * @param iNewVScale
 * The new scale.
 */
  virtual void        SetVScale(const double iNewVScale) = 0;

/**
 * Retrieves the shift along the rule-lines of <tt>this</tt> CATCone.
 * @return
 * The shift. This starts as 0.0, so that V measures rule-length from the
 * ex-ey plane of the CATMathAxis.  However,
 * to preserve parametrization under offsets, it may be changed.
 * In particular, positive offsets can be handled without the shift,
 * but a large enough negative offset requires a shift in V in order
 * to avoid a negative StartRadius.
 */
  virtual double      GetVShift() const = 0;

/**
 * Modifies the shift along the rule-lines of <tt>this</tt> CATCone.
 * @param iNewVScale
 * The new shift.
 */
  virtual void        SetVShift(const double iNewVScale) = 0;

 /**
 * Returns the angle between <tt>this</tt> cone and its axis third direction.
 * @return
 * The angle value.
 */
  virtual CATAngle          GetSemiAngle()   const = 0;

/**
 * Returns the apex of <tt>this</tt> CATCone.
 * @param ioPoint
 * The mathematical definition of the apex.
 */
  virtual void GetApex(CATMathPoint & ioPoint)        const = 0;

/** @nodoc */
  virtual CATMathPoint      GetApex()        const = 0;

/**
 * Returns the radius of the circular cross-section of <tt>this</tt> cone
 * at the input V-value.
 * @param iVval
 * The parameter value in the V direction.
 * @return
 * The corresponding radius value.
 */
  virtual  double  GetRadiusAtV(const double iVval)   const=0;

};

CATDeclareHandler(CATCone,CATElementarySurface);

#endif


