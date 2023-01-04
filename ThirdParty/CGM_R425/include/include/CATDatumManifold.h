#ifndef CATDatumManifold_h
#define CATDatumManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATDeclarativeManifold.h"

#include "YI00IMPL.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATDatumManifold ;
#else
extern "C" const IID IID_CATDatumManifold ;
#endif

class ExportedByYI00IMPL CATDatumManifold : public CATDeclarativeManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iReps)=0;  

};
  
CATDeclareHandler(CATDatumManifold,CATDeclarativeManifold);

#endif
