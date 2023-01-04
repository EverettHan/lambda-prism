#ifndef DSYSysStdIO_H
#define DSYSysStdIO_H
#include "DSYSysPath.h"
#include "JS0BASEILB.h"
#include "CATDataType.h"

class CATUnicodeString;

struct DSYSysFileDescriptor
{    
public:
    FILE * _fs;
    unsigned int _Id;       // Used to store the output Id from the DSYSYsRscManager

#ifndef _WINDOWS_SOURCE	
    char * _pathForUnlink;  // set only in case of temp file created manually
#endif
};

/**
 * DSYSysFOpen.
 * /!\ WARNING /!\ 
 * The CATUnicodeString version doesn't rely on DSYSysPath, it doesn't do any test on the canonical structure of iPath and may fail with a bad structured path (ex: "/" on win, ...).
 * For a safer DSYSysFOpen, the user may use the DSYSysPath version (see impl).
 * DO NOT USE char * version, since it is likely to fail under specific regional settings!
 * /!\ WARNING /!\ 
*/
HRESULT ExportedByJS0BASEILB DSYSysFOpen(const CATUnicodeString & iPath, const char *iMode, DSYSysFileDescriptor  & oFd, int tempfile = 0);
HRESULT ExportedByJS0BASEILB DSYSysFOpen(const char *  iPath, const char *iMode,DSYSysFileDescriptor & oFd, int tempfile = 0);
HRESULT ExportedByJS0BASEILB DSYSysFOpen(const DSYSysPath & iPath, const char *iMode, DSYSysFileDescriptor  & oFd, int tempfile = 0);

/**
 * DSYSysFClose.
 * Closes the file associated with iFileDesc and disassociates it.
 * @param [in] iFileDesc is a file descriptor returned by DSYSysFOpen.
 * @return S_OK upon success.
 * @return S_FALSE if iFileDesc is not associated with any file (anymore), for e.g. if it has already been closed.
 * @return E_FAIL in case of failure (Note that even in this case, iFileDesc will be invalidated).
 */
HRESULT ExportedByJS0BASEILB DSYSysFClose(DSYSysFileDescriptor & iFileDesc);

/**
 * DSYSysFRead.
 * Read block of data from stream.
 * Reads iSize bytes (at most) from the stream and stores them in the block of memory specified by oBuff.
 * @param [in]  iFileDesc is a file descriptor that specifies an input stream.
 * @param [out] oBuff is a pointer to a block of memory with a size of at least iSize bytes.
 * @param [in]  iSize is the size in bytes of the oBuff array.
 * @param [out] oRead is the total number of bytes read.
 * @return S_OK if at least 1 byte could be read from the stream without any error. At most, oRead equals iSize.
 * @return S_FALSE if there was nothing to be read (End of file) or if iSize is 0: oRead is set to 0.
 * @return an HRESULT error code if an error occurred (invalid file descriptor...).
 */
HRESULT ExportedByJS0BASEILB DSYSysFRead(DSYSysFileDescriptor & iFileDesc, char *oBuff, unsigned int iSize, unsigned int *oRead);

/**
 * DSYSysFWrite.
 * Write block of data to stream.
 * Writes an array of iSize bytes from the block of memory pointed by iBuff to the current position in the stream.
 * The position indicator of the stream is advanced by the total number of bytes written.
 * @param [in] iFileDesc is a file descriptor that specifies an output stream.
 * @param [in] iBuff is a pointer to the array to be written.
 * @param [in] iSize is the size in bytes of the array to be written.
 * @param [out] oWritten is the total number of bytes successfully written (optional).
 * @return S_OK if iSize bytes were successfully written.
 * @return S_FALSE if iSize is 0. In this case, oWritten is set to 0.
 * @return an HRESULT error code if an error occurred (invalid file descriptor...).
 */
HRESULT ExportedByJS0BASEILB DSYSysFWrite(DSYSysFileDescriptor & iFileDesc, const char *iBuff, unsigned int iSize, unsigned int *oWritten = NULL);


HRESULT ExportedByJS0BASEILB DSYSysFSeek (DSYSysFileDescriptor & iFileDesc, int iOffset, int iOrigin);
HRESULT ExportedByJS0BASEILB DSYSysFSeek (DSYSysFileDescriptor & iFileDesc, CATULONG64 iOffset, CATULONG64 iOrigin);


