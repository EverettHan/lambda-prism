//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/03/09
//===================================================================

#ifndef JSONJPair_H
#define JSONJPair_H

#include "DSUnicodeString.h"

namespace JSON
{
template <typename T>
class JPair
{
public:
  JPair(const CATUnicodeString& key, const T& value)
    : key_  (key)
    , value_(value)
  {
    // NOTHING
  }

  JPair& operator=(const JPair&) = delete;

public:
  const CATUnicodeString key_;
  const T& value_;
};

template <typename T>
[[deprecated("EXECUTION FRAMEWORK - DEPRECATED - 2019/07/10 - Use JSON::JOStream::Add instead")]] JPair<T> jpair(const CATUnicodeString& key, const T& value)
{
  return JPair<T>(key, value);
}
}

#endif /*JSONJPair_H*/
