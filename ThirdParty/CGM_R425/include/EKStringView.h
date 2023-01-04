//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2019/01/30
//===================================================================

#ifndef EKStringView_H
#define EKStringView_H

#include "EKExportedByKernel.h"
#include <stddef.h>
#include <string>

class CATUnicodeString;

namespace EK
{
/**
 * Lightweight view into a character array.
 * It does *not* own the string to which it points,
 * and that data cannot be modified through the view.
 * It is the programmer's responsibility to ensure that
 * it does not outlive the pointed-to character array.
 */
class ExportedByKernel StringView
{
public:
  StringView() noexcept;
  StringView(const char* str) noexcept;
  StringView(const char* str, size_t size) noexcept;
  StringView(const std::string& str) noexcept;

  /**
   * Returns the number of characters in the view.
   */
  size_t Size() const;

  /**
   * Returns a pointer to the underlying character array.
   * Note that the returned buffer may or may not be nul-terminated;
   * therefore, do not pass it to a routine that expects a nul-terminated string.
   */
  const char* Data() const;

  /**
   * Returns a "substring" of the view (at offset pos and length size) as another view.
   */
  StringView Sub(size_t pos, size_t size) const;

  /**
   * Moves the start of the view forward by n characters.
   */
  void RemovePrefix(size_t n);

  /**
   * Moves the end of the view backward by n characters.
   */
  void RemoveSuffix(size_t n);

  /**
   * Checks if the view starts with the given prefix.
   */
  bool StartsWith(const StringView& sv) const;

  /**
   * Checks if the view ends with the given suffix.
   */
  bool EndsWith(const StringView& sv) const;

  /**
   * Converts to owning strings.
   */
  std::string ToString() const;
  CATUnicodeString ToUnicode() const;

private:
  const char* ptr_;
  size_t size_;
};

DSYExport bool operator==(const StringView& lhs, const StringView& rhs);
DSYExport bool operator!=(const StringView& lhs, const StringView& rhs);
DSYExport bool operator<(const StringView& lhs, const StringView& rhs);
}

#endif /*EKStringView_H*/
