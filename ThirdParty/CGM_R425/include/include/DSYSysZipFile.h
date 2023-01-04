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
#ifndef DSYSysZipFile_H
#define DSYSysZipFile_H
#include <time.h>
#include "JS0ZLIB.h"

#include "CATMutex.h"
#include "CATILockBytes2.h"
#include "DSYSysMultiBuffer.h"
#include "CATSysDataType.h" // CATUC2Bytes


class DSYSysPath;

/**
 * Flag for @href #CATSysZip for appening files in an archive
 */
#define CATSYSZIP_APPEND		       0x1
/**
 * Flag for  for overwriting files in an archive
 */
#define CATSYSZIP_OVERWRITE	       0x2
/**
 * Flag for @href #ExtractAll for overwriting files in an archive
 */
#define CATSYSUNZIP_OVERWRITE	       0x1
/**
 * Flag for @href #ExtractAll for extarcting with saved paths
 */
#define CATSYSUNZIP_WITH_PATH	       0x10



/**
 * Type of access on zip archive.
 * @param CATSysZip_OpenNew
 *        To create a new archive. If a file already exist, it will be totally
 *        overwritten.
 * @param CATSysZip_Append
 *        To open a archive for adding new entries.
 * @param CATSysZip_Extract
 *        To open an existing archive for extraction.
 */
enum CATSysZipOpenMode {
            CATSysZip_OpenNew       = 0x00000001,
            CATSysZip_Append        = 0x00000002,
            CATSysZip_Extract       = 0x00000003,
            CATSysZip_ExtractShared = 0x00000004,
            CATSysZip_ReadCopy      = 0x10000000,
            CATSysZip_ReadWrite     = 0x01000000
};


/**
 * Flags for opening zip archive.
 * @param  DSYZIP_LF support of Large File
 */
#define DSYZIP_LF  0x00000001
/**
 * Flags for opening zip archive.
 * @param  DSYZIP_3MF support of 3MF format: Unicode support for entry names + generate entries for directories
 */
#define DSYZIP_3MF 0x00000010
/**
 * Flags for opening zip archive.
 * @param   DSYZIP_NO_DRM
 */
#define DSYZIP_NO_DRM 0x00000100

class CATUnicodeString;
class CATSysTSUnicodeString;    // TODO RM
class CATSysZipFd;
class CATSysSimpleHashTable;
class CATSysZipLockBytes2;

/**
*Information structure about files in a zip archive.
*used to get information about the file currently open in the archive.
*/
typedef struct fz_info_s
{
    unsigned int crc;
    unsigned int size;
	unsigned int zipSize;
	char  name[4096];
} fz_info;

/**
 * Class for managing compressed archives.
 * <br><b>Role</b>: DSYSysZipFile manages archives of compressed files 
 * following the .ZIP file format specification defined and published
 * by PKWARE (R). 
 */
