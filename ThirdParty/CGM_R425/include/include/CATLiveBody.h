#ifndef CATLiveBody_h
#define CATLiveBody_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCGMStreamAttribute.h"
#include "CATICGMObject.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATManifoldGroup.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfShort.h"
#include "ListPOfCATManifold.h"

#include "CATDeclarativeContext.h"
#ifdef CATIAR207
#include "CATLISTP_CATBaseUnknown.h"
#endif
#include "CATListOfCATGeometries.h"

class CATBody;
class CATCell;
class CATFace;
class CATCellManifold;
class CATDeclarativeManifold;
class CATDatumManifold;
class CATBoneFillet;
class CATJointFillet;
class CATJointChamfer;
class CATSubdivisionManifold;
class CATPlaneManifold;
class CATCylinderManifold;
class CATSphereManifold;
class CATConeManifold;
class CATTorusManifold;
class CATBoneChamfer;
class CATHierarchicalManifoldGroup;
class CATContextualManifoldGroup;
class CATSoftwareConfiguration;
class CATMathTransformation;
class CATCGMJournalList;
class CATHEdge;
class CATIntersectionHVertex;
class CATHVertex;
class CATRatioHVertex;
class CATDistanceHVertex;
class CATDraftManifold;
class CATCellManifoldGroup;
class CATCellManifoldGroupLayer;
class CATCGMJournal;
class CATHGeometry;
class CATCGMHashTable;
class CATButtonManifold;
class CATGeometry;
class CATLISTP(CATHGeometry);

#include "CATGMModelInterfaces.h"
#include "CATDeclarativeApplication.h"
#include "ListPOfCATCellManifoldGroupLayer.h"


class ExportedByCATGMModelInterfaces CATLiveBody : protected CATCGMStreamAttribute
{
  public:

  static CATLiveBody* GetLiveBody(CATBody *iBody);

  CATLiveBody();
  virtual ~CATLiveBody();
  CATCGMNewClassArrayDeclare;      // Pool allocation


  // --------------------------------------------------------------------------
  // Data access
  // --------------------------------------------------------------------------
  virtual CATBody* GetBody() const=0;

	// The hash table is allocated by the method. Think to delete it after usage.
  virtual CATCGMHashTable * GetDeclarativeManifolds() const = 0;
  virtual void							GetDeclarativeManifolds(ListPOfCATDeclarativeManifold &oDeclarativeManifolds) const=0;
  virtual void							GetSortedDeclarativeManifolds(ListPOfCATDeclarativeManifold &oDeclarativeManifolds) const=0;

  virtual int                     GetNbDeclarativeManifolds() const=0;
  virtual CATDeclarativeManifold* GetDeclarativeManifold(const int iDeclarativeManifoldIndex) const=0;
  virtual HRESULT                 Contains(const CATDeclarativeManifold* iDeclarativeManifold) const=0;

  // @param iDimension : -1 All the dimensions - 0 the vertices - 1 the edges - 2 the faces
	// The hash table is allocated by the method. Think to delete it after usage.
  virtual CATCGMHashTable * GetCellManifolds(short iDimension=-1) const=0;
  virtual void              GetCellManifolds(ListPOfCATCellManifold &oCellManifolds, short iDimension=-1) const=0;
  virtual void							GetCellManifolds(CATLISTP(CATGeometry)  &oGeometries) const=0;

  virtual int               GetNbCellManifolds() const=0;
  virtual CATCellManifold * GetCellManifold(const int iCellManifoldIndex) const=0;
  virtual HRESULT           Contains(const CATCellManifold* iCellManifold) const=0;

  virtual void							GetManifolds(ListPOfCATManifold &oManifolds) const=0;

  virtual void    GetHGeometries(CATLISTP(CATHGeometry) &oHGeometries) const=0;
  virtual HRESULT Contains(const CATHGeometry* iHGeometry) const=0;

  virtual void GetManifoldGroups(ListPOfCATManifoldGroup &oManifoldGroups) const=0;
  virtual void GetCellManifoldGroups(const CATCellManifoldGroupLayer* iGroupLayer, ListPOfCATCellManifoldGroup &oManifoldGroups) const=0;
  virtual void GetCellManifoldGroups(const ListPOfCATCellManifoldGroupLayer &iGroupLayers, ListPOfCATCellManifoldGroup &oManifoldGroups) const=0;

  // Deprecated methode : Do not use. It's only for Copy/Paste of NaturalShape
  virtual CATDeclarativeContextIndustry GetDeclarativeContextIndustry() const=0;

  // --------------------------------------------------------------------------
  //  Data access : Only use for debug tools
  // --------------------------------------------------------------------------
  virtual HRESULT GetAllCellManifoldGroups(ListPOfCATCellManifoldGroup & oAllCellManifoldGroupList) const=0;

