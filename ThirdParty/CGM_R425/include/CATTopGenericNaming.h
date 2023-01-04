#ifndef CATTopGenericNaming_H
#define CATTopGenericNaming_H
//--------------------------------------------------------------------------------------------------
// CATTopGenericNaming : Liste d'utilitaires specialises adaptes au GenericNaming
//
//
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 23 11 2000  Creation pour la nouvelle offre CATTopGN_InternalVerticesOfCommonBoundary
// Fev 05 CATTopGN_CellNeighbours                                                         FDN
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"

#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathDef.h"
#include "CATTopDef.h"


#include "ListVOfLong.h"
#include "CATCGMVersionCommonEdges.h"
#include "ListPOfCATConnectedCellsIterator.h"
#include "ListPOfCATCGMBoundedCellGroup.h"
#include "ListPOfCATIPGMTopGNCommonEdgeData.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfListPOfCATTopology.h"

class CATLISTP(CATCell);
class CATLISTP(CATDomain);
class CATLISTP(CATFace);
class CATBody;
class CATSoftwareConfiguration;
class CATCell;
class CATFace;


//------------------------------------------------------------------------------
// CATTopGN_InternalVerticesOfCommonBoundary 
//   Determination des sommets 
//     ayant comme seules aretes incidentes dans le Body,
//     des aretes de la frontiere commune entre les deux listes de Faces
//   La valeur de retour sous HResult permets de savoir s'il n'y pas eu
//   des anomalies dans les specifications des donnees d'entrees
//    (Body NULL, Face n'appartenant pas au Body,...)
//------------------------------------------------------------------------------
ExportedByCATTopologicalObjects HRESULT CATTopGN_InternalVerticesOfCommonBoundary
(
  CATBody                 *  iBody,
  const CATLISTP(CATCell) &  iFaces1,
  const CATLISTP(CATCell) &  iFaces2,
  CATLISTP(CATCell)       &  iVertices
);



//----------------------------------------------------------------------------------------------
// CATTopGN_CommonEdges 
//   soient deux paquets connexes et disjoint entre eux de Faces d'un meme Body
//     (chaque paquet est 1-manifold, sans Edge a plus de deux faces incidentes) 
//   on en determine les bords communs en paquets connexes d'Edges de telle facon
//   que chaque resultat voit toujours le premiere liste de Face avec le meme cote matiere 
//
//  Precision :
//    1) chaque liste de Faces fournie en entree forme un domaine orientable
//    que l'on stabilise en orientation avec la matiere entrant dans le Body (volumique/surfacique)
//    2) il reste une ambiguite de stabilisation dans le resultat quand celui-ci est forme 
//    d'un paquet connexe equivalent a un Wire ferme (problemne du choix de l'Edge initiale)
//    3) Il semble que la premiere version Body->CommonEdges orientait generalement le resultat
//     en s'assurant de voir le premiere paquet de Face a Droite.
// 
// y2021 - w48
//    Généralisation à N paquets connexes (N>=2) pour gérer les Edges Non-manifolds.
//----------------------------------------------------------------------------------------------
/**
 * @param iUseForNewTopGNCommonEdges, default value = FALSE
 * Env variable parameter, only used inside of the new CommonEdges services
 */
ExportedByCATTopologicalObjects HRESULT CATTopGN_CommonEdges
(
  CATBody                   * iBody,
  const CATLISTP(CATCell)   & iFaceList_1,
  const CATLISTP(CATCell)   & iFaceList_2,
  CATLISTP(CATCell)         & ioResult,
  CATListOfLong             & ioListOrientation,
  CATListOfLong             & ioNbOfEdgesByDomain,
  CATCGMVersionCommonEdges    iVersion = CatCGMCommonEdgesFirstDraft,
  CATBoolean                  iFirstListIsMatterSideLeft = FALSE,
  CATLISTP(CATConnectedCellsIterator) * iPtrLocalCellsIterators = NULL
);

ExportedByCATTopologicalObjects HRESULT CATTopGN_CommonEdges
(
  CATBody                   * iBody,
  const CATLISTP(CATCell)   & iFaceList_1,
  const CATLISTP(CATCell)   & iFaceList_2,
  CATLISTP(CATCell)         & ioResult,
  CATListOfLong             & ioListOrientation,
  CATLISTP(CATDomain)		   & oListOfUpperUpperDomain,
  CATListOfLong             & ioNbOfEdgesByDomain,
  CATCGMVersionCommonEdges    iVersion = CatCGMCommonEdgesFirstDraft,
  CATBoolean                  iFirstListIsMatterSideLeft = FALSE,
  CATLISTP(CATConnectedCellsIterator) * iPtrLocalCellsIterators = NULL
);



//----------------------------------------------------------------------------------------------
// CommonEdges service with N>2 lists of topology (i.e. Cell lists)
//----------------------------------------------------------------------------------------------
/**
 * @warning This method is on developmenent, do not use it
 * @param iBody
 * Input body
 * @param iConfig 
 * SoftwareConfiguration for future versioning
 * @param iTopoLists
 * List of topology lists
 * @param oCommonEdgeDataList
 * List of CATIPGMTopNGCommonEdgeData 
 * 
 * @return
 * S_OK if all common edges between given lists have been found
 * E_FAIL otherwise
 */
ExportedByCATTopologicalObjects HRESULT CATTopGN_CommonEdges
(
  CATBody * iBody,
  CATSoftwareConfiguration * iConfig,
  const ListPOfListPOfCATTopology & iTopoLists,
  ListPOfCATIPGMTopGNCommonEdgeData & oCommonEdgeDataList
);

