//==================================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//==================================================================================
//
// CATSobEdge.h
//
//==================================================================================
//
// Usage notes:
//
//==================================================================================
// 30.01.2018 : RAQ : Optimisation perfos, ajout GetOneRingOfPoints avec structure dédiée
// April,     2008 : RAQ : Ajout AddDetailAtPoint
// December,  2007 : RAQ : Ajout GetVertices
// December,  2004 : RAQ : Ajout gestion des points sur l'edge
// October,   2004 : RAQ : Optimisation mémoire
// September, 2004 : RAQ : Allocation des tableau par user pour GetOneRingOfPoints
// July,      2004 : RAQ : Ajout GetOneRingOfPoints
// February,  2004 : RAQ : Smoothing de l'edge
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// September, 2003 : JCV : Commentaires
// September, 2003 : JCV : Gestion Diag
// July,      2003 : JCV : Gestion du Sharpness
// Marsh,     2003 : JCV : Creation d'apres le proto de LLR
//==================================================================================
#ifndef CATSobEdge_H
#define CATSobEdge_H

#include "CATBoolean.h"
#include "CATSobObjects.h"
#include "CATSobCell.h"


//---------------------------------
// A SUPPRIMER .....
#include "CATSobListOfVertexOnEdge.h"

class CATSobVertexOnEdge;
//---------------------------------


class CATSobFace;
class CATSobVertex;
class CATSobEdgeLOD;
class CATSobEdgeAttribute;
class CATSobOneRingData;


/*////////////////////////////////////////////////////////////////////////////////////////////////////////////

  -- About orientation of edges:
  An edge is bounded by two vertices: StartVertex and EndVertex,
  and is adjacent to at more two faces: DirectFace and InvertFace.
  The face DirectFace gives the natural orientation to this edge (it is the first face using this edge
  during the construction of the base mesh). If the edge is adjacent to only one face (ie. DirectFace) then
  InvertFace is nul.
  The direction of the orientation always goes from StartVertex to EndVertex, it represents an u-axis.

    StartVertex ---------------------------> EndVertex
                          u

  -- Natural coordinates of points on the edge during subdivision:
  At a subdivision level 'i', the edge contains 2^i + 1 points.
  The natural orientation of the edge allows to locate points from their index along u with:
                        0 <= u <= 2^i

  At a such a subdivision level:
  StartVertex has coordinates ( 0 )
  EndVertex has coordinates   (2^i)

////////////////////////////////////////////////////////////////////////////////////////////////////////////*/


class ExportedByCATSobObjects CATSobEdge : public CATSobCell
{
public:

	virtual ~CATSobEdge() {}

/** 
 * Imposes a support face for the edge.
 *
 * @param iFace
 * the pointer on the support face.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK              </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_EdgeSameSupport </tt> <dd> The input face is already a support face of this edge
 * <dl><dt><tt>CATSobDiag_EdgeMoreSupport </tt> <dd> the edge has already two supports (maximum)
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual void SetFace(CATSobFace* iFace, const CATBoolean iUpdateRing = TRUE) = 0;
  
/** 
 * Removes a support face for the edge.
 *
 * @param iFace
 * the pointer on the support face.
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> The input face is not a support face of this edge
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual void RazFace(CATSobFace* iFace, const CATBoolean iUpdateRing = TRUE) = 0;

/** 
 * Gets the direct support face for the edge.
 * (for this face, the edge is used with his direct orientation) 
 *
 * @return
 * The pointer on the direct support face
 */
  virtual CATSobFace* GetDirectFace() const = 0;

/** 
 * Gets the invert support face for the edge.
 * (for this face, the edge is used with his inverse orientation) 
 *
 * @return
 * The pointer on the invert support face
 */
	virtual CATSobFace* GetInvertFace() const = 0;

/* Gets the other face support face for the edge.
 * Return Null if it's a free border edge
 * @return
 * The pointer on the invert support face
 */
  virtual CATSobFace* GetOtherFace(const CATSobFace* iRefFace) const = 0;

/**
 * Sets the edge's indice in one of the adjancent face
 *
 * @param iFace
 * One of the adjacent face for which to set the indice
 * @param iIndex
 * The index of the edge seen in iFace
 **/
  virtual void SetIndexInFace(CATSobFace* iFace, const int iIndex) = 0;

/**
 * Gets the indice of the edge in an adjacent face
 *
 * @param iFace
 * An adjacent face of this edge
 * 
 * @return
 * The edge's indice if iFace is an adjacent face of 'this',
 * -1 otherwise.
 **/
  virtual int GetIndexInFace(CATSobFace* iFace) const = 0;
  
/** 
 * Gets the start vertex of the edge, on the context of a face if necessary.
 *
 * @param iFace
 * the pointer on the context of support face.
 * if 0, the default is the direct face.
 *
 * @return
 * The pointer on the start vertex.
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> The input face is not a support face of this edge
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 *   CATSobDiag_InputCellsIncompatibility
 */
	virtual CATSobVertex* GetStartVertex(const CATSobFace* iFaceOn = 0) const = 0;

/** 
 * Gets the end vertex of the edge, on the context of a face if necessary.
 *
 * @param iFace
 * the pointer on the context of support face.
 * if 0, the default is the direct face.
 *
 * @return
 * The pointer on the end vertex.
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                        </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputCellsIncompatibility </tt> <dd> The input face is not a support face of this edge
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 *   CATSobDiag_InputCellsIncompatibility
 */
	virtual CATSobVertex* GetEndVertex(const CATSobFace* iFaceOn = 0) const = 0;

