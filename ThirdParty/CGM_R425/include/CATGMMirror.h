//===================================================================
// COPYRIGHT [DS] 2012/10/01
//===================================================================
// Header definition of class CATGMMirror
//===================================================================

// Interface on a CDMMirror, dedicated for applications that may not require CDMModel framework,
// and do not accept to use CATICDMMirror interface 
// These objects are twins of CDMMirror, their lifecycles are identical

//===================================================================
//  2012/10/01 Creation: juz
//===================================================================
#ifndef CATGMMirror_H
#define CATGMMirror_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATGMRelation.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMRelation;
class CATMathPlane;

class ExportedByCATCDMBaseInterfaces CATGMMirror: public CATGMRelation
{
public:

  // Lifecycle
  virtual ~CATGMMirror();

  // Get or set equation text
  virtual HRESULT GetMirrorCDMPlane(CATMathPlane& oPlane) = 0;

  // Internal Use
  virtual CDMRelation & GetAssociatedRelation() = 0;

protected:

  CATGMMirror();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMMirror (CATGMMirror &);
  CATGMMirror& operator=(CATGMMirror&);

};

//-----------------------------------------------------------------------
#endif
