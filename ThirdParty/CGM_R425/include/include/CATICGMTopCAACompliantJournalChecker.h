#ifndef CATICGMTopCAACompliantJournalChecker_h_
#define CATICGMTopCAACompliantJournalChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMVirtual.h"
#include "CAATopCheckForPartType.h"
#include "CATBoolean.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATCGMJournalList;
class CATUnicodeString;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopCAACompliantJournalChecker;

/**
* Class defining an object that checks a topological journal.
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopCAACompliantJournalChecker: public CATICGMVirtual
{
public:
  /**
   * Constructor
   */
  CATICGMTopCAACompliantJournalChecker();

  /**
      * Adds an input body to the CATICGMTopCAACompliantJournalChecker object.
      * Must be called prior to running CAACheck method.
      */
  virtual int CAAAddInputBody(CATBody *iInputBody, CAATopCheckForPartType copyNoCopy) = 0;

  /**
      * Tests whether the check is valid.
      */
  virtual int CAACheck() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopCAACompliantJournalChecker(); // -> delete can't be called
};

/**
* Constructs a CATICGMTopCAACompliantJournalChecker object.
* @param iReport
* The pointer to the journal to be checked.
* @param iResult
* The pointer to resulting body.
* @param iFeatureName
* The feature name: mainly to be used when checking a feature - otherwise, any string
* can be specified.
* @param iErrorVerdictOutput
* The name of the stream that contains the check global verdict.
* @param iErrorWarningOutput
* The name of the stream that contains the check details (possible errors
* and warnings).
* @param iVerdictVerbose
* Specifies whether the verdict file must be restricted to the global verdict (FALSE)
* or must provide a verdict for each rule to be checked (TRUE):
* <ul>
* <li>the correct backtracking of cells (mandatory)
* <li>the existence of non bording cells in the report
* <li>the existence of geometry in the report
* <li>the appropriate naming of cells.
* </ul> 
* @param iHTML_OUTPUT
* Specifies whether check results are to be output in html format in the specified iErrorVerdictOutput
* and iErrorWarningOutput (TRUE).
* @return [out, IUnknown#Release]
* The check verdict: O if the check is valid - 1 if the check is invalid.  
*/
ExportedByCATGMOperatorsInterfaces CATICGMTopCAACompliantJournalChecker *CATCGMCreateTopCAACompliantJournalChecker(
  CATCGMJournalList *iReport,
  CATBody *iResult,
  const CATUnicodeString *iFeatureName,
  ostream *iErrorVerdictOutput,
  ostream *iErrorWarningOutput,
  CATBoolean iVerdictVerbose = TRUE,
  CATBoolean iHTML_OUTPUT = FALSE);

#endif /* CATICGMTopCAACompliantJournalChecker_h_ */
