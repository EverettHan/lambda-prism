//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2005                                          *
//*===========================================================================*
//*                                                                           *
//*  CATILockBytesProperties                                                  *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation july 2005                                                       *
//*===========================================================================*
#ifndef __CATILOCKBYTESPROPERTIES
#define __CATILOCKBYTESPROPERTIES

#include "CATILockBytes.h"
#include "CATDataType.h"
#include "JS0COMP.h"
#include <time.h>

/**
 * Type of a property
 * @param CATSys_Empty
 *              There is no property for this implementation of ILockBytes
 * @param CATSys_INT32
 *		CATINT32
 * @param CATSys_UINT32
 *		CATUINT32
 * @param CATSys_LONG64
 *		CATLONG64
 * @param CATSys_ULONG64
 *		CATULONG64
 * @param CATSys_PtrChar
 *		pointer to a null terminated string
 * @param CATSys_PtrUCChar
 *		pointer to a null terminated unicode string (CATUC2bytes)
 * @param CATSys_FileTime
 *		FILETIME
 */
enum CATSysPropertyType { CATSys_Empty,
			  CATSys_INT32,
			  CATSys_UINT32,
			  CATSys_LONG64,
			  CATSys_ULONG64,
			  CATSys_PtrChar,
			  CATSys_PtrUCChar,
			  CATSys_FileTime,
			  CATSys_BOOL };

/**
 * ID of a property (open to extensions)
 */
enum CATSysPropertyID {  CATSysProp_ZipState =0x00000001,
			 CATSysProp_Size,
			 CATSysProp_LastAccess,
			 CATSysProp_LastModification,
			 CATSysProp_CreationTime};


/**
 * Acces status of a given property.
 * @param CATSysProp_ReadOnly 
 *        property in read only.
 * @param CATSysProp_RW
 *        property can be modified with a call to SetProperty
 */
enum CATSysPropertyStatus { CATSysProp_ReadOnly	=0x00000001,
			    CATSysProp_RW	=0x00000002};


struct CATSysProperty
{
  CATSysPropertyID	_PropID;
  CATSysPropertyType	_PropType;
  CATSysPropertyStatus	_PropStatus;
  union {
    unsigned char       _ValBool;
    CATINT32		_ValI4;
    CATUINT32		_ValUI4; 
    CATULONG64		_ValI8;
    CATULONG64		_ValUI8;
    char *		_ValPtr;
    CATUC2Bytes*        _VaulUC2S;
    FILETIME		_ValFT;
  };
};


// { 0xb706f842, 
//   0x5a49, 
//   0x0000,
//   { 0x02,0x80, 0x03, 0x10, 0x74, 0x00, 0x00, 0x00} };
extern "C" const IID IID_CATILockBytesProperties;

class  ExportedByJS0COMP CATILockBytesProperties : public IUnknown
{
public:
        
/**
 * Retrieves the properties of an ILockBytes
 * <b>Role</b>:Retrieves the properties of an ILockBytes. There is no garantee
 * that the implementation will not need to open the ILockBytes in order
 * to retrieve some properties, however this must be avoided as much as 
 * possible.
 * @param iNb
 *   the number of properties to be retrieved in the iPropArray array.
 * @param  iPropArray
 *   An array of CATSysProperty of iNb element allocated by the caller.
 *   At least the ID of the requested properties must have been set before
 *   the call.
 * @return
 *   S_OK on Success.
 *   STG_E_INVALIDPARAMETER if the iPropArray is not correctly set.
 *   STG_E_ACCESSDENIED the properties can not be queried for this ILockBytes.
*/
  virtual HRESULT __stdcall GetProperty( unsigned int iNb,
					 CATSysProperty * ioPropArray)=0;

  
/**
 * Sets the properties of an ILockBytes
 * <b>Role</b>:Sets the properties of an ILockBytes. There is no garantee
 * that the implementation will not need to open the ILockBytes in order
 * to retrieve some properties, however this must be avoided as much as 
 * possible.
 * @param iNb
 *   the number of properties to be retrieved in the iPropArray array.
 * @param  iPropArray
 *   An array of CATSysProperty of iNb element allocated by the caller.
 * @return
 *   S_OK on Success.
 *   STG_E_INVALIDPARAMETER if the iPropArray is not correctly set.
 *   STG_E_ACCESSDENIED the properties can not be queried for this ILockBytes.
*/
  virtual HRESULT __stdcall SetProperty( unsigned int iNb,
					 CATSysProperty * iPropArray)=0;

};

#endif



