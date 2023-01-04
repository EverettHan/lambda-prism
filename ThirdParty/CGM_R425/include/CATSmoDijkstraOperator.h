//===============================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//===============================================================================
//
// CATSmoDijkstraOperator.h
//
//===============================================================================
//
// Usage notes: 
// Calcul des plus courts chemins depuis une source selon l'algorithme de Dijkstra
// La "distance" d'un vertex a un autre est donnee par l'evaluateur d'arete.
// L'algo tourne en ~n*log(n) pour le run et on a tous les plus courts chemin depuis une source.
// Cette classe est donc multi-run
//
//===============================================================================
// August,  2005 : RNO : Création
//===============================================================================
#ifndef CATSmoDijkstraOperator_H
#define CATSmoDijkstraOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSobDiag.h"
#include "CATSobListOfVertex.h"
#include "CATSobListOfEdge.h"

class CATSobVertex;
class CATSobEdge;
class CATSmoEdgeEvaluator;
class CATSobMesh;

class CATSmoDijkstraOperatorPrivate;


class ExportedByCATSmoOperators CATSmoDijkstraOperator
{
public:

/**
 * Builds the operator.
 *
 * @param iMesh
 * A base mesh
 * @param iEval
 * An edge evaluator to retrieve the shortest path with respect to this criterion.
 **/
  CATSmoDijkstraOperator(CATSobMesh* iMesh, CATSmoEdgeEvaluator* iEval);

/**
 * @nodoc
 **/
  virtual ~CATSmoDijkstraOperator();

/**
 * Computes the path from a given vertex, to be called once.
 *
 * @param iSource
 * The beginning vertex of all paths
 * @param iEndVertex
 * Optionnal : an end vertex to restrict the computation to the shortest path from iSource to iEndVertex
 *
 * @return
 * CATSobDiag_OK if no errors, else se CATSobDiag.h
 **/
  CATSobDiag Run(CATSobVertex* iSource, const CATSobVertex* iEndVertex = 0);

/**
 * Gets the shortest path to a given vertex.
 *
 * @param iTo
 * The end vertex of the path
 * @param opVerticesPath
 * If opVerticesPath is not null, *opVerticesPath will be filled with the path of vertices : opVerticesPath[1]=iTo --> opVerticesPath[NbVerticesInPath]=iSource
 * @param opEdgesPath
 * If opEdgesPath is not null, *opEdgesPath will be filled with the path of edges.
 * @param opCost
 * If opCost is not null, *opCost will contain the cost of the shortest path.
 **/
  CATSobDiag GetShortestPathTo(CATSobVertex* iTo, CATLISTP(CATSobVertex)* opVerticesPath = 0, CATLISTP(CATSobEdge)* opEdgesPath = 0, double* opCost = 0);


/**
 * DEPRECATED : TO BE REMOVED SOON....
 *
 * Gets the shortest path to a given vertex as a vertices list.
 **/
  CATSobDiag GetShortestPathTo(CATSobVertex * iTo, CATLISTP(CATSobVertex)* oPath, double & oCost);

private :

  // Copy constructor and equal operator
  CATSmoDijkstraOperator (CATSmoDijkstraOperator &);
  CATSmoDijkstraOperator& operator=(CATSmoDijkstraOperator&);

  //--------- Data :
  CATSmoDijkstraOperatorPrivate* _DijkstraOperatorPrivate;
};


#endif

