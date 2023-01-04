// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//=============================================================================
//
// RESPONSIBLE  : PFV 
//
// DESCRIPTION  : Class for manage a sequence of TopOperator
//                in order to create BRep Modeling Operator for CATIA Live Shape.
//
//=============================================================================
// Creation PFV April 2008
//
//=============================================================================
#ifndef CATPersistentCellInfra_H
#define CATPersistentCellInfra_H

#include "PersistentCell.h"
#include "CATGMBaseInfra.h"
#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATPersistentCellFactory.h"
#include "CATGMLivePersistentCellInformer.h"
#include "CATAutoBaseThreadContext.h"
#include "ListVOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "ListPOfCATDeclarativeManifoldAgent.h"
#include "ListPOfCATPersistentFaces.h"
#include "CATCollecRoot.h"
#include "CATPersistentOperator.h"
#include "CATMathInline.h"
#include "ListPOfCATLiveBody.h"
#include "ListPOfCATGMLiveContextualFeatureFollowers.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATPersistentVertices.h"
#include "CATlsoDataCache.h"
#include "CATCGMHashTableWithAssoc.h"
#include "ListPOfCATlsoAgentInputDataCarrier.h"
#include "CATError.h"
#include "ListPOfCATManifoldBaseParameter.h"
#include "CATLiveBodyValidityServices.h"
#include "CATPersistentBody.h"
// #include "CATLSOHashMap.h"

class CATSoftwareConfiguration;
class CATGMLiveBodyAttribute;
class CATLiveBody;
class CATBody;
class CATTopJournalSpy;
class CATPersistentCellsJournal;
class CATLISTP(CATPersistentFace);
class CATLISTP(CATPersistentBody);
class CATLISTP(CATPersistentVertex);
class CATLISTP(CATEdge);
class CATLISTP(CATVertex);
class CATMathTransformation;
class CATAutoBaseRemoveFace;
class CATGMLiveShapeOperator;
class CATGMLiveInfra;
class CATTopMultiResult;
class CATCGMCellTracker;
class CATPersistentCellsBasedCellManifoldsManager;
class CATVariationalPatternParameters;
class CATIPGMTopOperator;
class CATDeclarativeOperatorsBridge;
class CATExtTopOperator;
//class CATTopOpInError;
//class CATPGMDRepBehavior;
class CATPersistentCellCellFollower;
//class CATCGMDiagnosis;
class CATlsoAgentInputDataCarrier;
class CATCGMJournalInfo;
class CATUnicodeString;
class CATGMSpecInfra;
class CATDeclarativeManifold;
class CATCellManifoldGroup;
class CATFaceHashTable;
class CATPersistentCell;
template <class CATPersistentCell> class CATLSOHashTable;
class CATEdgeHashTable;
class CATLISTP(CATGeometry);

//template <class CATCell, class CATLISTP(CATGeometry) > class CATLSOHashMap;


class ExportedByPersistentCell CATPersistentCellInfra : public CATGMBaseInfra
{
  friend class CATPersistentExtTopOperator;

public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  
 /* enum LastErrorLevel {
    LastErrorLevel_Undefined = 0,
    LastErrorLevel_Low       = 1,
    LastErrorLevel_Normal    = 2,
    LastErrorLevel_High      = 3,
    LastErrorLevel_Critical  = 4,
    LastErrorLevel_Fatal     = 5
  };*/

  // Constructor
  CATPersistentCellInfra(CATGeoFactory & iGeoFactory, CATSoftwareConfiguration* iConfig, const CATUnicodeString *iMainErrorMsgId=NULL);
protected:
  CATPersistentCellInfra(CATGeoFactory &iGeoFactory, const CATAutoBaseThreadContext* iThreadContext, CATPersistentCellFactory* iPersistentCellFactory);

public:
  // Destructor
  virtual ~CATPersistentCellInfra();

  // Use only for debug
  void DumpPersistentCellFactory();          // Use only for debug
  void SynthesisDumpPersistentCellFactory(); // Use only for debug
  void CreateLSOFileWithAdditionalName(CATExtTopOperator * ipExtTopOpeForDebug=NULL);

  // ------------------------------------------------------------
  // Create a PersistentBody from an input CATBody
  // ------------------------------------------------------------
  virtual CATPersistentBody* AppendInputBody(CATBody* iInputBody, CATGMLivePersistentCellInformer &ioPersistentCellInformer, CATBoolean iLiveCheck=TRUE);
  CATBoolean AppendInputPersistentBody(CATPersistentBody* iInputPersistentBody);
  INLINE void GetListOfInputPersistentBodies(CATLISTP(CATPersistentBody) &oInputPersistentBodies);

  // ------------------------------------------------------------
  // Get PersistanceFace or List: To follow cells between bodies
  // ------------------------------------------------------------
  CATPersistentFace* GetPersistentFace(CATGMLivePersistentCellInformer & iPersistentCellInformer, CATFace * iFace);
  void GetListOfPersistentFaces(CATGMLivePersistentCellInformer & iPersistentCellInformer,
    CATLISTP(CATFace) & iListOfFaces, CATLISTP(CATPersistentFace) & oListOfPersistentFaces);

  CATPersistentCell * GetThePersistentCellsInContainer(CATCell           & iCell,
                                                       CATPersistentBody & iContainer) const;
  //EYL FOR NewPCells
  CATPersistentCell * GetTheJournalPersistentCellInContainer(CATCell           & iCell,
  CATPersistentBody & iContainer) const;
  void GetAllJournalPEdgesInContainer(CATPersistentBody *iContainer,ListPOfCATPersistentEdges &iJournalPEdges);
  void GetListOfPersistentCellsInContainer(const CATLISTP(CATCell)            & iListOfCells,
                                            CATLISTP(CATPersistentCell)       & oListOfPersistenCells,
                                            const ListPOfCATPersistentBodies  & iContainers)const;

  void GetListOfPersistentCellsInContainer(const CATLISTP(CATCell)      & iListOfCells,
                                            CATLISTP(CATPersistentCell) & oListOfPersistenCells,
                                            CATPersistentBody           * iContainer)const;

  void GetListOfPersistentCellsInContainer( const CATCellHashTable      & iHashTabOfCells,
                                            CATLISTP(CATPersistentCell) & oListOfPersistenCells,
                                            CATPersistentBody           * iContainer)const;

  void GetListOfPersistentFacesInContainer(const CATLISTP(CATFace)     & iListOfFaces,
                                           CATLISTP(CATPersistentFace) & oListOfPersistenFaces,
                                           CATPersistentBody           * iContainer) const;
  void GetListOfPersistentFacesInContainer(const CATLISTP(CATFace)     & iListOfFaces,
                                           CATLISTP(CATPersistentFace) & oListOfPersistenFaces,
                                           const ListPOfCATPersistentBodies  & iContainers) const;
  // whith hashtable
  void GetListOfPersistentFacesInContainer(const CATFaceHashTable      & iHashTabOfFaces,
                                           CATLISTP(CATPersistentFace) & oListOfPersistenFaces,
                                           CATPersistentBody           * iContainer) const;
  void GetListOfPersistentFacesInContainer(const CATFaceHashTable      & iHashTabOfFaces,
                                           CATLISTP(CATPersistentFace) & oListOfPersistenFaces,
                                           const ListPOfCATPersistentBodies  & iContainers) const;
  void GetListOfPersistentEdgesInContainer(const CATEdgeHashTable      & iHashTabOfEdges,
                                           CATLISTP(CATPersistentEdge) & oListOfPersistenEdges,
                                           CATPersistentBody           * iContainer) const;

  void GetListOfPersistentEdgesInContainer(const CATLISTP(CATEdge)     & iListOfEdges,
                                           CATLISTP(CATPersistentEdge) & oListOfPersistenEdges,
                                           CATPersistentBody           * iContainer) const;

  void GetListOfPersistentVerticesInContainer(const CATLISTP(CATVertex)  & iListOfEdges,
                                           CATLISTP(CATPersistentVertex) & oListOfPersistenEdges,
                                           CATPersistentBody             * iContainer) const;
  
