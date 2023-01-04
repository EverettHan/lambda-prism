#ifndef CATIPGMPositionPtLoop_h_
#define CATIPGMPositionPtLoop_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMGeoOperator.h"
#include "CATDataType.h"

class CATGeoFactory;
class CATMathFunctionX;
class CATMathInterval;
class CATPCurve;
class CATPointOnCurve;
class CATSoftwareConfiguration;
class CATSurParam;
class CATSurface;
class CATSurLimits;
class CATCrvParam;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMPositionPtLoop;

class ExportedByCATGMModelInterfaces CATIPGMPositionPtLoop: public CATIPGMGeoOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPositionPtLoop();

  //-----------------------------------------------------------------------
  //- Public methods
  //-----------------------------------------------------------------------

  //NLD051208 Run() inconditionnel au lieu de CATCGMOperatorDebugDeclareRun(CATIPGMPositionPtLoop, CATIPGMGeoOperator);
  virtual int Run() = 0;

  virtual void SetBoxUV(CATSurLimits &iBoxUV) = 0;

  virtual CATLONG32 GetPosition() const = 0;

  // If the point was found on frontier, return the pcurve index and the param on this pcurve
  virtual void GetPositionOnFrontier(CATLONG32 &oPCrvIndex, CATCrvParam &oCrvParam) const = 0;

  // If the point was found on frontiers, return the pcurve indexes and the params on these pcurves
  // +  oNbPCurves is equal to the number of PCurves on which lie the point
  // +  oPCrvIndex is an array of size oNbPCurves, and oPCrvIndex[i] represents the index of the i-th PCurve
  //    including the point
  // +  oCrvParam is an array of size oNbPCurves, and oCrvParam[i] represents the parameter on the i-th PCurve
  //    including the point
  //
  // Note : when oNbPCurves>0, the arrays oPcrvIndex and oCrvParam should be deleted by the caller.
  virtual void GetPositionOnFrontiers(
    CATLONG32 &oNbPCurves,
    CATLONG32 *&oPCrvIndex,
    CATCrvParam *&oCrvParam) const = 0;

  // Methode speciale pour booleen : renvoie true si le point a ete trouve frontiere sur un trou 
  // Spec validite avec ice/xdt le 30/04/02 a 15h43 : le point est dans le trou s'il est a plus de la 
  // resolution de ses deux extremites (sinon, il sera considere dans un vertex)
  // oGapIndex contient l'index de la PCurve qui precede le trou (dans l'ordre passe dans le constructeur)
  virtual CATBoolean IsInGap(CATLONG32 &oGapIndex) = 0;

  // Methode speciale pour booleen : renvoie true si le point a ete trouve frontiere sur un vertex
  // extremite oGapIndex contient l'index de la PCurve qui precede le trou (dans l'ordre passe dans le constructeur)
  virtual CATBoolean IsInVertex() = 0;

  // When the point is in, return 1 is the loop is positively oriented, -1 is negatively oriented
  // return 0 is GetPosition did not return 1
  virtual CATLONG32 GetOrientation() = 0;

  virtual void SetSurParam(const CATSurParam &iSurParam) = 0;

  virtual void SetTolerance(double &iTol) = 0;

  /**
  *  @nodoc  
  *  Returns  the  Software  configuration  to  be  taken
  *  into  acccount  by  <tt>this</tt>  operator.
  *  @return  
  *  The  Software  configuration.
  */
  virtual CATSoftwareConfiguration *GetSoftwareConfiguration() const = 0;

  /**
  *  @nodoc  
  *  Keep extra data for optimisation
  * iopti = TRUE  : Data are kept for improving multirun performance
  *       = FALSE : No extra data are kept
  * Before Calling SetMultiRunOptimization, the otimization is OFF
  */
  virtual void SetMultiRunOptimization(CATBoolean iOpti = TRUE) = 0;

  virtual CATGeoOpTimer *GetTimer() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPositionPtLoop(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
  CATGeoFactory *iFactory,
  const CATSurParam &iSurParam,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam);

// Don't use anymore
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
  CATGeoFactory *iFactory,
  const CATSurParam &iSurParam,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam,
  const double iTol3D);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iSurParam,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMPositionPtLoop *CATPGMCreatePositionPtLoop(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  const CATSurParam &iSurParam,
  const CATLONG32 iNbPCrv,
  const CATPCurve **iPCrv,
  const CATCrvParam *iStartParam,
  const CATCrvParam *iEndParam,
  const double iTol3D,
  const CATBoolean iCopyInputParameter = TRUE);

#endif /* CATIPGMPositionPtLoop_h_ */