class  ExportedByJS0ZLIB DSYSysZipFile 
{
 public:

   
/**
 * Opens or creates an archive.
 * To be used in a multithreaded context. Thread safe.

 * When a DSYSysZipFile is opened in CATSysZip_ReadWrite mode, the underlying code first opens it in 
 * CATSysZip_ExtractShared mode then the Switch method is used to reopen it in CATSysZip_Append/CATSysZip_OpenNew 
 * modes and to fall back to read modes  (CATSysZip_Extract/CATSysZip_ExtractShared).
 * During the lifecycle of the DSYSysZipFile opened in CATSysZip_ReadWrite mode, it cannot be opened anymore 
 *  (the OpenZip method will then return a STG_E_SHAREVIOLATION error) except in CATSysZip_ReadCopy mode which allows the 
 * calling code to work on a separate copy of the zip archive. 
 * 
 * The CATSysZip_ReadCopy is used to open a zip archive and work on a separate temporary copy created in the $CATTemp directory. 
 * The temporary copy is deleted when the archive is closed.
 * When the archive has been opened otherwise in CATSysZip_OpenNew or CATSysZip_Append mode the OpenZip in CATSysZip_ReadCopy mode will fail.
 * When it has been opened in CATSysZip_ReadWrite mode, it will succeed only if no switch has been made or if the last switch was made to 
 * CATSysZip_Extract or CATSysZip_ExtractShared modes.
 * <br><b>Role</b>: 
 * @param iPath
 *   the path of the archive
 * @param iMode
 *   Opening mode.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				       incomplete.
 *   <br><tt> CATZ_FILENOTFOUND:</tt> if the archive was not found.
 *   <br><tt> @hrefCATFRead return code :</tt> if some IO error occured.
*/ 
	virtual HRESULT OpenZip(DSYSysPath & iPath, CATSysZipOpenMode iMode,int iFlags = 0 ) = 0;
/**
 * Opens or creates an archive from memory.
 * Thread unsafe
 * <br><b>Role</b>: 
 * @param ioMLB
 *   the CATSysMultiBuffer where the archive is or should be stored
 * @param iMode
 *   Opening mode.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				       incomplete.
 *   <br><tt> CATZ_FILENOTFOUND:</tt> if the archive was not found.
 *   <br><tt> @hrefCATFRead return code :</tt> if some IO error occured.
*/
  virtual HRESULT  OpenZip( DSYSysMultiBuffer * ioMLB , CATSysZipOpenMode iMode, int iFlag = 0) = 0;

    
	
/**
 * Parses the content of an archive.
  *Thread safe.
 * <br><b>Role</b>: Parses the content of a zip file.
 * @param oList
 *   the list of files compressed inside the archive.
 * @param oNb
 *   number of files in the zip file.
 * @param oSize
 *   the list of original sizes of the files inside the archive. Can be null
 *   if the information is not required.
 * @param oZipSize
 *   the list of original sizes of the files inside the archive. Can be null
 *   if the information is not required.
 * @param oTime
 *   the list of last modification time of the files inside the archive. 
 *   Can be null if the information is not required.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_INVALIDFUNCTION:</tt> if the file is not opened for
 *					   extraction or not opened at all.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if oList or oNb is null.
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive is corrupted.
*/			   
	virtual HRESULT  BrowseZip ( CATUC2Bytes ** & oList,
	       unsigned int *oNb,
	       size_t **oSize,
	       size_t **oZipSize,
	       time_t **oTime) = 0;		   

