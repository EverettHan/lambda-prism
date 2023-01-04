//=====================================================================================================
// Copyright Dassault Systemes Provence 2005-2007, All Rights Reserved 
//=====================================================================================================
//
// CATSmoSubdivisionMatrixOperator.h
//
//=====================================================================================================
//
// Usage notes: Calcul des coefficients de la matrice de subdivision (cf. doc - à venir... -)
//
//=====================================================================================================
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// 01-09-05 RAQ Création
//=====================================================================================================
#ifndef CATSmoSubdivisionMatrixOperator_H
#define CATSmoSubdivisionMatrixOperator_H

#include "CATSmoOperators.h"
#include "CATSobDiag.h"

//Structure subdivision
// #include "CATSobFace.h" // MMO BAD004
#include "CATSobListOfFace.h"
#include "CATSobListOfVertex.h" // MMO BAD004

class CATSobMesh;
class CATSobFace; // MMO BAD004
class CATSobEdge; // MMO BAD004

//Divers
#include "CATBoolean.h"


/*////////////////////////////////////////////////////////////////////////////////////////////////////////

  This operator is dedicated to the computing of the linear dependance of the vertices of the mesh
  on a given subdivision point.

  At a subdivision level 'n', a given subdivision point Pi can be expressed the following way:
  Pi=sum( a[j] * V[j], j=1..NbVertices) with { V[j], j=1..NbVertices} are the vertices of the mesh and
  { a[j], j=1..NbVertices} scalars.
  However a small number of mesh vertices are involved in the subdivision of Pi.
  This operator computes the vertices used and their associated reals a[j].

  How to use this operator:

  - You build the operator with CATSmoCreateSubdivisionMatrixOperator();
  - You give the part of the mesh on which you want to compute the coefficients with SetZone(...)
  - You give the subdivision level
  - You run the operator

  - To retrieve the involved vertices:
    When setting the zone, the operator looks for ALL the vertices involved in the subdivision of
    this zone -> Bigger the zone, the more involved vertices.
    They are retrieved by the method: GetInvolvedVertices(...).
  - To retrieve the coefficients of Pi:
    Pi can be located with (u, v) coordinates in a face, see CATSobFace.h or CATSobEdge.h.
    You must use the right method GetCoefForPoint(...) depending on where your point is
    located (Face, Edge, Vertex).
    The method gets back a pointer to an array of double "ioCoeff" containing the scalar { a[j] }.
    Its size is the size of the list returned by GetInvolvedVertices(...).
    You have the following mapping between coeff and vertices:
    ioCoeff[i] is the coefficient respect to the vertex InvolvedVertices[i+1].
    Array index begins to 0 for ioCoeff and to 1 for Vertices list.

  - This operator is MULTI-RUN:
    This means that after a run you can set another zone and run again,
                                            another level and run again for the same zone.

////////////////////////////////////////////////////////////////////////////////////////////////////////*/



class ExportedByCATSmoOperators CATSmoSubdivisionMatrixOperator
{
public:

/**
 * @nodoc
 * Destructor
 **/
  virtual ~CATSmoSubdivisionMatrixOperator() {}

/**
 * Set the subdivision level for which you want to retrieve the coefficients.
 * 
 * @param iLevel
 * The subdivision level, it must be >0
 **/
  virtual void SetLevel(const int iLevel) = 0;

/**
 * Set the faces on which you want to retrieve the coefficients.
 *
 * @param iFacesZone
 * A list of faces defining the zone
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag SetZone(const CATLISTP(CATSobFace)* iFacesZone) = 0;

/**
 * Set whether a connexity check must be done on the mesh zone given by
 * the method SetZone(...) during the operator run. This ensures that
 * the mesh zone can be seen as a valid new base mesh and that a subdivision
 * can be processed on it. By default, no check is performed
 *
 * @param iOnOff
 * Perform the check if iOnOff is TRUE, else no check
 **/
  virtual void SetCheckConnexity(const CATBoolean iOnOff = TRUE) = 0;

/**
 * Run the operator
 *
 * @return
 * CATSobDiag_OK if no problem, else see CATSobDiag.h
 **/
  virtual CATSobDiag Run() = 0;

/**
 * Get all the vertices involved in the subdivision of the mesh zone
 * given by the method SetZone(...).
 *
 * @param ioInvolvedVertices
 * A reference to a list of CATSobVertex* that will contain
 * the involved vertices.
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetInvolvedVertices(CATLISTP(CATSobVertex)& ioInvolvedVertices) = 0;
  
/**
 * Get the coefficients for a vertex included in the zone given
 * by the method SetZone(...).
 *
 * @param iVertex
 * The vertex
 * @param ioCoeff
 * A pointer to an array that will contain the coefficients.
 * This array MUST NOT be deleted
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetCoefForPoint(const CATSobVertex* iVertex, double*& ioCoeff) = 0;
  
/**
 * Get the coefficients for a point on an edge.
 * The edge must be included in the zone given by the method SetZone(...).
 * For the point coordinate, see CATSobEdge.h or CATSobFace.h
 *
 * @param iEdge
 * The edge
 * @param u
 * The coordinate of the point on the edge,
 * with 0 <= u <= 2^Level where Level is the level given in SetLevel(...).
 * @param ioCoeff
 * A pointer to an array that will contain the coefficients.
 * This array MUST NOT be deleted
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetCoefForPoint(const CATSobEdge* iEdge, const int u, double*& ioCoeff) = 0;

/**
 * Get the coefficients for a point identified by its (u, v) coordinate on a face.
 * The face must be included in the zone given by the method SetZone(...).
 * For the point coordinates, see CATSobEdge.h or CATSobFace.h
 * (u, v) are such that:
 * - If the face is quad: 0 <= u, v <= 2^Level
 * - If the face is triangular: 0 <= u, v <= 2^(Level-1)
 * where Level is the subdivision level set with the method SetLevel(...)
 *
 * @param iFace
 * The face
 * @param u
 * The first coordinate of the point in the face,
 * @param v
 * The second coordinate of the point in the face,
 * @param ioCoeff
 * A pointer to an array that will contain the coefficients.
 * This array MUST NOT be deleted
 * @param iDaughterFaceIndex
 * If the face is triangular, identify on which sub face the point is located
 * (see CATSobFace.h for more details)
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetCoefForPoint(const CATSobFace* iFace, const int u, const int v, double*& ioCoeff, const int iDaughterFaceIndex = 0) = 0;

/**
 * Get the operator diag
 *
 * @return
 * CATSobDiag_OK if internal process succeded, else see CATSobDiag.h
 **/
  virtual CATSobDiag GetDiag() = 0;

protected:

  //Constructor
  CATSmoSubdivisionMatrixOperator() {}

};


/**
 * Constructs this operator
 *
 * @return
 * A pointer to the operator.
 **/
ExportedByCATSmoOperators
CATSmoSubdivisionMatrixOperator* CATSmoCreateSubdivisionMatrixOperator();


#endif





