/* -*-c++-*- */
#ifndef CATCXStreamFactory_h
#define CATCXStreamFactory_h

#include "ExportedByCATTopologicalObjects.h"
#include "CATExtCGMReplay.h"
#include "CATCGMNewArray.h"

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
class ExportedByCATTopologicalObjects CATCXStreamFactory : public CATExtCGMReplay
{
  CATDeclareClass;
  
public:
  /** @nodoc */
  CATCGMNewClassArrayDeclare;
  
  void GetSharedlibOfOperator(const char *operatorId, char* & sharedlib);

  HRESULT GetAvailableOperators(CATListOfCATString &OpIds);

};


#endif



