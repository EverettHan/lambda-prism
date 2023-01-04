//*****************************************************************************
//* DEPRECATED R417 - DO NOT USE!                                             *
//*****************************************************************************
//* Replaced by CATUnicodeString which offers the same guarantees (per instance
//  thread-safety...).                                                        *
//* A migration sample is available: StringMigrationSample (FW SystemTS.tst)  *
//* Header: CATUnicodeString.h                                                *
//*****************************************************************************


#ifndef CATSysTSUnicodeString_h
#define CATSysTSUnicodeString_h

#include "CATSysTS.h"
#include "CATDataType.h"
#include "CATSysTSDataType.h"
#include "CATSysTSVectorOfCATUC2Bytes.h"
#include <stdlib.h>

// class CATSysTSInterUnicodeString;
class CATInterUnicodeString;
class CATSysTSVectorOfUnicodeString;

/** 
 * @deprecated R417 use CATUnicodeString instead.
 * Class to use for NLS character strings in a multithreaded application.
 * This string implementation uses atomic reference counting, making the management 
 * of shared references to strings thread safe. This however does NOT mean that string 
 * operations themselves are thread safe.
 * You can use different instances of CATSysTSUnicodeString at the same time in several threads.
 * But you should take the normal precautions when writing code that access the same 
 * CATSysTSUnicodeString instance from different threads.
 * In order to preserve thread safety, make your methods return copy of CATSysTSUnicodeString
 * and not references ; since this implementation uses reference counting, the copy construction
 * of a CATSysTSUnicodeString is efficient and does not lead to a deep copy of the internal 
 * string buffer.
 */
class ExportedByCATSysTS CATSysTSUnicodeString {

    public:
    
        /**
         * Constructs an empty Unicode string.
         */
        CATSysTSUnicodeString();
        
        /**
         * Constructs a CATSysTSUnicodeString instance from a char*.
       * If ipsz == NULL, builds an empty string.
         */
        CATSysTSUnicodeString(const char* ipsz);
        
        /**
         * Constructs a CATSysTSUnicodeString instance from a wchar*.
         */
        CATSysTSUnicodeString(const wchar_t* ipwsz);
        
        /**
         * Constructs a CATSysTSUnicodeString instance from a CATUC2Bytes* buffer and its size.
         */
        CATSysTSUnicodeString(const CATUC2Bytes* ipUCChar, int iCharLength);
        
        /** 
         * Copy constructor.
         */
        CATSysTSUnicodeString(const CATSysTSUnicodeString& iString);
        
        /**
         * Constructs a CATSysTSUnicodeString instance by extracting a substring from iStr
       * from iBegin (counting from 0, INCLUDING) to iEnd (counting from 0, EXCLUDING).
         */
        CATSysTSUnicodeString(const CATSysTSUnicodeString& iStr, int iBegin, int iEnd);
        
        /**
         * Destructor.
         */
        ~CATSysTSUnicodeString(); 
        
        /**
         * Builds the current string from an array of Unicode characters.
         * @param ipUCChar
         *   The array of Unicode characters
         * @param iCharLength
         *   The string length in unicode characters count
         */
        void BuildFromUCChar(const CATUC2Bytes *ipUCChar, int iCharLength);

        /**
         * Assignment operator from a char*.
         */
        CATSysTSUnicodeString& operator=(const char* ipsz);
        
        /**
         * Assignment operator from a wchar_t*.
         */
        CATSysTSUnicodeString& operator=(const wchar_t* ipwsz);
        
        /**
         * Assignment operator from a string
         */
        CATSysTSUnicodeString& operator=(const CATSysTSUnicodeString& iStr);
        
        /** @nodoc */
        CATBoolean operator==(const CATSysTSUnicodeString& iStr) const;
        
        /** @nodoc */
        CATBoolean operator!=(const CATSysTSUnicodeString& iStr) const; 
        
        /** @nodoc */
        CATBoolean operator<(const CATSysTSUnicodeString& iStr) const; 
        
        /** @nodoc */
        CATBoolean operator<=(const CATSysTSUnicodeString& iStr) const; 
        
        /** @nodoc */
        CATBoolean operator>(const CATSysTSUnicodeString& iStr) const; 
        
        /** @nodoc */
        CATBoolean operator>=(const CATSysTSUnicodeString& iStr) const; 
        
        /**
         * Compares the current CATSysTSUnicodeString instance to iString.
         * @param iString
         * The CATSysTSUnicodeString to compare with.
         * @param iIgnoringCase
         * Specify whether the comparison must ignore the case or not.
         * @return
         *   0 if the strings are identical, 
         *   <0 if the current string is lesser than iString
         *   >0 if the current string is greater than iString
         */
        int Compare(const CATSysTSUnicodeString& iString, CATBoolean iIgnoringCase = FALSE) const;
        