/**
 * @warning This method is on developmenent, do not use it
 * This method is not exposed to interface API
 * @nocgmitf @nodoc
 */
ExportedByCATTopologicalObjects HRESULT CATTopGN_CommonEdges
(
  CATBody                           * iBody,
  CATSoftwareConfiguration          * iConfig,
  const ListPOfListPOfCATCell       & iCellLists,
  ListPOfCATIPGMTopGNCommonEdgeData & oCommonEdgeDataList
);

/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
* CATTopGN_CellNeighbours
*  Find the neighbors of a given cells in the context of an input body.
*
*  @param ipContextBody
*    The context body.
*  @param ipCellList
*    The input cells to analyze.
*  @param ipOris
*    The input orientations.
*  @param oResultCells
*    The resulting neighbors containing all the connected components.
*  @param oNbOfCellsByDomain
*    Output list of short containing the cells number of each connected component.
*  @param iVersionGenericNaming (@DEPRECATED)
*    Please use the CATSoftwareConfiguration instead of this parameter.
*  @param ipConfig
*    The CGM Config.
*  @return
*   HRESULT = S_TRUE if there is no ambiguity in the resulting cells order
*    and  HRESULT = S_FALSE otherwise (same cell have been founed multiple times).
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_CellNeighbours(CATBody *                 ipContextBody,
                                                                const CATLISTP(CATCell) * ipCellList,
                                                                const CATListOfLong     * ipOris,
                                                                CATLISTP(CATCell)       & oResultCells,
                                                                CATListOfLong           & oNbOfCellsByDomain,
                                                                const short               iVersionGenericNaming,
                                                                CATSoftwareConfiguration * ipConfig = NULL);
/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
* CATTopGN_GroupCells
*  Group the input cells in a set of connected components.
*
*  @param ipContextBody
*    The context body.
*  @param ipCellsToGroup
*    The input cells to group: from Generic Naming point of view 
*    those cells must have the same naming.
*  @param oNbCellByGroup
*    output list of short containing the cells number of each connected component.
*  @param oGroups
*    The resulting connected component.
*  @param iConsiderNonManifold
*    Example: If 3 faces are connected by one edge
*      iConsiderNonManifold = TRUE means that the 3 faces will be in 3 connected components
*      iConsiderNonManifold = FALSE means that the 3 faces will be in one single connected component.
*    Same thing for edges.
*  @param iVersionGenericNaming (@DEPRECATED)
*    Please use the CATSoftwareConfiguration instead of this parameter.
*  @param ipConfig
*    The CGM Config.
*  @return
*    HRESULT
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_GroupCells(CATBody * ipContextBody,
                                                            const CATLISTP(CATCell) * ipCellsToGroup,
                                                            CATListOfLong & oNbCellByGroup,
                                                            CATLISTP(CATCell)& oGroups,
                                                            CATBoolean iConsiderNonManifold = FALSE,
                                                            CATSoftwareConfiguration* ipConfig = NULL);
/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
* CATTopGN_GetExpectedCellsForReporting
*  Find the expected cells to be followe in a given body.
*
*  @param ipContextBody
*    The context body.
*  @param ioReportingCells
*    output cells that should be followed.
*  @param ipConfig
*    The CGM Config.
* @return
*   HRESULT
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_GetExpectedCellsForReporting(CATBody * ipContextBody,
                                                                              CATLISTP(CATCell) & ioReportingCells,
                                                                              CATSoftwareConfiguration* ipConfig = NULL);
/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
* CATTopGN_IsCandidateForReporting
*  Check if a given cell should be followed or not.
*
*  @param ipContextBody
*    The context body.
*  @param ipCell
*    The cell to check
*  @param oIsCandidate
*    If oIsCandidate = TRUE, the cell should be followed otherwise it should not.
*  @param ipConfig
*    The CGM Config.
*  @return
*    HRESULT
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_IsCandidateForReporting(CATBody * ipContextBody,
                                                                         CATCell * ipCell,
                                                                         CATBoolean& oIsCandidate,
                                                                         CATSoftwareConfiguration* ipConfig = NULL);

/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
* CATTopGN_SelectEdgesFromFaces
*  Find edge frontier of the specified list of face and also non manifold edges.
*
*  @param ipContextBody
*    The context body.
*  @param ipFaces
*    The input faces to analyze: from Generic Naming point of view
*    those faces must have the same naming.
*  @param iConsiderNonManifold
*    Provide also non manifold edges
*  @param oEdges
*    Output edges (edges frontier of the specified list of faces and also non manifold edges).
*  @param ipConfig
*    The CGM Config.
*  @return
*    HRESULT
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_SelectEdgesFromFaces(CATBody * ipContextBody,
                                                                      const CATLISTP(CATFace)* ipFaces,
                                                                      CATLISTP(CATCell)& oEdges,
                                                                      CATBoolean iConsiderNonManifold = FALSE,
                                                                      CATSoftwareConfiguration * ipConfig = NULL);

/**
*  DISCLAIMER: this is a specif service made for Generic Naming only.
*
*  CATTopGN_VertexBoundedCells
*  Find bounded cells of input vertex 
*
*  @param iContextBody
*    The context body.
*  @param iVertex
*    The input vertex
*  @param oResult
*    Output list of CATCGMBoundedCellGroup type
*  @param ipConfig
*    The CGM Config.
*  @return
*    HRESULT
*/
ExportedByCATTopologicalObjects HRESULT CATTopGN_VertexBoundedCells(CATBody * iContextBody,
																	CATCell * iVertex,
	                                                                CATLISTP(CATCGMBoundedCellGroup)& oResult,
	                                                                CATSoftwareConfiguration* ipConfig = NULL);

#endif
