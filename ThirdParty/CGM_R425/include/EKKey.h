//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014/11/24
//===================================================================

#ifndef EKKey_H
#define EKKey_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h" // for SWXCSCommandServices/ProtectedInterfaces/SWXCSPredictiveCacheStore.h
#include <stdint.h>

namespace EK
{
class ExportedByKernel Key
{
public:
  Key();

public:
  bool operator<(const Key& rhs) const;
  bool operator==(const Key& rhs) const;
  bool operator!=(const Key& rhs) const;

private:
  // friends are here because Get/Key(uint64_t) must not be accessible by user code
  friend class Batch;
  friend class Snapshot;
  friend class StoreImpl;
  friend class StoreNode;
  friend class StoreNodeSlave;
  friend class StoreNodeMaster;
  friend uint64_t getKey(const Key& key);

private:
  explicit Key(uint64_t key);
  uint64_t Get() const;

private:
  uint64_t key_;
};
}

#endif /*EKKey_H*/
