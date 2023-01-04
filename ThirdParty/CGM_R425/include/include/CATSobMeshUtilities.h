//====================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved
//====================================================================
//
// CATSobMeshUtilities.h
//
//====================================================================
//
// Usage notes: Some utilities for meshes
//
//====================================================================
// 20.01.2014 : RAQ : Ajout IsAdjacentToTriangularFace, GetLocationInTriangularFace
// Feb,   2010 : RAQ : Ajout GetDetailsInfo
// Nov,   2008 : PMG : Enrichie RemoveAllDetailsOnMesh / Ajout GetFinestLODLevelOnMesh
// May,   2008 : RAQ : Ajout RemoveAllDetailsOnMesh
// June,  2005 : RAQ : Creation
//====================================================================
#ifndef CATSobMeshUtilities_H
#define CATSobMeshUtilities_H

//Pour l'export
#include "CATSobOperators.h"

//Divers
#include "CATSobDiag.h"
#include "CATBoolean.h"
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"
#include "CATListOfInt.h"

//STL
#ifndef _AIX_SOURCE
#include <vector>
#endif  //!_AIX_SOURCE

class CATSobMesh;
class CATSobVertex;


namespace CATSobMeshUtilities
{
  //Release générique
  template<typename T>
  void ReleaseObject(T* ipObject) { if(ipObject) ipObject->Release(); ipObject=0; }

/** 
 * Converts all the details of the mesh in corresponding local frames
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  ExportedByCATSobOperators 
    CATSobDiag ConvertDetailsToLocalFrame(CATSobMesh* iMeshGlobalFrame);

/** 
 * Converts all the details of the mesh in global frame
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  ExportedByCATSobOperators 
    CATSobDiag ConvertDetailsToGlobalFrame(CATSobMesh* iMeshLocalFrame);

/**
 * Removes all the details in the mesh.
 * Optionnaly this method can prune the detail tree by removing all the details
 * which level is strictly finer than a given one.
 *
 * @param ioMesh
 * The mesh to process
 * @param iLevelMin
 * All the details which level is finer than iLevelMin will be removed. If set to 0 all the details are removed.
 * iLevelMin will be the finest LOD level.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  ExportedByCATSobOperators 
    CATSobDiag RemoveAllDetailsOnMesh(CATSobMesh* ioMesh, const int iLevelMin = 0);

/**
 * Get the finest level of details in the mesh.
 *
 * @return
 * the finest level of details
 */
  ExportedByCATSobOperators
    int GetFinestLODLevelOnMesh(const CATSobMesh* iMesh);

/**
 * Check that all cells tags are unique.
 *
 * @param iCorrect
 * TRUE if cells tags must be corrected in case of multiplicity.
 * Be careful: If correction is asked, all cells tags will be overwritten, some links could be lost.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  ExportedByCATSobOperators 
    CATSobDiag CheckAndFixCellsTagsUniqueness(CATSobMesh* iMesh, const CATBoolean iCorrect);

/**
 * Retreives how many details are set on the mesh and the finest LOD level.
 *
 * @param iMesh
 * The mesh to analyse.
 * @param oNbDetails
 * The number of details on the mesh
 * @param oFinestLODLevel
 * The finest LOD level.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetDetailsInfo(CATSobMesh* iMesh, int& oNbDetails, int& oFinestLODLevel);

/**
 * Retreives the number of subdivision points for a given level.
 *
 * @param iMesh
 * The mesh
 * @param iLevel
 * The subdivision level
 * @param oNbSubdivPoints
 * The number of subdivision points.
 *
 * @return
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetNbSubdivisionPointsPerLevel(CATSobMesh* iMesh, const int iLevel, int& oNbSubdivPoints);

  ExportedByCATSobOperators 
    CATSobDiag CheckDetailsAmplitude(CATSobMesh* iMeshGlobalFrame, double& oUAmplitue, double& oVAmplitue, double& oNormalAmplitue );

/**
 * Retrieves one edge from an edge path defined by chained vertices
 *
 * @param iMesh
 *  The base mesh from which the edge is to be retrieved
 * @param iVerticesTags
 *  The list of vertices tags
 * @param iEdgeIndex
 *  The index of the edge to be retreived, the edge being defined by vertices iVerticesTags[iEdgeIndex] and iVerticesTags[iEdgeIndex+1]
 * @return
 *  The edge or NULL if it failed.
 **/
  ExportedByCATSobOperators
    CATSobEdge* GetOneEdgeFromChainedVertices(const CATSobMesh* iMesh, const CATListOfInt& iVerticesTags, const int iEdgeIndex);

/**
 * Retrieves a list of chained edges from a list of vertices
 *
 * @param iMesh
 *  The base mesh from which the edges are to be retrieved
 * @param iVerticesTags
 *  The list of vertices tags
 * @param oChainedEdgesList
 *  The list of chained edges
 *
 * @return
 *  CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetChainedEdgesFromVerticesTags(const CATSobMesh* iMesh, const CATListOfInt& iVerticesTags, CATLISTP(CATSobEdge)& oChainedEdgesList);

/**
 * Retrieves a list of ordered vertices from an ordered chained list of edges.
 *
 * @param iOrderedEdgesList
 * The ordered chained list of edges
 * @param oVertices
 * The ordered list of vertices
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetVerticesListFromEdgesList(const CATLISTP(CATSobEdge)& iOrderedEdgesList, CATLISTP(CATSobVertex)& oVertices);

/**
 * Retrieves a list of ordered vertices tags from an ordered chained list of edges.
 *
 * @param iOrderedEdgesList
 * The ordered chained list of edges
 * @param oVerticesTags
 * The ordered list of vertices tags
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetVerticesTagsListFromEdgesList(const CATLISTP(CATSobEdge)& iOrderedEdgesList, CATListOfInt& oVerticesTags);

/**
 * Retrieves the extremity vertices from a chained list of edges
 *
 * @param iOrderedEdgesList
 * The ordered chained list of edges
 * @param opVertex1
 * The first extremity vertex
 * @param opVertex2
 * The last extremity vertex
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag GetExtremityVerticesFromEdgesList(const CATLISTP(CATSobEdge)& iOrderedEdgesList, CATSobVertex*& opVertex1, CATSobVertex*& opVertex2);

/**
 * Extracts the one ring of faces around a given set of faces.
 *
 * @param iMesh
 * The current mesh.
 * @param iInputFaces
 * The faces from which the one ring is to be computed.
 * @param oOneRingOfFaces
 * The one ring of faces : this list only contains the one ring, it doesn't contain any faces of iInputFaces.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag ComputeOneRingAroundFaces(CATSobMesh* iMesh, const CATLISTP(CATSobFace)& iInputFaces, CATLISTP(CATSobFace)& oOneRingOfFaces, CATBoolean iAllowSharpEdgesCrossing = TRUE);

/**
 * Extracts N rings of faces around a given set of faces.
 *
 * @param iMesh
 * The current mesh.
 * @param iInputFaces
 * The faces from which the one ring is to be computed.
 * @param iNbRings
 * The number of rings to retrieve
 * @param oAllFaces
 * A list of faces containing the input faces and the N requested rings.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag ComputeNRingsAroundFaces(CATSobMesh* iMesh, const CATLISTP(CATSobFace)& iInputFaces, const int iNbRings, CATLISTP(CATSobFace)& oAllFaces, CATBoolean iAllowSharpEdgesCrossing = TRUE);

/**
 * Extracts N rings of faces around a given set of faces.
 *
 * @param iMesh
 * The current mesh.
 * @param ioFaces
 * The input faces but this list will be filled with neighbour faces.
 * @param iNbRings
 * The number of rings to retrieve
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag ComputeNRingsAroundFaces(CATSobMesh* iMesh, CATLISTP(CATSobFace)& ioFaces, const int iNbRings, CATBoolean iAllowSharpEdgesCrossing = TRUE);

/**
 * Extracts the biggest connex-by-edges set of faces containing a given face.
 *
 * @param ipSeedFace
 * A face in the connex area to compute
 * @param ioFaces
 * A connex-by-edges set of faces
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators
    CATSobDiag ComputeConnexByEdgesArea(const CATSobFace* ipSeedFace, CATLISTP(CATSobFace)& ioFaces);

/**
 * Checks whether a sub part of a mesh can be flattened without internal holes.
 * The topological domain must be homeomorphic to a disc : one connex manifold free border, genus 1.
 *
 * @param iFacesArea
 * The set of faces to process.
 * @param oIsFlattenable
 * Output of the method, oIsFlattenable is TRUE if the domain is flattenable, FALSE otherwise.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators 
    CATSobDiag CheckIfAreaIsFlattenable(const CATLISTP(CATSobFace)& iFacesArea, CATBoolean& oIsFlattenable);

/**
 * Computes the square distance between two vertices.
 *
 * @param iVertex1
 * The first vertex
 * @param iVertex2
 * The second vertex
 *
 * @return
 * The square distance between the two vertices, -1 if any error.
 **/
  ExportedByCATSobOperators
    double GetSquareDistance(const CATSobVertex* iVertex1, const CATSobVertex* iVertex2);

/**
  * Resets modification flag on all cells, ie all cells will be flagged 'unmodified'.
  *
  * @param iMesh
  * The mesh to process.
  *
  * @return
  * CATSobDiag_OK if no problem, else see CATSobDiag.h
  **/
  ExportedByCATSobOperators
    CATSobDiag ResetModifFlagOnAllCells(CATSobMesh* iMesh);

/**
 * Check whether two edges are sharing a common vertex and returns it.
 *
 * @param iEdge1
 * An Edge
 * @param iEdge2
 * An Edge
 *
 * @return
 * A common vertex or NULL if none exists.
 **/
  ExportedByCATSobOperators
    CATSobVertex* GetCommonVertexOfTwoEdges(CATSobEdge* iEdge1, CATSobEdge* iEdge2);

/**
 * Check whether two edges are sharing a same face and returns it.
 *
 * @param iEdge1
 * An Edge
 * @param iEdge2
 * An Edge
 *
 * @return
 * A common face or NULL if none exists.
 **/
  ExportedByCATSobOperators
    CATSobFace* GetCommonFaceOfTwoEdges(const CATSobEdge* iEdge1, const CATSobEdge* iEdge2);

/**
 * Check whether two faces are sharing a same edge and returns it.
 *
 * @param iFace1
 * A face
 * @param iFace2
 * A face
 * @param iopEdgeIndexInFace1
 * Optionnal, a pointer to an int that will contain the edge index in iFace1
 * @param iopEdgeIndexInFace2
 * Optionnal, a pointer to an int that will contain the edge index in iFace2
 *
 * @return
 * A common edge or NULL if none exists.
 **/
  ExportedByCATSobOperators
    CATSobEdge* GetCommonEdgeOfTwoFaces(CATSobFace* iFace1, CATSobFace* iFace2, int* iopEdgeIndexInFace1 = 0, int* iopEdgeIndexInFace2 = 0);

/**
 * Check whether an edge is adjacent to at least one triangular face
 *
 * @param ipEdge
 * The edge
 * @param opDirectTriFace
 * Optionnal parameter to retreive the edge's DirectFace if it is triangular
 * @param opInvertTriFace
 * Optionnal parameter to retreive the edge's InvertFace if it is triangular
 *
 * @return
 * TRUE if the edge is adjacent a triangular face, else otherwise.
 **/
  ExportedByCATSobOperators
    CATBoolean IsAdjacentToTriangularFace(const CATSobEdge* ipEdge, CATSobFace** opDirectTriFace = 0, CATSobFace** opInvertTriFace = 0);

/**
 * Gets all the information to identify an edge in a triangular face.
 * See CATSobEdge.h for edge representation in triangular faces.
 * Informations are provided with respect to the edge orientation in the given face.
 *
 * @param ipEdge
 * The edge
 * @param ipTriFace
 * The triangular face containing the edge
 * @param oDaughterFaceIndex1
 * The first sub-face containing the edge
 * @param oSubEdgeIndexInDaughterFace1
 * The edge index in the first daughter face
 * @param oDaughterFaceIndex2
 * The second sub-face containing the edge
 * @param oSubEdgeIndexInDaughterFace2
 * The edge index in the second daughter face
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  ExportedByCATSobOperators
    CATSobDiag GetLocationInTriangularFace(const CATSobEdge* ipEdge, CATSobFace* ipTriFace,
                                           int& oDaughterFaceIndex1, int& oSubEdgeIndexInDaughterFace1,
                                           int& oDaughterFaceIndex2, int& oSubEdgeIndexInDaughterFace2);

  //Extraction d'une loop d'edges libres
  ExportedByCATSobOperators
    CATSobDiag ExtractFreeEdgesLoop(CATSobEdge* iStartingEdge, CATLISTP(CATSobEdge)& oFreeEdgesLoop);

  //Extraction des vertex d'une loop d'edges libres
  ExportedByCATSobOperators
    CATSobDiag ExtractFreeVerticesLoop(CATSobEdge* iStartingEdge, CATListOfInt& oVerticesTags, const CATBoolean iRepeatLastAndFirstVertex = TRUE);

#ifndef _AIX_SOURCE
  //Extraction de toutes les loops d'edges libres d'un mesh.
  //Deux options cumulables : récupération sous forme de liste d'edges, ou liste de vertex avec premier et dernier vertex répétés
  ExportedByCATSobOperators
    CATSobDiag ExtractAllFreeEdgesLoops(CATSobMesh& iSobMesh, std::vector<CATLISTP(CATSobEdge)>* iopAllFreeEdgesLoops = nullptr, std::vector<CATListOfInt>* iopAllFreeVerticesLoops = nullptr);
#endif  //!_AIX_SOURCE

};


#endif


