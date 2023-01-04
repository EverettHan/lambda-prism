//=================================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//=================================================================================
//
// CATSobVertexTagVertexHashTable.h
//
//=================================================================================
//
// Usage notes: Hash table VertexTag (key) / Vertex (value)
//
//=================================================================================
// December,  2009 : RAQ : Creation
//=================================================================================
#ifndef CATSobVertexTagVertexHashTable_H
#define CATSobVertexTagVertexHashTable_H

//Pour l'export
#include "ExportedByCATSobUtilities.h"

//Classe mère
#include "CATSobHashTableWithAssoc.h"

class CATSobVertex;


class ExportedByCATSobUtilities CATSobVertexTagVertexHashTable: public CATSobHashTableWithAssoc
{
public:

  //Constructeur
  CATSobVertexTagVertexHashTable();

  //Destructeur
  virtual ~CATSobVertexTagVertexHashTable();

  /********************* SERVICES *********************/
  //Insertion d'un élément et de sa donnée associée
  void Insert(const unsigned int iVertexTag, const CATSobVertex* iVertex);
  
  //Récupération d'une donnée associée à un élément
  CATSobVertex* GetVertexFromTag(const unsigned int iVertexTag) const;

  //Test d'appartenance
  CATBoolean Contains(const unsigned int iVertexTag) const;

  //Suppression d'un élément
  void Remove(const unsigned int iVertexTag);
  /****************************************************/

protected:

};


#endif