        /** 
         * Returns the length of the CATSysTSUnicodeString, as unicode char count.
         * <b>Role</b>: Get the length as unicode char count.
         * This method returns the length of the string returned by @href #ConvertToUCChar,
         * without counting the terminator character.
         * @return 
         *   Character count.
         */
        int GetLengthInChar() const;
        
        /** 
         * Get the length of the CATSysTSUnicodeString, as byte count.
         * <b>Role</b>: Get the length as byte count.
         * This method returns the length of the string returned by @href #ConvertToChar,
         * without counting the terminator character.
         * @return 
         *   Byte count.
         */
        int GetLengthInByte() const;
        
        /**
         * Converts the string to a char * (MBCS view).
         * Warning : as this method is locale dependent, some Unicode characters may not be
         * represented with the used code page and would be lost in the returned char * buffer.
         * This method should be used only for debugging purpose and must be avoided as often as possible.
         * The length of the returned string is given by @href #GetLengthInByte.
         * @return 
         *   The char*
         */
        const char* ConvertToChar() const;
        
        /**
         * Converts the current string to a CATUC2Bytes character encoded 
         * string.
         * The length of the returned string is given by @href #GetLengthInChar.
         * @return
         *   The resulting CATUC2Bytes string
         */
        const CATUC2Bytes* ConvertToUCChar() const;
        
        /**
         * Concatenates iStr at the end of the string
         */
        CATSysTSUnicodeString& Append(const CATSysTSUnicodeString& iStr);
        
        CATSysTSUnicodeString& Append( const CATSysTSUnicodeString& iStr1, 
                                       const CATSysTSUnicodeString& iStr2 );
        
        CATSysTSUnicodeString& Append( const CATSysTSUnicodeString& iStr1, 
                                       const CATSysTSUnicodeString& iStr2,
                                       const CATSysTSUnicodeString& iStr3 );
        
        CATSysTSUnicodeString& Append(const CATSysTSUnicodeString& iStr,
                                      int iBegin, int iEnd);
        
        /**
         * Return a substring from iBegin (counting from 0, including) to iEnd (counting from 0, excluding)
         * if iBegin < 0 or iBegin > length-1 or iEnd < 1 or iEnd > length then
         *    return an empty string
         * <pre>
         * CATSysTSUnicodeString str("Hello");
         * str.Substring(1,3); will result in "el"
         * </pre>
         */
        CATSysTSUnicodeString SubString(int iBegin, int iEnd) const;
        
        /**
         * Clear and fill the list(vector) ovStrings with all strings after an before iPattern
         * the length of the list is always the number of occurences of iPattern + 1
         * "dogcatdog".Split("cat") fills ovStrings with {"dog", "dog"}
         * "dogcatdog".Split("dog") fills ovStrings with {"", "cat", ""}
         */
        void Split(const CATSysTSUnicodeString& iPattern, CATSysTSVectorOfUnicodeString& ovStrings) const;
        
        /**
         * Converts, formats and stores a specified integer, under
         * control of the format parameter, into the current string.
         * @param iIntegerValue
         *   The integer value
         * @param iCFormat
         *   The format of the integer value, defaulted to "%d", according to the sprintf
         *   library function base conversions
         * @return
         *   HRESULT specifying the success or not of the action
         */
        HRESULT BuildFromNum(int iIntegerValue, const char* iCFormat = "%d");

        /**
            * Converts, formats and stores a specified UTF-8 encoded
            * character string (about UTF-8, see above), into the current 
            * string.
            * @param iUTF8Data
            *   The pointer to the UTF-8 encoded character string
            * @param iByteCount
            *   The length of <tt>iUTF8Data</tt> in bytes
            * @return
            *   boolean specifying the success or not of the action
            *   <br><b>Legal values</b>: <tt>0</tt> if the conversion 
            *   succeeded, or <tt>negative value</tt> if the conversion did 
            *   not succeed.
            */
           int  BuildFromUTF8(const char *iUTF8Data, size_t iByteCount);

        /**
         * Convert the current string into a UTF-8 character string.
         * @param oUTF8String
         *   The resulting UTF-8 string
         *   It should be allocated as a table of 
         *   4*(this->GetLengthInChar()) elements
         * @param oByteCount
         *   String length in byte count
         */
        void ConvertToUTF8( char *oUTF8String, size_t *oByteCount) const;
        
        /**
         * Read character data, supposed to describe an integer
         * in an alphanumerical form, interpret it according to
         * a format, and store the converted result into the output 
         * parameter.
         * @param oIntegerValue
         *   The resulting integer value
         * @param iCFormat
         *   The format of the integer value, defaulted to "%d", according to the sprintf
         *   library function base conversions
         * @return
         *   HRESULT specifying the success or not of the action
         */
        HRESULT ConvertToNum(int& oIntegerValue, const char* iCFormat = "%d") const;
        
