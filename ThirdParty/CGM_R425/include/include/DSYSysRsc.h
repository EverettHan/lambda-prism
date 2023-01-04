// COPYRIGHT DASSAULT SYSTEMES 2014
#ifndef DSYSysRsc_H
#define DSYSysRsc_H

/************************************************************************/
/* Defines                                                              */
/************************************************************************/
#if defined(__JS0RSC)
# define ExportedByJS0RSC  DSYExport
#else // __JS0RSC
# define ExportedByJS0RSC  DSYImport
#endif  // __JS0RSC

/************************************************************************/
/* Local includes                                                       */
/************************************************************************/
#include "CATDataType.h"
#include "CATSysErrorDef.h"
#include "DSYExport.h"
#include "DSYSysRscError.h"
#include "DSYSysCommon.h"

//=======================================================================
typedef void* DSYSysRscHandle;
//=======================================================================

//=======================================================================
class CATILockBytes;
class DSYSysPath;
class DSYSysRscListPtr;
class DSYSysRscListFiles;
class DSYSysRscSearchPath;
class CATUnicodeString;
class DSYSysRscSearchPathImpl;
//=======================================================================

/************************************************************************/
/* Classes declaration                                                  */
/************************************************************************/

/**
 * @class DSYSysRscListFilesItem
 *
 * Class used to list all the elements in a folder for the DSYSysRsc API with DSYSysRscSearchPath::GetListFiles(). Relative path will be searched in the bundles, absolute folder file base.
 */
class ExportedByJS0RSC DSYSysRscListFilesItem
{
public:
    DSYSysRscListFilesItem();
    virtual ~DSYSysRscListFilesItem();

    DSYSysPath GetFolderPath();
    CATUnicodeString* GetFileList();
    int GetNbFiles();

protected:
    int               m_NbFiles;
    DSYSysPath*       m_pFolder;
    CATUnicodeString* m_pFiles;
};

/**
 * @class DSYSysRscSearchPath
 */
class ExportedByJS0RSC DSYSysRscSearchPath
{
public:
    DSYSysRscSearchPath();
    ~DSYSysRscSearchPath();

    /// Add path. Must end with \0.
    HRESULT Add(const char* ipPath);
    HRESULT Add(DSYSysPath& iPath);

    /// Add path of an environment variable.
    int AddEnvVariable(const char* iPath);
    
    /// Get number of path in the search order TODO un-expose
    size_t GetCount();
    
    /// NoDoc - Not to use
    DSYSysRscSearchPathImpl* GetSearchPathImpl() const
    { return m_pSearchPathImpl; }

private:
    DSYSysRscSearchPathImpl* m_pSearchPathImpl;
};

/************************************************************************/
/************************************************************************/



/************************************************************************/
/* Functions declaration                                                */
/************************************************************************/

////////////////////////////////////////////////////////////////
//////////////////////// Bundle reading ////////////////////////
////////////////////////////////////////////////////////////////

/**
  * This function is facultative for the use of DSYSysRsc API.
  * If not called, all calls of DSYSysRscOpen will lead to the official bundle located in the runtime view
  *
  * This function allow the use of a bundle outside the official runtime view by returning
  * a specific handle to give as a parameter in the DSYSysRscOpenEx function.
  * A call to DSYSysRscFinalizeEx is mandatory to avoid memory leaks.
  *
  * @param ipInstallPath        The path where to find the bundle and where fallback mode will look for files (used as prefix of relatives paths) MUST BE UTF8 ENCODED (ASCII char are OK so)
  *                             A path concatenation is OK.
  * @param ipBundleName         The name of the bundle
  * @param iopppInternalObj     The handler to use in the next DSYSysRscOpen function
  *
  */
