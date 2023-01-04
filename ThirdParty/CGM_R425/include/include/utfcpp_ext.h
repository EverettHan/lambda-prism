
#ifndef utfcpp_ext_H
#define utfcpp_ext_H


// #include "utf8/checked.h"// Requires C++ exceptions to be enabled and we don't want this header to propagate this requirement by default
#include "utf8/unchecked.h"
#include "CATSysDataType.h" // utf8::uint16_t, utf8::uint32_t

#include <functional>       // std::reference_wrapper
#include <iterator>         // std::iterator, std::input_iterator_tag

namespace utfcppext
{
    // constexpr const char REPLACEMENT_CHAR = '?';
    
    namespace internal
    {
        template <typename IterTyp>
        class proxy_iterator
        {
            std::reference_wrapper<IterTyp> m_ref;
        public:
            typedef typename std::iterator_traits<IterTyp>::iterator_category   iterator_category;
            typedef typename std::iterator_traits<IterTyp>::value_type          value_type;
            typedef typename std::iterator_traits<IterTyp>::difference_type     difference_type;
            typedef typename std::iterator_traits<IterTyp>::pointer             pointer;
            typedef typename std::iterator_traits<IterTyp>::reference           reference;
        
            proxy_iterator(IterTyp & iIter) noexcept : m_ref(iIter)
            {
            }
            
            proxy_iterator(const proxy_iterator<IterTyp> & iOther) noexcept = default;            
            proxy_iterator<IterTyp> & operator = (const proxy_iterator<IterTyp> & iOther) noexcept = default;
            
            operator IterTyp & () const noexcept { return m_ref.get(); }
        };
        
        template <typename u16bit_iterator>
        u16bit_iterator append16(uint32_t cp, u16bit_iterator result)
        {
            if (cp > 0xffff) { //make a surrogate pair
                *result++ = static_cast<utf8::uint16_t>((cp >> 10)   + utf8::internal::LEAD_OFFSET);
                *result++ = static_cast<utf8::uint16_t>((cp & 0x3ff) + utf8::internal::TRAIL_SURROGATE_MIN);
            }
            else
                *result++ = static_cast<utf8::uint16_t>(cp);
            return result;
        }
        
    }   // namespace internal
    
    namespace checked   // Checked, but no C++ exceptions
    {
        template <typename u16bit_iterator>
        bool next16(u16bit_iterator& it, u16bit_iterator end, utf8::uint32_t &oCodePoint)
        {
            utf8::uint32_t cp = utf8::internal::mask16(*it++);
            // Take care of surrogate pairs first
            if (utf8::internal::is_lead_surrogate(cp)) {
                if (it != end) {
                    utf8::uint32_t trail_surrogate = utf8::internal::mask16(*it++);
                    if (utf8::internal::is_trail_surrogate(trail_surrogate))
                        cp = (cp << 10) + trail_surrogate + utf8::internal::SURROGATE_OFFSET;
                    else
                    {
                        oCodePoint = static_cast<utf8::uint16_t>(trail_surrogate);
                        return false;
                    }
                }
                else
                {
                    oCodePoint = static_cast<utf8::uint16_t>(cp);
                    return false;
                }
            }
            // Lone trail surrogate
            else if (utf8::internal::is_trail_surrogate(cp))
            {
                oCodePoint = static_cast<utf8::uint16_t>(cp);
                return false;
            }
            oCodePoint = cp;
            return true;
        }
        
		/*
        template <typename u16bit_iterator, typename u32bit_iterator>
        u32bit_iterator utf16to32 (u16bit_iterator start, u16bit_iterator end, u32bit_iterator result)
        {
            u32bit_iterator resultStart = result;
            while(start != end)
            {
                utf8::uint32_t cp = 0;
                if(next16(start, end, cp))
                    *(result++) = cp;
                else
                    return resultStart;
            }
            return result;
        }
		
        template <typename u32bit_iterator, typename u16bit_iterator>
        u16bit_iterator utf32to16 (u32bit_iterator start, u32bit_iterator end, u16bit_iterator result)
        {
            while (start < end)
            {
                utf8::uint32_t cp = *start++;
                if (!utf8::internal::is_code_point_valid(cp))
                    throw utf8::invalid_code_point(cp);	// TODO do not throw an exception
                
                result = utfcppext::internal::append16(cp, result);
            }
            return result;
        }*/
        
    }   // namespace checked
    
    namespace unchecked 
    {
        namespace internal
        {
            /**
             * RawStringSafeIterator.
             * DO NOT USE. Harms PCS more than using functions in "utf8::checked" or "utf8" namespaces
             */
            template<typename CharTyp>
            class RawStringSafeIterator : public std::iterator<std::input_iterator_tag, CharTyp>
            {
                CharTyp* m_ptr;
                CharTyp* & m_ptrLimit;

