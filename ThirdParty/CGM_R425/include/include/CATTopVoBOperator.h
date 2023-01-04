// COPYRIGHT DASSAULT SYSTEMES 2011
//=============================================================================
// Creation JHN  23/05/2011
//
// VoB check creation. tool to check body result of operations. 
// This chack can allow us to know specific configurations of body which are not expected by customer
//
//=============================================================================

#ifndef __CATTopVoBOperator_h__
#define __CATTopVoBOperator_h__

// #include "CATListPOfCATCheckDiagnoses.h"
#include "CATTopOperator.h"
#include "CATCGMVoBTool.h"
#include "CATCGMVoBResult.h"
#include "CheckOperators.h"
#include "CATCollec.h"

class CATExtTopOperator;
class CATTopData;
class CATGeoFactory;
class CATLISTP(CATBody);


class ExportedByCheckOperators CATTopVoBOperator: public CATTopOperator
{
public: // Methodes a usage externe
  CATCGMVirtualDeclareClass(CATTopVoBOperator);

  //============================
  // Constucteur et destructeurs
  //============================


  /**
  * @nodoc
  * Constructor - not to be used.
  */
  CATTopVoBOperator(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible); 

  virtual ~CATTopVoBOperator();
  virtual void SetJournalForCreation(CATCGMJournalList * iJournalObBodyToCheck)=0;
  virtual void SetInputBodies(CATLISTP(CATBody) * iInputBodies)=0;
  virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) & oLisOfResults)=0;
  virtual void GetVoBResults(CATLISTP(CATCGMVoBResult) & iFailureResults, CATBoolean iBlock, CATBoolean &iCompletion)=0;
  virtual int RunInBackground()=0;
};

ExportedByCheckOperators CATTopVoBOperator *
CATCreateTopVoBOperator(CATGeoFactory * iFactory,
                        CATTopData    * iData,
                        CATBody       * iBodyToCheck,
                        const CATCGMVoBCheckOptions & iTool);

#endif
