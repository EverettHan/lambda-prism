//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2015/08/12
//===================================================================

#ifndef EKContextErrors_H
#define EKContextErrors_H

#include "EKStringView.h"
#include <iostream>

namespace EK
{
inline void displayOnCout(const StringView& prefix, const StringView& message)
{
  std::cout.write(prefix.Data(), prefix.Size());
  std::cout.write(message.Data(), message.Size());
  std::cout << std::endl;
}
}

#endif /*EKContextErrors_H*/
