#ifndef CATIPGMTwistAnalysis_h_
#define CATIPGMTwistAnalysis_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
//#include "CATIPGMOperator.h"
#include "CATIPGMGeoOperator.h"
#include "CATCollec.h"

class CATGeoFactory;
class CATMathFunctionXY;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;
class CATSurface;
class CATGeoOpTimer;
class CATSurLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTwistAnalysis;

// Q48 26/01/22: Migration to derive from CATGeoOperator
class ExportedByCATGMModelInterfaces CATIPGMTwistAnalysis: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTwistAnalysis();

  /**
   * See usage notes above for details.
   */
  virtual void SetCurvatureThreshold(double iCurvatureThreshold = 1.e3) = 0;

  /**
   * In SetCurvatureThreshold mode, specifies that the caller wants to know
   * the maximal curvature computed at potentially twisted points (see usage notes
   * above).
   */
  virtual void SetRecordMaxCurvature() = 0;

  virtual CATBoolean IsTwisted() /*const*/ = 0;

  /**
   * Returns 0 if not relevant, 1 otherwise.
   * The result is relevant only if the following conditions are fulfilled :
   *  - CurvatureThreshold and RecordMaxCurvature modes have been set up
   *  - IsTwisted has returned FALSE
   *  - Sufficient CGMLevel ( >= 96 )
   * In this case, retrives the maximal curvature computed. This is a
   * positive value not greater than the specified threshold.
   */
  virtual CATBoolean GetMaxCurvature(double &MaxCurvature) = 0;

  /**
   * Only for debug, or visual diagnostic : 
   *  Retrieves one point where the surface is twisted.
   * The stability of this method is NOT guaranteed.
   */
  virtual void GetTwistUV(double &u, double &v) = 0;

  /*
   *  Set the Multi Twist Option
   */
  virtual void SetSearchAllTwist(CATBoolean iFindAllTwist = TRUE) = 0;

  /**
   *  Retrieves All Twist.
   *  The stability of this method is guaranteed. 
   *  but not the order of solutions
   */
  virtual void GetTwistUVs(CATBoolean &oReliable, CATListOfDouble &uv) = 0;

  // Optimized grid evaluation activation
  // CAUTION: depending on the way grid evaluations are implemented in received functions,
  //  results may be different with optimization.
  //  ==> call to SetActiveOptimizedGridEval() must be managed by SoftwareConfiguration
  virtual void SetActiveOptimizedGridEval(int iActiveOptimizedGridEval = 1) = 0;

  // Optimized minimization (with direct minimizer) activation
  // CAUTION: depending on minimization behaviour,
  //  results may be different with optimization.
  //  ==> call to SetActiveOptimizedGridEval() must be managed by SoftwareConfiguration
  virtual void SetDirectMode(int iDirectMode = 1) = 0;

  // hln28032014
  // Tips process activation (default). 
  virtual void SetTipsProcess(int iTipsProcess = 1) = 0;

  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  //-----------------------------------------------------------------------
  //- Gestion timer 
  //-----------------------------------------------------------------------  
  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTwistAnalysis(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTwistAnalysis *CATPGMCreateTwistAnalysis(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATSurface *iSurface,
  const CATSurLimits &iSurLim);

// the constructor with no CATSoftwareConfiguration always plays
// the latest version
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTwistAnalysis *CATPGMCreateTwistAnalysis(
  CATGeoFactory *iFactory,
  CATSurface *iSurface,
  const CATSurLimits &iSurLim);

#endif /* CATIPGMTwistAnalysis_h_ */
