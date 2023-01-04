#ifndef CATPGMCellManifoldsManager_h_
#define CATPGMCellManifoldsManager_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCollec.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATDeclarativeApplication.h"

class CATBody;
class CATCGMJournalList;
class CATGeoFactory;
class CATSoftwareConfiguration;
class CATLISTP(CATBody);
class CATDeclarativeManifoldAgent;
class CATLISTP(CATDeclarativeManifoldAgent);
class CATLISTP(CATCellManifold);
class CATListPtrCATDeclarativeManifold;
class CATMathTransformation;
class CATCGMHashTable;
class CATDeclarativeContext;
class CATCGMProgressBar;
class CATLISTP(CATFace);
class CATLISTP(CATLiveBody);
class CATLISTP(CATCellManifoldGroup);
class CATLISTP(CATVertex);
class CATPGMDRepBehavior;

#ifndef NULL
#define NULL 0
#endif

class ExportedByCATGMModelInterfaces CATPGMCellManifoldsManager
{
public:
  /**
   * Constructor
   */
  CATPGMCellManifoldsManager();

  /**
   * Destructor
   */
  virtual ~CATPGMCellManifoldsManager();

  virtual void TransferDataFromDRepBehavior(const CATPGMDRepBehavior *ipDRepBehavior) = 0;

  // User Defined Cutting Vertices
  virtual void SetUserDefinedCuttingVertices(
    CATLISTP(CATVertex) &iUserDefinedCuttingVertices) = 0;

  // CreateImageManifolds
  // iNoLiveBodyChecker permet de desactive le check du body creer lorsqu'on sait qu'il va etre faux.
  // Utilise dans les ODT pour tester des vieux models.
  virtual HRESULT CreateImageManifolds(CATCGMJournalList *iCellManifoldsJournal = NULL) = 0;

  virtual HRESULT CreateImageManifolds(
    CATCGMJournalList *iCellManifoldsJournal,
    CATBoolean iNoLiveBodyChecker) = 0;

  virtual HRESULT CreateImageManifoldGroups(
    CATCGMJournalList *iCellManifoldsJournal,
    CATBoolean iNoLiveBodyChecker) = 0;

  // For Recognizer
  virtual void SetDeclarativeContext(CATDeclarativeContext *iCATDeclarativeContext) = 0;

  virtual void SetDeclarativeApplication(
    CATDeclarativeApplication iDeclarativeApplication) = 0;

  // For Local Recognition
  virtual void SetUserDefinedSelection(CATLISTP(CATFace) &iUserSelection) = 0;

  virtual void GetUserDefinedSelection(CATLISTP(CATFace) &ioUserSelection) = 0;

  virtual CATCGMJournalList *GetJournal() = 0;

  virtual CATMathTransformation *GetGlobalTransformation() = 0;

  virtual CATCGMHashTable *GetGroupsCarriedBeforeManifoldGroupCarrier() = 0;

  virtual void SetBRepToDRepMode(CATBoolean iBRepToDRepMode) = 0;

  virtual void SetPatternOfPatternCollisionCM(
    CATLISTP(CATCellManifold) &iCollisionCMList) = 0;

  virtual CATLISTP(CATCellManifold) GetPatternOfPatternCollisionCM() = 0;

  virtual void SetPatternNumberOfInstances(int iNbInstances) = 0;

  virtual int GetPatternNumberOfInstances() = 0;

  virtual void SetPatternGroupsInInstances(
    CATLISTP(CATCellManifoldGroup) *iGroupLists) = 0;

  virtual CATLISTP(CATCellManifoldGroup) *GetPatternGroupsInInstances() = 0;

  virtual void SetLivificationInputLiveBodyList(
    CATLISTP(CATLiveBody) *ipLivificationInputLiveBodyList) = 0;

  virtual void SetFullDomainMove() = 0;

  virtual void SetIsLastRun(CATBoolean iIsLastRun) = 0;

  virtual void SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet) = 0;

  virtual void SetSplitterMode(int iContextualSplitterMode = 0) = 0;

  virtual void SetProgressBar(CATCGMProgressBar *ipProgressBar) = 0;

};

/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration * iConfig,
  CATLISTP(CATBody) &iListOfCopyInputBodies,
  CATBody *iOutputBody,
  CATCGMJournalList *iTopOpJournal);

/**
 * @return [out, delete]
 * Deprecated method : use the methode with a CATSoftwareConfiguration
 */
ExportedByCATGMModelInterfaces CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATLISTP(CATBody) &iListOfCopyInputBodies,
  CATBody *iOutputBody,
  CATCGMJournalList *iTopOpJournal);

/**
 * @return [out, delete]
 */
ExportedByCATGMModelInterfaces CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration * iConfig,
  CATBody *iBody);

/**
 * @return [out, delete]
 * Deprecated method : use the methode with a CATSoftwareConfiguration
 */
ExportedByCATGMModelInterfaces CATPGMCellManifoldsManager *CATPGMCreateCellManifoldsManager(
  CATGeoFactory *iFactory,
  CATBody *iBody);

#endif /* CATPGMCellManifoldsManager_h_ */
