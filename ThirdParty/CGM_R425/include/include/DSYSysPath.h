#ifndef DSYSysPath_H
#define DSYSysPath_H

#include "CATDataType.h" 
#include "CATSysBoolean.h"
#include "CATSysTS.h"
#include "CATWTypes.h"
#include "DSYSysDirectoryIterator.h"
#include "DSYSysFNMatch.h"  // DSYSysFNMatchOptions
#include "DSYString.h"
#include "CxxSupport.h"

#include <stdio.h>

#undef DSYSysInvalidPath
#undef DSYSysAbsolutePath
#undef DSYSysHttpPath
#undef DSYSysHttpsPath
#undef DSYSysDLNamesPath
#undef DSYSysRelativePath
#undef DSYSysUNCPath
#undef DSYSysMountedDisk

#if defined(_WINDOWS_SOURCE)
# define DSYSYS_S_IREAD _S_IREAD
# define DSYSYS_S_IWRITE _S_IWRITE
# define DSYSYS_S_IEXEC _S_IEXEC
#else   // _WINDOWS_SOURCE
# define DSYSYS_S_IREAD S_IRUSR
# define DSYSYS_S_IWRITE S_IWUSR
# define DSYSYS_S_IEXEC S_IXUSR
#endif  // _WINDOWS_SOURCE

// Type flags - 32 max
#define DSY_PATH_INVALID                0x0001
#define DSY_PATH_ABSOLUTE               0x0002
#define DSY_PATH_RELATIVE               0x0004
#define DSY_PATH_MOUNTED_DISK           0x0008
#define DSY_PATH_UNC                    0x0010
#define DSY_PATH_HTTP                   0x0020
#define DSY_PATH_HTTPS                  0x0040
#define DSY_PATH_DLNAME                 0x0080
#define DSY_PATH_CANONICAL              0x0100

///////////////////////////////////////////
////// Types/Constants/Struct/Enum ////////
///////////////////////////////////////////
/*
* Path types defintions. These types can be the following depending on the type of plateform:
* Windows NT : DSYSysInvalidPath, DSYSysHttpPath, DSYSysHttpsPath, DSYSysDLNamesPath, DSYSysRelativePath, DSYSysUNCPath, DSYSysMountedDisk
* UNIX       : DSYSysInvalidPath, DSYSysHttpPath, DSYSysHttpsPath, DSYSysDLNamesPath, DSYSysRelativePath, DSYSysAbsolutePath
*/
enum DSYSysPathType
{
    // File path could not be found when building DSYSysPath object
    DSYSysInvalidPath  = DSY_PATH_INVALID,
    // Unix specific, paths on unix can be either absolute or relative
    DSYSysAbsolutePath = DSY_PATH_ABSOLUTE,
    // Relative path, on Unix and Windows plateforms
    DSYSysRelativePath = DSY_PATH_RELATIVE,
    // HTTP url types
    DSYSysHttpPath     = DSY_PATH_HTTP,
    DSYSysHttpsPath    = DSY_PATH_HTTPS,
    // DLName path
    DSYSysDLNamesPath  = DSY_PATH_DLNAME,
    // Windows NT specific path types
    DSYSysMountedDisk  = (DSY_PATH_ABSOLUTE|DSY_PATH_MOUNTED_DISK),
    DSYSysUNCPath      = (DSY_PATH_ABSOLUTE|DSY_PATH_UNC)
};


class DSYSysPath;
class DSYSysPathImpl;
class CATUnicodeString;
class CATSysTSUnicodeString;


/*
 * @class DSYSysPath
 * @info  General file and directory path manipulation class. 
 *        Usage:  When DSYSysPath object is declared, it is first in an invalid state, unless it is declared with the copy contructor
 *                It is then built using one of the Set/BuildFrom* methods which takes a string representation of the desired path.
 *                DSYSysPath supports Unicode (by using a wide char representation on Windows NT and a UTF8 representation on UNIX).
*/
class ExportedByCATSysTS DSYSysPath
{
public:
    ///////////////////////////////////////////
    ///////////////// Methods /////////////////
    ///////////////////////////////////////////

