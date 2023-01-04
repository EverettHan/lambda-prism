//========================================================================
// 17/07/19 PKC ajout CATSoftwareConfiguration aux arguments de GetCircle
// 17/09/19 PKC ajout CATSoftwareConfiguration à CreateBodyForCalculatingLength
//              ajout CATSoftwareConfiguration à CalculateLengthOfFeatureAlongAnAxis
// 18/09/19 PKC ajout CATSoftwareConfiguration à CalculateLengthOfBody
//========================================================================

#ifndef CATGMLiveShapeUtilities_H
#define CATGMLiveShapeUtilities_H

/*
##=================================================================================================##

 *** Merci de n'ajouter des methodes qui ne CONCERNENT QUE NATURAL SHAPE (ou le Live).  ***
     Sinon, utilisez : CATGMTopoUtilities
     -------------------------------------------------------------------------------
##=================================================================================================##
*/

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroup.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "CATListOfCATGeometries.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATBoolean.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATHGeometry.h"
#include "CATListOfCATCGMAttribute.h"
#include "CATCellManifoldHashTable.h"
#include "ListPOfListPOfCATCellManifolds.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfListPOfCATDRepSeed.h"
#include "ListPOfCATContextualManifold.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "IUnknown.h"
#include "ListPOfCATBody.h"
#include "CATManifold.h"
#include "ListPOfCATManifoldParameter.h"

#include "CATTopDefine.h"

#include "CATCGMJournalList.h"
#include "CATLISTP_CATMathPlane.h"
#include "CATIntersectionHVertex.h"
#include "CATListOfCATSurfaces.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATListOfCATCGMJournalList.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfCATPrototypeExtrusion.h"
#include "ListPOfCATDomain.h"
#include "ListPOfCATManifoldBaseParameter.h"
#include "ListPOfCATPersistentFaces.h"
#include "ListPOfCATBoneFillet.h"
#include "ListPOfCATJointFillet.h"
#include "ListPOfCATManifold.h"
#include "CATDMUpToDateStatusDefine.h"
#include "ListPOfCATBoneChamfer.h"
#include "CATLISTP_CATMathVector.h"
#include "ListPOfCATDraftManifold.h"
#include "ListPOfListPOfCATDeclarativeManifold.h"
#include "ListPOfCATManifoldModification.h"
#include "ListPOfCATPersistentEdges.h"
#include "ListPOfCATPersistentVertices.h"
#include "ListPOfCATPersistentBodies.h"

class CATSoftwareConfiguration;
class CATGeoFactory;
class CATBody;
class CATCell;
class CATVolume;
class CATEdge;
class CATVertex;
class CATSurface;
class CATCGMJournalList;
class CATBoneFillet;
class CATCellManifold;
class CATDeclarativeManifold;
class CATVertex;
class CATLiveBody;
class CATShell;
class CATCGMHashTable;
class CATDeclarativeManifoldCGM;
class CATCGMAttribute;
class CATMapVoidToVoid;
class CATCDMBaseServices;
class CATSphereManifold;
class CATMathOBB;
class CATMathAdvancedBox;
class CATlsoDataCache;
class CATGMSpecInfra;
class CATExtTopOperator;
class CATMathOBBCloud;
class CATPGMDRepBehavior;
class CATVertexHashTable;
class CATEdgeHashTable;
class CATFaceHashTable;
template <class CATCellManifold> class CATLSOHashTable;
class CATPersistentCellInfra;
class PersistentCell;
class CATPersistentBody;
class CATlsoPersistentContext;
class CATGMLiveContextualFeatureFollower;
class CATWire;
class CATCircle;
class CATCellHashTable;
class CATSurLimits;
class CATSurParam;


#define REMOVELISTOFLIST(Lists) { \
  int ielement = 0, nelement = Lists.Size(); \
  for(ielement = 1; ielement <= nelement; ielement++) \
  { \
    if (Lists[ielement]) \
      { \
        delete Lists[ielement]; \
        Lists[ielement] = NULL; \
      } \
  } \
}

#define REMOVEHASHOFFACELIST(HT) { \
  if (HT) \
  { \
    int ifacelist = 0, nfacelist = HT->Size(); \
    for (ifacelist = 0; ifacelist < nfacelist; ifacelist++) \
    { \
      ListPOfCATFace* FaceList = (ListPOfCATFace*)HT->GetAssoc(ifacelist); \
      CATSysDeletePtr(FaceList); \
    } \
    CATSysDeletePtr(HT); \
  } \
}

class ExportedByPersistentCell CATGMLiveShapeUtilities
{

/*
##=================================================================================================##

 *** Merci de n'ajouter des methodes qui ne CONCERNENT QUE NATURAL SHAPE (ou le Live).  ***
     Sinon, utilisez : CATGMTopoUtilities
     -------------------------------------------------------------------------------
##=================================================================================================##
*/
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATGMLiveShapeUtilities(CATSoftwareConfiguration * iConfig);
  virtual ~CATGMLiveShapeUtilities();

  static void GetFaces(const CATLISTP(CATGeometry) &iListOfGeometries, CATLISTP(CATFace) &oListOfFaces);
  static void GetFaces(const ListPOfCATCell &iListOfCells, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const ListPOfCATContextualManifold &iListOfContManifolds, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const ListPOfCATDeclarativeManifold &iListOfDeclManifolds, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const CATDeclarativeManifold& iDeclManifold, ListPOfCATFace& oListOfFaces);
  static void GetFaces(const CATDeclarativeManifold& iDeclManifold, CATFaceHashTable& oListOfFaces);
  static void GetFaces(const ListPOfCATCellManifoldGroup& iCellManifoldGroups, ListPOfCATFace& oListOfFaces);
  static void GetFaces(const CATCellManifoldGroup& iCellManifoldGroup, ListPOfCATFace& oListOfFaces);
  static void GetFaces(CATCellManifoldHashTable &iListOfCellManifolds, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const CATCellManifold &iCellManifold, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const ListPOfCATBoneFillet &iListOfBoneFillets, ListPOfCATFace &oListOfFaces);
  static void GetFaces(const ListPOfCATManifold &iManifolds, ListPOfCATFace &oListOfFaces);

  // Converto To HashTable
  static void GetFaces(const ListPOfCATCellManifold &iListOfCellManifolds, CATFaceHashTable &oFaceHT);
  static void GetFaces(const ListPOfCATDeclarativeManifold &iListOfDeclManifolds, CATFaceHashTable &oFaceHT);
  static void GetFaces(const ListPOfCATContextualManifold &iListOfContManifolds, CATFaceHashTable &oFaceHT);
  static void GetFaces(const ListPOfCATJointFillet &iListOfJointFillets, CATFaceHashTable &oFaceHT);
  static void GetFaces(const ListPOfCATCell &iListOfCells, CATFaceHashTable &oFaceHT);
  static void GetFaces(const CATLISTP(CATGeometry) &iListOfGeometries, CATFaceHashTable &oFaceHT);
  static void GetFaces(const CATCellManifold &iCellManifold, CATFaceHashTable &oFaceHT);
  
  static void GetFacesFromSurface(CATBody & iBody, const CATSurface *iSurface, ListPOfCATFace &oListOfFaces);

  static void GetBodies(const CATLISTP(CATICGMObject) &iCGMObjectList, ListPOfCATBody &oListOfBodies);

  static void GetSurfaces(const ListPOfCATFace & iListOfFaces, CATLISTP(CATSurface) & oSurfaceList);
  static CATSurface * GetSurface(const ListPOfCATFace & iListOfFaces);
  static void GetSurfaces(CATBody & iBody, CATLISTP(CATSurface) & oSurfaceList);
  static void GroupFacesBySurface(const ListPOfCATFace & iListOfFaces, CATListOfInt &oNbFacesPerSurface, ListPOfCATFace &GroupedFaceList);
  static HRESULT GroupFacesBySurface(const ListPOfCATFace & iListOfFaces, CATCGMHashTableWithAssoc &oSurfaceToFaceList); // 'item'=CATSurface*, 'Assoc'=ListPOfCATFace* it must be deleted after use.

  static void GetPersistentCells(const ListPOfCATPersistentFaces & iPersistentFaceList, ListPOfCATPersistentCells & oPersistentCellList);
  static void GetPersistentFaces(ListPOfCATPersistentCells & iPersistentCellList, ListPOfCATPersistentFaces & oPersistentFaceList);
  static void GetPersistentEdges(ListPOfCATPersistentCells & iPersistentCellList, ListPOfCATPersistentEdges & oPersistentEdgeList);
  static void GetPersistentVertices(ListPOfCATPersistentCells & iPersistentCellList, ListPOfCATPersistentVertices & oPersistentVertexList);

  static void GetEdges(const CATLISTP(CATGeometry) &iListOfGeometries, ListPOfCATEdge &oListOfEdges);
  static void GetEdges(const ListPOfCATCell &iListOfCells, ListPOfCATEdge &oListOfEdges);
  static void GetEdges(ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATEdge &oListOfEdges);
  static void GetEdges(const CATDeclarativeManifold& iDeclManifold, ListPOfCATEdge& oListOfEdges);
  static void GetEdges(const ListPOfCATCell &iListOfCells, CATEdgeHashTable &oEdgeHT); // From List + HT
  static void GetEdgesFromFaces(const ListPOfCATFace &iFaceList, CATEdgeHashTable &oEdgeHT); // From List -> HT
  static void GetEdgesFromFaces(const CATFaceHashTable &iFaceHT, CATEdgeHashTable &oEdgeHT); // From HT -> HT
  static void GetVertices(const ListPOfCATCell &iListOfCells, ListPOfCATVertex &oListOfVertices);
  static void GetVertices(const CATLISTP(CATGeometry) &iListOfGeometries, ListPOfCATVertex &oListOfVertices);
  static void GetVerticesFromEdges(const ListPOfCATEdge &iListOfEdges, ListPOfCATVertex &oListOfVertices);
  static void GetVerticesFromEdges(const ListPOfCATEdge &iListOfEdges, CATVertexHashTable &oVertexHT); // propre + perfo
  static void GetVerticesFromEdges(const CATEdgeHashTable &iListOfEdges, CATVertexHashTable &oVertexHT); // propre + perfo
  static void GetVerticesFromFaces(ListPOfCATFace &iListOfFaces, ListPOfCATVertex &oListOfVertices);
  static void GetVerticesFromFaces(const ListPOfCATFace &iListOfFaces, CATVertexHashTable &oVertexHT); // propre + perfo
  static void GetVerticesFromFace(CATFace *iFace, ListPOfCATVertex &oListOfVertices);
  static void GetAllVertices(const ListPOfCATCell & iCellList, CATVertexHashTable & oVertexHT);

