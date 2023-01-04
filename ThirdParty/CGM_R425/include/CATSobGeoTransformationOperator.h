//========================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved
//========================================================================
//
// CATSobGeoTransformationOperator.h
//
//========================================================================
//
// Usage notes: Geometric transformation of a subdivision base mesh.
//
//========================================================================
// September,  2009 : RAQ : Creation
//========================================================================
#ifndef CATSobGeoTransformationOperator_H
#define CATSobGeoTransformationOperator_H

//Pour l'export
#include "CATSobOperators.h"

//Divers
#include "CATSobDiag.h"


class CATSobMesh;



class ExportedByCATSobOperators CATSobGeoTransformationOperator
{
public:

  //Constructeur
  //La matrice de la transfo doit être donnée de la façon suivante :
  //
  //  iTransfoMatrix[0]   iTransfoMatrix[1]    iTransfoMatrix[2]
  //  iTransfoMatrix[3]   iTransfoMatrix[4]    iTransfoMatrix[5]
  //  iTransfoMatrix[6]   iTransfoMatrix[7]    iTransfoMatrix[8]
  //
  CATSobGeoTransformationOperator(CATSobMesh* iMesh, const double* iTransfoMatrix = 0, const double* iTranslationVector = 0);

  //Destructeur
  ~CATSobGeoTransformationOperator();

  //Option : mise à jour des l'info de modification des cellules
  void SetEnableModifFlagOnCells();

  //Run de l'opérateur
  CATSobDiag Run();

private:

  //Gestion du diag
  CATSobDiag SetDiag(const CATSobDiag iDiag);

  //Traitement des vertex
  CATSobDiag ProcessVertices();

  //Traitement des détails
  CATSobDiag ProcessDetails();

  //Application de la transfo
  void ApplyTransfoMatrix(const double* iInputVector, double* ioResultVector) const;

  //Réinitialisation des données de subdivision (buffer, orientations)
  CATSobDiag ResetSubdivisionData();

  //Evaluation du déterminant de la transfo
  double EvalDeterminant() const;


  //---------- Data:
  CATSobDiag _Diag;
  CATSobMesh* _Mesh;
  CATBoolean _EnableModifFlagOnCells;
  double _TransfoMatrix[9], _TranslationVector[3];
};


//----------------------------
// Application de la transfo
//----------------------------
inline void CATSobGeoTransformationOperator::ApplyTransfoMatrix(const double* iInputVector, double* ioResultVector) const
{
  if(iInputVector && ioResultVector)
  {
    ioResultVector[0]=iInputVector[0]*_TransfoMatrix[0]+iInputVector[1]*_TransfoMatrix[1]+iInputVector[2]*_TransfoMatrix[2];
    ioResultVector[1]=iInputVector[0]*_TransfoMatrix[3]+iInputVector[1]*_TransfoMatrix[4]+iInputVector[2]*_TransfoMatrix[5];
    ioResultVector[2]=iInputVector[0]*_TransfoMatrix[6]+iInputVector[1]*_TransfoMatrix[7]+iInputVector[2]*_TransfoMatrix[8];
  }
}

#endif


