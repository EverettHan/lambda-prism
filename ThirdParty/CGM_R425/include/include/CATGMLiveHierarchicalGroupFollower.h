#ifndef CATGMLiveHierarchicalGroupFollower_H
#define CATGMLiveHierarchicalGroupFollower_H


#include "CATGMLiveGroupFollower.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfListPOfCATCell.h"
#include "CATListOfCATCells.h"
#include "CATlsoIntegrity.h"
#include "CATSysDeletePtrList.h"
#include "CATCGMJournalList.h"
#include "CATWeekVersioning.h"

class CATCellManifoldGroup;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATCGMJournalList;
class CATCellManifoldGroupNavigator;
class CATCellManifoldGroupLayer;
class CATListPtrCATCellManifoldGroup;
class CATManifoldAttribute;
class CATCellManifold;
class CATLiveBody;
class CATCellManifoldHashTableWithAttributeAssoc;

class ExportedByPersistentCell CATGMLiveHierarchicalGroupFollower : public CATGMLiveGroupFollower 
{
protected:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveHierarchicalGroupFollower(CATCellManifoldGroup           &iNetworkGroup, 
    CATCellManifoldGroup           &iMainGroup,
    CATPersistentBody              &iInitialBodyWithGroup,
    CATPersistentCellInfra         &iInfra);

  //Copy constructor
  CATGMLiveHierarchicalGroupFollower(CATGMLiveHierarchicalGroupFollower & iFollower);

public:
  //FOR UNSTREAM ONLY
CATGMLiveHierarchicalGroupFollower(CATPersistentCellInfra         &iInfra);
  ~CATGMLiveHierarchicalGroupFollower();

  INLINE CATGMLiveHierarchicalGroupFollower *GetAsHierarchicalGroupFollower();
  INLINE CATCellManifoldGroup * GetMainCMGroup() const;

  INLINE CATPersistentBody *GetPersistentNewReferenceBody() const; 
  INLINE CATPersistentBody *GetCreatedPersistentBody() const;
  CATBody *GetNewReferenceBody() const; 
  INLINE void SetPersistentNewReferenceBody(CATPersistentBody *iPersistentNewReferenceBody);
  INLINE void CleanNewReferenceBody();

  INLINE CATCGMJournalList * GetOldRefNewRefJournal() const;
  void SetOldRefNewRefJournal(CATCGMJournalList * iOldRefNewRefJournal);


  // pour la reconstruction du graph
  void SetCMReferenceLinkedWithCreatedCells(CATCellManifold *iCMReference,ListPOfCATCell &iListOfCreatedCells);
  INLINE void SetCreatedPersistentBody(CATPersistentBody *iCreatedPersistentBody);
  INLINE void GetCMReference(ListPOfCATCellManifold &oListOfCMReference) const;
  INLINE void GetListOfCreatedCells(ListPOfListPOfCATCell &oListOfCreatedCells) const;
  
  void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const;
  
  void RemoveCellsToHappenToGroup();

   void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
   void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
   void CreateNewCMRefGroup(CATCellManifoldGroup* iOffsetGroup, CATLiveBody* iResultBody, CATLISTP(CATCellManifoldGroup) &oCMRefGroups);
   void CreateNewCMRefGroupWithCreatedAttr(CATCellManifoldGroup* iMainGroup, CATLiveBody* iResultBody, CATLISTP(CATCellManifoldGroup) &oCMRefGroups, CATCellManifoldHashTableWithAttributeAssoc *& ioRefCMWithAssocAttr);
   
   virtual void SetSpecificValue(CATManifoldAttribute * iAttr, int iIndex);

protected:
  INLINE void SetMainCMGroup(CATCellManifoldGroup *iMainGroup);//FOR UNSTREAM ONLY
  virtual CATManifoldAttribute *CreateManifoldAttribute(CATCellManifold *iCellManifold)const =0 ;

private:
  CATCellManifoldGroup     *_MainGroupToFollow;
  CATPersistentBody        *_PersistentNewReferenceBody;
  CATPersistentBody        *_CreatedPersistentBody;
  CATCGMJournalList        *_OldRefNewRefJournal;

  //pour la reconstruction du graph
  ListPOfCATCellManifold     _ListOfCMReference;
  ListPOfListPOfCATCell      _CreatedCellsPointingOnCMReference; 

};

INLINE CATCellManifoldGroup* CATGMLiveHierarchicalGroupFollower::GetMainCMGroup() const
{
  return _MainGroupToFollow;
}

INLINE CATPersistentBody * CATGMLiveHierarchicalGroupFollower::GetPersistentNewReferenceBody() const
{
  return _PersistentNewReferenceBody;
}

INLINE CATPersistentBody * CATGMLiveHierarchicalGroupFollower::GetCreatedPersistentBody() const
{
  return _CreatedPersistentBody;
}

INLINE CATCGMJournalList * CATGMLiveHierarchicalGroupFollower::GetOldRefNewRefJournal() const
{
  return _OldRefNewRefJournal;
}

INLINE void CATGMLiveHierarchicalGroupFollower::GetCMReference(ListPOfCATCellManifold &oListOfCMReference) const
{
  oListOfCMReference = _ListOfCMReference;
}

INLINE void CATGMLiveHierarchicalGroupFollower::GetListOfCreatedCells(ListPOfListPOfCATCell &oListOfCreatedCells)  const 
{
  oListOfCreatedCells = _CreatedCellsPointingOnCMReference;
}

INLINE void CATGMLiveHierarchicalGroupFollower::SetMainCMGroup(CATCellManifoldGroup *iMainGroup) //FOR OLD UNSTREAM ONLY
{    
  if(!_MainGroupToFollow)
    _MainGroupToFollow=iMainGroup;
}

INLINE void CATGMLiveHierarchicalGroupFollower::SetPersistentNewReferenceBody(CATPersistentBody *iPersistentNewReferenceBody)
{
  if(iPersistentNewReferenceBody)
    _PersistentNewReferenceBody = iPersistentNewReferenceBody;
}

INLINE void CATGMLiveHierarchicalGroupFollower::CleanNewReferenceBody() 
{
  _PersistentNewReferenceBody = NULL;
  CATSysDeletePtr(_OldRefNewRefJournal);
}

INLINE void CATGMLiveHierarchicalGroupFollower::SetCreatedPersistentBody(CATPersistentBody *iCreatedPersistentBody)
{
  _CreatedPersistentBody=iCreatedPersistentBody;
}
INLINE CATGMLiveHierarchicalGroupFollower *CATGMLiveHierarchicalGroupFollower::GetAsHierarchicalGroupFollower()
{
  return this;
}
#endif