        /**
         * Insert iStr before position iIndex
         */
        HRESULT Insert(int iIndex, const CATSysTSUnicodeString& iStr);
        
        /**
         * Insert range from iRangeBegin (including) to iRangeEnd (excluding)
       * of iStr before position iInsertIndex
         */
        HRESULT Insert(int iInsertIndex, const CATSysTSUnicodeString& iStr, 
                       int iRangeBegin, int iRangeEnd);
        
        /**
         * return TRUE if iPattern is at position iIndex (counting from 0)
         */
        CATBoolean IsSubStringAt(int iIndex, const CATSysTSUnicodeString& iPattern) const;
        
        /**
         * Search the first occurence of iPattern, beginning at iBegin
         * @return 
         *   <tt>found position (counting from 0)</tt> 
         *   <tt>-1 if not found</tt> 
         */
        int SearchSubString(const CATSysTSUnicodeString& iPattern, int iBegin = 0) const;

        /**
         * Search the first occurence of iPattern, beginning at iBegin (counting backward from the last element)
         * @return 
         *   <tt>found position (COUNTING FROM 0 FROM THE BEGINNING)</tt> 
         *   <tt>-1 if not found</tt> 
         */
        int SearchSubStringBackward(const CATSysTSUnicodeString& iPattern, int iBeginFromEnd = 0) const;

        /**
         * Replace range from iBegin (counting from 0, INCLUDING) to iEnd (counting from 0, EXCLUDING)
         * by iReplacing
         */
        HRESULT ReplaceRange(int iBegin, int iEnd, const CATSysTSUnicodeString& iReplacing);

        /**
         * Replace the FIRST occurrence of iPattern by iReplacing, beginning at iBegin (counting from 0)
         * @return the position of iPattern
         *   <tt>found position (counting backward from the last element)</tt> 
         *   <tt>-1 if not found</tt> 
         */
        int ReplaceSubString(const CATSysTSUnicodeString& iPattern, 
                           const CATSysTSUnicodeString& iReplacing,
                           int iBegin = 0);
    
        /**
         * Replace all occurences of iPattern by iReplacing
         */
        void ReplaceAll(const CATSysTSUnicodeString& iPattern, const CATSysTSUnicodeString& iReplacing);

        /* 
         * if iCapacity > length
         *   Set the expected maximum number of unicode characters in the current string.
         *   No allocation will occur while length stays under (or equal) to iCapacity.
         * else
         *   Do nothing.
         */
        void SetCapacity(int iCapacity);

        /**
         * Function used in HashMap, return a pointer to a buffer to internal memory
         * oSize is the size of the buffer
         * if (str1 == str2) then binDump1 == binDump2
         */
        const char* GetBinDump(CATUINT32& oSize) const;
    
        /**
         * Returns a hashcode value for this string.
         * There is no garantee about unicity.
         */
        unsigned int HashFunc() const;
   
        /**
         * Placement new / delete.
         */
        static void * operator new(size_t iSize, void * location);
        static void operator delete(void *iAddr, void * location);

    private:

#if !defined(_SUNOS_SOURCE) && !defined(_DS_PLATEFORME_64)
        /**
         * Prevent CATSysTSInterUnicodeString allocated on the heap
         */
        static void * operator new(size_t iSize);
        static void operator delete(void *iAddr);
#endif // !_SUNOS_SOURCE && !_DS_PLATEFORME_64

        // void _AllocNewRefString(
                        // int iCharLength, 
                        // CATBoolean iMakeCopy = FALSE, 
                        // CATBoolean iMakeDeepCopy = FALSE,
                        // CATBoolean iComputeBestLength = FALSE);
        
        // void _UpdateCharView();
        
        void _BuildFromChar(const char* ipsz);

        void _BuildFromWChar(const wchar_t* ipwsz);

        HRESULT _CheckRange(int iBegin, int iEnd) const;
        
        void _Reset();
        
        int _SortCompare(const CATSysTSUnicodeString& iStringToCompare) const;
        
        CATInterUnicodeString * _SetCapacity(int iCapacity, unsigned char iIsUnicode);

    private:

        // ++ IK8
        union
        {
            /*
             * @nodoc
             * _Str & _WStr are defined for debugging purposes.
             */
            char *_Str;
#ifdef _WINDOWS_SOURCE
            wchar_t     *_WStr;
#else   // _WINDOWS_SOURCE
            CATUC2Bytes *_WStr;
#endif  // _WINDOWS_SOURCE
            CATULONGPTR _StringRef;
        };
        // --IK8
    
    public:
    
        void ToUpper();
        
        void ToLower();
};

#endif // CATSysTSUnicodeString_h
