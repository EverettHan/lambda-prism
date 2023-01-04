//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2004                                          *
//*===========================================================================*
//*                                                                           *
//*  Compression		                                              *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation decembre 2004                                  adt              *
//*===========================================================================*
#ifndef DSYSysCompress_H
#define DSYSysCompress_H
#include "JS0ZLIB.h"
#include "JS0COMP.h"

#include "DSYSysZipErrorDef.h"
#include "CATSysDataType.h" // CATUC2Bytes

#ifdef __cplusplus
extern "C" {
#endif
  


/**
 *  Compresses a buffer.
 * <br><b>Role</b>: Compresses the source buffer into the destination buffer.
 * iSourceLen is the byte length of the source buffer. Upon entry, ioDestLen is
 * the total size of the destination buffer, which must be at least the value
 * returned by @href #CATSysCompressBound . Upon exit, ioDestLen is the actual 
 * size of the compressed buffer.
 * @param iSource
 *   the buffer to compress
 * @param iSourceLen
 *   the byte length of the source buffer
 * @param ioDest
 *   the destination buffer
 * @param ioDestLen
 *   the  byte length of the destination buffer 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER:</tt> if there was not enough room 
 *					      in the output buffer
*/
  HRESULT ExportedByJS0ZLIB CATSysCompress ( const char* iSource, 
					     size_t iSourceLen,
					     char *ioDest, size_t *ioDestLen);

/**
 *  Compresses a buffer.
 * <br><b>Role</b>: Compresses the source buffer into the destination buffer.
 * iSourceLen is the byte length of the source buffer. Upon entry, ioDestLen is
 * the total size of the destination buffer, which must be at least the value
 * returned by @href #CATSysCompressBound . Upon exit, ioDestLen is the actual 
 * size of the compressed buffer.
 * @param iSource
 *   the buffer to compress
 * @param iSourceLen
 *   the byte length of the source buffer
 * @param iLevel
 *    The compression level.
 *    It  must be between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param ioDest
 *   the destination buffer
 * @param ioDestLen
 *   the  byte length of the destination buffer 
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER:</tt> if there was not enough room 
 *					      in the output buffer
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if the level is not correct.
*/
  HRESULT ExportedByJS0ZLIB CATSysCompress2(const char* iSource, 
					    size_t iSourceLen,
					    int iLevel, char *ioDest,
					    size_t *ioDestLen);

/**
 *  Compresses a buffer.
 * <br><b>Role</b>: Compresses the source buffer into the destination buffer.
 * iSourceLen is the byte length of the source buffer. Upon entry, ioDestLen is
 * the total size of the destination buffer, which must be at least the value
 * returned by @href #CATSysCompressBound . Upon exit, ioDestLen is the actual 
 * size of the compressed buffer.
 * This method has to be used in conjunction with @href #CATSysUncompressEx.
 * @param iSource
 *   the buffer to compress
 * @param iSourceLen
 *   the byte length of the source buffer
 * @param iLevel
 *    The compression level.
 *    It  must be between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param ioDest
 *   the destination buffer
 * @param ioDestLen
 *   the  byte length of the destination buffer 
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER:</tt> if there was not enough room 
 *					      in the output buffer
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if the level is not correct.
*/
  HRESULT ExportedByJS0ZLIB CATSysCompressEx(const char* iSource, 
					    size_t iSourceLen,
					    int iLevel, char *ioDest,
					    size_t *ioDestLen);

/**
 *  Returns an upper bound on the compressed size.
 * <br><b>Role</b>: Returns an upper bound on the compressed size after a 
 * @href #CATSysCompress or @href #CATSysCompress2 on iSourceLen bytes.
 * @param iSourceLen
 *   the byte length of the source buffer
 * @return
 *   an upper bound on the compressed size
*/
  size_t ExportedByJS0ZLIB CATSysCompressBound (size_t iSourceLen); 



/**
 * Decompresses a buffer.
 * <br><b>Role</b>: Decompresses the source buffer into the destination buffer.
 * iSourceLen is the byte length of the source buffer. Upon entry, ioDestLen is
 * the total size of the destination buffer,which must be large enough to hold
 * the entire uncompressed data. (The size of the uncompressed data must have
 * been saved previously by the compressor and transmitted to the decompressor
 * by some mechanism outside the scope of this compression library.).
 * Upon exit, ioDestLen is the actual size of the compressed buffer.
 * @param iSource
 *   the buffer to compress
 * @param iSourceLen
 *   the byte length of the source buffer
 * @param ioDest
 *   the destination buffer
 * @param ioDestLen
 *   the  byte length of the destination buffer 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER :</tt> if there was not enough room 
 *                                             in the output  buffer
 *   <br><tt> CATZ_E_BADDATA:</tt> if the input data was corrupted or 
 *				   incomplete.
*/
  HRESULT ExportedByJS0ZLIB CATSysUncompress(const char *iSource, 
					     size_t iSourceLen,
					     char *ioDest,size_t *ioDestLen);



/**
 * Decompresses a buffer.
 * <br><b>Role</b>: Decompresses the source buffer into the destination buffer.
 * iSourceLen is the byte length of the source buffer. The size of the 
 * uncompressed data has been saved previously by  @href #CATSysCompressEx
 * Upon exit, oDestLen is the actual size of the compressed buffer.
 * @param iSource
 *   the buffer to compress
 * @param iSourceLen
 *   the byte length of the source buffer
 * @param oDest
 *   the destination buffer which is allocated by this function. The caller
 *   is in charge of its desallocation with a delete call.
 * @param oDestLen
 *   the  byte length of the destination buffer 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER :</tt> if there was not enough room 
 *                                             in the output  buffer
 *   <br><tt> CATZ_E_BADDATA:</tt> if the input data was corrupted or 
 *				   incomplete.
*/
  HRESULT ExportedByJS0ZLIB CATSysUncompressEx(const char *iSource, 
					       size_t iSourceLen,
					       char *& oDest,
					       size_t *ioDestLen);


/**
 * Compresses a file.
 * <br><b>Role</b>: Compresses a file. The file is compressed in place in the
 * same directory and is named iName.iExt.
 * @param iName
 *   the name of the file to compress
 * @param iLevel
 *    The compression level.
 *    It  must be or between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param iExt
 *   the extension to be used
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if the level is not correct.
*/
  HRESULT ExportedByJS0ZLIB DSYSysCompressFile(const CATUC2Bytes * iName, 
						int iLevel, 
						const char *iExt=".gz");
					
					
/**
 * Compresses a file.
 * <br><b>Role</b>: Compresses a file. The file is compressed in the
 * same directory and is named iName.iExt.
 * @param iName
 *   the name of the file to compress
 * @param iLevel
 *    The compression level.
 *    It  must be or between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param iMode
 *   <b>Legal values</b>:
 *   <br><tt> 0 :</tt> the file is compressed in place, thus the original
 *                     uncompressed file is deleted.
 *   <br><tt> 1:</tt>  the file is compressed but the original file remains
 * @param iExt
 *   the extension to be used
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if the level is not correct.
*/
  HRESULT ExportedByJS0ZLIB DSYSysCompressFileEx(const CATUC2Bytes * iName, 
						  int iLevel, int iMode,
						  const char *iExt="gz");					
/**
 * Decompresses a file.
 * <br><b>Role</b>: Decompresses a file. The file is decompressed in place in 
 * the same directory and is named iName less the extension.
 * @param iName
 *   the name of the file to compress
 * @param iExt
 *   the extension that has been used
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if the path is null or if the extension
 *                                     does not match.
 */
HRESULT ExportedByJS0ZLIB DSYSysUncompressFile(const CATUC2Bytes * iName, 
						const char *iExt="gz");




CATULONG32 ExportedByJS0ZLIB CATSysCRC32( const char *buf,   size_t len);



HRESULT ExportedByJS0ZLIB DSYSysMakeCRC32(const CATUC2Bytes * iFilePath, CATULONG32 * oCRC);


#ifdef __cplusplus
}
#endif




#endif /* ZLIB_H */

