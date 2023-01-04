//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2011                                          *
//*===========================================================================*
//*                                                                           *
//*  Advanced Function for JS0LIB0                                            *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation august 2011                                    adt              *
//*===========================================================================*
#ifndef CATTSLIBEX_H
#define CATTSLIBEX_H    42400
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifdef _WINDOWS_SOURCE
#include <io.h>
#include <stdlib.h>
#else
#include <dirent.h>
#include <limits.h>
#endif

#include "CATUniStd.h"
#include "CATWTypes.h"
#include "JS0TSLIB.h"
#include "DSYSysTSLib.h"    // CATLibStatus
#include "JS0HTTP.h"
#include "CATSysTS.h"
#include "DSYString.h"
#include "CATSysTSUnicodeString.h"


/** cf. defines CATLib.h */
#ifndef CATLibMuteProcess
#define CATLibMuteProcess               0x0001
#endif

#ifndef CATLibWaitProcess
#define CATLibWaitProcess               0x0002
#endif

#ifndef CATLibConsoleProcess
#define CATLibConsoleProcess            0x0004
#endif

#define CATLibProcessArgEscapeNone      0x0008

#define CATLibProcessArgEscape          0x0010  // cf. CATStartProcess(Ex) char* signatures declared in CATLib.h/CATLibEx.h

#define CATInvalidPath      -1
#define CATUnknownPath      0
#define CATAbsolutePath     1
#define CATHttpPath         2
// specifique Windows
#define CATUNCPath          18 // prev val: 3 ++IK8: temporary change to match DSYSysPathType enum value
#define CATMountedDisk      4
#define CATDLNamesPath      5
#define CATRelativePath     6
// pas de separateur en vue
#define CATFileName         7
#define CATURLDLNPath       9
#define CATHttpsPath        10




/**
 * Type of access on  document.
 * @param CATSysOpenMode_Read
 *        To open a document in read only.
 * @param CATSysOpenMode_Write
 *        To open a document in write only.
 * @param CATSysOpenMode_RW
 *        To open a document in read/write.
 */
enum CATSysOpenMode { CATSysOpenMode_Read	=0x00000001,
		      CATSysOpenMode_Write	=0x00000002,
		      CATSysOpenMode_RW		=0x00000003};



/**
 * Type of sharing mode on a document. 
 * @param  CATSysSharing_Exclusive
 *	No other processes will be able to open the document in whatever mode.
 * @param  CATSysSharing_Read	
 *	subsequent open operations on the document will be possible 
 *      in read mode.
 * @param  CATSysSharing_NoLock
 *      subsequent open operations on the document will be possible 
 *      in whatever mode. This mode will never be used for V5 document.
 */
enum CATSysSharing { CATSysSharing_Exclusive	=0x00000000,
		     CATSysSharing_Read		=0x00000010,
		     CATSysSharing_NoLock	=0x00000020};


/**
 * The possible actions to take on documents that exist and which action 
 * to take when documents do not exist.
 * @param  CATSys_OpenExisting
 *	  opens the document, but fails if it does not exist already.
 * @param  CATSys_CreateNew
 *	  creates a new document but fails if it already exists.	
 * @param  CATSys_CreateAlways
 *        creates a new document even if it already exists. In this case it
 *        will be overwriten.
 */
enum CATSysCreateMode { CATSys_OpenExisting	=0x00000100,
			CATSys_CreateNew	=0x00000200,
			CATSys_CreateAlways	=0x00000400};


/**
 * The possible actions to take when closing documents.
 * @param  CATSys_Close
 *	  Closes the document.
 * @param  CATSys_DeleteOnClose
 *	  Deletes the document on close.
 */
enum CATSysCloseMode { CATSys_Close		=0x00000000,
		       CATSys_DeleteOnClose	=0x00001000};





void ExportedByJS0TSLIB CATSysFileTimeToTime_t(FILETIME& iTime, time_t& oUTC);
void ExportedByJS0TSLIB CATSysTime_tToFileTime(time_t iUTC, FILETIME& oTime);
HRESULT ExportedByCATSysTS CATStat64ToStat32( CATFileInfo64 &iSt64, 
					      CATFileInfo32 &oSt);




// Make an HRESULT from and errno (unix) or a win32 error code (return of
// GetLastError)
HRESULT ExportedByJS0TSLIB CATConvertError ( int iError, int iFacility);



#define CATHRESULT(err,facilty)	MAKE_HRESULT(SEVERITY_ERROR,facilty,err)
#define CATLIBHRESULT(err)	MAKE_HRESULT(SEVERITY_ERROR,FACILITY_WIN32,err)


HRESULT ExportedByCATSysTS DSYSysTSGetArg(const char *ArgName, int &oSet, CATUnicodeString &oArgValue);
// @deprecated R417
HRESULT ExportedByCATSysTS DSYSysTSGetArg(const char *ArgName, int &oSet, CATSysTSUnicodeString &ArgValue);

HRESULT ExportedByCATSysTS DSYSysTSGetArg(const char *ArgName, int &oSet, int &oType, CATUnicodeString &oArgValue);
// @deprecated R417
HRESULT ExportedByCATSysTS DSYSysTSGetArg(const char *ArgName, int &oSet, int &oType, CATSysTSUnicodeString &ArgValue);

HRESULT ExportedByCATSysTS DSYSysTSAddArg(const char *ArgName, const CATUnicodeString *iArgValue);
// @deprecated R417
HRESULT ExportedByCATSysTS DSYSysTSAddArg(const char *ArgName, CATSysTSUnicodeString *ArgValue);