    /// Constructor (default).
    DSYSysPath();
    
    /// Constructor
    DSYSysPath(const CATUnicodeString &iString);
    
    /// Destructor.
    virtual ~DSYSysPath();

    /// Contructor (copy).
    DSYSysPath(const DSYSysPath& iSrc);

    /// Assignement operator is only defined with another DSYSyspath object as input.
    /// For string assignments use the Set methods which are safer because they
    /// allow you to check the validity of the new path.
    DSYSysPath& operator=(const DSYSysPath& iPath);
    
    /// Build path from different string representations.
    HRESULT Set(const CATUnicodeString &iString);
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    HRESULT Set(const char8_t* ipString);
#endif
    HRESULT Set(const char* ipString);  // ipString is expected to be UTF-8 encoded. Rather use the 'char8_t' signature, safer.
    HRESULT Set(const WCHAR* ipString);
    
    // Move constructor.
    DSYSysPath(DSYSysPath &&iRValue);
    // Move assignment operator.
    DSYSysPath& operator=(DSYSysPath &&iRValue);
    
    CATBoolean IsValid() const;
    
    /**
     * GetName.
     * Returns the final component of this path.
     * On UNIX for example, GetName returns "c" for the path "/a/b/c".
     * @param [in,out] ioHr, optional return code. If ioHr is not NULL, action will be performed only if SUCCEEDED(*ioHr) is true.
     */
    DSYSysPath GetName(HRESULT *ioHr = NULL) const;

    /**
     * GetParent. Returns the parent path, or an invalid path if this path does not have a parent.
     * On UNIX for example, the parent of "/a/b/c" is "/a/b".
     * @param [in,out] ioHr, optional return code. If ioHr is not NULL, action will be performed only if SUCCEEDED(*ioHr) is true.
     */
    DSYSysPath GetParent(HRESULT *ioHr = NULL) const;
    
    /// Comparison operators.
    bool operator == (const DSYSysPath& iComparand) const;
    bool operator == (const CATUnicodeString& iComparand) const;
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    bool operator == (const char8_t * ipComparand) const;
#endif
    bool operator == (const char * ipComparand) const;  // ipComparand is expected to be UTF-8 encoded. Rather use the 'char8_t' signature, safer.
    bool operator == (const WCHAR* ipComparand) const;

    bool operator != (const DSYSysPath& iComparand ) const { return !operator ==(iComparand); }
    bool operator != (const CATUnicodeString& iComparand) const { return !operator ==(iComparand); }
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    bool operator != (const char8_t * ipComparand) const { return !operator ==(ipComparand); }
#endif
    bool operator != (const char * ipComparand) const { return !operator ==(ipComparand); } // ipComparand is expected to be UTF-8 encoded. Rather use the 'char8_t' signature, safer.
    bool operator != (const WCHAR* ipComparand) const { return !operator ==(ipComparand); }

    /**
     * Determines whether the path is relative or absolute. This does not depend on the plateform.
     */    
    CATBoolean IsRelative() const;
    
    CATBoolean IsAbsolute() const;
    
    /**
     * GetExtension.
     * Returns an extension if the path links to a file.
     * @return S_OK upon success. oExt is valued with the file extension.
     * @return E_FAIL in case of error (the path links to a directory, the path is invalid...) oExt keep its initial value.
     * WARNING: this funcion has not the same behavior as the previous version (getExtension).
     */
    HRESULT GetExtension(CATUnicodeString & oExt) const;
    DSYSysPath & RemExtension(HRESULT *ioHr = NULL);
    HRESULT RemExtension(const CATUnicodeString & iExt);
    
