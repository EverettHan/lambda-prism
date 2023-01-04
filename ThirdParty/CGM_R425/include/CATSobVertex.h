//==================================================================================
// Copyright Dassault Systemes Provence 2003, All Rights Reserved
//==================================================================================
//
// CATSobVertex.h
//
//==================================================================================
//
// Usage notes:
//
//==================================================================================
// 30.01.2018 : RAQ : Optimisation perfos, ajout GetOneRingOfPoints avec structure dédiée
// April,     2008 : RAQ : Ajout AddDetailAtLevel
// October,   2006 : RAQ : Gestion tags sur les vertex
// November,  2004 : RAQ : Ajout GetValence pour éviter appel à ComputeRing
// November,  2004 : RAQ : Ajout méthodes pour interpoler les vertex
// October,   2004 : RAQ : Optimisation mémoire
// September, 2004 : RAQ : Allocation des tableau par user pour GetOneRingOfPoints
// July,      2004 : RAQ : Ajout GetOneRingOfPoints
// January,   2004 : RAQ : Changement d'architecture des subdivisions
// September, 2003 : JCV : Commentaires
// September, 2003 : JCV : Gestion Diag
// July,      2003 : JCV : acces au poid (Weight)
// June,      2003 : JCV : le Mesh donne au constructeur de SdmCell
// Marsh,     2003 : JCV : Creation d'apres le proto de LLR
//==================================================================================
#ifndef CATSobVertex_H
#define CATSobVertex_H

#include "CATSobObjects.h"

#include "CATSobCell.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"

#include "CATBoolean.h"

class CATSobMesh;
class CATSobVertexAttribute;
class CATSobOneRingData;

class ExportedByCATSobObjects CATSobVertex : public CATSobCell
{
public:

/** 
 * @nodoc
 */
	virtual ~CATSobVertex() {};

/** 
 * Imposes a modification on the vertex, all adjacent elements
 * are also flagged modified
 *
 * @param iNbModif
 * the value of the modification
 * 0 -> reset modifications
 * @param iNbRingsToUpdate
 * The number of cell rings around 'this' vertex to invalidate (max is 2)
 */
  virtual void SetModif(const short iNbModifs, const int iNbRingsToUpdate = 2) = 0;
  
/**
 * Get the Tag of 'this' vertex in the mesh
 *
 * @return
 * the tag of 'this' vertex
 */
  virtual unsigned int GetTag() const = 0;

/** 
 * Imposes Coordinates of vertex
 *
 * @param iX
 * The first coordinate
 * @param iY
 * The second coordinate
 * @param iZ
 * The third coordinate
 */
	virtual void SetCoordinates(const double& iX,
								const double& iY,
								const double& iZ) = 0;

/** 
 * Imposes Coordinates of vertex
 *
 * @param iCoords
 * An array of three double containing the new coordinates
 */
	virtual void SetCoordinates(const double iCoords[]) = 0;

/** 
 * Gets Coordinates of vertex
 *
 * @param oX
 * The first coordinate
 * @param oY
 * The second coordinate
 * @param oZ
 * The third coordinate
 */
	virtual void GetCoordinates(double& oX,
								double& oY,
								double& oZ) const = 0;

/** 
 * Gets Coordinates of vertex
 *
 * @param oCoords
 * An array of three double to retrieve the coordinates
 */
	virtual void GetCoordinates(double oCoords[]) const = 0;

/** 
 * Gets Coordinates of vertex
 *
 * @return
 * An array of three double containing the coordinates
 */
	virtual const double* GetCoordinates() const = 0;

/** 
 * Imposes Weight of vertex
 *
 * @param iWeight
 * the Weight of the vertex, using by subdivision operator.
 * 
 * The information value.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATSobDiag_OK                </tt> <dd> OK.
 * <dl><dt><tt>CATSobDiag_InputInvalidValue </tt> <dd> iWeight must be inclusing between 0. and 1.
 * </dl>
 * Use @href CATSobDiag include to see all the information values.
 */
  virtual void SetWeight (const double iWeight = 0.) = 0;
    
/** 
 * Gets Weight of vertex
 *
 * @return 
 * the Weight of the vertex, using by subdivision operator.
 */
  virtual double GetWeight () const = 0;

/**
 * Imposes the subdivision surface when converted to nurbs
 * to pass through 'this' vertex
 *
 * @param iInterpolOnOff
 * if TRUE the surface interpolates the point, else common rules are applied
 **/
  virtual void SetInterpolateVertex(const CATBoolean iInterpolOnOff = TRUE) = 0;
  
/**
 * Check if the surface must interpolate 'this' point
 *
 * @return
 * if TRUE the surface must interpolate the point
 **/
  virtual CATBoolean IsVertexInterpolated() = 0;

/**
 * Get the valence of 'this' vertex,
 * this is the number of edges shared by the vertex
 *
 * @return
 * The valence of the vertex
 **/
  virtual int GetValence() const = 0;

/** 
 * Gets edges using the vertex, there is no order on the edges
 *
 * @param
 * A pointer to a list of edges
 *
 * @return
 * The number of edges for this vertex
 */
  virtual int GetEdgesFast(CATLISTP(CATSobEdge)*& ioAllEdges) = 0;

/** 
 * Gets edges using the vertex, the edges are given in clockwise order
 * around 'this' vertex
 *
 * @param
 * A pointer to a list of edges
 *
 * @return
 * The number of edges for this vertex
 */
  virtual int GetEdges(CATLISTP(CATSobEdge)*& ioAllEdges) = 0;

/**
 * Checks if 'this' has no free edges around.
 *
 * @return
 * TRUE if 'this' vertex is closed (ie no free edges around), FALSE otherwise.
 **/
  virtual CATBoolean IsClosedVertex() = 0;
  
/** 
 * Gets faces using the vertex.
 *
 * @param
 * the list of faces using the vertex.
 * For performance please use the next method.
 */
	virtual void GetOneRing(CATLISTP(CATSobFace)& ioOneRing) = 0;

/**
 * Gets faces using the vertex.
 *
 * @param
 * A pointer to a list of faces
 *
 * @return
 * The number of faces around this vertex
 */
  virtual int GetOneRing(CATLISTP(CATSobFace)*& ioFaceRing) = 0;

/** 
 * Gets all the vertices around 'this' vertex at a given level.
 * 'This' vertex must have already been subdivided.
 * The vertices are denoted by Beta vertices if they share the same edge as 'this',
 * Gamma vertices if not.
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
 * 1. 'This' vertex shares exactly two free edges: no gamma vertices are given for
 *    they are not involved in the subdivision rules
 * 2. 'This' vertex shares more than two free edges: neither gamma or beta vertices are given for
 *    the vertex does not move.
 * 3. 'This' vertex has no free edges but one of the adjacent faces is not quad:
 *      3.1 The level for which the coordinates are to be retreived is 0: the operation can not be performed,
 *          the level must be at least 1.
 *      3.2 The level for which the coordinates are to be retreived is at least 1: see case 4
 * 4. 'This' vertex has no free edges, all the adjacent faces are quad or the level is at least 1:
 *    No problem, all the points are given
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
 * @param iArraysAllocatedByUser
 * If the point valence is well known, the user can allocate ioBetaVerticesCoords and
 * ioGammaVerticesCoords.
 * If iArraysAllocatedByUser==1, the method uses the array given, and
 * for each array, the size must be: 3*valence.
 * If iArraysAllocatedByUser==0, the method creates the array and the user must delete them.
 *
 * @return
 * CATSobDiag_OK if no problems, else see CATSobDiag.h
 */
  virtual CATSobDiag GetOneRingOfPoints(double*&  ioBetaVerticesCoords,
                                        int&      oNbBetaVertices,
                                        double*&  ioGammaVerticesCoords,
                                        int&      oNbGammaVertices,
                                        const int iLevel,
                                        const int iArraysAllocatedByUser=0) = 0;