  void GetListOfPersistentEdgesInContainer(const CATLISTP(CATEdge)     & iListOfEdges,
                                           CATLISTP(CATPersistentEdge) & oListOfPersistenEdges,
                                           ListPOfCATPersistentBodies  & iContainers) const;

  // -------------------------------------
  // Get Face or Body form Persistent Cell
  // --------------------------------------
  CATBody * GetBodyFromPersistentBody(const CATPersistentBody* iPersistentBody) const;
  
  //VB7 - project : clean code which use following method
  CATPersistentBody * GetPersistentBodyFromBody(const CATBody* iBody);
  //VB7 - project : use following methods instead of previous one
  CATPersistentBody * GetPersistentBodyFromBody_ForUnstream(const CATBody* iBody);
  CATPersistentBody * GetPersistentBodyFromBody_ForExternalBody(const CATBody* iBody);
  CATPersistentBody * GetPersistentBodyFromBody_ForTemporaryProto(const CATBody* iBody);
  CATPersistentBody * GetPersistentBodyFromBody_ForCellManifoldsManager(const CATBody* iBody);
  
  void GetPersistentBodiesFromBody(CATBody* iBody, ListPOfCATPersistentBodies & oResultPersistentBodies);

  //Get The created cells with info iInfo.
  //if iInfo =0, get all created cells without info too
  void GetCreatedCellsByInfo(const ListPOfCATPersistentCells &iOriginPersistentCells,const CATPersistentBody *iContainer,int iInfo, ListPOfCATCell &oCreatedCells);
  void GetCreatedCellsByInfo(CATPersistentCell *iOriginPersistentCell,const CATPersistentBody *iContainer,int iInfo, ListPOfCATCell &oCreatedCells);
  void GetCreatedFacesByInfo(const ListPOfCATPersistentCells &iOriginPersistentCells,const CATPersistentBody *iContainer,int iInfo, ListPOfCATFace &oCreatedFaces);
  
  void GetCellsRepresentationByType(CATPersistentBody * iPersistentBody, CATPersistentCell * iPersistentCell, int iType, ListPOfCATCell &oCells);
  void GetCellsRepresentation(CATPersistentBody * iPersistentBody, CATPersistentCell * iPersistentCell, ListPOfCATCell &oCells,
    CATListOfInt *oOrientations = NULL, CATListOfInt *oTypes = NULL);
  void GetFacesRepresentationByType(CATPersistentBody * iPersistentBody, const CATLISTP(CATPersistentFace) & iListOfPersistentFaces, int iType, CATLISTP(CATFace) &oListOfFaces);

  void GetPersistentFaceRepresentation(CATPersistentBody* iPersistentBody, CATPersistentFace* iPersistentFace, CATLISTP(CATFace) &ioFaces, CATListOfInt *oOrientations=NULL);
  void GetPersistentFaceRepresentation(CATPersistentBody* iPersistentBody, CATPersistentFace* iPersistentFace, CATFaceHashTable &ioFaceHT, CATListOfInt *oOrientations=NULL);

