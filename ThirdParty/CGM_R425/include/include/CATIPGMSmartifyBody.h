#ifndef CATIPGMSmartifyBody_h_
#define CATIPGMSmartifyBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2011

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATExtTopOperator;
class CATGeoFactory;
class CATTopData;
class CATCGMOutput;
class CATListValCATUnicodeString;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMSmartifyBody;

/** 
 * Class representing the operator that takes a body <ToSmartify>, and creates a result body that:
 *  1) will be geometrically identical to the input body <ToSmartify>
 *  2) will share as many geometrical and topological elements with another body <Reference>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMSmartifyBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMSmartifyBody();

  /**  
   * @nodoc
  * To be called before Run.
  * Activates or deactivates journaling on internal cells.
  * If not called, journaling on internal cells is not done by default.
  */
  virtual void SetFullJournal(CATBoolean iFullJournal) = 0;

  /**  
   * @nodoc
  * To be called after Run.
  * Value representing the efficacy of smartification (a.k.a. "smart level").
  * The real meaning of this value depends on the method used to create the operator,
  * because different types of smartification exist.
  */
  virtual CATLONG32 GetNbRetrieved1stLevelElements() = 0;

  /**
  * @nodoc
  * To be called after Run.
  * Returns the result of the transformation of the body at position iIdx in input list.
  * If ioJournal is not NULL and journaling is active,
  * the journal describing the transformation of the body is duplicated inside ioJournal.
  */
  virtual CATBody *GetSmartifiedBody(int iIdx, CATCGMJournalList *ioJournal) = 0;

  /**
  * @nodoc
  * Internal use only.
  */
  virtual CATBoolean CheckAfterRun(
    CATListValCATUnicodeString &oSucceeding,
    CATListValCATUnicodeString &oFailing) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMSmartifyBody(); // -> delete can't be called
};

#endif /* CATIPGMSmartifyBody_h_ */
