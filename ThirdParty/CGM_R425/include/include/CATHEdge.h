#ifndef CATHEdge_h
#define CATHEdge_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATHGeometry.h"
#include "CATCellManifold.h"
#include "ListPOfCATCellManifold.h"
#include "CATTopDefine.h"
#include "ListPOfCATEdge.h"

#include "ExportedByCATTopologicalObjects.h"


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTopologicalObjects IID IID_CATHEdge ;
#else
extern "C" const IID IID_CATHEdge ;
#endif

class ExportedByCATTopologicalObjects CATHEdge : public CATHGeometry
{
  CATDeclareInterface;

public:

  //------------------------
  // Get/Set Methods
  //------------------------
  virtual void GetSupport(ListPOfCATCellManifold oLeftAndRightSupport[2]) const = 0;
  virtual void GetLimiting(ListPOfCATCellManifold &oLimiting) const = 0;
  virtual HRESULT Set(ListPOfCATCellManifold oLeftAndRightSupport[2], ListPOfCATCellManifold& iLimiting) = 0;
  virtual HRESULT SetOrientation(const CATOrientation iRefOrientation) = 0;
  virtual CATOrientation GetOrientation() const = 0;
};
  
CATDeclareHandler(CATHEdge,CATHGeometry);

#endif
