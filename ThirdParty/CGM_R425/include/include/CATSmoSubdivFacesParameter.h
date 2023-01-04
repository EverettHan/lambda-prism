//======================================================================
// Copyright Dassault Systemes Provence 2017, All Rights Reserved
//======================================================================
//
// CATSmoSubdivFacesParameter.h
//
//======================================================================
//
// Usage notes : Paramètres pour l'opérateur CATSmoSubdivFacesOperator
//
//======================================================================
// 23.12.2020 : RBD : Ajout GetImgPoint() pour manipulateurs SPARK
// 23.01.2017 : RAQ : Creation
//======================================================================
#ifndef CATSmoSubdivFacesParameter_H
#define CATSmoSubdivFacesParameter_H

//Pour l'export
#include "CATSmoOperators.h"

//Monocodage OS
#include "CATLib.h"

//Subdivision
#include "CATSobAddRefRelease.h"
#include "CATSobListOfFace.h"
#include "CATSobDiag.h"

#include "CATMathPoint.h"

// STL
#include <vector>

class CATSobFace;
class CATSobEdge;

class ExportedByCATSmoOperators CATSmoSubdivFacesParameter
{
  SOB_DECLARE_ADDREF_RELEASE;

public:

  //Constructors
  CATSmoSubdivFacesParameter(const double iRatio = 0.5);
  CATSmoSubdivFacesParameter(const CATLISTP(CATSobFace)& iFacesToSubdiv, const double iRatio = 0.5);

  //------ Get :  d'un point sur le résultat (image) de la subdivision (pour positionner un manipulateur SPARK)
  // iFace : Input face before subdivision
  // iEdge : Input edge of iFace (any edge)
  // iLambda : Must be between 0. and 1. (0. = start vertex, 1.0 = end vertex of iEdge)
  // oEdgePoint : The point at iLambda on the edge iEdge
  // oImgPoint : A point on the TOP subdivided face from iFace
  //-----------------------------------------------------------------------------
  CATSobDiag GetImgPoint(const CATSobFace* iFace, const CATSobEdge* iEdge, const double iLambda, CATMathPoint &oEdgePoint, CATMathPoint &oImgPoint);


  //---- Data :
  CATLISTP(CATSobFace) m_facesToSubdivide;
  double m_ratio;

private:

  //Destructor
  ~CATSmoSubdivFacesParameter() {}

  //---- Data :
  std::vector<unsigned int> m_inputFacesTags, m_outCentralFacesTags;


};

#endif  //CATSmoSubdivFacesParameter_H


