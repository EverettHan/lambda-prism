#ifndef CATPatternManifoldAttribute_h
#define CATPatternManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMNewArray.h"
#include "CATInstancesManifoldAttribute.h"
#include "CATManifoldAttribute.h"
#include "CATMathInline.h"

class CATCloneManager;
class CATTransfoManager;
class CATMathTransformation;

#include "CATPersistentCell.h"
class ExportedByPersistentCell CATPatternManifoldAttribute : public CATInstancesManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATPatternManifoldAttribute,CATManifoldAttribute);

  CATPatternManifoldAttribute(); // Default constructor is mandatory
  CATPatternManifoldAttribute(int iPatternNumber, CATMathTransformation* iOptionalTransfo = NULL);
  virtual ~CATPatternManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE short GetPatternNumber();
  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void ComputeSpecificTreatment(
    const CATLISTP(CATCellManifoldGroup) & iParentGroups,
          CATLISTP(CATCellManifoldGroup) & ioImageSonList, 
    CATCellManifoldGroupCarrier          * iCellManifoldGroupCarrier) const;

  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          *iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual void OrganizeSonImageByGroup(
    ListPOfCATCellManifoldGroup         &iCellManifoldGroupsToCarry, 
    ListPOfCATCellManifoldGroup         &iParentSonsImages,
    CATCellManifoldGroupCarrier         *iCellManifoldGroupCarrier,
    ListPOfListPOfCATCellManifoldGroups &oSortedSonsImages);

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  INLINE virtual CATPatternManifoldAttribute *GetAsPatternManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

protected:
  void SetLocalTransfo(CATMathTransformation& LocalTransfo);

private:
  short _PatternNumber;
  CATMathTransformation* _LocalTransfo;

};

INLINE CATPatternManifoldAttribute *CATPatternManifoldAttribute::GetAsPatternManifoldAttribute()
{
  return this;
}

INLINE short CATPatternManifoldAttribute::GetPatternNumber()
{
  return _PatternNumber;
}
#endif

