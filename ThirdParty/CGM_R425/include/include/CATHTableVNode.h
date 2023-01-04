#ifndef CATHTableVNode_h
#define CATHTableVNode_h

#include "CATCGMHashTable.h"
#include "ListPOfCATVNode.h"
#include "CATErrorDef.h"

class CATVNode;
class CATVLink;

class ExportedByCATMathematics CATHTableVNode
{
public:
  CATHTableVNode();
  CATCGMNewClassArrayDeclare; // Pool allocation
  ~CATHTableVNode();

  HRESULT InsertNode(CATVNode *iNode);
  HRESULT InsertNode(const ListPOfCATVNode &iNodes);

  HRESULT FindNode(CATVNode *iNode) const;

  INLINE int Size() const { return _HT.Size(); }
  INLINE void RemoveAll() { _HT.RemoveAll(); }

private:
  CATCGMHashTable _HT;
};

#endif
