//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 1996                                          *
//*===========================================================================*
//*                                                                           *
//*  CATIStorage                                                              *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation mars 1997                                                       *
//*===========================================================================*

/* COPYRIGHT DASSAULT SYSTEMES 2004 */
#ifndef __CATILOCKBYTES
#define __CATILOCKBYTES

#include "CATWTypes.h"
#include "IUnknown.h"
#include "JS0BASEILB.h"


/**
 * A type for memory manipulation within the @href CATILockBytes interface.
 */
typedef void * CATMemHandle;
/**
 * Default value for an uninitialized @href CATMemHandle
 */
#define INVALIDMEM NULL

extern  ExportedByJS0BASEILB IID IID_CATILockBytes;


/**
 * Interface used by the V5 documents to represent their physical storage
 * as a byte array.
 * <b>Role</b>: This interface is used by the V5 composite documents to access 
 * to their physical storage device, without needing to consider the 
 * specifications of the physical storage.
 * This interface should be not implemented. 
 **/
class  CATILockBytes : public IUnknown
{
public:

/**
 * Reads a block of data in the byte array object.
 * <b>Role</b>: Reads a block of data at the specified offset fom the 
 * beginning of the array. 
 * @param iOffset [in]
 *  Offset of the block from the beginning of the array 
 * @param  iBuff [in]
 *  Buffer where data where will be stored.
 * @param iLengthToRead [i]
 *   the size of the requested data.
 * @param oLengthRead [out]
 *   the actual length of read data.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_SEEKERROR :</tt> problem in setting the read offset.
 *   <br><tt> STG_E_READFAULT :</tt> problem while reading.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> invalid arguments.
 *   <br><tt> STG_E_ACCESSDENIED:</tt> No sufficient permission to read.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
 */     
  virtual  HRESULT __stdcall ReadAt( ULARGE_INTEGER iOffset,
				     void FAR *iBuff,
				     ULONG iLengthToRead,
				     ULONG FAR *oLengthRead) = 0;
/**
 * Writes a block of data in the byte array object.
 * <b>Role</b>: Writes a block of data at the specified offset fom the 
 * beginning of the array. 
 * @param iOffset [in]
 *   Offset of the block  from the beginning of the array 
 * @param  iDataSource [in]
 *  Buffer of data to write.
 * @param iLengthToWrite [i]
 *   the size of the data to write.
 * @param oLengthWriten [out]
 *   the actual length of written data. Should be equal to iLengthToWrite if 
 *   no problem has occurred.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_SEEKERROR :</tt> problem in setting the read offset.
 *   <br><tt> STG_E_WRITEFAULT :</tt> problem while writing and iLengthToWrite
 *				      is not equal to LengthWritten.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> The write operation was not completed 
 *				      because there is no space left on the
 *				      storage device. The actual written length
 *				       is still returned in LengthWritten.
 *   <br><tt> STG_E_INVALIDPARAMETER :</tt> invalid arguments.
 *   <br><tt> STG_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> STG_E_ACCESSDENIED:</tt> No sufficient permission to write.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
*/                 
  virtual  HRESULT __stdcall WriteAt( ULARGE_INTEGER iOffset,
				      const void FAR *iDataSource,
				      ULONG iLengthToWrite,
				      ULONG FAR *LengthWritten) = 0;
/**
 * Flush all the buffers.
 * <b>Role</b>: Insures that any internal buffers maintained by the 
 * CATILockBytes object are written out to the permanent storage.
 * @return
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_WRITEFAULT :</tt> problem while writing.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> disk full error.
 *   <br><tt> STG_E_DISKISWRITEPROTECTED :</tt> disk write protected.
 *   <br><tt> STG_E_UNKNOWN :</tt> unexpected error.
*/               
  virtual HRESULT __stdcall Flush( void) = 0;


/**
 * Sets the size of the CATILockBytes.
 * <b>Role</b>: Sets the size of the CATILockBytes.
 * @ param iLength.
 *      The new size of the CATILockBytes.
 * @return   
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success. 
 *   <br><tt> STG_E_ACCESSDENIED:</tt> No sufficient permission to set 
 *                                     the size of the document.
 *   <br><tt> STG_E_SEEKERROR :</tt> problem in setting the new offset.
 *   <br><tt> STG_E_MEDIUMFULL :</tt> no space left on the backing storage to
 *                                    increase the size of the byte array.
*/             
  virtual HRESULT __stdcall SetSize( ULARGE_INTEGER iLength) = 0;



/**
 * Locks a region of the CATILockBytes.
 * <b>Role</b>: Locks a region of the CATILockBytes.
 * @param iOffset [in]
 *   Offset of the block from the beginning of the array
 * @param iLength [i] 
 *   the size of the region.  if iLength and Offset are null, then the lock
 *   is applied on the whole array.
 * @param dwLockType [in] 
 *        type of lock. 
 * @return 
 *   <b>Legal values</b>: 
 *   <br><tt> S_OK :</tt>on Success. 
 *   <br><tt> STG_E_INVALIDFUNCTION :</tt> the underlying object does not 
 *					   support locking.
 *   <br><tt> STG_E_LOCKVIOLATION :</tt> array object locked by another caller.
 *   <br><tt> STG_E_ACCESSDENIED:</tt> array object locked by another caller.
 *   <br><tt> STG_E_INVALIDHANDLE :</tt> the underlying storage device is not
 *					 available.
*/               
  virtual HRESULT __stdcall LockRegion( ULARGE_INTEGER iOffset,
					ULARGE_INTEGER iLegnth,
					DWORD dwLockType) = 0;
  
/**
 * Locks a region of the CATILockBytes.
 * <b>Role</b>: Locks a region of the CATILockBytes. This method is not 
 * implemented by any V5 implementation of this interface and are never
 * called by the V5 documents code. 
 * @param iOffset [in]
 *   Offset of the block from the beginning of the array  
 * @param iLength [i] 
 *   the size of the region. 
 * @param dwLockType [in] 
 *        type of lock. 
 * @return 
 *   <b>Legal values</b>: 
 *   <br><tt> STG_E_INVALIDFUNCTION :</tt> the underlying object does not 
 *					   support locking.
 *   <br><tt> STG_E_LOCKVIOLATION :</tt> array object locked by another caller.
 *   <br><tt> STG_E_INVALIDHANDLE :</tt> the underlying storage device is not
 *					 available.
*/
  virtual HRESULT __stdcall UnlockRegion( ULARGE_INTEGER iOffset,
					  ULARGE_INTEGER iLength,
					  DWORD dwLockType) = 0;

/**
 * Returns informations for the byte array object.
 * <b>Role</b>:  Returns informations for the CATILockBytes. 
 * @param oStat [io]
 *    pointer to a STATSTG structure.
 * @param iStatFlag [in]
 *    specifies whether the name of the object should be supplied.
 *   <b>Legal values</b>:
 *   <br><tt> STATFLAG_NONAME:</tt> no name is supplied.
 *   <br><tt> STATFLAG_DEFAULT:</tt> all fields are supplied
 * @return 
 *   <b>Legal values</b>:
 *   <br><tt> S_OK :</tt>on Success.
 *   <br><tt> STG_E_INVALIDPOINTER :</tt> invalid pointer for the STATSTG
 *					  structure. 
 *   <br><tt> STG_E_ACCESSDENIED:</tt> No sufficient permission to retrieve 
 *                                     the information concerning the array.
 *   <br><tt> STG_E_INSUFFICIENTMEMORY:</tt> no more memory.
 *   <br><tt> STG_E_INVALIDFLAG :</tt> value for iStatFlag is not valid.
*/          
  virtual HRESULT __stdcall Stat( STATSTG FAR *oStat,
				  DWORD iStatFlag) = 0;
        
};

#endif



