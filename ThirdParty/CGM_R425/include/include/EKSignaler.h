//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2013/02/12
//===================================================================

#ifndef EKSignaler_H
#define EKSignaler_H

#include "EKExportedByKernel.h"
#include "EKResults.h"
#include "CATSysErrorDef.h"
#include <memory>

namespace EK
{
class Node;
class SignalerData;

class ExportedByKernel Signaler : public Results
{
public:
  Signaler(Node& node, std::shared_ptr<SignalerData> data);
protected:
  ~Signaler() override;

  Signaler(const Signaler&) = delete;
  Signaler& operator=(const Signaler&) = delete;

public:
  HRESULT OnBinary(const Binary& message, Channel& worker) override;
  HRESULT OnText(const StringView& message, Channel& worker) override;

private:
  Node& node_;
  std::shared_ptr<SignalerData> data_;
};
}

#endif /*EKSignaler_H*/
