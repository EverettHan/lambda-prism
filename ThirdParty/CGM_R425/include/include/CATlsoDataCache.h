#ifndef CATlsoDataCache_H
#define CATlsoDataCache_H

//-----------------------------------//
//------VB7 - 09 - 12 - 2013---------//
//-----------------------------------//

#include "CATPersistentCell.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"
#include "CATDrawerCollector.h"
#include "CATCGMHashTableWithAssoc.h"
#include "ListPOfCATCellManifold.h"
#include "CATCellManifold.h"
#include "ListPOfCATFace.h"
#include "CATHashTableWithIntAssoc.h"

class CATCellManifoldPatternNavigator;
class CATVertex;
class CATMathPoint;
class CATBody;
class CATPersistentBody;
class CATCellManifoldGroup;
class CATCellManifoldManager;
    
class ExportedByPersistentCell CATlsoDataCache
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  //
  CATlsoDataCache(ListPOfCATBody & iBodyList);

  ~CATlsoDataCache();

  void UpdateBodyList(ListPOfCATBody & iBodyList);
  
  void RemoveBody(CATBody * iInputBody);

    // -------------
  // Get Methodes
  // -------------
  void              GetMathPoint(CATVertex & iVertex, CATMathPoint & oMathPoint);
  void              GetVertexList(CATBody & iBody, ListPOfCATVertex & oVertexList);
  void              GetEdgeList(CATBody & iBody, ListPOfCATEdge & oEdgexList);
  void              GetEdgeList(ListPOfCATVertex & iVertexList, ListPOfCATEdge & oEdgeList);
  void              GetEdgeList(ListPOfCATVertex & iVertexList, ListPOfCATEdge & oEdgeList, ListPOfCATEdge & oCommonEdgeList);//oCommonEdgeList : at least 2 vertices share these edges
  void              GetEdgeList(CATVertex       * iVertex, ListPOfCATEdge & oEdgeList);
  void              GetFaceList(CATEdge         * iEdge, ListPOfCATFace & oFaceList);
  void              GetFaceList(ListPOfCATEdge  & iEdgeList, ListPOfCATFace & oFaceList);
  void              GetFaceList(CATVertex       * iVertex, ListPOfCATFace & oFaceList);
  void              GetFaceList(ListPOfCATVertex & iVertexList, ListPOfCATFace & oFaceList);
  // get face list from edge : input edge does not belong to internal loop of output faces
  void              GetFaceListWithoutInternalLoop(CATEdge * iEdge, ListPOfCATFace & oFaceList);
  void              GetFaceListWithoutInternalLoop(ListPOfCATEdge & iEdgeList, ListPOfCATFace & oFaceList);
  void              GetCellManifoldList(CATEdge * iEdge, ListPOfCATCellManifold & oCMList);
  CATBody         * GetBody(CATVertex           * iVertex);
  CATBody         * GetBody(CATEdge             * iEdge);
  CATBody         * GetBody(CATFace             * iFace);
  CATBody         * GetBody(CATCellManifold     * iCM);


  //For NotUpToDate algo
  CATBody           * GetExtrapolatedRefBody(CATCellManifoldGroup * iCMGroup);
  void                SetExtrapolatedRefBody(CATCellManifoldGroup * iCMGroup, CATBody * iExtrapolatedRefBody);
  CATBody           * GetInstanceGroupBody(CATCellManifoldGroup * iCMGroup);
  void                SetInstanceGroupBody(CATCellManifoldGroup * iCMGroup, CATBody * iInstanceGroupBody);
  CATLONG32           GetExplicitType(CATCellManifoldPatternNavigator * iPatternNavigator);
  void                SetExplicitType(CATCellManifoldPatternNavigator * iPatternNavigator, CATLONG32 iExplicitType);
  int                 GetRefNbFaces(CATCellManifoldGroup * iCMGroup);
  void                SetRefNbFaces(CATCellManifoldGroup * iCMGroup, int iRefNbFaces);
  CATBody *           GetInstanceFaceBody(int iNumRefFace, CATCellManifoldGroup * iInstanceGroup);
  void                SetInstanceFaceBody(int iNumRefFace, CATCellManifoldGroup * iPatternGroup, CATCellManifoldGroup * iInstanceGroup, CATBody * iBody);
  CATBody *           GetRefFaceBody(int iNumRefFace, CATCellManifoldGroup * iPatternGroup);
  void                SetRefFaceBody(int iNumRefFace, CATCellManifoldGroup * iPatternGroup, CATBody * iBody);
  void                CleanInstanceBodyList(CATGeoFactory & iFactory);
  CATBody *           GetWithoutFilletReferenceBody(CATCellManifoldGroup * iPatternGroup);
  void                SetWithoutFilletReferenceBody(CATCellManifoldGroup * iPatternGroup, CATBody * iBody);
  CATBody *           GetModifiedBody(CATCellManifoldsManager * iCMManager);
  void                SetModifiedBody(CATCellManifoldsManager * iCMManager, CATBody * iBody);
  CATBody *           GetModifiedBodyFaceBody(int iNumFace);
  void                SetModifiedBodyFaceBody(int iNumFace, CATCellManifoldsManager * iCMManager, CATBody * iBody);
  void                CleanModifiedBody();
  void                SetOBBBodyForDebug(CATBody * iOBBBodyForDebug);
  CATBody *           GetOBBBodyForDebug();

  CATBoolean          IsInCollisionPatternGroup(CATCellManifoldPatternNavigator * iPatternNavigator);
  // -------------
  // Set Methodes
  // -------------

