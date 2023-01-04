//===================================================================
// COPYRIGHT [!output company] 2010/03/12
//===================================================================
// Header definition of class CATGMEquation
//===================================================================

// Interface on a CDMEquation, dedicated for applications that may not require CDMModel framework,
// and do not accept to use CATICDMEquation interface 
// These objects are twins of CDMEquation, their lifecycles are identical

//===================================================================
//  2010/07/12 Creation: chu
//===================================================================
#ifndef CATGMEquation_H
#define CATGMEquation_H

#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "CATGMRelation.h"
#include "CATCDMRelationEnum.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMEquation;
class CDMRelation;
class CATBody;
class CATUnicodeString;

class ExportedByCATCDMBaseInterfaces CATGMEquation: public CATGMRelation
{
public:

  // Lifecycle
  virtual ~CATGMEquation();

  // Get or set equation text
  virtual HRESULT GetEquationText(CATUnicodeString & oEquationText) = 0;
  virtual HRESULT SetEquationText(CATUnicodeString & iEquationText) = 0;

  // Get a CATGMConstraint from its name (the method assumes that the wanted constraint is used by the current equation)
  virtual HRESULT GetConstraintInEquationFromName(CATUnicodeString & iName, CATGMConstraint *& oConstraint) = 0;

  // Internal Use
  virtual CDMRelation & GetAssociatedRelation() = 0;

protected:

  CATGMEquation();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMEquation (CATGMEquation &);
  CATGMEquation& operator=(CATGMEquation&);

};

//-----------------------------------------------------------------------
#endif
