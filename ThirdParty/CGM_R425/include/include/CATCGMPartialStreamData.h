#ifndef CATCGMPartialStreamData_h_
#define CATCGMPartialStreamData_h_

//=============================================================================
// Fev. 08  Creation                                                      TXO
//============================================================================= 

#include "CATListOfCATICGMObjects.h"

class CATCGMHashTable;
class CATCGMSafeHashTable;

class CATCGMPartialStreamData
{
public:
  CATLISTP(CATICGMObject) _ToSend;
  const CATLISTP(CATICGMObject)* _Objects;
  CATCGMSafeHashTable* _SafeUserHashTable;
  CATCGMHashTable* _InternalHashTable;
};

#endif 
