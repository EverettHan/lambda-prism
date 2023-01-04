// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATCGMTessIDPopulate: Utility to populate CATCGMTessID object
//
//===================================================================
//
// June 2011  Creation: MPX
//===================================================================
#ifndef CATCGMTessIDPopulate_H
#define CATCGMTessIDPopulate_H

#include "CATGMModelInterfaces.h"
#include "CATBoolean.h"
#include "CATDataType.h"

class CATCGMTessID;
class CATCGMTessBody;
class CATCGMTessellateParam;

class ExportedByCATGMModelInterfaces CATCGMTessIDPopulate
{
public:

  static void PopulateForClassic(CATCGMTessID& ioTessID, CATCGMTessBody& iTessBody, const void* iData, int iOrientation);
  static void PopulateForDeltaMesh(CATCGMTessID& ioTessID, CATCGMTessBody& iTessBody, CATCGMTessellateParam& iTessellateParam, int iCellTag, int iNbDelta, int iOrientation);
  static void PopulateForPoly(CATCGMTessID& ioTessID, CATCGMTessBody& iTessBody,int iCellTag, int iOrientation);

  //static void PopulateForUV(CATCGMTessID& ioTessID, CATCGMTessBody& iTessBody, const void* iData, int iOrientation);

};


#endif // CATCGMTessIDPopulate_H

