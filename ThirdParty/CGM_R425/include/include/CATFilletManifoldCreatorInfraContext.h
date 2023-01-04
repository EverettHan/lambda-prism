#ifndef CATFilletManifoldCreatorInfraContext_H
#define CATFilletManifoldCreatorInfraContext_H

#include "PersistentCell.h"
#include "CATFilletManifoldCreatorBase.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATBoneFillet.h"
#include "ListPOfListPOfCATFace.h"
#include "CATCGMJournalList.h"
#include "CATMathInline.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATExtTopOperator.h"
#include "CATSurfaceRecognizer.h"

class CATlsoPersistentContext;
class CATCGMCellTracker;
class CATRibbonsReorderTracker;
class CATRibbonManifoldCreatorInfraContextUtilities;

class ExportedByPersistentCell CATFilletManifoldCreatorInfraContext : public CATFilletManifoldCreatorBase 
{
public:
  CATCGMDeclareManifoldAgent(CATFilletManifoldCreatorInfraContext, CATFilletManifoldCreatorBase)
	
	// Constructor
  CATFilletManifoldCreatorInfraContext();
	
  // Destructor
	virtual ~CATFilletManifoldCreatorInfraContext();

  void AddFilletBoneFollowers(ListPOfCATGMLiveContextualFeatureFollowers &iFilletBoneFollowers,CATListPV &iMatchedRibbons);
  void AddFilletBoneFollowers(ListPOfCATGMLiveContextualFeatureFollowers &iFilletBoneFollowers,CATListPV &iMatchedRibbons, int iNumOperatorIdForFollower);
  void SetCreationJournal(CATCGMJournalList* iJournal, CATRibbonsReorderTracker* iTracker); 

  virtual HRESULT CreateImageManifolds();
  virtual void AddCellManifoldImage(CATLISTP(CATCellManifold) &iParentCellManifolds, CATLISTP(CATCellManifold) &iChildrenManifolds, int iInfo, CATBoolean iForbidZeroInfo=TRUE);

  virtual int GetPriority();
  virtual CATBoolean IsAllowedToWorkOnCellManifoldWithoutAdvancedParentDeclarativeManifold();
  INLINE virtual CATDeclarativeManifoldAgent* Clone();
  
  // ST5 begin modifs: For Remove/Redo use
  // List of Sensitive DM to deal with
  void GetMostSensitiveDM(ListPOfCATDeclarativeManifold &oDeclarativeManifolds);
  void SetMostSensitiveDM(ListPOfCATDeclarativeManifold &iDeclarativeManifolds);
  void GetPersistentLimitingBodies(ListPOfCATPersistentBodies &oPersistentLimitingBodies);
  void SetPersistentLimitingBodies(ListPOfCATPersistentBodies &iPersistentLimitingBodies);

  CATRibbonManifoldCreatorInfraContextUtilities * GetUtilities(); // zus
  //EYL 12/2011 Methode temporaire en attendant la refonte du RemoveRedo pour arranger les journaux de creations de fillet
  CATDeclarativeManifold *GetOriginalFillet(ListPOfCATCellManifold &iBorderCellParentManifolds, ListPOfCATCellManifold & iChildren, CATPersistentBody * iPBody);

protected:
  virtual HRESULT SortFacesImplementation(ListPOfCATFace &iFacesToRecognize, ListPOfCATDRepSeed &oRibbonPieces);


  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATPersistentBody& iPBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);
  virtual CATBoneFillet* GetRadiusAndType(CATLISTP(CATCellManifold) &iBoneFilletRep, CATLISTP(CATCellManifold) iBoneFilletSupport[2], CATLiveBody& iLiveBody, ListPOfListPOfCATCellManifolds& iAllBoneAndJoint, double &ioRadius, CATSurfaceRecognizer::SurfaceType &oType);

  virtual void RecognizeJointAndDefineType(CATLiveBody &iLiveBody,
                                           CATGMLiveRibbonSorter &iRibbonSorter,
                                           int iJointIndex,
                                           ListPOfCATCellManifold &iJointFilletRep, 
                                           ListPOfCATCellManifold &iConnectedBoneFilletList,
                                           CATListOfInt &oResultDefineType);

  virtual void RepairBoneContextsInStepFillet(CATLiveBody              * iLiveBody,
                                              CATBoneFillet            * iBoneFillet,
                                              ListPOfCATCellManifold   & iBoneFilletRep,
                                              ListPOfCATCellManifold     ioBoneFilletSupport[2]);

  virtual CATFilletManifoldCreatorInfraContext *GetAsFilletManifoldCreatorInfraContext();
  virtual void FindMatchingFollowerOnBoneUsingRibbonTracker(ListPOfCATCellManifold iBoneReps,ListPOfCATGMLiveBoneFollowers &ioMatchingFollowers);
