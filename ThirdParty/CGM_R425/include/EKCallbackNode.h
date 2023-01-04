//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/11/26
//===================================================================

#ifndef EKCallbackNode_H
#define EKCallbackNode_H

#include "EKExportedByKernel.h"
#include "EKNode.h"

class CATCommand;

namespace EK
{
class NodeSettings;

class ExportedByKernel CallbackNode : public Node
{
protected:
  explicit CallbackNode(const CATUnicodeString& pool);
  explicit CallbackNode(const char* pool);
           CallbackNode(const CATUnicodeString& pool, const NodeSettings& settings);
           CallbackNode(const char* pool, const NodeSettings& settings);

public:
  void RunAndWait();
  static void Callback(CATCommand* command, int type, void* data);
};
}

#endif /*EKCallbackNode_H*/
