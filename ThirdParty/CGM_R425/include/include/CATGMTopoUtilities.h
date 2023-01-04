#ifndef CATGMTopoUtilities_H
#define CATGMTopoUtilities_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "CATSysBoolean.h"
#include "CATDataType.h"
#include "IUnknown.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATPersistentCells.h"
#include "CATListOfCATGeometries.h"
#include "CATGeoDef.h"
#include "ListPOfListPOfCATCell.h"

// CGMObject


// Include list



// ++++ Predeclarations ++++
class CATSoftwareConfiguration;
class CATBody;
class CATPersistentBody;
class CATPersistentCellInfra;
class CATCellHashTable;
class CATCellHashTableCGM;
class CATFaceHashTable;
class CATEdgeHashTable;
class CATVertexHashTable;
class CATCell;
class CATFace;
class CATEdge;
class CATVertex;
class CATGeoFactory;
class CATCGMHashTableWithAssoc;
class CATMathVector;
class CATMathPoint;



//==========================================================================================================
// CATGMTopoUtilities
// 
// Responsable: QF2
// 
// Classe utilitaire pour les operateur topo et lso. Elle ne contient que des methodes
// statiques.
// Ces methodes se doivent d'utiliser le code plus abouti et le plus performant possible.
// Les HashTables seront prioritaires dans les signatures. Il n'y pas de RemoveAll() en debut de methode.
//==========================================================================================================

class ExportedByPersistentCell CATGMTopoUtilities
{

public :

  // static void InsertCells(const CATCellHashTable & iCellToInsertHT, CATCellHashTableCGM & ioCellHT);

  static void GetFaces(const ListPOfCATCell &iCellList, CATFaceHashTable &oFaceHT);
  static void GetFaces(const CATLISTP(CATGeometry) &iListOfGeometries, CATFaceHashTable &oFaceHT);
  static void GetFaces(const CATCellHashTable & iCellHT, CATFaceHashTable &oFaceHT);

  static void GetEdges(const CATCellHashTable & iCellHT, CATEdgeHashTable &oEdgeHT);
  static void GetEdges(const ListPOfCATCell & iCellList, CATEdgeHashTable &oEdgeHT);
  static void GetEdges(const CATLISTP(CATGeometry) &iListOfGeometries, CATEdgeHashTable &oEdgeHT);

  static void GetVertices(const ListPOfCATCell &iCellList, CATVertexHashTable &oVertexHT);
  static void GetVertices(const CATFaceHashTable &iFaceHT, CATVertexHashTable &oVertexHT);
  static void GetVertices(CATFace & iFace, CATVertexHashTable &oVertexHT);
  static void GetVertices(const CATEdgeHashTable &iEdgeHT, CATVertexHashTable &oVerticesHT);
  static void GetCommonVertices(CATFace *iFace1, CATFace *iFace2, CATVertexHashTable &oCommonVerticeHT);
  static void GetCommonVertices(const CATFaceHashTable & iFaceHT, CATVertexHashTable &oCommonVerticeHT, CATBoolean bCommonToAllHT=FALSE);
  /* If bCommonToAllHT==TRUE, common vertices must belong to all edges of iEdgeHT */
  static void GetCommonVertices(const CATEdgeHashTable & iEdgeHT, CATVertexHashTable &oCommonVerticeHT, CATBoolean bCommonToAllHT=FALSE);
  static void GetCommonBoundingVertices(const CATFaceHashTable & iFaceHT1, const CATFaceHashTable & iFaceHT2, CATVertexHashTable &oCommonVertexHT);

  static void GetBorderEdges(const CATFaceHashTable & iFaceHT, CATEdgeHashTable & oBorderEdgeHT, CATEdgeHashTable *oNonBorderEdges=NULL, CATFaceHashTable * oBorderFaceHT=NULL, CATCGMHashTableWithAssoc * oEdgeToBorderFaceHT=NULL);
  static void GetCommonEdges(const CATFaceHashTable & iFaceHT, CATEdgeHashTable & oCommonEdgeHT);
  static void GetCommonEdges (CATFace * ipFace1, CATFace * ipFace2, CATEdgeHashTable & oCommonEdgeHT);
  static void GetCommonEdges(const CATFaceHashTable & iFaceHT1, const CATFaceHashTable & iFaceHT2, CATEdgeHashTable & oCommonEdgeHT);
  static void GetCommonSmoothEdges (CATSoftwareConfiguration * ipConfig, const CATFaceHashTable & iFaceHT1, const CATFaceHashTable & iFaceHT2, CATEdgeHashTable & oCommonEdgeHT);
  static void GetInternalSmoothEdges(CATFaceHashTable &iFaceHT, CATEdgeHashTable &oInternalSmoothEdgeHT, CATCGMHashTableWithAssoc & oInternalEdgesToAdjacentFaceHT, CATSoftwareConfiguration * iConfig);

