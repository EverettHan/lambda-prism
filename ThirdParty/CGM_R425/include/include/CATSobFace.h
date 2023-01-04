//==================================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//==================================================================================
//
// CATSobFace.h
//
//==================================================================================
//
// Usage notes:
//
//==================================================================================
// 30.01.2018 : RAQ : Optimisation perfos, ajout GetOneRingOfPoints avec structure dédiée
// April,     2008 : RAQ : Ajout AddDetailAtPoint
// December,  2004 : RAQ : Gestion LocalCut
// October,   2004 : RAQ : Optimisation mémoire
// September, 2004 : RAQ : Allocation des tableau par user pour GetOneRingOfPoints
// July,      2004 : RAQ : Ajout GetOneRingOfPoints
// June,      2004 : RAQ : Ajout de IsAHole et SetIsAHole
// April,     2004 : RAQ : Niveaux de détails
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// September, 2003 : JCV : Commentaires
// September, 2003 : JCV : Gestion Diag
// June,      2003 : JCV : le Mesh donne au constructeur de SdmCell
// Marsh,     2003 : JCV : Creation d'apres le proto de LLR
//==================================================================================
#ifndef CATSobFace_H
#define CATSobFace_H

#include "CATSobObjects.h"
#include "CATSobCell.h"
#include "CATSobDefine.h"

#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"
#include "CATSobFaceLOD.h"

#include "CATBoolean.h"

class CATSobVertex;
class CATSobMesh;
class CATSobEdge;
class CATSobFaceAttribute;
class CATSurface;
class CATSobOneRingData;

/*////////////////////////////////////////////////////////////////////////////////////////////////////

  A CATSobFace object represents a base mesh face. This face can be either quadrangular (4 edges)
  or triangular (3 edges). All the methods work on both representation, except that the interpretation
  of data is different. The following schemes explains how to manipulate these data.

  FOR QUADRANGULAR FACES

  -- About orientation in the face:
  Vertices and Edges are indexed from 1 to 4 in counter-clockwise order.
  This order gives a natural orientation to the face.


              V4--------------------------V3
              |        <---------         |                 Natural orientation attached to the face:
              |         Edge #3           |                                                             
              |                           |                    /|\                                           
           |  |                           | /|\                 |                                          
           |  |                           |  |                  | v                                        
   Edge #4 |  |                           |  | Edge #2          |                                                 
           |  |                           |  |                  |    u                                     
          \|/ |                           |  |                   ---------->                                        
              |         Edge #1           |                                                            
              |        --------->         |                                                           
              V1--------------------------V2

  V1 stands for vertex #1, V2 for vertex #2 ...

  -- Natural coordinates of points in the face during subdivision:
  At a subdivision level 'i', each edge contains 2^i + 1 points.
  The natural orientation of face allows to locate points from their
  indices along the u and v axis with:
                                        0 <= u <= 2^i
                                        0 <= v <= 2^i

  At a subdivision level 'i':

  V1 has coordinates (0  ,   0)
  V2 has coordinates (2^i,   0)
  V3 has coordinates (2^i, 2^i)
  V4 has coordinates (0  , 2^i)

  
  FOR TRIANGULAR FACES

  Currently, during subdivision, a triangular face is split into 3 quadrangular faces.

  -- About orientation in the face:
  Vertices and Edges are indexed from 1 to 3 in counter-clockwise order.
  The 3 quadrangular faces are indexed from 1 to 3 in counter-clockwise order ([1], [2] and [3]).
  The location of a point in the triangular face is done respect to one of the 3 quadrangular faces (see above).

                                                                       
                    V3                                                 
                    |  \                                               
                    ||   \                                             
                    ||3   _\                                           
                    ||   |\  \                                         
                    |V      \  \                                       
                    |      2  \  \                                     
                    |  [3]     _   \                                   
                    |           /| / \                                 
                |   |   4     1/ /     \     _                         
                |   | ---->   / /   /    \  |\                         
                |   |----------/  /        \   \  Edge #2              
        Edge #3 |   |  <----  | |_ 3       _ \   \                     
                |   |    3    |           |\   \   \                   
               \|/  |         |              \   \   \                 
                    |   [1]   |            2   \   \                   
                    | |     A |                      \                 
                    | |4   3| | |      [2]             \               
                    | |     | | |4                       \             
                    | V     | | |                          \           
                    |    1    | V          1                 \         
                    |  ---->  |       ---->                    \        
                    V1________|_________________________________V2
                       ------------->                                  
                           Edge #1                                     
                                                                       

  -- Coordinates of points in the face
  Each quadrangular face created in a triangular face has a natural orientation given by its edges.
  If the triangular face is subdivided to level 'i' (i>0), then each quad face is subdivided to level 'i-1'.
  The coordinates of a point in a such a quad face is (u, v) with
                      0 <= u <= 2^(i-1)
                      0 <= v <= 2^(i-1)

  For example:
  The center vertex (the vertex common to the three quad faces) has coordinates:
  (2^(i-1), 2^(i-1)) if seen in quad face #1
  (0      , 2^(i-1)) if seen in quad face #2
  (0      , 0      ) if seen in quad face #3

////////////////////////////////////////////////////////////////////////////////////////////////////*/


