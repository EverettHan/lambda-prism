#ifndef CATGMLiveOffsetUtilities_H
#define CATGMLiveOffsetUtilities_H

#include "CATCGMNewArray.h"

#include "CATTopDefine.h"

#include "CATPersistentCell.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathDef.h"
#include "CATCollec.h"
#include "CATlsoContext.h"
#include "CATEdge.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATManifoldParameter.h"
#include "CATBoneChamfer.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfShort.h"
#include "CATDraftManifold.h"


class CATLiveBody;
class CATCellManifoldOffsetNavigator;
class CATCellManifoldGroup;
class CATCGMJournalList;
class CATPersistentCellCellFollower;
class CATBoneFillet;
class CATlsoPersistentContext;
class CATOffsetManifoldAttribute;
class CATOffsetReferenceManifoldAttribute;


class ExportedByPersistentCell CATGMLiveOffsetUtilities
{
public:
  
  static void SetReferenceLiveBody(CATCellManifoldOffsetNavigator * iOffsetNav, CATLiveBody * iNewRefLiveBody);

  static void FindImageOffsetGroup(CATCellManifoldGroup * ipOldGroup, CATCGMJournalList * ipJournal, CATLiveBody * ipImageLiveBody, CATCellManifoldGroup *& opImageGroup);

  static void GetImageEdgesFromEdge(CATCellManifoldOffsetNavigator * iOffsetNavigator, CATEdge * iEdge, short iNumSkin, CATLISTP(CATEdge) & oEdges);

  static double GetInstanceOffsetValueForShellOperator(CATCellManifoldGroup * iInstanceGroup, CATListOfDouble & iOffsetValues, CATPersistentBody * iInputPBody, CATPersistentBody * iOutputPBody, CATPersistentCellInfra * iPersistentCellInfra);

  static double GetOffsetValueForShellOperator(CATCellManifoldGroup * iGroup, CATListOfDouble & iOffsetValues, CATPersistentBody * iInputPBody, CATPersistentBody * iOutputPBody, CATPersistentCellInfra * iPersistentCellInfra);

  static CATBoolean AreSimilarBoneFillets(CATCellManifoldOffsetNavigator * iOffsetNavigator, short iNumInstance, CATBoneFillet * iBF1, CATBoneFillet * iBF2);

  static CATBoolean AreSimilarBoneChamfers(CATCellManifoldOffsetNavigator * iOffsetNavigator, short iNumInstance, CATBoneChamfer * iBC1, CATBoneChamfer * iBC2);

  
  static CATBoolean AreSimilarDraftManifolds(CATCellManifoldOffsetNavigator * iOffsetNavigator, short iNumInstance, CATDraftManifold * iDM1, CATDraftManifold * iDM2); //DSH1 Start June 2020

  static CATBoolean AreSimilarCellManifoldLists(CATCellManifoldOffsetNavigator * iOffsetNavigator, short iNumInstance, ListPOfCATCellManifold & iCMList1, ListPOfCATCellManifold & iCMList2);

  static CATBoolean UpdateManifoldParameter(CATCellManifoldOffsetNavigator * iOffsetNavigator, short iNumInstance, CATManifoldParameter * iParam1, CATManifoldParameter * iParam2, const ListPOfCATManifoldParameter & iParams);
  //iFace a face on the input skin
  //iNumInstance, num of target skin
  static double ReplicateChamferLeftValue(CATCellManifoldOffsetNavigator * iOffsetNavigator,double iLeftValue, double iRightValue, CATEdge * iEdge, CATFace * iSupport, short iNumInstance, CATLiveTypeChamfer iChamferType);

  static double ReplicateChamferRightValue(CATCellManifoldOffsetNavigator * iOffsetNavigator,double iLeftValue, double iRightValue, CATEdge * iEdge, CATFace * iSupport, short iNumInstance, CATLiveTypeChamfer iChamferType);

  //Journal of cells
  static void GetLateralCreatedFaces(CATCGMJournalList & iThickJournal, ListPOfCATFace & oLateralFaces);

  static void GetLateralFaces(CATCellManifoldOffsetNavigator & iOffsetNavigator, ListPOfCATFace & oLateralFaces);

  static void   GetAllSkins(CATCellManifoldGroup* iOffsetNetwork, ListPOfCATCellManifoldGroup &oInstanceGroups, CATListOfShort & oSkinNumbers);
  static double GetSkinOffsetValue(CATCellManifoldGroup * iSkinGroup);
  static double GetSkinOffsetThickness (CATCellManifoldGroup * iSkinGroup0, CATCellManifoldGroup * iSkinGroup1);

  static HRESULT ExtractRequiredParameters(CATCellManifoldGroup* ipPattern,CATLONG32 iKey, ListPOfCATManifoldParameter & ioParamList);

  static HRESULT ExtractSonsRequiredParameters(CATCellManifoldGroup* ipNetworkGroup,CATLONG32 iKey, ListPOfCATManifoldParameter & ioParamList);

  static int GenerateDebugTag();

  static HRESULT ComputeOffsetFollowersForRemoveFeature(CATPersistentBody           * iInputPBody, 
                                                        ListPOfCATPersistentFaces   & iInputPersistentFaces, 
                                                        CATlsoPersistentContext     & iPersistentContext, 
                                                        ListPOfCATGMLiveContextualFeatureFollowers &oComputedOffsetFollowers); 

  // Utilitaire de code
  static CATOffsetManifoldAttribute * GetSkinAttribute (CATCellManifoldGroup * iInstanceCMdGroup);
  static CATOffsetReferenceManifoldAttribute * GetRefAttribute (CATCellManifoldGroup * iReferenceCMGroup);
};

#endif 

