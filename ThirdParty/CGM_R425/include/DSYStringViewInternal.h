
// Make sure users include DSYStringView.h and not this header which is implementation detail
#if !defined(DSYStringView_INTERNAL_DONT_INCLUDE)
#error You must include DSYStringView.h
#endif  // DSYStringView_INTERNAL_DONT_INCLUDE

#ifndef DSYStringViewInternal_H
#define DSYStringViewInternal_H

#include <functional>   // std::reference_wrapper
// #include <cassert>      // assert

#include "CATSysTS.h"           // ExportedByCATSysTS
#include "DSYSysCommon.h"

#define DSYStringHelper_INTERNAL_DONT_INCLUDE
#include "DSYStringHelperInternal.h"    // RawType_t
#undef  DSYStringHelper_INTERNAL_DONT_INCLUDE

#define DSYOptimizedBuffer_INTERNAL_DONT_INCLUDE
#include "DSYOptimizedBuffer.h" // OptimizedBuffer
#undef  DSYOptimizedBuffer_INTERNAL_DONT_INCLUDE

#if ( __cplusplus > 201402L || (defined(_WINDOWS_SOURCE) && (_MSC_VER >= 1916)) )
/** nodoc */
#define __DS_CXX14_SUPPORT_DEDUCED_RETURN_TYPES
#endif

/**
 * @nodoc
 * _DSY_UCS_PREVENT_SUBSTITUTION_FAILURE.
 * Fallback values to avoid substitution failure that would make the compiler 
 * discard a make_view candidate function and fall-back to other signatures.
 * We don't want that because the user might get errors difficult to read.
 * Our goal is to handle erroneous template arguments within the body of the function with static_assert.
 */
#define _DSY_UCS_PREVENT_SUBSTITUTION_FAILURE

/** nodoc */
// #define _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL

/** nodoc */
// _DSY_UCS_MK_VIEW_SUPPORT_SIGN_VARIANTS

/** nodoc For internal System use only!!!
 * DS character type CATUC2Bytes & CATUC4Bytes are not "strong" types of the langage, 
 * but typedefs respectively to uint16_t and uint32_t, general integers for which encoding is not defined, thus ambiguous!
 */
// #define _DSY_UCS_MK_VIEW_SUPPORT_DS_CHAR_TYPES

/** nodoc */
#define _DSY_UCS_MK_VIEW_ERROR_MSG      "make_view arguments compile-time validation failed!"
/** nodoc */
#define _DSY_UCS_RT_VIEW_ERROR_MSG      "returned_view CompileTimeChecks"

class CATUnicodeString;

namespace DSY
{
    namespace UCS   // UniCode Services
    {
    /**
     * Implementation details.
     * DO NOT USE!
     */
    namespace internal
    {
        using DSY::internal::OptimizedBuffer;
        using DSY::internal::RawType_t;
        using DSY::internal::non_copyable_but_movable;
        using DSY::internal::__UTFConverter;
        using DSY::internal::Strlen;
        
        /**
         * string_buffer.
         * Small internal buffer used to optimize conversion of small strings and avoid costly dynamic memory allocation.
         * Since this buffer will be moved, it should be kept small not to loose performance benefits.
         * Size = 32: Max 32 US ASCII characters or 8 UTF-32 characters
         */
        template <typename T>
        using string_buffer = OptimizedBuffer<T, (32 / sizeof(T))>;
        
        /**
         * base_type helper type.
         * remove_pointer + remove_const + remove_volatile
         */
        template <typename T>
        using base_type = typename std::remove_cv<typename std::remove_pointer<typename std::decay<T>::type>::type>::type;
        
        template <typename T>
        using base_raw_type = RawType_t<base_type<T>>;
    
        /**
         * ConvSrc2Dest<TypSrc, TypDest>.
         * This class is designed to ease and optimize conversions of strings between different UTF encodings.
         * It is especially useful to convert between a given UTF encoding and wchar_t, since the encoding of wchar_t strings depends (partly) on sizeof(wchar_t), which varies accross platforms.
         * Note that even if wchar_t strings are not bound to use a UTF encoding, they do in practice on most platforms; UTF-16 on Windows and UTF-32 on most Unix-derived OSes.
         *
         * IMPORTANT: the programmer must ensure that ipsz lives until ConvSrc2Dest is not used anymore!
         * In other words, the input string is not necessarily copied.
         */
        template<class TypSrc, class TypDest, bool IsSizeofMatch>
        class _ConvSrc2Dest : private non_copyable_but_movable
        {
        };

        template<class TypSrc, class TypDest>
        class _ConvSrc2Dest<TypSrc, TypDest, true> : private non_copyable_but_movable
        {
        public:
        
            _ConvSrc2Dest(const TypSrc *ipsz, size_t iLength) noexcept 
                : m_Length(iLength), m_psz(reinterpret_cast<const TypDest *>(ipsz))
            {
                static_assert((sizeof(TypSrc) == sizeof(TypDest)), 
                    "Assertion must be true for implementation to legitimetely avoid a deep copy/conversion of the input string!");
            }
            
            _ConvSrc2Dest(const _ConvSrc2Dest & iOther) : m_Length(iOther.iOther), m_psz(iOther.m_psz) {}
            _ConvSrc2Dest(_ConvSrc2Dest &&) = default;
            _ConvSrc2Dest & operator= ( _ConvSrc2Dest && ) = default;
            
            const TypDest *data() const noexcept { return m_psz; }   // No conversion required!
            
            size_t length() const noexcept { 
                if((size_t)-1 == m_Length)
                    m_Length = m_psz ? Strlen(m_psz) : 0;
                return m_Length;                
            }
            
