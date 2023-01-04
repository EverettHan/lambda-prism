//=========================================================================
// Copyright Dassault Systemes Provence 2012, All rights reserved
//=========================================================================
//
// CATSmoBorderEdgesExtractor.h
//
//=========================================================================
//
// Usage notes: Extraction des edges frontières d'un ensemble de faces
//
//=========================================================================
// October,    2012 : RAQ : Création
//=========================================================================
#ifndef CATSmoBorderEdgesExtractor_H
#define CATSmoBorderEdgesExtractor_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"


class ExportedByCATSmoOperators CATSmoBorderEdgesExtractor
{
public:

  //Destructeur
  virtual ~CATSmoBorderEdgesExtractor();

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Récupération de la frontière
  virtual const CATLISTP(CATSobEdge)& GetBorder() const = 0;


protected:

  //Constructeur
  CATSmoBorderEdgesExtractor();


private:

  //No default copy methods
  CATSmoBorderEdgesExtractor(const CATSmoBorderEdgesExtractor&);
  CATSmoBorderEdgesExtractor& operator=(const CATSmoBorderEdgesExtractor&);

};


/**
 * Creates the operator
 **/
ExportedByCATSmoOperators
CATSmoBorderEdgesExtractor* CATSmoCreateBorderEdgesExtractor(const CATLISTP(CATSobFace)& iFaces);


#endif  //CATSmoBorderEdgesExtractor_H


