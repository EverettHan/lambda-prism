#ifndef CATIPGMlsoJournalUtil_h_
#define CATIPGMlsoJournalUtil_h_

// COPYRIGHT DASSAULT SYSTEMES 2018
#include "IUnknown.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATBody.h"

class CATFace;
class CATGeoFactory;
class CATLiveBody;
class CATPersistentCellInfra;
class CATSoftwareConfiguration;
class CATVertex;
class CATlsoPersistentContext;
class CATCGMJournalList;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMlsoJournalUtil;

//=============================================================================
// CATIPGMlsoJournalUtil
// 
// responsable: LAP
// 
// Classe utilitaire pour l'operateur ModifyFace. Elle ne contient que des methodes
// statiques.
//=============================================================================
class ExportedByCATGMModelInterfaces CATIPGMlsoJournalUtil
{
public:
  /**
   * Constructor
   */
  CATIPGMlsoJournalUtil();

  static void CompleteMinimalValidJournal(
    CATLISTP(CATBody) &iInputCopyBodies,
    CATLISTP(CATBody) &iInputNoCopyBodies,
    CATBody *iResultBody,
    CATCGMJournalList &ioCellJournal);

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMlsoJournalUtil(); // -> delete can't be called
};

#endif /* CATIPGMlsoJournalUtil_h_ */
