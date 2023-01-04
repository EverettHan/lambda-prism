//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/05/25
//===================================================================

#ifndef EKResults_H
#define EKResults_H

#include "EKExportedByKernel.h"
#include "CATSysErrorDef.h"

namespace EK
{
class Binary;
class Channel;
class HypervisorInterpreter;
class Node;
class NodeImpl;
class StringView;
class ResultsImpl;

class ExportedByKernel Results
{
public:
  /**
   * Must be allocated with the "new" C++ keyword and will be automatically destroyed.
   * Used to consolidate intermediate results.
   */
  explicit Results(Node& node);

protected:
  /**
   * Never destroy this object with the "delete" C++ keyword, we will do it for you.
   */
  virtual ~Results() = 0;

  Results(const Results&) = delete;
  Results& operator=(const Results&) = delete;

public:
  /**
   * This method is called each time an answer is received
   * @param input: The answer of the working node
   * @param worker: You can answer to the worker node
   */
  virtual HRESULT OnBinary(const Binary&     input, Channel& worker);
  virtual HRESULT OnText  (const StringView& input, Channel& worker);

  /**
   * Join is called once every node has reacted to the messages it received.
   */
  virtual HRESULT Join();

private:
  void AddRef();
  void Release();

private:
  ResultsImpl& impl_;

private:
  friend ResultsImpl& getImpl(const Results& results);
  friend class Engine;
  friend class Multiplexer;

public:
  explicit Results(NodeImpl& node);
  explicit Results(HypervisorInterpreter& hypervisor);
};
}

#endif /*EKResults_H*/
