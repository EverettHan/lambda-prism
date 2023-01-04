#ifndef CATIPGMGMPolyUtilitiesItfBldr_h
#define CATIPGMGMPolyUtilitiesItfBldr_h

#include "CATGMModelInterfaces.h"
#include "CATBaseUnknown.h"
#include "CATDataType.h"
#include "CATTopDefine.h"
#include "CATIAV5Level.h"

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMGMPolyUtilitiesItfBldr;

class CATGeoFactory;
class CATBody;
class CATFace;
class CATSoftwareConfiguration;
class CATIPGMFaceCurvatureAnalyzer; // DPS
#ifdef CATIAR423
// Ajout wmn apres cgmitfgenerate et c/c du Create
class CATIPGMHybClashBodyChecker;
#endif
class CATPGMVolumePartitionBodyToolKit;

/**
 * Factory of implementations of CGM interfaces for the framework GMPolyUtilities.
 */
class ExportedByCATGMModelInterfaces CATIPGMGMPolyUtilitiesItfBldr: public CATBaseUnknown
{
  CATDeclareInterface;
public:

  virtual CATIPGMFaceCurvatureAnalyzer *CATPGMCreateFaceCurvatureAnalyzer(
    CATGeoFactory            * iFactory,
    CATSoftwareConfiguration * iConfig,
    CATFace                  * iFaceToEvaluate,
    CATOrientation             iFaceOrientation) = 0;

#ifdef CATIAR423
  virtual CATIPGMHybClashBodyChecker *CATPGMCreateHybClashBodyChecker(
    CATBody                  * iBody,
    CATSoftwareConfiguration * iConfig) = 0;
#endif

  virtual CATPGMVolumePartitionBodyToolKit * CATPGMCreateVolumePartitionBodyToolKit(
    CATBody * iPartitionBody, 
    CATSoftwareConfiguration * iConfig) = 0;
};

/**
 * Returns the factory of implementations of interfaces for the framework GMPolyUtilities.
 * @return
 *   The factory. Pay attention: no <tt>AddRef</tt> is run.
 */
CATIPGMGMPolyUtilitiesItfBldr *CATCGMGetGMPolyUtilitiesItfBldr();

#endif /* CATIPGMGMPolyUtilitiesItfBldr_h */
