#ifndef CATICGMLocalAnalysis2D_h_
#define CATICGMLocalAnalysis2D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMVirtual.h"
#include "CATDataType.h"

class CATMathDirection2D;
class CATSoftwareConfiguration;
class CATSurface;
class CATMathVector;
class CATSurParam;
class CATMathVector2D;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMLocalAnalysis2D;

/**
 * Class defining the local analysis on a point of a CATSurface.
 * <br>It performs curvature, torsion,
 * main normal and binormal on a point of a CATSurface. This class is not streamable.
 * The point where the analysis is done can be changed by @href CATICGMLocalAnalysis2D#SetParam.
 */
class ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMLocalAnalysis2D();

  /**
  * Retrieves the first fondamental form at the point of <tt>this</tt> CATICGMLocalAnalysis2D.
	* @param ioE
	* The first coordinate: <tt>ioE = FirstDerivU.Norm() ^ 2</tt>, where <tt>FirstDerivU</tt> is
	* the first derivative with regards to the first parameter.
	* @param ioF
	* The second coordinate: <tt>ioF = FirstDerivU * FirstDerivV</tt>, where <tt>*</tt> is the dot product.
	* @param ioE
	* The third coordinate: <tt>ioG = FirstDerivV.Norm() ^ 2</tt>, where <tt>FirstDerivV</tt> is
	* the first derivative with regards to the second parameter.
  */
  virtual void GetFirstFundamentalForm(double &ioE, double &ioF, double &ioG) = 0;

  /**
  * Retrieves the second fondamental form at the point of <tt>this</tt> CATICGMLocalAnalysis2D.
	* <br>Let <tt>H = (FirstDerivU ^ FirstDerivV) / (FirstDerivU ^ FirstDerivV).Norm()</tt>.
	* @param ioL
	* The first coordinate: <tt>ioL = SecondDerivU2 * H</tt>, where <tt>SecondDerivU2</tt> is
	* the second derivative with regards to the first parameter and <tt>*</tt> the dot product.
	* @param ioM
	* The second coordinate: <tt>ioM = SecondDerivUV * H</tt>,  where <tt>SecondDerivUV</tt> is
	* the second derivative with regards to the first parameter and second parameters, 
	* and <tt>*</tt> the dot product.
	* @param ioN
	* The third coordinate: <tt>ioN = SecondDerivU2 * H</tt>,  where <tt>SecondDerivV2</tt> is
	* the second derivative with regards to the second parameter and <tt>*</tt> the dot product.
  */
  virtual void GetSecondFundamentalForm(double &ioL, double &ioM, double &ioN) = 0;

  /**
  * Returns the gaussian curvature at the point of <tt>this</tt> CATICGMLocalAnalysis2D.
	* @return
  * The Gaussian curvature = <tt>Cmin*Cmax</tt>, where <tt>Cmin</tt> is the minium curvature
  * and <tt>Cmax</tt> the maximum curvature at the point of <tt>this</tt> analysis.
  */
  virtual double GetGaussianCurvature() = 0;

  /**
  * Returns the mean curvature at the point of <tt>this</tt> CATICGMLocalAnalysis2D.
	* @return
  * The mean curvature: <tt> = 0.5*(Cmin+Cmax) </tt>.
  */
  virtual double GetMeanCurvature() = 0;

  /**
  * Returns the min and max curvatures at the point of <tt>this</tt> CATICGMLocalAnalysis2D.
	* @param ioCmin
	* The minimum curvature.
	* @param ioCmax
	* The maximum curvature: <tt>ioCmin < ioCmax</tt>.
  */
  virtual void GetMinMaxCurvature(double &ioCmin, double &ioCmax) = 0;

  /**
  * Returns the min and max curvatures at the point of <tt>this</tt> CATICGMLocalAnalysis2D,
  * along with the associated principal curvature directions.
  * The returned 3d and 2d vectors represent directions: no assumption can be made
  * regarding the orientation of the vectors. Likewise, the directions are unspecified
  * at umbilical points (when min curvature = max curvature).
	* @param ioCmin
	* The minimum curvature.
	* @param ioCmax
	* The maximum curvature: <tt>ioCmin < ioCmax</tt>.
	* @param ioDirMin2D
  * The principal curvature direction associated to the minimal curvature,
  * expressed as a linear combination of the partial derivatives.
	* @param ioDirMax2D
  * The principal curvature direction associated to the maximal curvature.
  * expressed as a linear combination of the partial derivatives.
	* @param ioDirMin3D
  * The principal curvature direction associated to the minimal curvature,
  * expressed in 3D.
	* @param ioDirMax3D
  * The principal curvature direction associated to the maximal curvature,
  * expressed in 3D.
  */
  virtual void GetMinMaxCurvaturesAndDirections(
    double &ioCmin,
    double &ioCmax,
    CATMathVector2D &ioDirMin2D,
    CATMathVector2D &ioDirMax2D,
    CATMathVector &ioDirMin3D,
    CATMathVector &ioDirMax3D) = 0;

  /**
  * Returns the curvature along a direction of the surface.
  * @param iX
	* The first coordinate of the direction in the space of the surface.
	* @param iY
	* The second coordinate of the direction in the space of the surface.
	* @return 
	* The curvature.
	* <tt>C(iX,iY) = (L.iX^2+2M.iX.iY+N.iY^2) / (E.iX^2+2F.iX.iY+G.iY^2)</tt>, where <tt>L,M,N</tt> are
	* the coordinates of the second fundamental form and <tt>E, F, G</tt> the coordinates of the
	* first fundamental form
  */
  virtual double GetCurvatureAlongDirection(const double &iX, const double &iY) = 0;

  /**
  * Returns the 2D coordinates of the projection of the 3d vector <tt>iVector</tt> on the
  * surface. 
	* <br> These coordinates are such that: <tt>iVector = ioX*FirstDerivU + ioY*FirstDerivV</tt>,
	* where <tt>FirstDerivU</tt> and <tt>FirstDerivV</tt> are the first derivatives with respect to
	* the first and second surface parameters, and <tt>*</tt> is the dot product.
	* @param ioX
	* The coordinate along the first derivative with regards to the first surface parameter.
  * @param ioY
	* The coordinate along the first derivative with regards to the second surface parameter.
  * @return
	* The regularity of the point.
  *<dl><dt><tt> 0 </tt> <dd> if it is not regular (<tt>ioX</tt> and <tt>ioY</tt> are not calculated)
  *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
  */
  virtual CATLONG32 ProjectVector(CATMathVector &iVector, double &ioX, double &ioY) = 0;

  /**
 * Tests whether the point of <tt>this</tt> CATICGMLocalAnalysis2D is regular.
 *<br>A point is non regular when the partial derivative of one of its coordinate 
 * is null.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt><tt> 0 </tt> <dd> if it is not regular
 *    <dt><tt> 1 </tt> <dd> if it is regular</dl>
 */
  virtual CATLONG32 IsARegularParam() = 0;

  /**
 * Modifies the point where <tt>this</tt> CATLocalAnalysis2D is performed.
 *<br>The analysis is automatically done.
 * @param iNewParamToAnalyze
 * The parameter of the new point to analyze.
 */
  virtual void SetParam(const CATSurParam &iNewParamToAnalyze) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMLocalAnalysis2D(); // -> delete can't be called
};

/**
 * Creates a local analyzer on a point of a CATSurface.
 * @param iConfig
 * The level of code (Versionning).
 * @param iSupport
 * The surface on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
  CATSoftwareConfiguration *iConfig,
  const CATSurface *iSurface,
  const CATSurParam &iPointToAnalyze);

/**
 * Creates a local analyzer on a point of a CATSurface.
 * @param iSupport
 * The surface on which the analysis is done.
 * @param iPointToAnalyze
 * The parameter on <tt>iSupport</tt> of the point to analyze.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
  const CATSurface *iSurface,
  const CATSurParam &iPointToAnalyze);

/**
* Copy Constructor.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMModelInterfaces CATICGMLocalAnalysis2D *CATCGMCreateLocalAnalysis2D(
  const CATICGMLocalAnalysis2D &iAnalysisToCopy);

#endif /* CATICGMLocalAnalysis2D_h_ */
