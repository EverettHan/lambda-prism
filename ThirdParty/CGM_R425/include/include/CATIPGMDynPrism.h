#ifndef CATIPGMDynPrism_h_
#define CATIPGMDynPrism_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATDynOperatorDef.h"
#include "CATMathDef.h"

class CATBody;
class CATGeometry;
class CATMathDirection;
class CATPlane;
class CATLISTP(CATCurve);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynPrism;

class ExportedByCATGMOperatorsInterfaces CATIPGMDynPrism: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynPrism();

  virtual void SetLimit(
    CATDynLimit iId,
    CATDynLimitType iType,
    CATBoolean iIsAxisReverted,
    CATLength iOffset,
    CATGeometry *iInit,
    CATGeometry *iLimit,
    CATDynPropagationType iPropag) = 0;

  virtual void SetOperation(CATDynBooleanType iOperation = CATBoolNone) = 0;

  virtual void SetTrim(CATBody *iTrim = NULL) = 0;

  virtual void SetClosure(CATBoolean isProfileClosed) = 0;

  virtual void SetStiffenerMode(
    CATBoolean iStiffenerMode,
    CATBoolean iMatterSide) = 0;

  virtual void SetBothResult(CATBoolean iBothResultRequired) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynPrism(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynPrism *CATPGMDynCreatePrism(
  CATGeoFactory *Container,
  CATMathDirection *iDirection,
  const CATLISTP(CATCurve) &iProfile,
  CATPlane *iSupport,
  CATCGMJournalList *iJournal = NULL);

// Creation EntryPoints
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMDynPrism *CATPGMCreateDynPrism(
  CATGeoFactory *Container,
  CATTopData *iData,
  CATMathDirection *iDirection,
  const CATLISTP(CATCurve) &iProfile,
  CATPlane *iSupport);

#endif /* CATIPGMDynPrism_h_ */
