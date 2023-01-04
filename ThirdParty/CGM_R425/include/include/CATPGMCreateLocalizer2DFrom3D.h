#ifndef CATPGMCreateLocalizer2DFrom3D_h_
#define CATPGMCreateLocalizer2DFrom3D_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

//=============================================================================
// 04/10/17 NLD Ajout argument PCurveList a CATPGMCreateLocalizer2DFrom3D()
//=============================================================================
#ifndef NULL
#define NULL 0
#endif
#include "CATGMOperatorsInterfaces.h"
#include "CATCollec.h"

class CATCell;
class CATGeoFactory;
class CATLISTP_CATCell_;
class CATSoftwareConfiguration;
class CATLISTP(CATCell);
class CATLocalizer2DFrom3D;
class CATCurve;
class CATLISTP(CATCurve);


//-----------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces CATLocalizer2DFrom3D *CATPGMCreateLocalizer2DFrom3D(
  CATGeoFactory            * factory,
  CATSoftwareConfiguration * iSoftConfig,
  CATLISTP(CATCell)        * faces,
  CATLISTP(CATCurve)       * PCurveList = NULL
);

//Do Not Use this one anymore !
ExportedByCATGMOperatorsInterfaces CATLocalizer2DFrom3D *CATPGMCreateLocalizer2DFrom3D(
  CATGeoFactory     *factory,
  CATLISTP(CATCell) *faces);

#endif /* CATPGMCreateLocalizer2DFrom3D_h_ */
