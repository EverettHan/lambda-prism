//======================================================================
// Copyright Dassault Systemes Provence 2006, all rights reserved 
//======================================================================
//
// CATSmoPrimitiveCreationOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
//  March,         2017 : RBD : Ten years after : SetPosition method with a CATMathAxis
//  September,     2006 : RBD : Creation
//======================================================================
#ifndef CATSmoPrimitiveCreationOperator_H
#define CATSmoPrimitiveCreationOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSmoPrimitiveType.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;

class CATMathPoint;
class CATMathVector;
class CATMathAxis;


class ExportedByCATSmoOperators CATSmoPrimitiveCreationOperator: public CATSmoSubdivisionMeshOperator
{
public:
  
  //Destructeur
  virtual ~CATSmoPrimitiveCreationOperator();

  // Type de primitive a creer :
  // CATSmoPrimitive_SPHERE  (Default)
  // CATSmoPrimitive_CYLINDER   
  // CATSmoPrimitive_BOX          
  // CATSmoPrimitive_TORUS      
  // CATSmoPrimitive_PYRAMID  
  // CATSmoPrimitive_SQUARE_FACE 
  // CATSmoPrimitive_CIRCLE_FACE  
  // CATSmoPrimitive_TRIANGULAR_FACE 
  // CATSmoPrimitive_RING_FACE  
  virtual void SetPrimitiveType(const CATSmoPrimitiveType iPrimitive) = 0;


  // Nombre de sections de la primitive
  // Must be >= 4 (defaut)
  // Must be even
  virtual void SetNbSections(const int iNbSections) = 0;

  // Position de la primitive a creer
  // Info Vect
  //  0 -> prendre le triedre courant
  //  1 -> Z impose
  // -1 -> Z Donne, recalculer a partir du triedre courant CATPlane
  virtual void SetPosition(const CATMathPoint&  iPosition, 
                           const int            iInfoVect,
                           const CATMathVector& iVector,
                           const double         iRadius) = 0;


  // Position de la primitive a creer
  virtual void SetPosition(const CATMathAxis&  iAxis,
                           const double        iRadius) = 0; 

protected :
  //Constructeur
  CATSmoPrimitiveCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe);
  
  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

private :

};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoPrimitiveCreationOperator* CATSmoCreatePrimitiveCreationOperator(CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

