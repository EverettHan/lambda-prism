#ifndef CATPersistentOperator_H
#define CATPersistentOperator_H

#include "PersistentCell.h"
#include "CATBoolean.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATIACGMLevel.h"

#ifdef CATIACGMR421CAA
#include "CATAdvancedOperator.h"
#else
#include "CATDRepOperator.h"
#endif

class CATPersistentExtTopOperator; 
class CATPersistentBody;
class CATlsoPersistentContext;
class CATCGMPad;
class CATCGMStream;
class CATPersistentCellInfra;

/* 
------------------------------------------------------------------------------
--------------------------!!! CAA Interface !!!-------------------------------
------------------------------------------------------------------------------
Be very carreful, this has a CAA Interface created in 2013 by SolidWorks
 GMOperatorsInterfaces\PublicInterfaces\CATICGMPersistentOperator.h
Don't forget : @nodoc @nocgmitf
------------------------------------------------------------------------------
*/

#ifdef CATIACGMR421CAA
class ExportedByPersistentCell  CATPersistentOperator : public CATAdvancedOperator
#else
class ExportedByPersistentCell  CATPersistentOperator : public CATDRepOperator
#endif
{
  CATCGMVirtualDeclareClass(CATPersistentOperator);
public:

  /**
  * @nodoc @nocgmitf
  * Cannot be called
  * Constructor
  */
  CATPersistentOperator(CATGeoFactory *        iFactory,
                        CATTopData    *        iTopData, 
                        CATPersistentExtTopOperator *iImpl);

  /**
  * @nodoc @nocgmitf
  * Destructor
  */
  virtual ~CATPersistentOperator();

  /** @nodoc @nocgmitf */
  virtual int RunOperator();

  /** @nodoc @nocgmitf */
  CATPersistentExtTopOperator * GetPersistentOperatorImpl() const;
  
  /** @nodoc @nocgmitf */
  void SetParentContext(CATlsoPersistentContext *iParentContext);

  /**
  * @nodoc @nocgmitf
  * Only use if the operator is created with a shared liveinfra
  */
  CATPersistentBody * GetResultPersistentBody() const;

  /** @nodoc @nocgmitf */
  void TransfertInterruptionToOtherContext(CATlsoPersistentContext * iContext);


  /** @nodoc @nocgmitf */
  CATCellManifoldsManager* CreateCellManifoldsManager(ListPOfCATBody    & iListOfCopyInputBodies, 
                                                      ListPOfCATBody    & iListOfNoCopyInputBodies,
                                                      CATBody           * iOutputBody, 
                                                      CATCGMJournalList * iTopOpJournal);
  /** @nodoc @nocgmitf */
  void SetBestResultMode(CATBoolean iBestResultMode);
  
  /** @nodoc @nocgmitf */
  void GetPersistentBodiesNecessaryForNextRun(ListPOfCATPersistentBodies &oPersistentBodiesNecessaryForNextRun);
  
   /** @nodoc @nocgmitf */
  virtual CATPersistentOperator * GetAsPersistentOperator() const;

protected:
  // -------------------------------------------------------------------------
  // LAP : List of methodes that should not be there.
  //       It's for operator that have no specifique code for extensible
  // -------------------------------------------------------------------------
    /** @nodoc @nocgmitf */
  CATPersistentCellInfra & GetPersistentCellInfra() const;

  // @nocgmitf
  CATlsoPersistentContext * GetContext() const;

  // @nocgmitf
  CATPersistentBody       * GetInputPersistentBody(CATBoolean iForceInputOnly=FALSE,int index=1) const;

  // @nocgmitf
  void SetPersistentResultBody(CATPersistentBody * iResultPBody);

  // @nocgmitf
  void SetJournalForLastResult(CATCGMJournalList * iJournal,CATBoolean iRecordACopy=FALSE, CATBoolean iAllowEmptyJournal=FALSE);

  // @nocgmitf
  CATBoolean                IsInfraShared() const;

  // @nocgmitf
  // Return TRUE if the record is done.
  CATBoolean SetPersistentBodyResultAndLastJournalResult(CATPersistentBody * iResultPBody,
                                                         CATCGMJournalList * iJournal,
                                                         CATBoolean          iRecordAJournalCopy=FALSE);
  // @nocgmitf
  void SetInputAsOutputProtection(CATBoolean iProtection);

  // @nocgmitf
  CATBody                 & GetInputBody() const;

  // @nocgmitf
  // for CGMReplay
  void Dump(CATCGMOutput& os);
  
  // for CGMReplay Only
  virtual void DumpOutput(CATCGMOutput& os);

};

#endif
