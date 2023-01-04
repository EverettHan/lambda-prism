#ifndef CATGMLiveGeometricUtilities_H
#define CATGMLiveGeometricUtilities_H

#include "PersistentCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATListOfCATSurParams.h"
#include "CATMathDef.h"
#include "CATListOfInt.h"
#include "CATSysErrorDef.h"
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATCrvParam;
class CATMathPoint;

class ExportedByPersistentCell CATGMLiveGeometricUtilities
{
public:

  static HRESULT GetMinDistance(CATGeoFactory& iFactory, CATSoftwareConfiguration& iConfig, const CATMathPoint& iPoint, const ListPOfCATFace& iFaces, const ListPOfCATEdge& iEdges, 
                                CATPositiveLength& oMinDistance, CATLISTP(CATSurParam)& oMinDistanceLocation, CATListOfInt& oFaceIndexes);

  //-------------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif 

