#ifndef CATICGMMathNurbsCurveTools_h_
#define CATICGMMathNurbsCurveTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATCGMMathNurbsDimension.h"
#include "CATCollec.h"
#include "CATDataType.h"

class CATCurve;
class CATGeoFactory;
class CATKnotVector;
class CATMathFunctionX;
class CATMathSetOfPoints;
class CATPCurve;
class CATSurface;
class CATLISTP(CATPCurve);
class CATLISTP(CATCurve);

extern ExportedByCATGMModelInterfaces IID IID_CATICGMMathNurbsCurveTools;

/**
 * Class defining the operator that creates a set of C2 Nurbs curves.
 * The CATICGMMathNurbsCurveTools operator is created with the <tt>CATCGMCreateMathNurbsCurveTools</tt> method and 
 * directly released with the <tt>Release</tt> method.
 */
class ExportedByCATGMModelInterfaces CATICGMMathNurbsCurveTools: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMMathNurbsCurveTools();

  /**
  * Retrieves the mathematical equation associated with
  * <tt>this</tt> CATICGMMathNurbsCurveTools.
  * <br><tt>(ioFx(U,V), ioFy(U,V), ioFz(U,V))</tt> is then a point of the curve if dimension is Full3D.
  * <br><tt>(ioFx(U,V), ioFy(U,V))</tt> is then a point of the PCurve if dimension is LyingOn.
  * Note that in this case, ioFz is NULL.
  * The equations have to be deleted by the user. 
  * @param oFx
  * Pointer to the parametric equation of the first coordinate. 
  * @param oFy
  * Pointer to the parametric equation of the second coordinate. 
  * @param oFz
  * Pointer to the parametric equation of the third coordinate if dimension is Full3D, NULL otherwise. 
  */
  virtual void GetGlobalEquation(
    CATMathFunctionX *&oFx,
    CATMathFunctionX *&oFy,
    CATMathFunctionX *&oFz) const = 0;

  /**
  * Creates a set of Nurbs curves from a CATICGMMathNurbsCurveTools, the resulting
  * curves are at least C2.
  * @param iFactory
  * The geometry factory.
  * @param oListeOfCrv
  * The resulting list of curves. 
  */
  virtual void ConvertToC2NurbsCurves(
    CATGeoFactory *iFactory,
    CATLISTP(CATCurve) &oListeOfCrv) = 0;

  /**
  * Creates a set of PNurbs curves from a CATICGMMathNurbsCurveTools, the resulting
  * curves are at least C2.
  * @param iFactory
  * The geometry factory.
  * @param iSurface
  * The PNurbs support.
  * @param oListeOfCrv
  * The resulting list of curves. 
  */
  virtual void ConvertToC2PNurbs(
    CATGeoFactory *iFactory,
    CATSurface *iSurface,
    CATLISTP(CATPCurve) &oListeOfCrv) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMMathNurbsCurveTools(); // -> delete can't be called
};

/**
 * Creates an operator for dividing a Nurbs curve into several C2 Nurbs curves.
 * @param iKnotVector
 * The knot vector.
 * @param iIsRational
 * <b>Legal values</b>:
 * <dl><dt><tt>0</tt><dd>if it is not rational.
 *    <dt><tt>1</tt><dd>if it is rational.</dl>
 * @param iSetOfPoints
 * The set of control points.
 * @param iDimension
 * <dl><dt><tt>CATMathNurbsLyingOn: </tt> <dd> defines a 2D curve, 
 * only the first two coordinates specified in iSetOfPoints are used.
 * <dt><tt>CATMathNurbsFull3D: </tt><dd></dl> defines a 3D curve, the three coordinates are used.
 * @param iWeights
 * The array of weights (one weight per control point).
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMMathNurbsCurveTools *CATCGMCreateMathNurbsCurveTools(
  const CATKnotVector &iKnotVector,
  const CATLONG32 &iIsRational,
  const CATMathSetOfPoints &iSetOfPoints,
  const MathNurbsDimension &iDimension,
  const double *iWeights);

#endif /* CATICGMMathNurbsCurveTools_h_ */
