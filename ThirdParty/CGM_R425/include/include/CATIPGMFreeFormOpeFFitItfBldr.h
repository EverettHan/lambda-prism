#ifndef CATIPGMFreeFormOpeFFitItfBldr_h
#define CATIPGMFreeFormOpeFFitItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATFitting;
class CATMathSetOfPointsNDTwoTangents;
class CATGeoFactory;
class CATFrFNurbsMultiForm;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMFreeFormOpeFFitItfBldr;

/**
 * Factory of implementations of CGM interfaces for the framework FreeFormOperators,
 * dedicated to the module CATFreeFormOperatorsFFit.m.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMFreeFormOpeFFitItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:
  virtual CATFitting *CATPGMCreateFitting(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATMathSetOfPointsNDTwoTangents *iPoints,
    CATLength iFtittingTol,
    CATSkillValue mode
    ) = 0;

  virtual CATFitting *CATPGMCreateFitting(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration* iConfig,
    CATMathSetOfPointsNDTwoTangents *iPoints,
    CATLength iFtittingTol,
    CATLONG32 iDegree,
    CATFrFNurbsMultiForm *iPtr,
    CATSkillValue mode
    ) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework FreeFormOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMFreeFormOpeFFitItfBldr *CATCGMGetFreeFormOpeFFitItfBldr();

#endif /* CATIPGMFreeFormOpeFFitItfBldr_h */
