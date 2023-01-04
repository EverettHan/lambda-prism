#ifndef CATPersistentUtilities_H
#define CATPersistentUtilities_H
//===================================================================
// COPYRIGHT Dassault Systemes 2003
//===================================================================
//
// CATPersistentUtilities.h
// 		
//===================================================================
//  Oct 2003  Creation: JHG
//===================================================================

#include "CATTopRibTraceObject.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATTopDefine.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATCell.h"
#include "PersistentCell.h"

#include "ListPOfListPOfCATEdge.h"
#include "ListPOfCATPersistentBodies.h"

class CATCGMAttrId;
class CATCGMJournalList;
class CATBody;
class CATVertex;
class CATEdge;
class CATMathPoint;
class CATGeometry;
class CATPCurve;
class CATCloneManager;
class CATMathVector;

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATPersistentCellInfra;
class CATCellHashTable;


#define APPENDLIST(TargetList, SourceList) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
TargetList.Append(SourceList[ielement]); \
} \
}

#define APPENDCONVLIST(TargetList, SourceList, ConversionFunction) { \
  int ielement = 0; \
  for(ielement = 1; ielement <= SourceList.Size(); ielement++) \
{ \
TargetList.Append(ConversionFunction(SourceList[ielement])); \
} \
}

class ExportedByPersistentCell CATPersistentUtilities : public CATTopRibTraceObject
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  DEFINE_ADVOP_CLASS_NAME("CATPersistentUtilities")

  CATPersistentUtilities(CATGeoFactory &iFactory, CATSoftwareConfiguration *iConfig);

  virtual ~CATPersistentUtilities();
/*
  void FollowShellOrientationWithJournal(CATCGMJournalList *iJournal,
    CATBody *iNewShellBody, CATBody *iShellBodyToFollow, int &oRelativeOrientation);

  CATEdge *FollowCurveWithJournal(CATPCurve *iPCurve, CATCGMJournalList *iJournal);

  CATBody *CloneWithLyingOn(CATBody *iBodyToClone, CATCGMJournalList *iJournal,
    CATBody *iLyingOnBody, CATCloneManager **oDuplicator = NULL);

  void DualCloneWithLyingOn(CATBody *iBodyToClone, CATBody *&oClonedBody, 
    CATBody *iBodySupportToClone, CATBody *&oClonedBodySupport, CATCGMJournalList *iJournal);
*/
  CATBoolean FindOrientationBetweenTwinEdges(CATEdge *iEdge1, CATEdge *iEdge2, int &oOrientation);

  // Limitation : For not confused faces, the orientation is always 1.
  CATBoolean FindOrientationBetweenTwinFaces(CATFace *iFace1, CATFace *iFace2, int &oOrientation);

  CATBoolean FindOrientationBetweenEdgeAndListOfEdges(CATEdge &iEdge, ListPOfCATEdge &iListEdge, CATListOfInt &oOrientations);
//  void FindOrientationBetweenEdgeAndTwinListOfEdges(CATEdge &iEdge,
//    ListPOfCATEdge &iListEdge, ListPOfCATEdge &oOrderedListEdge, CATListOfInt &oOrientations);
  
  CATBoolean OrientListOfEdges(ListPOfCATEdge &iListEdge, ListPOfCATEdge &oOrderedListEdge, CATListOfInt &oOrientations,
    CATVertex ** oPseudoWireStartVertex = NULL, CATVertex ** oPseudoWireEndVertex = NULL);

  void GetVertexMathPoint(CATVertex *iVertex, CATMathPoint &oMathPoint);

/*  CATVertex *CreateVertexInBody(CATBody &iBody, const CATMathPoint &iPosition);

  int ComputeFreeEdgeSide(CATEdge *iEdge, CATBody *iShellBody);

  // Function for the skin
  CATBoolean IsSkin(CATBody *iInputBody);*/

  CATBody *CleanFatVertices(CATBody *iFrozenBody, ListPOfCATVertex &iVerticesToClean, CATCGMJournalList *iJournal);

/*  int CountSharpEdges(CATBody *iBody, ListPOfCATEdge *oSharpEdges = 0,
    ListPOfCATFace *oBoundedFaces1 = 0, ListPOfCATFace *oBoundedFaces2 = 0,
    CATListOfInt *oConvexity = 0);*/

  CATBody *RemoveFaces(CATBody *iBody, ListPOfCATCell &iFacesToRemove, CATBoolean iOrientationsNotReliable = 0);
/*
  // Return TRUE when the specified edges define only one connected component,
  // else return FALSE. When the so-constituted wire is open, oStartVertex and
  // oEndVertex are filled with extremity vertices; they are set to NULL if the
  // wire is closed.
  CATBoolean FindPseudoWireExtremities(ListPOfCATEdge &iEdges,
                                       CATVertex *&oStartVertex, CATVertex *&oEndVertex,
                                                             CATListOfInt *iEdgesOrientation = 0);*/

  CATBody *CreateBodyFromCellPack(const ListPOfCATCell &iCells, const CATListOfInt *iOrients = NULL,
                                                      ListPOfCATDomain *oDomains = NULL);

  // Create a journal for Extract persistent Body. The given journal must be deleted after use.
  // Extract can have been done from multiple bodies
  CATCGMJournalList * CreateCGMJournalFromExtract(const ListPOfCATPersistentBodies  & iInputPersistentBodies,                                                                                      
                                                   const CATCellHashTable           & iExtractedCellHT,
                                                   CATBody *                          iResultExtractBody,
                                                   CATPersistentCellInfra           & iPersistentInfra);

