#ifndef CATIPGMTopFRRRadiusComputationOpe_h_
#define CATIPGMTopFRRRadiusComputationOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMOperator.h"

class CATBody;
class CATGeoFactory;
class CATMathInterval;
class CATSoftwareConfiguration;
class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopFRRRadiusComputationOpe;

/**
 * Class defining the operator to compute the radius of a Body LOOKING LIKE a Fillet.
 * <br>
 * User should:
 * <ul>
 *<li> Create the operator with the <tt>CATPGMCreateTopFRRRadiusComputationOpe</tt>
 * global function, which defines the shell to treat.
 *<li> Run the operator with the <tt>Run</tt> method. In case of any failing treatment, the <tt>Run</tt>
 * method returns an integer error status different from 0:
 *
 *<li> Get the result Radius <tt>GetResult</tt> method.
 * The result Body should Contain Two domains which you explode in 2 Body.
 * In case of a NOT NULL error status from the <tt>Run</tt> method, the result body is the input body.
 *<li> Delete the operator with the usual C++ <tt>delete</tt> operator.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRRadiusComputationOpe: public CATIPGMOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopFRRRadiusComputationOpe();

  //To CAll AFTER run
  /**
  * Get The average Radius of the Body
  */
  virtual void GetEstimatedRadius(double &oRadius) = 0;

  /**
  * Get The Interval of All Radius Found in the Body
  * Warning ! The center of the interval is different from the EstimatedRadius
  */
  virtual void GetRadiusInterval(CATMathInterval &oInterval) = 0;

  /**
  * Give the operator opinion on the nature of the Body/Face
  */
  virtual CATBoolean IsFillet() = 0;

  /**
  * Get a more expansed Error message if run failed
  * The returned Error could be NULL if no Error has been detected
  * The Caller must managed the Error lifecycle and delete it
  */
  virtual void GetError(CATError *&Error) = 0;

  /*
  * Ask for the calculation of the mean Curvature vector (may take a little bit longer to compute when this option is on)
  */
  virtual void SetComputeMeanCurvatureVector() = 0;

  /*
  * Get an estimation of the mean Curvature vector of the fillet not that 1./oMeanCurv.Norm() may be slightly different 
  * from the GetEstimatedRadius value
  */
  virtual void GetComputeMeanCurvatureVector(CATMathVector &oMeanCurv) const = 0;

  /**
  * Force the operator to compute a Radius even if the surface (Fillet,Cylinder) can give the exact radius
  */
  virtual void SetNoUseOfNativeSurfaceType() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopFRRRadiusComputationOpe(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopFRRRadiusComputationOpe *CATPGMCreateTopFRRRadiusComputationOpe(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftConfig,
  CATBody *iShellBody);

#endif /* CATIPGMTopFRRRadiusComputationOpe_h_ */