class ExportedByCATSobObjects CATSobFace : public CATSobCell
{
public:

/** 
 * @nodoc
 */
  virtual ~CATSobFace() {}

/**
 * Test whether the face is quad or not
 *
 * @return
 * 1 if the face is quad, 0 else
 */
  virtual int IsQuadFace() const = 0;


/** 
 * Gets the number of Edges in the Face.
 *
 * @return
 * The number of Edges in the Face.
 */
	virtual int GetNbOfEdges () const = 0;	

/** 
 * Gets one Edge in the Face given by his rank.
 *
 * @param iIndexEdge
 * The rank of the Edge
 *
 * @return
 * The pointer on the edge
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidIndex </tt> <dd> Invalid Index : must be greater than 0 and lower or equal to the number of edges
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobEdge* GetEdge (const int iIndexEdge) = 0;	


/**
 * Gets all edges defined in the Face.
 *
 * @param ioListOfEdges
 * A pointer to the list
 *
 * @return
 * The number of edges in the face 
 */
  virtual int GetEdges(CATLISTP(CATSobEdge)*& ioListOfEdges) const = 0;
  
/** 
 * Gets the next Edge in the Face.
 *
 * @param iEdge
 * the reference Edge in the face 
 *
 * @return
 * The pointer on the next edge
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullEdge             </tt> <dd> Input Edge is nul
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> Input Edge is not in the face
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobEdge* NextEdge(const CATSobEdge* iEdge) = 0;

/** 
 * Gets the previous Edge in the Face.
 *
 * @param iEdge
 * the reference Edge in the face 
 *
 * @return
 * The pointer on the previous edge
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullEdge             </tt> <dd> Input Edge is nul
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> Input Edge is not in the face
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobEdge* PrevEdge(const CATSobEdge* iEdge) = 0;
  
/** 
 * Gets the neighbour Face by an edge given by his rank (starting at 1)
 *
 * @param iIndexEdge
 * the rank of the Edge. 
 *
 * @return
 * The pointer on the neighbour face
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidIndex </tt> <dd> Index must be greater than 0 and lower or equal to number of edges
 * <dl><dt><tt>CATSobDiag_EdgeNull          </tt> <dd> the face contains a nul Edge 
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobFace* GetNeighbour(const int iIndexEdge) = 0;

/** 
 * Gets the neighbour Face by an one of his edge.
 *
 * @param iEdge
 * an Edge of the face.
 *
 * @return
 * The pointer on the neighbour face
 * if this pointer is Null,
 * get the information value using GetDiag.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputNullEdge             </tt> <dd> Input Edge is nul
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> Input Edge is not in the face
 * <dl><dt><tt>CATSobDiag_EdgeNull                  </tt> <dd> the face contains a nul Edge 
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual CATSobFace* GetNeighbour(CATSobEdge* iEdge) = 0;

/**
 * Gets the iIndex-th vertex of the face (see diagram above)
 *
 * @param iIndex
 * The rank of the vertex in this face
 *
 * @return
 * The corresponding vertex
 */
  virtual CATSobVertex* GetVertex(const int iIndex) const = 0;

/**
 * Gets the index of a vertex in this face (see diagram above)
 *
 * @param iVertex
 * The vertex
 *
 * @return
 * The corresponding index
 */
  virtual int GetIndexOfVertex(const CATSobVertex* iVertex) const = 0;

/** 
 * Imposes the surface attach to the face
 *
 * @param iSurface
 * the pointer of the Surface (Nurbs)
 *
 * @param iDaughterFaceIndex
 * If the face is quad this param must be 0, else it is the index
 * of the sub-face.
 */
  virtual void SetSurface(CATSurface* iSurface, const int iDaughterFaceIndex = 0) = 0;

/** 
 * Gets the surface attach to the face
 *
 * @param iDaughterFaceIndex
 * If the face is quad this param must be 0, else it is the index
 * of the sub-face.
 *
 * @return 
 * the pointer of the Surface (Nurbs)
 */
  virtual CATSurface* GetSurface(const int iDaughterFaceIndex = 0) const = 0;

/**
 * Check whether the surface has been modified.
 *
 * @param iDaughterFaceIndex
 * If the face is quad this param must be 0, else it is the index
 * of the sub-face.
 *
 * @return
 * 1 if the surface has been modified, 0 else.
 */
  virtual short IsSurfaceModified(const int iDaughterFaceIndex = 0) = 0;

/**
 * Set if the surface has been modified or not
 *
 * @param iModif
 * 1 if the surface has been modified, 0 else
 * @param iDaughterFaceIndex
 * If the face is quad this param must be 0, else it is the index
 * of the sub-face.
 */
  virtual void SetSurfaceModified(const int iModif, const int iDaughterFaceIndex = 0) = 0;

/**
 * Get the Tag of 'this' face in the mesh
 *
 * @return
 * the tag of 'this' face
 */
  virtual unsigned int GetTag() const = 0;


