// COPYRIGHT Dassault Systemes 2000
//
#ifndef CATechSharedMemory_H
#define CATechSharedMemory_H

#include <CATString.h>
#include "ExportedByCATTechTools.h"

class CATHashDico;

/**
 * Object for direct file read/write (file mapping)
 **/
class  ExportedByCATTechTools CATechSharedMemory
{
public:
	/**
	 * Create
	 * iMode : 0 for read only, 1 for read/write
	 * iSize : size, 0 to get current file size
	 **/
	CATechSharedMemory( const CATString &iFileName, int iMode, int iSize, const CATHashDico *iKeyValue );

	/**
	 * Destructor
	 **/
  ~CATechSharedMemory( void );
 
	/**
	 * Get buffer
	 **/
	void *GetBuffer( void );
	/**
	 * Get buffer size
	 **/
	int   GetSize( void );
 
private:
	CATString _filename;
	void *_buffer;
	int   _size;
};

#endif
