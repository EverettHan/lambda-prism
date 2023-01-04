#ifndef CATGMLivePatternUtilities_H
#define CATGMLivePatternUtilities_H

#include "CATCGMNewArray.h"

#include "CATTopDefine.h"

#include "CATPersistentCell.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathDef.h"
#include "CATPatternManifoldSpecificationAttribute.h"
#include "CATCollec.h"
#include "ListPOfCATCellManifold.h"
#include "CATListOfCATCGMAttribute.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATGMLivePatternFollowers.h"
#include "CATlsoContext.h"
#include "ListPOfListPOfCATGMLiveContextualFeatureFollowers.h"
#include "CATBoneChamfer.h"
#include "CATDraftManifold.h"


class CATSoftwareConfiguration;
class CATBoneFillet;
class CATGMLiveSpecChg;
class CATCellManifoldGroup;
class CATCGMAttribute;
class CATMathVector;
class CATMathPoint;
class CATMathLine;
class CATPatternActivationInstanceStructure;
class CATPatternSecondaryTransfoStructure;
class CATLiveBody;
class CATCellManifoldPatternNavigator;
class CATTransfoCellDC;
class CATGMLivePatternFollower;
class CATPersistentCellInfra;
class CATVariationalPatternParameters;
class CATCGMHashTableWithAssoc;
class CATDeclarativeOperatorsBridge;
class CATDRepNavigator;
class CATGMLiveInfra;
class CATlsoPersistentContext;
class CATBoneFollowerPersistentFaceStructure;

class ExportedByPersistentCell CATGMLivePatternUtilities
{
public:

  // IZE SpecChg Management
  static HRESULT ExtractRequiredParameters(CATCellManifoldGroup* ipPattern,CATLONG32 iKey, ListPOfCATManifoldParameter & ioParamList);

  static HRESULT ExtractSpecChgFromParam(CATCellManifoldGroup* ipPattern, CATManifoldParameter * iParamToFind, CATLISTP(CATCGMAttribute) & ioSpecChg);

  //----------------------------------------------------------------------------------------------------------
  // Methodes pour le debug
  //----------------------------------------------------------------------------------------------------------
  
  // Ne peut etre utiliser QUE pour le debug.
  // Permet de suivre facilement les objets qui ne sont pas geres par la factory.
  static int GenerateDebugTag();
  static void InitDebugTagCounter(); // Pour l'instant le compteur est remi a 0 lors de l'unstream d'un patternSpecAttribute.
  
  //----------------------------------------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------------------------
  // Methodes pour  attributs / parametres d'edition
  //----------------------------------------------------------------------------------------------------------

  // Renvoie TRUE si les deux parametres modifient la meme caracteristique du Pattern.
  static CATBoolean HaveSameTarget(CATManifoldParameter * iParameter1, CATManifoldParameter * iParameter2);
  
  //----------------------------------------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------------------------
  // Methodes pour l'edition de pattern
  //----------------------------------------------------------------------------------------------------------

  static HRESULT SetMoveWithContextTransfoForEdition(CATCellManifoldGroup* ipPattern, 
    CATMathTransformation &iTransfo,
    CATVariationalPatternParameters * ioVariationalPatternParameters
    );

  static HRESULT SetSecondaryTransfoDataForEdition(CATCellManifoldGroup* ipPattern, 
    CATListOfShort & iInstanceNumbers, 
    CATLISTP(CATMathTransformation) & iSecondaryTransformations,
    CATVariationalPatternParameters * ioVariationalPatternParameters
    );

  static CATPatternManifoldSpecificationAttribute * CreateEditedPatternSpecAttr(CATCellManifoldGroup* ipPattern, 
                                                                                CATCellManifoldGroup* ipNewPattern,
                                                                                ListPOfCATGMLivePatternFollowers & iPatternFollowerList,
                                                                                CATGeoFactory       * iFactory,
                                                                                CATSoftwareConfiguration     * iConfig,
                                                                                CATPersistentBody                * iNewPersistentBody,
                                                                                CATVariationalPatternParameters * iVariationalPatternParameters = NULL,
                                                                                CATDeclarativeOperatorsBridge * iRemoveFaceRunner = NULL,
                                                                                CATCellManifoldsManager           * iCMManager = NULL
                                                                                );

  static HRESULT SimplifyPatternParameters(CATCellManifoldPatternNavigator  & iPatternNavigator,
                                  CATMathTransformation           &  oUnitaryTransfo,
                                  CATMathVector                   *&  oTranslationVector,
                                  CATMathLine                     *&  oRotationAxis,
                                  double                           & oRotationAngle,
                                  CATListOfShort                  &  oInstanceWithSecondaryTransformations,
                                  CATLISTP(CATMathTransformation) &  oSecondaryTransformations,
                                  CATMathTransformation           &  oRefTransfo
                                  );
  
/*
  static HRESULT CheckPatternAtLastRun(CATLiveBody          * ipLiveBody, 
                                       CATBoolean             iIsCalledByLiveOperator,
                                       int                  & oErrorNumber
                                       );
  */

