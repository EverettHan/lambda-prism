#ifndef DSYStringView_H
#define DSYStringView_H

// IMPORTANT: Dependency checks, must come before first include!
// DSYStringView can be used to make views for different string types, not necessarily CATUnicodeString,
// so we DO NOT want to include CATUnicodeString.h (useless + MISC error), directly or indirectly (from DSYStringView dependencies).
// Besides, if DSYStringView is used to make a view from a CATUnicodeString instance, 
// this means the caller must already have included CATUnicodeString.h.
#if !defined(DSYString_H)
#define DSYStringView_CheckNotIncluded_DSYString
#endif

#define DSYStringHelper_INTERNAL_DONT_INCLUDE
#include "DSYStringHelperInternal.h"
#undef  DSYStringHelper_INTERNAL_DONT_INCLUDE
#define DSYStringView_INTERNAL_DONT_INCLUDE
#include "DSYStringViewInternal.h"
#undef  DSYStringView_INTERNAL_DONT_INCLUDE

namespace DSY
{
    namespace UCS   // UniCode Services
    {
        /**
         * make_view.
         * <b>Role</b>: helper function to simplify conversion of a C/C++ string to a specified destination format, 
         * in a type-safe and efficient way.
         * Currently supported source string types include both raw string types from the langage and some known string classes: 
         * CATUnicodeString, char, wchar_t, char16_t, char32_t.
         * Currently supported destination string types: char (UTF8 only), wchar_t (Implementation-defined encoding), char16_t (UTF-16), char32_t (UTF-32).
         * You will find real-life examples below. Nethertheless, it is strongly advised that you read the full documentation.
         * 
         * @param TDest 
         *   The first template parameter that specifies the destination format (out of one of the supported destination types).
         *   A compile-time error will be raised if it is not supported (cf. message in the console).
         * @param EncodingArgs...
         *   Second/third template parameters required only if either source or destination encoding is ambiguous. 
         *   DO NOT specify it unless requested to (if you get a compile-time error message).
         * @param iStr
         *   The source string to convert (guaranteed not to be modified by make_view). 
         *   Its type will be auto-deduced and a compile-time error will be raised if it is not supported (cf. message in the console).
         *   "raw strings" (pointer to array of characters) must be null-terminated.
         *   Be careful about memory lifecycle! make_view doesn't copy source data, it only references it.
         *   As such, temporary string objects (CATUnicodeString...) will not be allowed as input and a compile-time error will be raised.
         *   To overcome this problem, make sure source parameters are named variables.
         * @return 
         *   A proxy object that acts as a "view" of the input string in the requested format.
         *   This object is opaque and MUST be typed using the "auto" C++ keyword (cf. examples below).
         *   DO NOT explicit its type in your code, it would prevent our team from enhancing this service and will not be supported! Potential compile errors ahead!
         *   You can expect this object to expose the following functions:
         *   - const TDest *data() const
         *     returns a null-terminated string in the requested format.
         *   - size_t length() const
         *     returns the length of the destination string in number of characters (not in bytes)
         *   Note that this object is meant to be stack allocated and cannot be copied (cf. examples).
         *
         * NOTE:
         *   - If source and destination formats are equivalent, then a simple cast will performed (Efficiency concern)
         *   - make_view implements the Small String Optimization (SSO) to optimize conversion time for short strings.
         * 
         ************
         * Examples:
         ************
         *
         *   // IMPORTANT: "auto" MUST be used to type the object returned by make_view
         *
         *   // Rather than: using namespace DSY::UCS;
         *   using DSY::UCS::make_view; // Bring make_view in the current namespace for this compilation unit
         *   using DSY::UCS::FromUTF8;  // idem FromUTF8
         *   using DSY::UCS::ToUTF8;    // idem ToUTF8
         *   using DSY::UCS::FromANSI;  // idem FromANSI
         *
         *   void Func1(const wchar_t *iWStr);
         *   void Func2(const wchar_t *iWStr, size_t iWStrLen);
         *
         *   int main()
         *   ...
         *   // Conversion from CATUnicodeString to wchar_t
         *   CATUnicodeString cus;
         *   auto strViewWChar = make_view<wchar_t>(cus);
         *   Func1(strViewWChar.data());
         *   Func2(strViewWChar.data(), strViewWChar.length());
         *
         *   // Conversion from CATUnicodeString to UTF-8
         *   auto strViewUtf8 = make_view<char, ToUTF8>(cus);
         *
         *   // Conversion from wchar_t to UTF-8 char *
         *   auto strViewUtf8 = make_view<char, ToUTF8>(L"SomeWideCharString"); // null-terminated input
         *   const char * pStr = strViewUtf8.data();                    // null-terminated output
         *   
         *   // Conversion from ANSI char * to wchar_t
         *   const char * strANSI = "SomeANSIEncodedString";
         *   auto strViewWChar = make_view<wchar_t, FromANSI>(strANSI);    // Source encoding must be specified for char-strings
         *   const wchar_t * pWStr = strViewWChar.data();
         *   Func1(strViewWChar.data());
         *   Func2(strViewWChar.data(), strViewWChar.length());
         *   
         *   const char * strUTF8 = "SomeANSIEncodedString";
         *   auto strViewUTF16 = make_view<char16_t, FromUTF8>(strUTF8);   // Source encoding must be specified for char-strings
         *   ...
         *   // For V5/3DEXP compatibility, you can replace the use of "auto" by the use of the DSYUCSViewType macro:
         *   DSYUCSViewType(wchar_t) myView  = make_view<wchar_t>(U"Some Utf8-encoded string!");    // U prefix: from UTF-32 (char32_t)
         */
        template <typename TDest, typename... EncodingArgs, typename TSrc>
        auto make_view(TSrc&& iStr) -> internal::returned_view_t<TSrc, TDest, EncodingArgs...> {
            return internal::_make_view<TDest, EncodingArgs...>(std::forward<TSrc>(iStr));
        }
        
        
        /**
         * MultiByteEncoding
         * Family of variable-width encodings using varying numbers of bytes (char type).
         * Also referred to as MBCS (Multi-Byte Character Set), which is an extension of SBCS (Single-Byte Character Sets)
         * @param ANSI
         *   The ANSI term refers to code page. At runtime, System's char-based APIs, CATUnicodeString::ConvertToChar... manipulate
         *   char-strings assumed to be encoded with the active code page, which is environment dependent.
         *   This code page might be UTF8, but there is no guarantee.
         *   If the char-string you are about to convert is not UTF8-encoded, it is most probably encoded with the ANSI charset, 
         *   so you may want to specify this value.
         * @param UTF8
         *   Unicode compliant encoding for char-strings.
         *   If you know by contract that the char-string you are about to convert is UTF8-encoded, specify this value
         */
        
        /**
         * FromUTF8 / FromANSI / ToUTF8.
         * To be used for conversions "From Multi-Byte Character Set", i.e. from char-strings to specify their encoding.
         * cf. MultiByteEncoding paragraph.
         */
        // using: bring FromUTF8, ToUTF8 & FromANSI into this namespace
        using FromUTF8 = internal::FromUTF8;
        using ToUTF8   = internal::ToUTF8;
        using FromANSI = internal::FromANSI;
        
    }   // namespace UCS   // UniCode Services
}   // namespace DSY

/**
 * DSYUCSViewType macro for V5/3DEXP compatibility. Usage example:
 * DSYUCSViewType(wchar_t) myView  = DSY::UCS::make_view<wchar_t, FromUTF8>(u8"Some Utf8-encoded string!");
 */
#define DSYUCSViewType(destType)  auto


// Dependency checks
#if defined(DSYStringView_CheckNotIncluded_DSYString)
# if defined(DSYString_H)
#  error Implementation problem! This header should not include DSYString.h/CATUnicodeString.h, this is the responsibility of callers!
# endif
#endif  // DSYStringView_CheckNotIncluded_DSYString

#endif  // DSYStringView_H
