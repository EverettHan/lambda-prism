#ifndef CATICGMReflectCurve_h_
#define CATICGMReflectCurve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMGeoOperator.h"
#include "CATBoolean.h"
#include "CATDataType.h"
//#include "CATReflectCurveSign.h"

class CATCurve;
class CATGeometry;
class CATPCurve;
class CATPlane;
class CATSurface;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMReflectCurve;

/**
* Class defining the operator to compute the reflect curves on a surface.
* <br>The reflect curves are the set of points of a surface such that the surface normal 
* at these points and a direction defines a constant angle.
* <ul>
* <li>The CATICGMReflectCurve operator is created with the <tt>CATCGMCreateReflectCurve</tt> method and 
* directly released with the <tt>Release</tt> method.
* It is is not streamable. 
*<li>In case of <tt>BASIC</tt>
* mode, the operation is automatically performed at the operator creation. 
* In case of <tt>ADVANCED</tt>
* mode, options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
* run the same operator with different curves or surfaces.
* <li>In both cases, the result is accessed with specific interators.
* </ul>
*/
class ExportedByCATGMModelInterfaces CATICGMReflectCurve: public CATICGMGeoOperator
{
public:
  /**
  * Constructor
  */
  CATICGMReflectCurve();

  /**
  * Initializes the iterator of the solution curves of <tt>this</tt> 
  * CATICGMProjectionCrvSur operator.
  * <br>By default, the initialization is performed once the operator runs, 
  * and this is therefore only used to read the solutions again.
  */
  virtual void BeginningCurve() = 0;

  /**
  * Skips to the next solution curve of <tt>this</tt> CATICGMReflectCurve operator.
  * <br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
  * @return
  * The existence of the next solution.
  * <br><b>Legal values</b>:
  * <dl><dt><tt>TRUE</tt> <dd>if there is a solution point
  *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
  */
  virtual CATBoolean NextCurve() = 0;

  /**
  * Creates the next solution curve as a curve on surface.
  * @return
  * The pointer to the created curve on surface. A new curve is created each time this method is called.
  * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
  */
  virtual CATPCurve *GetPCurve() = 0;

  /**
  * Creates the next solution curve.
  * @return
  * The pointer to the created curve. A new curve is created each time this method is called.
  * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
  */
  virtual CATCurve *GetCurve() = 0;

  /**
  * Returns the number of solution curves.
  * @return
  * The number of curves.
  */
  virtual CATLONG32 GetNumberOfPCurves() const = 0;

  /**
  * Modifies the surface domain to take into account for <tt>this</tt> CATICGMReflectCurve
  * operator (<tt>ADVANCED</tt> mode).
  * <br>It does not change the current surface 
  * limitations.  
  * @param iLimits
  * The new limitations of the surface, <tt>NULL</tt> to take the current limitations.
  */
  virtual void SetLimits(CATSurLimits *iLimits) = 0;

protected:
  /**
  * Destructor
  */
  virtual ~CATICGMReflectCurve(); // -> delete can't be called
};

#endif /* CATICGMReflectCurve_h_ */
