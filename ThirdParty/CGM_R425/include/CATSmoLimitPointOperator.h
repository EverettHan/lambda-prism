//=====================================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//=====================================================================================
//
// CATSmoLimitPointOperator.cpp
//
//=====================================================================================
//
// Usage notes: Implementation of CATSmoLimitPointOperator
//
//=====================================================================================
// 21/11/07 MMO Correction des erreurs BAD004 (headerruler)
// September, 2004 : RAQ : Création
//=====================================================================================
#ifndef CATSmoLimitPointOperator_H
#define CATSmoLimitPointOperator_H

// #include "CATSobDefine.h" // MMO BAD004
#include "CATSmoOperators.h"
#include "CATSobDiag.h"

#include "CATBoolean.h"

class CATSobFace;


class ExportedByCATSmoOperators CATSmoLimitPointOperator
{
public:

/**
 * Build a CATSmoLimitPointOperator object,
 * The array of double (filled by the operator) is allocated by the user
 * and will have to be deleted by the user.
 *
 * @param iFace
 * The face to get the limit points from.
 *
 * @param ioTabOfPoints
 * The array of double (created by the user) that will contain all
 * the limit points coordinates after running the operator.
 * The size of this array is given by the following rule:
 * If face is quad: Size := 3*(2^Level+1) * (2^Level+1)
 * If face is tri : Size := 3*(2^(Level-1)+1) * (2^(Level-1)+1)
 *
 * The points are arranged the following way (see CATSmoFaceData.h for further details):
 *
 *          4             The edges are indexes in the face by 1, 2, 3, 4.
 *     <-----------       The points are given from left to right and from up to down
 *   |  ......... /|\
 *   |  .........  |
 * 1 |  .........  | 3
 *   |  .........  |
 *  \|/ .........  |
 *     ----------->
 *          2
 *
 * @param iSizeOfTab
 * The size of the array given the user: ioTabOfPoints.
 * This param only verifies that the array has the good size.
 *
 * @param iLevel
 * The level for which the points have to be computed, iLevel must be > 0
 *
 * @param iIndexOfDaughterFace
 * If the face is triangular, the index of the quad face contained in this
 * triangular face must be given with: 1 <= iIndexOfDaughterFace <= 3 (see picture in CATSobFace.h)
 * If the face is quad, iIndexOfDaughterFace must be 0 (default value)
 **/
  CATSmoLimitPointOperator(CATSobFace* iFace,
                           double*     ioTabOfPoints,
                           const int   iSizeOfTab,
                           const int   iLevel,
                           const int   iIndexOfDaughterFace = 0);

/**
 * @nodoc
 **/
  ~CATSmoLimitPointOperator();

/**
 * Run operator.
 *
 * @return
 * CATSobDiag_OK if no error, else see CATSobDiag.h
 **/
  CATSobDiag Run();

private:

  CATSobDiag InitRun();
  CATSobDiag SetDiag(CATSobDiag iDiag);

  //Calcul des points limite pour les faces quadrangulaires
  CATSobDiag ComputeInnerPointsForQuadFace();
  CATSobDiag ComputeBorderPointsForQuadFace();

  //Calcul des points limite pour les faces triangulaires
  CATSobDiag ComputeInnerPointsForTriangularFace();
  CATSobDiag ComputeBorderPointsForTriangularFace();

  CATSobFace* _Face;
  double* _TabOfPoints;
  int _Level;
  short _IndexOfDaughterFace;
  int _Size;
  CATSobDiag _Diag;
  CATBoolean _IsQuadFace;

};


#endif

