//===============================================================================
// Copyright Dassault Systemes Provence 2005-2007, All Rights Reserved 
//===============================================================================
//
// CATSmoExtractGridOperator.h
//
//===============================================================================
//
// Usage notes: Extraction d'un ensemble de faces formant une grille
//
//===============================================================================
// 01-12-08 RNO Modification pour pouvoir deriver de cette classe et implementer ses propres IsVertexRegular
//              + Ajout de IsSplittingEdge
// 21-11-07 MMO Correction des erreurs BAD004 (headerruler)
// 01-02-05 RAQ Création
//===============================================================================
#ifndef CATSmoExtractGridOperator_H
#define CATSmoExtractGridOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Subdivision
#include "CATSobDiag.h"
#include "CATSobListOfFace.h"
#include "CATBoolean.h"

//Pour le debug
//#define DEBUG_EXTRACTGRIDOPERATOR

class CATSobFace;
class CATSobVertex;
class CATSobEdge;

class ExportedByCATSmoOperators CATSmoExtractGridOperator
{
public:

  //Constructeur
  CATSmoExtractGridOperator(CATSobFace* iFace);

  //Destructeur
  virtual ~CATSmoExtractGridOperator();

  //Diag de l'opérateur
  CATSobDiag GetDiag() const;

  //Run de l'opérateur
  CATSobDiag Run();

  //Récupération de la grille:
  //Les faces sont organisées de la manière suivante: la face (u, v) est donnée par oGridOfFaces[u+oUSize*v]
  //avec 0<u<oUSize et 0<v<oVSize
  CATSobDiag GetGrid(int& oUSize, int& oVSize, CATSobFace**& oGridOfFaces);

  //Debug...
  void GetSizeOfGrid(int& oMinU, int& oMaxU, int& oMinV, int& oMaxV) const;

protected :
  //Check d'un vertex
  virtual CATBoolean IsVertexRegular(CATSobVertex* iVertex);
  virtual CATBoolean IsSplittingEdge(CATSobEdge *  iEdge);//Default False

private:

  //Gestion des diag
  CATSobDiag SetDiag(const CATSobDiag iDiag);

  //Calcul des min/max en u et v (taille maximale de la grille)
  CATSobDiag ComputeGridDeepness(int& oMinU, int& oMaxU, int& oMinV, int& oMaxV);

  //Calcul de la taille exacte de la grille
  CATSobDiag ComputeGridSize(int& oMinU, int& oMaxU, int& oMinV, int& oMaxV);
  CATSobDiag ComputeGridSizeInUDirection(int& oMinU, int& oMaxU, int& oMinV, int& oMaxV);
  CATSobDiag ComputeGridSizeInVDirection(int& oMinU, int& oMaxU, int& oMinV, int& oMaxV);

  //Navigation dans le mesh à partir d'une face
  CATSobDiag BrowseMesh(CATSobFace* iStartFace,
                        const int   iStartEdgeIndex,
                        int&        oIndex,
                        CATBoolean& oHasLooped,
                        const int   iCheckCodeForVertices = 0);

  

  //Remplissage de la liste des faces formant la grille
  CATSobDiag FillListOfFaces();

#ifdef DEBUG_EXTRACTGRIDOPERATOR
  //Sauvegarde de la grille de faces dans un mesh
  void SaveGridAsMesh();
#endif


  //-------- Data
  CATSobDiag _Diag;
  CATSobFace* _InputFace;
  CATLISTP(CATSobFace) _GridOfFaces;
  int _MinU, _MaxU, _MinV, _MaxV;

};


#endif