                // In case end iterator gets derefenced, which is undefined behavior in STL
                // cf. https://en.cppreference.com/w/cpp/container/vector/end
                // "Returns an iterator to the element following the last element of the container.
                //  This element acts as a placeholder; attempting to access it results in undefined behavior."
                static CharTyp s_DerefEndSafe;	// To avoid derefencing out of range pointer that may cause an invalid memory access (read-protected memory for e.g.)
                
            public:
                explicit RawStringSafeIterator(CharTyp* x) : m_ptr(x), m_ptrLimit(m_ptr) {}
                RawStringSafeIterator(CharTyp* x, RawStringSafeIterator<CharTyp> & iEndIt) : m_ptr(x), m_ptrLimit(iEndIt.m_ptr) {}
                
                RawStringSafeIterator& operator++()
                {
                    // ++IK8
                    // cf. https://stackoverflow.com/questions/6673762/why-is-used-with-iterators-instead-of
                    // "Further, you aren't allowed to increment an iterator past the end of the range into which it points. 
                    // So, if you end up in a scenario where it != foo.end() does not do the same thing as it < foo.end(),
                    // you already have undefined behavior because you've iterated past the end of the range."
                    //
                    // ++IK8 IMPORTANT: avoid UMR that may cause crash if the code reaches read-protected memory! 
                    // And it surely will at some point if the loop goes on...
                    // Why not implement "operator!=" with "operator<", which is probably a more efficient solution (PCS)? Because:
                    //  1) "!=" is symetric, while "<" is not, so work if the code is written "start != end", but doesn't if it is written the other way around: "end != start"
                    //  2) Does not prevent UMRs, which may be fatal (cf. read-protected memory). Since ++ is allowed to move the iterator out of range.
                    if (m_ptr < m_ptrLimit)
                        ++m_ptr;                
                    
                    // --IK8
                    return *this;
                }
                RawStringSafeIterator operator++(int)
                {
                    RawStringSafeIterator tmp(*this);
                    operator++();
                    return tmp;
                }

                // operator CharTyp *&() { return m_ptr; }
                CharTyp & operator*()
                {
                    if (m_ptr == m_ptrLimit)
                    {
                        m_ptr = &s_DerefEndSafe;
                        m_ptrLimit = m_ptr;
                    }
                    return *m_ptr;
                }
                bool operator==(const RawStringSafeIterator<CharTyp> & rhs) const { return m_ptr == rhs.m_ptr; }
                bool operator!=(const RawStringSafeIterator<CharTyp> & rhs) const { return m_ptr != rhs.m_ptr; }
            };

            template<typename CharTyp>
            CharTyp RawStringSafeIterator<CharTyp>::s_DerefEndSafe = 0;
            
            // Unsafe! Rather use utfcppext::checked::next16 instead in most cases
            template <typename u16bit_iterator>
            utf8::uint32_t next16(u16bit_iterator& it)
            {
                utf8::uint32_t cp = utf8::internal::mask16(*it++);
                // Take care of surrogate pairs first
                if (utf8::internal::is_lead_surrogate(cp)) {
                    utf8::uint32_t trail_surrogate = utf8::internal::mask16(*it++);
                    cp = (cp << 10) + trail_surrogate + utf8::internal::SURROGATE_OFFSET;
                }
                return cp;
            }
            
            // next_boundary_safe: similar to utf8::internal::validate_next, but only boundary checks
            // no is_code_point_valid or is_overlong_sequence checks, so behavior matches more utf8::unchecked::next in a safe way
            // Possible errors: NOT_ENOUGH_ROOM, INVALID_LEAD, INCOMPLETE_SEQUENCE
            template <typename octet_iterator>
            utf8::internal::utf_error next_boundary_s(octet_iterator& it, octet_iterator end, utf8::uint32_t& code_point)
            {
                if (it == end)
                    return utf8::internal::NOT_ENOUGH_ROOM;

                // Save the original value of it so we can go back in case of failure
                // Of course, it does not make much sense with i.e. stream iterators
                octet_iterator original_it = it;

                utf8::uint32_t cp = 0;
                // Determine the sequence length based on the lead octet
                typedef typename std::iterator_traits<octet_iterator>::difference_type octet_difference_type;
                const octet_difference_type length = utf8::internal::sequence_length(it);

                // Get trail octets and calculate the code point
                utf8::internal::utf_error err = utf8::internal::UTF8_OK;
                switch (length) {
                    case 0: 
                        return utf8::internal::INVALID_LEAD;
                    case 1:
                        err = utf8::internal::get_sequence_1(it, end, cp);
                        break;
                    case 2:
                        err = utf8::internal::get_sequence_2(it, end, cp);
                    break;
                    case 3:
                        err = utf8::internal::get_sequence_3(it, end, cp);
                    break;
                    case 4:
                        err = utf8::internal::get_sequence_4(it, end, cp);
                    break;
                }

                if (err == utf8::internal::UTF8_OK) {
                    // Decoding succeeded. No more validations in this routine! Use utf8::internal::validate_next if more validation is required
                    code_point = cp;
                    ++it;
                    return utf8::internal::UTF8_OK;
                }

                // Failure branch - restore the original value of the iterator
                it = original_it;
                return err;
            }
            
        }   // namespace internal
        
        
        template <typename u16bit_iterator>
        uint32_t prior16(u16bit_iterator& it)
        {
            while (utf8::internal::is_trail_surrogate(*(--it)));
            u16bit_iterator temp = it;
            return internal::next16(temp);
        }
        
