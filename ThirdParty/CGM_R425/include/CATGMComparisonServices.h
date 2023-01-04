/* -*-C++-*- */

#ifndef CATGMComparisonServices_H
#define CATGMComparisonServices_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

DESCRIPTION  : For Topology Comparison
               
=============================================================================
*/

#include "CATPersistentCell.h"
#include "CATCGMVirtual.h"
#include "ListPOfCATBody.h"
#include "ListPOfCATVertex.h"
#include "ListPOfCATEdge.h"
#include "ListPOfCATFace.h"
#include "CATMathTransformation.h"
#include "CATlsoDataCache.h"
#include "CATSoftwareConfiguration.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATDrawerCollector.h"
#include "CATVertexHashTable.h"
#include "CATEdgeHashTable.h"

class CATCGMHashTableWithAssoc;

/** @nodoc @nocgmitf */
class ExportedByPersistentCell CATGMComparisonServices : public CATCGMVirtual
{
public:

  //Constructor
  CATGMComparisonServices(CATBody * iInputBody, ListPOfCATBody & iToCompareWithBodyList, CATMathTransformation & iTransformation, CATSoftwareConfiguration * iConfig);
  //Desctructor
  ~CATGMComparisonServices();

  //@nocgmitf
  void SetTolerance(double iTolerance);

  //@nocgmitf
  void SetDataCache(CATlsoDataCache * iDataCache);

  //@nocgmitf
  void GetSimilarVertices(CATVertex * iInputVertex, ListPOfCATVertex & oSimilarVertexList, ListPOfCATBody & oSimilarBodyList);// oSimilarVertexList parallel to oSimilarBodyList
  //@nocgmitf
  void GetSimilarEdges(CATEdge * iEdge, ListPOfCATEdge & oSimilarEdgeList, ListPOfCATBody & oSimilarBodyList, ListPOfCATEdge & oMicroEdgeList);// oSimilarEdgeList parallel to oSimilarBodyList
  //@nocgmitf
  void GetSimilarEdgesWithCandidates(
    CATEdge * iEdge, 
    ListPOfCATEdge & oSimilarEdgeList, 
    ListPOfCATBody & oSimilarBodyList, 
    ListPOfCATCell & oCandidates, 
    ListPOfCATFace & oCandidateFaceList, 
    ListPOfCATEdge & oCandidateFaceCandidateEdgeList,
    ListPOfCATEdge & oMicroEdgeList,
    CATBoolean & oNeedCandidateFaceForWireComparison);
  //@nocgmitf
  void GetSimilarFaces(CATFace * iFace, ListPOfCATFace & oSimilarFaceList, ListPOfCATBody & oSimilarBodyList, CATBoolean iInternalLoopOption=FALSE, CATBoolean iUseCandidates=TRUE);// oSimilarFaceList parallel to oSimilarBodyList

private:
  CATlsoDataCache * GetDataCache();
  CATGeoFactory * GetInputFactory();
  double GetSquareTolerance();
  double GetEpsilon();
  double GetTolerance();
  int GetBodyDim(CATCell * iCell);
  CATSoftwareConfiguration * GetSoftwareConfiguration();

  CATBoolean IsSharpEndVertex(CATEdge * iEdge);
  CATBoolean IsSharpStartVertex(CATEdge * iEdge);

  void AppendSimilarVertexListToBuffer(CATVertex * iFirstVertex, ListPOfCATVertex & iSimilarVertexList);
  void GetSimilarVertexListFromBuffer(CATVertex * iFirstVertex, ListPOfCATVertex & oSimilarVertexList, ListPOfCATBody & oSimilarBodyList);
  void AppendNotSimilarVertexToBuffer(CATVertex * iFirstVertex);
  CATBoolean HasNotSimilarVertexFromBuffer(CATVertex * iFirstVertex);

  void AppendSimilarEdgeListToBuffer(CATEdge * iFirstEdge, ListPOfCATEdge & iSimilarEdgeList, ListPOfCATEdge & iMicroEdgeList);
  void GetSimilarEdgeListFromBuffer(CATEdge * iFirstEdge, ListPOfCATEdge & oSimilarEdgeList, ListPOfCATBody & oSimilarBodyList, ListPOfCATEdge & oMicroEdgeList);
  void AppendNotSimilarEdgeToBuffer(CATEdge * iFirstEdge);
  CATBoolean HasNotSimilarEdgeFromBuffer(CATEdge * iFirstEdge);

  void GetSimilarStartAndEndVertex(CATEdge * iEdge, CATVertex *& oSimilarStartVertex, CATVertex *& oSimilarEndVertex);
  void GetSimilarStartAndEndVertex(CATEdge * iEdge, ListPOfCATVertex & oSimilarStartVertex, ListPOfCATVertex & oSimilarEndVertex);

  void GetCandidateEdges(CATEdge * iEdge, ListPOfCATCell & oCandidates, CATBoolean & oNeedCandidateFace);
  void GetCandidateFaceList(CATEdge * iEdge, ListPOfCATFace & oCandidateFaceList, ListPOfCATEdge & oCandidateFaceCandidateEdgeList);

  CATBoolean AreConfusedEdges(CATEdge * iFirstEdge, CATEdge * iSecondEdge, CATBoolean & oNeedCandidateFace);

  void GetCommonBorderFaces(ListPOfCATCell & iGlobalCandidates, ListPOfCATFace & oIntersectListOfFace);
  CATBoolean AllBorderEdgesInInputList(CATFace * iFace, ListPOfCATCell & iCellList, CATBoolean iInternalLoopOption);

private :
  //Input Data
  CATBody               * _InputBody;
  ListPOfCATBody          _ToCompareWithBodyList;
  CATMathTransformation   _Transformation;

  CATBoolean _UseGivenTolerance;
  double     _Tolerance;

  CATSoftwareConfiguration * _Config;

  //Internal Data
  CATBoolean                 _DataCacheOwner;
  CATlsoDataCache          * _DataCache;

  CATDrawerCollector       * _SimilarVerticesBuffer;
  CATVertexHashTable       * _NotSimilarVerticesBuffer;
  CATDrawerCollector       * _SimilarEdgesBuffer;
  CATDrawerCollector       * _SimilarMicroEdgesBuffer;
  CATEdgeHashTable         * _NotSimilarEdgesBuffer;
  CATCGMHashTableWithAssoc * _EdgeToBox;
  CATCGMHashTableWithAssoc * _BoxToMovedBox;
  CATDrawerCollector       * _ConfusedEdgesBuffer;

};

#endif
