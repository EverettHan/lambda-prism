//=================================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//=================================================================================
//
// CATSmoFitMeshesOperator.h
//
//=================================================================================
//
// Usage notes:
//
//=================================================================================
// May,  2008 : UIQ : Creation
//=================================================================================
#ifndef CATSmoFitMeshesOperator_H
#define CATSmoFitMeshesOperator_H

//Pour l'export
#include "CATSmoOperators.h"

#include "CATListOfInt.h"
#include "CATSobDiag.h"
#include "CATSobCell.h"

class CATSobMesh;
class CATSobEdge;
class CATSmoMeshTopoModifOperator;


class ExportedByCATSmoOperators CATSmoFitMeshesOperator
{
public:
 
  //Constructeur
  CATSmoFitMeshesOperator(CATSobMesh* iRefMesh, CATSobMesh* iMeshAfter, const int iLevel);

  //Destructeur
  virtual ~CATSmoFitMeshesOperator();

  //--------------------------------------------------
  //Set des listes :
  //    -Tag Ancienne Face
  //    -Tag New face
  //Il doit y avoir correspondance entre les 2 listes
  //--------------------------------------------------
  void SetListTagOldFace(CATListOfInt& iTagOldFace);
  void SetListTagNewFace(CATListOfInt& iTagNewFace);

  //--------------------------------------------------
  //Set servant a utiliser les details dans un
  //repère global ou local
  //--------------------------------------------------
  void SetLevelForMappingOnRefMesh(const int iLevelForMappingOnRefMesh);

  //Run de l'opérateur
  virtual CATSobDiag Run();


private :

  //-------------------------------------------------------------
  //Recherche de la position des point de subdivision de la face
  // + Ajt de detail pour plaquer le point sur l'ancienne face
  //-------------------------------------------------------------
  CATSobDiag MappingAjtDetail(CATSobFace* iOldFace, CATSobFace* iNewFace);


  //----------- Data:
  CATSobMesh *_RefMesh, *_MeshAfterModif;
  int _FittingLevel, _LevelForMappingOnRefMesh;
  CATBoolean _RecursiveFit;
  CATListOfInt _TagOldFace, _TagNewFace;

};



#endif


