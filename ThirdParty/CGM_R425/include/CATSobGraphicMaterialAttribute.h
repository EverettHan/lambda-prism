//=========================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved
//=========================================================================
//
// CATSobGraphicMaterialAttribute.h
//
//=========================================================================
//
// Usage notes: Attribute to handle graphic material of mesh faces.
//
//=========================================================================
// May,   2010 : RAQ : Création
//=========================================================================
#ifndef CATSobGraphicMaterialAttribute_H
#define CATSobGraphicMaterialAttribute_H

//Pour l'export
#include "CATSobObjects.h"

//Classe mère
#include "CATSobAttributes.h"

//Divers
#include "CATSobGraphicMaterial.h"


CATDECLARESOBATTRIBUTE(CATSobGraphicMaterialAttribute, CATSobGraphicMaterialAttributeID)

class CATSobGraphicMaterialAttribute: public CATSobAttributes
{
public:

  //Constructeur
  CATSobGraphicMaterialAttribute(const CATSobGraphicMaterial& iGraphicMaterial);

  //Récupération du matériau
  inline const CATSobGraphicMaterial& GetMaterial() const { return _GraphicMaterial; }


protected:

  //Destructeur
  virtual ~CATSobGraphicMaterialAttribute();

private:


  //-------- Data:
  CATSobGraphicMaterial _GraphicMaterial;

};


#endif

