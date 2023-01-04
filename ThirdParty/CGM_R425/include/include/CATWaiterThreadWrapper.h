

// COPYRIGHT DASSAULT SYSTEMES 2000

//--------------------------------------------------------------------------------------------------------------------

//class d'encapsulation de CATWaiterThread


//-----------------------------------------------------------------------------------------------------------------------
#ifdef _WINDOWS_SOURCE

#ifndef CATWaiterThreadWrapper_H
#define CATWaiterThreadWrapper_H

//include
#include <wtypes.h>
#include "JS0MT.h"
#include "CATThrMessage.h"
#include "CATHandleCB.h"

//forwards
class CATWaiterThread;




class ExportedByJS0MT CATWaiterThreadWrapper
{
public :

	static CATWaiterThreadWrapper* GetWaiterThread();
	~CATWaiterThreadWrapper();

	CATThrResult AddHandle(HANDLE h, CATHandleCB *iCB, BOOL mt = FALSE);
	CATHandleCB* RemoveHandle(HANDLE h);



private :

CATWaiterThreadWrapper();


CATWaiterThread*	_TheWaiter;

static CATWaiterThreadWrapper* _TheSingleton;

};




#endif // _CATWaiterThreadWrapper
#endif // _WINDOWS_SOURCE
