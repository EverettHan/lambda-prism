#ifndef CATOffsetManifoldAttribute_h
#define CATOffsetManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2010

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATMathInline.h"
#include "CATListOfShort.h"
#include "CATInstancesManifoldAttribute.h"
#include "CATOffsetLateralFacesManifoldAttribute.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATOffsetManifoldAttribute : public CATInstancesManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATOffsetManifoldAttribute,CATManifoldAttribute);

  enum LateralFacesType
  {
    Unknown = 0,
    Perpendicular = 10,
    G1 = 20
  };

  CATOffsetManifoldAttribute(); // Default constructr is mandatory
  CATOffsetManifoldAttribute(int iSkinNumber);
  virtual ~CATOffsetManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void ComputeSpecificTreatment(
    const CATLISTP(CATCellManifoldGroup) & iParentGroups,
          CATLISTP(CATCellManifoldGroup) & ioImageSonList, 
    CATCellManifoldGroupCarrier          * iCellManifoldGroupCarrier) const;

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

  INLINE void SetOffsetValue(double iOffsetValue);

  int GetSkinNumber();
  INLINE double GetOffsetValue() const;
  INLINE CATBoolean IsNullOffset();

  // Pour BodiesMapping
  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

  INLINE virtual CATOffsetManifoldAttribute *GetAsOffsetManifoldAttribute();

  // Methodes pour tester Stream/Unstream
  void SetReserveList(CATListOfShort & iList);
  void GetReserveList(CATListOfShort & oList);

private : 

  //start from 0 <<<<<<<<<<<<-----------
  int               _SkinNumber;

  //Valeur Globale d'offset VB7 | W40 | 2014
  // TRUE si _OffsetValue == 0. 
  // Permet d'eviter de comparer des double
  CATBoolean        _NullOffset; 
  double            _OffsetValue;

  // Liste de short supplementaire en cas de besoin.
  CATListOfShort   * _ReserveList;


};

INLINE CATOffsetManifoldAttribute *CATOffsetManifoldAttribute::GetAsOffsetManifoldAttribute()
{
  return this;
}

INLINE void CATOffsetManifoldAttribute::SetOffsetValue(double iOffsetValue) {
  _OffsetValue = iOffsetValue; }

INLINE double CATOffsetManifoldAttribute::GetOffsetValue() const {
  return _OffsetValue; }

INLINE CATBoolean CATOffsetManifoldAttribute::IsNullOffset() {
  return _NullOffset; }

#endif

