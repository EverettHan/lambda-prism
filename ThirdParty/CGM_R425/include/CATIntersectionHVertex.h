#ifndef CATIntersectionHVertex_h
#define CATIntersectionHVertex_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATHVertex.h"
#include "CATCellManifold.h"
#include "ListPOfCATCellManifold.h"
#include "ExportedByCATTopologicalObjects.h"




#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTopologicalObjects IID IID_CATIntersectionHVertex ;
#else
extern "C" const IID IID_CATIntersectionHVertex ;
#endif

class ExportedByCATTopologicalObjects CATIntersectionHVertex : public CATHVertex
{
  CATDeclareInterface;

public:

  virtual int GetNumberOfSupport() const = 0;
  virtual void GetSupport(int iList, ListPOfCATCellManifold &oList) const = 0;

  //------------------------
  // Do not use
  //------------------------
  virtual HRESULT Set(int iNumberOfLists, ListPOfCATCellManifold iLists[]) = 0;

};
  
CATDeclareHandler(CATIntersectionHVertex,CATHVertex);

#endif