  //------------------ New methods for the multi-res subdivision operator ------------------//
/**
 * Gets the buffer at a given level
 *
 * @param iLevel
 * The level for which the buffer is asked
 *
 * @return
 * The buffer or NULL if none exists
 */
  virtual double* GetBufferAtLevel(const int iLevel) = 0;

/**
 * Gets the coordinates of a point given by its indexes in the face and a subdivision level
 *
 * @param u
 * The first index in face
 * @param v
 * The second index in face
 * @param iLevel
 * The subdivision level
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * A pointer to an array of 3 double
 */
  virtual double* GetPoint(const int u, const int v, const int iLevel, const int iIndexOfDaughterFace=0) = 0;

/** 
 * Gets all the points around a point described by its (u, v)-coordinates in the face at a given level.
 * The face must have already been subdivided.
 * The points in the one-ring are denoted by Beta or Gamma as shown below:
 *
 *  Gamma ------------------ Beta ------------------ Gamma
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *  Beta ------------------- this ------------------ Beta
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *    |                        |                       |
 *  Gamma ------------------ Beta ------------------ Gamma
 *
 *
 * When retrieving the one ring, several cases exist:
 * 1. The point is a vertex, see GetOneRingOfPoints in CATSobVertex.h
 * 2. The point is on an edge, see GetOneRingOfPoints in CATSobEdge.h
 * 3. The point is exactly inside the face.
 *
 * @param ioBetaVerticesCoords
 * A pointer to an array of double that will contain the Beta vertices coordinates,
 * This array is create in the method if iArraysAllocatedByUser==0 (see below).
 * @param oNbBetaVertices
 * The number of Beta-type vertices
 * @param ioGammaVerticesCoords
 * A pointer to an array of double that will contain the Gamma vertices coordinates,
 * This array is create in the method if iArraysAllocatedByUser==0 (see below).
 * @param oNbGammaVertices
 * The number of Gamma-type vertices
 * @param iLevel
 * The subdivision level
 * @param iU
 * The first coordinate of the point in the face
 * @param iV
 * The second coordinate of the point in the face
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see up above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 * @param iArraysAllocatedByUser
 * If the point valence is well known, the user can allocate ioBetaVerticesCoords and
 * ioGammaVerticesCoords.
 * If iArraysAllocatedByUser==1, the method uses the array given, and
 * for each array, the size must be: 3*valence.
 * If iArraysAllocatedByUser==0, the method creates the array and the user must delete them.
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 */
  virtual CATSobDiag GetOneRingOfPoints(double*&  ioBetaVerticesCoords,
                                        int&      oNbBetaVertices,
                                        double*&  ioGammaVerticesCoords,
                                        int&      oNbGammaVertices,
                                        const int iLevel,
                                        const int iU,
                                        const int iV,
                                        const int iIndexOfDaughterFace=0,
                                        const int iArraysAllocatedByUser=0) = 0;

