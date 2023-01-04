#ifndef DSYSysConverter_H
#define DSYSysConverter_H

#include "CATSysTS.h"
#include "IUnknown.h"
// TODO: relpace IUnknown header by CATSysErrorDef only.
// #ifndef _HRESULT_DEFINED
    // #define _HRESULT_DEFINED
    // #include "CATSysErrorDef.h"
// #endif
#ifdef _SUNOS_SOURCE
    #include <string.h>
#else
    #include <cstddef>
#endif

namespace DSYSysConverter
{
    /**
    * Converts a binary buffer to a base-64 string.
    * <br><b>Role</b>: Converts a binary buffer to a base-64 string. 
    * About the base-64 conversion, see
    * @href CATCodePage#ConvertFromBase64 .
    * @param iBinaryBuffer
    *   The binary buffer to convert
    * @param iLength
    *   Length of iBinaryBuffer, in bytes
    * @param oBase64Buffer
    *   Base-64 string resulting from the conversion of iBinaryBuffer. 
    *   oBase64Buffer is allocated by the callee with the
    *   new operator, and it must be deallocated by the caller using delete[]
    */
    ExportedByCATSysTS HRESULT ConvertToBase64(const unsigned char *iBinaryBuffer, size_t iLength, char *&oBase64Buffer);

    /**
    * Converts a base-64 string to a binary buffer.
    * <br><b>Role</b>: Converts a base-64 string to a binary buffer. 
    * <br> The base-64 conversion enables, as the hexadecimal encoding, 
    * to encode a binary buffer in a clear-text string,
    * but the resulting string is shorter than using the hexadecimal encoding.
    * The following character set is used:
    * <ul>
    * <li>A - Z</li>
    * <li>a - z</li>
    * <li>0 - 9</li>
    * <li>+</li>
    * <li>/</li>
    * <li>=</li>
    * </ul>
    * @param iBase64Buffer
    *   The base-64 string to convert
    * @param oBinaryBuffer
    *   The binary buffer resulting from the conversion of iBase64Buffer.
    * oBinaryBuffer is allocated by the callee with the
    *   new operator, and the must ne deallocated by the caller using delete[]
    * @param oBufferLength
    *   Length of oBinaryBuffer, in bytes.
    */
    ExportedByCATSysTS HRESULT ConvertFromBase64(const char *iBase64Buffer, unsigned char *&oBinaryBuffer, size_t &oBufferLength);
}

#endif  // DSYSysConverter_H