 /* Gets the other vertex for the edge.
  *
  * @param iVertex
  * An extremity vertex of this edge.
  *
  * @return
  * The pointer on the other vertex of this edge.
  */
  virtual CATSobVertex* GetOtherVertex(const CATSobVertex* iVertex) const = 0;

/**
 * Gets the vertices regarding the edge direction in a face
 *
 * @param oStartVertex
 * A pointer that will contain the adress of StartVertex
 * @param oEndVertex
 * A pointer that will contain the adress of StartVertex
 * @param iFaceOn
 * The pointer on the context of support face, if 0 the default is the direct face.
 **/
  virtual void GetVertices(CATSobVertex*& oStartVertex, CATSobVertex*& oEndVertex, const CATSobFace* iFaceOn = 0) const = 0;

/** 
 * Gets the vertices tags regarding the edge direction in a face
 *
 * @param oStartVertexTag
 * The start vertex tag
 * @param oEndVertex
 * The endvertex tag
 * @param iFaceOn
 * The pointer on the context of support face, if 0 the default is the direct face.
 **/
  virtual void GetVerticesTags(unsigned int& oStartVertexTag, unsigned int& oEndVertexTag, const CATSobFace* iFaceOn = 0) const = 0;

/** 
 * Reverses the orientation of the edge.
 * --> swap Start and End Vertices
 */
  virtual void ReverseOrientation() = 0;
  
/** 
 * Imposes the sharpness value.
 *
 * @param iSharpness
 * Sharpness value : 0 -> no sharp and no weight (default)
 * if Sharpness value >= level of subdivision, the edge has a weight
 * For smoothing see EnableSmoothing
 *
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidValue </tt> <dd> The Sharpness value must be greater or equal to 0 and less or equal 100.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 *   CATSobDiag_InputCellsIncompatibility
 */
  virtual void SetSharpness(const short iSharpness) = 0;

/** 
 * Gets the sharpness value.
 *
 * @return 
 * The Sharpness value : 0 -> no sharp (default)
 * if Sharpness value <= 100 and > 0, the edge has a weight
 * For smoothing see IsSmoothingEnabled
 * if the edge is free (no invert support) return 999.
 */
  virtual short GetSharpness() const = 0;

/**
 * Specifies if the edge must be smoothed during surface construction,
 * this problem occurs only if the sharpness of the edge is not nul.
 *
 * @param iOnOff
 * iOnOff == TRUE : the edge will be smoothed
 * iOnOff == FALSE: the edge will be sharp (no tangent plane along the edge)
 */
  virtual void EnableSmoothing(const CATBoolean iOnOff) = 0;


/**
 * Sets if the edge have to be smoothed during surface construction.
 *
 * @return
 * TRUE : the edge will be smoothed
 * FALSE: the edge won't be smoothed (no tangent plane along the edge)
 */
  virtual CATBoolean IsSmoothingEnabled() const = 0;


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
 * Gets the coordinates of a point given by its index on the edge and a subdivision level
 *
 * @param u
 * The index of the point on the edge
 * @param v
 * The subdivision level
 *
 * @return
 * A pointer to an array of 3 double
 */
  virtual double* GetPoint(const int u, const int iLevel) = 0;

/** 
 * Gets all the points around a point described by its u-coordinates in the face at a given level.
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
 * 2. The point is exactly inside the edge:
 *    2.1 If the edge is a border, only the previous and the next point are given
 *        for they are the only involved in the subdivision rules
 *    2.2 The edge is not a border, all the good points are given.
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
 * @param iUOnEdge
 * The point coordinate on the edge
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
                                        const int iUOnEdge,
                                        const int iArraysAllocatedByUser=0) = 0;

  virtual CATSobDiag GetOneRingOfPoints(CATSobOneRingData& oOneRingData,
                                        const int iLevel,
                                        const int iUOnEdge) = 0;

  //---------------------- New methods for getting/setting details ---------------------//
/**
 * Test if the edge contains some details
 *
 * @return
 * 1 if details exist for the edge, else 0;
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
  virtual CATSobEdgeLOD* GetEdgeLODAtLevel(const int iLevel) const = 0;

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
  virtual CATSobEdgeLOD* CreateEdgeLODAtLevelOrInit(const int iLevel) = 0;

/**
 * Removes the iLevel-th level of a detail
 *
 * @param iLevel
 * The level
 *
 * @return0 if no problem occured, else 1
 */
  virtual int RemoveEdgeLOD(const int iLevel) = 0;

/**
 * Gets the detail on a point given by its index in the edge and a subdivision level
 *
 * @param u
 * The index on the edge
 * @param iLevel
 * The level of a subdivision
 *
 * @return
 * A pointer to an array of 3 double (detail vector), NULL if no detail exists
 */
  virtual double* GetDetailAtPoint(const int u, const int iLevel) const = 0;

/**
 * Sets the detail vector on a point given by its index on the edge and a subdivision level.
 * If a detail already exists it is overwritten.
 *
 * @param u
 * The index on the edge
 * @param iLevel
 * The level of a subdivision
 * @param iDetail
 * A 3 double-array containing the detail vector
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int SetDetailAtPoint(const int u, const int iLevel, const double* iDetail) = 0;

/**
 * Adds the detail vector on a point given by its index on the edge and a subdivision level
 * If a vector detail already exists they are summed.
 *
 * @param u
 * The index on the edge
 * @param iLevel
 * The level of a subdivision
 * @param iDetail
 * A 3 double-array containing the detail vector
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int AddDetailAtPoint(const int u, const int iLevel, const double* iDetail) = 0;

/**
 * Removes the detail on a point given by its index on the edge and a subdivision level
 *
 * @param u
 * The index on the edge
 * @param iLevel
 * The level of a subdivision
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int RemoveDetailAtPoint(const int u, const int iLevel) = 0;

/**
 * Gets the local frame for a point at a given level
 *
 * @param u
 * The index on the edge
 * @param iLevel
 * The level of a subdivision, iLevel must be > 0
 * @param ioFrame
 * The local frame for this point:
 * U vector is ioFrame[0..2]
 * V vector is ioFrame[3..5]
 * n vector is ioFrame[6..8]
 *
 * @return
 * 0 if no problem occured, else 1
 */
  virtual int GetLocalFrameAtPoint(const int u, const int iLevel, double* ioFrame) = 0;



