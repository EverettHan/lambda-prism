#ifndef CATPGMCreateSegmentation_h_
#define CATPGMCreateSegmentation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATDataType.h"
#include "CATSkillValue.h"
#include "CATCollec.h"

class CATCurve;
class CATNurbsCurve;
class CATSegmentation;
class CATSoftwareConfiguration;
class CATGeoFactory;
class CATCrvParam;
class CATLISTP(CATCurve);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATCurve *iCurve,
  CATLONG32 NbSeg,
  CATSkillValue mode = BASIC);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATLISTP(CATCurve) &iListe,
  CATLONG32 NbSeg,
  CATSkillValue mode = BASIC);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATCurve *iCurve,
  CATLONG32 NbSeg,
  CATLONG32 &NbBreak,
  CATCrvParam *Wpar,
  CATSkillValue mode = BASIC);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATCurve *iCurve,
  double &Tolap,
  CATSkillValue mode = BASIC);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATLISTP(CATCurve) &iListe,
  double &Tolap,
  CATSkillValue mode = BASIC);

ExportedByCATGMOperatorsInterfaces CATSegmentation *CATPGMCreateSegmentation(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftwareConfiguration,
  CATCurve *iCurve,
  double &Tolap,
  CATLONG32 &NbBreak,
  CATCrvParam *Wpar,
  CATSkillValue mode = BASIC);

#endif /* CATPGMCreateSegmentation_h_ */
