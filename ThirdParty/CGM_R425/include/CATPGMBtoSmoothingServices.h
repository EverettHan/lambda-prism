#ifndef CATPGMBtoSmoothingServices_h_
#define CATPGMBtoSmoothingServices_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"

class CATCldScan;
class CATGeoFactory;
class CATTolerance;
class CATSoftwareConfiguration;

//=====================================================================================================================
// ...
//=====================================================================================================================
class ExportedByCATGMOperatorsInterfaces CATPGMBtoSmoothingServices
{
public:
  //Ajout ANR pour Tooling
  static int Reordering(
    CATGeoFactory *iFactory,
    CATSoftwareConfiguration *iConfig,
    int iIndex1,
    int iIndex2,
    CATCldScan *&ioScan);

  // Suppression des points dupliques
  static void CleanOfTheInputScan(
    CATGeoFactory *iFactory,
    CATCldScan *InputScan,
    CATCldScan *&oCleanScan);

};

#endif /* CATPGMBtoSmoothingServices_h_ */
