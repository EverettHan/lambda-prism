//====================================================================
// Copyright Dassault Systemes Provence 2017, all rights reserved 
//====================================================================
//
// CATSmoXtrudeNEdgesUtilities.h
//
//====================================================================
//
// Usage notes: Some functions for the edges extrusion operator CATSmoXtrudeNEdgesOperatorCx2
// and the edges extrusion parameter CATSmoXtrudeNEdgesParameter
//
//====================================================================================
// November   2017 : RBD : Creation
//====================================================================================
#ifndef CATSmoXtrudeNEdgesUtilities_H
#define CATSmoXtrudeNEdgesUtilities_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"

#include "CATBoolean.h"
#include "CATMathPoint.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATMathVector.h"

class CATSobVertex;
class CATSobEdge;

#define RBDNewLength // NEW ADVANCED MODE : Min Length, direction et longueur suivant les arêtes (au lieu des sommets)

/** DEPRECATED (see InitStdExtrude below)
 * Initialization of the Edges extrusion (STANDARD mode).
 * 
 * @param iListEdges
 * The list of connected edges to extrude
 * @param iVertexEList
 * The list of vertices of the edges
 * @param iIsFixedDirection
 *    TRUE if the direction is fixed
 *    FALSE if the direction must be computed
 * @param iFixedDirection
 * The direction (normalized) if iIsFixedDirection is TRUE
 *
 * @return ioVect
 * An auxiliary array of CATMathVector. Contains the extrusion vector for each free edge
 * @return ioPtS
 * An auxiliary array of CATMathPoint. Contains the coordonnates of each vertex of the free edges
 * @return ioPtE
 * An auxiliary array of CATMathPoint. Contains the coordonnates of each extruded vertex
 * @return oValmin
 * The minimum value to initialize the extrusion length
 * DEPRECATED **/
void InitStdExtrude(const CATLISTP(CATSobEdge) &iListEdges, const CATLISTP(CATSobVertex) &iVertexEList, const CATBoolean iIsFixedDirection, const CATMathVector& iFixedDirection,
                    CATMathVector* &ioVect, CATMathPoint* &ioPtS, CATMathPoint* &ioPtE, double &oValmin);

/**
* Initialization of the Edges extrusion (STANDARD mode).
*
* @param iListEdges
* The list of connected edges to extrude
* @param iVertexEList
* The list of vertices of the edges
* @param iIsFixedDirection
*    TRUE if the direction is fixed
*    FALSE if the direction must be computed
* @param iFixedDirection
* The direction (normalized) if iIsFixedDirection is TRUE
* @param iIsAlongMehLines 
*  0 : No extrusion along mesh lines (the direction must be computed or must be fixed to a unique direction)
*  1 : The extrusion direction is the mean between two extremal mesh lines directions at each vertex
*  2 : The extrusion direction is the mesh line that is closer to a direction orthogonal at each vertex
*
* @return ioVect
* An auxiliary array of CATMathVector. Contains the extrusion vector for each free edge
* @return ioPtS
* An auxiliary array of CATMathPoint. Contains the coordonnates of each vertex of the free edges
* @return ioPtE
* An auxiliary array of CATMathPoint. Contains the coordonnates of each extruded vertex
* @return oValmin
* The minimum value to initialize the extrusion length
*/
void InitStdExtrude(const CATLISTP(CATSobEdge) &iListEdges, const CATLISTP(CATSobVertex) &iVertexEList, const CATBoolean iIsFixedDirection, const CATMathVector& iFixedDirection,
                    const int iIsAlongMeshLines, CATMathVector* &ioVect, CATMathPoint* &ioPtS, CATMathPoint* &ioPtE, double &oValmin);



/**
* Extrusion d'aretes : Calcul du vecteur d'extrusion d'une arete  (STANDARD mode).
*
* @param iEdge
* The free edge to extrude
* @param iIsFixedDirection
*    TRUE if the direction is fixed
*    FALSE if the direction must be computed 
* @param iFixedDirection
* The direction (normalized) if iIsFixedDirection is TRUE
*
* @return
* The extrusion vector (direction and length) of the free edge 
*/
CATMathVector ExtrusionVector(const CATSobEdge* iEdge, const CATBoolean iIsFixedDirection, const CATMathVector& iFixedDirection);


/**
* Extract the vertices of a list of connected edges to extrude (STANDARD mode).
*
* @param iListEdges
* The list of connected edges to extrude
* @param ioVertexEList
*/
CATSobDiag ExtractEndVertices(const CATLISTP(CATSobEdge) &iListEdges, CATLISTP(CATSobVertex) &ioVertexEList);


/**
* Initialization of the Edges extrusion (ADVANCED mode).
*
* @param iEdgesToXtrude
* The list of edges to extrude
* @param iMustInitDirection
* TRUE if the extrusion direction must be initialized
* @param iMustInitAngle
* TRUE if the extrusion angle must be initialized
* @param iMustInitLength
* TRUE if the extrusion length must be initialized
*
* @return oAdvDraftDirection
* The extrusion direction (or drafting direction)
* @return oAdvAngleDeg
* The extrusion angle (or drafting angle)
* @return oAdvLength
* The extrusion length (or drafting length)
*/
void InitAdvExtrude(const CATLISTP(CATSobEdge)& iEdgesToXtrude, const CATBoolean iMustInitDirection, const CATBoolean iMustInitAngle, const CATBoolean iMustInitLength,
                    CATMathVector& oAdvDraftDirection, double& oAdvAngleDeg, double& oAdvLength);




/**
* Utilities for Edges extrusion (STANDARD and ADVANCED mode).
*
*/
// Calcul du vecteur median
CATMathVector ComputeVector(const int iNbVectors, CATMathVector * iTabVectors);

// Calcul de la direction faisant un angle 0 par rapport au draft (ADVANCED mode)
CATSobDiag ComputeZeroDirection(const CATMathVector &iAdvDraftDirection, const int iAdvOrientXtrudeDir, const CATMathPoint &iPtPrec, const CATMathPoint &iPt, const CATMathPoint &iPtSuiv, CATMathVector &oZeroDir);

// Calcul de la direction faisant un angle 0 par rapport au draft (cas des extrémités) (ADVANCED mode)
CATSobDiag ComputeZeroDirection(const CATMathVector &iAdvDraftDirection, const int iAdvOrientXtrudeDir, const CATMathPoint &iPtPrec, const CATMathPoint &iPt, CATMathVector &oZeroDir);

// Orientation de la direction de draft par rapport à la liste d'arêtes (ADVANCED mode)
void OrientDraftDir(const CATLISTP(CATSobEdge) &iListEdges, CATMathVector &ioAdvDraftDirection, int &oAdvOrientDraft);

// Orientation de la direction d'extrusion par rapport à la liste d'arêtes (ADVANCED mode)
void OrientXtrudeDir(const CATMathVector & iAdvDraftDirection, const CATLISTP(CATSobEdge) &iListEdges,
                     CATLISTV(CATMathPoint)* PtS, const int iAdvOrientDraft, int &oAdvOrientXtrudeDir);


#endif

