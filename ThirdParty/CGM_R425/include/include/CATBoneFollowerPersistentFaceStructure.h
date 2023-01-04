#ifndef CATBoneFollowerPersistentFaceStructure_H
#define CATBoneFollowerPersistentFaceStructure_H

#include "CATCGMNewArray.h"

#include "CATSoftwareConfiguration.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfInt.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATPersistentBodies.h"
#include "CATCollec.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATPatternManifoldSpecificationAttribute.h"
#include "CATDrawerCollector.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCellManifoldHashTableWithAttributeAssoc.h"
#include "CATMathInline.h"
#include "ListPOfCATGMLivePatternFollowers.h"
#include "ListPOfCATExtTopOperators.h"

class CATPersistentBody;
class CATGMLiveContextualFeatureFollower;
class CATLiveBody;
class CATCellManifoldGroup;
class CATLISTP(CATCellManifoldGroup);
class CATRibbonsReorderTracker;
class CATPatternManifoldAttribute;
class CATPatternReferenceManifoldAttribute;
class CATVariationalPatternParameters;
class CATCGMStream;
class CATDeclarativeOperatorsBridge;

class ExportedByPersistentCell CATBoneFollowerPersistentFaceStructure
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATBoneFollowerPersistentFaceStructure();
  
  virtual ~CATBoneFollowerPersistentFaceStructure();

  //Methods
  void AddContextualFeatureFollower(CATGMLiveContextualFeatureFollower *iBoneFollower);
  
  void AddPersistentCell(CATPersistentCell &iPersistentCell);
  void RemovePersistentCell(CATPersistentCell *iPersistentCell);
  void AddListOfPersistentCell(ListPOfCATPersistentCells &iListOfPersistentCell);

  // ST5 begin modifs: For Remove/Redo use
  // List of Least and Sensitive DM to deal with
  void GetSensitiveDeclarativeManifolds(ListPOfCATDeclarativeManifold & oSensitiveDeclarativeManifolds,ListPOfCATPersistentBodies *iContainers=NULL,CATPersistentCellInfra *iInfra=NULL);
  INLINE CATPersistentBody * GetSensitiveDeclarativeManifoldsContainer();
  void GetRemoveFeaturePersistentLimitingBodies(ListPOfCATPersistentBodies & oRemoveFeaturePersistentLimitingBodies);

  void SetSensitiveDeclarativeManifolds(ListPOfCATDeclarativeManifold &iDeclarativeManifolds,CATPersistentBody *iContainer);
  void SetRemoveFeaturePersistentLimitingBodies(ListPOfCATPersistentBodies &iPersistentLimitingBodies);

  // ST5 Wk42/2010: Provides order in fillet creation after Redo
  CATRibbonsReorderTracker * GetRedoFeatureRibbonsReorderTracker();
  void SetRedoFeatureRibbonsReorderTracker(CATRibbonsReorderTracker * ipRibbonsTracker);
  void CreateRibbonsReorderTracker(CATSoftwareConfiguration * ipConfig);
  void DeleteRibbonsReorderTracker();
  void DeleteBoneFollowers();
  // ST5 Wk43/2010: Warns Redo when RemoveFillet propagation stopped on Joint 
  CATBoolean GetRemoveFilletStoppedOnJoint();
  void SetRemoveFilletStoppedOnJoint(CATBoolean iRemoveFilletStoppedOnJoint);
  //ST5 Wk36-2011: Dev for Joints shape stability
  void GetConstraintsForJointsShapeRecovery(ListPOfCATCell oListForJointsShapeRecovery[2]);
  void SetConstraintsForJointsShapeRecovery(ListPOfCATCell iListForJointsShapeRecovery[2]);
  //ST5 Wk47-2011: For body livification at Redo when a simplication occured
  void SetSimplifState(CATBoolean SimplifState);
  CATBoolean GetSimplifState();
  CATPersistentBody * GetPersistentBodyForTypeReport();
  void SetPersistentBodyForTypeReport(CATPersistentBody * ipPersistentBodyForTypeReport);

  void CreateNewCMRefGroups(CATCellManifoldGroup* iPatternGroup, CATLiveBody* iResultBody, CATLISTP(CATCellManifoldGroup) &oCMRefGroups);
  void CreateNewInstanceGroups(CATCellManifoldGroup* iPatternGroup, CATLiveBody* ioResultBody, CATLISTP(CATCellManifoldGroup) &ioInstanceGroups, int iNumOperator=0);
  void CompleteReferenceGroups(CATPatternManifoldAttribute* iAttribute, CATCellManifoldPatternNavigator * iCarriedPatternNav, CATLiveBody* ioResultBody, CATLISTP(CATCellManifoldGroup) &ioCMRefGroups);

  void GetPatternFollowers(CATCellManifoldGroup* iNetworkGroup, ListPOfCATGMLivePatternFollowers & oPatternFollowers);
  CATPatternManifoldSpecificationAttribute * CreatePatternSpecAttr(CATCellManifoldGroup* iNetworkGroup, CATPatternManifoldSpecificationAttribute * iCarriedAttribute, CATCellManifoldGroup* iOldNetworkGroup, CATVariationalPatternParameters * iVariationalPatternParameters, CATDeclarativeOperatorsBridge * iRemoveFaceRunner, CATGeoFactory * iFactory, CATSoftwareConfiguration * iConfig,CATPersistentBody      * iNewPersistentBody);

  void SetCMSetToRemoveByClashAnalysis(ListPOfCATCellManifold &iCellManifolds);
  ListPOfCATCellManifold GetCMSetToRemoveByClashAnalysis();

  CATPersistentBody *GetInitialBodyWithAllFeaturesForOperator(int iNumOperatorId);
  CATPersistentBody *GetInitialBodyWithoutAllFeaturesForOperator(int iNumOperatorId);

