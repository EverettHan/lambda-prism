#ifndef CATGMLivePatternFollower_H
#define CATGMLivePatternFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "CATGMLiveHierarchicalGroupFollower.h"
#include "CATDataType.h"
#include "CATMathTransformation.h"
#include "CATCGMJournalList.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATCollec.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATPersistentCells.h"
#include "ListPOfListPOfCATPersistentCells.h"


class CATCellManifoldGroup;
class CATLISTP(CATCellManifoldGroup);
class CATPersistentBody;
class CATBody;
class CATPersistentCellInfra;
class CATLiveBody;
class CATCGMHashTableWithAssoc;
class CATCellManifoldHashTableWithAttributeAssoc;
class CATCellManifoldPatternNavigator;
class CATPersistentCell;


class ExportedByPersistentCell CATGMLivePatternFollower : public CATGMLiveHierarchicalGroupFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLivePatternFollower(CATCellManifoldGroup           &iNetworkGroup, 
    CATCellManifoldGroup           &iPatternGroup,
    short                          &iInstanceNumber,
    CATPersistentBody              &iPatternedBody,
    CATPersistentCellInfra         &iInfra,
    CATLONG32                      &iExplicitType);
  
  //Copy constructor
  CATGMLivePatternFollower(CATGMLivePatternFollower & iFollower);
  
  //FOR UNSTREAL ONLY
  CATGMLivePatternFollower(CATPersistentCellInfra         &iInfra);

  //CATGMLivePatternFollower(const CATAutoBaseThreadContext      &iThreadContext,
  //                         CATCellManifoldGroup           &iNetworkGroup, 
  //                         short                          &iInstanceNumber);

  // Destructor
  ~CATGMLivePatternFollower();

  // Cast 
  INLINE virtual CATGMLivePatternFollower *GetAsPatternFollower();
  virtual void GetCellManifoldsInInputBody(ListPOfCATCellManifold &iInputCellManifolds) const;

  //static CATBoolean AreEqual(const CATGMLivePatternFollower &iFollower1, const CATGMLivePatternFollower &iFollower2);

  INLINE short GetInstanceNumber() const;


  INLINE CATPersistentBody *GetPersistentOtherReferenceBody() const; 
  CATBody *GetOtherReferenceBody() const; 
  INLINE void SetPersistentOtherReferenceBody(CATPersistentBody *iPersistentOtherReferenceBody);

  CATCellManifoldPatternNavigator * GetPatternNavigator() const;
  void SetPatternNavigator(CATCellManifoldPatternNavigator * iPatternNavigator);


  //------------------------------------------------------
  // METHODES A SUPPRIMER
  //------------------------------------------------------
  INLINE CATLONG32 GetExplicitType() const; // A supprimer
  INLINE void SetExplicitType(CATLONG32 iExplicitType);
  //------------------------------------------------------
  // FIN METHODES A SUPPRIMER
  //------------------------------------------------------

  INLINE void SetIsOutOfSupport(CATBoolean iIsOutOfSupport);
  INLINE void SetIntersectionSolving(CATBoolean iIntersectionSolving);
  INLINE CATBoolean GetIsOutOfSupport() const;
  INLINE CATBoolean GetIntersectionSolving() const;

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
  virtual void StreamCATCellManifoldNavigator(CATCellManifoldGroupNavigator *_Navigator, CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  virtual CATCellManifoldGroupNavigator *UnStreamCATCellManifoldNavigator(CATCGMStream& ioStr, CATGeoFactory * iFactory);
  INLINE CATBoolean GetNeedToBeRedone() const;
  INLINE void SetNeedToBeRedone(CATBoolean iNeedToBeRedone);

  void CleanSubdividedDatas();
  void StoreRepBeforeDeletePCellView(CATPersistentCell *iPCell,ListPOfCATCell &iRep);
  void StoreRepBeforeDeletePCellView(ListPOfCATPersistentCells &iRefSubdividedPCells,ListPOfListPOfCATPersistentCells &iSubdividedPCellsNewPCells);
  void GetSubdividedPCellsDatas(ListPOfCATPersistentCells &oRefSubdividedPCells,ListPOfListPOfCATCell &oSubdividedPCellsImages);
  void GetAssociatedRepPCells(ListPOfCATPersistentCells &iRefPCells,ListPOfCATPersistentCells &oAssociatedPCells);

protected:
  virtual CATCellManifoldGroupLayer *GetLayer() const;
  virtual CATManifoldAttribute *CreateManifoldAttribute(CATCellManifold *iCellManifold) const;

private:
  CATPersistentBody        *_PersistentOtherReferenceBody;
  short                     _InstanceNumberToFollow;
  CATLONG32                 _ExplicitType; // a supprimer
  CATBoolean                _IntersectionSolving;

  //VB7 pattern without remove/redo
  CATBoolean _NeedToBeRedone;

  // Pour pouvoir distinguer la desactivation par effet gomme 
  // de la desactivation par sortie du support 
  // a la reconstruction
  CATBoolean _IsOutOfSupport;

  ListPOfCATPersistentCells _RefSubdividedPCells;
  ListPOfListPOfCATCell     _SubdividedPCellsImages;
  ListPOfListPOfCATPersistentCells _SubdividedPCellsPersistentImages;

};

INLINE CATGMLivePatternFollower* CATGMLivePatternFollower::GetAsPatternFollower()
{
  return this;
}

INLINE CATPersistentBody *CATGMLivePatternFollower::GetPersistentOtherReferenceBody() const
{
  return _PersistentOtherReferenceBody;
}

INLINE short CATGMLivePatternFollower::GetInstanceNumber() const
{
  return _InstanceNumberToFollow;
}

INLINE CATLONG32 CATGMLivePatternFollower::GetExplicitType() const
{
  return _ExplicitType;
}

INLINE CATBoolean CATGMLivePatternFollower::GetNeedToBeRedone() const 
{
  return _NeedToBeRedone;
}

INLINE CATBoolean CATGMLivePatternFollower::GetIsOutOfSupport() const
{
  return _IsOutOfSupport;
}

INLINE CATBoolean CATGMLivePatternFollower::GetIntersectionSolving() const {
  return _IntersectionSolving; }

INLINE void CATGMLivePatternFollower::SetPersistentOtherReferenceBody(CATPersistentBody *iPersistentOtherReferenceBody)
{
   if(iPersistentOtherReferenceBody)
    _PersistentOtherReferenceBody = iPersistentOtherReferenceBody;
}

INLINE void CATGMLivePatternFollower::SetExplicitType(CATLONG32 iExplicitType)
{
  _ExplicitType = iExplicitType;
}

INLINE void CATGMLivePatternFollower::SetNeedToBeRedone(CATBoolean iNeedToBeRedone)
{
  _NeedToBeRedone = iNeedToBeRedone;
}

INLINE void CATGMLivePatternFollower::SetIsOutOfSupport(CATBoolean iIsOutOfSupport)
{
  _IsOutOfSupport = iIsOutOfSupport;
}

INLINE void CATGMLivePatternFollower::SetIntersectionSolving(CATBoolean iIntersectionSolving)
{
  _IntersectionSolving = iIntersectionSolving;
}

#endif

