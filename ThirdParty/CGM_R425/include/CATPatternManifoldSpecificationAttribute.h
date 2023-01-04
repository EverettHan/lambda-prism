#ifndef CATPatternManifoldSpecificationAttribute_h
#define CATPatternManifoldSpecificationAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATCellManifold.h"
#include "CATMathTransformation.h"
#include "CATListOfShort.h"
#include "CATCollec.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATPatternActivationStatus.h"
#include "CATMathInline.h"
#include "CATPatternBuildingType.h"
#include "CATInstancesManifoldSpecificationAttribute.h"
#include "ListPOfCATGMLivePatternFollowers.h"
#include "CATCellManifoldGroupCarrier.h"

class CATCloneManager;
class CATTransfoManager;
class CATCellManifoldPatternNavigator;
class CATDRepReferenceManager;
class CATDeclarativeOperatorsBridge;
class CATLISTP(CATMathTransformation);
class CATLISTP(CATCellManifold);
class CATLISTP(CATDeclarativeManifold);
class CATGMLivePatternFollower;
class CATPersistentCellInfra;

class ExportedByPersistentCell CATPatternManifoldSpecificationAttribute : public CATInstancesManifoldSpecificationAttribute
{
public:
  CATCGMDeclareAttribute (CATPatternManifoldSpecificationAttribute,CATManifoldAttribute);

  CATPatternManifoldSpecificationAttribute(); // Default constructor is mandatory
  CATPatternManifoldSpecificationAttribute(short iNbInstances, const CATMathTransformation &iUnitaryTransfo, const CATPatternBuildingType iBuildingType);  

  // CATPatternManifoldSpecificationAttribute(short iNbInstances, const CATMathVector &iTranslationVector, const CATPatternBuildingType iBuildingType);  // To remove
  // CATPatternManifoldSpecificationAttribute(short iNbInstances, const CATMathLine &iRotationAxis, double iRotationAngle, const CATPatternBuildingType iBuildingType); // To remove

  CATPatternManifoldSpecificationAttribute(const CATPatternManifoldSpecificationAttribute &iAttributeToCopy);
  CATPatternManifoldSpecificationAttribute(short                                  iNbInstances,
                                           const CATMathTransformation          & iUnitaryTransfo,
                                           const CATListOfShort                 * iInactivatedInstance,
                                           const CATListOfShort*                  iInactivatedTypes,
                                           const CATListOfShort*                  iInstanceWithSecondaryTransformations,
                                           const CATLISTP(CATMathTransformation)* iSecondaryTransformations,
                                           const CATLISTP(CATICGMObject)        & iLinkedObjects,
                                           const CATPatternBuildingType           iBuildingType );

  virtual ~CATPatternManifoldSpecificationAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE void SetPatternBuildingType(CATPatternBuildingType iType);
  INLINE CATPatternBuildingType GetPatternBuildingType() const;

  void SetReferencePattern(CATLiveBody* iRefLiveBody);
  void SetReferencePatternOfPattern(ListPOfCATCellManifoldGroup & iRefCellManifoldGroups);
  void AddInactivatedInstance(short iInstance);
  void SetInstanceActivationStatus(short iInstance, CATPatternActivationStatus iStatus);
  void SetActivationStatus(CATListOfShort& iInactivatedInstance, CATListOfShort& iInactivationTypes);
  void SetSecondaryTransfo(short iInstance, CATMathTransformation & iSecondaryTransfomation);
  HRESULT GetSecondaryTransfo(short iInstance, CATMathTransformation & oSecondaryTransfomation) const;

  short GetPatternType() const;
  HRESULT GetTranslationVector(CATMathVector &ioTranslationVector) const;
  HRESULT GetRotationData(CATMathLine &ioRotationAxis, double &ioRotationAngle) const;
  HRESULT GetUnitaryTransformation(CATMathTransformation &ioUnitaryTransfo) const;
  HRESULT GetSecondaryTransfoData(CATListOfShort &ioInstanceWithSecondaryTransformations, CATLISTP(CATMathTransformation) &ioSecondaryTransformations) const;
  HRESULT GetActivationStatus(CATListOfShort& oInactivatedInstance, CATListOfShort& oInactivationTypes) const;
  CATLiveBody* CreateReferenceLiveBody(CATBoolean iChangeLocation=FALSE);
  CATLiveBody* CreateReferenceLiveBody(int iInstance);
  CATBoolean IsInstanceActive(short iInstance) const;
  CATPatternActivationStatus GetActivationStatus(short iInstance) const;

