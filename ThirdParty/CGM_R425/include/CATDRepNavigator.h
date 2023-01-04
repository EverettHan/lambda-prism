#ifndef CATDRepNavigator_H
#define CATDRepNavigator_H

#include "CATPersistentCell.h"
#include "CATNavigatorBase.h"

#include "CATTopDefine.h"
#include "CATCollecRoot.h"
#include "CATListOfShort.h"
#include "CATSysDeletePtrList.h"

#include "ListPOfCATCellManifoldPatternNavigator.h"
#include "ListPOfCATCellManifoldOffsetNavigator.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "ListPOfCATManifoldRibbonNavigator.h"
#include "CATPatternDefine.h"
#include "CATDMUpToDateStatusDefine.h" 
#include "CATCellHashTable.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATIPGMDRepGroup.h"
#include "ListPOfCATCellManifoldGroup.h"
#include "CATListOfULONG32.h"
#include "ListPOfCATManifold.h"
#include "CATDRepOptions.h"
#include "ListPOfCATGMLiveShapeButtonNavigator.h"
#include "ListPOfCATGMLiveShapeButtonNavigatorInterface.h"
#include "ListPOfCATCellManifoldGroupLayer.h"
#include "ListPOfCATCellManifoldExtrusionNavigator.h"
#include "ListPOfCATCellManifoldLogoNavigator.h"
#include "ListPOfCATAdvancedStampNavigator.h"
#include "ListPOfCATManifoldParamId.h"

class CATLiveBody;
class CATFace;
class CATEdge;
class CATVertex;
class CATJointFillet;
class CATSurface;
class CATLISTP(CATSurface);
class CATMathPoint;
class CATHVertex;
class CATCellManifoldGroup;
class CATMathTransfromation;
class CATCellManifoldPatternNavigator;
class CATCellManifoldOffsetNavigator;
class CATCellManifoldExtrusionNavigator;
class CATDeclarativeManifold;
class CATTechnologicalLayer;
class CATCGMHashTableWithAssoc;
class CATLiveBodyCGM;
class CATPGMDRepBehavior;
class CATCellManifoldGroupLayer;
class CATEdgeHashTable;
class CATCellManifoldHashTable;

//Update DRepOffset for thickness edition - VB7 - 28 august 2014
//#define UPDATEOFFSET

// ----------------------------------------------------------------------------------------------
// DRepNavigator Interface creation method. Visible for the application
// ----------------------------------------------------------------------------------------------
ExportedByPersistentCell CATDRepNavigatorInterface* CATCreateDRepNavigatorInterface(CATSoftwareConfiguration* iSoftConf, CATBody* iBody); 


