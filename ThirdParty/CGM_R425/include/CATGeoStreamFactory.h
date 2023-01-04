/* -*-c++-*- */
#ifndef CATGeoStreamFactory_h
#define CATGeoStreamFactory_h

#include "Replay_GeometricOperators.h"
#include "CATExtCGMReplay.h"
#include "CATCGMNewArray.h"

/**
* Interface to manage persistency with CATMathStream/CACGMStream infrastructure
*/
 class ExportedByReplay_GeometricOperators CATGeoStreamFactory : public CATExtCGMReplay
{
  CATDeclareClass;
  
public:
  /** @nodoc */
  CATCGMNewClassArrayDeclare;
  
  void GetSharedlibOfOperator(const char *operatorId, char* & sharedlib);

  HRESULT GetAvailableOperators(CATListOfCATString &OpIds);

  CATBoolean IsTopological();
};


#endif



