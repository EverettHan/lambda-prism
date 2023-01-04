#ifndef DSYSysUCConv_H
#define DSYSysUCConv_H

#include "CATSysTS.h"
#include "CATSysDataType.h"

#define DSY_SYS_UC_CONV_REPL_CHAR       0x003F
#define DSY_SYS_UC_NUM_MAX_BYTES        0x04

#define _DSY_DEPRECATED_EXPORT_TRANSITIONAL // TODO RM

namespace DSYSysUCAlgorithm
{
    /**
    * ConvertUTF8ToUTF16 converts a string in UTF-8 format to UTF-16.
    * It translates the UTF-8 sequence pointed by ioStrUTF8 to the equivalent 
    * sequence of UTF-16 characters, up until either iStrUTF16Size characters 
    * have been translated or until there are no more UTF-8 characters to
    * convert in ioStrUTF8. If the function translates an entire UTF-8 string, 
    * ioStrUTF8 is set to a null pointer value.
    * WARNING: there is no guarantee that the output string will be 
    * null-terminated.
    * @param [in,out] ioStrUTF8 is a pointer to the UTF-8 string to convert. 
    *                 It is modified by the routine to point to past the 
    *                 last UTF-8 character converted if conversion stops 
    *                 prematurely (output buffer full for e.g.), or to a null 
    *                 pointer if the function reached the end of the string.
    * @param [in,out] ioUTF8BytesLeft is number of bytes of the string pointed 
    *                 by ioStrUTF8. It is modified by the routine to reflect 
    *                 the remaining number of bytes of ioStrUTF8 to convert.
    * @param [out]    oStrUTF16 is a pointer to an array that will UTF-16 data.
    *                 If it is NULL, the call doesn't output any data but 
    *                 rather returns the required buffer size for ioStrUTF8 
    *                 to be converted in one step. iStrUTF16Size is ignored.
    * @param [in]     iStrUTF16Size is the size of oStrUTF16 and defines the 
    *                 maximum number of characters to output.
    * @retval upon success, number of characters written to oStrUTF16 
    *                 (not including the eventual terminating null character).
    * @retval (unsigned int)-1 in case of failure (invalid parameters).
    */
    ExportedByCATSysTS unsigned int ConvertUTF8ToUTF16(const char *&ioStrUTF8, 
        int &ioUTF8BytesLeft, CATUC2Bytes *oStrUTF16, unsigned int iStrUTF16Size);
        
    // deprecated
#if defined(_DSY_DEPRECATED_EXPORT_TRANSITIONAL)
    ExportedByCATSysTS size_t ConvertUTF8ToUCS2(const char *&ioStrUTF8, 
        size_t &ioUTF8BytesLeft, CATUC2Bytes *oStrUTF16, size_t iStrUTF16Size);
#else   // _DSY_DEPRECATED_EXPORT_TRANSITIONAL
    inline size_t ConvertUTF8ToUCS2(const char *&ioStrUTF8, 
        size_t &ioUTF8BytesLeft, CATUC2Bytes *oStrUTF16, size_t iStrUTF16Size)
    {
        int l_UTF8BytesLeft = (int)ioUTF8BytesLeft;
        size_t rc = (int)ConvertUTF8ToUTF16(ioStrUTF8, l_UTF8BytesLeft, oStrUTF16, (unsigned int)iStrUTF16Size);
        ioUTF8BytesLeft = (size_t)l_UTF8BytesLeft;
        return rc;
    }
#endif  // _DSY_DEPRECATED_EXPORT_TRANSITIONAL
    // INTERNAL USE ONLY
    ExportedByCATSysTS int ConvertUTF8ToUCS2Legacy(const char *iUTF8String, size_t iUTF8Size, 
        CATUC2Bytes *oUnicodeString, int *oUnicodeSize);
    