    /**
     * Append/Add.
     * @param [in,out] path part (as a DSYSysPath or a CATUnicodeString).
     * @param [in,out] ioHr, return code. If ioHr is not NULL, action will be performed only if SUCCEEDED(*ioHr) is true.
     */
    HRESULT Append(const DSYSysPath& iPart);
    HRESULT Append(const CATUnicodeString & iPart);
#if (__cplusplus > 201703L) // char8_t is expected to be supported with C++20 and onwards 
    HRESULT Append(const char8_t *iPart);
#endif
    HRESULT Append(const char  *iPart);                     // iPart is expected to be UTF-8 encoded. Rather use the 'char8_t' signature, safer.
    HRESULT Append(const WCHAR *iPart);
    DSYSysPath & Add(const DSYSysPath & iPart, HRESULT *ioHr = NULL);
    DSYSysPath & Add(const CATUnicodeString & iPart, HRESULT *ioHr = NULL);
    
    HRESULT AddExtension(const CATUnicodeString & iExt);    
    HRESULT AddExtension(const char  *iExt);                // iExt is expected to be UTF-8 encoded.
    HRESULT AddExtension(const WCHAR *iExt);
    
    /**
     * ToString.
     * @param [in,out] ioHr, optional return code. If ioHr is not NULL, action will be performed only if SUCCEEDED(*ioHr) is true.
     */
    CATUnicodeString ToString(HRESULT *ioHr = NULL) const;    
    HRESULT GetAsString(CATUnicodeString& oString) const;

    CATULONG32 GetTypeMask() const;
    
    /**
     * Begin.
     * For a path to a browsable directory, returns an iterator pointing to the first element in that directory.
     * @param [in,out] ioHr, optional return code. If ioHr is not NULL, SUCCEEDED(*ioHr) must be true on input or an end iterator will be returned.
     * @param [in]  iFilterPattern is an optional pattern that allows to filter entry names following Unix filename pattern matching rules, in an efficient manner.
     *              If filtering is not required, iFilterPattern must be set to an empty string (or *).
     *              [Windows]: 
     *                 - the following characters are forbidden: 0x00-0x1F 0x7F " / : < > \ |
     *                   Note that the characters > < " also have a special meaning in patterns (DOS era legacy).
     *                 - "*.*" does not match all entries, but only the ones that actually contain a dot character, like on other OSes.
     *              Failing to comply to these rules will lead to undefined behavior.
     * @param [in]  iFilterOptions, mandatory argument if iFilterPattern is set (see DSYSysFNMatch.h)
     * @return a begin iterator.
     * @return an end iterator otherwise (not a directory, access denied...).
     */
    DSYSysDirectoryIterator Begin(const CATUnicodeString & iFilterPattern, const DSYSysFNMatchOptions & iFilterOptions, HRESULT *ioHr = NULL) const;
    DSYSysDirectoryIterator begin() const { return Begin(); }    // To support C++ range-based for loops
    DSYSysDirectoryIterator Begin(HRESULT *ioHr = NULL) const;
    
    /**
     * End.
     * @return an end iterator.
     */
    DSYSysDirectoryIterator End() const;
    DSYSysDirectoryIterator end() const { return End(); }        // To support C++ range-based for loops
    
    /**
     * @deprecated R420 Use Begin.
     * GetDirectoryIterator.
     */
    HRESULT GetDirectoryIterator(DSYSysDirectoryIterator & oItBegin) const;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// INTERNAL USE ONLY SECTION BEGIN (System FWs)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    /**
     * Check whether the file system entry exists, whether it is a file or a directory 
     * These methods result in a stat system call when called the first time and use cached information when susequently called
     */    
    CATBoolean Exists(int iForceCheck = 0) const;
    
    CATBoolean IsFile(int iForceCheck = 0) const;
    
    CATBoolean IsDirectory(int iForceCheck = 0) const;
    
    /**
     * Retrieve full file information as defined in stat.h , check read/write and file time information.
     * These methods result in a stat system call when called the first time and use cached information when susbequently called
     */
    HRESULT    Stat(CATFileInfo64 & oInfo, int iForceCheck = 0) const;
    
    HRESULT    GetTimes(time_t & olmt, time_t & olat) const;    
    
    CATBoolean CanRead(int iForceCheck = 0) const;
    
    CATBoolean CanWrite(int iForceCheck = 0) const;
    
