//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/04/24
//===================================================================

#ifndef EKSnapshotObserver_H
#define EKSnapshotObserver_H

#include "EKExportedByKernel.h"
#include <vector>

namespace EK
{
class Key;
class Snapshot;

class ExportedByKernel SnapshotObserver
{
public:
           SnapshotObserver() = default;
  virtual ~SnapshotObserver() = default;

  SnapshotObserver(const SnapshotObserver&) = delete;
  SnapshotObserver& operator=(const SnapshotObserver&) = delete;

  /**
   * This method is called by the Store when snapshot keys are updated.
   * Write your own derived SnapshotObserver class to implement this method.
   */
  virtual void Notify(Snapshot& snapshot, const std::vector<Key>& updatedKeys) = 0;
};
}

#endif /*EKSnapshotObserver_H*/
