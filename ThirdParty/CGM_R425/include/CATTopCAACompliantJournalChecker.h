#ifndef CATTopCAACompliantJournalChecker_H_
#define CATTopCAACompliantJournalChecker_H_

// COPYRIGHT DASSAULT SYSTEMES  2003

/**
 * @level Protected
 * @usage U1
 */ 

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMVirtual.h"
#include "CATCGMNewArray.h"
#include "CATTopOperator.h"
#include "CAATopCheckForPartType.h"

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

class CATGeoFactory;
class CATBody;
class CATTopData;

/**
* Class defining an object that checks a topological journal.
*/
class ExportedByCATTopologicalObjects CATTopCAACompliantJournalChecker : public CATCGMVirtual
{
  CATCGMVirtualDeclareClass(CATTopCAACompliantJournalChecker);
public :
    // Destructor
     virtual ~CATTopCAACompliantJournalChecker();
     
/**
* Constructs a CATTopCAACompliantJournalChecker object.
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
* @return
* The check verdict: O if the check is valid - 1 if the check is invalid.  
*/
    CATTopCAACompliantJournalChecker (CATCGMJournalList*      iReport,
                                      CATBody*                iResult,
                                      const CATUnicodeString* iFeatureName,
                                      ostream*                iErrorVerdictOutput,
                                      ostream*                iErrorWarningOutput,
                                      CATBoolean              iVerdictVerbose = TRUE,
                                      CATBoolean              iHTML_OUTPUT = FALSE);

     /** @nodoc */
      CATCGMNewClassArrayDeclare;
      /**
      * Adds an input body to the CATTopCAACompliantJournalChecker object.
      * Must be called prior to running CAACheck method.
      */
      int CAAAddInputBody(CATBody * iInputBody, CAATopCheckForPartType copyNoCopy);
    
     /**
      * Tests whether the check is valid.
      */
    int CAACheck();

//#ifdef CATIACGMV5R20
//     /** @nodoc */
//      CATBoolean IsABordingCell(CATCell* iCell, CATBody* inBody);
//#endif
    
private :
    
    CATCGMJournalList     * _iReport;          // the journal to be tested
    CATBoolean _iVerdictVerbose;
    const CATUnicodeString*  _iFeatureName;    // the feature name
    ostream*  _iErrorWarningOutput;            // the warning file
    ostream*  _iErrorVerdictOutput;            // the verdict file
    CATBody               * _iResult;          // the result body
    CATLISTP(CATBody)       _InputsCopy;       // the list of bodies in copy mode
    CATLISTP(CATBody)       _InputsNoCopy;     // the list of bodies in no copy mode
    CATBoolean              _HTML_OUTPUT;      // HTML formated output request

};

#endif
