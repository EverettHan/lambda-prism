// COPYRIGHT Dassault Systemes 2004

#ifndef _CATSysTSCodePage_H
#define _CATSysTSCodePage_H

#include <string.h>
#include "CATSysTS.h"
#include "CATSysTSDataType.h"

class ExportedByCATSysTS CATSysTSCodePage 
{
public:
    /**
     * Converts a string from a the current code page to Unicode 2-Bytes.
     * @param iCodePageString
     *   Pointer to the string to be converted.
     * @param iStringLength
     *   Length of the string to be converted.
     * @param oUnicodeString
     *   Pointer to the resulting Unicode string. 
     *   This string has no string-terminating  character.
     * @param oUnicodeSize
     *   Number of Unicode characters in oUnicodeString.
     */
    static void ConvertStrToUcs( const char * iCodePageString, 
        int iStringLength, CATUC2Bytes * oUnicodeString, int * oUnicodeSize );

    /**
     * Converts a string from a the current code page to Unicode 2-Bytes.
     * @param iCodePageString
     *   Pointer to the string to be converted.
     * @param oUnicodeString
     *   Pointer to the resulting Unicode string. This string has no string-terminating 
     *   character.
     * @param oUnicodeSize
     *   Number of Unicode characters in oUnicodeString.
     */
    static void ConvertStrToUcs( const char * iCodePageString,
        CATUC2Bytes * oUnicodeString, int * oUnicodeSize )
    {
        ConvertStrToUcs(iCodePageString, CATPtrToINT32(strlen(iCodePageString)), oUnicodeString, oUnicodeSize);
    }

    /**
     * Converts a Unicode 2-Bytes string to the current code page 
     * @param iUnicodeString
     *   Pointer to the string to be converted.
     * @param iUnicodeSize
     *   Number of Unicode characters to be converted.
     * @param oCodePageString
     *   Pointer to the resulting code page string.
     * @param oStringLength
     *   Length of the resulting string.
     */
    static void ConvertUcsToStr( const CATUC2Bytes * iUnicodeString, 
        int iUnicodeSize, char * oCodePageString, int * oStringLength = NULL );

    /**
     * @deprecated R417. Use DSYSysUCAlgorithm::ConvertUTF16ToUTF8.
     */
    static int  ConvertUCS2ToUTF8( CATUC2Bytes * iUnicodeString, 
        int iUnicodeSize, char * oUTF8String, size_t * oUTF8Size );

    /**
     * @deprecated R417. Use DSYSysUCAlgorithm::ConvertUTF8ToUTF16 .
     */
    static int  ConvertUTF8ToUCS2( const char * iUTF8String, 
        size_t iUTF8Size, CATUC2Bytes *oUnicodeString, int *oUnicodeSize );

    /**
     * @deprecated R417. Use DSYSysConverter::ConvertToBase64.
     */
    static HRESULT ConvertToBase64( unsigned char* iBinaryBuffer,
        const unsigned int iLength, char*& oBase64Buffer );

    /**
     * @deprecated R417. Use DSYSysConverter::ConvertFromBase64.
     */
    static HRESULT ConvertFromBase64( const char* iBase64Buffer,
        unsigned char*& oBinaryBuffer, unsigned int& oBufferLength);
};
#endif  // _CATSysTSCodePage_H