            TypDest *Detach()
            {
                if(!m_psz)
                    return nullptr;
                
                size_t len = length();                
                TypDest *pBuffer = (TypDest *)malloc((len + 1) * sizeof(TypDest));
                if(pBuffer)
                    memcpy(pBuffer, m_psz, (len + 1) * sizeof(TypDest));
                m_psz = nullptr;
                return pBuffer;
            }
        private:
            /*void ReInit(const TypSrc *ipsz, size_t iLength = (size_t)-1) noexcept
            {
                m_Length = iLength;
                m_psz = reinterpret_cast<const TypDest *>(ipsz);
            }*/
        
            // Members
            mutable size_t m_Length;  // Pointer to data not first member to detect silent bugs when a reference to this object is passed to printf for e.g.
            const TypDest *m_psz;
        };  // _ConvSrc2Dest<TypSrc, TypDest, true>
        
        
        template<class TypSrc, class TypDest>
        class _ConvSrc2Dest<TypSrc, TypDest, false> : private non_copyable_but_movable
        {
        public:            
            _ConvSrc2Dest(const TypSrc *ipsz, size_t iLength) noexcept : m_pSrc(ipsz), m_SrcLength(iLength), m_DstLength(0), m_buffer()
            {
                // ReInit();
            }
            _ConvSrc2Dest(const _ConvSrc2Dest & iOther)
                : m_pSrc(iOther.m_pSrc), m_SrcLength(iOther.m_SrcLength)
                , m_DstLength(iOther.m_DstLength), m_buffer(iOther.m_buffer)
            {
            }
            _ConvSrc2Dest(_ConvSrc2Dest &&) = default;
            _ConvSrc2Dest & operator= ( _ConvSrc2Dest && ) = default;
            
            const TypDest *data() const noexcept;  // Lazy conversion pattern
            size_t length() const noexcept;
            
            TypDest *Detach() { return m_buffer.Detach(); }
            
        private:
            const TypDest * ReInit() const noexcept
            {
                if(!m_pSrc)
                    return nullptr;
                if((size_t)-1 == m_SrcLength)
                    m_SrcLength = Strlen(m_pSrc);
                
                TypDest *l_pBuffer = m_buffer.reset(__UTFConverter<TypSrc, TypDest>::type::MaxLengthRequired(m_SrcLength));
                TypDest *pCharAfterLast = __UTFConverter<TypSrc, TypDest>::type::Do(l_pBuffer, m_pSrc, m_SrcLength);
                *pCharAfterLast = '\0';
                m_DstLength = (pCharAfterLast - l_pBuffer);
                return l_pBuffer;
            }
            
            // Members
            // Pointer to data not first member to detect silent bugs when a reference to this object is passed to printf for e.g.
            const TypSrc *m_pSrc;
            mutable size_t m_SrcLength;
            mutable size_t m_DstLength;
            mutable string_buffer<TypDest> m_buffer;
        };  // _ConvSrc2Dest<TypSrc, TypDest, false>
        
        template<class TypSrc, class TypDest>
        inline const TypDest * _ConvSrc2Dest<TypSrc, TypDest, false>::data() const noexcept
        {
            // Lazy conversion pattern
            const auto * p = m_buffer.data();    // If the pointer is not null, then the conversion has been performed
            if(!p)
            {
                p = ReInit();
            }
            return p;
        }
        
        template<class TypSrc, class TypDest>
        inline size_t _ConvSrc2Dest<TypSrc, TypDest, false>::length() const noexcept
        {
            data(); // Ensure data
            return m_DstLength;
        }
        
        // template<typename TypSrc, typename TypDest, typename Enable = void>
        // class ConvSrc2Dest
        // {
        // };
        
        template<class TypSrc, class CharType>
        // class ConvSrc2Dest<TypSrc *, CharType, typename std::enable_if<std::is_integral<TypSrc>::value>::type> // TODO match with pointer Do not found!
        class ConvSrc2Dest
            // Use private inheritance here make sure we handle what method is actually exposed
            : private internal::_ConvSrc2Dest<TypSrc, CharType, sizeof(TypSrc) == sizeof(CharType)>
        {
            typedef  internal::_ConvSrc2Dest<TypSrc, CharType, sizeof(TypSrc) == sizeof(CharType)> ConvSrc2DestBase;
        protected:
            typedef const TypSrc * typeCtor;
        public:
            
            ConvSrc2Dest() = delete;
            ConvSrc2Dest(typeCtor ipsz, size_t iLength = (size_t)-1) noexcept 
                : ConvSrc2DestBase(ipsz, iLength)
            {
                // Maintenance: make sure the behavior is well-defined if the input pointer is null! (=> not supported)
            }
            ConvSrc2Dest(ConvSrc2Dest &&iRValue) : ConvSrc2DestBase(std::forward<ConvSrc2DestBase>(iRValue))
            {
            }
            ConvSrc2Dest & operator= ( ConvSrc2Dest && ) = default;
            
            const CharType *data() const noexcept { return ConvSrc2DestBase::data(); }
            size_t length() const noexcept { return ConvSrc2DestBase::length(); }
            
            // TODO IMPROVEMENT: allocate a buffer if necessary, not implemented yet!
            // CharType *data() { return nullptr; }
            // CharType *Detach() get ownership of the buffer holding converted data + set m_psz to nullptr
        };
        
        
        /**
         * @nodoc
         * _GetStringAs.
         */
        ExportedByCATSysTS void _GetStringAs(const char *&opDest, unsigned int &oLength, const CATUnicodeString &iStr, string_buffer<char> &iBuffer);
        ExportedByCATSysTS void _GetStringAs(const CATUC4Bytes *&opDest, unsigned int &oLength, const CATUnicodeString &iStr, string_buffer<CATUC4Bytes> &iBuffer);  
        ExportedByCATSysTS void _GetStringAs(const CATUC2Bytes *&opDest, unsigned int &oLength, const CATUnicodeString &iStr, string_buffer<CATUC2Bytes> &iBuffer);
        
