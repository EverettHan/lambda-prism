#ifndef CATICGMLocalAnalysis1D_h_
#define CATICGMLocalAnalysis1D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"

class CATSoftwareConfiguration;
class CATCrvParam;
class CATCurve;
class CATMathVector;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMLocalAnalysis1D;

/**
 * Class defining the local analysis on a point of a CATCurve.
 * <br>It performs curvature, torsion,
 * main normal and binormal on a point of a CATCurve. This class is not streamable.
 * The point where the analysis is done can be changed by @href CATICGMLocalAnalysis1D#SetParam.
 */
class ExportedByCATGMModelInterfaces CATICGMLocalAnalysis1D: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMLocalAnalysis1D();

  /**
 * Returns the curvature at the point of <tt>this</tt> CATICGMLocalAnalysis1D.
 * @return
 * The curvature : the norm of the cross product of the first derivative and the second derivative 
 * divided by the cube of the norm of the first derivative.
 * <br><tt>Curvature = (FirstDeriv^SecondDeriv).Norm() / (FirstDeriv.Norm())^3</tt>.
 */
  virtual double GetCurvature() = 0;

  /**
 * Returns the torsion at the point of <tt>this</tt> CATICGMLocalAnalysis1D.
 * @return
 * The torsion: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>Torsion = V*ThirdDeriv / V*V</tt>, where <tt>*</tt> is the dot product and <tt>^</tt> the cross 
 * product.
 */
  virtual double GetTorsion() = 0;

  /**
 * Tests whether the point of <tt>this</tt> CATICGMLocalAnalysis1D is regular.
 * <br>A point is non regular when the partial derivative of one of its coordinate 
 * is null.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt><tt> 0 </tt> <dd> if it is not regular
 *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
 */
  virtual CATLONG32 IsARegularParam() = 0;

  /**
 * Returns the main normal at the point of <tt>this</tt> CATICGMLocalAnalysis1D.
 * @return
 * The main normal: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>MainNormal = (V / V.Norm() ) ^ FirstDeriv / FirstDeriv.Norm() </tt>, where <tt>^</tt> is the cross 
 * product.
 */
  virtual CATMathVector GetMainNormal() = 0;

  /**
 * Returns the binormal at the point of <tt>this</tt> CATICGMLocalAnalysis1D.
 * @return
 * The binormal: Let <tt>V = FirstDeriv ^ SecondDeriv</tt>. Then,
 * <br><tt>BiNormal = V / V.Norm() </tt>, where <tt>^</tt> is the cross 
 * product.
 */
  virtual CATMathVector GetBiNormal() = 0;

  /**
 * Modifies the point where <tt>this</tt> CATICGMLocalAnalysis1D is performed.
 * <br>The analysis is automatically done.
 * @param iNewParamToAnalyze
 * The parameter of the new point to analyze.
 */
  virtual void SetParam(CATCrvParam &iNewParamToAnalyze) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMLocalAnalysis1D(); // -> delete can't be called
};

/**
* Creates a local analyzer on a point of a CATCurve.
* @param iConfig
* The level of code (Versionning).
* @param iSupport
* The curve on which the analysis is done.
* @param iPointToAnalyze
* The parameter on <tt>iSupport</tt> of the point to analyze.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis1D(
  CATSoftwareConfiguration *iConfig,
  const CATCurve *iSupport,
  const CATCrvParam &iPointToAnalyze);

/**
* Creates a local analyzer on a point of a CATCurve.
* @param iSupport
* The curve on which the analysis is done.
* @param iPointToAnalyze
* The parameter on <tt>iSupport</tt> of the point to analyze.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis1D *CATCGMCreateLocalAnalysis1D(
  const CATCurve *iSupport,
  const CATCrvParam &iPointToAnalyze);

#endif /* CATICGMLocalAnalysis1D_h_ */
