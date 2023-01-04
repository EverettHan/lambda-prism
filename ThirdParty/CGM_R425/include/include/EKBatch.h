//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/27
//===================================================================

#ifndef EKBatch_H
#define EKBatch_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

namespace EK
{
class BatchImpl;
class Binary;
class Key;
class Snapshot;
class Store;
class Timestamp;

class ExportedByKernel Batch
{
public:
   /**
    * Batch Constructor
    *
    * A batch must be used in a single thread.
    */
  explicit Batch(Store& store);
  explicit Batch(Snapshot& snapshot);
          ~Batch();

  Batch(const Batch&) = delete;
  Batch& operator=(const Batch&) = delete;

public:
  /**
   * Add or replace a binary for "key".
   * The binary is immediately stored in a cache, you do not have to keep it.
   *
   * The associated store is not affected by this method until you commit the batch in the store.
   */
  HRESULT Put(const Key& key, const Binary& value);
  HRESULT Put(int key, const Binary& value);

  /**
   * Delete the stored binary for "key".
   *
   * The associated store is not affected by this method until you commit the batch in the store.
   */
  HRESULT Delete(const Key& key);
  HRESULT Delete(int key);

  /**
   * Commit the batch to the store.
   *
   * The batch is NOT cleared when you commit it. So be careful if you reuse the same batch.
   * It may be safer to use a new one.
   */
  HRESULT Commit() const;

  /**
   * Commit the batch to the store.
   * Outputs a timestamp corresponding to this commit action.
   */
  HRESULT Commit(Timestamp& timestamp) const;

private:
  BatchImpl& impl_;
};
}

#endif /*EKBatch_H*/
