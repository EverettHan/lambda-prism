
//===============================================================================
// Copyright Dassault Systemes Provence 2009, All Rights Reserved 
//===============================================================================
//
//
// CATSmoMultiEvaluator.h
//
//===================================================================================
//
// Usage notes:
//
//===================================================================================
// March,    2009 : RBD : Creation de l'interface a partir de CATSmoMultiEvaluator de RNO
// 23/07/07 RNO : Creation de CATSmoMultiEvaluator
//===============================================================================
#ifndef CATSmoMultiEvaluator_H
#define CATSmoMultiEvaluator_H

//Pour l'export
#include "CATSmoOperators.h"

#include "CATSmoEvalCommand.h"
#include "CATSmoEvalResult.h"
#include "CATSmoEvalLocation.h"

#include "CATSobDiag.h"

///---------------------------------------------
// WARNING ------ ATTENTION
//
// Restrictions :
// L'Evaluation des points (Command.OrderEvalSPoint) n'est pas faite sur la surface limite pour le moment utilisez SmoLimitPoint
// Il n'est pas possible d'evaluer aux vertex extraordinaire
// L'evaluation est faite sur la surface limite pour les cas reguliers ie
// Points de Valence 4 sans bord libre, sans sharp
// Points de valence 3 sur le bord
// Points de valence 2 dans les coins
//----------------------------------------------
class ExportedByCATSmoOperators CATSmoMultiEvaluator
{
public:

  // A SUPPRIMER
//  CATSmoMultiEvaluator( const CATSmoEvalCommand &iCommand);

  //Destructeur
  virtual ~CATSmoMultiEvaluator();

  //Obtention du diag
  virtual CATSobDiag GetDiag() const = 0;

  // Eval
  //  Input : - iListOfEdges : A pointer of a list of pointers of edges.
  //  Output: - oNbEdges     : the number of DIFFERENT edges in the input list
  //  Return : void 
  // 
  virtual CATSobDiag Eval(const CATSmoEvalLocation & iLocation, CATSmoEvalResult & oEval) = 0; //This can be used several time

  // Set Command
  //  Input : - iListOfEdges : A pointer of a list of pointers of edges.
  //  Output: - oNbEdges     : the number of DIFFERENT edges in the input list
  //  Return : void 
  // 
  virtual void SetCommand(const CATSmoEvalCommand &iCommand) = 0;

protected:

  //Constructeur (NE PAS UTILISER). Utilisez la methode de creation ci dessous.
  CATSmoMultiEvaluator();

};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoMultiEvaluator* CATSmoCreateMultiEvaluator(const CATSmoEvalCommand &iCommand);

#endif



