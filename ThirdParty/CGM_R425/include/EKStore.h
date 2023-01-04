//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/27
//===================================================================

#ifndef EKStore_H
#define EKStore_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"
#include <stddef.h>
#include <vector>

class CATUnicodeString;

namespace EK
{
class Binary;
class Context;
class Key;
class Snapshot;
class StoreImpl;
class StoreSettings;
class Timestamp;

class ExportedByKernel Store
{
public:
  /**
   * Store Constructor
   *
   * A store allows you to share data between different threads.
   */
   Store();

  /**
   * Store Constructor
   *
   * A store allows you to share data between different processes.
   */
   Store(const Context& context, const CATUnicodeString& name);
   Store(const Context& context, const CATUnicodeString& name, const StoreSettings& settings);

  ~Store();

  Store(const Store&) = delete;
  Store& operator=(const Store&) = delete;

public:
  /**
   * Create a new key.
   * monitoringName can be used to assign a key name for monitoring
   */
  Key CreateKey(const char* monitoringName = nullptr);

  /**
   * Create a vector of new keys.
   * monitoringPrefixName can be used to generate key names for monitoring
   */
  std::vector<Key> CreateKeys(size_t size, const char* monitoringPrefixName = nullptr);

  /**
   * Add or replace a binary for "key".
   * Input/Output a handle. If the key does not exist the store returns a new key
   * The binary is immediately stored, you do not have to keep it.
   */
  HRESULT Put(const Key& key, const Binary& value);
  HRESULT Put(int key, const Binary& value);

  /**
   * Add or replace a binary for "key".
   * Input/Output a handle. If the key does not exist the store returns a new key
   * The binary is immediately stored, you do not have to keep it.
   * Outputs a timestamp corresponding to this put action.
   */
  HRESULT Put(const Key& key, const Binary& value, Timestamp& timestamp);
  HRESULT Put(int key, const Binary& value, Timestamp& timestamp);

  /**
   * Delete the stored binary (if any) for "key".
   *
   * returns S_FALSE if not found.
   */
  HRESULT Delete(const Key& key);
  HRESULT Delete(int key);

  /**
   * Delete the stored binary (if any) for "key".
   * Outputs a timestamp corresponding to this delete action.
   *
   * returns S_FALSE if not found.
   */
  HRESULT Delete(const Key& key, Timestamp& timestamp);
  HRESULT Delete(int key, Timestamp& timestamp);

  /**
   * Get the binary for "key".
   *
   * returns S_FALSE if not found.
   */
  HRESULT Get(const Key& key, Binary& value);
  HRESULT Get(int key, Binary& value);

  /**
   * Get the binary for "key" at the provided timestamp.
   * A snapshot can be faster to get many keys for the same timestamp.
   *
   * returns S_FALSE if not found.
   */
  HRESULT Get(const Key& key, Binary& value, const Timestamp& timestamp);
  HRESULT Get(int key, Binary& value, const Timestamp& timestamp);

  /**
   * Create a snapshot of the store.
   * Every future modifications on the store will not impact the created snapshot.
   */
  HRESULT CreateSnapshot(Snapshot& snapshot);

  /**
   * Create a snapshot of the store at the provided timestamp.
   * Every future modifications on the store will not impact the created snapshot.
   */
  HRESULT CreateSnapshot(Snapshot& snapshot, const Timestamp& timestamp);

  /**
   * Every modification done on the store after the given timestamp will be reverted.
   */
  HRESULT Rollback(const Timestamp& timestamp);

  /**
   * Returns the current timestamp.
   */
  HRESULT GetCurrentTimestamp(Timestamp& timestamp);

  /**
   * Returns the oldest timestamp.
   */
  HRESULT GetOldestTimestamp(Timestamp& timestamp);

  /**
   * Returns the timestamps between begin and end. subsetKeys can contain a list of keys to inspect.
   * If subsetKeys is not provided all keys are used.
   */
  HRESULT GetTimestamps(const Timestamp& begin, const Timestamp& end, std::vector<Timestamp>& timeStamps, std::vector<Key>* subsetKeys = nullptr);

  /**
   * Set the persistent timestamp retained by the store.
   */
  HRESULT SetPersistent(const Timestamp& timestamp);

  /**
   * Save the store.
   */
  HRESULT Save(const CATUnicodeString& filename);

  /**
   * Load the store.
   */
  HRESULT Load(const CATUnicodeString& filename);

  /**
   * Reset the store.
   */
  HRESULT Reset();

  /**
   * Stop the store.
   */
  HRESULT Stop();

private:
  StoreImpl* impl_;

public:
  explicit Store(StoreImpl& impl);

private:
  friend StoreImpl* getImpl(const Store& store);
  friend class ESStore;
  void GetLocalMasterIdentifier(CATUnicodeString& hostName, int& port);
};
}

#endif /*EKStore_H*/