  virtual CATSobDiag GetOneRingOfPoints(CATSobOneRingData& oOneRingData,
                                        const int iLevel) = 0;

  /**
 * Gets faces using the vertex and these Neighbour faces .
 *
 * @param
 * the list of faces using the vertex and these Neighbour faces.
 */
  virtual void GetTwoRing (CATLISTP(CATSobFace) & ioTwoRing) = 0;

/** 
 * Notifies an edge use the vertex.
 *
 * @param
 * the pointer of the edge using the vertex.
 */
  virtual void SetEdge (CATSobEdge * iEdge) = 0;
  
/** 
 * Notifies an edge no use the vertex any more.
 *
 * @param
 * the pointer of the edge no using the vertex any more.
 */
  virtual void RazEdge (CATSobEdge * iEdge) = 0;

/** 
 * Notifies Faces using the vertex are modified.
 */
  virtual void ResetRing () = 0;


  //------------------ New methods for the multi-res subdivision operator ------------------//
/**
 * Gets the buffer at a given level
 *
 * @param iLevel
 * The level for which the buffer is asked
 * @param iParam
 * Do not use
 *
 * @return
 * The buffer or NULL if none exists
 */
  virtual double* GetBufferAtLevel(const int iLevel, const int iParam = 1) = 0;


  //---------------------- New methods for getting/setting details ---------------------//
/**
 * Test if the vertex contains some details
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
 * Gets the detail vector for a given level
 *
 * @param iLevel
 * The level for which to get the level
 *
 * @return
 * A pointer to an array of 3 double
 */
  virtual double* GetDetailAtLevel(const int iLevel) const = 0;

/**
 * Sets the detail vector at a given level, if a detail already exists it is overwritten.
 *
 * @param iLevel
 * The level
 * @param iDetailValue
 * An array of 3 double containing the coordinates of the detail vector
 *
 * @return
 * 1 if problems occured, 0 else
 */
  virtual int SetDetailAtLevel(const int iLevel, const double* iDetailValue) = 0;
  
/**
 * Adds a detail vector at a given level, if a vector detail already exists they are summed.
 *
 * @param iLevel
 * The level
 * @param iDetailValue
 * An array of 3 double containing the coordinates of the detail vector
 *
 * @return
 * 1 if problems occured, 0 else
 */
  virtual int AddDetailAtLevel(const int iLevel, const double* iDetailValue) = 0;

/**
 * Removes a detail at a given level
 *
 * @param iLevel
 * The level for which to remove the detail
 *
 * @return
 * 1 if problems occured, 0 else
 */
  virtual int RemoveDetailAtLevel(const int iLevel) = 0;

/**
 * Gets the local frame for a point at a given level
 *
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
  virtual int GetLocalFrameAtLevel(const int iLevel, double* ioFrame) = 0;





protected :

  CATSobVertex (CATSobMesh * iMesh):CATSobCell(iMesh){};

  private:
    // Copy constructor and equal operator
    CATSobVertex (CATSobVertex &);
    CATSobVertex& operator=(CATSobVertex&);

public :
  /************* DEPRECATED ***********
 * Gets edges using the vertex.
 *
 * @param
 * The list of edges using the vertex.
 */
	virtual void GetEdges(CATLISTP(CATSobEdge)& ioEdges) = 0;
};

#endif
