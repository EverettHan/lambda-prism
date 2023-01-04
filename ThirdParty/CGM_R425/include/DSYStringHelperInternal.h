
// Make sure users DO NOT include this header which is implementation detail
#if !defined(DSYStringHelper_INTERNAL_DONT_INCLUDE)
#error This header is an INTERNAL dependency of other non-internal headers.
#endif  // DSYStringHelper_INTERNAL_DONT_INCLUDE

#ifndef DSYStringHelperInternal_H
#define DSYStringHelperInternal_H

#include <cstring>      // std::strchr
#include <string>       // std::char_traits

#include "CATDataType.h"    // CATUC4Bytes...
#include "DSYSysUCAlgorithm.h"

#if defined(_DSY_UTFConverter_INLINE)
#define _DSY_UTFConverter_INLINE_ONLY
#endif

#if defined(_DSY_UTFConverter_INLINE_ONLY) || defined(_DSY_UTFConverter_INLINE_ALLOW)
#include "utfcpp_ext.h"     // utfcppext
#endif


namespace DSY
{
    /**
     * Implementation details.
     * DO NOT USE!
     */
    namespace internal
    {
        template<typename T, int SizeType>
        struct _AlgoStr
        {
            // Generic case
            static size_t Strlen(const T *ipStr)
            {
                const T *p = ipStr;
                while (*p) p++;
                return p - ipStr;
            }
            static const T *Strchr(const T *s, T c, size_t /*sLenghIfKnown*/ = -1)
            {
                while (*s != c)
                    if (!*s++)
                        return 0;
                return s;
            }
        };
        
        template<typename T>
        struct _AlgoStr<T, sizeof(char)>
        {
            // For all integral types sizeof(char) wide! => to catch signed & unsigned char
            static size_t Strlen(const T *ipStr) { 
                return std::strlen(reinterpret_cast<const char*>(ipStr));
            }
            static const T *Strchr(const T *s, T c, size_t /*sLenghIfKnown*/ = -1) {
                return reinterpret_cast<const T *>(
                    std::strchr(reinterpret_cast<const char*>(s), static_cast<char>(c)));
            }
        };
        
        template<typename T>
        struct _AlgoStr<T, sizeof(char16_t)> // NOTE: sizeof(char16_t) >= 2
        {
            // For all integral types sizeof(char16_t) wide!
            static size_t Strlen(const T *ipStr) { 
                return std::char_traits<char16_t>::length(reinterpret_cast<const char16_t*>(ipStr));
            }
            static const T *Strchr(const T *s, T c, size_t sLenghIfKnown = -1) {
                if(-1 == sLenghIfKnown) sLenghIfKnown = Strlen(s);
                return reinterpret_cast<const T *>(
                    std::char_traits<char16_t>::find(reinterpret_cast<const char16_t*>(s), sLenghIfKnown+1, c));
            }
        };
        
        template<typename T>
        struct _AlgoStr<T, sizeof(char32_t)> // NOTE: sizeof(char32_t) >= 4
        {
            // For all integral types sizeof(char32_t) wide!
            static size_t Strlen(const T *ipStr) {
                return std::char_traits<char32_t>::length(reinterpret_cast<const char32_t*>(ipStr));
            }
            static const T *Strchr(const T *s, T c, size_t sLenghIfKnown = -1) {
                if(-1 == sLenghIfKnown) sLenghIfKnown = Strlen(s);
                return reinterpret_cast<const T *>(
                    std::char_traits<char32_t>::find(reinterpret_cast<const char32_t*>(s), sLenghIfKnown+1, c));
            }
        };
        
        template<typename T, typename C = void>
        struct AlgoStr;
        
        template<typename T >
        struct AlgoStr<T, typename std::enable_if<std::is_integral<T>::value>::type > : public _AlgoStr<T, sizeof(T)>
        {
        };
        
        template<typename T>
        inline size_t Strlen(const T *ipStr) {
            static_assert(std::is_integral<T>::value, "Strlen check that type T is integral");
            return internal::AlgoStr<T>::Strlen(ipStr);
        }
        
        // Functionally useless, but keep to maintain good performance in Debug builds
        inline size_t Strlen(const wchar_t *ipStr) { return wcslen(ipStr); }
        
        
        template<int SizeType>
        struct _RawType
        {
        };
        // Optimizations
        template<>
        struct _RawType<sizeof(char)>
        {
            typedef char type;
        };
        template<>
        struct _RawType<sizeof(CATUC2Bytes)>
        {
            typedef CATUC2Bytes type;
        };
        template<>
        struct _RawType<sizeof(CATUC4Bytes)>
        {
            typedef CATUC4Bytes type;
        };
        
        template<typename T, typename C = void>
        struct RawType
        {
            // using T = type;
            // using pointer = type*;
            typedef T type;
            typedef type *pointer;
        };
        
        template<typename T>
        struct RawType<T, typename std::enable_if<std::is_integral<T>::value && sizeof(T) <= 4>::type >
        {
            typedef typename _RawType<sizeof(T)>::type type;
            typedef type *pointer;
        };
        
