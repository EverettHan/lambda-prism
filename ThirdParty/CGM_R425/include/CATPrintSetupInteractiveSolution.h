#ifndef CATPrintSetupInteractiveSolution_H
#define CATPrintSetupInteractiveSolution_H

#include "CATGMOperatorsInterfaces.h"

/* 
 * Abstract class for nesting interactive solution updates.
 * User must derive this class and implement its methods.
 */

class CATPrintSetupInteractiveSolution
{
public:
  CATPrintSetupInteractiveSolution();

  virtual ~CATPrintSetupInteractiveSolution() {}

  /*
   * Notify to user progression of nesting algorithm.
   * @param iProgressPercent A percentage value of progress.
   */
  virtual void NotifyProgress(double iProgressPercent) = 0;

  /*
   * The method will be called by the operator each time a new better solution is found.
   * User is free to read any data from the PrintSetup operator until this method returns
   * After data could be modified if another solution was found
   */
  virtual void NotifySolution() = 0;

  /*
   * When it has a meaning, the nesting algorithm will stop after finishing the firt iteration.
   * The user may still receive several updates on solve progress throug NotifyProgress or NotifySolution during
   * the first iteration.
   */
  void SetStopAfterFirstIteration(bool iStopAfterFirstIteration);
  bool IsStopAfterFirstIteration() const;

  void SetWaitCGM(bool iWait);
  bool IsWaitCGM() const;

private:
  bool _stopAfterFirstIteration;
  bool _waitCGM;
};

inline CATPrintSetupInteractiveSolution::CATPrintSetupInteractiveSolution()
  : _stopAfterFirstIteration(false)
  , _waitCGM(false)
{
}

inline void CATPrintSetupInteractiveSolution::SetStopAfterFirstIteration(bool iStopAfterFirstIteration)
{
  _stopAfterFirstIteration = iStopAfterFirstIteration;
}

inline bool CATPrintSetupInteractiveSolution::IsStopAfterFirstIteration() const
{
  return _stopAfterFirstIteration;
}

inline void CATPrintSetupInteractiveSolution::SetWaitCGM(bool iWait)
{
  _waitCGM = iWait;
}

inline bool CATPrintSetupInteractiveSolution::IsWaitCGM() const
{
  return _waitCGM;
}

#endif
