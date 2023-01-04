#ifndef CATGMLiveHVertexUtilities_H
#define CATGMLiveHVertexUtilities_H

#include "CATCGMNewArray.h"
#include "CATTopDefine.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h"

class CATHVertex;


class ExportedByPersistentCell CATGMLiveHVertexUtilities
{
public:

  static CATBoolean HaveSameSpecificParam(CATHVertex * iHVertex1, CATHVertex * iHVertex2, CATGeoFactory * iFactory, CATBoolean iOriToInvert=FALSE);

};

#endif 