  static void GetCells(const ListPOfCATDeclarativeManifold& iDeclManifolds, ListPOfCATCell& oListOfCells);
  static void GetCells(const CATDeclarativeManifold& iDeclManifold, ListPOfCATCell& oListOfCells);
  static void GetCells(const CATLISTP(CATGeometry) &iListOfGeometries, ListPOfCATCell &oListOfCells);
  static void GetCells(const ListPOfCATFace &iListOfFaces, ListPOfCATCell &oListOfCells);
  static void GetCells(const ListPOfCATEdge &iListOfEdges, ListPOfCATCell &oListOfCells);
  static void GetCells(const ListPOfCATVertex &iListOfVertices, ListPOfCATCell &oListOfCells);
  static void GetCells(const ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATCell &oListOfCells);
  static void GetCells(const CATCellManifoldGroup & iCellManifoldGroup, ListPOfCATCell & oListOfCells);
  static void GetCells(const CATManifold & iManifold, ListPOfCATCell & oListOfCells);
  static void GetCells(const ListPOfCATManifold & iManifoldList, ListPOfCATCell & oListOfCells);
  static void GetCells(const ListPOfListPOfCATCell & iCellListOfList, ListPOfCATCell & oListOfCells);
  static void GetCells(const ListPOfCATManifoldModification &iModifList, CATCellHashTable &oCellHT);

  static void GetReps(const CATLISTP(CATCellManifoldGroup) & iCMGList, ListPOfCATCellManifold & oCMList);

  static CATCellManifold *        GetCellManifold(CATFace * iFace, const CATLiveBody & iLiveBody);
  static CATDeclarativeManifold * GetDeclManifold(CATFace * iFace, const CATLiveBody & iLiveBody);

  static void GetDeclManifolds(const ListPOfCATFace &iListOfFaces,const CATLiveBody &iLiveBody, ListPOfCATDeclarativeManifold &oDeclManifolds, CATBoolean bRemoveDupplicate=TRUE);
  static void GetDeclManifolds(const ListPOfCATCell &iListOfCells,const CATLiveBody &iLiveBody, ListPOfCATDeclarativeManifold &oDeclManifolds);
  static void GetDeclManifolds(const ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATDeclarativeManifold &oDeclManifolds);
  static void GetDeclManifolds(const CATCellHashTable &iCellHT,const CATLiveBody &iLiveBody, ListPOfCATDeclarativeManifold &oDeclManifolds);
  static void GetDeclManifolds(const ListPOfCATManifold & iListOfManifolds,ListPOfCATDeclarativeManifold & oDeclManifolds);
  static void GetContManifolds(ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATContextualManifold &oContManifolds);
  static void GetContManifolds(ListPOfCATDeclarativeManifold &iDeclManifolds, ListPOfCATContextualManifold &oContManifolds);
  static void GetCellManifolds(ListPOfCATFace const & iListOfFaces, CATLiveBody const & iLiveBody, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(ListPOfCATEdge const & iListOfEdges, CATLiveBody const & iLiveBody, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const ListPOfCATCell &iListOfCell,const CATLiveBody &iLiveBody, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const CATCellHashTable &iCellHT,const CATLiveBody &iLiveBody, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const ListPOfCATDeclarativeManifold &iListOfDeclarativeManifolds, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const ListPOfCATBoneFillet &iListOfBoneFillets, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const ListPOfCATJointFillet &iListOfJointFillets, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const ListPOfCATManifold &iListOfManifolds, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifolds(const CATLISTP(CATGeometry) &iListOfGeometries, ListPOfCATCellManifold &oCellManifolds);
  static void GetCellManifoldFaces(CATFace &iFace, CATLiveBody &iLiveBody, ListPOfCATFace &oCellManifoldFaces);
  static void GetFaceManifolds(ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATCellManifold &oListOfCellManifolds);
  static void GetEdgeManifolds(ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATCellManifold &oListOfCellManifolds);
  static void GetJointFillets(const ListPOfCATDeclarativeManifold &iListOfDeclarativeManifolds, ListPOfCATJointFillet &oListOfJointFillets);
  static void GetJointFillets(const ListPOfCATContextualManifold &iContManifolds, ListPOfCATJointFillet &oListOfJointFillets);
  static void GetManifolds(const ListPOfCATCellManifold &iListOfCellManifolds, ListPOfCATManifold &oManifold);
  static void GetPatternGroups(const ListPOfCATManifold &iManifolds, ListPOfCATCellManifoldGroup &oPatternGroups);
  static void GetPatternGroups(const ListPOfCATCellManifoldGroup &iGroups, ListPOfCATCellManifoldGroup &oPatternGroups);
  static void GetExtrusionGroups(const ListPOfCATManifold &iManifolds, ListPOfCATCellManifoldGroup &oExtrusionGroups);
  static void GetLogoGroups(const ListPOfCATManifold &iManifolds, ListPOfCATCellManifoldGroup &oLogoGroups);
  static void GetAdvancedStampGroups(const ListPOfCATManifold &iManifolds, ListPOfCATCellManifoldGroup &oAdvancedStampGroups);
  static void GetFilletsManifold(const ListPOfCATManifold &iManifolds, ListPOfCATContextualManifold &oFillets);
  static void GetFilletsManifold(const ListPOfCATContextualManifold &iContManifolds, ListPOfCATBoneFillet &oFillets);
  static void GetChamfersManifold(const ListPOfCATManifold &iManifolds, ListPOfCATBoneChamfer &oChamfer);
  static void GetDraftsManifold(const ListPOfCATManifold &iManifolds, ListPOfCATDraftManifold &oDraft);
  static void GetDraftsManifold(const ListPOfCATDeclarativeManifold &iDMList, ListPOfCATDraftManifold &oDraftManifoldList);
  static void SortManifolds(const ListPOfCATManifold &iManifolds, ListPOfCATDeclarativeManifold &oDeclarativeManifold,ListPOfCATCellManifoldGroup &oCellManifoldGroups);

  static void GetAllFaces(ListPOfListPOfCATFace &iListOfListOfFaces, ListPOfCATFace &oListOfFaces);
  static void GetAllCellManifolds(ListPOfListPOfCATCellManifolds &iListOfListOfCellManifolds, ListPOfCATCellManifold &oListOfCellManifolds);
  static void GetAllCells(ListPOfCATCellManifold& iListOfCellManifolds, CATLISTP(CATCell)&  ioResult,  short  iDimension=-1);
  static void GetAllCells(const ListPOfCATCell &iListOfCells, ListPOfCATCell& ioResult, const short iDimension=-1);
  static void GetAllReps(ListPOfCATCellManifold &iListOfCellManifolds, CATLISTP(CATCell)&  ioResult,  short  iDimension=-1);

  static void GetAllLeaves(ListPOfCATCellManifoldGroup &iCellManifoldGroups,ListPOfCATCellManifold &oLeaves);

  static CATBoolean LocateFace(CATFace *iFace, ListPOfListPOfCATFace &iListOfListOfFaces, int &oListIndex, int &oFaceIndex);
  static CATBoolean LocateFace(CATFace *iFace, ListPOfListPOfCATDRepSeed &iListOfListOfSeeds, int &oListIndex);
  static CATBoolean LocateEdge(CATEdge *iEdge, ListPOfListPOfCATEdge &iListOfListOfEdges, int &oListIndex, int &oEdgeIndex);
  static CATBoolean LocateDM(CATDeclarativeManifold *iDM, ListPOfListPOfCATDeclarativeManifold &iListOfListOfDMs, int &oListIndex, int &oDMIndex);

  static CATBoolean AreAllFacesContainedInList(ListPOfCATFace &iFaces, ListPOfCATFace &iList);
  static CATBoolean AreAllEdgesContainedInList(ListPOfCATEdge &iEdges, ListPOfCATEdge &iList);
  static CATBoolean AreAllCellManifoldsContainedInList(ListPOfCATCellManifold &iCMs, ListPOfCATCellManifold &iList);
  static CATBoolean AreAllPersistentFacesContainedInList(ListPOfCATPersistentFaces &iPFs, ListPOfCATPersistentFaces &iList);
  static CATBoolean AreListsEquivalent(ListPOfCATEdge &iEdges1, ListPOfCATEdge &iEdges2);
  static CATBoolean AreAllBodiesContainedInList(ListPOfCATBody &iBodies, ListPOfCATBody &iList);  

  static CATBoolean IsInside(const ListPOfCATCell& iCells, CATBody& iBody);

  static void GetCellsNeighbourhood(ListPOfCATCell &iCells, CATBody &iBody, ListPOfCATCell &oNeighbourCells);
  static void GetCellsEntireNBH(ListPOfCATCell &iCells, CATBody &iBody, ListPOfCATCell &oNeighbourCells, const CATBoolean iThroughVerticesToo=FALSE);
  static void GetCellManifoldsNeighbourhood(const ListPOfCATCellManifold &iCellManifolds, CATLiveBody &iLiveBody, const CATBoolean iThroughVerticesToo, ListPOfCATCellManifold &oNeighbourCellManifolds);
  static void GetConnectedFaces(ListPOfCATFace &iFaces, CATBody &iBody, ListPOfCATFace &oConnectedFaces);
	static void GetConnectedFaces(const CATFaceHashTable &iFaceHT, CATBody &iBody, CATFaceHashTable &oConnectedFaceHT); /*with HT*/
  static void GetConnectedFaces(ListPOfCATFace &iFaces, ListPOfCATFace & iAllFaceList, ListPOfCATFace &oConnectedFaces);
  static void GetConnectedFaces(const CATFaceHashTable &iFaceHT, const CATFaceHashTable & iAllFaceHT, CATFaceHashTable &oConnectedFaceHT);
  static void RemoveUnconnected(CATLiveBody& iLiveBody, const int iListCount, ListPOfCATCellManifold iCellManifolds[]); // In every list, if CM are connected to the other lists, then remove unconnected CM
  static CATBoolean AreConnected(const ListPOfCATCellManifold& iCellManifold1, const ListPOfCATCellManifold& iCellManifold2, const CATBoolean iLowerDimToo = FALSE);
  static CATBoolean AreConnected(const ListPOfCATFace &iFaces1, const ListPOfCATFace &iFaces2);
  static CATBoolean AreConnected(const ListPOfCATEdge &iEdges1, const ListPOfCATEdge &iEdges2);
  static CATBoolean AreConnected(CATFace & iFace, ListPOfCATFace &iFaceList);
  static CATBoolean AreConnected(CATFace & iFace, const CATFaceHashTable &iFaceHT);
  static CATBoolean AreConnected(CATFace & iFace, ListPOfCATFace &iFaceList, ListPOfCATFace &oAdjacentFaceList);
  static CATBoolean AreConnected(CATFace & iFace1, CATFace &iFace2);
  static CATBoolean AreConnected(CATFace& iFace, CATCellManifold& iCellManifold);
  static CATBoolean AreConnected(CATEdge & iFirstEdge, CATEdge & iSecondEdge);
  static CATBoolean AreConnected(CATEdge & iEdge, CATEdgeHashTable & iEdgeHT);
  static CATBoolean AreConnectedBySameEdges(ListPOfCATCellManifold &iCMList);
  static CATBoolean AreConnected(const ListPOfCATCell &iCells1, const ListPOfCATCell &iCells2);
  static CATBoolean AreAtLeastTwoConnected(ListPOfCATCellManifold &iCMList);
  static CATBoolean EachCMIsConnectedToAnother(ListPOfCATCellManifold &iCMList);
  static CATBoolean GetCMConnectedToAnotherWithDifferentType(ListPOfCATCellManifold &iCMList, CATListOfShort &iCMTypeList, ListPOfCATCellManifold &oConnectedCMList, CATListOfShort &oConnectedCMTypeList);
  static CATBoolean AreAllEdgesConnected(ListPOfCATEdge &iEdges, CATBody &iBody);
  void GetConnectedFacesProvidedConvexity(ListPOfCATFace const &iFaces, CATBody &iBody, CATGeoConvexity &iConvexity, ListPOfCATFace &oConnectedFaces);
  void GetConnectedFacesProvidedSharpness(ListPOfCATFace const &iFaces, ListPOfCATFace const &iAllFaces, CATTopGeoContinuity &iContinuity, ListPOfCATFace &oConnectedFaces);
  void GetConnectedFacesProvidedSharpness(ListPOfCATFace const &iFaces, CATBody &iBody, CATTopGeoContinuity &iContinuity, ListPOfCATFace &oConnectedFaces);
  void GetConnectedFacesProvidedSharpness(CATFaceHashTable const &iFaceHT, CATBody &iBody, CATTopGeoContinuity &iContinuity, CATFaceHashTable &oConnectedFaceHT);
  void GetAllConnectedFacesProvidedSharpness(CATFace *iFace, CATBody &iBody, CATTopGeoContinuity &iContinuity, ListPOfCATFace &oConnectedFaces);//Gives G1 skin corresponding to input Face

  static double GetSquareMinDist(CATVertex *iFirstVertex, const ListPOfCATVertex &iSecondVertices);

  static void GetBorders(CATFace        &iFace, ListPOfCATEdge &oBorderEdges);
  static void GetBordersHT(CATFace      &iFace, CATEdgeHashTable &oBorderEdgeHT);
  static void GetBordersHT(const CATFaceHashTable &iFaceHT, CATEdgeHashTable &oBorderEdgeHT, CATEdgeHashTable* oNonBorderEdgeHT = NULL, const CATBoolean iIgnoreInternalLoops = FALSE, CATFaceHashTable* oBorderFaceHT = NULL);
  static void GetBorders(CATCell        &iCell, ListPOfCATCell &oBorderCells);
  static void GetBorders(CATCell        &iCell, CATCellHashTable & oBorderCellHT);
  static void GetBorders(const ListPOfCATFace &iListOfFaces, ListPOfCATEdge& oBorderEdges, ListPOfCATEdge* oNonBorderEdges = NULL, const CATBoolean iIgnoreInternalLoops = FALSE, ListPOfCATFace* oBorderFaces = NULL);
  static void GetBorders(const ListPOfCATCell &iListOfCells, ListPOfCATCell &oBorderCells);
  static void GetBorders(const CATCellManifold &iCM, ListPOfCATEdge &oBorderEdges);
  static void GetBorders(const CATDeclarativeManifold &iDM, ListPOfCATEdge &oBorderEdges);
  static void GetBorders(const ListPOfCATCellManifold &iCMs, ListPOfCATEdge &oBorderEdges);
  static void GetBorders(const ListPOfCATCellManifold &iCMs, ListPOfCATCell &oBorderCells);
  
  static void GetBoundingEdges(const ListPOfCATFace &iFaceList, CATEdgeHashTable &oBoundingEdgeHT);
  static void GetBoundingCells(const ListPOfCATCell &iCellList, ListPOfCATCell   &oBoundingCells);
  static void GetBoundingCells(const ListPOfCATCell &iCellList, CATCellHashTable &oBoundingCells);
  static void GetBoundingCells(const CATCellHashTable &iCellHT, CATCellHashTable &oBoundingCells);

  static void GetBorderEdgesInLoopOrder(ListPOfCATFace &iListOfFaces, CATBody &iBody, ListPOfListPOfCATEdge &oOrderedBorderEdges, ListPOfListPOfCATFace &oOrderedFaces);

  static void GetExtremities(const ListPOfCATEdge& iListOfEdges, ListPOfCATVertex& oVertices, ListPOfCATVertex* oNonBorderVertices=NULL, ListPOfCATEdge * oExtremityEdges=NULL);

  static void GetAdjacentEdges(CATSoftwareConfiguration *iConfig, 
                               CATVertex                &iVertex, 
                               CATBody                  &iBody, 
                               ListPOfCATEdge           &oAdjacentEdges);

  static void GetAdjacentEdges(CATSoftwareConfiguration *iConfig, 
                               CATEdge                  &iEdge, 
                               CATBody                  &iBody, 
                               ListPOfCATEdge           &oAdjacentEdges);

  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig, 
                               CATVertex                &iVertex, 
                               CATBody                  &iBody, 
                               ListPOfCATFace           &oAdjacentFaces);

  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig, 
                               ListPOfCATEdge           &iEdgeList, 
                               CATBody                  &iBody, 
                               ListPOfCATFace           &oAdjacentFaceList);

