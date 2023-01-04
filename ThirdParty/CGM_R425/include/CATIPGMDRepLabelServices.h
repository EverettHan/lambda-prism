#ifndef CATIPGMDRepLabelServices_h_
#define CATIPGMDRepLabelServices_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATCGMJournalList;
class CATDRepLabel;
class CATDRepLabelAssoc;
class CATGMDRepLabelServicesImpl;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMDRepLabelServices;

class ExportedByCATGMModelInterfaces CATIPGMDRepLabelServices: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDRepLabelServices();

  virtual HRESULT GetDRepLabelImages(
    CATDRepLabel *iDRepLabel,
    CATDRepLabelAssoc *&oDRepLabelAssoc) = 0;

  virtual int RunOperator() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDRepLabelServices(); // -> delete can't be called
};

ExportedByCATGMModelInterfaces CATIPGMDRepLabelServices *CATPGMCreateGMDRepLabelServices(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) &iInputBodyList,
  CATLISTP(CATBody) &iOutputBodyList,
  CATCGMJournalList *iCMJournal);

#endif /* CATIPGMDRepLabelServices_h_ */
