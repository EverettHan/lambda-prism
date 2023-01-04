#ifndef CATTopCellRetrieve_H
#define CATTopCellRetrieve_H

// COPYRIGHT DASSAULT SYSTEMES 2005
//----------------------------------------------------------------------------

#include "ExportedByCATTopologicalObjects.h"
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATListOfCATGeometries.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATGeometry;
class CATEdgeCurve;
class CATMacroPoint;

class ExportedByCATTopologicalObjects CATTopCellRetrieve
{
public:

  // Get the couples of Body/Cell that contains a provided geometry inside a container
  // The two resulting lists are to be read together :
  // oListOfCell[i] leads to the body oListOfBody[i] for each i in the list
  static void GetCellFromGeometry(CATGeoFactory *     iFactory,
                                  CATGeometry *       iGeom,
                                  CATLISTP(CATBody) & oListOfBody,
                                  CATLISTP(CATCell) & oListOfCell);

private:

  // See cpp for interface usage
  static CATBoolean FindGeom(CATEdgeCurve  * ipEdgeCurve,
                             CATGeometry   * iGeom);

  static CATBoolean FindGeomRec(CATEdgeCurve  * ipEdgeCurve,
                                CATGeometry   * iGeom,
                                CATLISTP(CATGeometry)& ioListComponents);

  static CATBoolean FindGeom(CATMacroPoint * ipMacroPoint,
                             CATGeometry   * iGeom);

};


#endif
