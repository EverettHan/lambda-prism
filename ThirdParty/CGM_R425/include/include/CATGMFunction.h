//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMFunction
//===================================================================

// Interface on a CATGMFunction, dedicated for applications that may not require CDMModel framework
// These objects are twins of CDMFunction, their lifecycles are identical

//===================================================================
//  2014/09/19 Creation: juz
//===================================================================
#ifndef CATGMFunction_H
#define CATGMFunction_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATErrorDef.h"

class CATGMFunctionOfCDMObject;

class ExportedByCATCDMBaseInterfaces CATGMFunction
{
public:
  // Lifecycle
  virtual ~CATGMFunction();

  virtual CATGMFunctionOfCDMObject* SafeCastToCATGMFunctionOfCDMObject();

protected:
  CATGMFunction();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMFunction (CATGMFunction &);
  CATGMFunction& operator=(CATGMFunction&);

};

#endif