  void GetListOfPersistentFacesRepresentation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                              CATLISTP(CATFace) &oListOfFaces);
  void GetListOfPersistentFacesRepresentation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                              CATFaceHashTable &oFaceHT);
  void GetListOfPersistentFacesRepresentationByModificationAndCreation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                              CATLISTP(CATFace) &oListOfFaces);

  //To find former representation
  void GetListOfPersistentFacesRepresentationByModificationAndCreationAncestors(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                              CATLISTP(CATFace) &oListOfFaces);
  void GetListOfPersistentFacesRepresentationByModificationAncestors(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                              CATLISTP(CATFace) &oListOfFaces);

  void GetListOfPersistentEdgesRepresentationByModificationAndCreation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges,
                                              CATLISTP(CATEdge) &oListOfEdges);

  //To find former representation
  void GetListOfPersistentEdgesRepresentationByModificationAndCreationAncestors(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges,
                                              CATLISTP(CATEdge) &oListOfEdges);
  void GetListOfPersistentEdgesRepresentationByModificationAncestors(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges,
                                              CATLISTP(CATEdge) &oListOfEdges);

  

  void GetListOfPersistentVerticesRepresentationByModificationAndCreation(CATPersistentBody * iPersistentBody, 
                                              const ListPOfCATPersistentVertices & iListOfPersistentVertices,
                                              ListPOfCATVertex &oListOfVertices);

  //To find former representation
  void GetListOfPersistentVerticesRepresentationByModificationAndCreationAncestors(CATPersistentBody * iPersistentBody, 
                                              const ListPOfCATPersistentVertices & iListOfPersistentVertices,
                                              ListPOfCATVertex &oListOfVertices);
  void GetListOfPersistentVerticesRepresentationByModificationAncestors(CATPersistentBody * iPersistentBody, 
                                              const ListPOfCATPersistentVertices & iListOfPersistentVertices,
                                              ListPOfCATVertex &oListOfVertices);

  void GetPersistentEdgeRepresentation(CATPersistentBody* iPersistentBody, CATPersistentEdge* iPersistentEdge, CATLISTP(CATEdge) &ioEdges);
  void GetListOfPersistentEdgesRepresentation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges,
                                              CATLISTP(CATEdge) &oListOfEdges,CATListOfInt *oListOfOrientation=NULL);
  void GetPersistentVertexRepresentation(CATPersistentBody* iPersistentBody, CATPersistentVertex* iPersistentVertex, CATLISTP(CATVertex) &ioVertices);
  void GetListOfPersistentVerticesRepresentation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentVertex) & iListOfPersistentVertices,
                                              CATLISTP(CATVertex) &oListOfVertices);
  void GetListOfPersistentCellsRepresentation(const CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentCell) & iListOfPersistentCells,
                                              CATLISTP(CATCell) &oListOfCells,
                                              CATListOfInt *oOrientations = NULL,
                                              CATListOfInt *oTypes = NULL);

  void GetListOfPersistentCellsRepresentationByModificationAndCreation(CATPersistentBody                        * iPersistentBody, 
                                                                       const CATLSOHashTable<CATPersistentCell> & iPersistentCellHT,
                                                                       CATCellHashTable                         & oCellHT) const;
  
  void GetListOfPersistentCellsRepresentationByModificationAndCreation(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentCell) & iListOfPersistentCells,
                                              CATLISTP(CATCell) &oListOfCells);

  void GetListOfPersistentCellsRepresentationByModificationAndCreationAncestors(CATPersistentBody * iPersistentBody, 
                                              const CATLISTP(CATPersistentCell) & iListOfPersistentCells,
                                              CATLISTP(CATCell) &oListOfCells);

  void GetAllChildrenWithTypes(const ListPOfCATCell &iInputCells,CATPersistentBody *iInputPBody,CATPersistentBody *iOutputPBody, ListPOfCATCell &oOutputCells, CATListOfInt &oTypes);
  void InvertRepresentationInContainer(CATPersistentCell *iPersistentCell, CATPersistentBody *iPersistentBody);

  void SetOrientationFromGeometryInContainer(CATPersistentBody *iContainer, CATCell *iCell,int iOrientationFromGeometry);
  void SetOrientationFromGeometryInContainer(CATPersistentBody *iContainer, CATPersistentCell *iPCell,CATCell *iCell,int iOrientationFromGeometry);

  // ------------------------------------------------------------
  // Get Persistent Cells created from a Persistent Cell
  // ------------------------------------------------------------
  void GetCreatedPersistentFaces(const ListPOfCATPersistentFaces &iOriginPersistentFaces, ListPOfCATPersistentFaces &oCreatedPersistentFaces,int iInfo= INT_MIN);
  void GetCreatedPersistentEdges(const ListPOfCATPersistentEdges &iOriginPersistentEdges, ListPOfCATPersistentEdges &oCreatedPersistentEdges,int iInfo= INT_MIN);
  void GetCreatedPersistentVertices(const ListPOfCATPersistentVertices &iOriginPersistentVertices, ListPOfCATPersistentVertices &oCreatedPersistentVertices,int iInfo= INT_MIN);
  
  void GetCreatedPersistentCells(const ListPOfCATPersistentCells &iOriginPersistentCells, ListPOfCATPersistentCells &oCreatedPersistentCells,int iInfo= INT_MIN);
  void GetCreatedPersistentCells(const CATLSOHashTable<CATPersistentCell> &iOriginPersistentCells, CATLSOHashTable<CATPersistentCell> &oCreatedPersistentCells,int iInfo= INT_MIN) const;

  void GetCreatedPersistentCells(CATPersistentCell * iOriginPersistentCell, CATLSOHashTable<CATPersistentCell> &oCreatedPersistentCells, int iInfo) const;
  void GetCreatedPersistentCells(CATPersistentCell * iOriginPersistentCell, ListPOfCATPersistentCells &oCreatedPersistentCells, int iInfo= INT_MIN);
  void GetAllCreatedCells(ListPOfCATPersistentCells &oCreatedPersistentCells,CATBoolean iOnlyTheOnesWithParents = 0);
  void GetAllModifiedCells(ListPOfCATPersistentCells &oModifiedPersistentCells);

  //GetExclusiveCreated Methods : To get the children created by only this parents (with no other parents)
  void GetExclusiveCreatedPersistentCells(CATPersistentCell *iOriginPersistentCell, 
                                                       ListPOfCATPersistentCells &oCreatedPersistentCells, int iInfo=INT_MIN);

  //return created exclusive children of each PCells, one by one.
  //For exclusive children of the groups, use GetExculsiveChildren method
  void GetExclusiveCreatedPersistentCells(ListPOfCATPersistentCells &iOriginPersistentCells, ListPOfCATPersistentCells &oCreatedPersistentCells);

  void GetExclusiveCreatedPersistentEdges(ListPOfCATPersistentEdges &iOriginPersistentEdges,
                                                       ListPOfCATPersistentEdges &oCreatedPersistentEdges);

  void GetExclusiveModifiedChildrenPersistentCells(ListPOfCATPersistentCells &iOriginPersistentCells, ListPOfCATPersistentCells &oExculsiveModifiedChildren);
  void GetExclusiveChildrenPersistentCells(ListPOfCATPersistentCells &iOriginPersistentCells, ListPOfCATPersistentCells &oExculsiveModifiedChildren);
  void GetModifiedPersistentFaces(const ListPOfCATPersistentFaces &iOriginFaces, ListPOfCATPersistentFaces &oModifiedFaces);
  void GetModifiedPersistentEdges(const ListPOfCATPersistentEdges &iOriginEdges, ListPOfCATPersistentEdges &oModifiedEdges);
  void GetModifiedPersistentVertices(const ListPOfCATPersistentVertices &iOriginVertices, ListPOfCATPersistentVertices &oModifiedVertices);
  
  void GetModifiedPersistentCells(const ListPOfCATPersistentCells &iOriginCells, ListPOfCATPersistentCells &oModifiedCells);
  void GetModifiedPersistentCells(const CATLSOHashTable<CATPersistentCell> &iOriginCells, CATLSOHashTable<CATPersistentCell> &oModifiedCells) const;

  void GetParentPersistentCells(CATPersistentCell *iCreatedPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells);
  void GetParentPersistentCellsInContainers(CATPersistentCell *iCreatedPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells, const ListPOfCATPersistentBodies &iContainers,
                                                                  CATBoolean &oInfoDefined,int &oInfoNumber) const;

  void GetParentModifiedPersistentCellsInContainers(CATPersistentCell *iCreatedPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells, const ListPOfCATPersistentBodies &iContainers,
                                                                  CATBoolean &oInfoDefined,int &oInfoNumber) const
                                                                  ;
  void GetParentModifiedPersistentCellsInContainers(const ListPOfCATPersistentCells & iCreatedPersistentCells, ListPOfCATPersistentCells &oOriginPersistentCells,ListPOfCATPersistentBodies &iContainers);
  void GetParentModifiedPersistentCellsInContainers(const CATLSOHashTable<CATPersistentCell> & iCreatedPersistentCells, CATLSOHashTable<CATPersistentCell> &oOriginPersistentCells, const ListPOfCATPersistentBodies &iContainers) const;

  void GetParentPersistentCellsInContainers(const CATLSOHashTable<CATPersistentCell> & iCreatedPersistentCells, CATLSOHashTable<CATPersistentCell> &oOriginPersistentCells, const ListPOfCATPersistentBodies &iContainers) const;
  void GetParentPersistentCellsInContainers(const ListPOfCATPersistentCells & iCreatedPersistentCells, ListPOfCATPersistentCells &oOriginPersistentCells,ListPOfCATPersistentBodies &iContainers);

  void GetParentModifiedPersistentCells(CATPersistentCell *iPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells);
  void GetParentPersistentCellsWithInfo(CATPersistentCell *iCreatedPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells);
  void GetParentPersistentCellsWithInfoAndGetInfo(CATPersistentCell *iCreatedPersistentCell, ListPOfCATPersistentCells &oOriginPersistentCells, int & oInfo);

  //EYL Util
  void GetCreatedImageFacesInContainer(const ListPOfCATFace &iInputFaces,const ListPOfCATPersistentBodies &iInputPersistentBodies,CATPersistentBody *iOutputPersistentBody,ListPOfCATFace &oOutputFaces);
  // ------------------------------------------------------------
  // Create PersistanceFace - do not use (mnj temp)
  // ------------------------------------------------------------
  CATPersistentFace* CreatePersistentFace(CATPersistentBody* iInputPersistentBody, CATFace* iFace);
  CATPersistentFace* CreatePersistentFace();

  // ------------------------------------------------------------
  // Create PersistanceEdge
  // ------------------------------------------------------------
  CATPersistentEdge* GetExistingOrCreatePersistentEdge(CATPersistentBody* iInputPersistentBody, CATEdge* iEdge);
  CATPersistentEdge* CreatePersistentEdge(CATPersistentBody* iInputPersistentBody, CATEdge* iEdge);
  CATPersistentEdge* CreatePersistentEdge();
  // ------------------------------------------------------------
  // Create PersistanceVertex
  // ------------------------------------------------------------
  CATPersistentVertex* CreatePersistentVertex(CATPersistentBody* iInputPersistentBody, CATVertex* iVertex);
  CATPersistentVertex* CreatePersistentVertex();
  //void FollowPersistentVerticesInsidePersistentBodies(ListPOfCATPersistentVertices &iPersistentVerticesToFollow);
  void AddPersistentVerticesToFollowInContainers(ListPOfCATPersistentVertices &ioPersistentVerticesToFollow,ListPOfCATPersistentBodies &iContainers);
  // ------------------------------------------------------------
  // Ask the model : optimized for time consuming
  // ------------------------------------------------------------
  CATBoolean IsBorderEdge(CATPersistentBody *iPersistentBody, CATEdge * ipEdge);

  void GetExpectedCellsForReporting(CATPersistentBody * iPersistentBody,
                                    CATLISTP(CATCell) & ioReportingCells);

  CATCellHashTable * GetExpectedCellsForReporting(CATPersistentBody *  iPersistentBody);

  // --------------------
  // Run a TopOperator
  // --------------------

  //Signature 1
  HRESULT RunTopOperator(CATTopOperator *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATPersistentBody*& oResultPersistentBody,CATlsoPersistentContext *iFatherContext, CATTopJournalSpy *iJournalSpy=NULL,CATBoolean iGetTypeFromJournal=FALSE,CATBoolean iUseCellTracker=FALSE,CATBoolean iRethrowError=FALSE, CATBoolean iCreateManifolds=FALSE);
  
  //Signature 2
  CATPersistentBody* RunTopOperator(CATTopOperator *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,CATlsoPersistentContext *iFatherContext,
    CATTopJournalSpy *iJournalSpy=NULL,CATBoolean iGetTypeFromJournal=FALSE,CATBoolean iUseCellTracker=FALSE, CATBoolean iCreateManifolds=FALSE);
  
  //Signature 3
  HRESULT RunTopOperator(CATTopMultiResult *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATLISTP(CATPersistentBody) &oListOfOperatorResultPersistentBodies,CATlsoPersistentContext *iFatherContext, CATTopJournalSpy *iJournalSpy, CATBoolean iCreateManifolds=FALSE);

  //Signature 4
  HRESULT RunTopOperator(CATIPGMTopOperator *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATPersistentBody*& oResultPersistentBody,CATlsoPersistentContext *iFatherContext, CATTopJournalSpy *iJournalSpy=NULL,CATBoolean iGetTypeFromJournal=FALSE,CATBoolean iRethrowError=FALSE, CATBoolean iCreateManifolds=FALSE);

  //Signature 5
  HRESULT RunTopOperator(CATICGMTopOperator *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATPersistentBody*& oResultPersistentBody,CATlsoPersistentContext *iFatherContext, CATTopJournalSpy *iJournalSpy=NULL,CATBoolean iGetTypeFromJournal=FALSE,CATBoolean iRethrowError=FALSE, CATBoolean iCreateManifolds=FALSE);

  // Some old boolean operators need to be call with GetResult(CATCGMJournalList * iJournal)
  /* HRESULT RunTopOperatorWithGetResultAndJournal(CATTopOperator              * iTopOpToBeRun,
                                                CATLISTP(CATPersistentBody) & iListOfOperatorInputPersistentBodies,
                                                CATPersistentBody          *& oResultPersistentBody,
                                                CATTopJournalSpy            * iJournalSpy=NULL);*/

  HRESULT RunTopOperatorWithoutCreatePersistentBody(CATTopOperator            * iTopOpToBeRun,      // for operator with result body
                                                     CATBody                 *& oResultBody,
                                                     CATlsoPersistentContext  * iFatherContext,
                                                     CATBoolean                 iLiveMode=FALSE, // set TRUE to have liveResult
                                                     CATBoolean                 iThrowIfError=FALSE);   

  //static HRESULT RunTopOperatorWithoutCreatePersistentBodyStatic(CATTopOperator * iTopOpToBeRun, // for operator with result body
  //                                    CATBody       *& oResultBody,
  //                                    CATlsoPersistentContext     *iFatherContext,
  //                                    const CATBoolean       iThrowIfError=FALSE,
  //                                    const CATBoolean  iResultBodyExpected=TRUE);

  //HRESULT RunTopOperatorWithoutResult(CATTopOperator * iTopOpToBeRun,
  //                                    CATlsoPersistentContext     *iFatherContext,
  //                                    CATBoolean       iThrowIfError=FALSE);  // for operator without result body : like BodyChecker

  HRESULT RunTopOperatorRethrowingError(CATTopOperator *iTopOpToBeRun, const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATPersistentBody*& oResultPersistentBody,CATlsoPersistentContext *iFatherContext, CATTopJournalSpy *iJournalSpy=NULL, CATBoolean iGetTypeFromJournal=FALSE, CATBoolean iCreateManifolds=FALSE);
  HRESULT RunTopOperatorRethrowingError(CATIPGMTopOperator           * iCATIPGMOpToBeRun, 
                                        const CATLISTP(CATPersistentBody)  & iListOfOperatorInputPersistentBodies,
                                        CATPersistentBody           *& oResultPersistentBody,
                                        CATlsoPersistentContext *iFatherContext,
                                        CATTopJournalSpy             * iJournalSpy=NULL,
                                        CATBoolean                     iGetTypeFromJournal=FALSE,
                                        CATBoolean                     iCreateManifolds=FALSE);
  



  // ------------------------------------------------------------------------
  // RunSameInfraOperator
  // ------------------------------------------------------------------------
  HRESULT RunSameInfraOperator(CATPersistentOperator * iTopOpToBeRun,CATPersistentBody *& oResultPersistentBody,CATlsoPersistentContext *iFatherContext,CATBoolean iRethrowError=FALSE);

  // --------------------
  // FillCGMJournal
  // --------------------
  //EYL Sep 2011 :
  //NoCopyInputBodies : spécifie si les Bodies doivent pris en mode NoCopy (0=Copy,1=NoCopy). Si non spécifiés, ils sont tous vu en mode Copy
  HRESULT FillCGMJournal(CATPersistentBody* iResultPersistentBody, CATCGMJournalList &oCGMJournalList, 
    const CATLISTP(CATPersistentBody)* iListInputPersistentBodies = NULL,CATListOfInt *NoCopyInputBodies=NULL,CATBoolean iReportCreationOrders=FALSE);
  
  virtual CATPersistentCellInfra * GetAsPersistentInfra() const;
  virtual CATGMLiveInfra         * GetAsGMLiveInfra()     const;

  virtual HRESULT CreateManifolds(CATPersistentBody             *& ioResultPersistentBody, 
                                  CATCGMJournalList             *  ioLiveJournal,
                                  CATlsoPersistentContext       *  iFatherContext,
                                  ListPOfCATDeclarativeManifold *  ioNotUpToDateDeclarativeManifold,
                                  ListPOfCATDeclarativeManifold *  ioNotUpToDateDeclarativeManifoldParent = NULL,
                                  CATLISTP(CATPersistentBody)   *  iLocalInputPersistentBodies=NULL,
                                  ListPOfCATLiveBody            *  ipLivificationInputLiveBodyList = NULL,
                                  CATMathTransformation         *  ipFulldomainMoveTranformation = NULL,
                                  CATBoolean                       iIsLastRun = FALSE,
                                  CATBoolean                       iCalledByRedoFillet = FALSE,
                                  CATLiveBody                   *  iBodyDuplicated=NULL,
                                  CATCGMJournalList             *  ipFullDomainMoveJournal = NULL,
                                  ListPOfCATDeclarativeManifoldAgent * iOptionalDMAgents=NULL,
                                  CATBoolean                       iSmartContext = FALSE,
                                  CATCGMHashTableWithAssoc      *  iSmartFacesOnInputBodies = NULL,
                                  CATBoolean                       iAssembleContext = FALSE);

  virtual HRESULT CreateManifolds(CATPersistentBody *& ioResultPersistentBody, CATCGMJournalList *ioLiveJournal,CATlsoPersistentContext       *  iFatherContext);
  
  virtual HRESULT CreateManifolds(CATPersistentBody *& ioResultPersistentBodyla, CATCGMJournalList * ioLiveJournal,CATlsoPersistentContext *  iFatherContext,ListPOfCATPersistentBodies &iInputPersistentBodies);

  // Method for manifoldInfra=1 and for DRepDependencyUpdater
  void CreateJournalOfCellsFromJournalOfCellManifolds(CATCGMJournalList &iJournalOfCellManifolds, 
                                                      CATCGMJournalList &ioJournalOfCells);
 
  //EYL :12/11 Code temporaire pour suplenter les appels au ThreadContext
  void SetRepresentationOfPersistentCellInContainerFromList(CATPersistentCell *iPersistentCell, CATPersistentBody *iContainer, 
    ListPOfCATCell &iCells, CATListOfInt &iOrientations, CATListOfInt* iTypes);
 
  // --------------------
  // No doc today
  // --------------------
  CATPersistentBody * CreateNewPersistentBodyWithDomainList(const ListPOfCATDomain      & iDomainList,
    ListPOfCATPersistentBodies           * ipPersistentBodiesList,
    CATlsoPersistentContext              * iFatherContext,
    CATBoolean                             iManageManifold=FALSE,
    CATBoolean                             iUSELESS_FreezeBody=TRUE);

  CATPersistentBody *CreatePersistentBodyFromTransfo(CATPersistentBody *iInputPersistentBody, CATMathTransformation &ioTransformation,
    int iDuplicateModeValue, CATCGMJournalList *& ioJournal, CATBoolean iForceTypeReport=FALSE);
  
  //if iBorderPersistentEdgesCreation == 0, Create BorderEdges and vertices with mode 0  []-Create->[E_];[]-Create->[V_]
  //if iBorderPersistentEdgesCreation == 1, [Bording Faces]-Create->[E_];[BordingEdges]-Create->[V_]
  CATPersistentBody *CreateExtractPersistentBody(CATPersistentBody &iPersistentBody,
                                                 const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                                 CATBoolean iBorderPersistentEdgesCreation = FALSE,
                                                 CATBoolean iRunCreateManifolds = FALSE);

  //Create BorderEdges and vertices with mode 2 [Bording deleted Faces]-Create->[E_];[Bording deleted Edges]-Create->[V_]
  CATPersistentBody *CreateExtractPersistentBody(CATPersistentBody &iPersistentBody,
                                                 const ListPOfCATCell    & iCells,
                                                 const CATListOfInt      * iOrients=NULL,
                                                 CATBoolean iRunCreateManifolds = FALSE);


  
    enum CreateUserPEdgesMode
  {
    CreateNoUserPEdges = 0,
    CreateUserBorderPEdges = 1,
    CreateUserAllPEdges = 2
  };
    
  //Create extractPBody and put user PEdges on input and output 
  //iCreateUserPEdgesMode == CreateNoUserPEdges : Do nothing
  //iCreateUserPEdgesMode == CreateUserBorderPEdges : create user pedges only on border future edges in result body
  //iCreateUserPEdgesMode == CreateUserAllPEdges : create user pedges on all future edges in result body
  CATPersistentBody *CreateExtractPersistentBodyWithUserPersistentEdgesOnBothBodies(CATPersistentBody &iPersistentBody,
                                                                                    const ListPOfCATCell    & iCells,
                                                                                    CreateUserPEdgesMode      iCreateUserPEdgesMode,
                                                                                    ListPOfCATPersistentEdges &oUserPEdges,
                                                                                    CATBoolean iRunCreateManifolds = FALSE);

  
  // iNewBordingCellsCreationOrderMode : how the new edges an vertices orders are 
  //iNewBordingCellsCreationOrderMode = 0 : []-Create->[E_];[]-Create->[V_]
  //iNewBordingCellsCreationOrderMode = 1 : [Bording Faces]-Create->[E_];[BordingEdges]-Create->[V_]
  //iNewBordingCellsCreationOrderMode = 2 : [Bording deleted Faces]-Create->[E_];[Bording deleted Edges]-Create->[V_]
  CATPersistentBody *CreateExtractPersistentBody(CATPersistentBody &iPersistentBody,
                                                 const CATLISTP(CATPersistentFace) & iListOfPersistentFaces,
                                                 int                          iNewBordingCellsCreationOrderMode,
                                                 CATBoolean iRunCreateManifolds = FALSE);

  CATPersistentBody *CreateExtractPersistentBody(CATPersistentBody &iPersistentBody, const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges);

  //Method without creation of PersistentBody. Tu use wisely
  CATBody *CreateExtractBody(CATPersistentBody &iPersistentBody,
                             const ListPOfCATCell    & iCells,
                             CATCGMJournalList					 &oJournal);


  CATPersistentBody *CreatePersistentExtractBodyFromCommonDomain(CATPersistentBody &iPersistentBody, 
    CATLISTP(CATPersistentFace) & iListOfPersistentFaces, CATBoolean iBorderPersistentEdgesCreation = FALSE);
  void ReportCreation(ListPOfCATPersistentCells &iOriginCells, CATPersistentCell *iCreatedCell, int *iInfoNumber=NULL);
  void ReportModification(ListPOfCATPersistentCells &iOriginCells, CATPersistentCell *iCreatedCell, int *iInfoNumber=NULL);

  virtual CATPersistentCellInfra* CloneWithSamePersistentCellFactory();

  // pour edition de la reference : PROTO  (for TransformFaceEngine) - VB7 - 18082011
  virtual void GetListPatternFollowers(int iNumOperatorID, ListPOfCATGMLiveContextualFeatureFollowers & oLiveContextualFeatureFollowers);

  // ----------------------------------
  // RemoveBody
  // Use it to Remove a PersistentBody, it does not remove the CATBody from the GeoFactory
  // ----------------------------------
  virtual void RemoveBody(CATPersistentBody* &ioPersistentBody,CATBoolean iRemoveCATBody=TRUE);
  void RemoveBodies(ListPOfCATPersistentBodies & ioPersistentBodyList, CATBoolean iRemoveCATBody=TRUE);
  HRESULT RemoveAllCellViews(CATPersistentBody * iPersistentBody);
  // ----------------------------------
  // IsAnInputBody
  // Return TRUE if the iPersistentBody is an input.
  // ----------------------------------
  virtual CATBoolean IsAnInputBody(CATPersistentBody* iPersistentBody);

  // ----------------------------------
  // IsAnInputBody
  // Return TRUE if the iBody is an input.
  // ----------------------------------
  virtual CATBoolean IsAnInputBody(CATBody* iBody);
  
  // ---------------------------------------
  // Utilitaires
  // ---------------------------------------
  //CATGeoFactory & GetFactory(short iImpliciteFactory=1) const;
  //INLINE CATSoftwareConfiguration * GetSoftwareConfiguration();

  void AttachPersistentBodyToCellInformer(CATPersistentBody *iPersistentBody,CATGMLivePersistentCellInformer &ioPersistentCellInformer);

  // If creation orders are to be reported in PersistentCellJournal, use CreatePersistentBodyFromJournalReportingCreationOrders
  //CATListOfInt &iCopyInputModes : Indicates, for each InputBody, if it is, in the journal, in copy mode( value 1), no copy mode (value 0) or unknown (value -1)
  // Value -1 is to avoid, because in this case, the time of computation will be increased.
  // For any question about that, please asl EYL
  CATPersistentBody * CreatePersistentBodyFromJournal(CATBody *iResultBody, const CATLISTP(CATPersistentBody) &iListInputPersistentBodies,CATListOfInt &iCopyInputModes,
    CATCGMJournalList &iJournal, CATTopJournalSpy &iUSELESS_JournalSpy, CATBoolean iUSELESS_FreezeBody = TRUE, CATBoolean iGetTypeFromJournal = FALSE,CATBoolean iUSELESS_CreatePersistentCellsNotInInputBodies=TRUE);
  CATPersistentBody * CreatePersistentBodyFromJournal(CATBody *iResultBody, const CATLISTP(CATPersistentBody) &iListInputPersistentBodies,CATListOfInt &iCopyInputModes,
    CATCGMJournalList &iJournal, CATBoolean iUSELESS_FreezeBody = TRUE, CATBoolean iUSELESS_GetTypeFromJournal = FALSE,CATBoolean iUSELESS_CreatePersistentCellsNotInInputBodies=TRUE);

  //Only for a convergence time, destroy this method after
  CATPersistentBody * DONOTUSE_CreatePersistentBodyFromJournalWITHOUTFREEZINGBODY(CATBody *iResultBody, const CATLISTP(CATPersistentBody) &iListInputPersistentBodies,CATListOfInt &iCopyInputModes,
    CATCGMJournalList &iJournal);

  CATPersistentBody * CreatePersistentBodyFromEmptyJournal(CATBody *iResultBody, CATPersistentBody *iInputPersistentBody);
  CATPersistentBody * CreatePersistentBodyFromEmptyJournal(CATBody *iResultBody, const CATLISTP(CATPersistentBody) &iListInputPersistentBodies);

  CATPersistentBody * CreatePersistentBodyFromJournalReportingCreationOrders(const CATLISTP(CATPersistentBody) &iListOfInputPersistentBodies,
                                                                                  CATListOfInt &iCopyInputModes,
                                                                                  CATCGMJournalList &iJournal,
                                                                                  CATBody &iResultBody,
                                                                                  CATBoolean iGetTypeFromJournal=FALSE);

  CATPersistentBody * CreatePersistentBodyForFastExtract(CATBody                           * iResultBody,
                                                         const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                                         const ListPOfCATPersistentCells   & iListOfPersistentCellPerBody,
                                                         const CATListOfInt                & iNumberOfPCellPerBody,
                                                         const CATListOfInt                & iCopyInputModes,
                                                         const CATCGMHashTableWithAssoc    * iCellToBeCreatedHT = NULL,
                                                         const ListPOfCATPersistentCells   * iListOfUserPersistentCells = NULL,
                                                         const ListPOfCATCell              * iListOfUsercells = NULL);



  // Replace persistentCells of some cells of ioPersistentBodyToModify according to new orders from iJournalInputPersistentBodies to ioPersistentBodyToModify.
  // iNewOrders can be a journal of cells or a journal of CellManifolds (but not a mixed one)
  // It's not a complete journal : it contain only order for cells to modify
  void RematchPersistentCellsInPersistentBody(CATPersistentBody *ioPersistentBodyToModify, CATCGMJournalList &iNewOrders, const ListPOfCATPersistentBodies &iJournalInputPersistentBodies);

  CATPersistentBody * CreatePersistentBodyFromJournal_V3(CATBody *iResultBody,const CATLISTP(CATPersistentBody) &iListInputPersistentBodies, CATListOfInt &iCopyInputModes, CATCGMJournalList &iJournal,CATBoolean iDONOTUSETODELETE_FreezeBody=TRUE);

  CATPersistentBody * DuplicatePersistentBody(CATPersistentBody* iInputPersistentBody);
  CATPersistentBody * CreatePersistentBodyWithNoInfo(CATBody *iResultBody, CATBoolean iUSELESS_FreezeBody = TRUE);
  CATPersistentBody * CreatePersistentBodyWithMinimalJournal(CATBody *iResultBody, ListPOfCATPersistentBodies &iInputPBodies);
  
  CATPersistentCellsBasedCellManifoldsManager* CreateCATPersistentCellsBasedCellManifoldsManager(ListPOfCATBody &iInputBodies,CATBody *iOutputBody);

  virtual CATDeclarativeOperatorsBridge * CreateDeclarativeOperatorsBridge();

  void DeleteFiliationOrders(ListPOfCATCell & iParentCells, CATPersistentBody *iParentPersistentBody, CATCell *iChildCell, CATPersistentBody *iChildPersistentBody);


  /** 
  *  Simulate CGMWarning if Warning_On and Flush Result.
  */
  // virtual CATCGMInputError * las();

