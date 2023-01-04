//====================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//====================================================================
//
// CATSobMRSubdivisionOperator.h
//
//====================================================================
//
// Usage notes: Opérateur de subdivision pour la multirésolution
//
//====================================================================
// 30.01.2018 : RAQ : Optimisations perfos
// 16.01.2018 : RAQ : Ajout SubdivideEdge
// October,   2004 : RAQ : Optimisation mémoire
// March,     2004 : RAQ : Creation
//====================================================================
#ifndef CATSobMRSubdivisionOperator_H
#define CATSobMRSubdivisionOperator_H

#include "CATSobOperators.h"
#include "CATSobDiag.h"

class CATSobMesh;
class CATSobFace;
class CATSobEdge;
class CATSobVertex;
class CATSobOneRingData;

enum CATSobMRSubdivOpeMode{ MR_BASIC, MR_ADVANCED };


class ExportedByCATSobOperators CATSobMRSubdivisionOperator
{
public:
  
/**
 * @nodoc
 **/
  virtual ~CATSobMRSubdivisionOperator();

/**   DO NOT USE: Use SubdivideFace
 * 
 * Runs the operator
 *
 * @return
 * CATSobDiag_OK if no problems occured, else a CATSobDiag (see CATSobDiag.h)
 **/
  virtual CATSobDiag Run() = 0;

/**
 * Subdivide all the faces to the same level (not adaptive)
 * See the operator's diag.
 **/
  virtual void SetSubdivideAll() = 0;

/**
 * Subdivide only the faces containing details,
 * this operation can force neighbour faces to be subdivided (adaptive)
 * See the operator's diag.
 **/
  virtual void SetSubdivideDetailsOnly() = 0;

/**
 * Subdivide a given face to a given level,
 * neighbour faces can be subdivided.
 **/
  virtual CATSobDiag SubdivideFace(CATSobFace* iFace, const int iLevel) = 0;
  
/**
  * Subdivide an edge to a given level,
  * Neighbour can be subdivided if needed.
  **/
  virtual CATSobDiag SubdivideEdge(CATSobEdge* iEdge, const int iLevel) = 0;

/**
  * Compute the one ring of subdivision points around a closed vertex
  **/
  virtual CATSobDiag GetOneRingOfPointsAroundClosedVertex(CATSobVertex* ipVertex, CATSobOneRingData& oOneRingData, const int iLevel) = 0;

/**
 * Get the diag of the operator
 *
 * @return
 * CATSobDiag_OK if no problems occured, see CATSobDiag.h
 **/
  virtual CATSobDiag GetDiag() = 0;

protected:
  
  CATSobMRSubdivisionOperator(CATSobMesh* iMesh);

private:
  //Copy constructor and equal operator (to minimize dll size)
  CATSobMRSubdivisionOperator(CATSobMRSubdivisionOperator&);
  CATSobMRSubdivisionOperator& operator=(CATSobMRSubdivisionOperator&);

};


ExportedByCATSobOperators 
CATSobMRSubdivisionOperator* CATSobCreateMRSubdivision(CATSobMesh*           iMesh,
                                                       const int             iLevel,
                                                       CATSobMRSubdivOpeMode iMode=MR_BASIC);

#endif
