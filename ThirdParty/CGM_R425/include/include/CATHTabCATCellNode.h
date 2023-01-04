/* -*-c++-*- */
//===========================================================================
//
// Avr. 2002   Migration vers CATCGMHashTable                       HCN
//
//===========================================================================
#ifndef CATHTabCATCellNode_h
#define CATHTabCATCellNode_h

#include <stdio.h>
#include "CATCGMHashTable.h"
#include "CATCGMNewArray.h"

class CATCellNode;

//#define OLD_HASH_TABLE_CODE_CELL_NODE

#ifdef OLD_HASH_TABLE_CODE_CELL_NODE

//=============================================================================
// ANCIEN CODE
//=============================================================================
/*
class CATHTabCATCellNode
{
public:

  CATHTabCATCellNode(int iSizeEstimate = 0);
  ~CATHTabCATCellNode();
  CATCGMNewClassArrayDeclare;
  
  void Insert(CATCellNode *);
  inline CATCellNode * Get(int iPos) const
  {
    if (iPos < 0 || iPos >= NbCellStocke)
      return NULL;
    return (CATCellNode *)*(AllocatedZone + DimArray + 2 * iPos);
  };

  void * Locate(CATCellNode *) const;
  CATCellNode * KeyLocate(unsigned int) const;
  void   Remove(CATCellNode *);
  void   RemoveAll();
  int    Size() const;
  
private:
  
  void  ReAllocate();

  int UpToNiceModulo(int);
  
  int * AllocatedZone;   // address of the allocated memory  
  int   DimArray;        // dimension of the hashtab (maximum number of bucket to be stored in the Hashtable)
  int   ArrayOrig[93];   // static array (93 = 3*DimArray with DimArray =31) 
  int * LastDirecBloc;   // Address of the first free bucket
  int   NbFreeBucket;	// Number of free buckets 
  int   NbCellStocke;    //  number of bucket stored in the hashtable
};
*/
//=============================================================================
// FIN ANCIEN CODE
//=============================================================================
#else

class CATHTabCATCellNode : public CATCGMHashTable
{
public:

  CATHTabCATCellNode(int iEstimatedSize = 0);
  ~CATHTabCATCellNode();
  CATCGMNewClassArrayDeclare;

  inline int                Insert(CATCellNode* ipNode);
  inline CATCellNode*       Get(int iPos) const;
  inline void*              Locate(CATCellNode* ipNode) const;
  inline CATCellNode*       KeyLocate(unsigned int iKey) const;
  inline int                Remove(CATCellNode* ipNode);

private:

  // Override de CATCGMHashTable
  static unsigned int HashKeyFunction(void* ipElem);
};

//-----------------------------------------------------------------------------
// Insert
//-----------------------------------------------------------------------------
inline int CATHTabCATCellNode::Insert(CATCellNode* ipNode)
{
  return (this->CATCGMHashTable::Insert((void*)ipNode));
}

//-----------------------------------------------------------------------------
// Get
//-----------------------------------------------------------------------------
inline CATCellNode* CATHTabCATCellNode::Get(int iPos) const
{
  return ((CATCellNode*)this->CATCGMHashTable::Get(iPos));
}

//-----------------------------------------------------------------------------
// Locate
//-----------------------------------------------------------------------------
inline void* CATHTabCATCellNode::Locate(CATCellNode* ipNode) const
{
  return (this->CATCGMHashTable::Locate((void*)ipNode));
}

//-----------------------------------------------------------------------------
// KeyLocate
//-----------------------------------------------------------------------------
inline CATCellNode* CATHTabCATCellNode::KeyLocate(unsigned int iKey) const
{
  return ((CATCellNode*)this->CATCGMHashTable::KeyLocate(iKey));
}

//-----------------------------------------------------------------------------
// Remove
//-----------------------------------------------------------------------------
inline int CATHTabCATCellNode::Remove(CATCellNode* ipNode)
{
  return (this->CATCGMHashTable::Remove((void*)ipNode));
}

#endif

#endif