public:
  INLINE CATPersistentCellsJournal * GetPersistentCellJournal() const; // ZUT : Methode temporaire pour code de test non actif
  const CATAutoBaseThreadContext& GetThreadContext() const;           // ZUT : Methode rendue temporairement public pour code de test non actif
  
  void SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);
  CATVariationalPatternParameters * GetVariationalPatternParameters();

  void GetInputLiveBodies(CATLISTP(CATLiveBody) & oInputLiveBodies);

  CATPersistentCellCellFollower* CreatePersistentCellCellFollower(ListPOfCATPersistentBodies &iInputPersistentBodies, CATPersistentBody &iOutputPersistentBody);
  

  //VB7
  INLINE CATlsoDataCache * GetDataCache(ListPOfCATBody & iBodyList);
  INLINE CATlsoDataCache * GetDataCache();
  
  void RemoveAllPersistentBodiesExceptList(ListPOfCATPersistentBodies &iPersistentBodiesToKeep);

  CATlsoAgentInputDataCarrier * GetAgentInputDataCarrier(CATPersistentExtTopOperator * iOpe, CATBoolean iWithCreateAndUpdate=TRUE);

  INLINE void GetAgentInputDataCarrierList(ListPOfCATlsoAgentInputDataCarrier & oAgentInputDataCarrierList);

  void AppendAgentInputDataCarrierList(CATlsoAgentInputDataCarrier * iAgentInputDataCarrier);

  void CleanInputDataCarrier(const CATPersistentExtTopOperator * iOpe);

  void CleanCellRepInContainer(CATPersistentCell *iPersistentCellToClean,CATCell *iCellToClean,CATPersistentBody *iContainer);

  void CleanInputPersistentBodyList(CATPersistentBody * iPersistentBody);
  
  //A passer en protected une fois convergé
  CATPersistentEdge* CreateUserPersistentEdge(CATPersistentBody* iInputPersistentBody, CATEdge* iEdge);
  CATPersistentVertex* CreateUserPersistentVertex(CATPersistentBody* iInputPersistentBody, CATVertex* iVertex);
  CATPersistentEdge* GetUserPersistentEdgeInContainer(CATEdge* iEdge,CATPersistentBody* iContainer);
  CATPersistentVertex* GetUserPersistentVertexInContainer(CATVertex* iVertex,CATPersistentBody* iContainer);


  void GetUserPersistentEdgesInContainer(ListPOfCATEdge &iEdges,CATPersistentBody* iContainer,ListPOfCATPersistentEdges &oUserPEdges);

  //--------------VB7--To carry ManifoldParameters-------// 
  //Only give changed parameters
  void GetParameterList(CATDeclarativeManifold * iDM, int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList);

  //Only give changed parameters
  void GetParameterList(CATCellManifoldGroup * iCMG, int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList);

  //Only give changed parameters
  void GetParameterList(int iNumOperatorId, ListPOfCATManifoldBaseParameter & oParameterList);
  
  void SetParameterList(ListPOfCATManifoldBaseParameter & iParameterList, int iNumOperatorId);

  void AppendParameter(CATManifoldBaseParameter * iParameter);
 
  void UpdateParameterWithSecondaryDM(CATDeclarativeManifold * iDM, CATDeclarativeManifold * iSecondaryDM);

  void CleanParameterSecondaryDM(CATDeclarativeManifold * iDM);

  CATDeclarativeManifold * GetParameterSecondaryDM(CATDeclarativeManifold * iDM);

  CATGMSpecInfra * GetSpecInfra();

  //VB7 W9 2021
  void StreamParameters( CATCGMStream & oStr, int iNumOpeId );
  void UnStreamParameters( CATCGMStream & iStr, int iNumOpeId, CATLiveBody* iLiveBody );

  virtual CATBoolean UseRematchProcess();

  void ResetAgentInputDataCarrier(CATPersistentExtTopOperator * iOpe);

  CATLiveBody * GetLiveBody(const CATPersistentBody * iPBody, const CATDRepExtTopOperator * iOpe=NULL);
  
  //This method create user PersistentEdges, copies of input ioPersistentEdgesToFollow (if they're not already user PEDges) in order to follow them through inner edges.
  //Also add the Union PEdge of them (for now)SetLiveBodyAllowed

  //All created PersistentEdges are added to ioPersistentEdgesToFollow
  void AddPersistentEdgesToFollowInContainers(ListPOfCATPersistentEdges &ioPersistentEdgesToFollow,ListPOfCATPersistentBodies &iContainers);  

  enum NewPCellsLevel
  {
    STEP0_INACTIVE = 0,
    STEP1_CREATEPBODIES = 1,
    STEP2_FILLCGMJOURNAL = 2,
    STEP3_USERPCELLS =3
  };
  void ActiveNewPCellLevel(NewPCellsLevel iNewPCellLevel);
  NewPCellsLevel GetNewPCellsLevel() const;

  //VB7 -- AvoidLastRun
  CATBoolean GetInvalidBodyDetected() const;
  CATLiveBodyValidity GetInvalidBodyStatus() const;
  void SetInvalidBodyDetected(CATLiveBodyValidity iValidity);
  void ResetInvalidBodyDetected();

  //VB7 LocalBuild
  void SetExpectedCellsReportingMode(CATExpectedCellsReportingMode iExpectedCellsReportingMode);
  CATExpectedCellsReportingMode GetExpectedCellsReportingMode() const;

  //======================= PRIVATE =======================================================
