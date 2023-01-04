//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/27
//===================================================================

#ifndef EKSnapshot_H
#define EKSnapshot_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <vector>

namespace EK
{
class Binary;
class Key;
class SnapshotObserver;
class SnapshotImpl;

class ExportedByKernel Snapshot
{
public:
  /**
   * A snapshot must be created from a store.
   * Every future modifications on the store will not impact the created snapshot.
   */
           Snapshot();

  /**
   * A snapshot must be created from a store.
   * Every future modifications on the store will not impact the created snapshot.
   *
   * You will get a snapshot only for the specified keys
   */
  explicit Snapshot(const std::vector<Key>& keys);
           Snapshot(const int* keys, int size);
          ~Snapshot();

  /**
   * Iterate and modify the snapshot.
   * Return S_FALSE if there were no next version.
   */
  HRESULT Next();

  /**
   * Iterate and modify the snapshot.
   * Return S_FALSE if there were no previous version.
   */
  HRESULT Prev();

  /**
   * Get updated keys since snapshot creation or previous last() call.
   * The given parameter updatedKeys will contain the list of updated keys.
   */
  HRESULT Last(std::vector<Key>& updatedKeys);
  HRESULT Last(std::vector<int>& updatedKeys);

  Snapshot(const Snapshot&) = delete;
  Snapshot& operator=(const Snapshot&) = delete;

public:
  /**
   * Get the binary at the key, considering the state of the store when you get this snapshot.
   *
   * returns S_FALSE if not found.
   */
  HRESULT Get(const Key& key, Binary& value) const;
  HRESULT Get(int key, Binary& value) const;

  /**
   * Create an observer. It will be notified when snapshot key values are modified.
   * The observer is allocated with the parameters.
   * Return a null pointer in case of error.
   */
  template <typename T, typename... Args>
  T* CreateObserver(double minTimeBetweenNotification, Args&&... args);

  /**
   * Delete the observer. The observer no longer receives notification when snapshot key values are modified.
   */
  HRESULT DeleteObserver();

private:
  HRESULT CreateObserver(SnapshotObserver* observer, double minTimeBetweenNotification);

private:
  SnapshotImpl& impl_;

private:
  friend SnapshotImpl& getImpl(const Snapshot& snapshot);
};
}

#include "EKSnapshot.hxx"

#endif /*EKSnapshot_H*/
