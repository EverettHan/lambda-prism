#ifndef CATIPGMGMPolyOperItfBldr1_h
#define CATIPGMGMPolyOperItfBldr1_h

#include "CATGMOperatorsInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATCollec.h"
#include "ListPOfCATBody.h"
#include "CATDataType.h"
#include "CATIAV5Level.h"
#ifdef CATIAR420
#include "CATTopDefine.h"
#endif

class CATIPGMConverterToPolyhedralBody;
class CATIPGMConverterPolyToExactBody;
class CATIPGMPolyhedralSweepDraft;
class CATIPGMPolyhedralFillSweepRibbon;
#ifdef CATIAR420
class CATIPGMPolyhedralSculptingOper;
#endif
#ifdef CATIAR421
class CATIPGMPolyhedralRoughOffset;
#endif
#ifdef CATIAR424
class CATIPGMPolyhedralORMIsoCurves;
class CATIPGMPolyhedralORMModelEditor;
class CATCGMOrmModel;
#endif

class CATPGMPolyBodyImporter;
class CATPGMPolyBodyAdapter;
class CATPGMGeoPolyBodyBuilder;
class CATPGMConvertBodyToGeoPolyBody;
class CATIPGMAdvancedBoundingBoxWireOper;
class CATIPGMPolyhedralBodyDecimator;
class CATICGMPolyhedralBodyDecimator;

class CATGeoFactory;
class CATTopData;
class CATSoftwareConfiguration;
class CATBody;
class CATDomain;
class CATPolyBody;
class CATMathDirection;
class CATMathPlane;

// Public itf only in 3DExperience
#ifdef CATIAR422
class CATICGMPolyhedralRoughOffset;
#endif

// Public itf only in 3DExperience
#ifdef CATIAR424
class CATICGMPolyhedralSweepDraft;
#endif

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMGMPolyOperItfBldr1;

/**
 * Factory of implementations of CGM interfaces for the framework GMPolyOperators.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMGMPolyOperItfBldr1: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMConverterToPolyhedralBody *CATPGMCreateConverterToPolyhedralBody(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMConverterPolyToExactBody *CATPGMCreateConverterPolyToExactBody(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

  virtual CATIPGMPolyhedralSweepDraft *CATPGMCreatePolyhedralSweepDraft(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    const CATMathDirection &iDraftDirection) = 0;

  virtual CATIPGMPolyhedralSweepDraft *CATPGMCreatePolyhedralSweepDraft(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    const CATMathPlane &iRefPlane) = 0;

  virtual CATIPGMPolyhedralFillSweepRibbon *CATPGMCreatePolyhedralFillSweepRibbon(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iGuideWireBody) = 0;

  virtual CATPGMPolyBodyImporter *CATPGMCreatePolyBodyImporter(
    CATGeoFactory * iTargetFactory, 
    CATSoftwareConfiguration * iSoftwareConfig, 
    CATPolyBody * iPolyBodyToImport) = 0;

  virtual CATPGMPolyBodyAdapter *CATPGMCreatePolyBodyAdapter(
    CATBody * iPHBody, 
    CATSoftwareConfiguration * iSoftwareConfig) = 0;

  virtual CATPGMPolyBodyAdapter *CATPGMCreatePolyBodyAdapter(
    CATDomain * iPHDomain,
    CATSoftwareConfiguration * iSoftwareConfig) = 0;

  virtual CATPGMGeoPolyBodyBuilder * CATPGMCreateGeoPolyBodyBuilder(
    CATGeoFactory * iTargetFactory, 
    CATSoftwareConfiguration * iSoftwareConfig) = 0;

  virtual CATPGMConvertBodyToGeoPolyBody * CATPGMCreateConvertBodyToGeoPolyBody(
    CATGeoFactory * iTargetFactory, 
    CATSoftwareConfiguration * iSoftwareConfig) = 0;

  virtual CATIPGMAdvancedBoundingBoxWireOper *CATPGMCreateAdvancedBoundingBoxWireOper(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    CATBody *iBody) = 0;

#ifdef CATIAR420
  virtual CATIPGMPolyhedralSculptingOper *CATPGMCreatePolyhedralSculptingOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToSculpt,
    CATBody *iBodyToSew,
    CATOrientation iOutwardOrientation) = 0;
#endif
  
#ifdef CATIAR422
  virtual CATIPGMPolyhedralSculptingOper *CATPGMCreatePolyhedralSculptingOper(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToSculpt) = 0;
#endif

#ifdef CATIAR424
  virtual CATIPGMPolyhedralORMIsoCurves *CATPGMCreatePolyhedralORMIsoCurves(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATCGMOrmModel *iOrmModel) = 0;

  virtual CATIPGMPolyhedralORMModelEditor* CATPGMCreatePolyhedralORMModelEditor(
      CATGeoFactory* iFactory,
      CATSoftwareConfiguration* iConfig,
      CATCGMOrmModel* iOrmModel,
      CATBoolean iDuplicateMode) = 0;
#endif

#ifdef CATIAR421
  virtual CATIPGMPolyhedralRoughOffset *CATPGMCreatePolyhedralRoughOffset(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToOffset) = 0;
#endif

#ifdef CATIAR422
  virtual CATICGMPolyhedralRoughOffset *CATCGMCreatePolyhedralRoughOffset(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBodyToOffset) = 0;
#endif

#ifdef CATIAR424
  virtual CATICGMPolyhedralSweepDraft *CATCGMCreatePolyhedralSweepDraft(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iWireBody,
    const CATMathDirection &iDraftDirection) = 0;
#endif

  virtual CATIPGMPolyhedralBodyDecimator *CATPGMCreatePolyhedralBodyDecimator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;

#ifdef CATIAR425
  virtual CATICGMPolyhedralBodyDecimator *CATCGMCreatePolyhedralBodyDecimator(
    CATGeoFactory *iFactory,
    CATTopData *iTopData,
    CATBody *iBody) = 0;
#endif
};

/**
 * Returns the factory of implementations of interfaces for the framework GeometricOperators.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGMPolyOperItfBldr1 *CATCGMGetGMPolyOperItfBldr1();

#endif /* CATIPGMGMPolyOperItfBldr1_h */
