#ifndef CATIPGMIntersectionChecker_h_
#define CATIPGMIntersectionChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMChecker.h"

class CATCXIntersectionChecker;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMIntersectionChecker;

class ExportedByCATGMModelInterfaces CATIPGMIntersectionChecker: public CATIPGMChecker
{
public:
  /**
   * Constructor
   */
  CATIPGMIntersectionChecker();

  //======================================
  // Methodes specifiques a CATIPGMTopOperator
  //======================================
  //====================================
  // Acces aux parametres de l'operateur
  //====================================
  virtual CATBoolean GetCheckOnlySelfIntersection() const = 0;

  virtual CATBoolean GetCheckOnlyDomainsIntersection() const = 0;

  virtual CATBoolean GetTopologicalResultMode() const = 0;

  virtual CATBoolean GetToleranceRestrictedMode() const = 0;

  //===========================================
  // Methodes de parametrisation de l'operateur
  //===========================================
  virtual void SetCheckOnlySelfIntersection() = 0;

  virtual void SetCheckOnlyDomainsIntersection() = 0;

  virtual void SetTopologicalResultMode(CATBoolean iTopologicalResultMode) = 0;

  virtual void SetToleranceRestrictedMode(CATBoolean iToleranceRestrictedMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMIntersectionChecker(); // -> delete can't be called
};

#endif /* CATIPGMIntersectionChecker_h_ */
