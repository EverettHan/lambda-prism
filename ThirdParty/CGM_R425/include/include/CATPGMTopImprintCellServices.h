#ifndef CATPGMTopImprintCellServices_h_
#define CATPGMTopImprintCellServices_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATErrorDef.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATCGMJournal;
class CATCGMJournalInfo;
class CATCGMJournalList;
class CATCell;
class CATGeoFactory;
class CATGeometry;
class CATLISTP_CATGeometry_;
class CATSoftwareConfiguration;

/**
* Class offers services on Imprint Attributes.
*
*
*/
class ExportedByCATGMModelInterfaces CATPGMTopImprintCellServices
{
public:
  
#ifdef CATIACGMR421CAA
   /** 
   * Merge the tassed "standard journal", given as input, and its potential Imprint Journal in a single journal 
   * <br><b>Role</b>: return a journal that corresponds to the standard journal and the 
   *
   * @param piSoftConfig [in]
   *   Soft Config that drive algo level
   * @param piMasterJournal [in]
   *   Standard Journal that will be dumped
   * @param pioImprintJournal [in]
   *   Journal to fill, Life Cycle Management under caller resp. 
   * @return
   * <dl>
   * <dt><tt>S_OK</tt>     <dd>if succeeded
   * <dt><tt>E_FAIL</tt>    <dd>if failed
   * </dl>
   */
  static HRESULT GetStandardAndImprintJournal(
    CATSoftwareConfiguration *piSoftConfig,
    CATCGMJournalList *piMasterJournal,
    CATCGMJournalList *&pioStandardAndImprintJournal);
#endif
};

#endif /* CATPGMTopImprintCellServices_h_ */