  HRESULT GetAllReferenceCellManifolds(CATLISTP(CATCellManifold) &ioReferenceCellManifolds);
  HRESULT GetReferenceCellManifolds(CATLISTP(CATCellManifold) &ioReferenceCellManifolds); // Linked CellManifolds without border ones
  HRESULT GetReferenceEdgeManifolds(CATLISTP(CATCellManifold) &ioReferenceEdgeManifolds);
  HRESULT GetReferenceCellManifoldGroups(CATLISTP(CATCellManifoldGroup) &ioReferenceCellManifoldGroups, const CATCellManifoldGroupLayer * iCMGLayer);

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &ImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void ComputeSpecificTreatment(
    const CATLISTP(CATCellManifoldGroup) & iParentGroups,
          CATLISTP(CATCellManifoldGroup) & ioImageSonList, 
    CATCellManifoldGroupCarrier          * iCellManifoldGroupCarrier) const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;

  void SetPatternOfPatternIsBeingCreated(CATBoolean iPatternOfPatternIsBeingCreated);
  CATBoolean PatternOfPatternIsBeingCreated();

  HRESULT GetPatternOfPatternReferences(CATLISTP(CATCellManifold) &oReferenceCellManifolds, CATLISTP(CATCellManifoldGroup) &oReferenceCellManifoldGroups, CATLiveBody *& oRefLiveBody);
  HRESULT GetPatternOfPatternReferences(CATLISTP(CATCellManifold) &oReferenceCellManifolds, CATLISTP(CATCellManifoldGroup) &oReferenceCellManifoldGroups);

  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  void UpdateReference(CATMathTransformation & iTransfo, CATCellManifoldGroup* ipNewPattern,CATCellManifoldGroup* ipOldPattern, CATSoftwareConfiguration* iConfig,CATPersistentBody *iNewPersistentBody);

  CATGeoFactory * GetFactory() const;

  // Pour BodiesMapping
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

  // Pour Debug
  int GetDebugTag();

     // On donne en entree le journal du move entre l'ancienne reference et la nouvelle reference.
  HRESULT UpdateReference(CATCGMJournalList * iRefTransfoJournal, CATBody * iNewRefBody);
  void UpdateReference(CATCellManifoldGroup* ipNewPattern, CATCGMJournalList * iRefTransfoJournal, CATBody * iNewRefBody,CATCellManifoldGroup* ipOldPattern, CATSoftwareConfiguration* iConfig,ListPOfCATGMLivePatternFollowers &iPatternFollowerList,CATPersistentBody *iNewPersistentBody);

  HRESULT DeleteRefCM(CATLISTP(CATCellManifold) &iReferenceCellManifoldsToDelete, CATDeclarativeOperatorsBridge * iRemoveFaceRunner, CATSoftwareConfiguration* iConfig, CATCGMJournalList *& oJournal);
  HRESULT DeleteRefCMG(CATLISTP(CATCellManifoldGroup) &iReferenceCellManifoldGroupsToDelete, CATSoftwareConfiguration* iConfig, CATCGMJournalList *& oJournal);

