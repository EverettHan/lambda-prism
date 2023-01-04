//====================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//====================================================================
//
// CATSobUtilitaireCutting.h
//
//====================================================================
//
// Usage notes:
//
//====================================================================
// January,   2005 : RAQ/ANR : Création
//====================================================================
#ifndef CATSobUtilitaireCutting_H
#define CATSobUtilitaireCutting_H

#include "CATSobOperators.h"

#include "CATSobDiag.h"
#include "CATBoolean.h"
#include "CATDataType.h" 

class CATSobMesh;
class CATSobEdge;
class CATSobFace; 

//--------------------------------------------------------------------------
//Variable pour prendre ou non en compte le one ring de la face à découper
//#define ONE_RING
//--------------------------------------------------------------------------

 

int SearchArcFromParameter_Raq(int NbOfKnots,
                               double *_Knots,
                               CATLONG32 *_Multiplicities,
                               const double &iParameter) ;


int CalculRpourJ_Raq(const int &ndeg, const int &nbsvn,
                     const CATLONG32 *mult,const int &jpole) ;

double ExtendedKV_Raq(const int &ndeg, const int &nbsvn,
                      double *vn,  CATLONG32 *mult, const int &jpol ) ;

int computeKnotVector_Raq(int iLevel, int &odegree, int &oNbOfKnots, double *&oKnots, CATLONG32 *& oMultiplicities) ;


void NewIncreaseDegree_Raq(int Degree,
                           double *_Knots,
                           CATLONG32 *_Multiplicities,
                           int NbOfKnots,
                           int NbOfCPs,
                           int &iNumberOfForms,
                           double  * itabOfCPs,
                           const int Delta_deg,
                           int &oDegree,
                           int &onewNbOfCPs,
                           double *& oPoles_nw) ;


int NewMultipleKnotInsertion_Raq(int Degree,
                                 double *&_Knots,
                                 CATLONG32 *&_Multiplicities,
                                 int &NbOfKnots,
                                 int NbOfCPs,
                                 int iNumberOfForms,
                                 double  *&_tabOfCPs,
                                 int &onewNbOfCPs,
                                 double    * iKnotValues,
                                 CATLONG32 * iMultiplicities,
                                 CATLONG32   iNbInsertions,
                                 double      iTolKnotConfusion=0.) ;

int NewNaturalKnotRemoval_Raq(int Degree,
                              double *&_Knots,
                              CATLONG32 *&_Multiplicities,
                              int &NbOfKnots,
                              int NbOfCPs,
                              int iNumberOfForms,
                              double  *&_tabOfCPs,
                              int &onewNbOfCPs,
                              const double &iKnot_value,
                              const  CATLONG32 &iMultiplicity ) ;


// ==========================================================================================
//
//                     POUR RAQQQQQQQQQQQQQQQQ
//
// ==========================================================================================


void ComputeCuttingPts_Raq(const int iLevel,
                           int&      ioNbCutsOn,
                           double*&  ioRatioOn);


int NewLocalCuttingFace_Raq(const int     iLevel,
                            double*       iTabPts,
                            const int     iNbCutsOnU,
                            const double* iRatioOnU, 
                            const int     iNbCutsOnV,
                            const double* iRatioOnV,
                            int&          oNbreFaceU,
                            int&          oNbreFaceV,
                            double**&     oTabGrid );


// ajouter par anr ... 14/02/2005
int computeKnotVec_Raq(int iLevel, const int iNbCutsOn, const double *iRatioOn, 
                       int &odegree, int &oNbOfKnots, double *&oKnots, CATLONG32 *& oMultiplicities) ;


int ComputeTargetLevel(int     iNbCutsOn, 
                       double *ioRatioOn,  
                       int    &oTargetLevel) ;

int RecalageOnTargetLevel(int     iTargetLevel,
                          int     iNbCutsOn, 
                          double *ioRatioOn) ;

// ajouter par anr ... 14/02/2005
ExportedByCATSobOperators
int NewLocalCuttingFace_Raq(const int     iLevel,
                            CATSobFace   *iFace, 
                            const int     iNbCutsOnU,
                            const double* iRatioOnU, 
                            const int     iNbCutsOnV,
                            const double* iRatioOnV,
                            int&          oNbreFaceU,
                            int&          oNbreFaceV,
                            double**&     oTabGrid,
                            CATSobMesh *& oMalekMesh,
                            int &         oTargetLevel); 

ExportedByCATSobOperators
int SmoothCuttingFace_Raq(const int     iTargetLevel,
                          CATSobFace    *iFace, 
                          CATSobMesh *& oSmoothMesh) ;

// pour les faces triangulaires ...
ExportedByCATSobOperators
int NewLocalCuttingFace_Raq(const int     iLevel,
                            CATSobFace   *iFace,
                            CATSobEdge   *iEdge,
                            const int     iNbCutsOnU,
                            const double* iRatioOnU, 
                            const int     iNbCutsOnV,
                            const double* iRatioOnV,
                            int&          oNbreFaceU,
                            int&          oNbreFaceV,
                            double**&     oTabGrid,
                            CATSobMesh *& oMalekMesh,
                            int &         oTargetLevel);  


#endif



