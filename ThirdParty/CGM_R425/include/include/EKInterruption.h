//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017/05/24
//===================================================================

#ifndef EKInterruption_H
#define EKInterruption_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

namespace EK
{
class InterruptionImpl;

class ExportedByKernel Interruption
{
public:
   Interruption();
  ~Interruption();

  Interruption(const Interruption& rhs);
  Interruption& operator=(const Interruption& rhs);

public:
  /**
   * Notify that the message related to this Interruption must be interrupted.
   */
  HRESULT Interrupt();

  /**
   * Return true if the message related to this Interruption has already been interrupted.
   */
  bool IsInterrupted() const;

private:
  friend InterruptionImpl* getImpl(const Interruption& interruption);

private:
  InterruptionImpl* impl_;

public:
  explicit Interruption(InterruptionImpl* impl);
};
}

#endif /*EKInterruption_H*/