public:
  //CATListOfInt                               _ListOfBoneFollowerType;

  INLINE ListPOfCATPersistentCells GetListOfPersistentCells();
  INLINE void AppendListOfPersistentCells(ListPOfCATPersistentCells &iListOfPersistentCells);
  void CleanNoMultiRunDatas();

  // Official get method to use
  void GetListOfContextualFollower(int iNumOperatorIDForFollower, ListPOfCATGMLiveContextualFeatureFollowers &oContextualFollower) const;  

  // Methode to call in the destructor of SingleModifyFace because tow operator could have the same adress
  void CleanFollowersForOperator(int iNumOperatorIDForFollower);

  void CleanFollowerList(ListPOfCATGMLiveContextualFeatureFollowers & iFollowerList);

  void SetCMInCollision(CATCellManifold * iCM, CATCellManifold * iOriginCM);
  void GetCMInCollision(ListPOfCATCellManifold & oCMInCollision);
  void SetCMInCollisionOrigin(CATCellManifold * iCM);
  void GetCMInCollisionOrigin(ListPOfCATCellManifold & oCMInCollisionOrigin);
  INLINE ListPOfCATCellManifold GetCMRepresentationInInitialBody();
  INLINE void AppendCMRepresentationInInitialBody(ListPOfCATCellManifold &iCMRepresentationInInitialBody);
  void ClearCollisionTables();
  //CATDrawerCollector * _CollisionDrawerCollector;
  void SetAssocAttr(CATCellManifold * iRefCM, CATPatternReferenceManifoldAttribute * iAttr);
  CATPatternReferenceManifoldAttribute * GetAssocAttr(CATCellManifold * iRefCM);
  CATCellManifoldHashTableWithAttributeAssoc * GetRefCMWithAssocAttr();


  void ReplacePersistentBodyWithAllFeature(CATPersistentBody *iPBodyToReplace, CATPersistentBody * ipReplacePBody);

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory,CATPersistentCellInfra  &iInfra) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory,CATPersistentCellInfra  &iInfra);

  // Private only
  INLINE const ListPOfCATGMLiveContextualFeatureFollowers & GetListOfBoneFollowers() const;

private:

  void Init();

  INLINE void CleanListOfPersistentCells();  


  // ST5 begin modifs: For Remove/Redo use

  ListPOfCATPersistentCells _ListOfPersistentCells;
  ListPOfCATGMLiveContextualFeatureFollowers  _ListOfBoneFollowers;
  
  //Pour le Pattern
  ListPOfCATCellManifold _CMRepresentationInInitialBody;
  ListPOfCATCellManifold _CMInCollision;
  ListPOfCATCellManifold _CMInCollisionOrigin;

  // List of Least and Sensitive DM to deal with

  ListPOfCATDeclarativeManifold _SensitiveDeclarativeManifolds;
  CATPersistentBody             *_SensitiveDeclarativeManifoldsContainer;
  ListPOfCATPersistentBodies _RemoveFeaturePersistentLimitingBodies;

  // ST5 Wk42/2010: Provides order in fillet creation after Redo
  CATRibbonsReorderTracker * _pRibbonsTracker;
  // ST5 Wk43/2010: Warns Redo when RemoveFillet propagation stopped on Joint
  CATBoolean _RemoveFilletHasStoppedOnJoint;
  //ST5 Wk36-2011: Dev for Joints shape stability
  CATBoolean _SimplifState;
  ListPOfCATCell _ListForJointsShapeRecovery[2];
  CATPersistentBody * _pPersistentBodyForTypeReport;

  // JJ3 pour le pattern : 
  CATCellManifoldHashTableWithAttributeAssoc * _RefCMWithAssocAttr;
  CATLONG32 _DebugTag; // Pour le debug

  //EYL Synchrone Lists recording, for each operator, the initial body with all features, and the final body without all features
  // In case of there is several RemoveFeature for one Redo Feature (Not up to date cm)
  ListPOfCATPersistentBodies _InputPersistentBodiesWithAllFeatures;
  ListPOfCATPersistentBodies _InputPersistentBodiesWithoutAllFeatures;
  CATListOfInt               _NumOperatorsCallingRemoveRedo;
};
INLINE ListPOfCATCellManifold CATBoneFollowerPersistentFaceStructure::GetCMRepresentationInInitialBody()
{
  return _CMRepresentationInInitialBody;
}
INLINE void CATBoneFollowerPersistentFaceStructure::AppendCMRepresentationInInitialBody(ListPOfCATCellManifold &iCMRepresentationInInitialBody)
{
  _CMRepresentationInInitialBody.Append(iCMRepresentationInInitialBody);
}
INLINE ListPOfCATPersistentCells CATBoneFollowerPersistentFaceStructure::GetListOfPersistentCells()
{
  return _ListOfPersistentCells;
}
INLINE void CATBoneFollowerPersistentFaceStructure::AppendListOfPersistentCells(ListPOfCATPersistentCells &iListOfPersistentCells)
{
  _ListOfPersistentCells.Append(iListOfPersistentCells);
}
INLINE void CATBoneFollowerPersistentFaceStructure::CleanListOfPersistentCells()
{
  _ListOfPersistentCells.RemoveAll();
}
INLINE const ListPOfCATGMLiveContextualFeatureFollowers & CATBoneFollowerPersistentFaceStructure::GetListOfBoneFollowers() const
{
  return _ListOfBoneFollowers;
}
INLINE CATPersistentBody * CATBoneFollowerPersistentFaceStructure::GetSensitiveDeclarativeManifoldsContainer()
{
  return _SensitiveDeclarativeManifoldsContainer;
}
#endif 

