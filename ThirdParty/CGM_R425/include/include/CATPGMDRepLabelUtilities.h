#ifndef CATPGMDRepLabelUtilities_h_
#define CATPGMDRepLabelUtilities_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMModelInterfaces.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATManifold.h"
#include "CATErrorDefs.h"

class CATBody;
class CATCGMJournalList;
class CATDRepLabel;
class CATDRepLabelAssoc;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATManifold;
class CATManifoldParamId;

//#define DREPLABEL_TEST_VB7 //To generate DRepLabelServices CGMReplay in our ODTs
class ExportedByCATGMModelInterfaces CATPGMDRepLabelUtilities
{
public:
  /**
   * Destructor
   */
  virtual ~CATPGMDRepLabelUtilities();

  virtual CATManifold * GetManifold(CATBody & iBody, const CATDRepLabel * iDRepLabel) = 0;
  virtual CATManifold * GetManifold(const CATLISTP(CATBody) & iBodyList, const CATDRepLabel *ipDRepLabel, CATBody **oFoundBody = NULL) = 0;

  // Allocated memory 
  // @param oParamIDWithValue must be released after use. 
  virtual HRESULT       CreateParamIDWithValue(CATBody * ipBody, const CATDRepLabel * ipDRepLabel, const CATManifoldParamId * ipParamID, CATManifoldParamId *& oParamIDWithValue) = 0;

  /**
  * Retrieve images of a single CATManifold via a CGMJournal.
  * @param iInitialManifold
  *   A pointer to the Manifold to follow.
  * @param ipCurrentBody
  *   The current body result on which we will get the images.
  * @param ipCellManifoldJournal
  *   A CGMJournal related to ipCurrentBody.
  * @oaram oManifoldImageList
  *   The retrieved images from iInitialManifold.
  */
  virtual HRESULT       GetImageManifolds(CATManifold *iInitialManifold, CATBody * ipCurrentBody, CATCGMJournalList *ipCellManifoldJournal, ListPOfCATManifold &oManifoldImageList) const = 0;

  // Do not use
  virtual HRESULT GetDRepLabelImages(CATDRepLabel * ipDRepLabel, CATDRepLabelAssoc *& oDRepLabelAssoc) = 0;

protected :
 /**
  * Constructor
  */
 CATPGMDRepLabelUtilities();

};

// create
ExportedByCATGMModelInterfaces CATPGMDRepLabelUtilities *CATPGMCreateGMDRepLabelUtilities(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATLISTP(CATBody) &iInputBodyList,
  CATLISTP(CATBody) &iOutputBodyList,
  CATCGMJournalList *iCMJournal);

//To use with GetManifold method
ExportedByCATGMModelInterfaces CATPGMDRepLabelUtilities *CATPGMCreateGMDRepLabelUtilities(
  CATSoftwareConfiguration *iConfig = NULL);

#endif /* CATPGMDRepLabelUtilities_h_ */
