#ifndef CATGMFilletSupportSider_H
#define CATGMFilletSupportSider_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"

#include "CATGeoFactory.h"
#include "CATSoftwareConfiguration.h"
#include "CATMath.h"
#include "CATMathFP.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"
#include "CATBody.h"
#include "CATCell.h"
#include "CATFace.h"
#include "CATEdge.h"
#include "CATVertex.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATVertex.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfListPOfCATFace.h"
#include "ListPOfListPOfCATEdge.h"
#include "CATListOfInt.h"
#include "CATListOfDouble.h"
#include "ListPOfCATListOfInt.h"
#include "CATIS.h"
#include "CATCGMDebug.h"
#include "CATMathDebug.h"
#include "CATWeekVersioning.h"
#include "CATCGMModif.h"
#include "CATCGMVersionningDefVar6.h"
#include "CATSysMacros.h"

#include "CATIsoParameter.h"
#include "CATMathVector.h"
#include "CATSurface.h"
#include "CATSurParam.h"
#include "CATPCurve.h"
#include "CATEdgeCurve.h"
#include "CATCrvParam.h"
#include "ListPOfCATDRepSeed.h"

class ExportedByPersistentCell CATGMFilletSupportSider
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation
  
  //------------------------------------------------------------
  // User interface
  //------------------------------------------------------------
  // face mode constructor
  CATGMFilletSupportSider(CATBody &iBody,
                          CATGeoFactory &iFactory,
                          CATSoftwareConfiguration &iConfig,
                          ListPOfCATFace &iSupportFacesToSide,
                          ListPOfCATFace &iFilletFaces,
                          CATListOfInt *iIsoparamForEachFace = NULL);

  // edge mode constructor
  CATGMFilletSupportSider(CATBody &iBody,
                          CATGeoFactory &iFactory,
                          CATSoftwareConfiguration &iConfig,
                          ListPOfCATEdge &iSupportEdgesToSide,
                          ListPOfCATFace &iFilletFaces,
                          CATListOfInt *iIsoparamForEachFace = NULL);

  virtual ~CATGMFilletSupportSider();

  HRESULT Run();

  void GetSidedSupportFaces(ListPOfCATFace oSidedSupportFaces[2]);
  void GetSidedSupportEdges(ListPOfCATEdge oSidedSupportEdges[2]);

  // DRepSeeds are not requested but can improve some results if specified
  void SetFilletPieces(ListPOfCATDRepSeed &iFilletPieces);

