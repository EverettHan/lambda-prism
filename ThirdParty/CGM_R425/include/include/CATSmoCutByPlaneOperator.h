//===========================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//===========================================================================
//
// CATSmoCutByPlaneOperator.h
//
//===========================================================================
//
// Usage notes: Opérateur de découpe d'un maillage par un plan.
//              /!\ Cet opérateur peut générer des ngones.
//
//===========================================================================
// December,  2009 : RAQ : Creation
//===========================================================================
#ifndef CATSmoCutByPlaneOperator_H
#define CATSmoCutByPlaneOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Divers
#include "CATSobDiag.h"

class CATSobMesh;
class CATMathPlane;
class CATSmoMeshTopoModifOperator;
class CATGeometry;

class ExportedByCATSmoOperators CATSmoCutByPlaneOperator
{
public:

  //Options de découpe
  enum CATSmoCutByPlaneOptions
  {
    CATSmoCutByPlane_InsertCut,         //Insertion de la découpe
    CATSmoCutByPlane_KeepDirectSide,    //Conservation des faces se trouvant 'au dessus' du plan (suivant la normale au plan)
    CATSmoCutByPlane_KeepInvertSide     //Conservation des faces se trouvant 'au dessous' du plan (suivant la normale au plan)
  };

  //Destructeur
  virtual ~CATSmoCutByPlaneOperator();

  //Set du plan V5 pour le journal topologique
  virtual void SetPlaneFace(CATGeometry* iPlaneFace) = 0;

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Diag de l'opérateur
  virtual CATSobDiag GetDiag() const = 0;


protected:

  //Constructeur
  CATSmoCutByPlaneOperator();


};


//Construction de l'opérateur
ExportedByCATSmoOperators
CATSmoCutByPlaneOperator* CATSmoCreateCutByPlaneOperator(CATSobMesh* iMesh, const CATMathPlane& iMathPlane,
                                                         CATSmoCutByPlaneOperator::CATSmoCutByPlaneOptions iCutOption = CATSmoCutByPlaneOperator::CATSmoCutByPlane_InsertCut,
                                                         CATSmoMeshTopoModifOperator* iTopoModifOperator = 0);


#endif