  virtual CATSobDiag GetOneRingOfPoints(CATSobOneRingData& oOneRingData,
                                        const int iLevel,
                                        const int iU,
                                        const int iV,
                                        const int iIndexOfDaughterFace = 0) = 0;

/**
 * Gets all the points of the face for a given subdivision level.
 * The array of double must be allocated by the user. The parameter iSizeOfTab
 * is used to check weither the array has a legal size.
 * At level 'i':
 *  - For a quadrangular face: iSizeOfTab must be 3*(2^i+1)*(2^i+1)
 *  - For a triangular face:   iSizeOfTab must be 3*(2^(i-1)+1)*(2^(i-1)+1)
 *
 * The points are arranged the following way:
 *
 *          3             The edges are indexes in the face by 1, 2, 3, 4.
 *     <-----------       The points are given from left to right and from down to up
 *   |  ......... /|\
 *   |  .........  |
 * 4 |  .........  | 2    Warning: it differs from CATSmoFaceData.
 *   |  .........  |
 *  \|/ .........  |
 *     ----------->
 *          1
 *
 * @param iLevel
 * The subdivision level
 * @param ioTabOfPoints
 * The array of double allocated by the user
 * @param iSizeOfTab
 * The number of double in the array, to check the size is legal
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 */
  virtual CATSobDiag GetAllPointsOfFaceAtLevel(const int iLevel, 
                                               double*&  ioTabOfPoints,
                                               const int iSizeOfTab,
                                               const int iDaughterFaceIndex = 0) = 0;

  
  //---------------------- New methods for getting/setting details ---------------------//
/**
 * Test if the face contains some details
 *
 * @return
 * 1 if details exist for the face, else 0;
 */
  virtual int HasDetails() const = 0;

/**
 * Gets the finest level of details index
 *
 * @return
 * 0 if no details exists, else the finest level of details index
 **/
  virtual int GetFinestLODLevel() const = 0;
  
/**
 * Gets the iLevel-th level of details
 *
 * @param
 * The level
 *
 * @return
 * The iLevel-th level of details, NULL if none exists
 */
  virtual CATSobFaceLOD* GetFaceLODAtLevel(const int iLevel) = 0;

/**
 * Create the iLevel-th level of details, if it already exists all details
 * for this level are erased
 *
 * @param
 * The level
 *
 * @return
 * The iLevel-th level of details, NULL if creation failed
 */
  virtual CATSobFaceLOD* CreateFaceLODAtLevelOrInit(const int iLevel) = 0;

/**
 * Removes the iLevel-th level of a detail
 *
 * @param iLevel
 * The level
 *
 * @return0 if no problem occured, else 1
 */
  virtual int RemoveFaceLOD(const int iLevel) = 0;

/**
 * Gets the detail on a point given by its indexes in the face and a subdivision level
 *
 * @param u
 * The first coordinate
 * @param v
 * The second coordinate
 * @param iLevel
 * The level of a subdivision
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * A pointer to an array of 3 double (detail vector), NULL if no detail exists
 */
  virtual double* GetDetailAtPoint(const int u, const int v, const int iLevel, const int iIndexOfDaughterFace=0) = 0;

/**
 * Sets the detail vector on a point given by its indexes in the face and a subdivision level.
 * If a detail already exists it is overwritten.
 *
 * @param u
 * The first coordinate
 * @param v
 * The second coordinate
 * @param iLevel
 * The level of a subdivision
 * @param iDetail
 * A 3 double-array containing the detail vector
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int SetDetailAtPoint(const int u, const int v, const int iLevel, const double* iDetail, const int iIndexOfDaughterFace=0) = 0;

/**
 * Adds a detail vector on a point given by its indexes in the face and a subdivision level.
 * If a vector detail already exists they are summed.
 *
 * @param u
 * The first coordinate
 * @param v
 * The second coordinate
 * @param iLevel
 * The level of a subdivision
 * @param iDetail
 * A 3 double-array containing the detail vector
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int AddDetailAtPoint(const int u, const int v, const int iLevel, const double* iDetail, const int iIndexOfDaughterFace=0) = 0;

/**
 * Removes the detail on a point given by its indexes in the face and a subdivision level
 *
 * @param u
 * The first coordinate
 * @param v
 * The second coordinate
 * @param iLevel
 * The level of a subdivision
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int RemoveDetailAtPoint(const int u, const int v, const int iLevel, const int iIndexOfDaughterFace=0) = 0;


  //---------------------------- Methods used for local frame ----------------------------//

/**
 * Gets the local frame at a point at a given level
 *
 * @param u
 * The first coordinate
 * @param v
 * The second coordinate
 * @param iLevel
 * The level of a subdivision, iLevel must be > 0
 * @param ioFrame
 * The local frame for this point:
 * U vector is ioFrame[0..2]
 * V vector is ioFrame[3..5]
 * n vector is ioFrame[6..8]
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture above)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int GetLocalFrameAtPoint(const int u, const int v, const int iLevel, double* ioFrame, const int iIndexOfDaughterFace = 0) = 0;


  //---------------------- Methods used when compressing and streaming a mesh ---------------------//

/**
 * Tag this face as a hole
 **/
  virtual void SetIsAHole() = 0;

/**
 * Check if this face represents a hole
 *
 * @return
 * 1 if this face represents a hole, 0 otherwise
 **/
  virtual int IsAHole() = 0;

