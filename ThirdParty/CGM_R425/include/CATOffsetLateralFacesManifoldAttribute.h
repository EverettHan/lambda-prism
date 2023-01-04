#ifndef CATOffsetLateralFacesManifoldAttribute_h
#define CATOffsetLateralFacesManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013
// VB7

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATListOfShort.h"

// @nocgmitf (this class doesn't need a CATIPGM interface)
class ExportedByPersistentCell CATOffsetLateralFacesManifoldAttribute : public CATManifoldAttribute
{
public:

  enum LateralFacesType
  {
    Unknown = 0,
    Perpendicular = 10,
    G1 = 20
  };

  CATCGMDeclareAttribute (CATOffsetLateralFacesManifoldAttribute,CATManifoldAttribute);

  CATOffsetLateralFacesManifoldAttribute(); // Default constructor is mandatory
  CATOffsetLateralFacesManifoldAttribute(CATOffsetLateralFacesManifoldAttribute::LateralFacesType iLateralFacesType);
  virtual ~CATOffsetLateralFacesManifoldAttribute();
  void Init();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE virtual CATOffsetLateralFacesManifoldAttribute *GetAsOffsetLateralFacesManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  INLINE CATOffsetLateralFacesManifoldAttribute::LateralFacesType GetLateralFacesType() const;
  

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;
  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

protected : 
  //For unstream only
  INLINE void SetLateralFacesType(CATOffsetLateralFacesManifoldAttribute::LateralFacesType iLateralFacesType);

private:

  LateralFacesType   _LateralFacesType;

};

INLINE CATOffsetLateralFacesManifoldAttribute * CATOffsetLateralFacesManifoldAttribute::GetAsOffsetLateralFacesManifoldAttribute() {
 return this; }

INLINE CATOffsetLateralFacesManifoldAttribute::LateralFacesType CATOffsetLateralFacesManifoldAttribute::GetLateralFacesType() const {
  return _LateralFacesType; }

INLINE void CATOffsetLateralFacesManifoldAttribute::SetLateralFacesType(CATOffsetLateralFacesManifoldAttribute::LateralFacesType iLateralFacesType)  {
  _LateralFacesType=iLateralFacesType; }

#endif

