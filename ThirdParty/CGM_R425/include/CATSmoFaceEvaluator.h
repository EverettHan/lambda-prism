//===============================================================================
// Copyright Dassault Systemes Provence 2005, All Rights Reserved 
//===============================================================================
//
// CATSmoEdgeEvaluator.h
//
//===============================================================================
//
// Usage notes: Evaluation Longueur ou autre d'une arete donnee
// On peut creer une classe derivee de celle-ci pour imlementer d'autres Evaluateur
//
//===============================================================================
// August,  2005 : RNO : Création
//===============================================================================
#if 0
#ifndef CATSmoEdgeEvaluator_H
#define CATSmoEdgeEvaluator_H

#include "CATSmoOperators.h"

class CATSobFace;


class ExportedByCATSmoOperators CATSmoFaceEvaluator
{
public:

  //Constructeur
  CATSmoFaceEvaluator(){};

  //Destructeur
  virtual ~CATSmoFaceEvaluator(){};

  //Diag de l'opérateur
  virtual double Eval(CATSobFace * iFace);

private :
  // Copy constructor and equal operator
  CATSmoFaceEvaluator (CATSmoFaceEvaluator &);
  CATSmoFaceEvaluator& operator=(CATSmoFaceEvaluator&);

  inline double Square(double idouble);
};


#endif
#endif