    /**
    * ConvertUTF16ToUTF8 converts a string in UTF-16 format to UTF-8.
    * It translates the UTF-16 sequence pointed by ioStrUTF16 to the equivalent 
    * sequence of UTF-8 characters, up until either iStrUTF8Size characters 
    * have been translated or until there are no more UTF-16 characters to
    * convert in ioStrUTF16. If the function translates an entire UTF-16 string, 
    * ioStrUTF16 is set to a null pointer value.
    * WARNING: there is no guarantee that the output string will be 
    * null-terminated.
    * @param [in,out] ioStrUTF16 is a pointer to the UTF-16 string to convert. 
    *                 It is modified by the routine to point to past the 
    *                 last UTF-16 character converted if conversion stops 
    *                 prematurely (output buffer full for e.g.), or to a
    *                 null pointer if the function reached the end of the 
    *                 string.
    * @param [in,out] ioUTF16CharLeft is number of characters of the string 
    *                 pointed by ioStrUTF16. It is modified by the routine to 
    *                 reflect the remaining number of characters of ioStrUTF16 
    *                 to convert.
    * @param [out]    oStrUTF8 is a pointer to an array of UTF-8 characters 
    *                 elements. If it is NULL, the call doesn't output any 
    *                 data but returns the required buffer size for ioStrUTF16 
    *                 to be converted in one step. iStrUTF8Size is ignored.
    * @param [in]     iStrUTF8Size is the size of oStrUTF8 and defines the 
    *                 maximum number of UTF-8 characters to output.
    * @retval upon success, number of UTF-8 bytes written to oStrUTF8 
    *                 (not including the eventual terminating null character).
    * @retval (unsigned int)-1 in case of failure (invalid parameters).
    */
    ExportedByCATSysTS unsigned int ConvertUTF16ToUTF8(const CATUC2Bytes *&ioStrUTF16, 
        int &ioUTF16CharLeft, char *oStrUTF8, unsigned int iStrUTF8Size);
    
    // deprecated
#if defined(_DSY_DEPRECATED_EXPORT_TRANSITIONAL)
    ExportedByCATSysTS size_t ConvertUCS2ToUTF8(const CATUC2Bytes *&ioStrUTF16, 
        size_t &ioUTF16CharLeft, char *oStrUTF8, size_t iStrUTF8Size);
#else   // _DSY_DEPRECATED_EXPORT_TRANSITIONAL
    inline size_t ConvertUCS2ToUTF8(const CATUC2Bytes *&ioStrUTF16, 
        size_t &ioUTF16CharLeft, char *oStrUTF8, size_t iStrUTF8Size)
    {
        int l_UTF16CharLeft = (int)ioUTF16CharLeft;
        size_t rc = (int)ConvertUTF16ToUTF8(ioStrUTF16, l_UTF16CharLeft, oStrUTF8, (unsigned int)iStrUTF8Size);
        ioUTF16CharLeft = (size_t)l_UTF16CharLeft;
        return rc;
    }
#endif  // _DSY_DEPRECATED_EXPORT_TRANSITIONAL
    
    namespace unchecked
    {
        ExportedByCATSysTS char *utf16to8(const CATUC2Bytes *start, const CATUC2Bytes *end, char *result);
        ExportedByCATSysTS CATUC2Bytes *utf8to16(const char *start, const char *end, CATUC2Bytes *result);
        ExportedByCATSysTS char *utf32to8(const CATUC4Bytes *start, const CATUC4Bytes *end, char *result);
        ExportedByCATSysTS CATUC4Bytes *utf8to32(const char *start, const char *end, CATUC4Bytes *result);
        ExportedByCATSysTS CATUC4Bytes *utf16to32(const CATUC2Bytes *start, const CATUC2Bytes *end, CATUC4Bytes *result);
        ExportedByCATSysTS CATUC2Bytes *utf32to16(const CATUC4Bytes *start, const CATUC4Bytes *end, CATUC2Bytes *result);
    }
    
    /************************************************************************/
    /* UTF-8 specific functions.                                            */
    /************************************************************************/
    
    /**
    * IsUTF8 allows to determine if a buffer does contain valid UTF-8 or not.
    * @param [in,out] ioStr is a pointer to the string buffer to be checked. 
    *                 It is modified by the routine to point to past the last 
    *                 UTF-8 character converted if an invalid character is
    *                 encountered.
    * @param [in]     iNBytes is the length of the input buffer ioStr.
    * @retval  0 upon success.
    * @retval -1 otherwise.
    */
    ExportedByCATSysTS int IsUTF8(const char *&ioStr, size_t iNBytes);
    // C++20: it makes no sense to add a char8_t signature, because char8_t data is supposed to be UTF8-encoded
    
    /**
    * CharUTF8Len returns the size of the UTF-8 character pointed by iStr, 
    * examining at most iMaxBytes bytes.
    * @param [in]  iStr is a pointer to the first byte of an UTF-8 encoded 
    *              character.
    * @param [in]  iMaxBytes is the maximum number of bytes of iStr to consider 
    *              for the UTF-8 character.
    * @retval size in bytes of the UTF-8 character pointed by iStr.
    * @retval  0 if iStr is pointing to a terminating null  character.
    * @retval -1 if iStr does not point to a valid UTF-8 character.
    */
    ExportedByCATSysTS int CharUTF8Len(const char *iStr, size_t iMaxBytes);
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    inline int CharUTF8Len(const char8_t *iStr, size_t iMaxBytes) {
        return CharUTF8Len(reinterpret_cast<char const*>(iStr), iMaxBytes);
    }
#endif
}

#endif  // DSYSysUCConv_H
