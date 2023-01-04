#ifndef CATIPGMGMScalarFieldsOperatorsItfBldr_h
#define CATIPGMGMScalarFieldsOperatorsItfBldr_h

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATMathDef.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATIAV5Level.h"

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGMScalarFieldsOperatorsItfBldr;

class CATGeoFactory;
class CATBody;
class CATFace;
class CATSoftwareConfiguration;
class CATIPGMFaceCurvatureAnalyzer;
#ifdef CATIAR424
class CATIPGMBuildExplicitPolyBodyTopOper;
class CATIPGMCreateLatticeNBTopOper;
class CATIPGMCloneImplicitBodyTopOper;
class CATIPGMCreateConformalGCLatticeTopOper;
class CATIPGMCreateConformalLatticeTopOper;
class CATIPGMCreateImplicitBodyTopOper;
class CATIPGMCreateTPMSTopOper;
class CATIPGMSmartDuplicateImplicitBodyTopOper;
#endif
class CATPGMVolumePartitionBodyToolKit;

/**
 * Factory of implementations of CGM interfaces for the framework GMPolyUtilities.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMGMScalarFieldsOperatorsItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

#ifdef CATIAR424
  virtual CATIPGMBuildExplicitPolyBodyTopOper* CATPGMCreateBuildExplicitPolyBodyTopOper(
    CATGeoFactory * iFactory,
    CATTopData * iTopData,
    CATBody * iBodyWithCavityToLattice) = 0;

  virtual  CATIPGMCreateLatticeNBTopOper* CATPGMCreateCreateLatticeNBTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMCloneImplicitBodyTopOper*  CATPGMCreateCloneImplicitBodyTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMCreateConformalGCLatticeTopOper* CATPGMCreateCreateConformalGCLatticeTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMCreateConformalLatticeTopOper* CATPGMCreateCATCreateConformalLatticeTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMCreateImplicitBodyTopOper* CATPGMCreateCreateImplicitBodyTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMCreateTPMSTopOper* CATPGMCreateCreateTPMSTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

  virtual CATIPGMSmartDuplicateImplicitBodyTopOper* CATPGMCreateSmartDuplicateImplicitBodyTopOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iInputBody) = 0;

#endif

};

/**
 * Returns the factory of implementations of interfaces for the framework GMPolyUtilities.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGMScalarFieldsOperatorsItfBldr *CATCGMGetGMScalarFieldsOperatorsItfBldr();

#endif /* CATIPGMGMScalarFieldsOperatorsItfBldr_h */