        template<typename T>
        using RawType_t = typename RawType<T>::type;    // Helper type
        
        
        template<typename TypSrc, typename TypDest, int S1, int S2>
        struct __DSYConvertUTF
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return TypicalLengthRequired(iSrcLength); }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }
            
            // Identity copy
            template <typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                static_assert((S1 == S2) && (S1 == 1 || S1 == 2 || S1 == 4) && (S2 == 1 || S2 == 2 || S2 == 4), "Invalid template parameters. Possible values are pairs of either 1, 2 or 4!");
                return Impl_Do<OutIterator>::Call(dest, ipsz, iLength);
            }
            
        private:
            template <typename OutIterator>
            struct Impl_Do
            {
                static OutIterator Call(OutIterator dest, const TypSrc *ipsz, size_t iLength)
                {

                    // sizeof(TypSrc) == sizeof(TypDest) if this compiles! (cf. static assertion)            
                    for (int k = 0; k < iLength; k++)
                        *dest++ = (TypDest)ipsz[k];
                    return dest;
                }
            };
            
            // Optimized version for raw arrays!
            template <typename T>
            struct Impl_Do<T *>
            {
                static T *Call(T *dest, const TypSrc *ipsz, size_t iLength)
                {            
                    memcpy(dest, ipsz, iLength * sizeof(TypSrc));   // Optimized copy, what about the iterator pattern
                    return dest + iLength;
                }
            };
        };
        
        // template to express output buffer size in characters (max / optimized / min):
        // 1 -> (2,4): len + 1  / (len/2+1,len/4+1)
        // 2 -> 4    : len + 1  / len/2+1
        // (2,4) -> 1: 4*len+1  / May not required more than len+1 (US ASCII), lets try out and realloc if necessary (2*len+1 => 3*len+1 => 4*len+1)
        // 4 -> 2    : 2*len+1  / len + 1
        // Optimized: alloc size for tradeoff between cpu performance and memory consumption
        // if OutOfMem inc n & szAllocChar = (min * n)  // While szAlloc < max, else abort
        // TODO IMPROVEMENT: out iterator that handles memory allocation! iter<TypDest, TypSrc> -> will allow to reduce memory allocated in most cases!
        // or implement an out iterator that counts required size (2 passes, but potential memory savings)
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 1, 2>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength / 2 + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            // Could be useful, but probably at the cost of potential greater code size!
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utfcppext::unchecked::utf8to16_s<OutIterator, const TypSrc *>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                RawType_t<TypDest> *p = DSYSysUCAlgorithm::unchecked::utf8to16(
                        reinterpret_cast<const char *>(ipsz), 
                        reinterpret_cast<const char *>(ipsz + iLength),
                        reinterpret_cast<RawType_t<TypDest> *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 1, 4>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength / 2 + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            // Could be useful, but probably at the cost of potential greater code size!
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utfcppext::unchecked::utf8to32_s<const TypSrc *, OutIterator>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                RawType_t<TypDest> *p = DSYSysUCAlgorithm::unchecked::utf8to32(
                        reinterpret_cast<const char *>(ipsz), 
                        reinterpret_cast<const char *>(ipsz + iLength),
                        reinterpret_cast<RawType_t<TypDest> *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 2, 1>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength * 4 + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            // Could be useful, but probably at the cost of potential greater code size!
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utfcppext::unchecked::utf16to8_s<const TypSrc *, OutIterator>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                char * p = DSYSysUCAlgorithm::unchecked::utf16to8(
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz), 
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz + iLength),
                        reinterpret_cast<char *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 2, 4>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength / 2 + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            // Could be useful, but probably at the cost of potential greater code size!
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utfcppext::unchecked::utf16to32_s<const TypSrc *, OutIterator>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                RawType_t<TypDest> *p = DSYSysUCAlgorithm::unchecked::utf16to32(
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz), 
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz + iLength),
                        reinterpret_cast<RawType_t<TypDest> *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 4, 1>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength * 4 + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utf8::unchecked::utf32to8<OutIterator, const TypSrc *>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                char *p = DSYSysUCAlgorithm::unchecked::utf32to8(
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz), 
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz + iLength),
                        reinterpret_cast<char *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        template<typename TypSrc, typename TypDest>
        struct __DSYConvertUTF<TypSrc, TypDest, 4, 2>
        {
            static size_t MaxLengthRequired(size_t iSrcLength) { return iSrcLength * 2 + 1; }
            static size_t TypicalLengthRequired(size_t iSrcLength) { return iSrcLength + 1; }    // Optimization
            
            #if defined(_DSY_UTFConverter_INLINE_ALLOW)
            // Could be useful, but probably at the cost of potential greater code size!
            template<typename OutIterator>
            static OutIterator Do(OutIterator dest, const TypSrc *ipsz, size_t iLength)
            {
                return utfcppext::unchecked::utf32to16<const TypSrc *, OutIterator>(ipsz, ipsz + iLength, dest);
            }
            #endif  // _DSY_UTFConverter_INLINE_ALLOW
            
            #if !defined(_DSY_UTFConverter_INLINE_ONLY)
            // Code size optimization
            static TypDest *Do(TypDest *dest, const TypSrc *ipsz, size_t iLength) {
                RawType_t<TypDest> *p = DSYSysUCAlgorithm::unchecked::utf32to16(
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz), 
                        reinterpret_cast<const RawType_t<TypSrc> *>(ipsz + iLength),
                        reinterpret_cast<RawType_t<TypDest> *>(dest)
                    );
                return reinterpret_cast<TypDest *>(p);
            }
            #endif  // _DSY_UTFConverter_INLINE_ONLY
        };
        
        
        template <typename TypSrc, typename TypDest>
        struct __UTFConverter
        {
            typedef __DSYConvertUTF<TypSrc, TypDest, sizeof(TypSrc), sizeof(TypDest)> type;
        };
        
        class non_copyable_but_movable
        {
        protected:
            non_copyable_but_movable() = default;
            ~non_copyable_but_movable() = default;

            non_copyable_but_movable(non_copyable_but_movable const &) = delete;
            non_copyable_but_movable& operator=(non_copyable_but_movable const &x) = delete;
            
            non_copyable_but_movable(non_copyable_but_movable &&iRValue) = default;
            non_copyable_but_movable & operator= ( non_copyable_but_movable && ) = default;
        };
        
    }   // namespace internal
}   // namespace DSY

#endif  // DSYStringHelperInternal_H
