//=================================================================================
// Copyright Dassault Systemes Provence 2006, All Rights Reserved 
//=================================================================================
//
// CATSmoMeshFromSDOOperator.h
//
//=================================================================================
//
// Usage notes:
//
//=================================================================================
// January,  2006 : RAQ : Creation
//=================================================================================
#ifndef CATSmoMeshFromSDOOperator_H
#define CATSmoMeshFromSDOOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Classe mère
#include "CATSmoSubdivisionMeshOperator.h"


class CATSobMesh;
class CATSmoMeshTopoModifOperator;

class ExportedByCATSmoOperators CATSmoMeshFromSDOOperator: public CATSmoSubdivisionMeshOperator
{
public:

  //Constructeur
  CATSmoMeshFromSDOOperator(const char* iFileName,
                            CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);

  //Destructeur
  virtual ~CATSmoMeshFromSDOOperator();

  //Obtention du mesh
  CATSobMesh* GetMesh();

protected:

  //Run de l'opérateur
  virtual CATSobDiag RunOperator();

private:

  //Lecture du fichier SDO
  CATSobDiag BuildMeshFromSDOFile(CATSobMesh*& iMesh);
  CATSobDiag CreateFaces(CATSobMesh* iMesh, int* iTabOfEdges, const int iNbFaces, const int iMaxNbEdgesPerFace, int* ioNewOrder = 0);

  //Fonction distance
  double GetDistance(const double* iPt1, const double* iPt2);

  //----- Data:
  char* _FileName;
};

ExportedByCATSmoOperators
CATSmoMeshFromSDOOperator* CATSmoCreateMeshFromSDOOperator(const char* iFileName,
                                                           CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);


#endif


