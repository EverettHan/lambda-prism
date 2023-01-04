//======================================================================
// Copyright Dassault Systemes Provence 2007, all rights reserved 
//======================================================================
//
// CATSmoExtrudeCreationOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
// December, 2010 : RBD : Ajout methodes pour : Rotations, homothetie(s), ... comme pour les tuyaux
// January,  2009 : RBD : Ajout méthode SetWeightsOnLongitudinalEdges
// December, 2008 : RBD : Ajout methode SetAutoWeight pour les vertex
// August,   2008 : RBD : Gestion de deux longueurs d'extrusion (au lieu d'une seule)
//                           ajout SetNbSectors et orientation du basemesh
// December, 2007 : JCV : Creation
//======================================================================
#ifndef CATSmoExtrudeCreationOperator_H
#define CATSmoExtrudeCreationOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"

// Objets CGM
#include "CATMathDirection.h"
#include "CATLISTV_CATMathPoint.h"
#include "CATListOfInt.h"

#include "CATBoolean.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;

class ExportedByCATSmoOperators CATSmoExtrudeCreationOperator: public CATSmoSubdivisionMeshOperator
{
public:
  
  //Destructeur
  virtual ~CATSmoExtrudeCreationOperator();

  virtual void SetProfileToExtrude(const CATLISTV(CATMathPoint) &iPointsList,
                                   const CATListOfInt           &iWeightsList,
                                   const CATBoolean              iIsClose = FALSE) = 0;

  // direction d'extrusion
  virtual void SetExtrusionDirection (const CATMathDirection &iDirection) = 0;
 
  // longueur d'extrusion
  virtual void SetExtrusionLength(const double i1stLength, const double i2ndLength=0.0, const double iEpsLength = 0.01) = 0;

  // Nombre de secteurs.
  virtual void SetNbSectors(const int iNbSectors = 1) = 0;

  // Get Nombre de secteurs.
  virtual int GetNbSectors() = 0;

  // Poids sur les edges du profil (= edges dans le sens longitudinal).
  // Le nombre de poids pris en compte est égal au nombre de point du profil (profil fermé)
  // ou au nombre de points - 1 (profil ouvert); En cas d'ambiguité, on gère.
  // Le poids varie entre -100 et +100.
  // Si un poids est > 0, l'edge est marquée smooth.
  // Si un poids est < 0, l'edge est marquée sharp.
  virtual void SetWeightsOnLongitudinalEdges(const CATListOfInt &iWeightsOnLongEdges) = 0;

  // Activation du poid automatique sur les vertex.
  virtual void SetAutoWeight(const CATBoolean iAutoWeight = 1) = 0;

  // Set du repère de la section de l'extrusion 
  // (Utile pour définir l'homothétie et la rotation)
  virtual void SetProfileAxis(const CATMathPoint       &iProfOrigin,
                      const CATMathDirection   &iProfU,
                      const CATMathDirection   &iProfV) = 0;
  // Applique un coefficient d'homothetie GLOBAL sur la section
  virtual void SetHomotheticCoeff(const double iHomotheticCoeff = 1.0) = 0;

  // Fixe les coefficients d'homothétie sur la 1ere et la derniere section 
  // pour une homothetie INCREMENTALE
  virtual void SetHomotheticCoeffs(const double iStartHomotheticCoeff, const double iEndHomotheticCoeff) = 0;

  // Retourne le coefficient d'homothétie sur la section
  virtual double GetHomotheticCoeff() = 0;

  // Retourne les coefficients d'homothétie sur la 1ere et la derniere section
  virtual void GetHomotheticCoeffs(double& oStartHomotheticCoeff, double& oEndHomotheticCoeff) = 0;

  // Change X en -X du repere local de la section si iInvert == TRUE
  virtual void InvertXProfil(const CATBoolean iInvert = TRUE) = 0;

  // Change Y en -Y du repere local de la section si iInvert == TRUE
  virtual void InvertYProfil(const CATBoolean iInvert = TRUE) = 0;

  //-------------------------
  // Permute les axes du repere local de la section
  // iFlip == 0 : Profil dans le repere (O, X, Y, Z)
  // iFlip == 1 : Profil dans le repere (O, -X, Y, Z)
  // iFlip == 2 : Profil dans le repere (O, -X, -Y, Z)
  // iFlip == 3 : Profil dans le repere (O, X, -Y, Z)
  //-------------------------
  virtual void FlipProfil(const int iFlip = 0) = 0;

  // Fait une rotation CONSTANTE du profil autour de la courbe guide, d'un angle donné 
  virtual void RotateProfil(const double iAngleDegree = 0.0) = 0;

  //-------------------------
  // Fait une rotation INCREMENTALE du profil autour de la courbe guide, 
  // à partir d'un angle initial jusqu'à un angle final.
  //-------------------------
  virtual void RotateProfil(const double iStartAngleDegree, const double iEndAngleDegree) = 0;


protected :
  //Constructeur
  CATSmoExtrudeCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe);
  
  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;



private :

};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoExtrudeCreationOperator* CATSmoCreateExtrudeCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

