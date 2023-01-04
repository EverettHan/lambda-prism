#ifndef CATIPGMTopSmartProject_h_
#define CATIPGMTopSmartProject_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybProject.h"

class CATBody;
class CATMathDirection;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSmartProject;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopSmartProject: public CATIPGMHybProject
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSmartProject();

  /**
	 * check that the complete wire has been projected on the shell
   * 0 : the check will be done
   * 1 : the check is not done
	 */
  virtual void SetNearOption(int iNear) = 0;

  //rlad
  virtual void SetDomainToProject(CATDomain *iDomain) = 0;

  virtual void SetRemoveArtefacts(int iRemoveArtefacts) = 0;

#ifdef CATIACGMR418CAA
  /** @nodoc */
  virtual void SetHandleMultiDomainBodies(CATBoolean iHandleMultiDomainBodies) = 0;

  /** @nodoc */
  virtual CATBoolean GetHandleMultiDomainBodies() const = 0;

#endif

  //rlaf
  /**
	 * Returns all the computed projections in a single body.
	 * @return
	 * The pointer to the resulting body. If you do not want to keep it, use the @href CATICGMContainer#Remove method
	 * to remove it from the geometric factory after the <tt>delet</tt>ion</tt> of <tt>this</tt> operator.
	 */
  virtual CATBody *GetResult() = 0;

  virtual CATBody *GetResult(CATCGMJournalList *iJourn) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSmartProject(); // -> delete can't be called
};

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSmartProject *CATPGMCreateTopSmartProject(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBody_To_Project,
  CATBody *iBody_Support,
  CATMathDirection *iDirection = NULL);

#endif /* CATIPGMTopSmartProject_h_ */