//=======================================================================
ExportedByJS0RSC HRESULT DSYSysRscInitializeEx(const char* ipInstallPath, const char* ipBundleName, void*** iopppInternalObj);
//=======================================================================


    /**
     * NON EX     : Find a resource file given one or several paths as a search order
     *              and create the associated handle in the bundle of the official runtime view.
     * EX version : Use the handle created in @DSYSysRscInitializeEx to allow the user the reading in a non official bundle
     *
     * @param ioppInternalObj   The handler on the custom bundle created in DSYSysRscInitialize
     * @param opRscHandle       An hanlde on the requested resource.
     * @param iSearchOrder      Sequence of paths where to find the resource file.
     *                          The paths can be relative (from the 'CATInstallPath'
     *                          variable, etc... example "resources\msgcatalog") 
     *                          or absolute.
     * @param ipRscName         Resource name (with extension). MUST BE UTF8 ENCODED
     *
     * @return            S_OK if successful or E_FAIL in the case of an error.
     */
    //=======================================================================
    ExportedByJS0RSC HRESULT DSYSysRscOpen(DSYSysRscHandle& opRscHandle, const DSYSysRscSearchPath& iSearchOrder, const CATUnicodeString& iRscName);
    ExportedByJS0RSC HRESULT DSYSysRscOpenEx(void** ioppInternalObj, DSYSysRscHandle& opRscHandle, const DSYSysRscSearchPath& iSearchOrder, const CATUnicodeString& iRscName);
    //======================= Deprecated ====================================
    ExportedByJS0RSC HRESULT DSYSysRscOpen(DSYSysRscHandle& opRscHandle, const DSYSysRscSearchPath& iSearchOrder, const char* ipRscName);
    ExportedByJS0RSC HRESULT DSYSysRscOpenEx(void** ioppInternalObj, DSYSysRscHandle& opRscHandle, const DSYSysRscSearchPath& iSearchOrder, const char* ipRscName);
    //======================= Deprecated ====================================

        /**
          * Get info on the requested resource.
          *
          * @param ipRscHandle        An hanlde on the requested resource.
          * @param oRscInfo           Resource name (with extension).
          *
          * @return            S_OK if successful or E_FAIL in the case of an error.
          */
        //=======================================================================
        ExportedByJS0RSC HRESULT DSYSysRscGetInfo(DSYSysRscHandle ipRscHandle, CATFileInfo64& oRscInfo, DSYSysPath* opRelativePath = NULL);
        //=======================================================================

        /**
          * Read the entire resource data in a row and save it into the passed buffer.
          *
          * @param ipRscHandle        An hanlde on the requested resource.
          * @param opBuffer           Buffer to save file data.
          * @param iBufferSize        Buffer size.
          *
          * @return            S_OK if successful or E_FAIL in the case of an error.
          */
        //=======================================================================
        ExportedByJS0RSC HRESULT DSYSysRscRead(DSYSysRscHandle ipRscHandle, char* opBuffer, const size_t iBufferSize);
        //=======================================================================

        /**
          * Get an CATILockBytes object from the requested resource.
          *
          * @param ipRscHandle        An hanlde on the requested resource.
          * @param oppLockByte        A CATILockByte instance on the requested resource.
          *
          * @return            S_OK if successful or E_FAIL in the case of an error.
          */
        //=======================================================================
        ExportedByJS0RSC HRESULT DSYSysRscGetILB(DSYSysRscHandle ipRscHandle, CATILockBytes** oppLockByte);
        //=======================================================================

    /**
      * Release the requested resource handle.
      *
      * @param iopRscHandle       An hanlde on the requested resource.
      *
      * @return            S_OK if successful or E_FAIL in the case of an error.
      */
    //=======================================================================
    ExportedByJS0RSC HRESULT DSYSysRscClose(DSYSysRscHandle& iopRscHandle);
    //=======================================================================

/**
 * This function close the hadle openned in the DSYSysRscInitialize function.
 * Mandatory to avoid memory leaks.
 *
 * @param iopppInternalObj The handler to close.
 */
//=======================================================================
ExportedByJS0RSC HRESULT DSYSysRscFinalizeEx(void*** iopppInternalObj);
//=======================================================================


////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////


/************************************************************************/
/* Utility functions declaration                                        */
/************************************************************************/

/**
  * Get a list of the files into one or more paths of the DSYSysRscSearchPath
  * The search will be done in the bundle of the official runtime view.
  *
  * NON EX     : List all the files in a given DSYSysRscSearchPath.
  * EX version : Use the handle created in @DSYSysRscInitializeEx to allow the user the listing in a non official bundle
  *
  * @param oppRscListFileItem A DSYSysRscListFilesItem* object where to get the name of the folder listed, number of files and a list of CATUnicodeString (definition at the top the this source).
  * @param iSearchOrder       The search order
  * @param iSearchOrderIndex  The index of the search order to list
  *
  * @return            S_OK if successful or E_FAIL in the case of an error.
  */
//=======================================================================
ExportedByJS0RSC HRESULT DSYSysRscListFilesInSearchPath(DSYSysRscListFilesItem** oppRscListFileItem, DSYSysRscSearchPath& iSearchOrder, unsigned int ipSearchOrderIndex);
ExportedByJS0RSC HRESULT DSYSysRscListFilesInSearchPathEx(void** ippInternalObj, DSYSysRscListFilesItem** oppRscListFileItem, DSYSysRscSearchPath& iSearchOrder, unsigned int ipSearchOrderIndex);
//=======================================================================

/**
* Return the official bundle name.
* Can be overloaded by CATBundleName environment variable.
*/
//=======================================================================
ExportedByJS0RSC HRESULT DSYSysRscGetBundleName(const char*& opBundleName);
ExportedByJS0RSC HRESULT DSYSysRscGetBundleName(CATUnicodeString& oBundleName);
//=======================================================================

/************************************************************************/
/************************************************************************/
#endif  // DSYSysRsc_H