    /**
     * @deprecated R417 BrowseZip.
     * Use the signature with CATUnicodeString.
     */
    virtual HRESULT  BrowseZip ( CATSysTSUnicodeString ** oList,
	       unsigned int *oNb,
	       size_t **oSize,
	       size_t **oZipSize,
	       time_t **oTime) = 0;
/**
 * Opens a file in the archive.
 *Thread safe.
 * <br><b>Role</b>: Opens a file in the archive for writing or reading.
 * depending on the opening mode that has been passed to @href #OpenZip.
 * Due to the zip format only one file can be opened inside an archive a given
 * time. A subsequent call to this methods on a new file, will first close the
 * current one.
 * @param iName
 *   the name of the entry in the archive.
 * @param iLevel
 *    The compression level. This argument is ignored if the archive is opened
 *    for extraction.
 *    It  must be between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param iFlag
 * 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				    incomplete.
 *   <br><tt> CATZ_E_FILENOTFOUND:</tt> if no file has been found with the 
 *                                      given name.
 */		 
  virtual HRESULT OpenFileInZip ( CATUC2Bytes *iName, int iLevel, DWORD iFlag =0 ) = 0;

/**
 * @deprecated R417 OpenFileInZip.
 * Use the signature with CATUnicodeString.
 */
  virtual HRESULT OpenFileInZip (CATSysTSUnicodeString & iName, int iLevel, DWORD iFlag =0 ) = 0;
/**
 * Opens a file in the archive.
 *Thread safe.
 * <br><b>Role</b>: Opens a file in the archive for reading. Returns a pointer 
 * on an ILockBytes2 object containing the uncompressed data in memory that 
 *can   be read using ILockBytes2 methods.  
 * This method can be used in a multithreaded context to open multiple ILockBytes2 objects in multiple threads. 
 *Each object can then be used to read unzipped data in a separate thread. 
 * @param iName
 *   the name of the entry in the archive.
 * @param iLevel
 *    The compression level. This argument is ignored if the archive is opened
 *    for extraction.
 *    It  must be between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied).
 * @param iFlag
 * 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				    incomplete.
 *   <br><tt> CATZ_E_FILENOTFOUND:</tt> if no file has been found with the 
 *                                      given name.
 */	
  virtual HRESULT OpenFileInZip (CATUC2Bytes *iName, int iLevel,  DWORD iFlag , CATILockBytes2 *& opZLB) = 0;
	
/**
 * @deprecated R417 OpenFileInZip.
 * Use the signature with CATUnicodeString.
 */
  virtual HRESULT OpenFileInZip (CATSysTSUnicodeString & iName, int iLevel,  DWORD iFlag , CATILockBytes2 *& opZLB) = 0;
/**
 * Closes an archive.
 * <br><b>Role</b>: Closes the archive.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   tbd
*/
  virtual HRESULT Close(DWORD iFlag = 0)=0;  
  
	
/**
 * Writes a buffer in the archive.
 *Thread unsafe.
 * <br><b>Role</b>: Writes a buffer into the file that have been opened before
 * with @href #OpenFileInZip. The archive must have been open in 
 * @href #CATSysZip_OpenNew or @href #CATSysZip_Append mode.
 * @param iBuff
 *    the data to be written
 * @param iLen
 *     the length of the data to be written.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDFUNCTION :</tt> if the archive is not opened for
 *					    writing or no file has been yet
 *                                          opened with OpenFileInZip.
*/
  virtual HRESULT AddBufferInZip ( char *iBuff, size_t iLen ) = 0;

/**
 * Reads data in the archive.
 *Thread unsafe.
 * <br><b>Role</b>: Reads data from the file that have been opened before
 * with @href #OpenFileInZip. The archive must have been open in 
 * @href #CATSysZip_Extract.
 * @param ioBuff
 *    the buffer where the data will be written
 * @param iLen
 *     the length of the buffer.
 * @param ioRead
 *     the length of data actually copied.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDFUNCTION :</tt> if the archive is not opened for
 *					    writing or no file has been yet
 *                                          opened with OpenFileInZip.
*/
  virtual HRESULT ReadBufferInZip ( char *ioBuff, size_t iLen, size_t *oRead ) = 0;

/**
 * Close a file in the archive.
 * Thread unsafe
 * <br><b>Role</b>: Close the current file  that has been open with 
 * @href #OpenZip.
 * Due to the zip format only one file can be opened inside an archive a given
 * time. A subsequent call to this methods on a new file, will first close the
 * current one.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_FILENOTFOUND:</tt> if no file has been yet opened.
 */
    virtual HRESULT CloseFileInZip( ) = 0;
	

/**
 * Adds files into an archive.
 *Thread Unsafe.
 * <br><b>Role</b>: 
 * @param iList
 *   the list of path of the files to add.
 * @param iNb
 *   number of files to add.
 * @param iLevel
 *    The compression level.
 *    It  must be between 0 and 9:
 *    1 gives best speed, 9 gives best compression, 0 gives no compression at
 *    all (the input data is simply copied a block at a time).
 * @param iBaseDir
 *    The path of directory. If the added files are in a sub directory of 
 *    iBaseDir the stored path will be only relative to iBaseDir and not 
 *    absolut.
 * @param iFlag
 * 
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				    incomplete.
*/
  virtual HRESULT AddFile( DSYSysPath * iList, unsigned int iNb,
	int iLevel, DSYSysPath * iBaseDir=NULL, 
	DWORD iFlag=0) = 0;
		   
/**
* Adds a directory into an archive.
*Thread Unsafe.
* <br><b>Role</b>: Adds a whole directories arborescence into the archive. 
* @param iDir
*   the path of the directory
* @param iLevel
*    The compression level.
*    It  must be between 0 and 9:
*    1 gives best speed, 9 gives best compression, 0 gives no compression at
*    all (the input data is simply copied a block at a time).
* @param iFlag
* 
* @return
*   <b>Legal values</b>:
*   <br><tt> S_OK :</tt>on Success.
*   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory.
*   <br><tt> CATZ_E_INVALIDARG :</tt> if arguments are not valid.
*   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
*				    incomplete.
*/
	virtual HRESULT AddDirectory( DSYSysPath & iDirectory, int iLevel,
	DSYSysPath * iBaseDir=NULL, 
	DWORD iFlag=0) = 0;
	
/**
 * Decompresses an archive
  *Thread Unsafe.
 * <br><b>Role</b>: 
 * @param iExtractDir
 *   the path of the directory where files will be extracted to.
 * @param iFlag
 *   mode of the extraction that is a ORING of the following flags:
 *   CATSYSUNZIP_OVERWRITE for overwriting files at the extraction
 *   CATSYSUNZIP_WITH_PATH for recreating the arborescence.
 * @param oNb
 *   Number of files actually extracted.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INSUFFICIENTBUFFER:</tt> if there was not enough room 
 *					      in the output buffer
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if iExtractDir is NULL
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
 *				    incomplete.
*/
	virtual HRESULT ExtractAll ( DSYSysPath &iExtractDir, DWORD iFlag,
	unsigned int *oNb=NULL)= 0; 

/**
 * Decompresses a specific file.
  *Thread Unsafe.
 * <br><b>Role</b>: Decompress a specific file from the archive. 
 * @param iPath
 *   the file path of the zip file 
 * @param iExtractDir
 *   the path of the directory where files will be extracted to.
 * @param iFile
 *   the name of the file to be extracted.
 * @param iFlag
 *   mode of the extraction that is a ORING of the following flags:
 *   CATSYSUNZIP_OVERWRITE for overwriting files at the extraction
 *   CATSYSUNZIP_WITH_PATH for recreating the arborescence.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_OUTOFMEMORY :</tt> if there was not enough memory
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if iExtractDir is NULL.
 *   <br><tt> CATZ_E_FILENOTFOUND:</tt> if no file has been found with the 
 *                                      given name.
 *   <br><tt> CATZ_E_BADDATA :</tt> if the archive was corrupted or 
  *				    incomplete.
 */

