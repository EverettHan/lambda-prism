#ifndef CATIPGMTopVoBOperator_h_
#define CATIPGMTopVoBOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"
#include "CATCGMVoBCheckOptions.h"

class CATExtTopOperator;
class CATGeoFactory;
class CATTopData;
class CATCGMJournalList;
class CATLISTP(CATBody);
class CATLISTP(CATCGMVoBResult);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopVoBOperator;

class ExportedByCATGMOperatorsInterfaces CATIPGMTopVoBOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopVoBOperator();

  virtual void SetJournalForCreation(CATCGMJournalList *iJournalObBodyToCheck) = 0;

  virtual void SetInputBodies(CATLISTP(CATBody) *iInputBodies) = 0;

  virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) &oLisOfResults) = 0;

  virtual void GetVoBResults(
    CATLISTP(CATCGMVoBResult) &iFailureResults,
    CATBoolean iBlock,
    CATBoolean &iCompletion) = 0;

  virtual int RunInBackground() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopVoBOperator(); // -> delete can't be called
};

/**
 * @return [out,IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopVoBOperator *CATPGMCreateTopVoBOperator(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToCheck,
  const CATCGMVoBCheckOptions &iTool);

#endif /* CATIPGMTopVoBOperator_h_ */
