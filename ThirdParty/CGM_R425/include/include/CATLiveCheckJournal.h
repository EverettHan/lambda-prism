#ifndef CATLiveCheckJournal_h_
#define CATLiveCheckJournal_h_

// COPYRIGHT DASSAULT SYSTEMES  2002

#include "ExportedByCATTopologicalObjects.h"         // for windows nt
#include "CATTopOperator.h"
#include "CATBoolean.h"
#include "ListPOfCATBody.h"

class CATGeoFactory;
class CATLiveBody;
class CATBody;
class CATTopData;
class CATCGMJournalList;
class CATUnicodeString;

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

/**
 * Class describing the object whereby you check whether
 * a topological journal is valid.
 */

// Specify whether an input body is to be added in Copy or No Copy mode
enum CATLiveCheckJournalType {CATLiveCheckNoCopy=32, CATLiveCheckCopy=33};

class ExportedByCATTopologicalObjects CATLiveCheckJournal 
{
public:
    
    // Destructor
    virtual ~CATLiveCheckJournal();
    
/**
* Constructs a CATLiveCheckJournalExp object.
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
* @return
* The check verdict: O if the check is valid.  
*/
    CATLiveCheckJournal (CATCGMJournalList * iReport,
        CATBody * iResult,
        const CATUnicodeString* iFeatureName,
        ostream*                iErrorVerdictOutput,
        ostream*                iErrorWarningOutput,
        CATBoolean verboseVerdict = TRUE,
		CATBoolean  iHTML_OUTPUT=FALSE);
    
    // Add an input body to the CATLiveCheckJournal object
    // is needed prior to running CAACheck
    int AddInputBody(CATBody * iInputBody);
    
    // Test whether the journal is valid
    int Check();

private :
    
    CATCGMJournalList     * _iReport;          // the journal to be tested
    CATBoolean _iVerdictVerbose;
    const CATUnicodeString*  _iFeatureName;    // the feature name
    ostream*  _iErrorWarningOutput;            // the warning file
    ostream*  _iErrorVerdictOutput;            // the verdict file
    CATBody               * _iResult;          // the result body
    CATLISTP(CATBody)       _InputsCopy;       // the list of bodies in copy mode
    CATBoolean              _HTML_OUTPUT;      // HTML formated output request
  
};

#endif