private:

  //------------------------------------------------------------------------------
  // Forbidden (Declared but not Defined) : Copy constructor & assignment operator
  //------------------------------------------------------------------------------
  CATPersistentCellInfra( const CATPersistentCellInfra & );            // Not Implemented
  CATPersistentCellInfra & operator=( const CATPersistentCellInfra & ); // Not Implemented

  //Main methods
  // iNewBordingCellsCreationOrderMode : how the new edges an vertices orders are 
  //iNewBordingCellsCreationOrderMode = 0 : []-Create->[E_];[]-Create->[V_]
  //iNewBordingCellsCreationOrderMode = 1 : [Bording Faces]-Create->[E_];[BordingEdges]-Create->[V_]
  //iNewBordingCellsCreationOrderMode = 2 : [Bording deleted Faces]-Create->[E_];[Bording deleted Edges]-Create->[V_]

  CATPersistentBody *CreateExtractPersistentBodyMain(CATPersistentBody*           iPersistentBody, 
                                                     const ListPOfCATCell               &iCells,                                                     
                                                     const CATListOfInt                 *iOrients,
                                                     int                          iNewBordingCellsCreationOrderMode,
                                                     CATBoolean                   iRunCreateManifolds);
  CATBody *CreateExtractBodyMain(CATPersistentBody*           iPersistentBody, 
                                 const ListPOfCATCell               &iCells,
                                 const CATListOfInt                 *iOrients,
                                 int                          iNewBordingCellsCreationOrderMode,
                                 CATCGMJournalList					 &oJournal);
  
  CATCGMJournalList *CreateCGMJournalForExtract(CATPersistentBody*           iInputPersistentBody,
                                                CATBody *                    iResultBody,
                                                int                          iNewBordingCellsCreationOrderMode,
                                                const ListPOfCATCell         &iExtractedCells);

  //iWithCreatedFaces : if false, only by modification
  //iFindAncestors : if false, find children, if true, find ancestors
  void GetHashTabOfPersistentCellsRepresentation(CATPersistentBody * iPersistentBody, 
    const CATLSOHashTable<CATPersistentCell> & iPersistentCellHT, const CATBoolean iWithCreatedCells, const CATBoolean iFindAncestors,
    CATCellHashTable & oCellHT) const;

  void GetListOfPersistentCellsRepresentation(CATPersistentBody * iPersistentBody, 
    const CATLISTP(CATPersistentCell) & iListOfPersistentCells, const CATBoolean iWithCreatedCells, const CATBoolean iFindAncestors,
    CATLISTP(CATCell) &oListOfCells);

  void GetListOfPersistentFacesRepresentation(CATPersistentBody * iPersistentBody, 
    const CATLISTP(CATPersistentFace) & iListOfPersistentFaces, const CATBoolean iWithCreatedFaces, const CATBoolean iFindAncestors,
    CATLISTP(CATFace) &oListOfFaces);
  void GetListOfPersistentFacesRepresentation(CATPersistentBody * iPersistentBody, 
    const CATLISTP(CATPersistentFace) & iListOfPersistentFaces, const CATBoolean iWithCreatedFaces, const CATBoolean iFindAncestors,
    CATFaceHashTable &oFaceHT);

  void GetListOfPersistentEdgesRepresentation(CATPersistentBody * iPersistentBody, 
    const CATLISTP(CATPersistentEdge) & iListOfPersistentEdges, const CATBoolean iWithCreatedEdges, const CATBoolean iFindAncestors,
    CATLISTP(CATEdge) &oListOfEdges,CATListOfInt *oListOfOrientation);
  
  void GetListOfPersistentVerticesRepresentation(CATPersistentBody * iPersistentBody, 
    const ListPOfCATPersistentVertices & iListOfPersistentVertices, const CATBoolean iWithCreatedVertices, const CATBoolean iFindAncestors,
    ListPOfCATVertex &oListOfVertices);

  // Private LastWarning Management
  // ----------------------------------------------------- 
  // void ReleasePermanentWarning();
  // INLINE const CATLISTP(CATCGMDiagnosis) & GetPermanentWarningList() const;

  //EYL FOR NewPCells
  void GetAllUserPersistentEdgesInContainer(const CATPersistentBody *iContainer,ListPOfCATPersistentEdges &oUserPersistentEdges) const;
  void GetAllUserPersistentVerticesInContainer(const CATPersistentBody *iContainer,ListPOfCATPersistentVertices &oUserPersistentVertices) const;
  void TransferUserPersistentCellsRepresentation_V3(const ListPOfCATPersistentBodies &iInputPersistentBodies,CATPersistentBody *iResultPersistentBody,CATCGMJournalList &iJournal);
  void GetInputBodyUserCellsAndCellsToSpy(CATPersistentBody *iInputPersistentBody,ListPOfCATCell &oInputUserCells,CATCellHashTable &oInputCellsToSpy);
  CATCellHashTable *GetOutputCellsToAnalyze(CATCGMJournalList &iJournal,CATCellHashTable &iInputCellsToFollow);
  void FillUserCellsJournalForNewCell(CATCell *iOutputCell,CATPersistentBody *iResultPersistentBody,ListPOfCATCell &iInputUserCells,
                                      CATCGMJournalList &iOperationJournal,CATCGMJournalList &ioUserCellsJournal);
  void ReportUserPCellsFromUserCellsJournal(const ListPOfCATPersistentBodies &iInputPersistentBodies,CATPersistentBody *iResultPersistentBody,CATCGMJournalList &iUserCellsJournal,CATCellHashTable &iInputCellsToKeep);

  //Modify journal for good PersistentBody Creation
  void UpdateJournalForPersistentBodyCreation(const ListPOfCATPersistentBodies &iPersistentBodies,const CATCellHashTable *iReportingOutputCells, CATCGMJournalList &ioJournal);
  //Supress Creations orders if there is already a modification one on same cell
  void UpdateJournalForOutputCellsWithTwoOrders(CATCGMJournalList &ioJournal);
  //To know PersistentCells located in two bodies of the list
  void UpdateJournalForSharedPCellsInInputPBodies(const ListPOfCATPersistentBodies &iPersistentBodies,const CATCellHashTable *iReportingOutputCells, CATCGMJournalList &ioJournal);
  //To avoid haveing a cell midified in vertex or the opposite
  void UpdateUserJournalForDimensionParadox(CATCGMJournalList &ioJournal);

  
  HRESULT FillCGMJournal_NewPCells(CATPersistentBody* iResultPersistentBody, 
                                   const ListPOfCATPersistentBodies iListInputPersistentBodies, CATListOfInt *NoCopyInputBodies, 
                                   CATCGMJournalList &oCGMJournalList);
  void FillCGMJournalForOutputCell(CATCell *iOuputCell, CATPersistentBody *iResultPersistentBody, 
                                   const ListPOfCATPersistentBodies iListInputPersistentBodies,
                                   CATCGMJournalList &ioCGMJournalList,CATCellHashTable *ioInputCopyCells);