  static CATFace* GetOtherFace(CATEdge* iEdge, CATFace* iRefFace, CATBody* iBody, CATShell* iShell);

  //oSmoothSkins : Memory is allocated to create each element of this list, so client needs to free it.
  static HRESULT GetSmoothSkins(CATSoftwareConfiguration       *iConfig, 
                                CATGeoFactory                  &iFactory,
                                ListPOfCATCellManifold         &iCellManifolds,
                                CATBody                        &iBody, 
                                ListPOfListPOfCATCellManifolds &oSmoothSkins);
  
  static void GetSmoothSkinsWithAnglePropagation(CATSoftwareConfiguration       &iConfig,
                                                 CATGeoFactory                  &iFactory,
                                                 ListPOfCATFace                 &iFaces,
                                                 CATBody                        &iBody,
                                                 double                         &iSmoothAngle,
                                                 ListPOfListPOfCATFace          &oSmoothSkins);

  //oGroupsOfConnectedCellManifolds : Memory is allocated to create each element of this list, so client needs to free it.
  // @Param iDontCrossShellBorder : if TRUE, a group of ConnectedCellManifold will belong to a single shell.
  static void GetGroupsOfConnexCellManifolds(ListPOfCATCellManifold         &iCellManifolds, 
                                             CATLiveBody                    &iLiveBody,
                                             ListPOfListPOfCATCellManifolds &oGroupsOfConnectedCellManifolds,
                                             CATBoolean                      iDontCrossDomainBorder=FALSE,
                                             CATBoolean                      iThroughVertexContact=FALSE);

  //oGroupsOfConnectedFaces : Memory is allocated to create each element of this list, so client needs to free it.
  static void GetGroupsOfConnexFaces(ListPOfCATFace        &iFaces, 
                                     CATBody               &iBody, 
                                     ListPOfListPOfCATFace &oGroupsOfConnectedFaces);

  //oGroupsOfConnectedEdges : Memory is allocated to create each element of this list, so client needs to free it.
  static void GetGroupsOfConnexEdges(ListPOfCATEdge        &iEdges, 
                                     CATBody               &iBody, 
                                     ListPOfListPOfCATEdge &oGroupsOfConnectedEdges);

  static void GetGroupsOfConnexCells(
                                     ListPOfCATCell           &iCells,
                                     CATBody                  &iBody,
                                     ListPOfListPOfCATCell    &oGroupsOfConnectedCells);

  static CATShell* FindShellThatOwnsAtleastOneOfTheseFaces(ListPOfCATFace & iFaces, CATBody & iInputBody);

  static void PropagateFace(CATSoftwareConfiguration *iConfig, 
                            CATGeoFactory            &iFactory,
                            CATFace                  &iFace, 
                            CATBody                  &iBody,
                            ListPOfCATFace           &iStoppingFaces,
                            ListPOfCATFace           &oFaces);

  static void PropagateFace(CATSoftwareConfiguration *iConfig, 
                            CATGeoFactory            &iFactory,
                            ListPOfCATFace           &iFaces, 
                            CATBody                  &iBody,
                            ListPOfCATFace           &iStoppingFaces,
                            ListPOfCATFace           &oFaces);

  static void PropagateFacesAmongFaces(CATSoftwareConfiguration *iConfig, 
                                      CATGeoFactory             &iFactory,
                                      ListPOfCATFace            &iFacesToPropagate, 
                                      CATBody                   &iBody,
                                      ListPOfCATFace            &iAllFaces,
                                      ListPOfCATFace            &oFaces);

  static void PropagateCellManifold(CATSoftwareConfiguration *iConfig, 
                                     CATGeoFactory           &iFactory,
                                     CATCellManifold         &iCellManifold, 
                                     CATBody                 &iBody,
                                     ListPOfCATCellManifold  &iAllCellManifolds,
                                     ListPOfCATCellManifold  &oCellManifolds);

  
  static void PropagateCellManifold(CATSoftwareConfiguration *iConfig, 
                                     CATGeoFactory           &iFactory,
                                     ListPOfCATCellManifold  &iCellManifolds, 
                                     CATBody                 &iBody,
                                     ListPOfCATCellManifold  &iAllCellManifolds,
                                     ListPOfCATCellManifold  &oCellManifolds);

  static void PropagateEdge(CATSoftwareConfiguration *iConfig, CATGeoFactory &iFactory, CATEdge &iEdge, CATBody &iBody, ListPOfCATEdge &oEdges, CATBoolean iManualPropag=FALSE);
  static void PropagateEdge(CATSoftwareConfiguration *iConfig, CATGeoFactory &iFactory, ListPOfCATEdge &iEdges, CATBody &iBody, ListPOfCATEdge &oEdges, CATBoolean iManualPropag=FALSE);
  static void PropagateEdgeOnFaces(CATSoftwareConfiguration *iConfig, CATEdge & iEdge, ListPOfCATFace & iFaces, CATBody & iBody, ListPOfCATEdge &oEdges);

  static void PropagateEdgesAmongEdges(CATSoftwareConfiguration *iConfig,
                                       CATGeoFactory &iFactory,
                                       CATBody &iBody,
                                       ListPOfCATEdge &iEdgesToPropag,
                                       ListPOfCATEdge &iAllowedEdges,
                                       ListPOfCATEdge &oPropagatedEdges,
                                       CATBoolean iAllowFork = TRUE,
                                       ListPOfCATVertex *iStoppingVertices = NULL,
                                       CATBoolean iCheckSmooth = TRUE,
                                       double *iSmoothAngle = NULL);

  static void PropagateFacesAmongFaces(CATSoftwareConfiguration *iConfig,
                                       CATGeoFactory &iFactory,
                                       CATBody &iBody,
                                       ListPOfCATFace &iFacesToPropag,
                                       ListPOfCATFace &iAllowedFaces,
                                       ListPOfCATFace &oPropagatedFaces,
                                       ListPOfCATEdge *iStoppingEdges = NULL,
                                       CATBoolean iCheckSmooth = TRUE,
                                       double *iSmoothAngle = NULL);

