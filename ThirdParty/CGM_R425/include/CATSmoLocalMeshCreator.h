//=======================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//=======================================================================
//
// CATSmoLocalMeshCreator.h
//
//=======================================================================
//
// Usage notes: Base mesh local pour le cutting pour le PCCM
//
//=======================================================================
// March,     2005 : RAQ : Creation
//=======================================================================
#ifndef CATSmoLocalMeshCreator_H
#define CATSmoLocalMeshCreator_H

#include "CATSmoOperators.h"

#include "CATSobListOfFace.h"

#include "CATSobDiag.h"

class CATSobFace;
class CATSobMesh;


class ExportedByCATSmoOperators CATSmoLocalMeshCreator
{
public:

  //Constructeur
  CATSmoLocalMeshCreator(CATSobFace* iFace, const int iLevel);

  //Destructeur
  ~CATSmoLocalMeshCreator();

  //Run de l'opérateur
  CATSobDiag Run();

  //Obtention du mesh
  CATSobMesh* GetMesh();

  //Obtention du nombre de découpes et des ratios
  void GetNbCuts(int& oNbCuts, double*& oRatio);

  //Diag de l'opérateur
  CATSobDiag GetDiag();


private:

  CATSobDiag SetDiag(const CATSobDiag iDiag);
  
  //Calcul des ratios en fonction des faces voisines
  CATSobDiag ComputeFineCutsAndOneRing(int&                  oNbCutsOnU,
                                       double*&              oRatioOnU,
                                       int&                  oNbCutsOnV,
                                       double*&              oRatioOnV,
                                       CATLISTP(CATSobFace)* oOneRing);

  //Join des base mesh relatifs à chacunes des faces voisines
  CATSobDiag RunJoinMeshes(CATSobMesh* ioMeshDest, CATSobMesh* iMeshSrc);


  //-------- Data
  CATSobFace* _Face;
  CATSobMesh* _Mesh;
  int _NbCutsOnU, _NbCutsOnV;
  double *_RatioOnU, *_RatioOnV;
  CATSobDiag _Diag;
  const int _Level;
};


//---------------------
// Obtention du mesh
//---------------------
inline CATSobMesh* CATSmoLocalMeshCreator::GetMesh()
{
  return _Mesh;
}


#endif