  //---------------------------- New methods for points on edges ----------------------------//
/**
 * Check if 'this' edge contains some 'CATSobVertexOnEdge'
 *
 * @return
 * TRUE if some vertices exist on 'this', else FALSE
 **/
  virtual CATBoolean HasVertexOnEdge() const = 0;
  
/**
 * Gets all the CATSobVertexOnEdge elements on 'this' edge
 *
 * @param ioAllVerticesOnEdgeList
 * A pointer on the list of vertices on edge
 *
 * @return
 * The number of CATSobVertexOnEdge elements on 'this' edge
 **/
  virtual int GetAllVerticesOnEdge(CATLISTP(CATSobVertexOnEdge)*& ioAllVerticesOnEdgeList) const = 0;

/**
 * Gets all the CATSobVertexOnEdge elements on 'this' edge respect to an adjecent face
 *
 * @param ioAllVerticesOnEdgeList
 * The adress of a list
 * @param iFace
 * An adjancent face of 'this' edge
 *
 * @return
 * The size of ioAllVerticesOnEdgeList
 **/
  virtual int GetAllVerticesOnEdge(CATLISTP(CATSobVertexOnEdge)* iAllVerticesOnEdgeList, CATSobFace* iFace) = 0;


/**
 * --------- DO NOT USE ----------
 **/
  virtual CATBoolean IsEdgeCut() = 0;

protected :

  CATSobEdge(CATSobMesh* iMesh): CATSobCell(iMesh){}

  private :
    // Copy constructor and equal operator
  CATSobEdge (CATSobEdge &);
  CATSobEdge& operator=(CATSobEdge&);

};

#endif
