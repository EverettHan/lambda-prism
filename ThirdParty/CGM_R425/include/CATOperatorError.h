#ifndef __CATOperatorError_h__
#define __CATOperatorError_h__

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CATInternalError.h"
#include "CATErrors.h"
#include "CATCGMInternalError.h"

#include "CATGMOperatorsInterfaces.h"

#include "CATListOfCATGeometries.h"

class CATGeometry;

class ExportedByCATGMOperatorsInterfaces CATOperatorError : public CATCGMInternalError
{
public :
  CATDeclareErrorClass(CATOperatorError, CATCGMInternalError)
    
  CATOperatorError();
  
  ~CATOperatorError();

  virtual void GetGeometry(CATLISTP(CATGeometry) &iolistGran1,
			   CATLISTP(CATGeometry) &iolistGran2);

   	/** @nodoc */
   CATCGMNewClassArrayDeclare;
};
#endif