  // ------------------------------------------------------------------------------
  // CDM - Utilities
  // ------------------------------------------------------------------------------
  // Return ManifoldList associated to ipCell if they can be under CDM Constraints.
  virtual  HRESULT GetManifoldToConstraint(CATCell *ipCell, ListPOfCATManifold &oManifoldToConstraint) const = 0;

  // --------------------------------------------------------------------------
  // Visualization object
  // --------------------------------------------------------------------------
  virtual HRESULT CreateCharacteristicGeometry(CATSoftwareConfiguration *ipConfig, CATGeometry *ipGeometry, int iContractType, CATGeometry *&oCreatedGeometry) const = 0;

  // --------------------------------------------------------------------------
  // DRep Namming
  // --------------------------------------------------------------------------
  virtual void GetManifoldWithPersistentName(CATCGMHashTable &oPublishedManifold) const = 0;

  // --------------------------------------------------------------------------
  // XVM access
  // --------------------------------------------------------------------------
#ifdef CATIAR207
  virtual HRESULT GetXVMRef(CATBaseUnknown *&oXVMRef, const CLSID& iType) const=0;
  //virtual HRESULT DuplicateConstraint(const CATLISTP(CATBaseUnknown) & iDomainXVM, const CATLISTP(CATGeometry) & iDomainCGM, CATLiveBody * ioTargetLiveBody, CATCGMJournal * iCGMJournal, int iJournalMode = 0, CATBoolean iStatelessXVMBody = FALSE) const =0;
  // @Deprecated
  virtual HRESULT SynchronizeXVM(CATLiveBody *InputLiveBody, CATCGMJournalList *iJournal) =0;
#endif

  // --------------------------------------------------------------------------
  // Utilities
  // --------------------------------------------------------------------------
  virtual HRESULT GetConnectedCellManifolds(const ListPOfCATCellManifold &iInitialCellManifold, ListPOfCATCellManifold &oConnectedCellManifold, CATBoolean iOnlySmoothAdjacency = FALSE, CATSoftwareConfiguration* iConfig = NULL)=0;
  virtual HRESULT GetConnectedDeclarativeManifolds(const ListPOfCATDeclarativeManifold &iInitialDeclarativeManifold, ListPOfCATDeclarativeManifold &oConnectedDeclarativeManifold, CATBoolean iOnlySmoothAdjacency = FALSE, CATSoftwareConfiguration* iConfig = NULL)=0;
  virtual HRESULT GetDependentDeclarativeManifolds(const CATDeclarativeManifold* iDeclarativeManifold, ListPOfCATDeclarativeManifold& oDependantDeclarativeManifold, CATSoftwareConfiguration* iConfig)=0; // S_OK if any
  virtual HRESULT GetDependentDeclarativeManifolds(const ListPOfCATDeclarativeManifold &iDeclarativeManifold, ListPOfCATDeclarativeManifold& oDependantDeclarativeManifold, CATSoftwareConfiguration* iConfig)=0; // S_OK if any
  virtual HRESULT GetCellManifoldFromCells(const ListPOfCATCell & iCells, ListPOfCATCellManifold &oCellManifold) const=0;
  virtual CATCellManifold         * GetCellManifoldFromCell(CATCell* iCell) const=0;
  virtual CATDeclarativeManifold  * GetDeclarativeManifoldFromCell(CATCell* iCell) const=0;
  virtual void                      GetDeclarativeManifoldFromCells(const ListPOfCATCell & iCells, ListPOfCATDeclarativeManifold &oDeclarativeManifold) const=0;
  virtual void                      GetDeclarativeManifoldFromCells(const ListPOfCATCell & iCells, CATCGMHashTable & oDeclarativeManifoldsHT) const = 0;
  virtual CATManifoldGroup        * GetManifoldGroupFromDeclarativeManifold(CATDeclarativeManifold* iDeclarativeManifold) const=0;
  virtual CATCellManifoldGroup    * GetCellManifoldGroupFromCellManifold(CATCellManifold* iCellManifold, CATCellManifoldGroupLayer* iGroupLayer) const=0;
  virtual void                      GetCellManifoldGroupsFromCellManifold(CATCellManifold* iCellManifold, const CATCellManifoldGroupLayer* iGroupLayer, ListPOfCATCellManifoldGroup &oManifoldGroups) const=0;
  virtual CATCellManifoldGroup    * GetCellManifoldGroupParent(CATCellManifoldGroup* iCellManifoldGroup, CATCellManifoldGroupLayer* iGroupLayer) const=0;