private:

  //------------------------------------------------------------
  // Private utilities
  //------------------------------------------------------------
  enum SupportTypeMode
  {
    SupportTypeMode_Unknown = 0,
    SupportTypeMode_Edge = 1,
    SupportTypeMode_Face = 2
  };

  // common constructor
  void Init(CATBody &iBody, CATGeoFactory &iFactory, CATSoftwareConfiguration &iConfig, ListPOfCATFace &iFilletFaces, CATListOfInt *iIsoparamForEachFace = NULL);

  HRESULT SideSupportFaces();
  HRESULT SideSupportEdges();

  HRESULT InitSidedGroups(ListPOfListPOfCATFace &oGroupsOfFilletFaces,
                          ListPOfCATListOfInt &oGroupsOfIsoparamOrientations,
                          ListPOfListPOfCATEdge oGroupsOfSidedEdges[2],
                          ListPOfListPOfCATFace oGroupsOfSidedFaces[2]);

  HRESULT LocalSideSupportEdges(CATFace &iFace, ListPOfCATEdge &iLocalSupportEdges, CATIsoParameter iIsoparam, ListPOfCATEdge oSidedEdges[2], CATOrientation &oOrientationOfSupports);

  void GetFollowingG1EdgesInLoop(CATFace &iFace, CATEdge &iEdge, CATBoolean iGoBackward, ListPOfCATEdge &ioAllowedEdges, ListPOfCATEdge &oFollowingG1Edges);

  HRESULT MergeSidedGroupsBasedOnSupportFacesSmoothSkins(ListPOfListPOfCATFace &ioGroupsOfFilletFaces,
                                                         ListPOfCATListOfInt &ioGroupsOfIsoparamOrientations,
                                                         ListPOfListPOfCATEdge ioGroupsOfSidedEdges[2],
                                                         ListPOfListPOfCATFace ioGroupsOfSidedFaces[2]);

  HRESULT MergeSidedGroupsBasedOnIsoparOrientations(ListPOfListPOfCATFace &ioGroupsOfFilletFaces,
                                                    ListPOfCATListOfInt &ioGroupsOfIsoparamOrientations,
                                                    ListPOfListPOfCATEdge ioGroupsOfSidedEdges[2],
                                                    ListPOfListPOfCATFace ioGroupsOfSidedFaces[2]);

  void GetGroupsWithSynchronizedOrientations(ListPOfCATFace &iFaces,
                                             CATListOfInt &iIsoparamForEachFace,
                                             ListPOfListPOfCATFace &oGroupOfSynchronizedFaces,
                                             ListPOfCATListOfInt &oCorrespondingIsoparam,
                                             ListPOfCATListOfInt &oCorrespondingIsoparamOrientation);

  CATOrientation GetOrientationRelatedToAdjacentFace(CATFace &iFace1, CATIsoParameter iIsoparam1, CATFace &iFace2, CATIsoParameter iIsoparam2, CATEdge &iContactEdge);
  CATOrientation GetOrientationRelatedToAdjacentFace(CATFace *iFace[2], CATIsoParameter iIsoparam[2], CATEdge &iContactEdge);

  void GetSmoothlyConnectedFacesThroughEdges(CATFace &iFace, ListPOfCATEdge &iEdges, ListPOfCATFace &oSmoothlyConnectedFaces, ListPOfCATEdge *oThroughEdge = NULL);
  void GetAdjacentFaces(CATEdge &iEdge, ListPOfCATFace &iInternalFaces, CATFace *&oInternalAdjacentFace, CATFace *&oExternalAdjacentFace);
  void GetAdjacentFaces(CATEdge &iEdge, CATFace &iInternalFace, CATFace *&oInternalAdjacentFace, CATFace *&oExternalAdjacentFace);

  HRESULT DiscardSupportFaces(ListPOfCATFace &iSupportFacesToDiscard, ListPOfListPOfCATEdge ioGroupsOfSidedEdges[2], ListPOfListPOfCATFace ioGroupsOfSidedFaces[2]);
  void AppendAndRevertIfNecessary(CATListOfInt &iTargetList, CATListOfInt &iListToAppend, CATBoolean iNeedsToRevert);

  void DumpGroups(ListPOfListPOfCATFace &ioGroupsOfFilletFaces, ListPOfListPOfCATEdge ioGroupsOfSidedEdges[2], ListPOfListPOfCATFace ioGroupsOfSidedFaces[2]);

  //------------------------------------------------------------
  // Data
  //------------------------------------------------------------
  CATBody &_Body;
  CATGeoFactory &_Factory;
  CATSoftwareConfiguration &_Config;

  CATBoolean _AlreadyExecuted;
  SupportTypeMode _SupportTypeMode;

  ListPOfCATFace _SupportFacesToSide;
  ListPOfCATEdge _SupportEdgesToSide;
  ListPOfCATFace _SupportFaceForEachSupportEdge;

  ListPOfCATFace _DiscardedFacesToSide;
  ListPOfCATEdge _DiscardedEdgesToSide;

  ListPOfCATFace _FilletFaces;
  CATListOfInt _IsoparamForEachFace;
  ListPOfCATDRepSeed _FilletPieces;

  ListPOfCATEdge _SidedSupportEdges[2];
  ListPOfCATFace _SidedSupportFaces[2];
};

#endif 