    /**
     * Change file access rights and file times.
     * chmod's argument is the same mode_t field that can be found in CATFileInfo64.
     */
    HRESULT Chmod(long iNewMode) const;
    
    HRESULT SetTimes(time_t ilmt, time_t ilat) const;
    
    /**
     * Directory and file creation and removal 
     * the iRecursive argument in RmDir is used to force directory removal even when it is not empty
     * when set to 1 RmDir recursively REMOVES ALL the content of the directory
     */
    HRESULT MakeDir() const;
    
    HRESULT Remove(int iRecursive = 0) const;     // iRecursive is ignored if the path links to a file.
    
    HRESULT Move(const DSYSysPath& iNewPath) const;
    
    /**
     * Print a message along with the string representation the current DSYSysPath object in the trace file/stream.
     * "DSYSysPath" Traces need to be activated through the DSYSysTrace mechanism
     */
    HRESULT PrintInTrace(const char * iMessage = NULL, int iOption = 0) const;
    
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// INTERNAL USE ONLY SECTION BEGIN (System FWs)
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DEPRECATED METHODS SECTION BEGIN
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    // @deprecated R417
    HRESULT Set(const CATSysTSUnicodeString& ipString);
    DSYSysPathType getType() const;
    CATBoolean isRelative() const { return IsRelative(); }
    CATBoolean isAbsolute() const { return IsAbsolute(); }
    HRESULT getExtension(CATSysTSUnicodeString & oExt) const;
    HRESULT removeExtension(const CATSysTSUnicodeString & iExt);
    HRESULT split(DSYSysPath& oParent, CATSysTSUnicodeString& oChild) const;  // split replacement: cf. GetParent, GetName, GetExtension
    HRESULT split(DSYSysPath& oParent, CATSysTSUnicodeString& oDirectoryName, CATSysTSUnicodeString & oFileName, CATSysTSUnicodeString & oExtension) const;
	HRESULT append(const CATSysTSUnicodeString & iPart);
    HRESULT append(const DSYSysPath& iPart) { return Append(iPart); }
	HRESULT append(const CATUnicodeString & iPart) { return Append(iPart); }
    HRESULT append(const WCHAR * iPart){ return Append(iPart); }
    HRESULT append(const char * iPart) { return Append(iPart); }
    HRESULT addExtension(const CATSysTSUnicodeString & iExt);
    HRESULT addExtension(const WCHAR * iExt) { return AddExtension(iExt); }
    HRESULT addExtension(const char * iExt)  { return AddExtension(iExt); }
    HRESULT getAsString(CATSysTSUnicodeString& oString) const;
    HRESULT getDirectoryIterator(DSYSysDirectoryIterator & oIt) const { return GetDirectoryIterator(oIt); }
    CATBoolean exists(int iForceCheck=0) const { return Exists(iForceCheck); }
    CATBoolean isFile(int iForceCheck=0) const { return IsFile(iForceCheck); }
    CATBoolean isDirectory(int iForceCheck=0) const { return IsDirectory(iForceCheck); }
    HRESULT stat(CATFileInfo64 & oInfo,int iForceCheck=0) const { return Stat(oInfo, iForceCheck); }
    CATBoolean canRead(int iForceCheck=0) const { return CanRead(iForceCheck); }
    CATBoolean canWrite(int iForceCheck=0) const{ return CanWrite(iForceCheck); }
    HRESULT getTimes(time_t & olmt, time_t & olat) const { return GetTimes(olmt, olat); }
    HRESULT chmod(long iNewMode) const { return Chmod(iNewMode); }
    HRESULT setTimes(time_t ilmt, time_t ilat) const { return SetTimes(ilmt, ilat); }
    HRESULT createDirectory() const { return MakeDir(); }
    HRESULT removeDirectory(int iRecursive) const { return Remove(iRecursive); }
    HRESULT removeFile() const { return Remove(); }
    HRESULT move(const DSYSysPath& iNewPath) const { return Move(iNewPath); }
    HRESULT printInTrace(const char * iMessage = NULL, int iOption = 0) const { return PrintInTrace(iMessage, iOption); }
    HRESULT BuildFromWCHAR(const WCHAR * iString) { return Set(iString); }
    HRESULT BuildFromUTF8(const char * iString) { return Set(iString); }
    HRESULT BuildFromTSString(const CATSysTSUnicodeString & iString) { return Set(iString); }

