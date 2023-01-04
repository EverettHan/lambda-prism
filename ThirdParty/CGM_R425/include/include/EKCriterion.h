//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/03/12
//===================================================================

#ifndef EKCriterion_H
#define EKCriterion_H

#include "EKExportedByKernel.h"
#include <string>

class CATUnicodeString;

namespace EK
{
class ExportedByKernel Criterion
{
public:
  /**
   * The selected node will belong to my Hypervisor
   */
  static Criterion OnlyMyHypervisor();

  /**
   * The selected node will belong to another Hypervisor
   */
  static Criterion NotMyHypervisor();

  /**
   * The selected node will belong to my Hypervisor if possible
   * Otherwise it will belong to another Hypervisor
   */
  static Criterion PreferMyHypervisor();

  /**
   * The selected node will have the identifer 'identifier'
   */
  static Criterion Identifier(const CATUnicodeString& identifier);
  static Criterion Identifier(const char* identifier);

  /**
   * The selected node will be chosen within the specified timeout (integer in seconds)
   * If no node can be selected, the status of the NodeId becomes 'disconnected' at the end of the timeout
   */
  static Criterion Timeout(int valueInSeconds);
  Criterion WithTimeout(int valueInSeconds);

  /**
   * If no node can be immediatly selected, the Select will not be queued,
   * instead, the status of the NodeId becomes 'disconnected'
   */
  static Criterion NoQueuing();
  Criterion WithoutQueuing();

  /**
   * Only select an already running node
   * If no node can be selected, the status of the NodeId becomes 'disconnected'
   */
  static Criterion NoProcessCreation();
  Criterion WithoutProcessCreation();

private:
  int uniqueId_;
  int policy_;
  std::string name_;
  int timeout_;
  bool noQueuing_;
  bool noProcess_;

private:
  friend class Constraint;

private:
  Criterion(int policy, const std::string& name);
  Criterion(int uniqueId, int policy, const std::string& name, int timeout, bool noQueuing, bool noProcess);
};
}

#endif /*EKCriterion_H*/
