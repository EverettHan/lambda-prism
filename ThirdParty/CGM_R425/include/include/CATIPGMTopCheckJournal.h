#ifndef CATIPGMTopCheckJournal_h_
#define CATIPGMTopCheckJournal_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATJournalCheckRule.h"

class CATIPGMTopCAACompliantJournalChecker;
class CATICGMTopOperator;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopCheckJournal;

class ExportedByCATGMModelInterfaces CATIPGMTopCheckJournal: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCheckJournal();

  virtual void SetJournalCheckOption(
    CATJournalCheckRule iJournalCheckRule,
    CATBoolean iActivated) = 0;

  /** @nodoc  CheckJournal / pour donner les entrees de l'operateur ... */
  virtual void AddInputBody(
    CATBody *input,
    CATTopCheckJournalType copy_or_not = CATTopCheckCopy) = 0;

  /** @nodoc  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
  virtual void AddInputObject(
    CATICGMObject *obj,
    CATTopCheckJournalType copy_or_not = CATTopCheckNoCopy) = 0;

  /** @nodoc  CheckJournal / pour donner d'autres entree non Body (elements de sketch ...) ... */
  virtual void AddInputObjects(
    const CATLISTP(CATGeometry) &objs,
    CATTopCheckJournalType copy_or_not = CATTopCheckNoCopy) = 0;

  // throw an error on problem detection (throw is conditionned to "CATIPGMTopCheckJournal")
  virtual void Check() = 0;

  // renvoie 0 si le journal est OK ou n'a pas encore ete checke, sinon le journal est KO
  virtual int JournalIsNotGood() = 0;

  // methode statique de test d'ACTIVATION du check
  static CATBoolean CheckOn();

  //ATTENTION : l'argument lvl n'a plus de sens
  static void SetThrowOnError(int lvl = 2);

  static void UnsetThrowOnError();

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCheckJournal(); // -> delete can't be called
};

// Constructeur pour gestion pointue des traces (Feature tuning)
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCheckJournal *CATPGMCreateTopCheckJournal(
  CATICGMTopOperator *iOperator,
  CATGeoFactory *iFactory,
  const CATTopData &iReport,
  CATBody *iResult,
  const CATUnicodeString *ipFeatureName,
  CATBoolean iTraceManagement = FALSE,
  ostream *ipVerdictOutput = NULL,
  ostream *ipErrorWarningOutput = NULL,
  CATBoolean iVerboseCheckOK = TRUE,
  CATBoolean iVerboseCheckKO = TRUE,
  CATBoolean iCAACompliant = TRUE,
  CATBoolean iHTML_OUTPUT = FALSE);

// You must specify   Operator or complete definition Factory/CATTopData/Result
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMModelInterfaces CATIPGMTopCheckJournal *CATPGMCreateTopCheckJournal(
  CATICGMTopOperator *iOperator,
  CATGeoFactory *iFactory,
  const CATTopData &iReport,
  CATBody *iResult);

#endif /* CATIPGMTopCheckJournal_h_ */
