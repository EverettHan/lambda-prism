#ifndef CATlsoTree_h
#define CATlsoTree_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2010

//===========================================================================
//
//
//
// November 2018  Creation ( Heritance from CATCGMVirtual )  QF2
//
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMVirtual.h"
#include "CATSysBoolean.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATMathInline.h"
#include "CATListPV.h"

class CATlsoTreeNode;
class CATCell;
class CATCellHashTable;
class CATCGMHashTable;
class CATICGMObject;
class CATlsoCellTreeNode;

// --------------------------------------------------------------------------------
// Class CATlsoTree
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATlsoTree : public CATCGMVirtual
{
public :
  virtual ~CATlsoTree();

  // INLINE CATUINT32 GetNbElements() const;
  INLINE int Size() const;

  CATBoolean Owns(CATlsoTreeNode *iNode) const;

  // recursive deletion - returns nb delete nodes.
  // 0  -> cannot be found.
  // -1 -> cannot be removed (ipTreeNode is Root).  
  int RemoveNode(CATlsoTreeNode * ipTreeNode, CATBoolean iPreserveRootAndProtected=TRUE, CATCGMHashTable *oDeleteObjectHT=NULL);


protected :
  CATlsoTree();
  CATlsoTree(CATlsoTreeNode *iTopNode);

  INLINE const CATListPV & GetTopNodes() const;
  INLINE const CATCGMHashTableWithAssoc & GetLinkBufferHT() const;

  // return created child node if success
  int AddNode(CATlsoTreeNode *ipParentNode, CATlsoTreeNode * ipChildNode);

  void GetAllObjectFrom(const CATlsoTreeNode *ipParentNode, CATCGMHashTable &oAllObjectHT) const;

  const CATlsoTreeNode * FindNodeFromObject(const CATICGMObject *iObject) const;

private :
  // recursive 
  int RecursiveRemove(CATlsoTreeNode *ipCell, CATCGMHashTable *oDeletedCellHT=NULL);

  // forbiden operator
  CATlsoTree(const CATlsoTree & iLsoTree);
  CATlsoTree & operator=(const CATlsoTree & iLsoTree);

  // Internal data
  // --------------------------------------
  CATListPV  _HeadNodeList;

  CATCGMHashTableWithAssoc    _BufferAssocHT; // link iCell -> Node
};

INLINE int CATlsoTree::Size() const {
  return _BufferAssocHT.Size(); }

INLINE const CATListPV & CATlsoTree::GetTopNodes() const {
  return _HeadNodeList; }

INLINE const CATCGMHashTableWithAssoc & CATlsoTree::GetLinkBufferHT() const {
  return _BufferAssocHT; }




// ================================================================================
// Class CATlsoCellTree
// ================================================================================
class ExportedByCATTopologicalObjects CATlsoCellTree : public CATlsoTree
{
public :
  // Constructor 
  CATlsoCellTree(const CATCell *ipCell=NULL);
  // Destructor
  virtual ~CATlsoCellTree();

  
  // ----------------------------------------------------------
  // Modifiers
  // ----------------------------------------------------------
  // return 1 if success
  int AddRoot(CATCell *ipParentCell);

  int AddNode(CATCell *ipParentCell, CATCell * ipChildCell, CATlsoCellTreeNode **oAssocChildNode=NULL);
  int AddNode(CATlsoCellTreeNode *ipParentNode, CATCell * ipChildCell);

  int RemoveNode(CATCell *ipCell, CATBoolean iPreserveRootAndProtected=TRUE, CATCellHashTable *oDeletedCellHT=NULL);
  
  // Protection service
  int SetAsProtected(CATlsoCellTreeNode *iCellTreeNode); // wont be remove by removeNode methods if iPreserveRootAndProtected is TRUE.

  // ----------------------------------------------------------
  // Access
  // ----------------------------------------------------------
  CATBoolean Owns(CATCell *iCell) const;
  // int TestLinkBetween(const CATCell *ipAncesterCell, const CATCell *ipSonCell) const;

  void GetAllCells(CATCellHashTable &oAllCellHT) const;
  void GetCellsFrom(const CATCell *ipParentCell, CATCellHashTable &oAllChildHT) const;

  CATlsoCellTreeNode * GetCellNode(const CATCell *ipCell) const;

protected :

  CATlsoCellTreeNode * CreateCellNode(const CATCell *ipCell) const;

private :


  // forbiden operator
  CATlsoCellTree(const CATlsoCellTree & iLsoTree);
  CATlsoCellTree & operator=(const CATlsoCellTree & iLsoTree);

};


#endif
