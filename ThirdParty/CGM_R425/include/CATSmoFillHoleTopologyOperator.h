//========================================================================================
// Copyright Dassault Systemes Provence 2018, All Rights Reserved
//========================================================================================
//
// CATSmoFillHoleTopologyOperator.h
//
//========================================================================================
//
// Usage notes : Operator to quad mesh a hole in a subdivision mesh.
//               A hole is defined as a contour defined by a set of edges lists.
//               Each edges list is a 'side' of the hole.
//
//========================================================================================
// 07.02.2018 : RAQ : Création
//========================================================================================
#ifndef CATSmoFillHoleTopologyOperator_H
#define CATSmoFillHoleTopologyOperator_H

//Pour l'export
#include "ExportedByCATSmoRemesh.h"

//Structure de subdivision
#include "CATSobDiag.h"
#include "CATSobVertex.h"
#include "CATSobEdge.h"
#include "CATSobFace.h"
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"

//Opérateurs de subdivision
#include "CATSmoSubdivisionMeshOperator.h"


class CATSobMesh;
class CATSmoMeshTopoModifOperator;


class CATSmoFillHoleTopologyOperator : public CATSmoSubdivisionMeshOperator
{
public:

  //Destructor
  ~CATSmoFillHoleTopologyOperator();

  //Allows the operator to add a triangle if the total number of edges in the contour is even.
  virtual void SetAddTriangleIfOddContour() = 0;

  //Disables mesh updating : warning operator checks may fail
  virtual void SetDisableMeshUpdate() = 0;
  
  //Run : creates the topology
  CATSobDiag Run() { return CATSmoSubdivisionMeshOperator::Run(); }

  //Retreives all the created faces
  virtual const CATLISTP(CATSobFace)& GetNewFaces() const = 0;

  //Retreives all the created vertices
  virtual const CATLISTP(CATSobVertex)& GetNewVertices() const = 0;

  //Check whether mesh orientation has been reversed
  virtual CATBoolean GetMeshOrientationHasBeenReversed() const = 0;


protected:

  //Constructor
  CATSmoFillHoleTopologyOperator(CATSobMesh* ipMesh, CATSmoMeshTopoModifOperator* ipTopoModifOpe);

};

/**
 * Creates the operator.
 *
 * @param ipMesh
 * Current subdivision mesh
 * @param ipArrayOfEdgesList
 * An array of edges list, each entry defining the edges on the associated side of the contour.
 * Two consecutive entries represent two connex sides in the countour.
 * @param iNbSidesInContour
 * The number of sides of the contour.
 * @param ipContoursOrientation
 * Optionnal. Each entry indicates if the edges are given in the same order as the array ipArrayOfEdgesList.
 * A strictly positive value means 'same order', a strictly negative value means 'reversed order'.
 * If the parameter is null, the operator computes the ordering itself.
 * @param ipTopoModifOperator
 * Optionnal. The operator to follow all the chages in the mesh, often required for topological operators.
 * 
 * @return
 * A pointer to an instance of the operator.
 **/
ExportedByCATSmoRemesh
CATSmoFillHoleTopologyOperator* CATSmoCreateFillHoleTopologyOperator(CATSobMesh* ipMesh,
                                                                     CATLISTP(CATSobEdge)* ipArrayOfEdgesList, const unsigned int iNbSidesInContour,
                                                                     int* ipContoursOrientation = 0,
                                                                     CATSmoMeshTopoModifOperator* ipTopoModifOperator = 0);

/**
* Creates the operator.
*
* @param ipMesh
* Current subdivision mesh
* @param ipArrayOfVerticesList
* An array of vertices list, each entry containing the vertices on the corresponding side.
* The vertices must be ordered.
* @param iNbSidesInContour
* The number of sides of the contour.
* @param ipTopoModifOperator
* Optionnal. The operator to follow all the chages in the mesh, often required for topological operators.
*
* @return
* A pointer to an instance of the operator.
**/
ExportedByCATSmoRemesh
CATSmoFillHoleTopologyOperator* CATSmoCreateFillHoleTopologyOperator(CATSobMesh* ipMesh,
                                                                     CATLISTP(CATSobVertex)* ipArrayOfVerticesList, const unsigned int iNbSidesInContour,
                                                                     CATSmoMeshTopoModifOperator* ipTopoModifOperator = 0);

#endif  //CATSmoFillHoleTopologyOperator_H