class ExportedByPersistentCell CATDRepNavigator : public CATNavigatorBase
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATDRepNavigator(const CATTopData &iData, CATLiveBody* iLiveBody); 

  // Destructor
  virtual ~CATDRepNavigator();

  // ----------------------------------------------------------------------------------------------
  // Read typed DRep Navigators, they must not be deleted after use.
  // ----------------------------------------------------------------------------------------------
  virtual HRESULT GetCellManifoldPatternNavigatorsItf(ListPOfCATCellManifoldPatternNavigatorInterface& oPatternNavigators);
  virtual HRESULT GetManifoldRibbonNavigatorsItf(ListPOfCATManifoldRibbonNavigatorInterface& oRibbonNavigators);
  // new
  virtual HRESULT GetDraftManifoldNavigatorsItf(ListPOfCATManifoldRibbonNavigatorInterface& oDraftNavigators);
  virtual HRESULT GetSpecificManifoldRibbonNavigatorsItf(CATCellManifold * iCMToScan, ListPOfCATManifoldRibbonNavigatorInterface& oRibbonNavigators);
  virtual HRESULT GetButtonManifoldNavigatorsItf(ListPOfCATGMLiveShapeButtonNavigatorInterface& oButtonNavigators);

  // ----------------------------------------------------------------------------------------------
  // Read typed DRepGroups, they must not be deleted after use. Release() is already called on them when DRepNavigator is deleted.
  // Use AddRef if you need to keep a valid pointer on them. 
  // @param iTechnicalGroupLayer is Mandatory
  // @param oPGMDRepGroupList is cleaned before processing
  // ----------------------------------------------------------------------------------------------
  virtual HRESULT GetPGMDRepGroupsFromCellManifold(CATCellManifold * iCellManifoldToScan, const CATTechnologicalLayer &iTechnicalGrouplLayer, CATLISTP(CATIPGMDRepGroup) &oPGMDRepGroupList);
  virtual HRESULT GetAllPGMDRepGroups(const CATTechnologicalLayer &iTechnicalGrouplLayer, CATLISTP(CATIPGMDRepGroup) &oPGMDRepGroupList);

  // ==============================================================================================
  // CGM internal use only
  // ==============================================================================================
  HRESULT GetCellManifoldPatternNavigators   (ListPOfCATCellManifoldPatternNavigator    & oPatternNavigators);
  HRESULT GetCellManifoldExtrusionNavigators (ListPOfCATCellManifoldExtrusionNavigator  & oExtrusionNavigators);
  HRESULT GetManifoldRibbonNavigators        (ListPOfCATManifoldRibbonNavigator         & oRibbonNavigators);  
  // New - draft
  const ListPOfCATManifoldRibbonNavigator & GetDraftManifoldNavigators();
  HRESULT GetCellManifoldOffsetNavigators (ListPOfCATCellManifoldOffsetNavigator & oOffsetNavigators);
  HRESULT GetGroupNavigators         (ListPOfCATCellManifoldGroupNavigator & oGroupNavigators);  
  HRESULT GetButtonManifoldNavigators(ListPOfCATGMLiveShapeButtonNavigator & oButtonNavigators);
  CATBoolean GetCellManifoldGroupExtendMode(CATCellManifoldGroup & iCMGroup);

  void  GetCellManifoldGroups(ListPOfCATCellManifoldGroup &oCellManifoldGroups) const; 

  //VB7 March 2018 AdvancedStamp
  HRESULT GetAdvancedStampNavigators(ListPOfCATAdvancedStampNavigator & oAdvancedStampNavigators);
  HRESULT CreateAdvancedStampNavigators(ListPOfCATAdvancedStampNavigator& oAdvancedStampNavigators);

  // Static Utilities - CGM use only
  // ----------------------------------------------------------------------------------------------
  static CATCellManifoldGroupLayer * GetGroupLayerFromCellManifoldGroup (const CATCellManifoldGroup* iCellManifoldGroup);
  static CATBoolean             IsOutdated(CATLiveBody *iLiveBody, CATSoftwareConfiguration * iConfig, CATPGMDRepBehavior * ipDRepBehavior, CATDRepOptions::Outdated_Reason & oReason);
  static const CATDRepOptions * GetDRepOptions(CATLiveBody *iLiveBody);
  static void  DumpLiveBody (CATLiveBody * iLiveBody, CATCGMOutput &Os);  
  // ==============================================================================================




  // ----------------------------------------------------------------------------------------------
  // Do not use following methods
  // ----------------------------------------------------------------------------------------------
  // Generate typed DRep Navigators, they must be deleted after use (CATSysDeletePtrList).
  // ----------------------------------------------------------------------------------------------
  //HRESULT CreateCellManifoldPatternNavigators(ListPOfCATCellManifoldPatternNavigator& oNavigatorList);
  HRESULT CreateCellManifoldOffsetNavigators(ListPOfCATCellManifoldOffsetNavigator& oNavigatorList);
  HRESULT CreateCellManifoldExtrusionNavigators(ListPOfCATCellManifoldExtrusionNavigator& oNavigatorList);
  HRESULT CreateCellManifoldLogoNavigators(ListPOfCATCellManifoldLogoNavigator& oNavigatorList);
  HRESULT CreateGroupNavigators(ListPOfCATCellManifoldGroupNavigator& oNavigatorList);
  HRESULT CreateButtonNavigators(ListPOfCATGMLiveShapeButtonNavigator& oNavigatorList);
  //CATCellManifoldPatternNavigator** GenerateCellManifoldPatternNavigators(int &oNumberOfGenerators);
  // ----------------------------------------------------------------------------------------------

  // GetAs methods
  virtual CATDRepNavigator* GetAsDRepNavigator();

  // Set methods
  void SetIgnoreBoneManifoldsMode(CATBoolean iMode); // Default mode is TRUE

  // Compute methods
  virtual HRESULT ComputeAdjacentElements(CATBoolean iOnlySmoothAdjacency = FALSE, CATBoolean iComputeTransitionMathPoint = FALSE, CATBoolean iIgnoreCellsWithSameSurface = FALSE);
  virtual HRESULT ComputeBorderPseudoVertices(CATBoolean iOnlyPseudoVertexWithAtLeastFourSharpEdges = TRUE, CATBoolean iComputePseudoVertexMathPoint = TRUE);
  virtual HRESULT ComputeCommonBorderEdges();

  // New
  // Compute the extended list of cell manifold via SPEC selection. 
  // Current Spec : 
  //     1. Neutral Draft --extend--> Draft CellManifold.
  // @ param iUserCMSelection : ~IN, CMs selected by the user.
  // @ param oSpecExtentedCMHashTab : ~OUT, CMs selected by user + computed spec selection.
  // virtual HRESULT SpecExtendCellManifolds(const ListPOfCATCellManifold &iUserCMSelection, CATCellManifoldHashTable &oSpecExtentedCMHashTab) const;

  // New
  // Compute the extended list of cell manifold via SPEC selection. 
  // Current Spec : 
  //    1. Neutral Draft --extend--> Draft CellManifold.
  // @ param ipCellManifold : ~IN, input geometry (CATCellManifold)
  // @ param oRelativeDraftManifoldHT : ~OUT, relative declarative DraftManifolds
  virtual HRESULT NeutralContextToDraftManifold(CATCellManifold *ipCellManifold, CATDeclarativeManifoldHashTable &oRelativeDraftManifoldHT) const;


  // Downward link search for first bounding CellManifolds
  // Dimension n -> n-1 ( ex : FaceManifolds -> EdgeManifolds )
  // @param iCellManifoldList : All CMs must have the same dimension,
  //                            otherwise this method returns E_FAIL
  virtual HRESULT ComputeBoundingCells (const ListPOfCATCellManifold & iCellManifoldList, 
                                        ListPOfCATCell               & oBoundingCells, 
                                        ListPOfCATCellManifold       & oBoundingCellManifolds,
                                        ListPOfCATEdge               * oFreeBorderEdges=NULL,
                                        ListPOfCATVertex             * oFreeBorderVertices=NULL);

  // Downward link search for all type of bounding cells
  // Dimension n -> n-1, n-2. The depth of search depend of given inputs.
  virtual HRESULT ComputeBoundingCells (const CATCellManifold   * iCellManifold, 
                                        ListPOfCATEdge          * oBoundingEdges=NULL,
                                        ListPOfCATVertex        * oBoundingVertices=NULL,
                                        ListPOfCATCellManifold  * oBoundingEdgeManifolds=NULL,
                                        ListPOfCATCellManifold  * oBoundingVertexManifolds=NULL);

  // Upward link search  for bounded CellManifolds 
  // Dimension n -> n+1 ( ex : EdgesManifolds -> FacesManifolds )
  virtual HRESULT ComputeBoundedCellManifolds(const ListPOfCATCellManifold &iBorderCellManifoldList, ListPOfCATCellManifold &oBoundedCellManifolds);

  // Determine les CellManifolds de dimension n adjacentes aux CM d’entrées de dimension n.
  // Dimension n -> n ( ex : FaceManifolds -> FaceManifolds )
  virtual HRESULT ComputeAdjancentCellManifolds (const ListPOfCATCellManifold &iCellManifolds, ListPOfCATCellManifold &oAdjacentCellManifolds);


  // --------------------------------------------------------------------------------------------------------------
  // Publishable & Published DRep
  // --------------------------------------------------------------------------------------------------------------
  // DRep Access
  virtual HRESULT GetPublishableManifolds(CATCellManifold * ipCellManifold, ListPOfCATManifold & oPublishableManifolds);
  // Get ManifoldList from geometry type
  virtual HRESULT GetManifoldFromGeometryType(const CATListOfULONG32 & iGeometryTypes, ListPOfCATManifold & oManifoldToFollow) const;
  
  // Get published paramId from Manifold
  // @oPubParamIDList : Do no release ! It is pointed directly by the CATLiveBody.
  // @nocgmitf - CGM Use ony ! not to be exposed to application.
  HRESULT IsPublished(CATManifold * ipManifold, ListPOfCATManifoldParamId *oPubParamIDList=NULL) const;
  // @nocgmitf - cgm use only
  HRESULT IsPublished(CATManifold * ipManifold, CATListOfInt &oPublishedKeys) const;

  // ComputeG1Edges
  // --------------
  // This methode is design for VariationalManager,
  // in order to give the right moving edges for FlexiblePlus operator.
  //   SPEC1 : Give the edge G1 at the boundary of the ListOfSameMoveCell
  //   SPEC2 : Do not return the edges already given iListOfSameMoveCellList
  // ------------------------------------------------------------------------
  void ComputeG1Edges(ListPOfListPOfCATCell & iListOfSameMoveCellList,
                      ListPOfCATEdge        & oG1EdgesList,
                      ListPOfCATFace        & oFaceRightList, // Parallele list with oG1EdgesList
                      ListPOfCATFace        & oFaceLeftList); // Parallele list with oG1EdgesList

  virtual HRESULT GetHVertexPosition(CATHVertex *iHVertex, CATMathPoint &oPosition);
  HRESULT GetMultiOccurenceCellManifolds(CATCellManifoldGroup* iNetworkGroup, CATLISTP(CATCellManifold) &oMultiOccurenceCellManifolds);
  HRESULT GetAdaptedPlane(CATMathPlane &ioMathPlane);
  HRESULT GetUpToDateStatus(CATDeclarativeManifold * iDM, CATDMUpToDateStatus &oStatus);
  HRESULT GetUpToDateStatus(CATCellManifoldGroup * iCMG, CATDMUpToDateStatus &oStatus);
  
  // ------------------------------------------------------------------------
  //Group Methods
  // ------------------------------------------------------------------------
  CATBoolean IsGroupFullyCoveredByCells(const CATCellManifoldGroup *iGroup,const ListPOfCATCellManifold &iCellManifolds);
  CATBoolean IsGroupEditable(const CATCellManifoldGroup *iGroup); // Is Group modifiable with CATManifoldEditor

  void GetCellManifoldGroupsFromCellManifold(CATCellManifold * ipCellManifold, ListPOfCATCellManifoldGroup &oGroupsOnCellManifold);
  // deprecated
  void GetCellManifoldGroupsFromCellManifold(const ListPOfCATCellManifoldGroupLayer &iGroupLayers,ListPOfCATCellManifoldGroup &oGroupsOnCellManifold);

  // ------------------------------------------------------------------------
  // Pattern Methods 
  // ------------------------------------------------------------------------
  CATBoolean BelongsToCellManifoldPattern();
  CATBoolean BelongsToCellManifoldPattern(CATCellManifoldPatternNavigator *& oPatternNavigator, short &oInstanceNumber);
  CATBoolean BelongsToCellManifoldPattern(CATCellManifoldGroup* &ioNetworkGroup, CATCellManifoldGroup* &ioPatternGroup, short &oInstanceNumber, 
    CATMathTransformation * ioTransfoFromReference, CATBoolean * ioPatternGroupIsComplete = NULL);
  CATBoolean LiveBodyHasPatterns(); 
  CATBoolean LocatePatternGroup(CATCellManifoldGroup * iGroup, CATCellManifoldPatternNavigator ** opPatternNavigator = NULL);

  // ------------------------------------------------------------------------
  // Offset Methods 
  // ------------------------------------------------------------------------
  CATBoolean BelongsToOffsetGroup();
  CATBoolean BelongsToOffsetGroup(CATCellManifoldOffsetNavigator *& oOffsetNavigator, short &oInstanceNumber);

  // ------------------------------------------------------------------------
  //Instance group methods
  // ------------------------------------------------------------------------
  CATBoolean BelongsToInstanceGroup(CATCellManifoldGroup * &oNetworkGroup);
  CATBoolean BelongsToInstanceGroup (CATCellManifold *iCellManifold, 
                                      CATCellManifoldGroup *&oCellManifoldOwnerGroup, 
                                      CATCellManifoldGroup *&oInstanceGroup, 
                                      CATCellManifoldGroup *&oNetworkGroup, 
                                      CATCellManifoldGroupNavigator *&oManifoldGroupNav);
  CATBoolean BelongsToInstanceGroup (CATCellManifoldGroup * iNetworkGroup, CATCellManifoldGroup *&oInstanceGroup, CATCellManifoldGroup *&oCellManifoldOwnerGroup);
  
  // ------------------------------------------------------------------------
  //Extrusion group methods
  // ------------------------------------------------------------------------
  CATBoolean BelongsToExtrusionGroup(CATCellManifoldExtrusionNavigator *& oExtrusionNavigator);
  
  // ------------------------------------------------------------------------
  //Logo group methods
  // ------------------------------------------------------------------------
  CATBoolean BelongsToLogoGroup(CATCellManifoldLogoNavigator *& oLogoNavigator);

  // ------------------------------------------------------------------------
  //AdvancedStamp group methods
  // ------------------------------------------------------------------------
  CATBoolean BelongsToAdvancedStampGroup(CATAdvancedStampNavigator *& oAdvancedStampNavigator);
  CATBoolean LocateAdvancedStampGroup(CATCellManifoldGroup * iGroup, CATAdvancedStampNavigator ** opAdvancedStampNavigator = NULL);

  // ------------------------------------------------------------------------
  // Edge packets
  // ------------------------------------------------------------------------
  // Representative = stable edge that represents the edge packet.
  HRESULT GetRepresentative(const ListPOfCATCell & iPacketEdges, CATEdge *& oRepresentative);
  HRESULT GetRepresentative(CATEdge * iEdge, CATEdge *& oRepresentative);
  HRESULT GetPacketExtremities(CATEdge * iEdge, CATVertex *& oStartVertex, CATVertex *& oEndVertex);
  HRESULT GetPacket(CATEdge * iEdge, ListPOfCATCell & oPacketEdges);

  HRESULT GetBorderEdgeManifolds(ListPOfCATCellManifold & oBorderEdgesManifolds);
  
  CATLiveBody* CreateReferenceLiveBody(CATCellManifoldGroup* iNetworkGroup);

  HRESULT IsVertexSmooth();

  CATSoftwareConfiguration * GetSoftwareConfiguration() const;


  void CleanDataForMultiRun();

  //Get methods
  INLINE const CATTopData * GetTopData()  const;
  INLINE CATLiveBody      * GetLiveBody() const;

