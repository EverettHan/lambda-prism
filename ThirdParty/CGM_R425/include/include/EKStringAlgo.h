//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2012/03/09
//===================================================================

#ifndef EKStringAlgo_H
#define EKStringAlgo_H

#include "DSUnicodeString.h"
#include <locale.h>
#if (defined(_IOS_SOURCE) || defined(_DARWIN_SOURCE))
#include <xlocale.h>
#endif
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#ifdef _WINDOWS_SOURCE
#define locale_t _locale_t
#define newlocale(mask, name, x) _create_locale(mask, name)
#define freelocale _free_locale
#else
#define newlocale(mask, name, x) newlocale(mask ## _MASK, name, x)
#endif /*_WINDOWS_SOURCE*/

namespace EK
{
inline bool empty(const CATUnicodeString& value)
{
  return value.IsNull() == 1;
}

inline int size(const CATUnicodeString& value)
{
  return value.GetLengthInChar();
}

inline bool startsWith(const CATUnicodeString& value, const CATUnicodeString& start)
{
  return empty(start) || ! value.SearchSubString(start);
}

inline bool endsWith(const CATUnicodeString& value, const CATUnicodeString& end)
{
  const int index = size(value) - size(end);
  return index >= 0 && value.SearchSubString(end, 0, CATUnicodeString::CATSearchModeBackward) == index;
}

inline int toInt(const char* str)
{
  char* end = nullptr;
  int value = strtol(str, &end, 10);
  return *end ? 0 : value;
}

inline unsigned int toUInt(const char* str)
{
  char* end = nullptr;
  unsigned int value = strtoul(str, &end, 10);
  return *end ? 0 : value;
}

inline int8_t toInt8(const char* str)
{
  int16_t value;
  int ret = sscanf(str, "%hd", &value); // hh prefix is not supported by Visual Studio
  return ret == 1 ? (int8_t)value : 0;
}

inline uint8_t toUInt8(const char* str)
{
  uint16_t value;
  int ret = sscanf(str, "%hu", &value); // hh prefix is not supported by Visual Studio
  return ret == 1 ? (uint8_t)value : 0;
}

inline int16_t toInt16(const char* str)
{
  int16_t value;
  int ret = sscanf(str, "%hd", &value);
  return ret == 1 ? value : 0;
}

inline uint16_t toUInt16(const char* str)
{
  uint16_t value;
  int ret = sscanf(str, "%hu", &value);
  return ret == 1 ? value : 0;
}

inline int64_t toInt64(const char* str)
{
  long long value;
  int ret = sscanf(str, "%lld", &value);
  return ret == 1 ? value : 0;
}

inline uint64_t toUInt64(const char* str)
{
  unsigned long long value;
  int ret = sscanf(str, "%llu", &value);
  return ret == 1 ? value : 0;
}

inline double toDouble(const char* str)
{
  char* end = nullptr;
#ifdef _ANDROID_SOURCE
  double value = strtod(str, &end);
#else
  locale_t locale = newlocale(LC_NUMERIC, "C", nullptr);
#ifdef _WINDOWS_SOURCE
  double value = _strtod_l(str, &end, locale);
#else
  locale_t old = uselocale(locale);
  double value = strtod(str, &end);
  uselocale(old);
#endif /*_ANDROID_SOURCE*/
  freelocale(locale);
#endif
  return *end ? 0. : value;
}

inline float toFloat(const char* str)
{
  return static_cast<float>(toDouble(str));
}

inline CATUnicodeString toString(int value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%d", value);
  return buffer;
}

inline CATUnicodeString toString(unsigned int value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%u", value);
  return buffer;
}

inline CATUnicodeString toString(long value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%ld", value);
  return buffer;
}

inline CATUnicodeString toString(unsigned long value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%lu", value);
  return buffer;
}

inline CATUnicodeString toString(long long value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%lld", value);
  return buffer;
}

inline CATUnicodeString toString(unsigned long long value)
{
  char buffer[32];
  (void)snprintf(buffer, 32, "%llu", value);
  return buffer;
}

inline CATUnicodeString toString(double value, const char* format = "%.17g")
{
  char buffer[32];
#ifdef _ANDROID_SOURCE
  snprintf(buffer, 32, format, value);
#else
  locale_t locale = newlocale(LC_NUMERIC, "C", nullptr);
#ifdef _WINDOWS_SOURCE
  _snprintf_l(buffer, 32, format, locale, value);
#else
  locale_t old = uselocale(locale);
  snprintf(buffer, 32, format, value);
  uselocale(old);
#endif /*_ANDROID_SOURCE*/
  freelocale(locale);
#endif
  return buffer;
}

inline CATUnicodeString toString(const char* value)
{
  return CATUnicodeString(value);
}

inline CATUnicodeString toString(bool value)
{
  return value ? "true" : "false";
}

inline const char* rcToString(HRESULT rc)
{
  if (rc == S_OK)
    return "S_OK";
  if (rc == S_FALSE)
    return "S_FALSE";
  if (rc == E_FAIL)
    return "E_FAIL";
  if (rc == E_NOTIMPL)
    return "E_NOTIMPL";
  if (rc == E_INVALIDARG)
    return "E_INVALIDARG";
  if (rc == E_UNEXPECTED)
    return "E_UNEXPECTED";
  if (rc == E_NOINTERFACE)
    return "E_NOINTERFACE";
  if (rc == E_OUTOFMEMORY)
    return "E_OUTOFMEMORY";
  if (rc == E_POINTER)
    return "E_POINTER";
  if (rc == E_HANDLE)
    return "E_HANDLE";
  if (rc == E_ABORT)
    return "E_ABORT";
  if (rc == E_ACCESSDENIED)
    return "E_ACCESSDENIED";
  if (rc == E_PENDING)
    return "E_PENDING";

  return FAILED(rc) ? "FAILED(rc)" : "SUCCEEDED(rc)";
}
}

#endif /*EKStringAlgo_H*/