        /**
         * @nodoc
         * Wrapper class for C++11 range-based for loop.
         * Use typedefs StrAsUTFX[UnSafe].
         */
        template<class CharType>
        // template<typename CharType = DSYStringIterSafe>
        // class CxxStrWrapper
        class ConvSrc2Dest<CATUnicodeString, CharType> : private non_copyable_but_movable
        {
            // Do not copy the string, it is the responsibility of the caller to make sure it stays alive while this object is alive
            // => Make the caller responsible, if we don't now, there would be no way to go back in the future without breaking compatibility
            // OLD CODE BEGIN
            // typename StringIterStruct::strType str;
            // DSYStringIterSafe::strType str;
            // CATUnicodeString str;
            // OLD CODE END
            std::reference_wrapper<const CATUnicodeString> str;  // Reference for PCS + Make callers manage lifecycle to avoid propagation of bogus client code
            // Pointer to data not first member to detect silent bugs when a reference to this object is passed to printf for e.g.
            mutable const CharType *m_psz;
            mutable unsigned int    m_DstLength;
            mutable string_buffer<RawType_t<CharType>> m_buffer;   // _GetStringAs: use of RawType avoids problems with wchar_t + limit the number of signatures to export
        protected:
            typedef const CATUnicodeString & typeCtor;
        public:
        
            ConvSrc2Dest(typeCtor iStr);
            // Disallow object temporaries BEGIN (R-Values)
            // Mandatory to avoid invalid memory access due to lazy conversions
            ConvSrc2Dest(CATUnicodeString && iStr) = delete;
            ConvSrc2Dest(const CATUnicodeString && iStr) = delete;
            // Disallow object temporaries END
            
            ConvSrc2Dest(ConvSrc2Dest &&iOther) = default;
            ConvSrc2Dest & operator= ( ConvSrc2Dest && ) = default;
            ~ConvSrc2Dest();
            
            const CharType *data() const noexcept;
            size_t length() const noexcept;
        };
        
        template<typename CharType>
        inline ConvSrc2Dest<CATUnicodeString, CharType>::ConvSrc2Dest(const CATUnicodeString &iStr)
            : str(iStr), m_psz(nullptr), m_DstLength(0), m_buffer()
        {
        }
        
        template<typename CharType>
        inline ConvSrc2Dest<CATUnicodeString, CharType>::~ConvSrc2Dest()
        {
        }
        
        template<typename CharType>
        inline const CharType *ConvSrc2Dest<CATUnicodeString, CharType>::data() const noexcept
        {
            // Lazy initialization
            if(!m_psz)
                _GetStringAs(reinterpret_cast<const RawType_t<CharType> *&>(m_psz), m_DstLength, str, m_buffer);
            return m_psz;
        }
        
        template<class CharType>
        inline size_t ConvSrc2Dest<CATUnicodeString, CharType>::length() const noexcept
        {
            data(); // Ensure data
            return m_DstLength;
        }
        
        
#if defined(_DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL)
        template<class CharType>
        class ConvSrc2Dest<std::wstring, CharType> : private ConvSrc2Dest<wchar_t, CharType>
        {
        public:
            // Forward the job
            ConvSrc2Dest(const std::wstring & iStr) : ConvSrc2Dest<wchar_t, CharType>(iStr.data(), iStr.length())
            {
            }
            // Disallow object temporaries (R-Values) because we operate on iStr's inner data, 
            // which implies that iStr stays alive while this object is alive
            ConvSrc2Dest(std::wstring && iStr) = delete;
            ConvSrc2Dest(const std::wstring && iStr) = delete;
            
            ConvSrc2Dest(ConvSrc2Dest &&iOther) = default;
            ConvSrc2Dest & operator= ( ConvSrc2Dest && ) = default;
            ~ConvSrc2Dest() = default;
            
            using ConvSrc2Dest<wchar_t, CharType>::data;
            using ConvSrc2Dest<wchar_t, CharType>::length;
            // using ConvSrc2Dest<wchar_t, CharType>::operator const CharType *;
        };
        
        template<class CharType>
        class ConvSrc2Dest<std::string, CharType> : private ConvSrc2Dest<char, CharType>
        {
        public:
            // Forward the job
            ConvSrc2Dest(const std::string & iStr) : ConvSrc2Dest<char, CharType>(iStr.data(), iStr.length())
            {
            }
            // Disallow object temporaries (R-Values) because we operate on iStr's inner data, 
            // which implies that iStr stays alive while this object is alive
            ConvSrc2Dest(std::string && iStr) = delete;
            ConvSrc2Dest(const std::string && iStr) = delete;
            
            ConvSrc2Dest(ConvSrc2Dest &&iOther) = default;
            ConvSrc2Dest & operator= ( ConvSrc2Dest && ) = default;
            ~ConvSrc2Dest() = default;
            
            using ConvSrc2Dest<char, CharType>::data;
            using ConvSrc2Dest<char, CharType>::length;
            // using ConvSrc2Dest<char, CharType>::operator const CharType *;
        };
#endif  // _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL        
        
        
        ExportedByCATSysTS const char * _GetStringAs(const char *iStr, size_t &ioStrLength, string_buffer<char> &iBuffer);
        ExportedByCATSysTS const CATUC4Bytes * _GetStringAs(const char *iStr, size_t &ioStrLength, string_buffer<CATUC4Bytes> &iBuffer);
        ExportedByCATSysTS const CATUC2Bytes * _GetStringAs(const char *iStr, size_t &ioStrLength, string_buffer<CATUC2Bytes> &iBuffer);
        
        template<class CharType>
        class ConvCharEnv2Dest : private non_copyable_but_movable
        {
        public:
            