        /**
         * IMPORTANT: the following algorithms are safe replacements for UTF8-CPP unchecked algorithms which are risky to use
         *  + utfcppext::unchecked::utf8to32_s    => replacement for   utf8::unchecked::utf8to32
         *  + utfcppext::unchecked::utf8to16_s    => replacement for   utf8::unchecked::utf8to16
         *  + utfcppext::unchecked::utf16to32_s   => replacement for   utf8::unchecked::utf16to32
         *  + utfcppext::unchecked::utf16to8_s    => replacement for   utf8::unchecked::utf16to8
         *
         * Why just not use checked algorithms ?
         *  1) Because sometimes we just don't care if some of the characters are corrupted (to prepare a string for display for e.g.)
         *  2) Because unchecked algorithms are much more efficient (PCS ~x2)
         * 
         * These safe "_s" versions are designed to be as efficient as UTF8-CPP unchecked algorithms but are safer:
         * no risk of out of bound reads, which could cause invalid memory access exceptions...
         */
        
        template <typename octet_iterator, typename u32bit_iterator>
        u32bit_iterator utf8to32_s (octet_iterator start, octet_iterator end, u32bit_iterator result)
        {
            const auto len = end - start;
            if (len >= 4)
            {
                octet_iterator end2 = end - 4 + 1;
                while (start < end2)
                    (*result++) = utf8::unchecked::next(start);    // Faster than utf8::next
            }
            
            while (start != end)
            {
                utf8::uint32_t cp = 0;
                /*try {
                    // const utfcppext::internal::proxy_iterator<octet_iterator> endProxy = end;
                    // return utf8::utf8to16(curProxy, endProxy, result);
                    // return utf8::utf8to16(start, end, result);
                    cp = utf8::next(start, end);
                // } catch(utf8::invalid_utf8 & ex) {
                    // cp = ex.utf8_octet();
                } catch(std::exception & ex) {
                    (void *)(&ex);
                    cp = REPLACEMENT_CHAR;
                }                
                (*result++) = cp;*/
                
                utf8::internal::utf_error err_code = internal::next_boundary_s/*utf8::internal::validate_next*/(start, end, cp);
                switch (err_code) {
                    case utf8::internal::UTF8_OK :
                        (*result++) = cp;
                        break;
                    default :
                        ++start;    // Skip invalid char
                }
            }

            return result;
        }        
        
