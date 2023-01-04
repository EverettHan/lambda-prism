//===================================================================
// COPYRIGHT [!output company] 2011/10/28
//===================================================================
// Header definition of class CATGMMatchConstraint
//===================================================================

// Interface on a CATGMMatchConstraint, dedicated for applications that may not require CDMModel framework,
// and do not accept to use CATICDMMatchConstraint interface 
// These objects are twins of CDMMatchConstraint, their lifecycles are identical

//===================================================================
//  2011/10/28 Creation: cn8
//===================================================================
#ifndef CATGMMatchConstraint_H
#define CATGMMatchConstraint_H

#include "CATErrorDef.h"
#include "CATGMRelation.h"
#include "CATCDMContinuity.h"
#include "CATCDMBaseInterfaces.h" // export

class CDMRelation;
class CATBody;

class ExportedByCATCDMBaseInterfaces CATGMMatchConstraint: public CATGMRelation
{
public:

  // Lifecycle
  virtual ~CATGMMatchConstraint();

  // Set the iNumber-th Body suuport of the MatchConstraint and its associated ratio to define the point (1 <= iNumber <= 2)
  virtual HRESULT GetMatchSupport(int iNumber, CATBody * &oBody, double & oRatio) = 0;

  // Get the diffusion along the wire 
  virtual HRESULT GetMatchDiffusion(double &oDiffusion) = 0;

  // Get the continuity
  virtual HRESULT GetCDMContinuity(CATCDMContinuity &oContinuity) = 0;

  // Get/Set the continuity status
  virtual HRESULT GetCDMContinuityStatus(CATCDMContinuity::ContinuityType &oContinuity, CATBoolean iNewest = FALSE) = 0;
  virtual HRESULT SetCDMContinuityStatus(CATCDMContinuity::ContinuityType iContinuity) = 0;


  // Internal Use
  virtual CDMRelation & GetAssociatedRelation() = 0;

protected:

  CATGMMatchConstraint();

private:

  // The copy constructor and the equal operator must not be implemented
  CATGMMatchConstraint (CATGMMatchConstraint &);
  CATGMMatchConstraint& operator=(CATGMMatchConstraint&);

};

//-----------------------------------------------------------------------
#endif