  static void GetCommonEdges(CATFace &iFace1, CATFace &iFace2, ListPOfCATEdge &oCommonEdges);
  static void GetCommonEdges(ListPOfCATFace &iFaces, ListPOfCATEdge &oCommonEdges);
  static void GetCommonBoundingEdges(ListPOfCATFace &iFaces1, ListPOfCATFace &iFaces2, ListPOfCATEdge &oCommonEdges);
  static void GetCommonBoundingEdges(ListPOfCATFace &iFaces1, ListPOfCATFace &iFaces2, ListPOfCATEdge &oCommonEdges, ListPOfCATFace &oFaces1, ListPOfCATFace &oFaces2);
  // Gros problem perfo
  static void GetCommonBoundingVertices(ListPOfCATFace iFaces[2], ListPOfCATVertex &oCommonVertices); // A ne jamais utiliser, sous peine de mort. -> CATGMTopoUtilities::GetCommonBoundingVertices
  // -----------------------------------------------------------------------------------------------
  static void GetCommonBoundingVertices(CATFaceHashTable iFaceHTArray[2], CATVertexHashTable &oCommonVertexHT);
  static void GetCommonExtremityVertices(ListPOfCATEdge &iEdges1, ListPOfCATEdge &iEdges2, ListPOfCATVertex &oCommonVertices, ListPOfCATEdge &oEdges1, ListPOfCATEdge &oEdges2);

  static void GetCommonVertices(CATEdge &iEdge1, CATEdge &iEdge2, ListPOfCATVertex& oCommonVertices);
  static void GetCommonVertices(ListPOfCATCellManifold & iCMList, ListPOfCATVertex& oCommonVertices);
  static void GetCommonVertices(const ListPOfCATFace & iFaceList, ListPOfCATVertex& oCommonVertices);
  static void GetCommonVertices(CATFace &iFace1, CATFace &iFace2, ListPOfCATVertex& oCommonVertices);
  static void GetCommonVertices(CATFace &iFace1, CATFace &iFace2, CATFace &iFace3, ListPOfCATVertex& oCommonVertices);
  static void GetCommonCells(const int iNbList, ListPOfCATCellManifold iCM[], const int iCellDimension, ListPOfCATCell& oCommonBorderCells);
  static void GetCommonCellsThroughFillets(const int iNbList, ListPOfCATCellManifold iCM[], CATBody& iBody, const int iCellDimension, ListPOfCATCell& oCommonBorderCells);
  static CATVertex* GetAVertexSharedByFaceListAndAFace(ListPOfCATFace const & iFaceList, CATFace const & iFace);

  static HRESULT OrderPseudoWireEdges(ListPOfCATEdge &iPseudoWireEdges, ListPOfCATEdge &oOrderedPseudoWireEdges, 
                                      CATVertex **oStartVertex = NULL, CATVertex **oEndVertex = NULL,
                                      CATListOfInt *oEdgeOrientations=NULL);

  void FindExtremityFaceInRib(ListPOfCATEdge &iOneExtremityEdges, 
                              ListPOfCATFace &RibFaces, 
                              CATBody        *iBody, 
                              CATFace       *&oOtherExtremityFace);

  // Return :
  //  - CATUnknownContinuity if there is no common border
  //  - CATSmooth if :
  //    - iMustBeAllSmooth == TRUE and every common edge is smooth
  //    - iMustBeAllSmooth == FALSE and one common edge is smooth
  //  - CATSharp if :
  //    - iMustBeAllSmooth == TRUE and one common edge is sharp
  //    - iMustBeAllSmooth == FALSE and every common edge is sharp
  static CATTopGeoContinuity GetFrontierContinuity(CATSoftwareConfiguration &iConfig,
                                                   ListPOfCATFace &iListOfFaces1,
                                                   ListPOfCATFace &iListOfFaces2,
                                                   CATBoolean iMustBeAllSmooth = TRUE,
                                                   CATAngle *iMinSharpAngle = NULL);
  static CATTopGeoContinuity GetEdgeContinuity(CATSoftwareConfiguration &iConfig,
                                               CATBody &iBody,
                                               ListPOfCATEdge &iEdges,
                                               CATBoolean iMustBeAllSmooth = TRUE,
                                               CATAngle *iMinSharpAngle = NULL);

  static CATTopGeoContinuity GetEdgeContinuity(CATSoftwareConfiguration &iConfig,
                                               CATBody &iBody,
                                               CATEdge &iEdge,
                                               CATAngle *iMinSharpAngle = NULL);
  
  static void GetEdgesMatchingContinuity(CATSoftwareConfiguration &iConfig,
                                         CATBody &iBody,
                                         ListPOfCATEdge &iEdges,
                                         CATTopGeoContinuity iContinuityToMatch,
                                         ListPOfCATEdge &oEdgesMatchingContinuity,
                                         CATAngle *iMinSharpAngle = NULL);

/*
##=================================================================================================##

 *** Merci de n'ajouter des methodes qui ne CONCERNENT QUE NATURAL SHAPE (ou le Live).  ***
     Sinon, utilisez : CATGMTopoUtilities
     -------------------------------------------------------------------------------
##=================================================================================================##
*/

  CATTopGeoContinuity GetFrontierContinuity(CATCellManifold &iManifold1, CATCellManifold &iManifold2);
  CATTopGeoContinuity GetFrontierContinuity(ListPOfCATCellManifold &iManifolds1, ListPOfCATCellManifold &iManifolds2);
  CATTopGeoContinuity GetFrontierContinuity(ListPOfCATFace &iListOfFaces1, ListPOfCATFace &iListOfFaces2);
  CATBoolean          HaveSmoothFrontier(ListPOfCATFace &iListOfFaces1, ListPOfCATFace &iListOfFaces2);
  void                GetEdgeGlobalSharpness(CATEdge         *iEdge,
                                             CATFace         *iFace1,
                                             CATFace         *iFace2,
                                             CATTopSharpness &oSharpness,
                                             CATOrientation  *oOrientation,
                                             CATShell        *iShellOwningTheTwoFaces);

  HRESULT             GetVertexOrientedAngle(CATVertex *iVertex,
                                             CATEdge   *iEdge1,
                                             CATEdge   *iEdge2,
                                             CATFace   *iFace,
                                             CATAngle  *oAngle);

  static void UpdateEdgeWithJournal(CATEdge &iEdge, CATBody &iBody, CATCGMJournalList &iJournal, ListPOfCATEdge &oNewEdges);
  static void UpdateEdgesWithJournal(ListPOfCATEdge &iEdges, CATBody &iBody, CATCGMJournalList &iJournal, ListPOfCATEdge &oNewEdges);

  static void UpdateFaceWithJournal(CATFace &iFace, CATCGMJournalList &iJournal, ListPOfCATFace &oNewFaces);
  static void UpdateFacesWithJournal(ListPOfCATFace &iFaces, CATCGMJournalList &iJournal, ListPOfCATFace &oNewFaces);

