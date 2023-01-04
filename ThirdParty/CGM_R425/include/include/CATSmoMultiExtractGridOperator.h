
#ifndef CATSmoMultiExtractGridOperator_H
#define CATSmoMultiExtractGridOperator_H
//===============================================================================
// Copyright Dassault Systemes Provence 2008, All Rights Reserved 
//===============================================================================
//
// CATSmoExtractGridOperator.h
//
//===============================================================================
//
// Usage notes: Extraction des zones formant des grilles dans un BaseMesh quelconque
// Attention : Le decoupage des grilles n'est pas optimal en nombre ni en forme
// Par contre il est stable par rapport a la geometrie (meme topologie => meme decoupage)
// L'operateur est en gros un encapsulage de l'operateur CATSmoExtractGridOperator
//
//===============================================================================
// 01-12-08 : RNO : Création
//===============================================================================

//Pour l'export
#include "CATSmoOperators.h"

//Subdivision
#include "CATSobDiag.h"

#include "CATBoolean.h"

#include "CATSobListOfFace.h"
#include "CATSobListOfEdge.h"
#include "CATSobListOfVertex.h"

#include "CATSobDefine.h"
#include "CATSobCell.h"

//Mesh Operators
#include "CATSmoExtractGridOperator.h"
#include "CATSmoElementaryGrid.h"
#include "CATSmoMEGOEdgeConnexityInfo.h"






class CATSobMesh;
class CATSobFace;
class CATSobVertex;

//Structure subdivision


class CATSobFace;
class CATSobEdge;
class CATSobVertex;

class CATSmoElementaryGrid;
class CATSmoExtractGridOperatorForMultiGrid;



//Classe principale
class ExportedByCATSmoOperators CATSmoMultiExtractGridOperator
{
public:

  

  //Destructeur
  virtual ~CATSmoMultiExtractGridOperator(){};

  virtual CATSobDiag Run() = 0;

  //Get The Number Of Grids
  virtual int GetNumberOfGrids() const = 0;
  virtual int GetTriangularFaces(CATLISTP(CATSobFace) &oTriangularFaces) const = 0 ;

  //Do not Remove/Delete the ElementaryGrid since it use by the operator and will be deleted internally
  //NumGrid [1..GetNumberOfGrids] 
  // DO NOT FORGET to Call the RemoveAllGrid method before deleting the CATSmoMultiExtractGridOperator
  // otherwise you will have to delete all grids by yourself
  virtual CATSobDiag GetOneGrid(int NumGrid,CATSmoElementaryGrid *& ElementaryGrid) const = 0;
  //Delete All CATSmoElementaryGrid
  virtual void RemoveAllGrids() = 0;

  virtual int GetAllSplittingEdges(CATLISTP(CATSobEdge) & oSplittingEdges) const = 0;

  virtual int GetCorners(CATLISTP(CATSobVertex) & oCorners) const = 0;

  virtual CATSobDiag GetEdgeConnexity(CATSobEdge * iEdge,CATSmoMEGOEdgeConnexityInfo & oConnexity) const = 0;
protected:
  //Constructeur
  CATSmoMultiExtractGridOperator(CATSobMesh* iMesh){};
};

ExportedByCATSmoOperators
CATSmoMultiExtractGridOperator * CATCreateSmoMultiExtractGridOperator(CATSobMesh* iMesh);


#endif