private :
// ----------------------------------------------------------------------------
  HRESULT SortFacesAccordingToJournal(CATCGMJournalList& iCreationJournal, CATBody& iInputBody, CATBody& iOutputBody, ListPOfCATFace& ioFaces, ListPOfCATDRepSeed& oRibbonPieces);

  void SortFacesAccordingToJournalDiscardIrrelevantCandidates(ListPOfCATFace& ioFaces);

  int SortFacesAccordingToJournalFIndOutSupports(CATBody& iInputBody, 
                                                 CATBody& iOutputBody,
                                                 CATLiveBody& iOutputLiveBody, 
                                                 ListPOfCATFace& ioFaces,
                                                 CATCGMJournalList& iJournal,
                                                 ListPOfCATFace PieceReps[], 
                                                 ListPOfListPOfCATFace PieceSupports[], 
                                                 CATListOfInt PieceSides[]);
  
  void SortFacesAccordingToJournalSupportConnexity(CATBody& iOutputBody, 
                                                   const int PieceCount, 
                                                   ListPOfCATFace PieceReps[], 
                                                   ListPOfListPOfCATFace PieceSupports[], 
                                                   CATListOfInt PieceSides[]);

  void SortFacesAccordingToRepsConnexitySameSupports(CATBody& iOutputBody,
                                         const int PieceCount, 
                                         ListPOfCATFace PieceReps[], 
                                         ListPOfListPOfCATFace PieceSupports[], 
                                         CATListOfInt PieceSides[]);

  void SortFacesAccordingToJournalUnTass(const int PieceCount, 
                                         ListPOfCATFace PieceReps[], 
                                         ListPOfListPOfCATFace PieceSupports[], 
                                         CATListOfInt PieceSides[]);

  HRESULT SortFacesAccordingToJournalComputeSidesAndCreatePieces(CATBody& iOutputBody, 
                                                                 ListPOfCATFace& ioFaces, 
                                                                 const int PieceCount, 
                                                                 ListPOfCATFace PieceReps[], 
                                                                 ListPOfListPOfCATFace PieceSupports[], 
                                                                 CATListOfInt PieceSides[],
                                                                 ListPOfCATDRepSeed& oRibbonPieces);

  HRESULT EnrichRibbonPieces(CATBody &iOutputBody, ListPOfCATDRepSeed &ioRibbonPieces);
  // ----------------------------------------------------------------------------

  // Specs for DRep
  //Twin lists
  ListPOfCATGMLiveContextualFeatureFollowers _FilletBoneFollowers;
  CATListPV _FilletRibbons;//CATListPV because we haven't access to CATDynFiletRibbon

  CATCGMJournalList _LocalCellManifoldJournal;
  CATCGMJournalList* _Journal;
  CATRibbonsReorderTracker* _RibbonsReorderTracker;
  CATRibbonManifoldCreatorInfraContextUtilities *_InfraContextUtilities;
  ListPOfCATDeclarativeManifold _MostSensitiveDM;
  ListPOfCATPersistentBodies _PersistentLimitingBodies;
};

INLINE CATDeclarativeManifoldAgent* CATFilletManifoldCreatorInfraContext::Clone()
{
  return new CATFilletManifoldCreatorInfraContext();
}

#endif
