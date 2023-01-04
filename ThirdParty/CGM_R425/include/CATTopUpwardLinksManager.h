// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATTopUpwardLinksManager: 
//  Commonly needed services to get upwardlinks for body
//  
//
//
//=============================================================================
//
// Usage notes: 
//
//
//=============================================================================
//  November 2014  Creation                                                 U29
//=============================================================================

#ifndef CATTBHUpwardLinksSlave_H
#define CATTBHUpwardLinksSlave_H

#include "CATBoolean.h"
#include "ExportedByCATTopologicalObjects.h"
#include "ListPOfCATBody.h"

class CATCGMHashTableWithAssoc;
class HashTableAssocList;
class CellHashTableAssocList;


class ExportedByCATTopologicalObjects CATTopUpwardLinksManager
{

public:

  /**
  * Constructor
  */ 
  CATTopUpwardLinksManager(const ListPOfCATBody& iInputBodies);

  /**
  * Destructor
  */
  ~CATTopUpwardLinksManager();

  void Init();
  void        Dump(CATCGMOutput & os);
  CATBoolean  IsFreeEdge(CATEdge *ipEdge, ListPOfCATBody* opBodies=0);
  CATBoolean  IsCellInSideBody(CATCell*,CATBody*);

  //Attributs
  HashTableAssocList*             _pCellToBodies; // Link between (Vertex,Edge,Face) to bodies
  CellHashTableAssocList*         _pAllLinks;       // UpwardLinks for all input bodies
  CATCGMHashTableWithAssoc*       _pBodyToLinks;  //UpwardLinks per body

  ListPOfCATBody                 _inputBodies;
};

#endif