        template <typename u16bit_iterator, typename octet_iterator>
        u16bit_iterator utf8to16_s (octet_iterator start, octet_iterator end, u16bit_iterator result)
        {
            const auto len = end - start;
            utfcppext::internal::proxy_iterator<octet_iterator> startProxy = start;
            if (len >= 4)
            {
                octet_iterator end2 = end - 4 + 1;
                const utfcppext::internal::proxy_iterator<octet_iterator> end2Proxy = end2;
                result = utf8::unchecked::utf8to16(startProxy, end2Proxy, result);
                // result = utf8::unchecked::utf8to16(start, end2, result);
            }
            // Use the checked algo (less efficient) for the end of the string to prevent invalid memory access if the input string is invalid/corrupted            
            while(start != end)
            {
                utf8::uint32_t cp = 0;
                /*try {
                    // const utfcppext::internal::proxy_iterator<octet_iterator> endProxy = end;
                    // return utf8::utf8to16(startProxy, endProxy, result);
                    // return utf8::utf8to16(start, end, result);
                    cp = utf8::next(start, end);
                // } catch(utf8::invalid_utf8 & ex) {
                    // cp = ex.utf8_octet();
                } catch(std::exception & ex) {
                    (void *)(&ex);
                    cp = REPLACEMENT_CHAR;
                }
                result = utfcppext::internal::append16(cp, result);*/
                
                utf8::internal::utf_error err_code = internal::next_boundary_s/*utf8::internal::validate_next*/(start, end, cp);
                switch (err_code) {
                    case utf8::internal::UTF8_OK :
                        result = utfcppext::internal::append16(cp, result);
                        break;
                    default :
                        ++start;    // Skip invalid char
                }
            }
            return result;
        }
        
        
        template <typename u16bit_iterator, typename u32bit_iterator>
        u32bit_iterator utf16to32_s (u16bit_iterator start, u16bit_iterator end, u32bit_iterator result)
        {
            const auto len = end - start;
            if (len >= 2)
            {
                u16bit_iterator end2 = end - 2 + 1;
                // ++IK8 18:10:09 start may go past end2, hence < instead of !=
                while (start < end2)
                // ++IK8 18:10:09
                    *(result++) = internal::next16(start);    // Faster than utfcppext::checked::next16
            }
            
            while(start != end)
            {
                utf8::uint32_t cp;
                // try {
                utfcppext::checked::next16(start, end, cp);
                // } catch(std::exception & ex) {
                //     (void *)(&ex);
                // }
                *(result++) = cp;
            }

            return result;
        }
        
        template <typename u16bit_iterator, typename octet_iterator>
        octet_iterator utf16to8_s (u16bit_iterator start, u16bit_iterator end, octet_iterator result)
        {
            const auto len = end - start;
            // utfcppext::internal::proxy_iterator<u16bit_iterator> curProxy = start;
            if (len >= 2)
            {
                u16bit_iterator end2 = end - 2 + 1;
                // const utfcppext::internal::proxy_iterator<u16bit_iterator> end2Proxy = end2;
                // result = utf8::unchecked::utf16to8(curProxy, end2Proxy, result);                
                // ++IK8 18:10:09 start may go past end2, hence < instead of !=
                while (start < end2)
                // ++IK8 18:10:09
                {
                    utf8::uint32_t cp = internal::next16(start);    // Faster than utfcppext::checked::next16
                    result = utf8::unchecked::append(cp, result);
                }
            }
            // Use the checked algo (less efficient) for the end of the string to prevent invalid memory access if the input string is invalid/corrupted
            
            // const utfcppext::internal::proxy_iterator<u16bit_iterator> endProxy = end;
            // return utf8::utf16to8(curProxy, endProxy, result);
            // return utf8::utf16to8(start, end, result);
            while(start != end)
            {                
                utf8::uint32_t cp;
                // try {
                utfcppext::checked::next16(start, end, cp);
                // } catch(std::exception & ex) {
                //     (void *)(&ex);
                // }
                result = utf8::unchecked::append(cp, result);
            }
            
            return result;
        }
        

        template <typename u32bit_iterator, typename u16bit_iterator>
        u16bit_iterator utf32to16 (u32bit_iterator start, u32bit_iterator end, u16bit_iterator result)
        {
            while (start < end)
            {
                utf8::uint32_t cp = *start++;
                result = utfcppext::internal::append16(cp, result);
            }
            return result;
        }
        
        // next_s: replacement for utf8::unchecked::next which prevents invalid memory (read) accesses
        // cf. utf8to32_s
        template <typename octet_iterator>
        utf8::uint32_t next_s(octet_iterator& it, const octet_iterator end)
        {
            utf8::uint32_t cp = 0;
            const auto len = end - it;
            if (len >= 4)
            {
                cp = utf8::unchecked::next(it);    // Faster than utf8::next
            }
            else if(it != end)
            {                
                utf8::internal::utf_error err_code = internal::next_boundary_s/*utf8::internal::validate_next*/(it, end, cp);
                switch (err_code) {
                    case utf8::internal::UTF8_OK :
                        break;
                    default :
                        ++it;    // Skip invalid char
                }
            }
            return cp;
        }
        
        // next16_s: safer alternative to utfcppext::unchecked::next16 which prevents invalid memory (read) accesses
        // cf. utf16to32_s
        template <typename u16bit_iterator>
        utf8::uint32_t next16_s(u16bit_iterator & it, const u16bit_iterator end)
        {
            utf8::uint32_t cp = 0;
            const auto len = end - it;
            if (len >= 2)
            {
                cp = internal::next16(it);    // Faster than utfcppext::checked::next16
            }
            else if(it != end)
            {
                utfcppext::checked::next16(it, end, cp);
            }
            return cp;
        }
    }   // namespace unchecked
}

#endif  // utfcpp_ext_H
