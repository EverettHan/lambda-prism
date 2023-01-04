//======================================================================
// Copyright Dassault Systemes Provence 2003-2007, all rights reserved 
//======================================================================
//
// CATSmoSubdivFacesOperator.h
//
//======================================================================
//
// Usage notes:
//
//======================================================================
//  January,    2021 : RBD : Implementation GetCentralFaceTag()
//  November,   2007 : MMO : Correction des erreurs BAD004 (headerruler)
//  August,     2006 : RBD : Creation d'apres CATSmoSubdivFacesOperatorCx2
//  January,    2004 : RAQ : Changement d'architecture des subdivisions
//  September,  2003 : JCV : Creation
//======================================================================
#ifndef CATSmoSubdivFacesOperator_H
#define CATSmoSubdivFacesOperator_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"

//Monocodage OS
#include "CATLib.h"

//STL
#ifdef _AIX_SOURCE
#undef throw
#endif  //_AIX_SOURCE
#include <vector>

class CATSobMesh;
class CATSmoMeshTopoModifOperator;
class CATSmoSubdivFacesParameter;

class ExportedByCATSmoOperators CATSmoSubdivFacesOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Destructeur
  virtual ~CATSmoSubdivFacesOperator();

  //Set mono-paramètre : un AddRef est fait par l'opérateur sur ipParam
  virtual void SetFacesToSubdivide(CATSmoSubdivFacesParameter* ipParam) = 0;

  //Set multi-paramètres : un AddRef est fait par l'opérateur sur chacun des paramètres
  virtual void SetFacesToSubdivide(const std::vector<CATSmoSubdivFacesParameter*>& iParams) = 0;

#if defined(_WINDOWS_SOURCE) || defined(_LINUX_SOURCE)
  //Multi-parameters set : parameters are not addreferenced by the operator, but the operator will release them.
  //This signature is useful if you just want to give the parameters to the operator and then you don't care about them anymore.
  virtual void SetFacesToSubdivide(std::vector<CATSmoSubdivFacesParameter*>&& ioParams) = 0;
#endif  //_WINDOWS_SOURCE || _LINUX_SOURCE

  //DEPRECATED : use parameter services instead
  //Subdivision d'une liste de faces
  virtual void SetFacesToSubdivide(CATLISTP(CATSobFace)* iFacesToSubdiv, const double iRatio = 0.5) = 0;

  // After Run(), return the tag > 0 of central face of the subdivision of input face given by iInputFaceTag > 0
  // return a diag if there is no central face :
  //     return CATSobDiag_InputNullFace if the input tag face iInputFaceTag is zero ;
  //     return CATSobDiag_FaceNull if there is no central face associated to iInputFaceTag;
  //     return CATSobDiag_OK if there is a valid result
  virtual CATSobDiag GetCentralFaceTag(const unsigned int iInputFaceTag, unsigned int &oCentralFaceTag) = 0;

protected:

  //Constructeur
  CATSmoSubdivFacesOperator(CATSobMesh* iMesh, CATSmoMeshTopoModifOperator* iTopoModifOpe);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoSubdivFacesOperator* CATSmoCreateSubdivFacesOperator(CATSobMesh* iMesh, 
                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif

