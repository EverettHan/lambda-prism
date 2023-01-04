//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/03/09
//===================================================================

#ifndef EKStringComparator_H
#define EKStringComparator_H

#include "DSUnicodeString.h"

namespace EK
{
struct StringComparator
{
  bool operator()(const CATUnicodeString& lhs, const CATUnicodeString& rhs) const
  {
    return lhs.SortCompare(rhs) < 0;
  }
};
}

#endif /*EKStringComparator_H*/
