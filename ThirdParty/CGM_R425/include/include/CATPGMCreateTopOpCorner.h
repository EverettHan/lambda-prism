#ifndef CATPGMCreateTopOpCorner_h_
#define CATPGMCreateTopOpCorner_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

#ifndef NULL
#define NULL 0
#endif

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATGeometry;
class CATLaw;
class CATIPGMTopCorner;
class CATTopData;

//
// CATPGMCreateTopCorner -> CATTopCorner.h
/**
* @nodoc
* Deprecated. Use CATPGMCreateTopCorner.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner *CATPGMCreateTopOpCornerForPJB(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iCurve1,
  CATBody *iCurve2,
  CATBody *iSupport,
  double iRadius);

// CATPGMCreateTopCorner -> CATTopCorner.h
/**
* @nodoc
* Deprecated. Use CATPGMCreateTopCorner.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner *CATPGMCreateTopOpCorner(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iCurve1,
  CATBody *iCurve2,
  CATBody *iSupport,
  double iRadius);

/**
* @nodoc
* Deprecated. Use CATPGMCreateTopCorner.
 * @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner *CATPGMCreateTopOpCornerTgtCenterOnPt(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iCurve,
  CATBody *iPoint,
  CATBody *iSupport);

/**
* @nodoc
* Deprecated. Use CATPGMCreateTopCorner.
 * @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCorner *CATPGMCreateTopOpCornerTgtCenterOnCrvRad(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iCurveCenter,
  CATBody *iCurveTgt,
  double iRadius,
  CATBody *iSupport);


#endif /* CATPGMCreateTopOpCorner_h_ */