  static void GetConnectedFaceHT(const CATFaceHashTable & iFaceHT, CATEdgeHashTable & iEdgeHT, CATFaceHashTable & oConnectedFaceHT, CATBoolean iAlsoVertexConnection=FALSE);
  static void GetConnectedFaceHT (const CATFaceHashTable& iFaceHT, CATEdge* ipEdge, CATFaceHashTable& oConnectedFaceHT);

  static void GetExtremities(const CATEdgeHashTable& iEdgeHT, CATVertexHashTable& oExtremityVertexHT, CATVertexHashTable* oNonBorderVertexHT=NULL, CATEdgeHashTable * oExtremityEdgeHT=NULL);

  static void GetBorders(const CATCellHashTable & iCellHT, CATCellHashTable &oBorderCellHT);

  static void GetConnectedFacesProvidedConvexity(CATSoftwareConfiguration & iConfig, const CATFaceHashTable &iFaceHT, CATBody &iBody, CATGeoConvexity &iConvexity, CATFaceHashTable &oConnectedFaceHT);

  // Edge from Loop
  static void GetEdgesFromInnerLoop(const CATFaceHashTable &iFaceHT, CATEdgeHashTable &oInnerEdgeHT);
  static void GetEdgesFromOuterLoop(const CATFaceHashTable &iFaceHT, CATEdgeHashTable &oOuterEdgeHT);
  static void GetEdgesFromOuterLoop(CATFace * ipFace, CATEdgeHashTable & oOuterEdgeHT);

  static void GetSkinBorderVertices(CATBody * ipSkinBody, CATVertexHashTable &oVertexBorderHT);

  static CATBoolean AreConnected(const CATFaceHashTable &iFacesHT1, const CATFaceHashTable &iFacesHT2);

  static CATBoolean AreConnected(const CATFaceHashTable &iFacesHT);

  // Edge Ordering
  static HRESULT FastEdgeOrdering (CATCellHashTable& ioEdgesToOrderHT, CATCell* iFirstEdge = NULL); 

  // Retrieves previous and next Edge (if in iEdgeHT) of iEdge
  static void GetPreviousAndNextEdge(CATEdge                * iEdge, 
                                     const CATCellHashTable & iEdgeHT, 
                                     CATCell                *&oPreviousEdge,
                                     CATCell                *&oNextEdge,
                                     CATBoolean             * oCheckManifold = NULL);

  static void GetAdjacentEdges(CATSoftwareConfiguration *iConfig, 
                               CATEdge                  *iEdge, 
                               CATBody                  *iBody, 
                               CATEdgeHashTable         &oAdjacentEdgeHT);

