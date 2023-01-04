// COPYRIGHT DASSAULT SYSTEMES 2020, ALL RIGHTS RESERVED.
//===================================================================

#ifndef UniquePtrDeleter_H
#define UniquePtrDeleter_H

#include "CATBaseUnknown.h"
#include "CATPolyBody.h"

namespace Poly
{
struct CATBaseUnknownDeleter {
  void operator()(CATBaseUnknown* p) const {
    if (p) {
      p->Release();
      p = nullptr;
    }
  }
};

struct CATPolyBodyDeleter {
  void operator()(CATPolyBody* p) const {
    if (p) {
      p->Release();
      p = nullptr;
    }
  }
};
}

#endif // !CATPolyDeleterHelper_H
