//===================================================================================
// Copyright Dassault Systemes Provence 2003-2007, All Rights Reserved 
//===================================================================================
//
// CATSmoChainEdgesOperator.h
//
//===================================================================================
//
// Usage notes: Compute N lists of C0-chained edges from a list of edges.
//
//===================================================================================
//  November,  2008 : RBD : Creation with a little help from JCV
//===================================================================================
#ifndef CATSmoChainEdgesOperator_H
#define CATSmoChainEdgesOperator_H

//Pour l'export
#include "CATSmoOperators.h"

//Objets subdivision
#include "CATSobDiag.h"
#include "CATSobEdge.h"
#include "CATSobListOfEdge.h"

#include "CATBoolean.h"

class CATSobVertex;

class ExportedByCATSmoOperators CATSmoChainEdgesOperator
{
public:

  //Destructeur
  virtual ~CATSmoChainEdgesOperator();

  //Run de l'opérateur
  virtual CATSobDiag Run() = 0;

  //Obtention du diag
  virtual CATSobDiag GetDiag() const = 0;

  // Set edges
  //  Input : - iListOfEdges : A pointer of a list of pointers of edges.
  //  Output: - oNbEdges     : the number of DIFFERENT edges in the input list
  //  Return : void 
  // 
  virtual CATSobDiag SetEdgesToChain(const CATLISTP(CATSobEdge)* iListOfEdges, int &oNbEdges) = 0;

  // Set vertices
  //  Input : - iListOfVertices : A pointer of a list of pointers of vertices.
  //                              These vertices are "cutting vertices" i.e
  //                              these vertices, if encountered, stop the chaining process.
  //  Return : void 
  // 
  virtual CATSobDiag SetCuttingVertices(const CATLISTP(CATSobVertex)* iListOfVertices) = 0;

  // Get the total number of computed chained lists
  //  Output : - oHowMuchLists : The number of computed C0-chained lists of edges.
  //           
  //  Return : Diag 
  // 
  virtual CATSobDiag GetNumberOfChainedLists(int &oHowMuchLists) = 0;

  // Get a list by its number (between 1 and oHowMuchLists)
  // The computed list iIndicList is ADDED (appended)to the input/ouput list ioListOfEdges.
  // oHowMuchElem is the total number of ADDed edges (output), NOT the number of edges in ioListOfEdges.
  // So BE CAREFUL if you don't use an empty list.
  //
  //  Input  : - iIndicList   : The indicia of the list to return (between 1 and oHowMuchLists)
  //           - ioListOfEdges: A list of edges empty or not.
  //  Output : - ioListOfEdges: ADDED (or appended) list of C0-chained edges.
  //           - oHowMuchElem : The number of edges ADDED in the list.
  //           - oIsClosed    : TRUE if the ADDed chain of edges is closed.
  //           
  //  Return : Diag 
  // 
  virtual CATSobDiag GetAList(const int iIndicList, CATLISTP(CATSobEdge)& ioListOfEdges, int &oHowMuchElem, CATBoolean &oIsClosed) = 0;

  // Get the size of a list by its number (between 1 and oHowMuchLists)
  // oHowMuchElem is the number of edges (output) in the iIndicList list computed.
  //
  //  Input  : - iIndicList   : The indicia of the list to return (between 1 and oHowMuchLists)
  //  Output : - oHowMuchElem : The number of edges ADDED in the list.
  //           - oIsClosed    : TRUE if the chain of edges is closed.
  //           
  //  Return : Diag 
  // 
  virtual CATSobDiag GetSizeOfAList(const int iIndicList, int &oHowMuchElem, CATBoolean &oIsClosed) = 0;


  // Get the extremities of a list by its number (between 1 and oHowMuchLists)
  //
  //  Input  : - iIndicList   : The indicia of the list to return (between 1 and oHowMuchLists)
  //  Output : - oStartVertex : The start vertex if the chain IS NOT closed, NULL otherwise.
  //           - oEndVertex   : The end vertex if the chain IS NOT closed, NULL otherwise.
  //           
  //  Return : Diag 
  // 
  virtual CATSobDiag GetExtremitiesOfAList(const int iIndicList, CATSobVertex* &oStartVertex, CATSobVertex* &oEndVertex) = 0;

  // Iterator : Get the first, next or last list of chained edges
  // The computed list is ADDED to the input/ouput list ioListOfEdges.
  // oHowMuchElem is the total number of ADDed edges (output), NOT the number of edges in ioListOfEdges.
  // So BE CAREFUL if you don't use empty input/output list.
  //
  //  Output : - ioListOfEdges: ADDED (or appended) list of C0-chained edges.
  //           - oHowMuchElem : The number of edges ADDED in the list.
  //           - oIsClosed    : TRUE if the ADDed chain of edges is closed.
  //           - oStartVertex : The start vertex if the chain IS NOT closed, NULL otherwise.
  //           - oEndVertex   : The end vertex if the chain IS NOT closed, NULL otherwise.
  //           
  //  Return : Diag 
  //           
  virtual CATSobDiag GetFirstList(CATLISTP(CATSobEdge)&  ioListOfEdges, int &oHowMuchElem, CATBoolean &oIsClosed, CATSobVertex* &oStartVertex, CATSobVertex* &oEndVertex) = 0;
  virtual CATSobDiag GetNextList (CATLISTP(CATSobEdge)&  ioListOfEdges, int &oHowMuchElem, CATBoolean &oIsClosed, CATSobVertex* &oStartVertex, CATSobVertex* &oEndVertex) = 0;
  virtual CATSobDiag GetLastList( CATLISTP(CATSobEdge)&  ioListOfEdges, int &oHowMuchElem, CATBoolean &oIsClosed, CATSobVertex* &oStartVertex, CATSobVertex* &oEndVertex) = 0;

protected:

  //Constructeur (NE PAS UTILISER). Utilisez la methode de creation ci dessous.
  CATSmoChainEdgesOperator();

};


//Méthode de création de l'opérateur
ExportedByCATSmoOperators
CATSmoChainEdgesOperator* CATSmoCreateChainEdgesOperator();

#endif