    /**
    * Retrieve temporary directory for the current user (and current application on mobile plateforms).
    * IMPORTANT: for security reasons, to create a temporary file, rather use DSYSysCreateTempFile (DSYSysStdIO.h).
    */
    static HRESULT getTempDirectory(DSYSysPath & oPath);

    /**
    * @deprecated
    * Retrieve Home directory for the current user (and current application on mobile plateforms).
    */
    static HRESULT getHomeDirectory(DSYSysPath & oPath);

    /**
    * @deprecated
    * GetTempFilePath/getTempFilePath
    * IMPORTANT: since there is a race between between testing whether the name exists and opening the file,
    * every use of this function is a security risk. Rather use DSYSysCreateTempFile (DSYSysStdIO.h).
    */
    static HRESULT GetTempFilePath(DSYSysPath & oPath, const CATUnicodeString * iPrefix = NULL, const DSYSysPath * iDirectory = NULL);
    static HRESULT getTempFilePath(DSYSysPath & oPath, const CATSysTSUnicodeString * iPrefix = NULL, const DSYSysPath * iDirectory = NULL);
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// DEPRECATED METHODS SECTION END
    /////////////////////////////////////////////////////////////////////////////////////////////////////////

private:
    /// Friendship declarations.
    friend class DSYSysPathImpl;
    
    /// Path implementation object.
    DSYSysPathImpl* _impl;
};


/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

//=======================================================================
HRESULT ExportedByCATSysTS DSYSysPathHome(DSYSysPath& oPath);
//=======================================================================

//=======================================================================
HRESULT ExportedByCATSysTS DSYSysPathDocument(DSYSysPath& oPath);
//=======================================================================

//=======================================================================
HRESULT ExportedByCATSysTS DSYSysPathTemporary(DSYSysPath& oPath);
//=======================================================================

//=======================================================================
HRESULT ExportedByCATSysTS DSYSysPathDesktop(DSYSysPath& oPath);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
HRESULT ExportedByCATSysTS DSYSysPathBaseName(const DSYSysPath& iPath, CATUnicodeString& oFileName);
//=======================================================================

/************************************************************************/
/************************************************************************/

//=======================================================================
inline bool operator ==(const CATUnicodeString & iComparand1, const DSYSysPath & iComparand2)
//=======================================================================
{
    return (iComparand2 == iComparand1);
}

//=======================================================================
bool ExportedByCATSysTS operator ==(const char * ipComparand1, const DSYSysPath & iComparand2);
//=======================================================================

//=======================================================================
bool ExportedByCATSysTS operator ==(const WCHAR * ipComparand1, const DSYSysPath & iComparand2);
//=======================================================================

//=======================================================================
inline bool operator !=(const CATUnicodeString & iComparand1, const DSYSysPath & iComparand2)
{
    return !(iComparand2 == iComparand1);
}
//=======================================================================

//=======================================================================
inline bool operator !=(const char * ipComparand1, const DSYSysPath & iComparand2)
{
    return !( iComparand2 == ipComparand1);
}
//=======================================================================

//=======================================================================
inline bool operator !=(const WCHAR * ipComparand1, const DSYSysPath & iComparand2)
{
    return !( iComparand2 == ipComparand1);
}
//=======================================================================

/************************************************************************/
/* Implementation                                                       */
/************************************************************************/

// Move constructor.
inline DSYSysPath::DSYSysPath(DSYSysPath &&iRValue) : _impl(NULL)
{
    // "Steal" the letter from the source object
    _impl = iRValue._impl;    
    // Resetting the source impl pointer so that the destructor does not free it multiple times.
    iRValue._impl = NULL;
}

#endif  // DSYSysPath_H