  static void GetAdjacentFace(CATFace &iFace, CATEdge &iCommonEdge, CATBody &iBody, CATFace *&oAdjacentFace);
  static void GetAdjacentFaces(ListPOfCATFace & iFaces, CATBody & iBody, ListPOfCATFace & oAdjacentFaces);
  static void GetAdjacentFaces(CATFaceHashTable & iFaceHT, CATBody & iBody, CATFaceHashTable & oAdjacentFaceHT);
  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig, CATEdgeHashTable & iEdgeHT, CATBody & iBody, CATFaceHashTable & oAdjacentFaceHT, CATBoolean iThroughVertex=FALSE);
  static void GetSmoothAdjacentFaces(CATSoftwareConfiguration &iConfig, ListPOfCATFace &iFaces, CATBody &iBody, ListPOfCATFace &oAdjacentFaces, double *iMinSharpAngle = NULL, ListPOfCATFace *iRestrictToFaces = NULL);
  static void GetAdjacentEdgeList(ListPOfCATEdge & iEdgeList, ListPOfCATEdge & iAllEdgeList, ListPOfCATEdge & oAdjacentEdgeList);
  static void GetAdjacenteEdgHT(CATEdgeHashTable & iEdgeHT, CATEdgeHashTable & iAllEdgeHT, CATEdgeHashTable & oAdjacentEdgeHT);

  static CATBoolean IsBorderVertex(CATVertex  * iVertex, CATBody  * iBody, CATSoftwareConfiguration *iConfig);
  static CATBoolean IsBorderEdge(CATEdge  * iEdge, CATBody  * iBody);
  static CATBoolean IsVertexToBeFollowed(CATVertex  * iVertex, CATBody  * iBody, CATSoftwareConfiguration *iConfig);
  static CATBoolean IsEdgeToBeFollowed(CATEdge  * iEdge, CATBody  * iBody);
  static void GetFreeBorderEdges(ListPOfCATEdge &iEdges, CATBody &iBody, ListPOfCATEdge &oFreeBorderEdges, ListPOfCATFace &oBorderFaces); 
  static void GetFreeBorderEdges(ListPOfCATFace &iFaces, CATBody &iBody, ListPOfCATEdge &oFreeBorderEdges, ListPOfCATFace &oBorderFaces); 
  static CATBoolean IsFreeBorderFace(CATFace *iFace, CATBody *iBody);
  static CATBoolean IsFreeBorderFaces(ListPOfCATFace &iFace, CATBody &iBody);
  static CATBoolean IsFreeBorderCellManifold(CATCellManifold &iCellManifold, CATBody &iBody);//iCellManifold : dim 2
  static void RemoveBorderEdges(ListPOfCATEdge &ioEdges, CATBody *iBody);
  static CATBoolean HasFreeBorderEdges(CATDeclarativeManifold &iDeclarativeManifold, CATBody &iBody);
  static CATBoolean GetFreeBorderEdges(CATDeclarativeManifold &iDeclarativeManifold, CATBody &iBody, ListPOfCATEdge & oBorderEdges);

  CATBoolean IsThreeSidedFace(CATFace &iFace, CATBody &iBody, ListPOfCATEdge *oSides[3]);
  void GetSmoothSides(ListPOfCATFace &iFaces, CATBody &iBody, ListPOfListPOfCATEdge & oSides);

  void GetSharpBorders(ListPOfCATFace &iFaces, CATBody &iBody, ListPOfCATEdge &oSharpBorderEdges);
  void GetSmoothBorders(ListPOfCATFace &iFaces, CATBody &iBody, ListPOfCATEdge &oSmoothBorderEdges);
  void GetInternalSharpEdges(ListPOfCATFace &iFaces, ListPOfCATEdge &oInternalSharpEdges);
  static void GetInternalSmoothEdges(ListPOfCATFace &iFaces, ListPOfCATEdge &oInternalSmoothEdges, CATSoftwareConfiguration * iConfig);
  // AJT1: The optional CATBody can be specified to improve the performance
  static void GetInternalEdges(ListPOfCATFace &iFaces, ListPOfCATEdge &oInternalEdges, CATCGMHashTableWithAssoc * oInternalEdgesToAdjacentFaces=NULL, CATBody *iBody = NULL, CATBoolean iNonManifoldManagement = FALSE);

  static const CATSurface * RetrieveUnderlyingSurface(CATCell * iCell);
  static const CATSurface * RetrieveUnderlyingSurface(CATFace * iFace);

  static CATTopConvexity MatterConvexity(CATDeclarativeManifold & iDeclaration, CATBody& iBody, CATFace& iFace, CATSoftwareConfiguration* iConfig); // Hole MatterConvexity is -1

  static CATBoolean IsEdgeBoundingDifferentsGroupsThroughJournal(CATEdge *iInputEdge, CATBody *iWorkingBody, CATCGMJournalList *iJournal);

  static CATBoolean IsOffsetOfPreviousDeclarative(ListPOfCATCellManifold &iManifoldImages, CATDeclarativeManifold *iParentDM, CATLiveBody &iLiveBody, double & oOffsetValue, ListPOfCATCellManifold &ioManifoldOrigin);

  static HRESULT CreateJournalOfCellManifoldsFromJournalOfCells(CATCGMJournalList &iJournalOfCells, 
                                                                CATCGMJournalList &ioJournalOfCellManifolds,
                                                                ListPOfCATBody & iInputBodies,ListPOfCATBody & iOutputBodies);

  static HRESULT CreateJournalOfDeclarativeManifoldsFromJournalOfCellManifolds(CATCGMJournalList &iJournalOfCellManifolds, 
                                                                               CATCGMJournalList &ioJournalOfDeclarativeManifolds,
                                                                               ListPOfCATBody & iInputBodies, ListPOfCATBody & iOutputBodies);

  //Methods to follow Manifolds through MODIFICATIONS
  static void FollowManifoldList(ListPOfCATManifold &iManifoldsToFollowInInitialBody,CATLiveBody *iInitialLiveBody, CATLiveBody *iCurrentLiveBody,
                                 CATCGMJournalList *iLiveJournal,ListPOfCATManifold &oManifoldsFollowedCurrentBody,CATBoolean iImagesWithSameType);
  static void FollowDeclarativeManifoldsList(ListPOfCATDeclarativeManifold &iDeclarativeManifoldsToFollowInInitialBody,CATLiveBody *iInitialLiveBody, 
                                             CATLiveBody *iCurrentLiveBody,
                                             CATCGMJournalList *iLiveJournal, ListPOfCATDeclarativeManifold &oDeclarativeManifoldsFollowedInCurrentBody,CATBoolean iImagesWithSameType);

  static void FollowCellManifoldGroups(ListPOfCATCellManifoldGroup &iCMGToFollowInInitialBody,CATLiveBody *iInitialLiveBody, 
                                            CATLiveBody *iCurrentLiveBody,
                                            CATCGMJournalList *iLiveJournal, ListPOfCATCellManifoldGroup &oCMGFollowedInCurrentBody);
  
  static void FollowDeclarativeManifolds(CATDeclarativeManifold *iDeclarativeManifoldToFollowInInitialBody,CATLiveBody *iInitialLiveBody, 
                                         CATLiveBody *iCurrentLiveBody,
                                         CATCGMJournalList *iLiveJournal, ListPOfCATDeclarativeManifold &oDeclarativeManifoldsFollowedInCurrentBody,CATBoolean iImagesWithSameType);

  //To KNOW IF Two DEclarative have the same type
  static CATBoolean HaveDeclarativeManifoldsSameType(CATDeclarativeManifold *iDM1,CATDeclarativeManifold *iDM2);
                                            
  static void SortCellManifoldByEquivalenceClasses(ListPOfCATCellManifold &iManifoldImages, ListPOfListPOfCATCellManifolds &ioSortedManifoldImages, CATSoftwareConfiguration* iConfig);
  void CreateJournalOfCellsFromJournalOfCellManifolds(CATCGMJournalList &iJournalOfCellManifolds, CATCGMJournalList &ioJournalOfCells);

  static void ConvertListOfCellsToListOfFaces(CATLISTP(CATCell) & iListOfCellsToMove, CATLISTP(CATFace) & oListOfFacesToMove);

  static void ConvertListOfCellsToListOfEdges(CATLISTP(CATCell) & iListOfCellsToMove, CATLISTP(CATEdge) & oListOfEdgesToMove);

  static void ConvertListOfCellsToListOfVertices(CATLISTP(CATCell) & iListOfCellsToMove, CATLISTP(CATVertex) & oListOfVerticesToMove);

  static void ConvertListOfGeometriesToListOfFaces(CATLISTP(CATGeometry) & iListOfGeometriesToMove, CATLISTP(CATFace) & oListOfFacesToMove);

  static void ConvertListOfGeometriesToListOfCells(CATLISTP(CATGeometry) & iListOfGeometriesToMove, CATLISTP(CATCell) & oListOfCellsToMove);

  static void ConvertListOfFacesToListOfCells(CATLISTP(CATFace) const & iListOfFacesToMove, CATLISTP(CATCell) & oListOfCellsToMove);

  static void ConvertListOfVerticesToListOfCells(CATLISTP(CATVertex) & iListOfVerticesToMove, CATLISTP(CATCell) & oListOfCellsToMove);

  static void ConvertListOfCellManifoldToListOfGeometry(CATLISTP(CATCellManifold) & iListOfCellManifolds, CATLISTP(CATGeometry) & oListOfGeometry);

  static void ConvertListOfHGeometryToListOfGeometry(ListPOfCATHGeometry & iListOfHGeometries, CATLISTP(CATGeometry) & oListOfGeometry);

  static void ConvertListOfDeclarativeManifoldToListOfGeometry(CATLISTP(CATDeclarativeManifold) & iListOfDeclarativeManifolds, CATLISTP(CATGeometry) & oListOfGeometry);

  static void ConvertListOfCellManifoldGroupToListOfGeometry(CATLISTP(CATCellManifoldGroup) & iListOfCellManifoldGroups, CATLISTP(CATGeometry) & oListOfGeometry);

  static void ConvertListOfEdgesToListOfCells(CATLISTP(CATEdge) & iListOfEdges, CATLISTP(CATCell) & oListOfCells);

  static void ConvertListOfGeometriesToListOfCellManifolds(CATLISTP(CATGeometry) & iListOfGeoms, CATLISTP(CATCellManifold) & oListOfCMs);

  static CATBoolean AreSameLists(const ListPOfCATFace & iList1, const ListPOfCATFace & iList2);
  static CATBoolean AreSameLists(const ListPOfCATEdge & iList1, const ListPOfCATEdge & iList2);
  static CATBoolean AreSameLists(const ListPOfCATVertex & iList1, const ListPOfCATVertex & iList2);
  static CATBoolean AreSameLists(const ListPOfCATCell & iList1, const ListPOfCATCell & iList2);
  static CATBoolean AreSameLists(const ListPOfCATCell & iList1, const ListPOfCATFace & iList2);
  static CATBoolean AreSameLists(const ListPOfCATCellManifold & iList1, const ListPOfCATCellManifold & iList2);
  static CATBoolean AreSameLists(const CATLISTP(CATGeometry) & iList1, const CATLISTP(CATGeometry) & iList2);
  static CATBoolean AreSameLists(const ListPOfCATPersistentCells & iList1, const ListPOfCATPersistentCells & iList2);
  static CATBoolean AreSameLists(const CATListOfInt &iList1, const CATListOfInt & iList2);
  static CATBoolean AreSameLists(const CATListOfShort &iList1, const CATListOfShort & iList2);
  static CATBoolean AreSameLists(const CATListOfDouble &iList1, const CATListOfDouble & iList2, double iEps);
  static CATBoolean AreSameLists(const ListPOfCATDeclarativeManifold &iList1, const ListPOfCATDeclarativeManifold & iList2);
  static CATBoolean AreSameLists(const ListPOfCATDomain &iList1, const ListPOfCATDomain & iList2);

  // check if iList is included (not necessary equal) to iContainer
  static CATBoolean IsListIncluded(const ListPOfCATFace & iList, const ListPOfCATFace & iContainer);
  
  static void IntersectionListAndHT(const ListPOfCATFace & iList1, const CATFaceHashTable & iHT2, ListPOfCATFace & oList);

  static CATBoolean HaveCommonElements(ListPOfCATVertex& iList1, ListPOfCATVertex& iList2);
  static CATBoolean HaveCommonElements(ListPOfCATEdge& iList1, ListPOfCATEdge& iList2);
  static CATBoolean HaveCommonElements(ListPOfCATFace& iList1, ListPOfCATFace& iList2);
  static CATBoolean HaveCommonElements(ListPOfCATCell& iList1, ListPOfCATCell& iList2);
  static CATBoolean HaveCommonElements(ListPOfCATCellManifold& iList1, ListPOfCATCellManifold& iList2);

  /** You can use CATLSOHashTable<> instead of the following methods, it will be easier **/
  static CATCGMHashTable * CreateHT(const ListPOfCATCell & iList);
  static CATCGMHashTable * CreateCMHT(const ListPOfCATCellManifold & iList);
  static CATCGMHashTable * CreateDMHT(const ListPOfCATDeclarativeManifold & iList);
  static CATCGMHashTable * CreateFaceHT(const ListPOfCATFace & iList);
  static ListPOfCATCell  * CreateList(const CATCGMHashTable * iHT);
  static ListPOfCATCellManifold        * CreateCMList(const CATCGMHashTable * iHT);
  static ListPOfCATDeclarativeManifold * CreateDMList(const CATCGMHashTable * iHT);
  static ListPOfCATFace                * CreateFaceList(const CATCGMHashTable * iHT);
  /* ------------------------------------------------------------------------------ */

  static void Add             (CATCGMHashTable * ioHT1, const CATCGMHashTable * iHT2);
  static void AddToHashTable  (CATCellHashTable &ioCellHashTable, const ListPOfCATCell &iCellList);
  static void AddToHashTable  (CATCGMHashTable &ioFacesHashTable, const ListPOfCATFace &iFaceList); // avoid duplicates
  static void AddToHashTable  (CATCGMHashTable &ioCMGsHashTable, const ListPOfCATCellManifoldGroup &iCMGList); // avoid duplicates
  static void AppendHashTable (ListPOfCATFace &ioListOfFace, const CATCGMHashTable * iCATFaceHashTable); // no check. Assurez vous que iCATFaceHashTable ne contient que des faces

  static void AppendWithoutDuplicates(ListPOfCATFace &ioFaceList, const ListPOfCATFace &iAddList);
  static void AppendWithoutDuplicates(ListPOfCATCell &ioCellList, const ListPOfCATCell &iAddList);
  static void AppendWithoutDuplicates(ListPOfCATCellManifoldGroup &ioCMGList, const ListPOfCATCellManifoldGroup &iAddList);
  static void Substract(CATCGMHashTable * ioHT1, const CATCGMHashTable * iHT2);
  static void Substract(ListPOfCATCell & ioList1, const ListPOfCATCell & iList2); // JJ3 : creation de cette methode car je suspect la methode par defaut d'etre en N2
  static void Substract(ListPOfCATCell & ioList1, const CATCGMHashTable * iHT2);
  static CATCGMHashTable * Intersection(const CATCGMHashTable * iHT1, const CATCGMHashTable * iHT2);
  static CATBoolean HaveCommonElements(const CATCGMHashTable * iHT1, const CATCGMHashTable * iHT2);
  static void GetConnexeComponents(ListPOfCATCell & iFacesList, CATLISTP(ListPOfCATCell)  & oConnexeComponents);
  static void RemoveDuplicates(ListPOfCATCell & ioCellList);
  static void RemoveCMDuplicates(ListPOfCATCellManifold & ioCMList);
  static void RemoveDMDuplicates(ListPOfCATDeclarativeManifold & ioDMList);
  static void RemoveFaceDuplicates(ListPOfCATFace & ioFaceList);

  static CATBoolean IsAJournalOfCells(CATCGMJournalList * iJournal);
  static void FindFirsts(CATCell * iCell, CATCGMJournalList * iJournal, CATLISTP(CATCell) & oOriginCells);
  static void FindLasts(CATCell * iCell, CATCGMJournalList * iJournal, CATLISTP(CATCell) & oNewCells);

  static void FindLastCells(CATLISTP(CATCell) & iCells, CATCGMJournalList * iJournal, CATLISTP(CATCell) & oCells);
  static void GetFirstsCellsFromCellManifold(CATCellManifold * iCellManifold, CATCGMJournalList * iJournal, CATLISTP(CATCell) & oCells);
  static void GetLastFaces(CATLISTP(CATFace) & iFaces, CATCGMJournalList * iJournal, CATLISTP(CATFace) & oFaces);
  static void GetCreatedCellManifolds(CATCGMJournalList * iJournal,ListPOfCATCellManifold &oCreatedCellManifolds);
  static CATCGMJournalList * DeleteCreationOrder(CATCGMJournalList * iJournal);
  static void GetNewRepresentation(CATLISTP(CATFace) & iFaces,CATPersistentBody * iOriginalPersistentBody, CATPersistentBody * iPersistentBody, CATPersistentCellInfra & iPersistentInfra, CATLISTP(CATFace) & oFaces,CATBoolean iThroughCreationOrdersToo=FALSE);
  static void ComputeImage(CATCloneManager& iCloner, const ListPOfCATFace& iFaces, ListPOfCATFace& oFaces);
  static void ComputeImage(CATCloneManager& iCloner, const ListPOfCATCellManifold& iCMs, ListPOfCATCellManifold& oCMs);
  static void ComputeImage(CATCloneManager& iCloner, const ListPOfCATPrototypeExtrusion& iPrototypes, ListPOfCATPrototypeExtrusion& oPrototypes);
  static void GetCreatedPersistentFaceList(ListPOfCATPersistentFaces & iPFaceList, CATPersistentCellInfra & iPersistentInfra, ListPOfCATPersistentFaces & oPFaceList, int iInfoType=0);

  static CATEdge * GetCommonEdgeFromFaces(CATLISTP(CATFace) & iFaces);
  static void GetCommonEdgesFromFaces(CATLISTP(CATFace) & iFaces, ListPOfCATEdge & oBorderEdges);
  static void GetCommonVerticeFromEdges(CATLISTP(CATEdge) & iEdges, ListPOfCATVertex & oCommonVertices);
  static void GetCommonEdgesFromCellManifolds(CATLISTP(CATCellManifold) & iCMList, ListPOfCATEdge & oBorderEdges);

  static CATCellManifold * GetImageCellManifold(CATCellManifold * iCellManifold, CATCGMJournalList * iJournal, CATCGMJournalRequest iRequest = ThroughCreateAndModify);
  static void GetImageCellManifold(const ListPOfCATCellManifold& iCellManifold, CATCGMJournalList* iJournal, ListPOfCATCellManifold& oCellManifold, CATCGMJournalRequest iRequest = ThroughCreateAndModify);
  static HRESULT GetImageCellManifold(ListPOfCATCellManifold& iCellManifold, CATPersistentCellInfra& iInfra,CATPersistentBody *iOriginBody,  CATPersistentBody& iTargetBody, ListPOfCATCellManifold& oCellManifold);

  static HRESULT GetImageAndAncestorCellManifold(ListPOfCATCellManifold& iCellManifold, CATPersistentCellInfra& iInfra, CATPersistentBody &iPBody, CATPersistentBody& iTargetBody, ListPOfCATCellManifold& oCellManifold,CATBoolean iWithByCreation=FALSE);
  static HRESULT GetImageCellManifoldWithType(ListPOfCATCellManifold& iCellManifold, CATPersistentCellInfra& iInfra, CATPersistentBody& iInputBody, CATPersistentBody& iTargetBody, ListPOfCATCellManifold& oCellManifold, int iType=-2);
  static void GetParentCellManifold(CATCellManifold & iCellManifold, CATPersistentCellInfra& iInfra, CATPersistentBody& iInputBody, CATPersistentBody& iTargetBody, ListPOfCATCellManifold& oCellManifold, int iType);

  static void AddCellManifoldImage(CATCGMJournalList* ioJournal, CATLISTP(CATCellManifold)& iParentCellManifolds, CATLISTP(CATCellManifold)& iChildrenManifolds, const int iInfo, const CATCGMJournal::Type iType=CATCGMJournal::Creation);

  static HRESULT XScaleDRep(CATTransfoManager& iTransfoManager, CATLISTP(CATICGMObject)& iTransformed); // For CATCGMODTScaleManager only
  static HRESULT PropagateDRep(CATSoftwareConfiguration *iConfig, CATTransfoManager& iTransfoManager, CATLISTP(CATICGMObject)& iTransformed, CATMapVoidToVoid* oMap=NULL); 

  // IZE SpecChg Management
  // new
  static HRESULT ExtractRequiredParameters(CATDeclarativeManifold* ipDM, CATLONG32 iKey, ListPOfCATManifoldBaseParameter & ioBaseParamList);  
  static HRESULT ExtractSpecChgFromParam(CATDeclarativeManifold* ipDM, CATManifoldBaseParameter * iParamToFind, CATLISTP(CATCGMAttribute) & ioSpecChg);
  // deprecated
  static HRESULT ExtractRequiredParameters(CATDeclarativeManifold* ipDM, CATLONG32 iKey, ListPOfCATManifoldParameter & ioParamList);
  static HRESULT ExtractSpecChgFromParam(CATDeclarativeManifold* ipDM, CATManifoldParameter * iParamToFind, CATLISTP(CATCGMAttribute) & ioSpecChg);

  static CATBoolean IsEditingChamfer(ListPOfCATManifoldParameter & iParamList);

  //ST5 Wk24-2014: Returns all inner located edges for each Face in the list
  static void GetEdgesFromInnerLoop(ListPOfCATFace &iFaces, ListPOfCATEdge &oEdges);
  static void GetEdgesFromOuterLoop(ListPOfCATFace &iFaces, ListPOfCATEdge &oEdges);
  static void GetEdgeFromOuterLoop(CATFace * iFace, ListPOfCATEdge & oEdges);
  static void GetEdgeFromOuterLoop(CATCellManifold * iCM, ListPOfCATEdge & oEdges);
  static void GetEdgeFromOuterLoop(CATCellManifold * iCM, ListPOfCATEdge & oEdges, ListPOfCATFace & oBoundedFaceList);//oBoundedFaceList parallel to oEdges
  // Appends to the incoming list ioFaces.
  static void GetFacesFromOuterShell(CATVolume * iVolume, ListPOfCATFace & ioFaces);
  static void InitDebugTools(); 
  static void SelectFacesFromBody(CATBody * iBody, ListPOfCATFace & iFaces, ListPOfCATFace & oFaces);
  static void SelectFacesFromBody(CATBody * iBody, CATFaceHashTable &iFaces, CATFaceHashTable & oFaces);
  static void DumpCDMMirror(CATCDMBaseServices * iCDMBaseServices, CATCGMOutput & iOS);
  
  static void RemoveValues(ListPOfCATEdge & ioRefEdgeList, ListPOfCATEdge & iEdgeList);
  static void RemoveValues(ListPOfCATCell & ioRefCellList, ListPOfCATCell & iCellList);
  static void RemoveValues(ListPOfCATCellManifold & ioRefCMList, ListPOfCATCellManifold & iCMList);
  static void RemoveValues(ListPOfCATFace & ioRefFaceList, ListPOfCATFace & iFaceList);
  static void RemoveValues(ListPOfCATDomain & ioRefDomainList, ListPOfCATDomain & iDomainList);
  static void RemoveValues(ListPOfCATPersistentFaces & ioRefPFaceList, ListPOfCATPersistentFaces & iPFaceList);
  static void RemoveValues(ListPOfCATPersistentEdges & ioRefPEdgeList, ListPOfCATPersistentEdges & iPEdgeList);
  static void RemoveValues(ListPOfCATPersistentCells & ioRefPCellList, ListPOfCATPersistentCells & iPCellList);
  static void RemoveValues(ListPOfCATCellManifoldGroup & ioRefCMGList, ListPOfCATCellManifoldGroup & iCMGList);

  static CATDeclarativeManifold * GetDeclarativeManifoldFromCellAndListOfBodies(CATCell * iCell, CATLISTP(CATBody) & iBodies);
  static void GetTwoMinIndices(CATListOfDouble & iDistanceList, int & oIndFirstMin, int & oIndSecondMin);
  static void ComputeDistanceBetweenTwoBodies(CATBody * iFirstBody, CATBody * iSecondBody, double & oCurdistance);
  static CATBoolean HasPattern(CATBody  * iBody);
  static CATBoolean IsClosedSkin(CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);
  static CATBoolean IsClosedSkinExist(CATPersistentBody * iPersistentBody, CATlsoPersistentContext & iContext);
  static void GetCommonEdgesBetweenTwofaces(ListPOfCATFace & iFaceList, ListPOfCATEdge & oEdgeList);
  static void GetBodiesFromPersistentBodies(ListPOfCATPersistentBodies & iPersistentBodyList, ListPOfCATBody & oBodyList, CATPersistentCellInfra & iPersistentInfra);

  static CATDomain *  GetLumpDomainFromVolume(CATVolume * iVol, CATBody * iBody);

  //Journal Change
  static void ChangeJournalInputBodyToCopyInput(CATCGMJournalList &ioJournalToChange,CATPersistentBody *iInputNoCopyPersistentBody,CATPersistentCellInfra &iPersistentInfra);
  static void ChangeJournalInputBodyToCopyInput(CATCGMJournalList &ioJournalToChange,const ListPOfCATPersistentBodies &iInputNoCopyPersistentBodies,CATPersistentCellInfra &iPersistentInfra);
  static void ChangeJournalInputBodyToCopyInputWithCreatedCellsToKeep(CATCGMJournalList &ioJournalToChange,const ListPOfCATPersistentBodies &iInputNoCopyPersistentBodies,CATPersistentCellInfra &iPersistentInfra,ListPOfCATCell &iCreatedCellsToKeepAsCreated);
  //if Cell A has several images, the ones having also in their parents the iSortingCells are set as modified, the others as created
  static void ChangeJournalInputBodyToCopyInputWithSortingCellsInCaseOfMultipleImages(CATCGMJournalList &ioJournalToChange,const ListPOfCATPersistentBodies &iInputNoCopyPersistentBodies,CATPersistentCellInfra &iPersistentInfra,ListPOfCATCell &iSortingCells);
  // -----------
  // CreateBody
  // -----------
  static CATPersistentBody * CreateNewPersistentBodyByMergingPersistentBodyList(const ListPOfCATPersistentBodies &iPersistentBodyList,
                                                                                CATlsoPersistentContext    &iContext,
                                                                                CATBoolean                  iManageManifold = FALSE,
                                                                                const CATPGMDRepBehavior *  ipDRepBehavior=NULL);

  static CATBody * CreateNewBodyByMergingBodyList(const ListPOfCATBody     & iBodiesList,
                                                  CATSoftwareConfiguration * iConfig,
                                                  CATBoolean                 iManageManifold,
                                                  const CATPGMDRepBehavior * ipDRepBehavior);
  
  static CATBody * CreateNewBodyWithDomainList(const ListPOfCATDomain   &iDomainList,
                                               CATSoftwareConfiguration *iConfig,
                                               CATGeoFactory            *iFactory,
                                               CATBoolean                iManageManifold,
                                               const CATPGMDRepBehavior *ipDRepBehavior=NULL, // Mandatory if iManageManifold is TRUE.
                                               ListPOfCATBody           *ipBodiesList=NULL,
                                               CATCGMJournalList        *oJournal=NULL);

  static CATBody * CreateNewBodyWithDomainList(const ListPOfCATDomain      & iDomainList,
                                               CATSoftwareConfiguration * iConfig,
                                               CATGeoFactory            * iFactory,
                                               CATBoolean                 iManageManifold,
                                               ListPOfCATPersistentBodies &iInputPBodies,
                                               CATPersistentCellInfra     &iInfra,
                                               CATCGMJournalList        * oJournal);


  static HRESULT CreateManifoldImage(CATGeoFactory            *iFactory,
                                     CATSoftwareConfiguration *iConfig,
                                     const ListPOfCATBody     &iInputBodies,
                                     const CATPGMDRepBehavior *ipDRepBehavior,
                                     CATBody                 *&ioOutputBody,
                                     CATCGMJournalList       * oCMJournal=NULL);

  static CATBoolean AllCellsHaveSameGeometry(ListPOfCATCellManifold & firstManifolds, ListPOfCATCellManifold & secondManifolds);
  static CATBoolean AreSameMathPlaneList(CATLISTP(CATMathPlane) & iPlaneListA, CATLISTP(CATMathPlane) & iPlaneListB, CATGeoFactory * iFactory);
  static void GetVerticesFromIntersectionHVertex(CATIntersectionHVertex * iIntersectionHVertex, CATBoneFillet * iBF, ListPOfCATVertex & oVertexList);
  static HRESULT GetAngleFromEdge(CATEdge & iEdge, CATBody & iBody, double & oAngle);
  static HRESULT GetAngleFromMathPlanes(CATMathPlane & iMP1,CATMathPlane & iMP2, double & oAngle);
  static CATBoolean AreOrthogonalMathPlanes(CATMathPlane & iMP1,CATMathPlane & iMP2);
  static CATBoolean FromSameOperator(CATGMLiveContextualFeatureFollower * iFollower, int iNumOperator);
  static void GetAllSons(CATCellManifoldGroup & iCMG, CATLISTP(CATCellManifoldGroup) & oSons);

  //Fillet util
  static void GetCommonJoints(ListPOfCATBoneFillet &iBoneFillets,CATLiveBody *iLiveContainer,ListPOfCATJointFillet &oCommonJointFillets);

  // Returns the UV bounding box, with respect to the surface of iFace, of the vertex iCommonVertex.
  static void GetVertex2DBoundingBox(CATFace &iFace, CATVertex &iCommonVertex, CATSurLimits &oBoundingBox);
  static void GetLyingOnFacesFromWire(CATWire & iWire, CATBody & iBody, ListPOfCATFace & oLyingOnFaceList);
  static void GetBorderEdgeList(CATBody & iBody, ListPOfCATEdge & oBorderEdgeList, ListPOfCATFace * oBorderFaceList=NULL);//oBorderFaceList parallel to oBorderEdgeList if oBorderFaceList exists
  static void DumpStringInFile(const CATString* iToDump, const char* iFile);
  static void GetAllDomainLiveBodies(CATPersistentBody * iPersistentBody,  CATlsoPersistentContext & iContext, ListPOfCATPersistentBodies & oPersistentBodyDomainList, CATLISTP(CATCGMJournalList) & oManifoldJournalList);
  static void GetCellList(ListPOfListPOfCATCell & iCellListOfList, ListPOfCATCell & oCellList);
  static void GetConnectedCellManifolds(const ListPOfCATCellManifold & iToCheckCMList, const ListPOfCATCellManifold & iRefCMList, ListPOfCATCellManifold & oConnectedCMList);
  static CATPersistentBody * ExtractVolumicToSurfacic(CATPersistentBody * iNewRefOnTouchedArea, CATlsoPersistentContext * iContext,CATBoolean iCreateLiveResult=FALSE);
  static CATBoolean AtLeastOneOuterDomain(CATLISTP(CATDomain) & iDomainList);
  static double CalculateLengthOfFeatureAlongAnAxis(CATGeoFactory & iFactory, CATSoftwareConfiguration * iConfig, ListPOfCATFace const & iFaces, CATMathLine const & iAxis, CATMathPoint & oAxisOrigin); // PKC 17/09/19
  static double Average(CATListOfDouble & iDoubleList);
  static CATBoolean AreAllDomainsContainedInList(ListPOfCATDomain &iDomainList, ListPOfCATDomain &iList);

  static HRESULT GetTargetFeatureSpec(CATDeclarativeManifold* iDM, int iNumOperatorId, CATGMSpecInfra * iSpecInfra, int& oFeatureType, CATBoolean& oFeatureTypeForbidden);
  static HRESULT GetAdmissibleTargetFeatureSpec(CATDeclarativeManifold* iDM, CATLiveBody &iLiveBody, CATlsoPersistentContext & iContext, int iNumOperatorId, CATGMSpecInfra * iSpecInfra, int& oFeatureType, CATBoolean& oFeatureTypeForbidden);
  static CATBoolean AreSmoothlyConnectedByFillets(CATBody & iBody, CATFace & iFace, CATFace & iSmoothlyConnectedFace, ListPOfCATFace & iAllSmoothFaces);

  static CATBoolean ContainsCylinderOrSphere(CATLiveBody * iLiveBody, CATSoftwareConfiguration * iConfig);
  
  static CATBoolean IsSphere(CATBody * iBody, CATSoftwareConfiguration * iConfig, CATGeoFactory * iFactory);

  //Utilitaires NotUpToDate
  static void GetNotUpToDateDeclarativeManifolds(CATCGMJournalList &iLiveJournal,ListPOfCATDeclarativeManifold &oNotUpToDateDeclarativeManifoldParents);
  static void SetUpToDateStatus(ListPOfCATCellManifold & iCellManifoldList, CATCellManifoldHashTable * iCMInCollision, CATDMUpToDateStatus iStatus);
  static void SetUpToDateStatus(ListPOfCATCellManifold & iCellManifoldList, ListPOfCATCellManifold & iCMInCollision, CATDMUpToDateStatus iStatus);

  //CreateOBB
  static void CreateBox( CATGeoFactory &iFactory, CATMathAdvancedBox & iBox, CATlsoDataCache & iDataCache, int iR = -1, int iG = -1, int iB = -1 );
  static void CreateBox( CATGeoFactory &iFactory, const CATMathOBB &iBox, CATlsoDataCache & iDataCache, int iR, int iG, int iB );

  static CATCircle * GetCircle(CATEdge * iEdge, CATFace * iBoundedFace, CATGeoFactory * iFactory, CATBoolean & oNeedToRemoveCircle, CATSoftwareConfiguration * iConfig); // PKC 17/07/19

  static CATSphereManifold * GetUniqueSphereManifold(ListPOfCATCellManifold & iCMList);

  static CATBoolean AreConfusedCMGeoms(CATGeometry * iGeom1, CATGeometry * iGeom2, CATGeoFactory & iFactory, CATSoftwareConfiguration & iConfig);
  static CATBoolean AreConfusedFaces(CATFace * iFace1, CATFace * iFace2, CATGeoFactory & iFactory, CATSoftwareConfiguration & iConfig);
  static CATBoolean AreConfusedVertexList(ListPOfCATVertex & iVertexList1, ListPOfCATVertex & iVertexList2, double iEps);

  static void GetFacesFromOnlyOneParent(CATCGMJournalList * iJournal, ListPOfCATFace & oFaceList);

  static void GetPlaneLimits(CATGeoFactory & iFactory, CATMathPlane & iMathPlane, CATMathBox & iLimitingBox, CATMathPoint & oLowPoint, CATMathPoint & oHighPoint);

  static void ComputeCenter(ListPOfCATFace & iFaceList, CATMathPoint & oMathPoint);

  static CATBoolean OnlyOnOnePlaneBody(CATBody * iBody);

  static void GetPathFaceListThrowRibbons(ListPOfCATFace iFaceList1, ListPOfCATFace iFaceList2, CATLiveBody & iLiveBody, CATSoftwareConfiguration * iConfig, ListPOfCATFace & oPathFaceList);

  static void GetNeighboorFaceListThrowRibbons(ListPOfCATFace & iFaceList1, CATLiveBody & iLiveBody, ListPOfCATFace & oNeighboorFaceList, ListPOfCATFace & oRibbonsFaceList);

  static void GetNeighboorFaceHTThrowRibbons(CATFace * iFace, CATLiveBody & iLiveBody, CATFaceHashTable & oNeighboorFaceList, CATFaceHashTable & oRibbonsFaceList); /*using HT*/

	// Get adjacent faces through ribbons with HT with assoc. s.t. (item, assoc) with item: CATFace * neighboorFace assoc: CATFaceHashTable of ribbon adjacent to item 
	static void GetNeighboorFaceHTThroughRibbons(const CATFaceHashTable &	iFaceHT, CATLiveBody	* ipLiveBody, CATCGMHashTableWithAssoc & oNeighboorFacesWithAssocRibbonsHT);

  static void GetBoundingBoxFromListOfFaces(ListPOfCATFace & iListOfFaces, CATMathBox & oBB);

  static void EvalAverageNormal(ListPOfCATFace & iFaceList, CATBody & iBody, CATMathVector & oAverageNormalVector, CATMathPoint & oAverageCenter);

  static void EvalNormal(CATFace & iFace, CATBody & iBody, CATSurParam & iParam, CATMathVector & oNormalVector);

  static void GetTopCellManifoldGroups(CATLiveBody & iLiveBody, ListPOfCATCellManifoldGroup & oTopManifoldGroups);

  static CATBoolean IsClosableSurface(CATSurface * iSurface, int iLevel=0/*for recursivity*/);

  static void ComputeOBBCloudFromCellHT(CATCellHashTable & iCellsHT, CATMathOBBCloud & ioOBBCloud);

  static void GetImpactedByOBBCloudFaceList(CATBody & iBody, CATGeoFactory & iFactory, CATMathOBBCloud & iOBBCloud, ListPOfCATFace & oImpactedFaceList);
  static void GetImpactedByBBFaceList(CATBody & iBody, CATMathBox & iBox, ListPOfCATFace & oImpactedFaceList);
  static void GetImpactedByBBFaceHT(CATBody & iBody, CATMathBox & iBox, CATFaceHashTable & oImpactedFaceHT);
  static void GetImpactedByBBFaceHT(CATFaceHashTable & iFaceHT, CATMathBox & iBox, CATFaceHashTable & oImpactedFaceHT);

  static CATBoolean HasOnlyNullElements(ListPOfListPOfCATCellManifolds & iListOfList);
  static void ModifyCuttingEdgeForForceFilletTest(ListPOfCATCell & iCellList, ListPOfCATEdge & ioCuttingEdges);

  static void FilterForForceFilletTest(ListPOfCATFace & ioFaceList);

  static void FilterForForceFilletTest(ListPOfCATCellManifold & ioCMList);

  static void FilterForForceFilletTest(CATLSOHashTable<CATCellManifold> & ioCellManifoldHT);
  static void GetConnectedCellManifoldsThroughVertices(CATLiveBody & iLiveBody, ListPOfCATCellManifold & iCMList, ListPOfCATCellManifold & oConnectedCMList);
  static HRESULT GetConnectedCellManifoldsThroughBoneFillet(CATLiveBody & iLiveBody, ListPOfCATCellManifold & iCMList, ListPOfCATCellManifold & oConnectedCMList);
  static double ComputeEdgeLength(CATEdge *iEdge, CATSoftwareConfiguration *iSoftwareConfig);
  static double ComputeEdgeLength(CATLISTP(CATEdge) &iListOfEdge, CATSoftwareConfiguration *iSoftwareConfig);

  static void GetNeighborEdgeInUnorderedPseudoWire(CATSoftwareConfiguration &iConfig,
                                                   CATBody &iBody,
                                                   ListPOfCATEdge &iPseudoWire,
                                                   CATEdge &iEdge,
                                                   CATVertex &iEdgeBorder,
                                                   CATEdge *&oNeighborEdge);

  static void GetGroupsOfSmoothConnexEdges(CATSoftwareConfiguration &iConfig,
                                           CATBody &iBody,
                                           ListPOfCATEdge &iEdges,
                                           ListPOfListPOfCATEdge &oGroupsOfConnectedEdges);

  static void EstimateBodyCenterThroughFaceCenter(CATBody * iBody, CATMathPoint & oCenter);

  static int GetNbSharpVertices(CATFace * iFace);

  static void GetCommonAdjacentFaces(ListPOfCATFace & iFaceList, CATBody & iBody, ListPOfCATFace & oAdjacentFaceList);

  static void FillTheGaps(CATBody & iBody, CATSoftwareConfiguration * iConfig, CATGeoFactory & iFactory, CATFaceHashTable & ioFaceHT);

  static void GetVolumeWithFaces(CATBody * ipBody, ListPOfCATFace & iFaces, ListPOfCATCell & oCells);
  static void GetVolumeWithFaces(CATBody * ipBody, CATFaceHashTable & iFaces, CATCellHashTable & oCells);

  static void GetAllContexts(CATFaceHashTable & iFaceHT, CATLiveBody & iLiveBody, CATFaceHashTable & oContextFaceHT, CATBoolean * oFarContext = NULL);

  static void ExtendTroughDeclarativeManifolds_ForLocalBuild(CATFaceHashTable & iFaceHT, CATLiveBody & iLiveBody, CATFaceHashTable & oDMFaceHT, CATBoolean iDeepPropagation=FALSE);
  static void GetDependencies(ListPOfCATCellManifold & iCMList, ListPOfCATContextualManifold & oContextualManifoldList);

  static void ActivateHGeometryDependencies(CATSoftwareConfiguration & iConfig, CATLiveBody & iLiveBody);

  static void GetShellDomainListFromEdge(CATEdge & iEdge, CATBody & iBody, CATLISTP(CATDomain) & oShellDomainList);

  // Some Draft Utilities (YSY2)
  static void GetUniqueNeutralGeomRepFromDraftManifold(const CATDraftManifold * iDraftManifold, CATSurface *&oNeutralGeomRep);
  static void GetNeutralFaceListFromDraftManifold(const CATDraftManifold * iDraftManifold, ListPOfCATFace & oNeutralFaceList);
