#ifndef CATIPGMSweep2_h_
#define CATIPGMSweep2_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATBoolean.h"
#include "CATMathDef.h"
#include "CATSweepLimitDef.h"
#include "CATBooleanType.h"

class Brep;
class CATBody;
class CATCGMJournalList;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATDomain;
class CATEdge;
class CATPGMExtruder;
class CATGeoFactory;
class CATGeometry;
class CATMathPlane;
class CATPCurve;
class CATShell;
class CATSurLimits;
class CATSweep;
class CATSweep2Body;
class CATSweep2EdgeInfo;
class CATSweep2FaceFaceInterResult;
class CATSweep2FaceInfo;
class CATSweep2MarchingEdge;
class CATSweep2MarchingInit;
class CATSweep2Parallel;
class CATSweep2Ribbon;
class CATSweep2Shell;
class CATSweep2TransferInfo;
class CATSweep2TransferOnEdgeInfo;
class CATSweepBRep;
class CATSweepSpec;
class CATIPGMTopBooleanOperator;
class CATIPGMTopologicalOperator;
class CATWire;
class Spec;
class CATLISTP(CATDomain);
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSweep2;

//=============================================================================
class ExportedByCATGMOperatorsInterfaces CATIPGMSweep2: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSweep2();

  virtual int Run() = 0;

  virtual CATSweep *GetSweepOperator() = 0;

  virtual CATBody *GetResult() = 0;

  virtual void SetDiscontinuityTreatment(CATLONG32 iMode = 0) = 0;

  virtual void SetCuspTreatment(CATLONG32 iMode = 0) = 0;

  //----------------------------------------------------------------------
  // >>> METHODES SPECIFIQUES DE CATSWEEP, TRANSMISES DIRECTEMENT A _SWEEP
  //  CATBody * GetProfile();
  //  CATBody * GetCenter();
  virtual CATBoolean InvariantResult() = 0;

  virtual CATBody *GetBooleanResult() = 0;

  virtual CATCGMJournalList *GetBooleanTopReport() = 0;

  virtual void UnsetCheckTopoTwist(CATBoolean iUnsetCheckTopoTwist = CATBoolean(1)) = 0;

  virtual void SetOldShapeRequested() = 0;

  virtual void SetRelimitationMode(short iMode, short iAutomaticDirectionInversion = 1) = 0;

  virtual void SetReversePolarity(CATBoolean iPolarity) = 0;

  virtual void GetReversePolarity(CATBoolean &oPolarity) = 0;

  virtual void SetSimplification(CATBoolean iSimplify) = 0;

  virtual void SetFreezeMode(CATBoolean iFreezeMode) = 0;

  virtual void SetLimit(
    CATLimit iId,
    CATLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATGeometry *iLimit,
    CATBody *iPropagationBody,
    CATPropagationType iPropagationFlag,
    CATBoolean iIsThickness) = 0;

  virtual void SetLimit(
    CATLimit iId,
    CATLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATLISTP(CATCell) &iLimit,
    CATBody *iPropagationBody,
    CATPropagationType iPropagationFlag,
    CATBoolean iIsThickness) = 0;

  virtual void SetVirtualBoolean() = 0;

  virtual void SetBothResult() = 0;

  virtual void SetBoolean(CATBoolType iBoolType, CATBody *iTrimBody) = 0;

  virtual void SetProfileClosure(CATBoolean iToClose, CATBody *iTrimBody) = 0;

  virtual void SetThinSolidMode(
    const CATBoolean iThinSolidMode,
    const CATBoolean iIsNeutralFiber,
    const double iThinSolidThickness[2],
    CATLISTP(CATDomain) *iWireListWithReverseThinSolidSide) = 0;

  virtual void SetRefPlane(CATMathPlane &iRefPlane) = 0;

  virtual CATBoolean IsBothResult() = 0;

  virtual void SetTwistReduction(CATBoolean iTwistReduction = 0) = 0;

  virtual void GetTwistReduction(CATBoolean &oTwistReduction) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSweep2(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMSweep2 *CATPGMCreateSweep2(
  CATGeoFactory *iGeoFactory,
  CATTopData *iTopData,
  CATBody *iProfBody,
  CATBody *iCntBody,
  CATPGMExtruder *iExtruder);

#endif /* CATIPGMSweep2_h_ */
