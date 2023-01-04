//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobFaceTagFaceHashTable.h
//
//=================================================================================
//
// Usage notes: Hash table FaceTag (key) / Face (value)
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobFaceTagFaceHashTable_H
#define CATSobFaceTagFaceHashTable_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Classe mère
#include "CATSobHashTableWithAssoc.h"

class CATSobFace;


class ExportedByCATSobUtilities CATSobFaceTagFaceHashTable: public CATSobHashTableWithAssoc
{
public:

  //Constructeur
  CATSobFaceTagFaceHashTable();

  //Destructeur
  virtual ~CATSobFaceTagFaceHashTable();

  /********************* SERVICES *********************/
  //Insertion d'un élément et de sa donnée associée
  void Insert(const unsigned int iFaceTag, const CATSobFace* iFace);
  
  //Récupération d'une donnée associée à un élément
  CATSobFace* GetFaceFromTag(const unsigned int iFaceTag) const;

  //Test d'appartenance
  CATBoolean Contains(const unsigned int iFaceTag) const;

  //Suppression d'un élément
  void Remove(const unsigned int iFaceTag);
  /****************************************************/

protected:

};


#endif

