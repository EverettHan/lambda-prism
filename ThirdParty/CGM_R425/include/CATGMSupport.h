//===================================================================
// COPYRIGHT 3DS 2014/01/15
//===================================================================
// Header definition of class CATGMSupport
//===================================================================


//===================================================================
//  2014/01/15 Creation: JUZ
//===================================================================
#ifndef CATGMSupport_H
#define CATGMSupport_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATErrorDef.h"

#include "CATCDMLabelType.h"

class CATGMTopoSupport;
class CATGMManifoldSupport;


class ExportedByCATCDMBaseInterfaces CATGMSupport
{
public:

  // Lifecycle
  virtual ~CATGMSupport();

  virtual CATGMTopoSupport* SafeCastToGMTopoSupport();

  virtual CATGMManifoldSupport* SafeCastToGMManifoldSupport();

  virtual HRESULT GetOldSupport(CATGMSupport*& oSupport) = 0;

  // returns the type of contract
  virtual HRESULT GetLabelContractType(CDMLabelType &oLabelType) = 0;

protected:
  CATGMSupport();

private:
  // The copy constructor and the equal operator must not be implemented
  CATGMSupport (CATGMSupport &);
  CATGMSupport& operator=(CATGMSupport&);

};

//-----------------------------------------------------------------------
#endif
