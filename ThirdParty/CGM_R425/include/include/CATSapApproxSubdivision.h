//====================================================================
// Copyright Dassault Systemes Provence 2008, all rights reserved 
//====================================================================
//
//======================================================================
// Jan,      30 th 2008 Creation                                    ANR
//======================================================================

#ifndef CATSapApproxSubdivision_H
#define CATSapApproxSubdivision_H
 
//Pour l'export
#include "CATSapApprox.h" 

#include "CATSobFace.h"   
#include "CATSapKnotVector.h" 
#include "CATMathGridOfPoints.h"

class ExportedByCATSapApprox CATSapApproxSubdivision 
{
public :
 
	virtual ~CATSapApproxSubdivision();    
 
  virtual CATSobDiag Run() = 0;

  // les gets
  // Si la face est quad : Appeler une seule fois le Get sans le iIndexOfDaughterFace ou avec iIndexOfDaughterFace=0
  // Si la face est triangulaire : Je fais le calcul des trois surfaces, alors Appeler trois fois le Get 
  // avec iIndexOfDaughterFace=1, 2, 3
  // DO NOT DELETE NOR MODIFY (MAY BE SHARED)
  virtual CATSapKnotVector *GetKnotVector(int iIndexOfDaughterFace=0) = 0;
  
  //DELETE IT IF YOU GET IT
  virtual CATMathGridOfPoints * GetCtlPoints(int iIndexOfDaughterFace=0) = 0 ;

  // si on a demande tout le BaseMesh
  virtual CATSapKnotVector *GetKnotVectorOfAFace(int iNumFace, int iIndexOfDaughterFace=0) = 0;

  virtual CATMathGridOfPoints * GetCtlPointsOfAFace(int iNumFace, int iIndexOfDaughterFace=0) = 0 ;

};

//Méthode de création de l'opérateur
ExportedByCATSapApprox
CATSapApproxSubdivision* CATSapCreateApproxSubdivision(CATSobFace *iFace, const int iLevel = 2);

ExportedByCATSapApprox
CATSapApproxSubdivision* CATSapCreateApproxSubdivision(CATLISTP(CATSobFace) * iListFaces, const int iLevel = 2);

ExportedByCATSapApprox
CATSapApproxSubdivision* CATSapCreateApproxSubdivision(CATSobMesh *iMesh, const int iLevel = 2);

#endif


