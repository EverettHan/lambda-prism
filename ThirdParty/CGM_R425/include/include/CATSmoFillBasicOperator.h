//======================================================================
// Copyright Dassault Systemes Provence 2006-2007, all rights reserved 
//======================================================================
//
// CATSmoFillBasicOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
// November,  2017 : RBD : Ajout set multi-paramètres pour la symétrie, code d'après RAQ
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// 01-12-06 RBD Creation
//======================================================================
#ifndef CATSmoFillBasicOperator_H
#define CATSmoFillBasicOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
// #include "CATSobEdge.h" // MMO BAD004
#include "CATSobListOfEdge.h"

#include "CATLib.h" //Monocodage OS

//STL
#ifdef _AIX_SOURCE
#undef throw
#endif  //_AIX_SOURCE
#include <vector>

class CATSobMesh;
class CATSmoMeshTopoModifOperator;
class CATSmoFillEdgesParameter;


class ExportedByCATSmoOperators CATSmoFillBasicOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoFillBasicOperator();

  //Mono-parameter set : ipParam is addreferenced by the operator, it is also released with it.
  virtual void SetEdgesToFill(CATSmoFillEdgesParameter* ipParam) = 0;

  //Multi-parameters set : parameters are all addreferenced by the operator, they're also released with it.
  virtual void SetEdgesToFill(const std::vector<CATSmoFillEdgesParameter*>& iParams) = 0;

#if defined(_WINDOWS_SOURCE) || defined(_LINUX_SOURCE)
  //Multi-parameters set : parameters are not addreferenced by the operator, but the operator will release them.
  //This signature is useful if you just want to give the parameters to the operator and then you don't care about them anymore.
  virtual void SetEdgesToFill(std::vector<CATSmoFillEdgesParameter*>&& ioParams) = 0;
#endif  //_WINDOWS_SOURCE || _LINUX_SOURCE

  //DEPRECATED : Use CATSmoFillEdgesParameter instead
  //Set d'une liste d'aretes : 2, 3 ou 4 pas plus.
  virtual void SetEdgesToFill(CATLISTP(CATSobEdge)* iEdgesToFill) = 0;


protected:

  //Constructeur
  CATSmoFillBasicOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoFillBasicOperator* CATSmoCreateFillBasicOperator(CATSobMesh* iMesh, 
                                                       CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