/*
##=================================================================================================##

 *** Merci de n'ajouter des methodes qui ne CONCERNENT QUE NATURAL SHAPE (ou le Live).  ***
     Sinon, utilisez : CATGMTopoUtilities
     -------------------------------------------------------------------------------
##=================================================================================================##
*/


private:
  CATSoftwareConfiguration * _SoftwareConfiguration;
  
  // iWhatToMatch = 1 means it will match the continuity
  // iWhatToMatch = 2 means it will match the convexity
  // otherwise, it will throw
  void GetConnectedFacesProvidedContinuityOrConvexity(ListPOfCATFace const &iFaces, CATBody &iBody, CATTopSharpness &iSharpness, ListPOfCATFace &oConnectedFaces, int iWhatToMatch);
  static void PropagateEdgeOnceOnFaces(
    CATSoftwareConfiguration  * iConfig, 
    CATEdge                   & iEdge,
    CATVertex                 & iVertex,
    ListPOfCATEdge            & iAllowedEdges,
    CATBody                   & iBody, 
    ListPOfCATEdge            & oPropagatedEdges,
    ListPOfCATVertex          & oPropagatedVertices);

  static CATBody* CreateBodyForCalculatingLength(ListPOfCATFace const     & HoleFaces,
                                                 CATSoftwareConfiguration * iConfig,  // PKC 17/09/2019 on rajoute config
                                                 CATGeoFactory            & iFactory);
  static double CalculateLengthOfBody(CATBody* iBody, CATSoftwareConfiguration * iConfig, CATMathLine const & iAxis, CATMathPoint & oAxisOrigin);
  //Main method
  static void ChangeJournalInputBodyToCopyInputMain(CATCGMJournalList &ioJournalToChange,const ListPOfCATPersistentBodies &iInputNoCopyPersistentBodies,CATPersistentCellInfra &iPersistentInfra, ListPOfCATCell &iCreatedCellsToKeepAsCreated);
  static CATBody * CreateNewBodyWithDomainListMain(const ListPOfCATDomain      & iDomainList,
                                                   CATSoftwareConfiguration * iConfig,
                                                   CATGeoFactory            * iFactory,
                                                   CATBoolean                 iManageManifold,
                                                   const CATPGMDRepBehavior * ipDRepBehavior,
                                                   ListPOfCATBody           * ipBodiesList);

 public:
  //DSH1 Start April 2017
  /**
  * Method for Sorting Faces
  * This method sorts the list of face <ioListOfFaces> 
  * in order to each face is connex with the
  * next one.
  * <oIsClosed> is equals to 1 if the ribbons is
  * closed and 0 if it is opened.
  * <iFirstFace> allows to fix the first face
  *  of the face ribbon 
  */
  static HRESULT SortFaces (ListPOfCATFace& ioListOfFaces, int& oIsClosed,CATSoftwareConfiguration *iConfig, CATFace* iFirstFace = NULL);

  /**
  * Method to Analyse Connexity
  * This methods analyses the connexity between 
  * the faces <iFace1> and <iFace2> and returns
  * the list of common edges.
  * @param oIsConnex (int&) : 1 if the faces are adjacent and returns 0 in the other case
  * @paramo IsSmoothFrontier : TRUE if continuity is of type CATSmooth
  */
  static HRESULT AnalyseConnexity (CATFace* iFace1, CATFace* iFace2, CATLISTP(CATEdge)& oListOfCommonEdges, int& oIsConnex, CATBoolean & oIsSmoothFrontier,CATSoftwareConfiguration *iConfig);

  /*
  * Method GetSortedGroupsOfConnexFaces
  * This method groups connex faces and and sorts them and groups them further if morethan two faces are meeting
  * at junction.
  * <iFaces> is input list of faces
  * <oGroupsOfConnectedFaces> is list of grouped Faces.
  */
  //oGroupsOfConnectedFaces : Memory is allocated to create each element of this list, so client needs to free it.
  static void GetSortedGroupsOfConnexFaces(ListPOfCATFace &iFaces, 
                                            CATBody &iBody, 
                                            ListPOfListPOfCATFace &oGroupsOfConnectedFaces,CATSoftwareConfiguration *iConfig);
  /**
  * Method to Sort and Group Faces
  * This method Sorts faces using SortFaces method and groups them if more than two faces are meeting at junction
  * <iListOfFaces> is input list of faces to be sorted and grouped
  * <oGroupsOfFaces> is list of grouped faces.
  */ 

  static HRESULT SortAndGroupFaces(ListPOfCATFace iListOfFaces, ListPOfListPOfCATFace &oGroupsOfFaces,CATSoftwareConfiguration *iConfig);
  
  
  /**
  * Method AnalyseConnexity
  * This methods analyses the connexity between 
  * the edges <iEdge1> and <iEdge2> and returns
  * the common evertex.
  * It returns 1 if the edges are adjacent and returns
  * 0 in the other case.
  *
  * @param iEdge1 (CATEdge*) : 
  * @param iEdge2 (CATEdge*) : 
  * @param oVertex (CATVertex* &) : 
  * @param oIsConnex (int&) : 
  * @param iTolerance (double) : the distance tolerancy between two edge point
  * iEdge1   iEdge2
  * @return HRESULT : 
  */
  static HRESULT AnalyseConnexity (CATEdge*  iEdge1, CATEdge*  iEdge2, CATVertex* & oVertex, int&  oIsConnex, double iTolerance = -1);
//DSH1 End April 2017

//For specicifc use for CATDraftManifold
//if shell orientation of both bodies are not along same direction, Draft angle sign should be changed
//iOldFaces : RepFaces corresponding to DraftManifold on ipOldBody
//iNewFaces : RepFaces corresponding to DraftManifold on ipNewBody
  static CATBoolean ChangeDraftAngleSignIfRequired(CATBody* ipOldBody, CATBody* ipNewBody, const ListPOfCATFace& iOldFaces, const ListPOfCATFace& iNewFaces); //DSH1 May 2021

  
};

#endif 

