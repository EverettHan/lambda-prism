#ifndef CATIPGMHybConfusion_h_
#define CATIPGMHybConfusion_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"
#include "CATHybDef.h"

class CATExtHybConfusion;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybConfusion;

class ExportedByCATGMOperatorsInterfaces CATIPGMHybConfusion: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybConfusion();

  /** @nodoc */
  virtual int Run() = 0;

  virtual void SetCandidateDomain(CATDomain *iDomain) = 0;

  virtual void SetSupportDomain(CATDomain *iDomain) = 0;

  //--------------------------------------------------------------------------
  //  Diagnostic CATHybConfusionDiagnostic{ NO_CONFUSION, FULL_CONFUSION, CONTACT };
  //  
  //  * Defines the differents results of a confusion diagnostic.
  //  * @param NO_CONFUSION
  //  * There is no confusion at all between the bodies.
  //  * @param FULL_CONFUSION
  //  * There is a full confusion between the bodies.
  //  * @param CONTACT
  //  * There is an intersection between the bodies but not a full confusion.
  //  
  //--------------------------------------------------------------------------
  virtual CATHybConfusionDiagnostic GetConfusionDiagnostic() = 0;

  /** @nodoc  */
  virtual CATExtHybConfusion *GetHybConfusionExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybConfusion(); // -> delete can't be called
};

#endif /* CATIPGMHybConfusion_h_ */
