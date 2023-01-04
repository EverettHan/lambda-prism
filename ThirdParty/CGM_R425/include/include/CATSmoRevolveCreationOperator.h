//======================================================================
// Copyright Dassault Systemes Provence 2007, all rights reserved 
//======================================================================
//
// CATSmoRevolveCreationOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
//  December,     2008 : RBD : Ajout methode SetAutoWeight pour les vertex
//  September,    2008 : RBD : Ajout methode SetWeightsOnLongitudinalEdges
//  June,         2008 : RBD : Ajout SetRevolutionLandmark et SetAngleSector
//  December,     2007 : JCV : Creation
//======================================================================
#ifndef CATSmoRevolveCreationOperator_H
#define CATSmoRevolveCreationOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSmoFillRevolveType.h"

// Objets CGM
//#include "CATMathAxis.h"
#include "CATMathPoint.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATListOfInt.h"
#include "CATBoolean.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;

class ExportedByCATSmoOperators CATSmoRevolveCreationOperator: public CATSmoSubdivisionMeshOperator
{
public:
  
  //Destructeur
  virtual ~CATSmoRevolveCreationOperator();

  virtual void SetProfileToRevolve (const CATLISTV(CATMathPoint) &iPointsList,
                                    const CATListOfInt           &iWeightsList,
                                    const CATBoolean              iIsClose = FALSE) = 0;

  // axe de rotation
  virtual void SetRevolutionAxis (const CATMathPoint &iOrigin, const CATMathDirection &iAxeRot) = 0;

  // axe de rotation + 1er vecteur du repère (En general oriente du cote du profil).
  virtual void SetRevolutionLandmark (const CATMathPoint &iOrigin, const CATMathDirection &iAxeRot, const CATMathDirection & iFirstVector) = 0;
 
  // angle de revolution en degrés
  virtual void SetRevolutionAngle(const double iAngleDeg) = 0;

  // Secteur angulaire revolution en degrés avec i1stAngleDeg et i2ndAngleDeg entre 0 et 2*Pi.
  // Pris en compte TOUJOURS dans le sens trigo :
  //    Donc de i1stAngleDeg vers i2ndAngleDeg si i2ndAngleDeg > i1stAngleDeg
  //         de i1stAngleDeg - 2*Pi vers i2ndAngleDeg si i1stAngleDeg > i2ndAngleDeg
  // Si i2ndAngleDeg - i1stAngleDeg < iEpsAngleDeg on force le resultat sur [0, 2*Pi]
  virtual void SetAngleSector(const double i1stAngleDeg, const double i2ndAngleDeg, const double iEpsAngleDeg = 5.0) = 0;


  // Nombre de secteurs
  virtual void SetNbSections(const int iNbSectors = 8) = 0;

  // Remplissage du haut et du bas de la surface 
  // (Seulement cas OUVERT  et si le nombre de secteurs est PAIR) 
  virtual void FillTopOrBottom(const CATSmoFillRevol iFill = CATSmoNoFillRevol) = 0;

  // Poids sur les edges du profil (= edges dans le sens longitudinal).
  // Le nombre de poids pris en compte est égal au nombre de point du profil (profil fermé)
  // ou au nombre de points - 1 (profil ouvert); En cas d'ambiguité, on gère.
  // Le poids varie entre -100 et +100.
  // Si un poids est > 0, l'edge est marquée smooth.
  // Si un poids est < 0, l'edge est marquée sharp.
  // Dans le cas où on rempli le bas ou le haut du mesh, on applique le poid correspondant
  // iWeightsOnBottomEdges ou iWeightsOnTopEdges
  virtual void SetWeightsOnLongitudinalEdges(const CATListOfInt &iWeightsOnLongEdges,
                                             const int iWeightsOnBottomEdges = 100, const int iWeightsOnTopEdges = 100) = 0;

  // Activation du poid automatique sur les vertex.
  virtual void SetAutoWeight(const CATBoolean iAutoWeight = 1) = 0;

protected :
  //Constructeur
  CATSmoRevolveCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe);
  
  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

private :

};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoRevolveCreationOperator* CATSmoCreateRevolveCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);

#endif