            ConvCharEnv2Dest(const char *iStr, size_t iLength = (size_t)-1);
#if defined(_DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL)
            // std::string support BEGIN
            ConvCharEnv2Dest(const std::string & iStr) : ConvCharEnv2Dest(iStr.data(), iStr.length()) {}
            // Disallow object temporaries (R-Values) because we operate on iStr's inner data, 
            // which implies that iStr stays alive while this object is alive
            ConvCharEnv2Dest(std::string && iStr) = delete;
            ConvCharEnv2Dest(const std::string && iStr) = delete;
            // std::string support END
#endif  // _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL
            
            ConvCharEnv2Dest(ConvCharEnv2Dest &&iOther) = default;
            ConvCharEnv2Dest & operator= ( ConvCharEnv2Dest && ) = default;
            ~ConvCharEnv2Dest() = default;
            
            const CharType *data() const noexcept;
            size_t length() const noexcept;
        
        private:
            
            const char * m_pSrc;
            mutable size_t m_SrcLength;
            mutable size_t m_DstLength;
            mutable string_buffer<RawType_t<CharType>> m_buffer;   // _GetStringAs: use of RawType avoids problems with wchar_t + limit the number of signatures to export
        };  // ConvCharEnv2Dest
        
        template<class CharType>
        inline ConvCharEnv2Dest<CharType>::ConvCharEnv2Dest(const char *iStr, size_t iLength)
            : m_pSrc(iStr), m_SrcLength(iLength), m_DstLength(0), m_buffer()
        {
            // Maintenance: make sure the behavior is well-defined if the input pointer is null! (=> not supported)
        }
        
        template<class CharType>
        inline const CharType * ConvCharEnv2Dest<CharType>::data() const noexcept
        {
            // Lazy conversion pattern
            const auto * p = m_buffer.data();    // If the pointer is not null, then the conversion has been performed
            if(!p && m_pSrc)
            {
                if((size_t)-1 == m_SrcLength)
                    m_SrcLength = strlen(m_pSrc);
                size_t ioStrLength = m_SrcLength;
                p = _GetStringAs(m_pSrc, ioStrLength, m_buffer);
                m_DstLength = ioStrLength;
            }
            return reinterpret_cast<const CharType *>(p);
        }
        
        template<class CharType>
        inline size_t ConvCharEnv2Dest<CharType>::length() const noexcept
        {
            data(); // Ensure data
            return m_DstLength;
        }
        
        
        /**
         * make_view_encoding_known.
         * "Raw" types supported which have a specified unambiguous encoding.
         */
        template <typename T>
        constexpr bool make_view_encoding_known()
        {
            if(!std::is_integral<T>::value && sizeof(T) > 4)
                return false;   // Not a "raw" type, handled separately
            constexpr bool value = std::is_same<T, char16_t>::value  // Unicode UTF-16
                                       || std::is_same<T, char32_t>::value  // Unicode UTF-32
                                       || std::is_same<T, wchar_t >::value  // Implementation/Platform defined, but unambiguous
                                       // --IK8 19:10:07 
                                    #if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
                                       || std::is_same<T, char8_t>::value  // Unicode UTF-8
                                    #endif
                                    #if defined(_DSY_UCS_MK_VIEW_SUPPORT_DS_CHAR_TYPES)
                                       // DO NOT support CATUC2Bytes & CATUC4Bytes because they are not strong types of the langage (but typedefs respectively to uint16_t and uint32_t)
                                       // for which encoding is not defined, thus ambiguous!
                                       || std::is_same<T, CATUC2Bytes>::value
                                       || std::is_same<T, CATUC4Bytes>::value
                                    #endif  // _DSY_UCS_MK_VIEW_SUPPORT_DS_CHAR_TYPES
                                       // --IK8 19:10:07
                                       ;
            return value;
        };
        
        template <typename TSrc>
        struct make_view_is_char_based
        {
            // Control list of supported source types to avoid problematic unexpected usages (cf. maintenance)
            // char * strings or wrapper classes (such as std::string)
            static constexpr bool value = std::is_same<TSrc, char>::value
#if defined(_DSY_UCS_MK_VIEW_SUPPORT_SIGN_VARIANTS)
                || std::is_same<TSrc, unsigned char>::value || std::is_same<TSrc, signed char>::value
#endif  // _DSY_UCS_MK_VIEW_SUPPORT_SIGN_VARIANTS
#if defined(_DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL)
                || std::is_same<TSrc, std::string>::value
#endif  // _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL
                ;
        };
        
        /**
         * make_view_encoding_ambiguous.
         * Types for which encoding is considered ambiguous, but that we support if encoding info is provided explicitly by the user.
         */
        template <typename T>
        constexpr bool make_view_encoding_ambiguous()
        {
            if(!std::is_integral<T>::value && sizeof(T) > 4)
                return false;   // Not a "raw" type, handled separately
            constexpr bool value = make_view_is_char_based<T>::value;    // || ...
            return value;
        };
        
        template <typename TDest>
        struct make_view_supported_dst_type
        {
            static constexpr bool value = make_view_encoding_known<TDest>()
                                       || make_view_encoding_ambiguous<TDest>();
        };
        