HRESULT ExportedByJS0BASEILB DSYSysFTell (DSYSysFileDescriptor & iFileDesc, unsigned int *oOffset);
HRESULT ExportedByJS0BASEILB DSYSysFTell (DSYSysFileDescriptor & iFileDesc, CATULONG64 *oOffset);


CATBoolean ExportedByJS0BASEILB DSYSysFEof(DSYSysFileDescriptor & iFileDesc);

HRESULT ExportedByJS0BASEILB DSYSysFSize (DSYSysFileDescriptor & iFileDesc, unsigned int * oSize);
HRESULT ExportedByJS0BASEILB DSYSysFSize (DSYSysFileDescriptor & iFileDesc, CATULONG64 * oSize);

#define DSYSysFCopy_KeepFileTime    0x01
/**
 * DSYSysFCopy.
 * Copy file which path is iName to path iCopyName.
 * @param [in] iName is the path to the file to copy. Note that directory copy is not supported!
 * @param [in] iCopyName is the path to the destination file.
 * @param [in] imode is 0 or one of the following flags:
 *             DSYSysFCopy_KeepFileTime: preserve file times
 * @return S_OK upon success.
 * @return an HRESULT error code if an error occurred (Access denied...).
 */
HRESULT ExportedByJS0BASEILB DSYSysFCopy (const DSYSysPath & iName, const DSYSysPath & iCopyName, int iMode = 0);
HRESULT ExportedByJS0BASEILB DSYSysFCopy (DSYSysFileDescriptor & iFdSource, DSYSysFileDescriptor & iFdCopy);

/**
 * DSYSysFGets.
 * Reads characters from iFileDesc and stores them as a C string into oBuff until (iNum-1) characters have been read or 
 * either a newline or the end-of-file is reached, whichever happens first.
 * A newline character makes fgets stop reading, but it is considered a valid character by the function and included in the string copied to oBuff.
 * A terminating null character is automatically appended after the characters copied to oBuff.
 * @param [out] oBuff is a pointer to an array of chars where the string read is copied.
 * @param [in]  iNum is the maximum number of characters to be copied into oBuff (including the terminating null-character).
 * @param [in]  iFileDesc is a file descriptor that specifies an input stream.
 * @return S_OK if one or more characters have been read.
 * @return S_FALSE if end-of-file has been reached.
 * @return an HRESULT error code if an error occurred (invalid file descriptor...).
 */
HRESULT ExportedByJS0BASEILB DSYSysFGets (char * oBuff, int iNum, DSYSysFileDescriptor & iFileDesc);

HRESULT ExportedByJS0BASEILB DSYSysFPuts (const char * iBuff, DSYSysFileDescriptor & iFileDesc, int *oWritten);

/**
 * DSYSysFGetc.
 * Returns the character currently pointed by the internal file position indicator of the specified descriptor iFileDesc.
 * The internal file position indicator is then advanced to the next character.
 * @param [in]  iFileDesc is a file descriptor that specifies an input stream.
 * @param [out] oCar is a pointer to an integer that will hold the character read.
 * @return S_OK if a character has been read.
 * @return S_FALSE if end-of-file has been reached.
 * @return an HRESULT error code if an error occurred (invalid file descriptor...).
 */
HRESULT ExportedByJS0BASEILB DSYSysFGetc (DSYSysFileDescriptor & iFileDesc, int *oCar);

HRESULT ExportedByJS0BASEILB DSYSysFPutc (DSYSysFileDescriptor & iFileDesc, int iCar);

HRESULT ExportedByJS0BASEILB DSYSysFFlush(DSYSysFileDescriptor & iFileDesc);

HRESULT ExportedByJS0BASEILB DSYSysFTruncate(DSYSysFileDescriptor & iFileDesc, CATULONG64 iOffset);

/**
 * DSYSysCreateTempFile.
 * Create and open a unique temporary file and return its file descriptor.
 * Optionally, the file's name can be prefixed by iPrefix.
 * @param [out] oFd file descriptor
 * @param [in,out] ioPath 
 *                 on input, if valid, specify the directory in which the temporary file is to be created. Otherwise,
 *                 the default temporary directory will be used.
 *                 on output, if the function succeeds, contains the path to the temporary file newly created
 * @param [in] iPrefix an optional prefix for the temporary file name. 
 * @return S_OK upon success
 * @return an HRESULT error code if an error occurred.
 */
HRESULT ExportedByJS0BASEILB DSYSysCreateTempFile(DSYSysFileDescriptor & oFd, DSYSysPath & ioPath, const CATUnicodeString * iPrefix = NULL);

#endif  // DSYSysStdIO_H
