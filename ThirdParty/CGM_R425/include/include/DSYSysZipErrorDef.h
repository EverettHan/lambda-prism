#ifndef DSYSysZipErrorDef_H
#define DSYSysZipErrorDef_H

#include "CATSysErrorDef.h"
#include "CATWTypes.h"

#if !defined(_WINDOWS_SOURCE)
# include <errno.h> // EBADF
#endif  // !_WINDOWS_SOURCE


/* errors code*/
/**
 * facilty compression
 */
#define FACILTIY_CATZLIB		0xFFE
/**
 * Unable to execute the operation in this context
 */
#define CATZ_E_INVALIDFUNCTION		_HRESULT_TYPEDEF_(0x8FFE0001L)
/**
 * Unable to find a archive file or a file inside an archive
 */
#define CATZ_E_FILENOTFOUND		_HRESULT_TYPEDEF_(0x8FFE0002L)
/**
 * Unable to find the files to add in a archive
 */ 
#define CATZ_E_PATHNOTFOUND		_HRESULT_TYPEDEF_(0x8FFE0003L)
/**
 * Not enough Memory
 * ERROR_NOT_ENOUGH_MEMORY for the facility compression
 */
#define CATZ_E_OUTOFMEMORY		_HRESULT_TYPEDEF_(0x8FFE0008L)
/**
 * Incorrect version
 */
#define CATZ_E_INVALIDVERSION		_HRESULT_TYPEDEF_(0x8FFE000BL)
/**
 * Invalid or corrupted data 
 * ERROR_INVALID_DATA for the facility compression
 */
#define CATZ_E_BADDATA	 		_HRESULT_TYPEDEF_(0x8FFE000DL)
/**
 * Writing error in a gzip file 
 */
#define CATZ_E_WRITEFAULT		_HRESULT_TYPEDEF_(0x8FFE001DL)
/**
 * Invalid password for the current zip file
 */
#define CATZ_E_INVALIDPASSWORD		_HRESULT_TYPEDEF_(0x8FFE0056L)
/**
 * Invalid argument
 * ERROR_INVALID_PARAMETER for the facility compression
 */
#define CATZ_E_INVALIDARG		_HRESULT_TYPEDEF_(0x8FFE0057L)
/**
 * Insufficient buffer size 
 */
#define CATZ_E_INSUFFICIENTBUFFER	_HRESULT_TYPEDEF_(0x8FFE007AL)
/**
 * File name already exists in archive
 */
#define CATZ_E_ALREADYEXISTS	_HRESULT_TYPEDEF_(0x8FFE00B7L)



#define CATSYSZ_NO_COMPRESSION         0x0
#define CATSYSZ_BEST_SPEED             0x1
#define CATSYSZ_BEST_COMPRESSION       0x9
#define CATSYSZ_DEFAULT_COMPRESSION    0x6


#ifdef _WINDOWS_SOURCE
#define ERRNO		GetLastError()
#define INVALIDFD	ERROR_INVALID_HANDLE
#else
#define ERRNO		errno
#define INVALIDFD	EBADF
#endif 


// Pour passer facilement en HRESULT
// pour ne pas modifier les codes d'erreur de la zlib on se remappe
// sur des erreur standard win32 avec une facilite Zlib que l'on cree
// Si err =-1 Z_ERRNO cela signifie que l'erreur est une erreur systeme
// et non liee a la zlib
static const int HRZLIB[9] ={ S_OK, S_OK, S_OK, E_FAIL, CATZ_E_INVALIDARG,
		     CATZ_E_BADDATA, CATZ_E_OUTOFMEMORY, 
		     CATZ_E_INSUFFICIENTBUFFER, CATZ_E_INVALIDVERSION };

#define Z_ERR_HR(err)   (((err) != -1) ?  HRZLIB[ Z_NEED_DICT -err] :DSYConvertError(ERRNO,  FACILITY_WIN32))
// les erreurs du zip sont les erreurs zlib -100
#define ZIP_ERR_HR(err)	((err<(-100)) ?  Z_ERR_HR((err+100)) :((err==-1) ?  DSYConvertError(ERRNO, FACILITY_WIN32): S_OK))

#endif
