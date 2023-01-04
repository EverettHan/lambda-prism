#ifndef CATChamferManifoldCreatorInfraContext_H
#define CATChamferManifoldCreatorInfraContext_H


#include "CATChamferManifoldCreatorBase.h"
#include "CATCGMNewArray.h"

#include "PersistentCell.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "CATCGMJournalList.h"
#include "CATMathInline.h"

class CATRibbonManifoldCreatorInfraContextUtilities;
class CATRibbonsReorderTracker;

class ExportedByPersistentCell CATChamferManifoldCreatorInfraContext : public CATChamferManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATChamferManifoldCreatorInfraContext, CATChamferManifoldCreatorBase);
	
	// Constructor
  CATChamferManifoldCreatorInfraContext();
	
  // Destructor
	virtual ~CATChamferManifoldCreatorInfraContext();

  void SetChamferBoneFollowers(ListPOfCATGMLiveContextualFeatureFollowers &iChamferBoneFollowers,CATListPV &iMatchedRibbons);

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);

  void SetReorderTracker(CATRibbonsReorderTracker* iTracker); 

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();

  CATRibbonManifoldCreatorInfraContextUtilities *GetUtilities();

  //EYL 12/2011 Methode temporaire en attendant la refonte du RemoveRedo pour arranger les journaux de creations de chamfer
  CATDeclarativeManifold *GetOriginalChamfer(ListPOfCATCellManifold &iBorderCellParentManifolds, ListPOfCATCellManifold &iChildren, CATPersistentBody *iPBody);

  INLINE virtual CATChamferManifoldCreatorInfraContext *GetAsChamferManifoldCreatorInfraContext();

protected:
  virtual CATBoolean GetChamferParams(CATLISTP(CATCellManifold) &iBoneChamferRep, short &oChamferType, double &oLeftValue, double &oRightValue);
  virtual void FindMatchingFollowerOnBoneUsingRibbonTracker(ListPOfCATCellManifold iBoneReps,ListPOfCATGMLiveBoneFollowers &ioMatchingFollowers);

private: 
  virtual HRESULT CreateBoneChamfer(BoneChamferCMData& iData, CATLISTP(CATDeclarativeManifold) &ioCreatedChamferManifolds);

  CATCGMJournalList _LocalCellManifoldJournal;

  
  CATRibbonsReorderTracker* _RibbonsReorderTracker;

  //Twin lists
  ListPOfCATGMLiveContextualFeatureFollowers _ChamferBoneFollowers;
  CATListPV _FilletRibbons;//CATListPV because we haven't access to CATDynFiletRibbon

  CATRibbonManifoldCreatorInfraContextUtilities *_InfraContextUtilities;

};

INLINE CATDeclarativeManifoldAgent* CATChamferManifoldCreatorInfraContext::Clone()
{
  return new CATChamferManifoldCreatorInfraContext();
}

INLINE CATChamferManifoldCreatorInfraContext *CATChamferManifoldCreatorInfraContext::GetAsChamferManifoldCreatorInfraContext()
{
  return this;
}

#endif
