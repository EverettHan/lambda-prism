
#ifndef DSYStringHelperSTLFileSystem_H

#if (__cplusplus >= 201703L)    // Requires C++17 support at least

#define DSYStringHelperSTLFileSystem_H  42400

#include <filesystem>           // C++ STL header
#include "DSYString.h"          // CATUnicodeString
#include "DSYStringHelper.h"    // DSY::CUSFrom

/**
 * ++IK8 21:01:11
 * 
 * DSYStringHelperSTLFileSystem.h
 * This header exposes the namespace "DSY::filesystem" which allows for
 * proper interoperability between CATUnicodeString and STL API std::filesystem (std::filesystem::path...):
 *   - Unicode-Safe: no risk of data-loss due to some manual unsafe conversions, such as:
 *     std::filesystem::path myPath { cus.ConvertToChar() };    // Potential data loss due to CATUnicodeString::ConvertToChar
 *   - Efficient: optimized for performance, thanks to the knowledge of CATUnicodeString's memory layout
 * 
 * [Usage]
 * First add the following directive in your cpp file (not in a header file):
 *     using namespace DSY::filesystem;
 * - To build a C++ path object from a CATUnicodeString, use the following function:
 *   STLPathFrom( const CATUnicodeString & iCUS, ...)
 * - Other operations using the path's operators are seamless (concatenation with operators /, /= or +=).
 * - To convert a C++ path to a CATUnicodeString, use the following function:
 *   CUSFrom(std::filesystem::path const & iPath)
 * 
 * ++IK8 21:01:11
 */

namespace DSYSysUCAlgorithm
{
    /** @nodoc Include "DSYSysUCAlgorithm.h" to use this function */
    ExportedByCATSysTS int IsUTF8(const char *&ioStr, size_t iNBytes);
}

namespace DSY
{
  namespace filesystem
  {
    namespace detail    // INTERNAL USE ONLY, subject to change without notice!
    {
        using path_value_type = std::filesystem::path::value_type;
        
        auto const * _getStrPtrForStdPath(const CATUnicodeString & iCUS)
        {            
            // IMPORTANT: std::filesystem::path is expected to convert the input to native filesystem encoding internally
            // So if we have the right data format inside the CATUnicodeString, lets give it to the path constructor
            constexpr bool bIsPathUtf16 = std::is_same_v<path_value_type, wchar_t> && (sizeof(wchar_t) == sizeof(CATUC2Bytes));
            static_assert(bIsPathUtf16 || (!bIsPathUtf16 && std::is_same_v<path_value_type, char>), R"(Unexpected "value_type": code review required!)");
            if constexpr ( bIsPathUtf16 ) {
                // Windows platform, most probably
                return reinterpret_cast<wchar_t const *>(iCUS.ConvertToUCChar());
            
    #if 0   // Temporary? Wait for C++20 char8_t constructor to be available?
                //  1) std::filesystem::u8path does not take a format parameter (The "fmt" parameter would be ignored)
                //  2) What if C++ globale locale is changed to non UTF-8???
            } else if constexpr (sizeof(char16_t) == sizeof(CATUC2Bytes)) {
                return reinterpret_cast<char16_t const *>(iCUS.ConvertToUCChar());
    #endif
            } else {
                // If the source character type is char, the encoding of the source is assumed to be the native narrow encoding
                // => depends on the current global C++ locale, not necessarily UTF-8
                // But ConvertToChar is expected to return UTF-8 encoded data - otherwise wrong configuration
                // Indeed, legacy code pages (# UTF-8) are used only on Windows, platform on which "value_type" is currently wchar_t
                return iCUS.ConvertToChar(); // ConvertToChar is expected to return UTF-8 on all platforms but Windows (for now at least)
                // Validate Unicode support by ODT!
            }
        }   // _getStrPtrForStdPath
        
        template<typename T>
        CATUnicodeString __CUSFrom(const T * ipsz, size_t iLength)
        {
            return DSY::CUSFrom(ipsz, iLength);
        }
        
    }   // namespace detail
      
    
    template<std::filesystem::path::format Fmt = std::filesystem::path::format::native_format>
    [[nodiscard]] inline 
    CATUnicodeString // std::enable_if_t<(Fmt == std::filesystem::path::format::native_format || Fmt == std::filesystem::path::format::generic_format), CATUnicodeString> 
    CUSFrom(std::filesystem::path const & iPath)
    {
        using path_fmt = std::filesystem::path::format;
        
        static_assert((Fmt == path_fmt::native_format) || (Fmt == path_fmt::generic_format), 
            "CUSFrom(std::filesystem::path const &): only native_format & generic_format are supported; auto_format is not allowed!");
        
        // WARNING encoding of refPathStr when "path_value_type" is char.
        const std::filesystem::path::string_type & refPathStr = (Fmt == path_fmt::native_format) ? 
                                                                iPath.native() : iPath.generic_string<detail::path_value_type>();
        // IMPORTANT: refPathStr can be either:
        //  1) a reference to tha path's internal string (native)
        //  2) a reference to a generated temporary (generic_string)
        
        // path_value_type could be char, wchar_t, char16_t, char32_t, char8_t
        if constexpr (std::is_same_v<detail::path_value_type, char>) 
        {
            CATUnicodeString cus;
            // The path's internal string is a char* string, expected to be UTF-8 encoded (Unix OS branch).
            // However, this is not necessarily true, since file names are byte strings with unspecified encoding on Unix/Linux.
            // Thus, the path content MUST be validated, which is done by the path class conversion functions
            char const *path_cstr = refPathStr.c_str();
            if(DSYSysUCAlgorithm::IsUTF8(path_cstr, refPathStr.length()) == 0) 
            #if __cplusplus >= 202002L
                [[likely]] 
            #endif
            {
                cus.BuildFromUTF8(refPathStr.c_str(), refPathStr.length());
            } else {    // The byte string is not valid UTF-8
                // The following implementation forces a conversion that is expected to throw a standard exception in case of encoding problem
                std::wstring const & wstr = (Fmt == path_fmt::native_format) ? iPath.string<wchar_t>() : iPath.generic_string<wchar_t>();
                cus.BuildFromWChar(wstr.data(), wstr.length());
            }
            return cus;
        } 
        else
        {
            // For Windows, "path_value_type" is currently wchar_t
            // Make the call to DSY::CUSFrom dependent on "path_value_type" to avoid build issue 
            // when path_value_type is char (Linux...). Indeed, CUSFrom is deleted for char * input.
            CATUnicodeString cus = detail::__CUSFrom<detail::path_value_type>(refPathStr.c_str(), refPathStr.length());
            return cus;
        }
    }   // CUSFrom( std::filesystem::path const & )


