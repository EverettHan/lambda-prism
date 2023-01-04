//=========================================================================
// Copyright Dassault Systemes Provence 2012, All rights reserved
//=========================================================================
//
// CATSmoConnexityFacesOperator.h
//
//=========================================================================
//
// Usage notes: Découpage en composantes connexes d'une liste de faces
//
//=========================================================================
// October,    2012 : RAQ : Création
//=========================================================================
#ifndef CATSmoConnexityFacesOperator_H
#define CATSmoConnexityFacesOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSobDiag.h"
#include "CATSobFace.h"
#include "CATSobListOfFace.h"


class ExportedByCATSmoOperators CATSmoConnexityFacesOperator
{
public:

  //Destructeur
  virtual ~CATSmoConnexityFacesOperator();

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Récupération des composantes connexes
  virtual CATSobDiag GetConnexComponents(CATLISTP(CATSobFace)*& oConnexSetOfFaces, int& oNbConnexSets) = 0;
  
  //Récupération des composantes connexes
  virtual CATSobDiag GetNbConnexComponents(int& oNbConnexSets) = 0;
  

protected:

  //Constructeur
  CATSmoConnexityFacesOperator();



private:

  //No default methods
  CATSmoConnexityFacesOperator(const CATSmoConnexityFacesOperator&);
  CATSmoConnexityFacesOperator& operator=(const CATSmoConnexityFacesOperator&);

};


/**
 * Création de l'opérateur
 **/
ExportedByCATSmoOperators
CATSmoConnexityFacesOperator* CATSmoCreateConnexityFacesOperator(const CATLISTP(CATSobFace)& iFaces);

#endif  //CATSmoConnexityFacesOperator_H