HRESULT ExportedByCATSysTS DSYSysTSSetArg(int argc, char **argv);
HRESULT ExportedByCATSysTS DSYSysTSResetArg(const char *ArgName);

HRESULT ExportedByJS0HTTP  DSYBuildCASTGC( CATUnicodeString CASUrl, CATUnicodeString CASTGC);
// @deprecated R417
HRESULT ExportedByJS0HTTP  DSYBuildCASTGC( CATSysTSUnicodeString CASUrl, CATSysTSUnicodeString CASTGC);

HRESULT ExportedByJS0HTTP  DSYGetCASTGC( CATUnicodeString &CASUrl, CATUnicodeString &CASTGC);


/** 
 * @nodoc 
 * CATStartProcess / CATStartProcessEx
 * Unicode-compliant signatures: replacement for char-based signatures (CATLib.h)
 * CATStartProcessEx allows to customize the process's environment block
 * Example:
 * const CATUnicodeString iProgName = "PROGRAM_NAME";
 * CATUnicodeString argv[] = { "First_Argument", ...,  "Last_Argument" };
 * argv[k].BuildFromWChar("SomeUnicodeString");
 * CATLibStatus st = CATStartProcess(iProgName, argc, argv, ...);
 *
 * @param [in] iProgName identifies the module to be executed. This string can either specify the name of the module or its full path.
 * @param [in] argc is the number of arguments in argv.
 * @param [in] argv is an array of arguments. 
 *             IMPORTANT: behavior changes compared to char-based signatures (CATLib.h):
 *                   1) argv[0] must not point to the program name, but rather to the first argument => Simplification
 *                   2) By default, the caller does not have to handle OS-specific escaping of arguments anymore (cf. Windows). 
 *                      This will be handled internally, unless the flag "CATLibProcessArgEscapeNone" is set. => Enhanced portability
 *                      However, manual escaping may still be required in some cases, for e.g. when launching Shell commands (cmd /c "SomeCommand > SomeFile" on Windows, sh "SomeScript" on Unix...)
 * @param [in] wait if true, the father process waits for the end of the child process (synchronous mode)
 *                  otherwise, the father process goes on (asynchronous mode). Note that CATWaitProcess may be called 
 *                  later on to wait for the end of the child process.
 * @param [in] iFlags: if CATLibWaitProcess is set, the father process waits for the end of the child process (synchronous mode)
 *                  otherwise, the father process goes on (asynchronous mode). Note that CATWaitProcess may be called 
 *                  later on to wait for the end of the child process.
 *                  Legal flags:
 *                   - CATLibWaitProcess
 *                   - CATLibMuteProcess: redirect traces of forked process to /dev/null.
 *                                        On Windows, for a program using WinMain, the nCmdShow parameter is set to SW_HIDE to instruct it not to show any window.
 *                   - CATLibConsoleProcess: DEPRECATED, DO NOT USE ANYMORE since it has no effect.
 *                   - CATLibProcessArgEscapeNone: disable automatic escaping of arguments (effect on Windows only).
 *                                                 Not recommended but can be useful in specific cases, for e.g. sometimes when launching commands interpreted by CMD.EXE.
 *                   - CATLibProcessArgEscape: no effect with the CATUnicodeString-based signatures below (implied by default)
 *                                                 Useful to enable automatic OS-specific escaping with char-based signatures (CATLib.h)
 * @param [out, optional] opPID is a pointer to an integer variable that will be filled with the process's ID
 * @param [out, optional] opExitCode is a pointer to a variable that will be filled with the process exit code if "wait" has been set to true (or if the CATLibWaitProcess flag is set). Not relevant otherwise.
 * @param [in] envp is an array of environment variables terminated by an empty string, or NULL to inherit the environment block of the current process.
 */
ExportedByCATSysTS CATLibStatus CATStartProcessEx (const CATUnicodeString &iProgName,
                            int argc,
                            CATUnicodeString const *const argv,
                            int iFlags, int *opPID,
                            int *opExitCode,
                            CATUnicodeString const *const envp = nullptr);

/** @nodoc */
inline CATLibStatus CATStartProcess (const CATUnicodeString &iProgName,
                            int argc,
                            CATUnicodeString const *const argv,
                            bool wait, int *opPID,
                            int *opExitCode)
{
   return CATStartProcessEx(iProgName, argc, argv, (wait ? CATLibWaitProcess:0), opPID, opExitCode);
}


/** @nodoc */
/* Only implemented on windows, may be need for iOS and why not for android*/
ExportedByCATSysTS int CATStartShellExecuteEx(const CATUnicodeString &icomPath, int iFlags, int *oPid, int *oExitStatus);



/**
 * DSYFindFileByRelPath.
 * Safe replacement for CATFindPath (CATLib.h).
 * @param [in] iszRelPath is the relative path of the file (or directory) to search
 * @param [out] oszPath is set to the path of the file (or directory) if it is found (true is returned)
 * @param [in, opt] ipszPathConcat if NULL, the file (or directory) will be searched in CATInstallPath
 * @return boolean which is true if the file (or directory) is found, false otherwise
 */
ExportedByCATSysTS bool DSYFindFileByRelPath(const CATUnicodeString &iszRelPath, CATUnicodeString & oszPath, const CATUnicodeString *ipszPathConcat = nullptr);


#endif	// CATTSLIBEX_H