//======================= PROTECTED =======================================================
protected:

  //VB7 -W12 2015
  void RemoveBodyInDataCache(CATPersistentBody * iInputPBody);

  // Enum for _AllPersistentBodyHashTable
  enum {
    INPUT_PERSISTENTBODY = 0,
    INPUT_NEURAL_PERSISTENTBODY,
    PROTECTED_PERSISTENTBODY,
    CREATED_PERSISTENTBODY,
  };
  
  //Main method
  HRESULT RunTopOperator(CATTopOperator *iTopOpToBeRun, 
    const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATLISTP(CATPersistentBody) &oListOfOperatorOutputPersistentBodies,
    CATlsoPersistentContext     *iFatherContext,
    CATTopJournalSpy *iUSELESS_JournalSpy=NULL,
    CATBoolean iUSELESS_GetTypeFromJournal=FALSE,CATBoolean iUSELESS_UseCellTracker=FALSE,
    CATBoolean iRethrowError=FALSE,
    CATBoolean iCreateManifolds=FALSE);

  // void TransferLiveBodyAccessRights(CATTopOperator * iSonOpe);
  void TransferPersistentEdgeRepresentation(const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,
    CATPersistentBody &iResultPersistentBody,CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy);
  void TransferPersistentEdgeRepresentation(CATPersistentBody &iFromBody, CATPersistentBody &iToBody,CATCGMJournalList *iJournal, CATTopJournalSpy &iJournalSpy);
  void TransferPersistentVertexRepresentation(CATPersistentBody &iFromBody, CATPersistentBody &iToBody,CATCGMJournalList *iJournal,
                                                             CATTopJournalSpy &iJournalSpy);
  void TransferPersistentVertexRepresentation(const ListPOfCATPersistentBodies &iSrcPersistentBodies, CATPersistentBody &iTargetPersistentBody,CATCGMJournalList *iJournal, 
                                                             CATTopJournalSpy &iJournalSpy,CATListOfInt &iCopyInputModes);

  CATPersistentBody* CreatePersistentBodyFromOperatorResult(const CATLISTP(CATPersistentBody) &iListOfOperatorInputPersistentBodies,CATListOfInt &iCopyInputModes,
    CATCGMJournalList &iJournal, CATBody &iResultBody, CATCGMCellTracker *iUSELESS_CellTracker, CATTopJournalSpy *iUSELESS_JournalSpy, CATBoolean iGetTypeFromJournal=FALSE);

  void AddToCreatedPersistentBodiesList(CATPersistentBody * iPersistentBody);

  CATPersistentCellFactory & GetPersistentCellFactory();
  void DumpAllPersistentBodyHashTable();
  virtual void RemovePCellOfInternalDatas(CATPersistentCell *iPersistentCell);


  // 6 SubMethodes for CreatePersistentBodyFromJournal_V3
  // -----------------------------------------------------
  void CreatePersistentCellFromJournalOnly(CATCGMJournalList                 & iJournal,
                                           const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                           CATPersistentBody                 & iResultPersistentBody,
                                           CATCellHashTable                   & ioReportingCellHashTable);
  void CreateOrUpdatePersistentCellFromModification(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                                    CATPersistentBody       & iResultPersistentBody,
                                                    ListPOfCATCell          & iAfterCellList,
                                                    ListPOfCATCell          & iBeforeCellList,
                                                    const CATCGMJournalInfo * ipInfo,
                                                    CATCellHashTable         & ioReportingCellHashTable);
  void CreatePersistentCellFromCreation(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                        CATPersistentBody       & iResultPersistentBody,
                                        ListPOfCATCell          & iAfterCellList,
                                        ListPOfCATCell          & iBeforeCellList,
                                        const CATCGMJournalInfo * ipInfo,
                                        CATCellHashTable         & ioReportingCellHashTable);
  void CreatePersistentCellFromSubdivision(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                           CATPersistentBody       & iResultPersistentBody,
                                           ListPOfCATCell          & iAfterCellList,
                                           ListPOfCATCell          & iBeforeCellList,
                                           const CATCGMJournalInfo * ipInfo,
                                           CATCellHashTable         & ioReportingCellHashTable);
  void CreatePersistentCellFromAbsorption(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                          CATPersistentBody       & iResultPersistentBody,
                                          ListPOfCATCell          & iAfterCellList,
                                          ListPOfCATCell          & iBeforeCellList,
                                          const CATCGMJournalInfo * ipInfo,
                                          CATCellHashTable         & ioReportingCellHashTable);

  void FindPCellListFromOneCell(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                CATCell                           * ipBeforeCell,
                                CATLISTP(CATPersistentCell)       & oBeforePCellList);
  void FindJournalPCellListFromOneCell(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                       CATCell                           * ipBeforeCell,
                                       CATLISTP(CATPersistentCell)       & oBeforePCellList);

  void FindPCellListFromCellList(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                 const ListPOfCATCell              & iBeforeCellList,
                                 CATLISTP(CATPersistentCell)       & oBeforePCellList);
  void FindJournalPCellListFromCellList(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                        const ListPOfCATCell              & iBeforeCellList,
                                        CATLISTP(CATPersistentCell)       & oBeforePCellList);

  void CreateOnePersistentCellAndOnePCellJournalCreationItem(CATCell                     * ipAfterCell,
                                                             CATLISTP(CATPersistentCell) & iBeforePCellList,
                                                             const CATCGMJournalInfo     * ipInfo,
                                                             CATPersistentBody           & iResultPersistentBody,
                                                             CATCellHashTable            & ioReportingCellHashTable);
  void CreateOnePersistentCellAndOnePCellJournalModificationItem(CATCell                     * ipAfterCell,
                                                                 CATLISTP(CATPersistentCell) & iBeforePCellList,
                                                                 const CATCGMJournalInfo     * ipInfo,
                                                                 CATPersistentBody           & iResultPersistentBody,
                                                                 CATCellHashTable            & ioReportingCellHashTable);

  void CloneViewOfUntouchedPersitentCellFromInputBodies(const CATLISTP(CATPersistentBody) & iListInputPersistentBodies,
                                                        CATPersistentBody                 & iResultPersistentBody,
                                                        CATCellHashTable                  & ioReportingCellHashTable);

  CATPersistentFace *CreateJournalPersistentFace(CATPersistentBody* iInputPersistentBody, CATFace* iFace);
  CATPersistentEdge* CreateJournalPersistentEdge(CATPersistentBody* iInputPersistentBody, CATEdge* iEdge);
  CATPersistentVertex* CreateJournalPersistentVertex(CATPersistentBody* iInputPersistentBody, CATVertex* iVertex);
  
  void GetCommonPersistentCells(const ListPOfCATPersistentBodies &iPersistentBodies,ListPOfCATPersistentCells &oCommonPersistentCells)const;
  //Erase Rep of PersistentCells linked to iCellsToClean in iResultPersistentBody, and delete them if there are empty after that
  void CleanBadPersistentCells(CATPersistentBody *iresultPersistentBody, CATLISTP(CATGeometry) &iCreatedGeometries);

  // -------------------------------------------------------------------
  // Internal Data
  // -------------------------------------------------------------------
  // CATGeoFactory                   & _GeoFactory;
  CATPersistentCellFactory        * _PersistentCellFactory;
  CATBoolean                        _PersistentCellFactoryOwner;
  const CATAutoBaseThreadContext  * _ThreadContext;
  CATLISTP(CATPersistentBody)       _InputPersistentBodies;
  CATCGMHashTableWithAssoc          _AllPersistentBodyHashTable;
  int                               _int_INPUT_PERSISTENTBODY;
  int                               _int_INPUT_NEURAL_PERSISTENTBODY;
  int                               _int_PROTECTED_PERSISTENTBODY;
  int                               _int_CREATED_PERSISTENTBODY;
  CATPersistentCellsJournal       * _PersistentCellJournal;
  CATBoolean                        _UserCreatedPersistentEdges;
  ListPOfCATPersistentEdges         _ListOfUserCreatedPersistentEdges;
  ListPOfCATPersistentVertices      _ListOfUserCreatedPersistentVertices;
  CATBoolean                        _UserCreatedPersistentVertices;
  CATVariationalPatternParameters * _VariationalPatternParameters;
  //CATBoolean                        _LiveBodyAllowed;  
  //CATTopOpInError                 * _LastWarning; // contains warning list
  //CATLISTP(CATCGMDiagnosis)         _PermanentWarningList;
  //CATTopOpInError                 * _LastError;
  //LastErrorLevel                    _LastErrorCriticality;
  //CATUnicodeString                  _MainErrorMsgId;
  //CATPGMDRepBehavior              * _DRepBehavior;  

  //VB7 -- cache
  CATlsoDataCache                 * _DataCache;

  //VB7 -- To carry ManifoldParameters
  CATGMSpecInfra                  * _GMSpecInfra;

  ListPOfCATlsoAgentInputDataCarrier _AgentInputDataCarrierList;
  NewPCellsLevel _NewPCell_Level;

  //VB7 -- Avoid LastRun
  CATBoolean                         _InvalidBodyDetected;
  CATLiveBodyValidity                _InvalidBodyStatus;


  //VB7 - LocalBuild : to avoid Border Persistent Edge
  CATExpectedCellsReportingMode      _ExpectedCellsReportingMode;
};

INLINE void CATPersistentCellInfra::GetListOfInputPersistentBodies(CATLISTP(CATPersistentBody) &oInputPersistentBodies)
{
  oInputPersistentBodies = _InputPersistentBodies;
}

INLINE CATPersistentCellsJournal * CATPersistentCellInfra::GetPersistentCellJournal() const {
  return _PersistentCellJournal; }

INLINE CATlsoDataCache * CATPersistentCellInfra::GetDataCache(ListPOfCATBody & iBodyList) {
  if(!_DataCache)
    _DataCache = new CATlsoDataCache(iBodyList);
  else
    _DataCache->UpdateBodyList(iBodyList);
  return _DataCache; }

INLINE CATlsoDataCache * CATPersistentCellInfra::GetDataCache() {
  return _DataCache; }

//INLINE CATSoftwareConfiguration * CATPersistentCellInfra::GetSoftwareConfiguration()
//{
//  return GetPersistentCellFactory().GetSoftwareConfiguration();
//}

INLINE void CATPersistentCellInfra::GetAgentInputDataCarrierList(ListPOfCATlsoAgentInputDataCarrier & oAgentInputDataCarrierList) {
  oAgentInputDataCarrierList = _AgentInputDataCarrierList; }

#endif
