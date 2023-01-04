#ifndef CATIPGMTryConfusionCrvCrv_h_
#define CATIPGMTryConfusionCrvCrv_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"

class CATCurve;
class CATEdgeCurve;
class CATGeoFactory;
class CATMathSetOfPointsND;
class CATPointOnCurve;
class CATPointOnEdgeCurve;
class CATSoftwareConfiguration;
class CATCrvParam;
class CATCrvLimits;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTryConfusionCrvCrv;

/**
 * Class defining the operator that computes the overlapping zones between two curves.
 *<br>Two curves are overlapping within a given tolerance if their
 * Haussdorf distance <tt>dH</tt> is less than this tolerance.<br>
 * <pre>
 * dH= MAX [ Max{Point1 in Curve1}Min{Point2 in Curve2} distance(Point1,Point2),
 *           Max{Point2 in Curve2}Min{Point1 in Curve1} distance(Point1,Point2) ]</pre>
 *<ul>
 *<li>The CATIPGMTryConfusionCrvCrv is not streamable. 
 *<li>After its creation, run it with the <tt>Run</tt> method. 
 * Then, you access the results by the mean of an iterator. <tt>Release</tt> it after use. 
 *</ul>
 */
class ExportedByCATGMModelInterfaces CATIPGMTryConfusionCrvCrv: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTryConfusionCrvCrv();

  virtual void Run2() = 0;

  /**
  * Runs the operator.
  */
  // non necessaire car Run() toujours declare:
  // CATCGMOperatorDebugDeclareRun(CATIPGMTryConfusionCrvCrv, CATIPGMGeoOperator);
  virtual int Run() = 0;

  /**
	 * Initializes the iterator of the overlapping zones.
	 */
  virtual void BeginningConfusion() = 0;

  // Return 0 if no confusion exists, 1 else
  virtual CATBoolean GetConfusion() = 0;

  virtual CATBoolean NextConfusion() = 0;

  // Return 0 if no confusion exists, return a merged curve if a confusion exists
  virtual CATEdgeCurve *GetEdgeCurve() = 0;

  virtual CATEdgeCurve *GetEdgeCurve(
    CATPointOnEdgeCurve *&oStart,
    CATPointOnEdgeCurve *&oEnd) = 0;

  // Return the params limits of the confusion on a given curve (_Crv1 or _Crv2)
  virtual void GetConfusionLimits(CATCurve *iCrv, CATCrvParam &oStart, CATCrvParam &oEnd) = 0;

  virtual void GetConfusionLimits(CATCurve *iCurve, CATCrvLimits &oLimits) = 0;

  virtual void GetFirstConfusionParam(CATCrvParam &Param1, CATCrvParam &Param2) = 0;

  virtual void GetSecondConfusionParam(CATCrvParam &Param1, CATCrvParam &Param2) = 0;

  virtual void SetParamIncl(CATCrvParam Param1[4],CATCrvParam Param2[4][2],CATLONG32 NbInclusion[4], int NbSol) = 0;

  virtual void SetDetectInvalidMergedCurve() = 0;

  // If a confusion exists, this option allows to create a merged curve whose
  // RefCurve will be stable whatever input swapping of iCrv1 and iCrv2
  virtual void SetStableRefCurve(CATBoolean iEnable = TRUE) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTryConfusionCrvCrv(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(CATGeoFactory *);

//Do not use - EAB - 10/09/04
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(
  CATGeoFactory *iWhere,
  CATCurve *iCrv1,
  const CATCrvLimits &iLimits1,
  CATCurve *iCrv2,
  const CATCrvLimits &iLimits2,
  const double iTolerance);

/**
	* Constructs a CATTryCOnfusionCrvCrv.
	* @param iWhere
  * The pointer to the factory of the curves.
	* @param iCrv1
	* The pointer to the first curve.
	* @param iLimits1
	* The limitations of <tt>iCrv1</tt> to take into account.
	* @param iCrv2
	* The pointer to the secong curve.
	* @param iLimits2
	* The limitations of <tt>iCrv2</tt> to take into account. 
	* @param iTol
  * The maximum Haussdorf distance for deciding the overlap.
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTryConfusionCrvCrv *CATPGMCreateTryConfusionCrvCrv(
  CATGeoFactory *iWhere,
  CATSoftwareConfiguration *iConfig,
  CATCurve *iCrv1,
  const CATCrvLimits &iLimits1,
  CATCurve *iCrv2,
  const CATCrvLimits &iLimits2,
  const double iTolerance);

#endif /* CATIPGMTryConfusionCrvCrv_h_ */
