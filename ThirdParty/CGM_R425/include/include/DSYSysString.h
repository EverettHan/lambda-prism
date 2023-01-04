#ifndef DSYSysString_H
#define DSYSysString_H

// COPYRIGHT DASSAULT SYSTEMES 2009

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#ifdef _WINDOWS_SOURCE
# define DSYSysStrToUChar                                         DSYSysStrToWChar
#else   // _WINDOWS_SOURCE
# define DSYSysStrToUChar                                         DSYSysStrToUTF8
#endif  // _WINDOWS_SOURCE

#ifdef DSYSysStringConvertToUTF8
# undef DSYSysStringConvertToUTF8
#endif  //  DSYSysStringConvertToUTF8
#define DSYSysStringConvertToUTF8                                 DSYSysStrToUTF8

/************************************************************************/
/* Global includes                                                      */
/************************************************************************/
#include <stdio.h>
#include <stdarg.h>

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATSysTS.h"
#include "DSYSysCommon.h"

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/** @class CATUnicodeString */
class CATUnicodeString;

/************************************************************************/
/* Functions prototypes                                                 */
/************************************************************************/

//=======================================================================
/**
 * Copy a C-string to another C-string buffer
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 *
 * @return                        0 on success, -1 on error.
 */
ExportedByCATSysTS int DSYSysStrCpy(char* opDst, size_t iDstSize, const char* ipSrc);
//=======================================================================

//=======================================================================
/**
 * Copy a C-string to a wide-char string buffer
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 *
 * @return                        0 on success, -1 on error.
 */
ExportedByCATSysTS int DSYSysStrCpy(wchar_t* opDst, size_t iDstSize, const _DSYSysUTF8_(char)* ipSrc);
//=======================================================================

//=======================================================================
/**
 * Copy  a wide-char to a C-string string buffer
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 *
 * @return                        0 on success, -1 on error.
 */
ExportedByCATSysTS int DSYSysStrCpy(_DSYSysUTF8_(char)* opDst, size_t iDstSize, const wchar_t* ipSrc);
//=======================================================================

//=======================================================================
/**
 * Copy a wide-char string to a wide-char string buffer
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 */
ExportedByCATSysTS int DSYSysStrCpy(wchar_t* opDst, size_t iDstSize, const wchar_t* ipSrc);
//=======================================================================

//=======================================================================
/**
 * Append a C-string to another C-string buffer.
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 */
ExportedByCATSysTS int DSYSysStrCat(char* opDst, size_t iDstSize, const char* ipSrc);
//=======================================================================

//=======================================================================
/**
 * Append a wide-char string to a wide-char string buffer
 *
 * @param opDst       Location of destination string buffer
 * @param iDstSize    Size of the destination string buffer
 * @param ipSrc       Null-terminated source string buffer
 */
ExportedByCATSysTS int DSYSysStrCat(wchar_t* opDst, size_t iDstSize, const wchar_t* ipSrc);
//=======================================================================

/************************************************************************/
/************************************************************************/

/**
 * Return token extracted from string
 * /!\ Input string is modified /!\
 *
 * @param iStrPtr       Input string
 * @param iDelim        char array of delimiters
 *
 * @return              the next token extracted (points into the iStrPtr buffer)
 */
ExportedByCATSysTS char* DSYSysStrSep(char** ippStrPtr, const char* ipDelim);

/*
* Stub to ExportedByCATSysTS
*/
ExportedByCATSysTS char * CATSysStrtokLegacy( char * orig, const char * sep, char ** ptr);

/************************************************************************/
/************************************************************************/

//=======================================================================
/** @nodoc */
ExportedByCATSysTS int DSYSysStrToUTF8(_DSYSysUTF8_(char)* opString, const size_t iString, CATUnicodeString& iUnicodeString);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS _DSYSysUTF8_(char)* DSYSysStrToUTF8(const CATUnicodeString& irUnicodeString);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS _DSYSysUTF8_(char)* DSYSysStrToUTF8(const wchar_t* ipPathW);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS wchar_t* DSYSysStrToWChar(const CATUnicodeString& irUnicodeString);
//=======================================================================

//=======================================================================
/** @nodoc */
ExportedByCATSysTS int DSYSysStrBuildU(CATUnicodeString& orUnicodeString, const DSYSysUChar_t* ipString);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
extern "C" ExportedByCATSysTS char* DSYSysStrFormatAlloc(const char * ipFormat, ...);
//=======================================================================

#endif  // DSYSysString_H