protected : 

private : 

  void ComputeVertexToEdgeHashTable();
  void ComputeEdgeToFaceHashTable();
  void ComputeVertexToBodyHashTable();
  
  CATCGMHashTableWithAssoc * _VertexToMathPoint;

  CATCGMHashTableWithAssoc * _BodyToVertexList;

  CATCGMHashTableWithAssoc * _BodyToEdgeList;

  ListPOfCATBody _InputBodyList;

  //0 : Vertex -> Edge
  //1 : Edge   -> Face
  //2 : Edge   -> CM
  //3 : Vertex -> Body
  //4 : Edge   -> Body
  //5 : Face   -> Body
  //6 : CM     -> Body
  //7 : Vertex -> Face
  //8 : Edge   -> Face without internal loop
  CATBoolean     _NeedUpToDate[9];

  CATDrawerCollector       * _VertexToEdgeDrawerCollector;
  CATDrawerCollector       * _EdgeToFaceDrawerCollector;
  CATDrawerCollector       * _EdgeToFaceDrawerWithoutInternalLoopCollector;
  CATDrawerCollector       * _EdgeToCellManifoldDrawerCollector;
  CATCGMHashTableWithAssoc * _VertexToBody;
  CATCGMHashTableWithAssoc * _EdgeToBody;
  CATCGMHashTableWithAssoc * _FaceToBody;
  CATCGMHashTableWithAssoc * _CellManifoldToBody;
  CATDrawerCollector       * _VertexToFaceDrawerCollector;

  //Pattern NotUpToDate
  CATCGMHashTableWithAssoc * _PatternGroupToExtrapolatedRefBody;
  CATCGMHashTableWithAssoc * _InstanceGroupToBody;
  CATHashTableWithIntAssoc * _PatternGroupToExplicitType;
  CATHashTableWithIntAssoc * _PatternGroupToRefNbFaces;
  CATCGMHashTableWithAssoc * _InstanceGroupToFaceBodyList;
  CATCGMHashTableWithAssoc * _PatternGroupToRefFaceBodyList;
  CATCGMHashTableWithAssoc * _PatternGroupToRefBody;
  CATCGMHashTableWithAssoc * _CMManagerToModifiedBody;
  ListPOfCATBody           * _ModifiedBodyFaceBodyList;
  CATHashTableWithIntAssoc *_IsInCollisionPatternGroupHT;
  CATBody                  *_OBBBodyForDebug;
};

#endif
