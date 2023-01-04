//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/27
//===================================================================

#ifndef EKTimestamp_H
#define EKTimestamp_H

#include "EKExportedByKernel.h"

namespace EK
{
class TimestampImpl;

class ExportedByKernel Timestamp
{
public:
  /**
   * A timestamp is set when you do a write access in the store (put, delete, etc).
   * Keeping a timestamp guarantees that, for each key, every value stored after this timestamp will keep being reachable through the store.
   */
   Timestamp();

  /**
   * When a timestamp is deleted, we release the values that are not reacheable anymore.
   * We will not deallocate data that are handled by a kept EK::Binary, even if an EK::Timestamp is deleted.
   */
  ~Timestamp();

public:
  Timestamp(const Timestamp& rhs);
  Timestamp& operator=(const Timestamp& rhs);

private:
  TimestampImpl* impl_;

private:
  friend TimestampImpl& getImpl(const Timestamp& timestamp);

public:
  explicit Timestamp(TimestampImpl& impl);
};
}

#endif /*EKTimestamp_H*/
