//*===========================================================================*
//* COPYRIGHT DASSAULT SYSTEMES 2003                                          *
//*===========================================================================*
//*                                                                           *
//*  CATILockBytes2                                                           *
//*                                                                           *
//*  Usage Notes:                                                             *
//*===========================================================================*
//*  Creation july 2003                                                       *
//*===========================================================================*
#ifndef __CATILOCKBYTES2
#define __CATILOCKBYTES2

#include "CATILockBytes.h"
#include "JS0BASEILB.h"
#include <time.h>

#define CATSTGM_SEQUENTIAL		0x00000400



extern ExportedByJS0BASEILB IID IID_CATILockBytes2;

class  CATILockBytes2 : public CATILockBytes
{
public:
        
/**
 * Defines the way to open the ILockbytes
 * <b>Role</b>:Defines the way to open the ILockBytes.
 * @param iMode 
 *   the opening mode.
 *	<b>Legal values</b>:
 *	<br><tt>STGM_READ :</tt>   for read acces 
 * 	<br><tt>,STGM_WRITE:</tt>  for write acces
 * @param  iFlag 
 *  Tells if we will make a full save , interesting for Enovia Performance)
 * @param iSize
 * the size of the Document : in Case of Open Write.
 * @return
 *   S_OK on Success.
*/
  virtual HRESULT __stdcall Open( DWORD iMode,
				  DWORD iFlag, 
				  time_t iTS = 0,
				  ULARGE_INTEGER *iSize=NULL) = 0;
  
/**
 * Closes the ILockBytes.
 * <b>Role</b>: Closes the ILockBytes but the ressources remain available.
 * @return
 *	<b>Legal values</b>:
 *	<br><tt>S_OK :</tt>   on Success
*/
  virtual HRESULT __stdcall Close( DWORD iFlag =0) = 0;

 /**
  * Purges the Resources associated with the File
  * <b>Role</b>: Purges the Resources associated associated to the ILockBytes
  * @return
  *	<b>Legal values</b>:
  *	<br><tt>S_OK :</tt>   on Success
*/
  virtual HRESULT __stdcall Purge() = 0;


};

#endif