    /**
     * @deprecated R417 ExtractFile.
     * Use the signature with CATUnicodeString.
     */
    virtual HRESULT ExtractFile (  DSYSysPath &iExtractDir, CATSysTSUnicodeString & iFile, 
									DWORD iFlag ) = 0;
/**
 * <br><b>Role</b>: Change modes on a DSYSysZipFile object that was opened in CATSysZip_ReadWrite mode.
 * When a DSYSysZipFile is opened in CATSysZip_ReadWrite mode, the underlying code first opens it in 
 * CATSysZip_ExtractShared mode then the Switch method is used to reopen it in CATSysZip_Append/CATSysZip_OpenNew 
 * modes and to fall back to read modes  CATSysZip_Extract/CATSysZip_ExtractShared. 
 * @param iMode
 *   The desired mode for the switch. Only the following modes can be used here: 
 *                       CATSysZip_OpenNew	, CATSysZip_Append	, CATSysZip_Extract	, CATSysZip_ExtractShared.
 *     
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> CATZ_E_INVALIDARG :</tt> if a wrong mode was required. Or values returned by the OpenZip or Close methods 
 */
  virtual HRESULT SwitchMode(CATSysZipOpenMode iMode) = 0;

  /**
* Commits the modifications that were written to a zip archive opened in Append modes.
*     
* @return
*   Fails when modifications cannot be written.
*/
  virtual HRESULT Commit() = 0;
	
/**
 *Returns an fz_info structure about the file that is currently open in the zip archive
 * Thread unsafe
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> E_FAIL</tt> if file or archive is not opened.
 */	
	virtual HRESULT GetCurrentInfo(fz_info * oInfo) = 0;
	
	
	virtual ~DSYSysZipFile() {};

    // ++IK8 - New CUS-based signatures
public:
    virtual HRESULT  BrowseZip ( CATUnicodeString ** oList,
               unsigned int *oNb,
               size_t **oSize,
               size_t **oZipSize,
               time_t **oTime) = 0;
    virtual HRESULT OpenFileInZip (const CATUnicodeString & iName, int iLevel, DWORD iFlag =0 ) = 0;
    virtual HRESULT OpenFileInZip (const CATUnicodeString & iName, int iLevel,  DWORD iFlag , CATILockBytes2 *& opZLB) = 0;
    virtual HRESULT ExtractFile (  DSYSysPath &iExtractDir, const CATUnicodeString & iFile, 
                                        DWORD iFlag ) = 0;
    // ++IK8 - New CUS-based signatures

#if defined(_WINDOWS_SOURCE)    // Signatures provided for Native wchar_t support
    virtual HRESULT  BrowseZip (WCHAR ** & oList,
	       unsigned int *oNb,
	       size_t **oSize,
	       size_t **oZipSize,
	       time_t **oTime) = 0;
    virtual HRESULT OpenFileInZip (WCHAR *iName, int iLevel, DWORD iFlag =0 ) = 0;
    virtual HRESULT OpenFileInZip (WCHAR *iName, int iLevel, DWORD iFlag , CATILockBytes2 *& opZLB) = 0;
#endif
	
};


#endif /* ZLIB_H */
