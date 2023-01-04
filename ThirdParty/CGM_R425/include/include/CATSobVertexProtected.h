//=============================================================================
// Copyright Dassault Systemes Provence 2016, All Rights Reserved
//=============================================================================
//
// CATSobVertexProtected.h
//
//=============================================================================
//
// Usage notes: ***************** DON'T INCLUDE THIS HEADER *****************
//              Classe n'exposant en Protected que les méthodes de CATSobVertex
//              dont les services ne sont pas ouverts aux utilisateurs mais
//              utilisables par les frameworks de subdivision
//
//=============================================================================
// 26.10.2016 : RAQ : Creation
//=============================================================================
#ifndef CATSobVertexProtected_H
#define CATSobVertexProtected_H

//Classe mère
#include "CATSobVertex.h"

//Divers
#include "CATSobDiag.h"

class CATSobMesh;

class CATSobVertexProtected : public CATSobVertex
{
public:

  //Destructeur
  virtual ~CATSobVertexProtected() {}

  //Test manifold : le onering des faces est soit homéomorphe à une disque fermé ou à un disque ouvert
  virtual CATSobDiag IsManifold(CATBoolean& oIsManifold) const = 0;

  //Test manifold "extended" : le vertex n'est pas considéré manifold s'il contient un secteur fermé et au moins un secteur ouvert
  //Autrement dit, on accepte les vertex avec plusieurs secteurs ouverts mais aucun fermé
  virtual CATSobDiag IsManifoldExtended(CATBoolean& oIsManifold) const = 0;

  //Test si le vertex contient un secteur fermé de faces
  virtual CATBoolean HasClosedSector() const = 0;


protected:

  //Constructeur
  CATSobVertexProtected(CATSobMesh* ipMesh):
    CATSobVertex(ipMesh) {}

private:

  //Copy constructor and equal operator
  CATSobVertexProtected(CATSobVertexProtected&);
  CATSobVertexProtected& operator=(CATSobVertexProtected&);

};



#endif  //CATSobVertexProtected_H

