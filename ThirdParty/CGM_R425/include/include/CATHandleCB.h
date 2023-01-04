#ifndef CATHandleCB_H
#define CATHandleCB_H



// COPYRIGHT DASSAULT SYSTEMES 2000


struct CATHandleCB
{
	void (*func)( void *clidat, HANDLE h, void *iId);
	void *Data;
	HANDLE h;
	void* AddData;
	int flags;
};

#endif
