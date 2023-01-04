#ifndef CATIPGMLiveUXDRepOpe_h_
#define CATIPGMLiveUXDRepOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2017

#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"
#include "CATErrorDef.h"

class CATBody;
class CATCell;
class CATDRepExtTopOperator;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATMathPoint;
class CATLISTP(CATBody);
class CATLISTP(CATManifold);
class CATLISTP(CATManifoldParameter);

//Create the UXMRep and UXPRep only for the CATManifoldParameter and Manifold associated with iLocationCell of iCurrentBody
//update parameters corresponding to iLocationPoint
ExportedByCATGMOperatorsInterfaces HRESULT CATPGMCreateUXDRepOpe(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATBody *iCurrentBody,
  CATCell *iLocationCell,
  CATMathPoint *iLocationPoint,
  CATLISTP(CATManifold) &iCurrentManifoldList,
  CATBody *iFirstBody,
  CATLISTP(CATManifold) &iFirstManifoldList,
  CATLISTP(CATManifoldParameter) &ioParameterList,
  CATLISTP(CATBody) &oUXPRepBodyList,
  CATLISTP(CATBody) &oUXMRepBodyList);

#endif /* CATIPGMLiveUXDRepOpe_h_ */
