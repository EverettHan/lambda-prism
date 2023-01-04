#ifndef CATlsoErrorUtilities_H
#define CATlsoErrorUtilities_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"

class CATTopOpInError;

// @nocgmitf (do not create phase 2 interface) 
class ExportedByPersistentCell CATlsoErrorUtilities
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  static CATBoolean IsTopErrorContains(CATTopOpInError & iTopError, const char * iErrorMessageID);
};

#endif 
