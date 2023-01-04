//===================================================================================
// Copyright Dassault Systemes Provence 2012, All Rights Reserved
//===================================================================================
//
// CATSmoFixInternalValence2VertexOperator.h
//
//===================================================================================
//
// Usage notes: Opérateur de régularisation de tous les vertex de valence 2 internes
//              dans un mesh.
//
//===================================================================================
// April,   2012 : RAQ : Creation
//===================================================================================
#ifndef CATSmoFixInternalValence2VertexOperator_H
#define CATSmoFixInternalValence2VertexOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Classe mère
#include "CATSmoSubdivisionMeshOperator.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoFixInternalValence2VertexOperator : public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoFixInternalValence2VertexOperator();



protected:

  //Constructeur
  CATSmoFixInternalValence2VertexOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);
};


/**
 * Creates the operator
 **/
ExportedByCATSmoOperators
CATSmoFixInternalValence2VertexOperator* CATSmoCreateFixInternalValence2Operator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);

#endif  //CATSmoFixInternalValence2VertexOperator_H


