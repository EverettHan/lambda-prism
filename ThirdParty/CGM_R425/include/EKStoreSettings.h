//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/08/04
//===================================================================

#ifndef EKStoreSettings_H
#define EKStoreSettings_H

#include "EKExportedByKernel.h"

namespace EK
{
class ExportedByKernel StoreSettings
{
public:
  static const int noTimeout = -1;

  /**
   * This is the default mode when no StoreSettings are specified.
   *
   * A store master is created on the same machine and your (slave) store is connected to it.
   * Your store keeps data in its local cache. Data is fetched from its store master
   * only when it can't be found in the local cache. Then the found data is inserted into the local cache.
   */
  static StoreSettings UseReplication();

  /**
   * Your store is connected to a store master on another machine.
   * If a store master already exists locally, it is used.
   * Your store doesn't have any local cache.
   *
   * When your store is created it attempts to reach the Store master.
   * If the Store master doesn't respond before the timeout elapses,
   * the store stops waiting its store master and returns an error.
   * Use noTimeout if you want to wait for the Store master until it sends a response.
   */
  static StoreSettings NoReplication(int timeout = 60000); // default timeout is 60 seconds

private:
  friend class StoreImpl;

private:
  const bool useReplication_;
  const int timeout_;

private:
  StoreSettings(bool useReplication, int timeout);
  StoreSettings& operator=(const StoreSettings&) = delete;

};
}

#endif /*EKStoreSettings_H*/
