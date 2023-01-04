//=================================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//=================================================================================
//
// CATSmoEdgesPathOperator.h
//
//=================================================================================
//
// Usage notes : Calcul d'un chemin d'edges entre deux vertex parmis toutes les
//               edges vérifiant un critère donné
//
//=================================================================================
// 07.09.2017 : RAQ : Creation
//=================================================================================
#ifndef CATSmoEdgesPathOperator_H
#define CATSmoEdgesPathOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSobDiag.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"
#include "CATLib.h"

//STL
#ifndef _AIX_SOURCE
#include <functional>
#endif  //!_AIX_SOURCE

class CATSobMesh;
class CATSobVertex;
class CATSobHashTableWithAssoc;



class CATSmoEdgesPathOperator
{
public:

  //Constructeur
  ExportedByCATSmoOperators
    CATSmoEdgesPathOperator(const CATSobMesh* ipSobMesh, const CATSobVertex* ipStartVertex, const CATSobVertex* ipEndVertex);

  //Destructeur
  ExportedByCATSmoOperators
    virtual ~CATSmoEdgesPathOperator();

  //Run de l'opérateur
  //La lambda ifEdgeSelectionFunction renvoie true si l'edge envoyée à argument est candidate à être utilisée dans le chemin, false sinon.
#ifndef _AIX_SOURCE
  typedef std::function<bool(const CATSobVertex*, const CATSobEdge*)> EdgeSelectionFunction_t;
#else
  typedef bool (*EdgeSelectionFunction_t) (const CATSobVertex*, const CATSobEdge*);
#endif  //!_AIX_SOURCE
  
  ExportedByCATSmoOperators
    virtual CATSobDiag Run(EdgeSelectionFunction_t ifEdgeSelectionFunction);

  //Récupération du chemin d'edge
  ExportedByCATSmoOperators
    const CATLISTP(CATSobEdge)& GetEdgesPath() const;

  //Récupération du chemin de vertex
  ExportedByCATSmoOperators
    const CATLISTP(CATSobVertex)& GetVerticesPath() const;

private:

  //Calcul d'un chemin d'edges sharps entre deux vertex
  CATSobDiag ComputeSharpEdgesPathBetweenVertices(const CATSobVertex* iStart, const CATSobVertex* iEnd, CATLISTP(CATSobEdge)& oSharpEdgesPath) const;

  //Décodage du chemin entre deux vertex
  CATSobDiag DecodePath(const CATSobVertex* iStart, const CATSobVertex* iEnd,
                        const CATSobHashTableWithAssoc& iActiveVerticesPathHT, CATLISTP(CATSobEdge)& oSharpEdgesPath, CATLISTP(CATSobVertex)& oVerticesPath) const;

  //Set du diag
  CATSobDiag SetDiag(const CATSobDiag iDiag);



  //--------- Data:
  CATSobDiag _Diag;
  const CATSobMesh* m_pSobMesh;
  const CATSobVertex *m_pStartVertex, *m_pEndVertex;
  CATLISTP(CATSobEdge) m_sharpEdgesPath;
  CATLISTP(CATSobVertex) m_verticesPath;
};

#endif  //CATSmoEdgesPathOperator_H