    [[nodiscard]] inline std::filesystem::path STLPathFrom( const CATUnicodeString & iCUS, 
                                std::filesystem::path::format fmt = std::filesystem::path::format::auto_format )
    {        
        // WRONG!!! return std::filesystem::path(iCUS.ConvertToChar()); // Possible data loss!
        return std::filesystem::path(detail::_getStrPtrForStdPath(iCUS), fmt);
    }
    /*
    inline operator std::filesystem::path(const CATUnicodeString & iCUS) {
        return STLPathFrom(iCUS);
    }
    */
    
#if 1
    template<typename T, std::enable_if_t<std::is_base_of_v<std::filesystem::path,std::decay_t<T>>, int> = 0 >
    std::filesystem::path & operator+= (T && path, CATUnicodeString const & eltToAppend)
    {
        // Perfect forwarding, safe to return a reference to the path object? (which may be a temporary)
        return std::forward<T>(path) += detail::_getStrPtrForStdPath(eltToAppend);
    }
#else
    inline std::filesystem::path & operator+= (std::filesystem::path & path, CATUnicodeString const & strToConcat)
    {        
        return path += detail::_getStrPtrForStdPath(strToConcat);
    }
#endif
    
#if 1
    template<typename T, std::enable_if_t<std::is_base_of_v<std::filesystem::path,std::decay_t<T>>, int> = 0 >
    std::filesystem::path & operator/= (T && path, CATUnicodeString const & eltToAppend)
    {
        // Perfect forwarding, safe to return a reference to the path object? (which may be a temporary)
        return std::forward<T>(path) /= detail::_getStrPtrForStdPath(eltToAppend);
    }
#else
    inline std::filesystem::path & operator/= (std::filesystem::path & path, CATUnicodeString const & eltToAppend)
    {        
        return path /= detail::_getStrPtrForStdPath(eltToAppend);
    }
#endif
    
    /**
     * std::filesystem::path operator/( const std::filesystem::path & lhs, CATUnicodeString const & rhs )
     * 
     * Enables safe concatenation of a path component with a CATUnicodeString,
     * using the preferred directory separator if appropriate (see operator/= for details).
     * IMPORTANT: if implemented wrong, this operator can cause ambiguity for right hand side values (rhs) 
     * that are not of types CATUnicodeString/std::filesystem::path, but are auto-convertible to any of them
     * cf. STL operator: std::filesystem::path operator/( const std::filesystem::path& lhs, const std::filesystem::path& rhs );
     * Thus, we make it available only for rhs values of type CATUnicodeString
     */
    template<typename T>
    [[nodiscard]] 
    std::enable_if_t<std::is_base_of_v<CATUnicodeString,T>, std::filesystem::path> 
    // std::filesystem::path
    operator/ ( const std::filesystem::path & lhs, T const & rhs )
    // Causes ambiguity: inline std::filesystem::path operator/ ( const std::filesystem::path & lhs, CATUnicodeString const & rhs )
    {
        return std::filesystem::path(lhs) /= rhs;
        // auto p2 = std::filesystem::path(lhs);
        // return p2 /= rhs;        
    }
    
// #if defined(__DSYStringHelperSTLFileSystem_Concat_LHS_CUS)  // Unsafe? because no way to provide the format...
    // The user could still create a path instance using STLPathFrom to specify that if needed
    template<typename T>
    [[nodiscard]] 
    std::enable_if_t<std::is_base_of_v<CATUnicodeString,T>, std::filesystem::path> 
    operator/ ( T const & lhs, const std::filesystem::path & rhs )
    {
        // Quid of std::filesystem::path::format? => defaults to auto_format, cf. std::filesystem::path constructor
        return STLPathFrom(lhs) /= rhs;
    }
// #endif  // __DSYStringHelperSTLFileSystem_Concat_LHS_CUS
    
  } // namespace DSY::filesystem
  
  // For the sake of homogeneity with other CUSFrom helper functions, 
  // bring DSY::filesystem::CUSFrom( std::filesystem::path const & ) into the DSY namespace
  using DSY::filesystem::CUSFrom;
    
}   // namespace DSY

#endif

#endif  // DSYStringHelperSTLFileSystem_H