protected:
  virtual CATCellManifoldPatternNavigator * CreateCATCellManifoldPatternNavigator(const CATTopData &iData, CATLiveBody* iLiveBody, CATCellManifoldGroup* iNetworkGroup); 
  virtual CATCellManifoldPatternNavigator * CreateCATCellManifoldPatternNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup* iNetworkGroup); 
  virtual CATCellManifoldPatternNavigator * CreateCATCellManifoldPatternNavigator(CATCellManifoldPatternNavigator * iPatternNavigator);

  CATBoolean IsOutdated(CATSoftwareConfiguration * iConfig, CATPGMDRepBehavior * ipDRepBehavior, CATDRepOptions::Outdated_Reason & oReason) const;
  CATCellManifoldGroupNavigator *GetCATCellManifoldGroupNavigator(const CATCellManifoldGroup *iGroup);
  
  INLINE const ListPOfCATManifoldRibbonNavigator & GetRefDraftNavigators() const;

private:
  CATDRepNavigator(CATDRepNavigator& iNavigator); 
  CATDRepNavigator& operator=(const CATDRepNavigator&);  

  const CATLiveBodyCGM & GetLiveBodyCGM() const; // throw if null

  HRESULT GetCommonBorderEdgesOrSharpness(CATCellManifold *iCM1, ListPOfCATCell &iBorderCells1, ListPOfCATCell &iBoundedCells1,
    CATCellManifold *iCM2, ListPOfCATCell &iBorderCells2, ListPOfCATCell &iBoundedCells2,
    CATTopGeoContinuity *oContinuity = NULL, ListPOfCATEdge* ioCommonBorderEdges = NULL);
  
  HRESULT GetBoundary(CATCellManifold *iCellManifold, int idim, ListPOfCATCell &oBorderCells, ListPOfCATCell* ioBoundedCells = NULL) const;
  HRESULT GetBoundary(ListPOfCATCellManifold &iListOfCellManifolds, int idim, ListPOfCATCell &oBorderCells, ListPOfCATCell* ioBoundedCells = NULL) const;

  HRESULT ComputeMidPoint(ListPOfCATEdge &iListOfEdges, CATMathPoint &oMiddlePoint) const;

  HRESULT GetBoundedFacesAndEdges(CATVertex * iVertexVertex, 
    ListPOfCATFace &oBoundedFaces, ListPOfCATEdge &oBoundedEdges, CATBoolean iOnlySharpEdges);

  HRESULT CreateJointFilletPseudoVertex(CATJointFillet* iJointFillet,
    CATBoolean iOnlyPseudoVertexWithAtLeastFourSharpEdges, CATBoolean iComputePseudoVertexMathPoint);

  HRESULT ComputeCommonIntersectionPoint(CATLISTP(CATSurface) &iBorderSurfaces, ListPOfCATCell &iSortingVertices,
    CATBoolean &oCommonIntersectionExist, CATMathPoint &oCommonIntersectionPoint) const;

  CATBoolean IsSmoothEdge(CATEdge * iEdge, CATFace *& oFaceR, CATFace *& oFaceL) const;

  CATFace   * ConvertToFace(CATCell *iCell) const;
  CATEdge   * ConvertToEdge(CATCell *iCell) const;
  CATVertex * ConvertToVertex(CATCell *iCell) const;
  void GetVertexMathPoint(CATVertex* iVertex, CATMathPoint &oPosition) const;
  void GetCellManifoldsFromFaces(ListPOfCATFace &iFaces, ListPOfCATCellManifold &oCellManifolds) const;

  HRESULT ComputeCellManifoldsAdjacentToCell();

  HRESULT GetConnexComponent(CATEdge * iEdge, CATEdgeHashTable & oPacketEdges, CATVertex *& oStartVertex, CATVertex *& oEndVertex, CATBoolean & oEndVertexIsSmooth) const;

  // =======================================================================================================================
  // PGMDRepGroup Management
  // =======================================================================================================================
  HRESULT GetPGMDRepGroupFromCellManifoldGroup(const ListPOfCATCellManifoldGroup &iRetrievedCMGroupList, CATLISTP(CATIPGMDRepGroup) & oPGMDRepGroupList);

  CATIPGMDRepGroup * CreatePGMDRepGroupFrom(const CATCellManifoldGroup * iCellManifoldGroup);
  CATIPGMDRepGroup * RetrievePGMGroupFromHT(const CATCellManifoldGroup * iCellManifoldGroup) const;
  
  int InsertToPGMDRepGroupBufferHT(const CATCellManifoldGroup * iCellManifoldGroup, const CATIPGMDRepGroup *iAssociatedPGMDRepGroup);
  // -----------------------------------------------------------------------------------------------------------------------