  static HRESULT CheckPatternStructure(CATCellManifoldGroup * ipPattern,
                                       int                  & oErrorNumber
                                       );

  static HRESULT CheckPatternGroupStructure(CATCellManifoldGroup * ipPattern,
                                            int                  & oErrorNumber,
                                            CATBoolean             iCheckSpecAttr = TRUE);

  // Update the pattern references of the body.
  // A RemoveFace is performed to remove all the CM Ref without image in the pattern.
  static HRESULT UpdatePatternReferences(CATBody * ioBody, CATDeclarativeOperatorsBridge * iDeclarativeOpBridge, CATSoftwareConfiguration* iConfig);
  static HRESULT UpdatePatternReference(CATCellManifoldPatternNavigator  & iPatternNavigator, CATDeclarativeOperatorsBridge * iDeclarativeOpBridge, CATSoftwareConfiguration* iConfig);



  //----------------------------------------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------------------------
  // Methodes pour les entrees du Transforme Face
  //----------------------------------------------------------------------------------------------------------

  /*static HRESULT SplitGlobalAndLocalTransformations(CATTransfoCellDC                * iDC, 
                                                    CATCellManifoldGroup            * ipPattern, 
                                                    CATTransfoCellDC                * oRefTransfoDC, 
                                                    CATListOfShort                  & oInstancesList, 
                                                    CATLISTP(CATMathTransformation) & oLocalTransfoList
                                                    );*/

  /*static HRESULT SplitTransformations(ListPOfCATCellManifold          & iCMToMoveList, 
                                      CATLISTP(CATMathTransformation) & iTransfoList, 
                                      CATLiveBody                     * iInputLiveBody,
                                      ListPOfCATCellManifold          & oNoPatternCMToMoveList,
                                      CATLISTP(CATMathTransformation) & oNoPatternTransfoList,
                                      CATLISTP(CATCellManifoldGroup)  & oPatternList, 
                                      CATCGMHashTableWithAssoc **     & oRefCMWithTransfo,
                                      int                             & oRefCMWithTransfoSize,
                                      CATLISTP(CATMathTransformation) & oNewUnitaryTransfo
                                      );*/

  /*static HRESULT SplitTransformationsOnePattern(ListPOfCATCellManifold          & iCMToMoveList, 
                                                CATLISTP(CATMathTransformation) & iTransfoList, 
                                                CATLiveBody                     * iInputLiveBody,
                                                CATCellManifoldPatternNavigator * iPatternNav,
                                                CATBoolean                      & oNewUnitaryTransfo,
                                                CATGeoFactory                   & iFactory); //TRUE si l’unitarytransfo a changée*/

  static HRESULT SplitSpacingAndOtherTransfo(ListPOfCATCellManifold          & iCMToMoveList, 
                                      CATLISTP(CATMathTransformation) & iTransfoList, 
                                      CATLiveBody                     & iInputLiveBody,
                                      CATCellManifoldPatternNavigator & iPatternNav,
                                      CATVariationalPatternParameters & iVariationalPatternParameters, 
                                      CATGeoFactory                   & iFactory,
                                      CATCGMHashTableWithAssoc       *& oTransfoWithPatternFaces,
                                      CATBoolean                      & oMoveGlobal,
                                      CATCGMHashTableWithAssoc       * oTransfoWithSupportCM = NULL
                                      );


  // oType = 1 => GlobalMove.
  // oType = 2 => Changement de la transfo unitaire.
  // oType = 3 => Le type ne peut pas etre determine.
  //static HRESULT ComputePatternTransfoType(ListPOfCATCellManifold & iCMToMoveList, CATLISTP(CATMathTransformation) & iTransfoList, CATCellManifoldGroup  * iPattern, CATBody * iInputBody, int & oType);

  static HRESULT CheckAndCorrectVariationalOutput(ListPOfCATCellManifold & ioCMToMoveList, CATLISTP(CATMathTransformation) & ioTransfoList, CATBody * iInputBody);

  static HRESULT FindCommonTransformations(ListPOfCATCellManifold & ioCMToMoveList, CATLISTP(CATMathTransformation) & iTransfoList, CATLISTP(CATMathTransformation) & oTransfoList, ListPOfCATFace **& oFacesLists);

  //----------------------------------------------------------------------------------------------------------


  //----------------------------------------------------------------------------------------------------------
  // Autres methodes
  //----------------------------------------------------------------------------------------------------------

  static CATCGMAttribute *GetPatternAttribute(CATCellManifoldGroup* ipPattern);