  HRESULT GetOriginPoint(CATCellManifoldGroup * iNetworkgroup, CATMathPoint & oOriginPoint) const;

  
  INLINE virtual CATPatternManifoldSpecificationAttribute *GetAsPatternManifoldSpecificationAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  virtual void AfterGroupCreationActions(CATCGMJournalList *ioCellManifoldGroupJournal, CATCellManifoldGroupCarrier *iCellManifoldGroupCarrier);
  
  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          *iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);
  
  virtual HRESULT ComputeNotUpToDateCMs(
    CATCellManifoldGroup        * iParentCellManifoldGroup,
    CATCellManifoldGroup        * iImageCellManifoldGroup,
    CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

  virtual void OrganizeSonImageByGroup(
    ListPOfCATCellManifoldGroup         &iCellManifoldGroupsToCarry, 
    ListPOfCATCellManifoldGroup         &iParentSonsImages,
    CATCellManifoldGroupCarrier         *iCellManifoldGroupCarrier,
    ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);

  // Methodes utilisees pour le test du stream/unstream pour les elements non utilises en 2012x
  void SetSecondaryTransformationsTypes(CATListOfShort* iSecondaryTransformationsTypes);
  void SetReferenceManager(CATDRepReferenceManager * iReferenceManager);
  void SetDesactivatedInstancesData(CATLISTP(CATManifoldAttribute) * iDesactivatedInstancesData, CATListOfShort* iDesactivatedInstancesDataInstanceNumber);
  void SetExplicitType(CATLONG32 iExplicitType);
  void GetSecondaryTransformationsTypes(CATListOfShort*& oSecondaryTransformationsTypes);
  void GetReferenceManager(CATDRepReferenceManager *& oReferenceManager);
  void GetDesactivatedInstancesData(CATLISTP(CATManifoldAttribute) *& oDesactivatedInstancesData, CATListOfShort*& oDesactivatedInstancesDataInstanceNumber);
  void GetExplicitType(CATLONG32 & oExplicitType);
  virtual CATManifoldAttribute* CloneWithSameLinks(CATCloneManager& iCloner) const; // Compatibility method. Should not be necessary. To be removed.

protected :

  INLINE const CATMathTransformation & GetSpecTransfo() const;
  void SetSpecTransfo(const CATAngle &iRotationAngle, const CATMathLine &iAxisLine);
  void SetSpecTransfo(const CATMathVector &iTranslationVector);

    /**
    * Checks whether two attributes of the same identifier are equal.
    * <br>Called in the == and =! operators.
    * @return
    * <tt>1</tt> if they are, <tt>0</tt> otherwise.
    */
   // virtual CATLONG32 Compare(const CATCGMAttribute & iToCompare);

private:

  void Init();

  void RecursiveGetLiveBodyElements(CATLISTP(CATDomain)              &ioRefDomains, 
                                    CATLISTP(CATCellManifold)        &ioRefCM,
                                    CATLISTP(CATDeclarativeManifold) &ioRefDM, 
                                    CATLISTP(CATCellManifoldGroup)   &ioRefGroups); 

  CATListOfShort GetDesactivatedInstances(CATPatternActivationStatus iStatus) const;

  /*
  HRESULT GetReferenceCellManifoldImages(short iRefCM, 
                                 short iInstance, 
                                 CATCellManifold* &iorefCellManifold, 
                                 CATLISTP(CATCellManifold) &ioImageCellManifolds, 
                                 CATCellManifoldGroupCGM *iGroup, 
                                 CATLISTP(CATCellManifold) &iListOfReferenceCM);
  */

  CATDomain * GetReferenceDomain();

  // Transfo unitaire
  CATMathTransformation  _UnitaryTransfo; // full spec

  CATMathVector* _TranslationVector; // to remove
  CATMathLine* _RotationAxis;        // to remove
  double _RotationAngle;             // to remove

  // Intances desactivees
  CATListOfShort* _InactivatedInstance;
  CATListOfShort* _InactivationTypes;

  // Secondary Transfo
  CATListOfShort* _InstanceWithSecondaryTransformations;
  CATLISTP(CATMathTransformation)* _SecondaryTransformations;
  // Type de secondary transfo : Relative/Absolue
  CATListOfShort* _SecondaryTransformationsTypes; // A venir : differents types de specialisation en position
                                          
  // ReferenceManager
  CATDRepReferenceManager * _ReferenceManager; // A venir : multi reference (specialisation en forme)

  // Liste des Attribut des network groups des sous pattern pour conserver les donnes lors de leur desactivation.
  CATLISTP(CATManifoldAttribute) * _DesactivatedInstancesData; // A venir : pattern de pattern
  CATListOfShort* _DesactivatedInstancesDataInstanceNumber;  // A venir : pattern de pattern

  // Stokage du type de pattern : protrusion ou depression.
  // Evite de recalculer lorsqu'on connait le type.
  // 1 : Depression
  // 2 : Protrusion
  // 3 : Unknown (on aura tout le temps ça pour les vieux models. A recalculer dans ce cas)
  CATLONG32 _ExplicitType; // A venir : stokage de l'info protrusion/depression


  CATPatternBuildingType         _PatternBuildingType;

  // Donnee temporaire lors de la construction d'un pattern de pattern
  CATBoolean _PatternOfPatternIsBeingCreated; // donne tout le temps a false sauf entre PatterOfPattern Carrier et Creator.

  int _DebugTag; // donne non streamee pour debug.


};

INLINE CATPatternManifoldSpecificationAttribute *CATPatternManifoldSpecificationAttribute::GetAsPatternManifoldSpecificationAttribute() {
  return this; }

INLINE void CATPatternManifoldSpecificationAttribute::SetPatternBuildingType(CATPatternBuildingType iType) {
 _PatternBuildingType = iType; }

INLINE CATPatternBuildingType CATPatternManifoldSpecificationAttribute::GetPatternBuildingType() const {
  return _PatternBuildingType; }

INLINE const CATMathTransformation & CATPatternManifoldSpecificationAttribute::GetSpecTransfo() const {
  return _UnitaryTransfo; }

#endif