  static void GetAdjacentEdges(CATSoftwareConfiguration *iConfig, 
                               CATVertexHashTable       &iVertexHT, 
                               CATBody                  *iBody, 
                               CATEdgeHashTable         &oAdjacentEdgeHT);
  
  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig, 
                               CATVertex                *iVertex,
                               CATBody                  *iBody, 
                               CATFaceHashTable         &oAdjacentFaceHT);

  static void GetAdjacentFaces(CATSoftwareConfiguration *iConfig,           
                               CATBody                  *iBody,
                               const CATEdgeHashTable   &iEdgeHT, 
                               CATFaceHashTable         &oAdjacentFaceHT);

  static void GetAdjacentCells(CATSoftwareConfiguration *iConfig, 
                               CATVertex                *iVertex, 
                               CATBody                  *iBody, 
                               CATEdgeHashTable         &oAdjacentEdgeHT,
                               CATFaceHashTable         &oAdjacentFaceHT);

  static void GetAdjacentFaceHT(CATEdge                 *iEdge, 
                                CATFaceHashTable        &iFaceHT,
                                CATFaceHashTable        &oAdjacentFaceHT,
                                CATBoolean              iVertexConnexity=TRUE);

  static void GetAdjacentFaceHT(CATEdgeHashTable        &iEdgeHT, 
                                CATFaceHashTable        &iFaceHT,
                                CATFaceHashTable        &oAdjacentFaceHT,
                                CATBoolean              iVertexConnexity=TRUE);

  static void FindAdjacentFacesToFaces(CATSoftwareConfiguration * iConfig,
                                       CATBody                  * iInputBody,
                                       const CATFaceHashTable   & iFaceHT,
                                       CATFaceHashTable         & oNeighbourFaces,
                                       CATBoolean                 iIncludeVertexAdjacency=FALSE,
                                       CATBoolean                 iTangencyPropag=FALSE);

  // Memory is allocated. Use delete[] operand to free the array.
  static void GetGroupsOfConnectedFaces(CATBody                * iBody, 
                                        const CATFaceHashTable & iFaceHT,                                         
                                        CATFaceHashTable       * oArrayOfConnectedFaces[], /*1D Tab dimension (single array)*/
                                        CATULONG32              & oArraySize);

  // Memory is allocated. Use delete[] operand to free the array.
  static void GetGroupsOfConnectedEdges(CATBody                * iBody, 
                                        const CATEdgeHashTable & iEdgeHT,                                         
                                        CATEdgeHashTable       * oArrayOfConnectedEdges[], /*1D Tab dimension (single array)*/
                                        CATULONG32             & oArraySize);

  // Memory is allocated. Use delete[] operand to free the array.
  static void GetGroupsOfConnectedFaces(const CATFaceHashTable & iFaceHT,                                         
                                        CATFaceHashTable       * oArrayOfConnectedFaces[], /*1D Tab dimension (single array)*/
                                        CATULONG32              & oArraySize);

  
  // Memory is allocated. Use delete[] operand to free the array.
  // Return size of oArrayOfSmoothGroup.
  static CATULONG32 GetSmoothSkinGroups(CATSoftwareConfiguration * iConfig,
                                        CATGeoFactory            * iFactory,
                                        CATBody                  * iBody, 
                                        const CATFaceHashTable   & iFaceHT,                                               
                                        CATFaceHashTable        ** oArrayOfSmoothGroup); /*1D Tab dimension (single array)*/                                  


  static void GetBoundaryCells(CATCell *iCell, CATCellHashTable &oBoundaryCells);
  static void GetBoundaryCells(const CATCellHashTable &iCellHT, CATCellHashTable &oBoundaryCells);
  static CATCellHashTableCGM * GetBoundaryCells(const CATCellHashTableCGM &iCellHT); // create a HashTable with righ type. It must be free after use.

  static void GetBoundaryCells(CATFace *iFace, CATEdgeHashTable & oBoundaryEdgeHT);
  static void GetBoundaryCells(const CATFaceHashTable &iFaceHT, CATEdgeHashTable & oBoundaryEdgeHT);
  static CATBoolean HasFreeBorderEdge(CATFace *iFace, CATBody *iBody);

  // liens remontant
  static void GetBoundedCells(CATVertex *iVertex, CATBody *iBody, CATEdgeHashTable &oBoundedEdgeHT);
  static void GetBoundedCells(CATEdge   *iEdge,   CATBody *iBody, CATFaceHashTable &oBoundedFaceHT);
  static void GetBoundedCells(CATCell   *iCell,   CATBody *iBody, CATCellHashTable &oBoundedCellHT);
  static void GetBoundedCells(const CATCellHashTable &iCellHT, CATBody *iBody, CATCellHashTable &oBoundedCellHT);

  // similar to TopologicalBasic::GetCommonBorderCells
  static void GetCommonBorderCells(const CATCellHashTableCGM &iCellHTab1, 
                                   const CATCellHashTableCGM &iCellHTab2, 
                                   CATUINT32                  iDepthOfSearch,
                                   CATCellHashTable          &oCommonBorderHT);

  static void GetCommonBorderVertices(const CATFaceHashTable &iFaceHTab1, 
                                      const CATFaceHashTable &iFaceHTab2,
                                      CATVertexHashTable     &oCommonVerticeHT);

  static void EvalAverageNormal(const CATFaceHashTable & iFaceHT, CATBody & iBody, CATMathVector & oAverageNormalVector, CATMathPoint & oAverageCenter);

  static void GetGroupsOfMultiDimConnexCells(ListPOfCATCell & iCellList, ListPOfListPOfCATCell &oGroupsOfConnectedCells);
    ;
  // Get PersistentCells of iCellsHT (optimized)
  /**
   * @brief Gets the Persistent Cells of input Cell HT
   * 
   * @details
   *  Optizimed method to get Persitent Cells from HT.
   * The persistent cells are retrieved either using 
   * PersistentCellInfra (if iCells.Size small) or the 
   * PersistentBody (hence the need of all cells to get complementary)
   * 
   * @param iCellsHT
   *  Input Cells HT.
   * @param iAllCellsInBodyHT
   *  All cells contained in body (bc. GetAllCells() is time consumming)
   * @param ipPersistentBody
   *  Input PersistentBody.
   * @param iInfra
   *  Persistent Infra.
   * @param oPersistentCellsList
   *   PersistentCells retrieved.
   */
  static void GetPersistentCells(const CATCellHashTable       & iCellsHT,
                                 const CATCellHashTable       & iAllCellsInBodyHT,
                                 CATPersistentBody            * ipPersistentBody,
                                 const CATPersistentCellInfra & iInfra,
                                 ListPOfCATPersistentCells    & oPersistentCellsList);

  /*!
   * @brief
   *  Gets the intersection between two CATCellHashTables.
   * 
   * @details
   *  The iteration is made on the biggest input CellHT so the
   * searching can be made on the smallest (other) input CellHT.
   * 
   * @param iCellHT1
   *  Input CellHT.
   * @param iCellHT2
   *  Input CellHT.
   * @param oIntersectionCellHT
   *  Output CellHT which contains Cells that are both in iCellHT1 and iCellHT2.
   */
#ifndef NEW_CELL_HASHTABLE
  static void IntersectionBetweenCellHashTables(const CATCellHashTable &iCellHT1,
                                                const CATCellHashTable &iCellHT2,
                                                CATCellHashTable       &oIntersectionCellHT);
#endif
};




#endif 

