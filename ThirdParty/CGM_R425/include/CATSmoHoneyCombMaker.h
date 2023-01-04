

//===============================================================================
// Copyright Dassault Systemes Provence 2010, All Rights Reserved 
//===============================================================================
//
// CATSmoExtractGridOperator.h
//
//===============================================================================
//
// Usage notes: 
// Creation d'un base mesh en grille d'hexagones regulier
//
//===============================================================================
// Auguste,   2010 : RBD : Modifs pour creation operateur topo
// May,       2010 : RNO : Création jour de Solidarite
//===============================================================================
#ifndef CATSmoHoneyCombMaker_H
#define CATSmoHoneyCombMaker_H

//Pour l'héritage
#include "CATSmoSubdivisionMeshOperator.h"

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobListOfEdge.h"

class CATSobMesh;
class CATSmoMeshTopoModifOperator;

//====================================================================
// Evaluateur associé
//====================================================================
class ExportedByCATSmoOperators CATSmoHoneyCombMakerEvaluator
{
public:
  CATSmoHoneyCombMakerEvaluator(){};
  virtual  ~CATSmoHoneyCombMakerEvaluator(){};
  // Return the coordinate of au,v point : oPt
  // Layer could be used to distinguish the Bottom Layer (0)  or TopLayer (1)
  // InOut Can be used to apply special eval for inner loop (0) of an Hexagon or external Loop (1)
  virtual int EvalPoint(double u,double v,int Layer, int InOut,double oPt[3]);
};

//====================================================================
// class CATSmoHoneyCombMaker
//====================================================================
class ExportedByCATSmoOperators CATSmoHoneyCombMaker: public CATSmoSubdivisionMeshOperator
{
public:
  virtual  ~CATSmoHoneyCombMaker();
  
  //The Number of cells in the 2 directions
  virtual void SetSize(int NbU,int NbV) = 0;
  //The Dimension of the external Haxagon and the internal one
  // Must choose such as i2DExternalRadius>i2DInternalRadius>0
  virtual void SetDimension(double i2DExternalRadius, double i2DInternalRadius) = 0;

  //Set an External Evaluator (Overload see the above class to make wavy and funny honey comb)
  virtual void SetExternalEvaluator(CATSmoHoneyCombMakerEvaluator * Evaluator) = 0;

  //Make a 2 layered HoneyComb : Your Evaluator should distinguish the Two Layers
  //The Mesh will be closed (no free edges)
  virtual void SetDoubleLayeredHoneyComb() = 0;

    //Get the "outer boundary" (in thick mode get the union of the two layers boudary edges)
  virtual void GetExternalEdges(CATLISTP(CATSobEdge) & oExternalEgdes) const = 0;

  //Get the inner loop of the hexa cell
  virtual void GetInternalEdges(CATLISTP(CATSobEdge) & oInternalEgdes) const = 0;
  
  //Get All Vertical edges (inner or outer)
  virtual void GetVerticalEdges(CATLISTP(CATSobEdge) & oVerticalEdges) const = 0;

  // Poids sur les edges des cellules
  // Le poids varie entre -100 et +100.
  // Si un poids est > 0, l'edge est marquée smooth.
  // Si un poids est < 0, l'edge est marquée sharp.
  virtual void SetWeightsOnEdges(const int iWeightOnExternalEdges,
                                 const int iWeightOnInternalEdges,
                                 const int iWeightOnVerticalEdges) = 0;

  // Activation du poid automatique sur les vertex.
  virtual void SetAutoWeight(const CATBoolean iAutoWeight = 1) = 0;

// RBD ----- A SUPPRIMMER 
//  virtual CATSobDiag Run() = 0; // Utiliser Run() de la classe mère;
//  virtual CATSobMesh * GetResult() = 0; // Utiliser GetResultMesh() de la classe mère;
// RBD ----- A SUPPRIMMER 

  
protected:
  //Constructeur
  CATSmoHoneyCombMaker(CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);

  //Run de l'opérateur
  virtual CATSobDiag RunOperator() = 0;
  
};

//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoHoneyCombMaker * CATSmoCreateHoneyCombMaker(CATSmoMeshTopoModifOperator* iTopoModifOpe = 0);
#endif