        template <typename TSrc>
        constexpr bool make_view_supported_src_type()
        {
            using decayedTyp = typename std::decay<TSrc>::type;
            using baseTyp = base_type<decayedTyp>;  // remove_pointer + remove_const + remove_volatile
            
            constexpr bool bIsRawString = (std::is_pointer<decayedTyp>::value && std::is_integral<baseTyp>::value && sizeof(baseTyp) <= 4);
            // If TSrc is not a pointer to a "raw" string, it is probably an object (CATUnicodeString...)
            // In this case, do not allow temporaries (rvalues &&), because for optimization purposes, make_view::data can return a pointer to 
            // the instance's internal data, which must stay alive!
            // make_view could move the temporary object in a member variable in this particular case, but lets keep the behavior homogeneous for 
            // maintenance purposes (small limitation).
            static_assert(bIsRawString || !std::is_rvalue_reference<TSrc>::value, 
                "Input must be a named variable! Temporaries are not supported!");
            
            // Control list of supported source types to avoid problematic unexpected usages (cf. maintenance)
            constexpr bool value = //make_view_supported_dst_type<TSrc>::value // same as output + objects
                                   // bIsRawString  // "Raw types" case (--IK8 19:10:07: test not restrictive enough!)
                                   // ++IK8 19:10:07: enforce well-defined list of supported types!
                                   make_view_encoding_known<baseTyp>() || make_view_encoding_ambiguous<baseTyp>()
                                   // ++IK8 19:10:07
                                   // Also support some specific object types as input which we do not support as output
                                || std::is_same<baseTyp, CATUnicodeString>::value
#if defined(_DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL)
                                || std::is_same<baseTyp, std::string>::value
                                || std::is_same<baseTyp, std::wstring>::value
#endif  // _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL
                                ;
            return value;
        };
        
        
        
        
        struct From {};
        struct To {};
        
        
        enum class MultiByteEncoding
        {
            ANSI,
            UTF8
        };
        
        template<MultiByteEncoding enc>
        struct FromMBCS { 
            using type = From;
            static constexpr MultiByteEncoding value = enc;
        };

        template<MultiByteEncoding enc>
        struct ToMBCS { 
            using type = To;
            static constexpr MultiByteEncoding value = enc;
        };
        
        using FromUTF8 = FromMBCS<MultiByteEncoding::UTF8>;
        using ToUTF8   = ToMBCS  <MultiByteEncoding::UTF8>;
        using FromANSI = FromMBCS<MultiByteEncoding::ANSI>; // Potentially Non-Unicode source
        // WARNING: ToANSI experimental! dangerous to expose because target encoding is potentially not Unicode, hence risk of data loss
        using ToANSI   = ToMBCS  <MultiByteEncoding::ANSI>;
        
        template <typename Encoding>
        struct make_view_supported_encoding
        {
            static constexpr bool value = std::is_same<Encoding, FromUTF8>::value || 
                                        std::is_same<Encoding, ToUTF8>::value ||
                                        std::is_same<Encoding, FromANSI>::value;
        };
        
        /* Example only begin */
        enum class Encoding16
        {
            UCS2,
            UTF16
        };
        
        template<Encoding16 enc>
        struct FromVariableEncoding16 { 
            using type = From;
            static constexpr Encoding16 value = enc;
        };

        template<Encoding16 enc>
        struct ToVariableEncoding16 { 
            using type = To;
            static constexpr Encoding16 value = enc;
        };
        /* Example only end */
        
        template <typename CharTyp>
        struct EncodingForRawType
        {
            using type = void;  // Default 
        };
        template <>
        struct EncodingForRawType<char> 
        {
            using type = MultiByteEncoding;
        };
        template <>
        struct EncodingForRawType<CATUC2Bytes> 
        {
            using type = Encoding16;
        };
        template <typename CharTyp>
        using EncodingForRawType_t = typename EncodingForRawType<CharTyp>::type;
        
        
        /**
         * make_view_encoding_match.
         * T = either source or destination type
         * ExpectedEncWay = From/To depending on value of T
         */
        template <typename Encoding, typename T, typename ExpectedEncWay>
        struct make_view_encoding_match // TODO std::string, std::wstring... cf. _DSY_UCS_STD_STRING_SUPPORT_EXPERIMENTAL
        {
            static constexpr bool value = make_view_encoding_ambiguous<base_type<T>>()    // if false, encoding parameter is not relevant for T
                                          // Check that encoding way is valid (From/To)
                                          && std::is_same<typename Encoding::type, ExpectedEncWay>::value
                                          // Check that encoding type is valid (MBCS for e.g.)
                                          && std::is_same<EncodingForRawType_t<base_raw_type<T>>, 
                                                typename std::decay<decltype(Encoding::value)>::type>::value;
        };
        
        
        template<typename T1, typename T2, typename T1Type, typename T2Type>
        struct _PairFromTo 
#if !defined(_DSY_UCS_PREVENT_SUBSTITUTION_FAILURE)
        {
            static constexpr bool hasType = false;
        }
#else
        {
            using TypeFrom = void;
            using TypeTo   = TypeFrom;
        }
#endif
        ;
        
        template<typename T1, typename T2>
        struct _PairFromTo<T1, T2, From, To>
        {
#if !defined(_DSY_UCS_PREVENT_SUBSTITUTION_FAILURE)
            static constexpr bool hasType = true;
#endif
            using TypeFrom = T1;
            using TypeTo = T2;
        };

        template<typename T1, typename T2>
        struct _PairFromTo<T2, T1, To, From>
        {
#if !defined(_DSY_UCS_PREVENT_SUBSTITUTION_FAILURE)
            static constexpr bool hasType = true;
#endif
            using TypeFrom = T1;
            using TypeTo = T2;
        };


