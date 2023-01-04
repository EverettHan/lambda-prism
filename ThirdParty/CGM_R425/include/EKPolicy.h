//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/08/01
//===================================================================

#ifndef EKPolicy_H
#define EKPolicy_H

namespace EK
{
enum ExecutePolicy
{
  hideWindow = 0x0,
  showWindow = 0x1,
  processRespawn = 0x2,
  processDetach = 0x4,
  processBlocking = 0x8,
  processRespawnViaAutoScaling = 0x10,
  processInternal = 0x20
};

enum BoxingPolicy
{
  BoxingDisabled = 0x0,
  BoxingMemory = 0x1,
  BoxingCpu = 0x2
};
}

#endif /*EKPolicy_H*/