/*  void ComputeInsideDirection(int iVertexDirection, CATEdge *iEdge, CATFace *iBoundedFace, CATMathVector &oVector);
  void EvalTangent(int iVertexDirection, CATEdge *iEdge, CATMathVector &oVector);

  CATBoolean TestWetherTwoEdgesHaveSameVertices(CATEdge *iEdge1, CATEdge *iEdge2, int &oOri);

  CATOrientation PositionVertexVsShell(CATMathPoint &iPoint, CATShell *iShell);

  void GetCommonBoundingCells(ListPOfCATCell &iCells1, ListPOfCATCell &iCells2, ListPOfCATCell &oCommonCells);

  void OrderOrientedEdges(ListPOfCATEdge &iEdges, CATListOfInt &iOrientation, CATListOfInt &oNumberOfEdgesByGroup, ListPOfCATEdge &oOrderedEdges,
    CATListOfInt &oOrderedOrientation);

#ifdef UNDEF_CallFilletOnUnfilletedParts
  void GroupEdgesNonManifold(ListPOfCATEdge &iEdgesToGroup, ListPOfCATEdge &oGroupedEdges,
    CATListOfInt &oNbOfEdgesByGroup);
  void StabilizeEdgesOrder(ListPOfCATEdge &iEdgesToOrder, ListPOfCATEdge &oOrderedEdges);
#endif

  void ReleaseAttribute(const ListPOfCATCell &iCellsToClean, const CATCGMAttrId *iAttrId);*/
  // Return TRUE when the specified edges define only one connected component,
  // else return FALSE. When the so-constituted wire is open, oStartVertex and
  // oEndVertex are filled with extremity vertices; they are set to NULL if the
  // wire is closed.
  static CATBoolean FindPseudoWireExtremities(ListPOfCATEdge &iEdges,
                                              CATVertex *&oStartVertex, CATVertex *&oEndVertex,
                                              CATListOfInt *iEdgesOrientation = 0,
                                              CATEdge **oStartEdge = 0, CATEdge **oEndEdge = 0);

  static void FindSetOfEdgesBoundingVertices(ListPOfCATEdge &iEdges, ListPOfCATVertex &oVertices, 
                                             CATListOfInt *iEdgesOrientation = 0, CATListOfInt *oVerticesOrientation = 0,
                                             ListPOfCATEdge *oExtremityEdges = 0);

  static CATBoolean PseudoWireContainsVertices(ListPOfCATEdge &iEdges, ListPOfCATVertex &iVerticesToFind, CATBoolean &oVxInTheMiddle,
                                             CATListOfInt *iEdgesOrientation = 0);

  
  static void GetCommonEdges(CATFace &iFace1, CATFace &iFace2, ListPOfCATEdge &oCommonEdges);
  static void GetCommonBoundingEdges(ListPOfCATFace &iFaces1, ListPOfCATFace &iFaces2, ListPOfCATEdge &oCommonEdges);

  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig, 
                               CATVertex                &iVertex, 
                               CATBody                  &iBody, 
                               ListPOfCATFace          &oAdjacentFaces);

  static CATBoolean GetLimitingFaces(CATSoftwareConfiguration *iConfig, 
                                     ListPOfCATEdge &iPseudoWireEdges, 
                                     CATBody &iBody,
                                     ListPOfCATFace oLimitingFaces[2]);
  //This method create a valid copy mode journal between iInputPersistentBodies and iResultPersistentBody, with needed deleted cells and created cells from nothing
  static void CreateMinimalValidJournal(const ListPOfCATPersistentBodies &iInputPersistentBodies,
                                        CATBody                    *iResultBody,
                                        CATPersistentCellInfra     &iInfra,
                                        CATCGMJournalList          &oJournal);

  //Compute the images of a face through the PersistentCellInfra
  static void GetImageFacesThroughPersistentFaces(CATFace *iInputFace, CATPersistentBody *iInputPersistentBody,
                                                  CATPersistentCellInfra &iInfra,
                                                  CATPersistentBody *iOuputPersistentBody, ListPOfCATFace &oOutputFaces);

  //Compute the images of an edge through the PersistentCellInfra
  static void GetImageEdgesThroughPersistentEdges(CATEdge *iInputEdge, CATPersistentBody *iInputPersistentBody,
                                                  CATPersistentCellInfra &iInfra,
                                                  CATPersistentBody *iOuputPersistentBody, ListPOfCATEdge &oOutputEdges);

  //Compute the images of a vertex through the PersistentCellInfra
  static void GetImageVertexsThroughPersistentVertexs(CATVertex *iInputVertex, CATPersistentBody *iInputPersistentBody,
                                                      CATPersistentCellInfra &iInfra,
                                                      CATPersistentBody *iOuputPersistentBody, ListPOfCATVertex &oOutputVertexs);


private:
  void CleanFatVertex(CATGeoFactory *iFactory, CATVertex *iVertex, CATBody *iBody);
  CATBoolean FindOrientationBetweenExtremityVertices(CATVertex *StartVertex1, CATVertex *EndVertex1, 
    CATVertex *StartVertex2, CATVertex *EndVertex2, int &oOrientation);

  CATGeoFactory &_Factory;
  CATSoftwareConfiguration *_Config;
};

#endif