        template<typename T1, typename T2>
        struct PairFromTo : _PairFromTo<T1, T2, typename T1::type, typename T2::type>
        { };
        
        
        /**
         * view_empty.
         * Dummy view to return when template arguments are not valid.
         * Errors will be handled by static_assert in make_view bodies, but some compilers, 
         * such as MSVC, seem to care first about the nature of the object returned, thus
         * potentially bypass the static_assert by some other hard to understand error...
         */
        /* Replaced by static_assert
        template<typename TypDest>
        struct view_empty : private non_copyable_but_movable {
            // Error handling. It seems that we have to at least declare members to make sure 
            // the compiler focuses on make_view body (MSVC).
            const TypDest *data() const;
            size_t length() const;
        };   // Default view
        */
        
        
        template<typename TSrc, typename TDst>
        constexpr bool CompileTimeChecks()
        {
            // iStr may be a pointer/array type, a reference to a string object (CATUnicodeString)...
            // hence the need to forward it to the ConvSrc2Dest template
            
            constexpr bool bIsSrcEncAmbiguous = make_view_encoding_ambiguous<base_type<TSrc>>();
            constexpr bool bIsDstEncAmbiguous = make_view_encoding_ambiguous<base_type<TDst>>();
            static_assert(!( bIsSrcEncAmbiguous && !bIsDstEncAmbiguous),
                R"~(Source encoding is ambiguous, you need to specify it. Ex: make_view<wchar_t,FromUTF8>("strUTF8"))~");
            static_assert(!(!bIsSrcEncAmbiguous &&  bIsDstEncAmbiguous),
                R"~(Destination encoding is ambiguous, you need to specify it. Ex: make_view<char,ToUTF8>(L"wstr"))~");
            static_assert(!( bIsSrcEncAmbiguous &&  bIsDstEncAmbiguous), 
                R"~(Both source & destination encoding are ambiguous, you need to specify them. Ex: make_view<char,FromANSI, ToUTF8>("strANSI"))~");
            
            // Suppress the following asserts if type char because char is supported, but not by this signature
            // (|| bIsDstEncAmbiguous... TODO really Useful???)
            static_assert( make_view_supported_dst_type<TDst>::value || bIsDstEncAmbiguous, "Destination type is not supported!");
            static_assert( make_view_supported_src_type<TSrc>() || bIsSrcEncAmbiguous, "Source type is not supported!");
            
            // ++IK8 19:10:04 Check there is actually something to convert:
            using srcBaseTyp = base_type<typename std::decay<TSrc>::type>;
            static_assert(!std::is_same<TDst, srcBaseTyp>::value, "Nothing to convert! Same source and destination!");
            // ++IK8 19:10:04
            
            return !bIsSrcEncAmbiguous && !bIsDstEncAmbiguous;
        }   // CompileTimeChecks<TSrc, TDst>
        
        template<typename TSrc, typename TDst, typename Encoding>
        constexpr bool CompileTimeChecks()
        {
            // Encoding: for either source (TSrc) of destination (TDst)
            
            // Check validity of Source and Destination types
            static_assert( make_view_supported_dst_type<TDst>::value, "Destination type not supported!");
            static_assert( make_view_supported_src_type<TSrc>(), "Source type not supported!");
            
            // Check that the right signature of make_view is being used (according to TSrc & TDst)
            constexpr bool bIsSrcEncAmbiguous = make_view_encoding_ambiguous<base_type<TSrc>>();
            constexpr bool bIsDstEncAmbiguous = make_view_encoding_ambiguous<base_type<TDst>>();
            static_assert((bIsSrcEncAmbiguous ^ bIsDstEncAmbiguous), 
                R"~(Given the source & destination types, either 0 or 2 "Encoding" template arguments should be provided!)~");
            
            // Exposed API, be restrictive on input types!
            static_assert(make_view_supported_encoding<Encoding>::value, 
                "Template 2nd argument is not supported. You must use one of the documented types.");
            
            // Check validity of encoding parameter            
            constexpr bool bEncodingMatchSrc = make_view_encoding_match<Encoding, base_type<TSrc>, From>::value;
            constexpr bool bEncodingMatchDst = make_view_encoding_match<Encoding, base_type<TDst>, To>::value;
            static_assert(bEncodingMatchSrc || bEncodingMatchDst, "Template 2nd argument is not valid. You probably mixed From/To types...");
            
            // ++IK8 19:10:04 Check there is actually something to convert:
            // Nothing to do in this case, clearly, TSrc & TDst are different because Encoding has been specified for only one of them!
            
            return (bIsSrcEncAmbiguous ^ bIsDstEncAmbiguous);
        }   // CompileTimeChecks<TSrc, TDst, Encoding>
        
