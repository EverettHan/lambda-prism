#ifndef CATConfusedLoop_H
#define CATConfusedLoop_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATLoop.h"

//-----------------------------------------------------------------------------
#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATConfusedLoop ;
#else
extern "C" const IID IID_CATConfusedLoop ;
#endif

class ExportedByCATGMModelInterfaces CATConfusedLoop : public CATLoop
{

  CATDeclareInterface;

  public :
};


#endif
