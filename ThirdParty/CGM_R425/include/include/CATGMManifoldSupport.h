//===================================================================
// COPYRIGHT 3DS 2019
//===================================================================
// Header definition of class CATGMManifoldSupport
//===================================================================


//===================================================================
//  2019/07/19 Creation: KUB
//===================================================================
#ifndef CATGMManifoldSupport_H
#define CATGMManifoldSupport_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATGMSupport.h"
#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATManifold.h" 
#include "ListPOfCATBody.h"


#include "CATCDMLabelType.h"

class CATBody;
class CATManifold;


class ExportedByCATCDMBaseInterfaces CATGMManifoldSupport: public CATGMSupport
{
public:
  // Lifecycle
  virtual ~CATGMManifoldSupport();

  virtual HRESULT GetManifoldSupport(CATManifold*& oGeometry, CATBody*& Body);

protected:
  CATGMManifoldSupport();

private:
  // The copy constructor and the equal operator must not be implemented
  CATGMManifoldSupport(CATGMManifoldSupport &);
  CATGMManifoldSupport& operator=(CATGMManifoldSupport&);

};

//-----------------------------------------------------------------------
#endif