        template<typename TSrc, typename TDst, typename Encoding1, typename Encoding2>
        constexpr bool CompileTimeChecks()
        {
            // Check validity of Source and Destination types
            static_assert( make_view_supported_dst_type<TDst>::value, "Destination type not supported!");
            static_assert( make_view_supported_src_type<TSrc>(), "Source type not supported!");
            
            // Check that the right signature of make_view is being used (according to TSrc & TDst)
            constexpr bool bIsSrcEncAmbiguous = make_view_encoding_ambiguous<base_type<TSrc>>();
            constexpr bool bIsDstEncAmbiguous = make_view_encoding_ambiguous<base_type<TDst>>();
            static_assert((bIsSrcEncAmbiguous && bIsDstEncAmbiguous), 
                R"~(Given the source & destination types, either 0 or 1 "Encoding" template arguments should be provided!)~");
            
            // Exposed API, be restrictive on input types!
            static_assert(make_view_supported_encoding<Encoding1>::value, 
                "Template 2nd argument is not supported. You must use one of the documented types.");
            static_assert(make_view_supported_encoding<Encoding2>::value, 
                "Template 3rd argument is not supported. You must use one of the documented types.");            
            
            // Check validity of encoding parameters before using PairFromTo
            constexpr bool bEncodingMatchSrc = make_view_encoding_match<Encoding1, base_type<TSrc>, From>::value
                ^ make_view_encoding_match<Encoding2, base_type<TSrc>, From>::value;
            constexpr bool bEncodingMatchDst = make_view_encoding_match<Encoding1, base_type<TDst>, To>::value
                ^ make_view_encoding_match<Encoding2, base_type<TDst>, To>::value;
            static_assert(bEncodingMatchSrc, "Template 2nd argument is not valid. You probably mixed From/To types...");
            static_assert(bEncodingMatchDst, "Template 3rd argument is not valid. You probably mixed From/To types...");
            
            // ++IK8 19:10:04 Check there is actually something to convert: 
            // if values of Encoding1 & Encoding2 are of the same type, we must check that they are different
            constexpr bool bEncodingSameValueType = std::is_same<typename std::decay<decltype(Encoding1::value)>::type, 
                                                                 typename std::decay<decltype(Encoding2::value)>::type>::value;
            using srcBaseTyp = base_type<typename std::decay<TSrc>::type>;
            constexpr bool bIsSrcDstDifferent = !std::is_same<TDst, srcBaseTyp>::value; // To support cast signed/unsigned
            static_assert((bEncodingSameValueType && Encoding1::value != Encoding2::value) || !bEncodingSameValueType || bIsSrcDstDifferent, 
                            "Nothing to convert! Same source and destination encodings!");
            
            // Even if TSrc & TDst are considered equivalent, we know by now that we have some work to do
            // because Encoding1 != Encoding2
            // ++IK8 19:10:04
            
            return (bIsSrcEncAmbiguous && bIsDstEncAmbiguous);
        }   // CompileTimeChecks<TSrc, TDst, Encoding1, Encoding2>
        
        
        /**
         * returned_view.
         * Requires EncodingParams [0-2] to be ordered the following way: [EncodingSrc] [EncodingDest]
         */
        template<typename TSrc, typename TDst, typename... EncodingParams>
        // static_assert(false, R"~(Unknown "Encoding" template parameter!)~");
        struct returned_view 
#if defined(_DSY_UCS_PREVENT_SUBSTITUTION_FAILURE)
        {
            // Void is not good enough, MSVC outputs an error that void
            // cannot be assigned to the target variable. => Dummy view_empty
            // TODO choose between view_empty or static_assert...
            // using type = view_empty<TDst>;
            static_assert(CompileTimeChecks<TSrc, TDst, EncodingParams...>(), _DSY_UCS_RT_VIEW_ERROR_MSG);
        }
#endif
        ;
        
        template<typename TSrc, typename TDst>
        struct returned_view<TSrc, TDst>
        {
            using type = ConvSrc2Dest<base_type<TSrc>, TDst>;
        };
        
        template<typename TSrc, typename TDst>
        struct returned_view<TSrc, TDst, FromUTF8>
        {
            using type = ConvSrc2Dest<base_type<TSrc>, TDst>;
        };
        
        template<typename TSrc, typename TDst>
        struct returned_view<TSrc, TDst, ToUTF8>
        {
            using type = ConvSrc2Dest<base_type<TSrc>, TDst>;
        };
        
        template<typename TSrc, typename TDst>
        struct returned_view<TSrc, TDst, FromANSI>
        {
            using type = ConvCharEnv2Dest<TDst>;
        };
        
        
        
#if !defined(_DSY_UCS_REORDER_INVALID)
        template<typename TSrc, typename TDst, typename Encoding1, typename Encoding2>
        struct _returned_view
#if defined(_DSY_UCS_PREVENT_SUBSTITUTION_FAILURE)
        {
            // Void is not good enough, MSVC outputs an error that void
            // cannot be assigned to the target variable. => Dummy view_empty
            // using type = view_empty<TDst>;
            static_assert(CompileTimeChecks<TSrc, TDst, Encoding1, Encoding2>(), _DSY_UCS_RT_VIEW_ERROR_MSG);
        }
#endif
        ;
        
        template<typename TSrc, typename TDst>
        struct _returned_view<TSrc, TDst, FromANSI, ToUTF8>
        {
            using type = ConvCharEnv2Dest<TDst>;
        };
        
#if defined(_DSY_UCS_MK_VIEW_SUPPORT_SIGN_VARIANTS)
        template<typename TSrc, typename TDst>
        struct _returned_view<TSrc, TDst, FromUTF8, ToUTF8> // For signed/unsigned support "casts"
        {
            using type = ConvSrc2Dest<base_type<TSrc>, TDst>;
        };
#endif  // _DSY_UCS_MK_VIEW_SUPPORT_SIGN_VARIANTS
        
        template<typename TSrc, typename TDst, typename Encoding1, typename Encoding2>
        struct returned_view<TSrc, TDst, Encoding1, Encoding2>
            : _returned_view<TSrc, TDst, typename PairFromTo<Encoding1, Encoding2>::TypeFrom, 
                                         typename PairFromTo<Encoding1, Encoding2>::TypeTo>
        {
        };
        
#else   // _DSY_UCS_REORDER_INVALID
        
        template<typename TSrc, typename TDst>
        struct returned_view<TSrc, TDst, FromANSI, ToUTF8>
        {
            using type = ConvCharEnv2Dest<TDst>;
        };
#endif  // _DSY_UCS_REORDER_INVALID
        
        template<typename TSrc, typename TDst, typename... EncodingParams>
        using _returned_view_t = typename returned_view<TSrc, TDst, EncodingParams...>::type;
        
