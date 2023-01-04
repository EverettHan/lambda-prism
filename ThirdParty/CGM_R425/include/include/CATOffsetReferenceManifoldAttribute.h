#ifndef CATOffsetReferenceManifoldAttribute_h
#define CATOffsetReferenceManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2010

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfDouble.h" 
#include "CATMathInline.h"
#include "CATListOfShort.h"
#include "CATInstancesReferenceManifoldAttribute.h"
#include "CATICGMObject.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;
class CATCellManifoldGroupCarrier;

class ExportedByPersistentCell CATOffsetReferenceManifoldAttribute : public CATInstancesReferenceManifoldAttribute
{
public:

  CATCGMDeclareAttribute (CATOffsetReferenceManifoldAttribute,CATManifoldAttribute);

  CATOffsetReferenceManifoldAttribute(); // Default constructr is mandatory
  CATOffsetReferenceManifoldAttribute(const ListPOfCATCellManifold &iReferenceCellManifoldList, CATBoolean iNullOffset, double iOffsetValue);
  CATOffsetReferenceManifoldAttribute(CATCellManifold * iReferenceCellManifoldList, CATBoolean iNullOffset, double iOffsetValue);
  CATOffsetReferenceManifoldAttribute(CATCellManifold * iReferenceCellManifoldList);
  virtual ~CATOffsetReferenceManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          *iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
                           CATCGMLinkType           iLinkType,
                           CATRCOLL(int)*           oSharedStatus,
                           CATLISTV(CATString)*     oLinksString);

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);

  HRESULT GetReferenceCellManifolds(ListPOfCATCellManifold &oReferenceCellManifoldList);
  CATCellManifold * GetReferenceCellManifold();
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  INLINE virtual CATOffsetReferenceManifoldAttribute *GetAsOffsetReferenceManifoldAttribute();

  // Set
  void SetReserveList(CATListOfShort & iReserveList);
  INLINE void SetOffsetValue(double iOffsetValue);
  INLINE void SetIsActiveOffsetValue(CATBoolean iIsActiveOffsetValue);

  //Get
  void   GetReserveList(CATListOfShort & oReserveList);
  INLINE double GetOffsetValue() const;
  INLINE CATBoolean IsNullOffset();
  INLINE CATBoolean IsActiveOffsetValue();

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

private:
  void SetReferenceCellManifoldList(const ListPOfCATCellManifold &iReferenceCellManifoldList);
  void SetReferenceCellManifold(CATCellManifold *iReferenceCellManifold);
  

  ListPOfCATCellManifold   _ReferenceCellManifoldList;
  CATBoolean               _NullOffset; 
  // TRUE si _OffsetValue == 0. 
  // Permet d'eviter de comparer des double
  double                   _OffsetValue;

  //Surcharge locale de la valeur d'offset globale - VB7 | W40 | 2014
  CATBoolean               _IsActiveOffsetValue;

  // Liste de short supplementaire en cas de besoin.
  CATListOfShort         * _ReserveList;

};

INLINE CATOffsetReferenceManifoldAttribute *CATOffsetReferenceManifoldAttribute::GetAsOffsetReferenceManifoldAttribute()
{
  return this;
}

INLINE double CATOffsetReferenceManifoldAttribute::GetOffsetValue() const {
  return _OffsetValue; }

INLINE void CATOffsetReferenceManifoldAttribute::SetOffsetValue(double iOffsetValue) {
  _OffsetValue = iOffsetValue; }

INLINE CATBoolean CATOffsetReferenceManifoldAttribute::IsNullOffset() {
  return _NullOffset; }


INLINE void CATOffsetReferenceManifoldAttribute::SetIsActiveOffsetValue(CATBoolean iIsActiveOffsetValue) {
  _IsActiveOffsetValue = iIsActiveOffsetValue; }

INLINE CATBoolean CATOffsetReferenceManifoldAttribute::IsActiveOffsetValue() {
  return _IsActiveOffsetValue; }


#endif

