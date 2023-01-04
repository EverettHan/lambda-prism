#ifndef CATHTableVNodeAssocVLinks_h
#define CATHTableVNodeAssocVLinks_h

#include "CATCGMHashTableWithAssoc.h"
#include "ListPOfCATVNode.h"
#include "ListPOfCATVLink.h"
#include "CATErrorDef.h"

class CATVNode;
class CATVLink;

class ExportedByCATMathematics CATHTableVNodeAssocVLinks
{
public:
  CATHTableVNodeAssocVLinks();
  CATCGMNewClassArrayDeclare; // Pool allocation
  ~CATHTableVNodeAssocVLinks();

  HRESULT InsertLink(CATVNode *iNode, CATVLink *iLink);
  HRESULT RemoveLink(CATVNode *iNode, CATVLink *iLink);

  HRESULT FindNode(CATVNode *iNode) const;
  HRESULT FindNode(CATVNode *iNode, ListPOfCATVLink &oLinks) const;

  void GetNodes(ListPOfCATVNode &oNodes) const;

  INLINE int Size() const { return _HT.Size(); }

private:
  CATCGMHashTableWithAssoc _HT;
};

#endif
