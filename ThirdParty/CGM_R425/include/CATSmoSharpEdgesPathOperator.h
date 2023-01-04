//=================================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//=================================================================================
//
// CATSmoSharpEdgesPathOperator.h
//
//=================================================================================
//
// Usage notes: Calcul d'un chemin d'edges sharps entre deux vertex.
//
//=================================================================================
// 07.09.2017 : RAQ : Migration implémentation sur CATSmoEdgesPathOperator pour plus de généralité
// March,   2010 : RAQ : Creation
//=================================================================================
#ifndef CATSmoSharpEdgesPathOperator_H
#define CATSmoSharpEdgesPathOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Classe mère
#include "CATSmoEdgesPathOperator.h"

//Divers
#include "CATSobDiag.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"

class CATSobMesh;
class CATSobVertex;
class CATSmoEdgesPathOperator;

class CATSmoSharpEdgesPathOperator : public CATSmoEdgesPathOperator
{
public:

  //Constructeur
  ExportedByCATSmoOperators
    CATSmoSharpEdgesPathOperator(const CATSobMesh* ipSobMesh, const CATSobVertex* ipStartVertex, const CATSobVertex* ipEndVertex);

  //Destructeur
  ExportedByCATSmoOperators 
    ~CATSmoSharpEdgesPathOperator();

  //Run de l'opérateur
  ExportedByCATSmoOperators 
    CATSobDiag Run();

  //Récupération du chemin d'edge
  inline const CATLISTP(CATSobEdge)& GetEdgesPath() const { return CATSmoEdgesPathOperator::GetEdgesPath(); }

  //Récupération du chemin de vertex
  inline const CATLISTP(CATSobVertex)& GetVerticesPath() const { return CATSmoEdgesPathOperator::GetVerticesPath(); }
};


/**
 * Calcul d'un chemin d'edges sharp entre deux vertex, retourne le chemin d'edges.
 **/
ExportedByCATSmoOperators
CATSobDiag CATSmoComputeSharpEdgesPathBetweenVertices(const CATSobMesh* iSobMesh, const CATSobVertex* iStartVertex, const CATSobVertex* iEndVertex,
                                                      CATLISTP(CATSobEdge)& oSharpEdgesPath);

/**
 * Calcul d'un chemin d'edges sharp entre deux vertex, retourne le chemin de vertex.
 **/
ExportedByCATSmoOperators
CATSobDiag CATSmoComputeSharpEdgesPathBetweenVertices(const CATSobMesh* iSobMesh, const CATSobVertex* iStartVertex, const CATSobVertex* iEndVertex,
                                                      CATLISTP(CATSobVertex)& oVerticesPath);



#endif