        /**
         * returned_view_t.
         * The goal of this type is to create a different return type for every combination of input template parameters,
         * even if the "real" parent type is sometimes the same.
         * IMPORTANT: maintenance concern to avoid unexpected type compatibility to be exploited by client code...
         * => Hide the different opaque view types behind returned_view_t.
         * Multiplication of types should not be a concern since the class is just a wrapper with no code.
         */
        template<typename TSrc, typename TDst, typename... EncodingParams>
        struct returned_view_t : private _returned_view_t<TSrc, TDst, EncodingParams...>
        {
		private:
			using BaseClass = _returned_view_t<TSrc, TDst, EncodingParams...>;
		public:
            static_assert(CompileTimeChecks<TSrc, TDst, EncodingParams...>(), _DSY_UCS_RT_VIEW_ERROR_MSG);
            
#if defined(_DSY_UCS_RT_VIEW_ALLOW_TEMPORARIES)
            // Provided only for compatibility with existing code in SystemXXX frameworks
            // Unsafe, to be removed!
            const TDst *data() const noexcept { return BaseClass::data(); }
            size_t length() const noexcept { return BaseClass::length(); }
            // No using, rather explicit the exposed signature right here!
            // using _returned_view_t<TSrc, TDst, EncodingParams...>::data;
            // using _returned_view_t<TSrc, TDst, EncodingParams...>::length;
#else   // _DSY_UCS_RT_VIEW_ALLOW_TEMPORARIES
            // The member function "data" returns a pointer to memory managed internally by the object
            // So it is dangerous to allow it to be called on a temporary object (about to die)
            // Ex: 
            // 1)
            // const TDst *p = returned_view_t<...>().data();   // Dangerous call on a temporary object, should not compile!
            // auto c = p[0];   // Free Memory Read!
            // 2) However, this would be legit:
            // F(returned_view_t<...>().data());
            // But to avoid programming errors, disallow anyway!
            const TDst *data() const & noexcept { return BaseClass::data(); }
            const TDst *data() const && = delete;
            size_t length() const & noexcept { return BaseClass::length(); }
            size_t length() const && = delete;
#endif  // _DSY_UCS_RT_VIEW_ALLOW_TEMPORARIES
            
            using _returned_view_t<TSrc, TDst, EncodingParams...>::_returned_view_t;
            
            // DO NOT allow implicit cast operator which is dangerous => use data member function
            operator const TDst *() const = delete;
        };
        
        
        
        /**
         * _make_view.
         * Hidden implementation of make_view.
         * Supporting variadic number of arguments to allow passing string input length. 
         * IMPORTANT: variadic argument support is reserved for internal use (cf. DSYStringHelperPrivate.h)
         *            Mainly because it exposes complexity and also because it is dangerous to rely on length supplied by the caller.
         */
        template<typename TDst, typename TSrc, typename ... Args>   // C++11 parameter packs that accepts zero or more template arguments
        inline returned_view_t<TSrc, TDst> _make_view(TSrc&& iStr, Args&& ... iArgs)  // TSrc&& can bind an lvalue or an rvalue 
        {
            static_assert(CompileTimeChecks<TSrc&&, TDst>(), _DSY_UCS_MK_VIEW_ERROR_MSG);
            
            // std::forward for perfect forwarding
            return returned_view_t<TSrc, TDst>(std::forward<TSrc>(iStr), std::forward<Args>(iArgs) ...);
        }   // _make_view with no Encoding parameter
        
        
        // For special case of char * strings (and wrapper classes) for which encoding is ambiguous (such as std::string)
        template<typename TDst, typename Encoding, typename TSrc, typename ... Args>    // C++11 parameter packs that accepts zero or more template arguments
        inline returned_view_t<TSrc, TDst, Encoding> _make_view(TSrc&& iStr, Args&& ... iArgs)    // TSrc&& can bind an lvalue or an rvalue 
        {
            static_assert(CompileTimeChecks<TSrc&&, TDst, Encoding>(), _DSY_UCS_MK_VIEW_ERROR_MSG);
            
            // std::forward for perfect forwarding
            return returned_view_t<TSrc, TDst, Encoding>(std::forward<TSrc>(iStr), std::forward<Args>(iArgs) ...);
        }   // _make_view with 1 Encoding parameter
        
        
        
        /*template<typename TDst, typename Encoding1, typename Encoding2, typename TSrc>
        inline std::enable_if<has not TypeFrom & TypeTo> _make_view(TSrc&& iStr)
        {
            static_assert(false, "Invalid args...");
        }*/
        
        template<typename TDst, typename Encoding1, typename Encoding2, typename TSrc, typename ... Args>   // C++11 parameter packs that accepts zero or more template arguments
        inline auto /*auto only => avoids SFINAE skip */ _make_view(TSrc&& iStr, Args&& ... iArgs)    // TSrc&& can bind an lvalue or an rvalue 
            // Use trailing return type, C++11 feature introduced to simplify defining function templates 
            // whose return type depends on an expression involving its arguments
            -> returned_view_t<TSrc, TDst, 
#if !defined(_DSY_UCS_REORDER_INVALID)
                    Encoding1, Encoding2
#else   // _DSY_UCS_REORDER_INVALID
                    typename PairFromTo<Encoding1, Encoding2>::TypeFrom, 
                    typename PairFromTo<Encoding1, Encoding2>::TypeTo
#endif  // _DSY_UCS_REORDER_INVALID
                    >
        {
            static_assert(CompileTimeChecks<TSrc&&, TDst, Encoding1, Encoding2>(), _DSY_UCS_MK_VIEW_ERROR_MSG);
            
#if !defined(_DSY_UCS_REORDER_INVALID)
            // std::forward for perfect forwarding
            return returned_view_t<TSrc, TDst, Encoding1, Encoding2>(std::forward<TSrc>(iStr), std::forward<Args>(iArgs) ...);
#else   // _DSY_UCS_REORDER_INVALID
            using EncodingFrom_t = typename PairFromTo<Encoding1, Encoding2>::TypeFrom;
            using EncodingTo_t   = typename PairFromTo<Encoding1, Encoding2>::TypeTo;
            // std::forward for perfect forwarding
            return returned_view_t<TSrc, TDst, EncodingFrom_t, EncodingTo_t>(std::forward<TSrc>(iStr), std::forward<Args>(iArgs) ...);
#endif  // _DSY_UCS_REORDER_INVALID
        }   // _make_view with 2 Encoding parameters
        
        
    }   // namespace internal
    }   // namespace UCS (UniCode Services)
}   // namespace DSY

#endif  // DSYStringViewInternal_H
