#ifndef CATPGMTopCellRetrieve_h_
#define CATPGMTopCellRetrieve_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"

class CATEdgeCurve;
class CATGeoFactory;
class CATGeometry;
class CATMacroPoint;
class CATLISTP(CATCell);
class CATLISTP(CATBody);

class ExportedByCATGMModelInterfaces CATPGMTopCellRetrieve
{
public:
  // Get the couples of Body/Cell that contains a provided geometry inside a container
  // The two resulting lists are to be read together :
  // oListOfCell[i] leads to the body oListOfBody[i] for each i in the list
  static void GetCellFromGeometry(
    CATGeoFactory *iFactory,
    CATGeometry *iGeom,
    CATLISTP(CATBody) &oListOfBody,
    CATLISTP(CATCell) &oListOfCell);
};

#endif /* CATPGMTopCellRetrieve_h_ */
