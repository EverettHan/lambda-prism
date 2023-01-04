#ifndef CATPatternReferenceManifoldAttribute_h
#define CATPatternReferenceManifoldAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATCGMNewArray.h"
#include "CATInstancesReferenceManifoldAttribute.h"
#include "CATManifoldAttribute.h"
#include "CATMathInline.h"
#include "CATICGMObject.h"
#include "CATPersistentCell.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATCellManifoldGroupCarrier.h"

class CATCellManifold;
class CATCloneManager;
class CATTransfoManager;
class CATCellManifoldGroupCarrier;

class ExportedByPersistentCell CATPatternReferenceManifoldAttribute : public CATInstancesReferenceManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATPatternReferenceManifoldAttribute,CATManifoldAttribute);

  CATPatternReferenceManifoldAttribute(); // Default constructor is mandatory
  CATPatternReferenceManifoldAttribute(CATCellManifold* iReferenceCellManifold);  
  virtual ~CATPatternReferenceManifoldAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;
  INLINE CATCellManifold * GetReferenceCellManifold();

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
    const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual void GetCellManifoldSpecificNavigators(
    CATLiveBody                          * iInputLiveBody, 
    CATCellManifoldGroupCarrier          *iCellManifoldGroupCarrier,
    ListPOfCATCellManifoldGroupNavigator & oGroupNavigatorList);

  virtual void OrganizeImageByGroup(
    ListPOfCATCellManifoldGroup    & iCellManifoldGroupsToCarry,
    ListPOfCATCellManifold         & iLeavesImages,
    CATListOfShort                 * iLeavesImagesType,
    CATCellManifoldGroupCarrier    * iCellManifoldGroupCarrier,
    CATCellManifoldGroupLayer      * iGroupLayer,
    ListPOfListPOfCATCellManifolds & oSortedLeavesImages,
    ListPOfCATListOfShort          & oSortedLeavesImagesType);

  virtual HRESULT ComputeNotUpToDateCMs(
    CATCellManifoldGroup        * iParentCellManifoldGroup,
    CATCellManifoldGroup        * iImageCellManifoldGroup,
    CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier);

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
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  // On donne en entree le journal du move entre l'ancienne reference et la nouvelle reference.
  void UpdateReference(CATCGMJournalList * iRefTransfoJournal);  
  
  INLINE virtual CATPatternReferenceManifoldAttribute *GetAsPatternReferenceManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  void DiGraphDump(CATCGMOutput& Output);

protected:
  void SetReferenceCellManifold(CATCellManifold* iReferenceCellManifold);

private:
  virtual CATManifoldAttribute* CloneWithSameLinks(CATCloneManager& iCloner) const; // Compatibility method. Should not be necessary. To be removed.
  void Init();
  CATCellManifold * _ReferenceCellManifold;
  int _DebugTag; // Only for debug tasks.

};

INLINE CATPatternReferenceManifoldAttribute *CATPatternReferenceManifoldAttribute::GetAsPatternReferenceManifoldAttribute()
{
  return this;
}

//--------------------------------------------------------------------
INLINE CATCellManifold* CATPatternReferenceManifoldAttribute::GetReferenceCellManifold()
//--------------------------------------------------------------------
{
  return _ReferenceCellManifold;
}
#endif