  // Duplicate this CATLiveBody and its CATBody
  //  iFactory  factory where this CATLiveBody should be duplicated, it can be the same factory as the container of this CATLiveBody or not
  //  iConfig the software configuration (mandatory)
  //  iMathTransfo the CATMathTransformation to apply to the duplication, it can be NULL in this case no transformation is applied
  //  oResultBody the pointer to the result CATBody with an attached CATLiveBody
  //  oJournal if not NULL this CATCGMJournalList is fullfilled with the CellManifold journal from this CATLiveBody to the result CATLiveBody
  virtual HRESULT Duplicate(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig,
    CATMathTransformation *iMathTransfo, CATBody *& oResultBody, CATCGMJournalList * oJournal = NULL, CATBoolean iCopyXVM=TRUE) const=0;
  // @Nodoc
  virtual HRESULT DuplicateWithCellManifoldCells(CATGeoFactory *iFactory, CATSoftwareConfiguration *iConfig, CATBody *& oResultBody, CATCGMJournalList * oJournal = NULL) const=0;

  // ----------------------------------------------------------
  // DREP Color Management
  // RGB [0-255]
  // ----------------------------------------------------------
  // Return RBG [0-255] color of DRepFeature type
  // Exposed. Dedicated to Application
  static void  GetUserColor(CATGeometricType iType, CATDeclarativeApplication iApplication, int &oR, int &oG, int &oB);

  // --------------------------------------------------------------------------
  // Factory methods
  // --------------------------------------------------------------------------
  virtual CATCellManifold* CreateCellManifold(ListPOfCATCell &iCells)=0;

  virtual CATDatumManifold*         CreateDatumManifold()=0;
  virtual CATBoneFillet*            CreateBoneFillet()=0;
  virtual CATJointFillet*           CreateJointFillet()=0;
  virtual CATJointChamfer*          CreateJointChamfer()=0;
  virtual CATSubdivisionManifold*   CreateSubdivisionManifold()=0;
  virtual CATPlaneManifold*         CreatePlaneManifold()=0;
  virtual CATCylinderManifold*      CreateCylinderManifold()=0;
  virtual CATSphereManifold*        CreateSphereManifold()=0;
  virtual CATConeManifold*          CreateConeManifold()=0;
  virtual CATTorusManifold*         CreateTorusManifold()=0;
  virtual CATBoneChamfer*           CreateBoneChamfer()=0;
  virtual CATHEdge*                 CreateHEdge()=0;
  virtual CATIntersectionHVertex*   CreateIntersectionHVertex()=0;
  virtual CATRatioHVertex*          CreateRatioHVertex()=0;
  virtual CATDistanceHVertex*       CreateDistanceHVertex()=0;
  virtual CATDraftManifold*         CreateDraftManifold()=0;
  virtual CATButtonManifold*        CreateButtonManifold()=0;

  virtual CATContextualManifoldGroup* CreateContextualManifoldGroup(ListPOfCATDeclarativeManifold &iRep, CATListOfShort* iType, ListPOfCATDeclarativeManifold &iContext, CATListOfShort* iContextType = NULL)=0;

  virtual CATCellManifoldGroup*     CreateCellManifoldGroup(ListPOfCATCellManifold &iRep, CATCellManifoldGroupLayer* iGroupLayer)=0;
  virtual CATCellManifoldGroup*     CreateCellManifoldGroup(ListPOfCATCellManifold &iLeaves, ListPOfCATCellManifoldGroup &iSons, CATCellManifoldGroupLayer* iGroupLayer)=0;
  virtual CATCellManifoldGroup*     CreateCellManifoldGroup(ListPOfCATCellManifold &iRep, CATListOfShort &iType, CATCellManifoldGroupLayer* iGroupLayer)=0;
  virtual CATCellManifoldGroup*     CreateCellManifoldGroup(const ListPOfCATCellManifold &iRep, CATListOfShort* iType, const ListPOfCATCellManifold &iContext, const CATListOfShort &iContextType, CATCellManifoldGroupLayer* iCMGroupLayer)=0;

  virtual void AddCellManifold(CATCellManifold* iCellManifold)=0;
  virtual void AddDeclarativeManifold(CATDeclarativeManifold* iDeclarativeManifold)=0;
  virtual void AddHGeometry(CATHGeometry* iHGeometry)=0;   
  virtual void AddCellManifoldGroup(CATCellManifoldGroup* iCellManifoldGroup)=0;

  virtual HRESULT Remove(CATDeclarativeManifold* ioDeclarativeManifold)=0;
  virtual HRESULT Remove(CATCellManifold* ioCellManifold)=0;
  virtual HRESULT Remove(CATCellManifoldGroup* ioCellManifoldGroup)=0;
  virtual HRESULT Remove(CATHGeometry* ioHGeometry)=0;

  //---------------------------------------------------------------------------
  // CGM Private - DO NOT USE
  //---------------------------------------------------------------------------

  //For LiveChecker Only. It avoids multiple check and activates
  virtual void SetValidationOK()=0;
  virtual CATBoolean IsCheckedAndValid()=0;
  //  virtual void Dump(CATCGMOutput& os)=0;
  //  virtual CATICGMObject* Clone(CATCloneManager& iCloneManager) const=0;

};
#endif
  
