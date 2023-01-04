#ifndef CATSmoElementaryGrid_H
#define CATSmoElementaryGrid_H
//===============================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//===============================================================================
//
// CATSmoElementaryGrid.h
//
//===============================================================================
//
// Represente une grille de SobFace avec quelques utilitaires embarques
//
//===============================================================================
// 15-12-08 : RNO : Création
//===============================================================================

//Pour l'export
#include "CATSmoOperators.h"
#include "CATSobFace.h"

#include "CATSobListOfEdge.h"
#include "CATSobListOfFace.h"
class CATSmoElementaryGridChained;
typedef enum
{
  SmoSouthGridBorder =1,
  SmoEastGridBorder  =2,
  SmoNorthGridBorder =3,
  SmoWestGridBorder  =4
} CATSmoGridBorderType; //En fait comme si c'etait une face quad (edgenum)

class ExportedByCATSmoOperators CATSmoElementaryGrid
{
public:
  CATSmoElementaryGrid();
  CATSmoElementaryGrid(int Nu,int Nv, CATSobFace ** Grid);
  
  virtual ~CATSmoElementaryGrid();

  void SetGrid(int iNU, int iNV, CATSobFace ** Grid);
  CATSobFace ** GetGrid() const;
  void GetSize(int & oNU, int &oNV) const;
  int GetNumberOfFaces() const;//NU*NV
  
  int IsClosedU();
  int IsClosedV();

  void ComputeBorderEdges(CATSmoGridBorderType iBorderType,CATLISTP(CATSobEdge)& oListOfEdges, CATLISTP(CATSobFace) & SobFaces);
 
private:
  int _NU,
      _NV;
  CATSobFace ** _Grid;
  int _ClosedU,
      _ClosedV;
  //pu [0,nU-1] PV [0,nV-1]
  inline int GetArrayIndex(int PU,int PV) const {  return((PU)+ (PV)*_NU);};
  void ComputeClosure();
  void ComputeOrientations();
  int ComputeOrientationForFirstFace(int iNU,int iNV,CATSobFace * const *  oTabOfSobFace, CATBoolean & oIsDirect);
  int ComputeNbRotationBetweenTwoFaces(CATSobFace * iRef,CATSobFace *  iOtherFace);
  int GetSharedEdgeIndexInFirstFace(CATSobFace * FirstFace, CATSobFace * SecondFace);
  short * _CellOrientations;
};

class CATSmoElementaryGridChained:public CATSmoElementaryGrid
{
public:
  CATSmoElementaryGridChained();
  CATSmoElementaryGridChained(int Nu,int Nv, CATSobFace ** Grid);
  virtual ~CATSmoElementaryGridChained();

  CATSmoElementaryGridChained * GetNextGrid();
  void SetNextGrid(CATSmoElementaryGridChained * iNext);
  private:
  CATSmoElementaryGridChained * _NextGrid;
};

#endif
