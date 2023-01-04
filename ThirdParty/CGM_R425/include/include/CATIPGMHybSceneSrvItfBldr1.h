#ifndef CATIPGMHybSceneSrvItfBldr1_h
#define CATIPGMHybSceneSrvItfBldr1_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATCollec.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"

class CATIPGMHLROperator;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathPlane;
class CATICGMHLROperator;
class CATPlane;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybSceneSrvItfBldr1;

/**
 * Factory of implementations of CGM interfaces for the framework HybridSceneServices.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMHybSceneSrvItfBldr1: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATICGMHLROperator *CATCGMCreateHLROperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATICGMHLROperator *CATCGMCreateHLROperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathPlane const &iProjectionPlane) = 0;

  virtual CATIPGMHLROperator *CATPGMCreateHLROperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig) = 0;

  virtual CATIPGMHLROperator *CATPGMCreateHLROperator(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATMathPlane const &iProjectionPlane) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework HybridSceneServices.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMHybSceneSrvItfBldr1 *CATCGMGetHybSceneSrvItfBldr1();

#endif /* CATIPGMHybSceneSrvItfBldr1_h */