  static HRESULT GetCorrectedAngle(double &ioRotationAngle);

  // Renvoie la liste des networkgroup de plus haut niveau presents dans la liste iCMGroups
  static HRESULT GetNetworkGroups(ListPOfCATCellManifoldGroup & iCMGroups, ListPOfCATCellManifoldGroup & oNetworkGroups);
  //static HRESULT GetNetworkGroup(CATCellManifoldGroup * iCMGroup, CATCellManifoldGroup *& oNetworkGroup);

  // Renvoie la liste des groupes reference contenu dans le network group en entree.
  static HRESULT GetReferenceGroupes(const CATCellManifoldGroup* ipPattern, ListPOfCATCellManifoldGroup & oReferenceGroups);

  // Renvoie le networkgroup associe a une CM
  //static HRESULT GetNetworkGroup(CATLiveBody * iLiveBody, CATCellManifold *iCM, CATCellManifoldGroup *& oNetworkGroup);


  
  static HRESULT GetImagePattern(CATCellManifoldGroup *  iOldPattern,
                                 CATCGMJournalList    *  iJournal,
                                 CATLiveBody          *  iNewLiveBody,
                                 CATCellManifoldGroup *& oNewPattern);

  // Renvoie le pattern follower associe a l'instance iInstance
  //static CATGMLivePatternFollower * GetInstancePatternFollower(ListPOfCATGMLiveContextualFeatureFollowers & iFollowerList, int iInstance);
  static CATGMLivePatternFollower * GetInstancePatternFollower(ListPOfCATGMLivePatternFollowers & iFollowerList, int iInstance);

  static void GetReferenceEdgeFromEdge(CATLiveBody *iLiveBody, CATPersistentBody * iRefPBody, CATCellManifoldPatternNavigator * iPatternNav, CATCGMJournalList * iJournal, CATEdge * iEdge, CATLISTP(CATCell) & oEdges, CATLISTP(CATCellManifold) & iClosureCM, CATPersistentCellInfra *  iPersistentCellInfra, CATlsoContext * iContext, short iChosenInstance);

  static void GetReferenceFaceFromSupportFace(CATLiveBody *iLiveBody, CATPersistentBody * iRefPBody, CATCellManifoldPatternNavigator * iPatternNav, CATCGMJournalList * iJournal, CATFace * iFace, CATLISTP(CATCell) & oFaces, CATLISTP(CATCellManifold) & iClosureCM, CATPersistentCellInfra *  iPersistentCellInfra, CATlsoContext * iContext);

  //static void GetFirstEdgesFromRefEdge(CATLiveBody *iLiveBody, CATEdge * iEdge, CATCGMJournalList * iJournal, CATLISTP(CATCell) & oCells);

  static HRESULT FindImagePatternGroup(CATCellManifoldGroup * ipOldGroup, CATCGMJournalList * ipJournal, CATLiveBody * ipImageLiveBody, ListPOfCATCellManifoldGroup & opImageGroupList);

  static void GetPatternFollowers(CATCellManifoldGroup * iNetworkGroup, ListPOfCATGMLiveContextualFeatureFollowers & iFollowerList, ListPOfCATGMLivePatternFollowers & oPatternFollowers);
 
  static CATBoolean AtLeastOneFaceBelongToPattern(CATLiveBody *iLiveBody, ListPOfCATFace & iFaceList);
  
  static int GetNumberOfPattern(CATDRepNavigator & iDRepNavigator);

  static void GetImageEdgesFromEdge(CATCellManifoldPatternNavigator * iPatternNavigator, CATEdge * iEdge, short iNumInstance, CATLISTP(CATEdge) & oEdges);

  static HRESULT DeleteRefCM(CATPatternManifoldSpecificationAttribute * iSpecAttribute, CATCellManifoldPatternNavigator * iPatternNavigator, CATLISTP(CATCellManifold) &iReferenceCellManifoldsToDelete, CATDeclarativeOperatorsBridge * iRemoveFaceRunner, CATSoftwareConfiguration* iConfig);

  static HRESULT DeleteRefCMG(CATPatternManifoldSpecificationAttribute * iSpecAttribute, CATCellManifoldPatternNavigator * iPatternNavigator, CATLISTP(CATCellManifoldGroup) &iReferenceCellManifoldGroupsToDelete, CATSoftwareConfiguration* iConfig);

  static CATPersistentBody *CreateBestResultPersistentBody(ListPOfCATManifoldParameter &iManifoldParameters,
                                                           CATPersistentCellInfra          &iPersistentCellInfra,
                                                           CATlsoPersistentContext * iContext,
                                                           CATCGMJournalList *oLiveJournal=NULL);
  static HRESULT FollowersSorting( ListPOfCATGMLiveContextualFeatureFollowers &iListOfBoneFollowers,
    ListPOfListPOfCATGMLiveContextualFeatureFollowers & oListOfListOfPatternFollowers) ;


