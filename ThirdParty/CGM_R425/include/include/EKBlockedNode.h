//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/02/11
//===================================================================

#ifndef EKBlockedNode_H
#define EKBlockedNode_H

#include "EKExportedByKernel.h"
#include "EKNode.h"

namespace EK
{
class ExportedByKernel BlockedNode : public Node
{
protected:
  explicit BlockedNode(const CATUnicodeString& pool);
  explicit BlockedNode(const char* pool);
           BlockedNode(const CATUnicodeString& pool, const NodeSettings& settings);
           BlockedNode(const char* pool, const NodeSettings& settings);
};
}

#endif /*EKBlockedNode_H*/
