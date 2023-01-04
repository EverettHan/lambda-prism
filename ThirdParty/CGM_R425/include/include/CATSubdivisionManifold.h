#ifndef CATSubdivisionManifold_h
#define CATSubdivisionManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATEvaluableManifold.h"

#include "ListPOfCATCellManifold.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATSubdivisionManifold ;
#else
extern "C" const IID IID_CATSubdivisionManifold ;
#endif

class CATSubdivMesh;
class CATShell;

class ExportedByCATGMModelInterfaces CATSubdivisionManifold : public CATEvaluableManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   CATSubdivMesh* iSubdivMesh,
                   CATShell* iSubdivShell) = 0;

  virtual CATSubdivMesh* GetSubdivMesh() const = 0;


};
  
CATDeclareHandler(CATSubdivisionManifold,CATEvaluableManifold);

#endif