  static void GetPatternGroupList(const CATLISTP(CATCellManifold) & iCMList, CATLiveBody & iLiveBody, CATLISTP(CATCellManifoldGroup) & oPatternGroupList);
  static void GetPatternGroup(CATCellManifold * iCM, CATLiveBody & iLiveBody, CATCellManifoldGroup *& oPatternGroup);

  static CATBoolean UpdateManifoldParameter(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATManifoldParameter * iParam1, CATManifoldParameter * iParam2, const ListPOfCATManifoldParameter & iParams);

  static CATBoolean AreSimilarBoneFillets(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATBoneFillet * iBF1, CATBoneFillet * iBF2);

  static CATBoolean AreSimilarBoneChamfers(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATBoneChamfer * iBC1, CATBoneChamfer * iBC2);

  static CATBoolean AreSimilarCellManifoldLists(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, ListPOfCATCellManifold & iCMList1, ListPOfCATCellManifold & iCMList2);

  static CATBoolean AreSimilarDraftManifolds(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATDraftManifold * iDM1, CATDraftManifold * iDM2); //DSH1 June 2020

  // insert in oNetWorkGroupHTab a Pattern network group of iDRepNavigator if all its CM are in iCellManifoldList
  static void AppendCoveredNetworkGroupHT(CATDRepNavigator & iDRepNavigator, ListPOfCATCellManifold & iCellManifoldList, CATCGMHashTable & oNetWorkGroupHTab);

  static CATBody * GetPatternBodyImage(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATFace * iOriginFace , CATBody * iBody);

  static CATPersistentBody * GetPatternPersistentBodyImage(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATFace * iOriginFace , CATPersistentBody * iPBody, CATlsoPersistentContext  &iContext);

  static void GetPatternTransfoImage(CATCellManifoldPatternNavigator * iPatternNavigator, short iNumInstance, CATMathTransformation & iTransfo, CATFace * iOriginFace, CATMathTransformation & oMathTransfo);

  static CATBoolean PatternEdition(CATLiveBody & iLiveBody, ListPOfCATFace & iFaceList);

  static CATBoolean NeedPatternReplicator(ListPOfCATManifoldParameter & iParamList);

  static CATGMLivePatternFollower * GetPatternFollowerFromNewPatternGroup(CATCellManifoldGroup * iNewPattern, ListPOfCATGMLivePatternFollowers & iPatternFollowerList);

  static CATGMLivePatternFollower * GetPatternFollowerFromNewPatternGroup(CATCellManifoldGroup * iNewPattern, ListPOfCATGMLiveContextualFeatureFollowers & iFollowerList);

  static void GetPatternFollowerList(ListPOfCATGMLiveContextualFeatureFollowers & iFollowerList, ListPOfCATGMLivePatternFollowers & oPatternFollowerList);

  static HRESULT CheckEdgesToErase(CATCellManifoldPatternNavigator * iPatternNav, ListPOfCATCellManifold & iClosureCMList, CATLiveBody * iLiveBody, ListPOfCATFace & iFaceList);

  static CATBoolean ComputeClashBetweenInstanceAndModifiedCells(int iInstance, CATCellManifoldPatternNavigator * iPatternNavigator, CATBody *& ioMovingFacesBody, CATCellManifoldsManager *  iCMManager);
 
  static void GetModifiedZoneBody(CATCellManifoldsManager *  iCMManager, CATBody *& ioMovingFacesBody);
  
  static CATBoolean ComputeClashBetweenInstanceAndModifiedCells_2(int iInstance, CATCellManifoldPatternNavigator * iPatternNavigator, CATCellManifoldsManager *  iCMManager);
  
  static void GetCreatedCellManifoldList(CATGMLivePatternFollower * iFollower, CATBody * iBody, ListPOfCATCellManifold & oCreatedCMList);

  static void GetFollowerListFromRefGroup(CATBoneFollowerPersistentFaceStructure * iPatternStructure, int iNumOperatorID, CATCellManifoldGroup * iGroup, ListPOfCATGMLivePatternFollowers & oFollowerlist);

  static void GetPatternCMGListType(ListPOfCATCellManifoldGroup & iCMGList, CATBoolean &oPatternGroup, CATBoolean &oInstanceGroup, CATBoolean &oMixedGroup);

  static void FindBestClosureFaces(CATlsoContext * iContext, CATBody * iBody, ListPOfCATFace & iBorderFaceList, CATBody * iRefBody, ListPOfCATFace & ioClosureFaceList);

  static CATMathVector ComputeNormalVsShell(CATFace & iFace,CATBody & iBody);

};

#endif 