protected:
 CATLiveBody* _LiveBody;
 CATBoolean _IgnoreBoneManifolds;

 // ----------------------------------------------------------------------------------------------
 // Navigators Buffers
 void InitPatternNavigators();
 void InitRibbonNavigators();
 HRESULT InitDraftNavigators();
 void InitGroupNavigators();
 void InitOffsetNavigators();
 void InitButtonNavigators();
 void InitExtrusionNavigators();
 void InitLogoNavigators();
 void InitAdvancedStampNavigators();


 ListPOfCATCellManifoldPatternNavigator   _PatternNavigators;
 ListPOfCATManifoldRibbonNavigator        _RibbonNavigators;
 ListPOfCATManifoldRibbonNavigator        _DraftNavigators; // new
 ListPOfCATCellManifoldGroupNavigator     _GroupNavigators;
 ListPOfCATCellManifoldOffsetNavigator    _OffsetNavigators;
 ListPOfCATGMLiveShapeButtonNavigator     _ButtonNavigators;
 ListPOfCATCellManifoldExtrusionNavigator _ExtrusionNavigators;
 ListPOfCATCellManifoldLogoNavigator      _LogoNavigators;
 ListPOfCATAdvancedStampNavigator         _AdvancedStampNavigators;
 CATBoolean _PatternNavigatorsBuffer;
 CATBoolean _RibbonNavigatorsBuffer;
 CATBoolean _DraftNavigatorsBuffer;
 CATBoolean _GroupNavigatorsBuffer;
 CATBoolean _OffsetNavigatorsBuffer;
 CATBoolean _ButtonNavigatorsBuffer;
 CATBoolean _ExtrusionNavigatorsBuffer;
 CATBoolean _LogoNavigatorsBuffer;
 CATBoolean _AdvancedStampNavigatorsBuffer;
 // ----------------------------------------------------------------------------------------------

 // Assciate CellManifoldGroup and created PGMDRepGroup
 CATCGMHashTableWithAssoc * _PGMDRepGroupBufferHT; 

 // FOR DEBUG PURPOSE ONLY
 // Do not use in algorithm.
 int _DebugTag;

};

INLINE const CATTopData * CATDRepNavigator::GetTopData()  const { 
  return (/*(CATTopData*)*/&_TopData); }

INLINE CATLiveBody * CATDRepNavigator::GetLiveBody() const { 
  return _LiveBody; }

INLINE const ListPOfCATManifoldRibbonNavigator & CATDRepNavigator::GetRefDraftNavigators() const {
  return _DraftNavigators; }

#endif
