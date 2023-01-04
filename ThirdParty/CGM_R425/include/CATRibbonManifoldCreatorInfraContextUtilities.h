#ifndef CATRibbonManifoldCreatorInfraContextUtilities_H
#define CATRibbonManifoldCreatorInfraContextUtilities_H

#include "CATCGMNewArray.h"

#include "ListPOfCATCell.h"
#include "ListPOfCATCellManifold.h"
#include "IUnknown.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "CATCGMJournalList.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATBody.h"


class CATRibbonManifoldCreatorBase;
class CATLISTP(CATDeclarativeManifold);
class CATDeclarativeManifold;
class CATLiveBody;
class CATContextualManifold;
class CATRibbonsReorderTracker;
class CATPersistentBody;
class PersistentCell;


class ExportedByPersistentCell CATRibbonManifoldCreatorInfraContextUtilities
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATRibbonManifoldCreatorInfraContextUtilities(CATRibbonManifoldCreatorBase               *iAgent, 
                                                CATCGMJournalList                          &iLocalCellManifoldJournal,
                                                ListPOfCATGMLiveContextualFeatureFollowers &iFeatureBoneFollowers);
  
  virtual ~CATRibbonManifoldCreatorInfraContextUtilities();

  //methodes - ST5 begin modifs: the CreatedCellManifolds becomes an output
  HRESULT CreateImageManifolds(ListPOfCATDeclarativeManifold &oCreatedDM);

  //ST5 Wk42/2010
  CATRibbonsReorderTracker * GetRedoFeatureRibbonsReorderTracker();
  void SetRedoFeatureRibbonsReorderTracker(CATRibbonsReorderTracker * ipRibbonsTracker);
  //ST5 Wk47-2011
  void GetFilletCellsToSimplify(ListPOfCATCell & oFilletCellsToSimplify);
  void SetFilletCellsToSimplify(ListPOfCATCell & iFilletCellsToSimplify);
  CATPersistentBody * GetPersistentBodyForTypeReport();
  void SetPersistentBodyForTypeReport(CATPersistentBody * ipPersistentBodyForTypeReport);

private:

  void ReportCellManifoldImages(CATLISTP(CATDeclarativeManifold) &iCreatedDM);
  void ReportBorderCellManifoldImages(CATLISTP(CATDeclarativeManifold) &iCreatedDM);

  void ReportModification(CATLISTP(CATCellManifold) &iParentCellManifolds, 
                                                              CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo = 0);

  void GetParentManifolds(CATDeclarativeManifold &iParentFeature, 
                                                              CATDeclarativeManifold &iCreatedFeature,
                                                              CATLiveBody &iParentLiveBody,
                                                              CATLiveBody &iLiveBody,
                                                              ListPOfListPOfCATCellManifolds &oListOfListOfParentManifolds);

  void GetMatchingParentFeatures(CATDeclarativeManifold           &iCreatedFeature, 
                                 CATLISTP(CATDeclarativeManifold) &iParentFeatureCandidates,
                                 CATLISTP(CATDeclarativeManifold) &oMatchingFeatures);

  CATBoolean AreFeaturesMatching(CATDeclarativeManifold &iCreatedFeature, 
                                 CATDeclarativeManifold &iFeatureCandidate);


  void GetOriginalContextualManifold(CATGMLiveContextualFeatureFollower &iBoneFollower,
                                     ListPOfCATDeclarativeManifold &ioParentFeatureCandidates,
                                     ListPOfCATBody &oParentBodies);

  HRESULT CleanEmptyDeclarativeManifolds(ListPOfCATDeclarativeManifold &ioUpdateCreatedDM);

  void FindParentFeaturesWithFollowers(CATDeclarativeManifold * iCreatedFeature, ListPOfCATDeclarativeManifold & ioMatchingParentFeature, CATLiveBody * iLiveBody);

 
private:
  CATRibbonManifoldCreatorBase *_Agent;
  CATCGMJournalList &_LocalCellManifoldJournal;
  ListPOfCATGMLiveContextualFeatureFollowers _FeatureBoneFollowers;

  //ST5 Wk42/2010: Provides order in fillet creation after Redo
  CATRibbonsReorderTracker * _pRibbonsTracker;
  //ST5 Wk47-2011: Fillet cells to be simplified
  ListPOfCATCell _FilletCellsToSimplify;
  CATPersistentBody * _pPersistentBodyForTypeReport;
};

#endif 