  //------------------------------- Methods used for LocalCut Operations ---------------------------//

/**
 * Retrieves the local mesh for 'this' face, when the face is locally cut
 *
 * @return
 * The local mesh if exists, else NULL
 **/
  virtual CATSobMesh* GetLocalMesh() = 0;

/**
 * Removes the local mesh for 'this' face, when the face is locally cut
 *
 * @param iReleaseVerticesOnEdge
 * if TRUE: removes all the vertices on the edges of the face when deleting the local mesh
 * if FALSE: removes only the local mesh of the face
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 **/
  virtual CATSobDiag RemoveLocalMesh(const CATBoolean iReleaseVerticesOnEdge=FALSE) = 0;

/**
 * Gets the number of cuts for 'this' face along the U-axis ans the V-axis
 * The local mesh must exist.
 *
 * @param oNbCutsOnU
 * The number of cuts along the U-axis, 0 if none
 * @param oNbCutsOnV
 * The number of cuts along the V-axis, 0 if none
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetNbCuts(int& oNbCutsOnU, int& oNbCutsOnV) = 0;

/**
 * Gets the number of cuts for 'this' face along the U-axis ans the V-axis and the corresponding ratios
 * The local mesh must exist.
 *
 * @param oNbCutsOnU
 * The number of cuts along the U-axis, 0 if none
 * @param oRatioOnU
 * A pointer that will contain the ratio of the cuts along the U-axis.
 * If there is no cuts (ie. oNbCutsOnU==0), the pointer will be NULL
 * The array must be deleted by the user
 * @param oNbCutsOnV
 * The number of cuts along the V-axis, 0 if none
 * @param oRatioOnV
 * A pointer that will contain the ratio of the cuts along the V-axis.
 * If there is no cuts (ie. oNbCutsOnV==0), the pointer will be NULL
 * The array must be deleted by the user
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetNbCuts(int& oNbCutsOnU, double*& oRatioOnU, int& oNbCutsOnV, double*& oRatioOnV) = 0;



/** ********* DEBUG: Do not use ***********
 * Is Loop subdivided
 *
 * @return
 * TRUE if Loop subdivision must be performed on 'this',
 * FALSE if Catmull-Clark subdivision.
 **/
  virtual CATBoolean IsLoopFace() const = 0;


protected:

  CATSobFace(CATSobMesh* iMesh):CATSobCell(iMesh){};

  public :
    
/** *********** DEPRECATED ***********
 * Gets all Edges defined in the Face.
 *
 * @param ioEdgesOfFace
 * the list of Edges defined in the mesh
 *
 * @return
 * the number on the defined Edges 
 */
  virtual int GetEdges (CATLISTP(CATSobEdge) & ioEdgesOfFace) const = 0;	

  private:
      // Copy constructor and equal operator
  CATSobFace (CATSobFace &);
  CATSobFace& operator=(CATSobFace&);
}; 

#endif
