//======================================================================
// Copyright Dassault Systemes Provence 2017, All Rights Reserved
//======================================================================
//
// CATSmoGlobalCutParameter.h
//
//======================================================================
//
// Usage notes : Paramètres pour l'opérateur CATSmoGlobalCutOperator
//
//======================================================================
// 23.04.2021 : RBD : Ajout GetImgPoint() pour manipulateurs SPARK
// 06.01.2017 : RAQ : Creation
//======================================================================
#ifndef CATSmoGlobalCutParameter_H
#define CATSmoGlobalCutParameter_H

//Pour l'export
#include "CATSmoOperators.h"

//Monocodage OS
#include "CATLib.h"

//Subdivision
#include "CATSobDiag.h"

//Divers
#include "CATSobAddRefRelease.h"
#include "CATMathPoint.h"
#include "CATMathDirection.h"
#include "CATBoolean.h"


class CATSobVertex;
class CATSobEdge;
class CATSobFace;



class ExportedByCATSmoOperators CATSmoGlobalCutParameter
{
  SOB_DECLARE_ADDREF_RELEASE;

public:

  /**
   * Builds a global cut parameter.
   *
   * @param ipSobEdge
   * A pointer to a CATSobEdge to cut
   * @param iNbCuts
   * The number of cuts along the edge, should be >0
   * @param ipRatios
   * Optionnal. If the cuts are not uniformly spaced ipRatios contains the cuts separation positions inside the edge with respect to the edge orientation.
   * For exemple if an edge has length 1 and contains 2 cuts at position 0.2 and 0.8, the array will contain { 0.2 (0.2 - 0.0), 0.6 (0.8 - 0.2) }
   * The array should of size iNbCuts
   * @param iTransferAllocationOfpRatios
   * if TRUE the pointer ipRatios is directly used in 'this' object and it will be deleted with it, else a new array is created inside 'this' object.
   * @param ipVertexParallel
   * If ipVertexParallel is not NULL, and is equal to the StarVertex or EndVertex of ipSobEdge, the algorithm perform iNbCuts parallel cuts of ipSobEdge.
   * If L is the length of ipSobEdge, the first cut is at L/(iNbCuts+1) from ipVertexParallel, next cut is at 2L/(iNbCuts+1), ... the last cut is at iNbCutsL/(iNbCuts+1)
   * from ipVertexParallel.
   If ipRatios is not NULL, it contains the iNbCuts length values 
  **/
  CATSmoGlobalCutParameter(CATSobEdge* ipSobEdge, const unsigned int iNbCuts = 1, double* ipRatios = 0, const CATBoolean iTransferAllocationOfpRatios = TRUE, CATSobVertex* ipVertexParallel = 0);


  //-----------------------------------------------------------------------------
  //------ Get :  d'un point sur le résultat (image) et de la direction du global cut (pour positionner un manipulateur SPARK)
  // Cette methode peut etre apellee AVANT le Run() de l'opérateur de global cut pour prépositioner un manipulateur
  // iEdge : Input edge before extrusion
  // iLambda : Must be between 0. and 1. (0. = start vertex, 1.0 = end vertex of iEdge)
  // oImgPoint : The point at iLambda on the edge iEdge
  // oCuttingDir : The cutting direction (normalized) of the edge iEdge from oEdgePoint
  //-----------------------------------------------------------------------------
  CATSobDiag GetImgPoint(const CATSobFace* iFaceOn, const CATSobEdge* iEdge, const double iLambda, CATMathPoint &oImgPoint, CATMathDirection &oCuttingDir);


  //----- Data :
  CATSobEdge* m_pSobEdge;
  CATSobVertex* m_pVertexParallel;
  unsigned int m_nbCuts;
  double* m_pRatios;

private:

  //Destructor
  ~CATSmoGlobalCutParameter();

  //No copy constructors
  CATSmoGlobalCutParameter(const CATSmoGlobalCutParameter&);
  CATSmoGlobalCutParameter& operator=(const CATSmoGlobalCutParameter&);

};

#endif  //CATSmoGlobalCutParameter_H


