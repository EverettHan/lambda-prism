//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMFunctionOfCDMObject
//===================================================================

// Interface on a CATGMFunctionOfCDMObject, dedicated for applications that may not require CDMModel framework
// These objects are twins of CDMFunctionOfCDMObject, their lifecycles are identical

//===================================================================
//  2014/09/19 Creation: juz
//===================================================================
#ifndef CATGMFunctionOfCDMObject_H
#define CATGMFunctionOfCDMObject_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATGMFunction.h"
#include "CATErrorDef.h"
#include "CATCDMPublicationEnum.h"

class ExportedByCATCDMBaseInterfaces CATGMFunctionOfCDMObject : public CATGMFunction
{
public:
  // Lifecycle
  virtual ~CATGMFunctionOfCDMObject();

  virtual CATGMFunctionOfCDMObject* SafeCastToCATGMFunctionOfCDMObject();

  virtual HRESULT GetFunctionDescription (CATCDMPublicationEnum::FunctionDescription &oFunctionDesc) = 0;

protected:
  CATGMFunctionOfCDMObject();

private:
  // The copy constructor and the equal operator must not be implemented
  CATGMFunctionOfCDMObject (CATGMFunctionOfCDMObject &);
  CATGMFunctionOfCDMObject& operator=(CATGMFunctionOfCDMObject&);
};

#endif

