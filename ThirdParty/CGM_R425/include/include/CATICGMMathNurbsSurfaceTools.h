#ifndef CATICGMMathNurbsSurfaceTools_h_
#define CATICGMMathNurbsSurfaceTools_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATCollec.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATKnotVector;
class CATMathFunctionXY;
class CATMathGridOfPoints;
class CATSurface;
class CATLISTP(CATSurface);

extern ExportedByCATGMModelInterfaces IID IID_CATICGMMathNurbsSurfaceTools;

/**
 * Class defining the operator that creates a set of C2 Nurbs surfaces.
 * The CATICGMMathNurbsSurfaceTools operator is created with the <tt>CATCGMCreateMathNurbsSurfaceTools</tt> method and 
 * directly released with the <tt>Release</tt> method.
 */
class ExportedByCATGMModelInterfaces CATICGMMathNurbsSurfaceTools: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMMathNurbsSurfaceTools();

  /**
  * Retrieves the mathematical equation associated with
  * <tt>this</tt> CATICGMMathNurbsSurfaceTools.
  * <br><tt>(ioFx(U,V), ioFy(U,V), ioFz(U,V))</tt> is then a point of the surface.
  * The equations have to be deleted by user. 
  * @param oFx
  * Pointer to the parametric equation of the first coordinate. 
  * @param oFy
  * Pointer to the parametric equation of the second coordinate. 
  * @param oFz
  * Pointer to the parametric equation of the third coordinate.
  */
  virtual void GetGlobalEquation(
    CATMathFunctionXY *&oFx,
    CATMathFunctionXY *&oFy,
    CATMathFunctionXY *&oFz) const = 0;

  /**
  * Creates a set of Nurbs surfaces from a CATICGMMathNurbsSurfaceTools, the resulting
  * surfaces are at least C2.
  * @param iFactory
  * The geometry factory.
  * @param oListeOfSur
  * The resulting list of surfaces. The list is ordered as described below:
  * <tt>Sur(1,1), Sur(1,...),..., Sur(1,NbVSurfaces), Sur(2,1),..., Sur(NbUSurfaces,NbVSurfaces) </tt>
  * @param NbUSurfaces
  * The number of surfaces along U.
  * @param NbVSurfaces
  * The number of surfaces along V.
  */
  virtual void ConvertToC2NurbsSurfaces(
    CATGeoFactory *iFactory,
    CATLISTP(CATSurface) &oListeOfSur,
    int &NbUSurfaces,
    int &NbVSurfaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMMathNurbsSurfaceTools(); // -> delete can't be called
};

/**
 * Creates an operator for dividing a Nurbs surface into several C2 Nurbs surfaces.
 * @param iUKnotVector
 * The knot vector along U.
 * @param iVKnotVector
 * The knot vector along V.
 * @param iIsRational
 * <b>Legal values</b>:
 * <dl><dt><tt>0</tt><dd>if it is not rational.
 *    <dt><tt>1</tt><dd>if it is rational.</dl>
 * @param iVertices
 * The set of control points.
 * @param iWeights
 * The array of weights (one weight per control point).
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMMathNurbsSurfaceTools *CATCGMCreateMathNurbsSurfaceTools(
  const CATKnotVector &iUKnotVector,
  const CATKnotVector &iVKnotVector,
  const CATLONG32 &iIsRational,
  const CATMathGridOfPoints &iVertices,
  const double *iWeights);

#endif /* CATICGMMathNurbsSurfaceTools_h_ */
