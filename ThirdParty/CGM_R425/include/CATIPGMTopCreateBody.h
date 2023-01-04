#ifndef CATIPGMTopCreateBody_h_
#define CATIPGMTopCreateBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2009

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATDomain;
class CATLISTP(CATDomain);

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopCreateBody;

//--------------------------------------------------------------------------------------------------
class ExportedByCATGMModelInterfaces CATIPGMTopCreateBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCreateBody();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCreateBody(); // -> delete can't be called
};

//--------------------------------------------------------------------------------------------------
// Official service for operator creation
//--------------------------------------------------------------------------------------------------
// Deprecated
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
  const CATUnicodeString &iRoleOfOutput,
  CATBody *iInputBody,
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATDomain) &iDomains,
  CATListOfInt &iLocations);

// Official
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
  const CATUnicodeString &iRoleOfOutput,
  const CATLISTP(CATBody) &iInputBodies,
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATDomain) &iDomains);

// Official
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
  const CATUnicodeString &iRoleOfOutput,
  const CATLISTP(CATBody) &iInputBodies,
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATDomain) &iDomains,
  CATListOfInt &iLocations);

// Deprecated
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATDomain) &iDomains,
  CATListOfInt &iLocations);

// Official
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCreateBody *CATPGMCreateTopCreateBody(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATLISTP(CATDomain) &iDomains);

#endif /* CATIPGMTopCreateBody_h_ */
