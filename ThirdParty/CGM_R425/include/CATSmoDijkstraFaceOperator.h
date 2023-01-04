//===============================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//===============================================================================
//
// CATSmoDijkstraFaceOperator.h
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
// September,  2008 : RNO : Création
//===============================================================================
#if 0
#ifndef CATSmoDijkstraFaceOperator_H
#define CATSmoDijkstraFaceOperator_H

#include "CATSmoOperators.h"
#include "CATSobDiag.h"

class CATSobFace;
class CATSobEdge;
class CATSmoEdgeEvaluator;
class CATSobMesh;

#include "CATSobListOfFace.h"
#include "CATBoolean.h"


class ExportedByCATSmoOperators CATSmoDijkstraFaceOperator
{
public:

  //Constructeur
  // Un mesh + un evaluateur
  CATSmoDijkstraFaceOperator(CATSobMesh *iMesh,CATSmoEdgeEvaluator * iEval);
  //Destructeur
  virtual ~CATSmoDijkstraFaceOperator();

  
  

  // Compute Paths from the source edge (Call Run Once)
  // A n'appeler qu'une seule fois !!!.
  CATSobDiag Run(CATSobFace * iSource);
   
  // 
  // Get the ShortestPath ( an ordered sequence of faces) 
  // From the Source Edge to <iTo> Edge.
  // Peut etre appelee plusieurs fois
  // ATTENTION NE PAS CHANGER CELL RANK entre le Run et le Get
  CATSobDiag GetShortestPathTo(CATSobFace * iTo, CATLISTP(CATSobFace)* oPath, double & oCost);


private :
  // Copy constructor and equal operator
  CATSmoDijkstraFaceOperator (CATSmoDijkstraFaceOperator &);
  CATSmoDijkstraFaceOperator& operator=(CATSmoDijkstraFaceOperator&);

  //Compute "OneRing" around face
  int MyRing(CATSobFace * iSource,CATLISTP(CATSobFace)  & Ring);
  //
  CATSobMesh * _Mesh;
  CATSmoEdgeEvaluator * _Evaluator;
  CATBoolean _UseVertex;
  int * _Prev;
  int _Start;
  double * _Lambda;
};


#endif
#endif
