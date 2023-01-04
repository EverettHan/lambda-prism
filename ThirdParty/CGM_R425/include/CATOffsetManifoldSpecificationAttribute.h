#ifndef CATOffsetManifoldSpecificationAttribute_h
#define CATOffsetManifoldSpecificationAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2010

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h" 
#include "CATMathInline.h"
#include "CATListOfShort.h"
#include "CATInstancesManifoldSpecificationAttribute.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;
class CATDRepReferenceManager;

class ExportedByPersistentCell CATOffsetManifoldSpecificationAttribute : public CATInstancesManifoldSpecificationAttribute
{
public:
  CATCGMDeclareAttribute (CATOffsetManifoldSpecificationAttribute,CATManifoldAttribute);

  enum ContextType
  {
    Unknown = 0,
    FullOffset = 1,
    LocalOffset = 2
  };

  CATOffsetManifoldSpecificationAttribute(); // Default constructr is mandatory
  CATOffsetManifoldSpecificationAttribute(int iNumberOfSkins);
  CATOffsetManifoldSpecificationAttribute(int                              iNumberOfSkins,
                                          CATListOfShort*                  iInactivatedInstance,
                                          CATListOfShort*                  iInactivatedTypes,
                                          CATLISTP(CATICGMObject)        & iLinkedObjects);

  virtual ~CATOffsetManifoldSpecificationAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &ImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void OrganizeSonImageByGroup(
    ListPOfCATCellManifoldGroup         &iCellManifoldGroupsToCarry, 
    ListPOfCATCellManifoldGroup         &iParentSonsImages,
    CATCellManifoldGroupCarrier         *iCellManifoldGroupCarrier,
    ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);

  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          *iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 
  int GetNumberOfSkins() const;
  HRESULT GetReferenceCellManifolds(CATLISTP(CATCellManifold) &oReferenceCellManifolds);
  CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;  

  void SetReferenceOffset(CATLiveBody* iRefLiveBody);
  void RemoveReferenceOffset();
  CATLiveBody* CreateReferenceLiveBody();

  INLINE virtual CATOffsetManifoldSpecificationAttribute *GetAsOffsetManifoldSpecificationAttribute();

  INLINE void SetContextType(CATOffsetManifoldSpecificationAttribute::ContextType iContextType);

  INLINE CATOffsetManifoldSpecificationAttribute::ContextType GetContextType() const;

  // Methodes pour tester Stream/Unstream
  void SetDesactivatedSkinsData(CATLISTP(CATManifoldAttribute) & iDesactivatedSkinsData);
  void GetDesactivatedSkinsData(CATLISTP(CATManifoldAttribute) & oDesactivatedSkinsData);
  void SetRefCMData(CATLISTP(CATManifoldAttribute) & iRefCMData);
  void GetRefCMData(CATLISTP(CATManifoldAttribute) & oRefCMData);
  void SetReferenceManager(CATDRepReferenceManager * iReferenceManager);
  CATDRepReferenceManager * GetReferenceManager();

  // Pour BodiesMapping
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

private:
  int                              _NumberOfSkins;

  CATListOfShort                 * _InactivatedSkins;
  CATListOfShort                 * _InactivationType;

  // list des attributs des skins desactives pour conserver leur caracteristiques
  CATLISTP(CATManifoldAttribute) * _DesactivatedSkinsData;
  // list des attributs des CM ref sans image pour conserver leur caracteristiques
  CATLISTP(CATManifoldAttribute) * _RefCMData;

  // ReferenceManager pour pouvoir gerer plusieurs skins de reference
  CATDRepReferenceManager        * _ReferenceManager;

  ContextType                      _ContextType;
};

INLINE CATOffsetManifoldSpecificationAttribute *CATOffsetManifoldSpecificationAttribute::GetAsOffsetManifoldSpecificationAttribute()
{
  return this;
}

INLINE void CATOffsetManifoldSpecificationAttribute::SetContextType(CATOffsetManifoldSpecificationAttribute::ContextType iContextType) {
  _ContextType = iContextType; }

INLINE CATOffsetManifoldSpecificationAttribute::ContextType CATOffsetManifoldSpecificationAttribute::GetContextType() const {
  return _ContextType; }
#endif

