
#ifndef CATSysTSCreateInstance_h
#define CATSysTSCreateInstance_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include "CATSysTSObjectModeler.h"
#include "IUnknown.h"
#include "CATCmpGuid.h"

/**
 * Creates an instance of the class associated with a specified CLSID.
 * Use the macros <tt>CATSysTSBeginClassObject</tt>, <tt>CATSysTSAddClassObject</tt>,
 * and <tt>CATSysTSEndClassObject</tt> to enable a component to be created 
 * with <tt>CATSysTSCreateInstance</tt>
 * @param iClsid
 *   The class identifier (CLSID) of the object
 * @param iInterfaceId
 *   The identifier of the requested interface
 * @param ppv
 *   The address of output variable that receives the interface pointer
 * @return
 *   <tt>S_OK</tt> if the creation succeeded, <tt>E_FAIL</tt> otherwise.
 */
HRESULT ExportedByCATSysTSObjectModeler CATSysTSCreateInstance(const CLSID& iClsid, const IID& iInterfaceId, void** ppv);


#define CATSysTSClassObject_Exported DSYExport
#include "DSYExport.h"

/**
 * Macros to enable a component to be created with CATSysTSCreateInstance.
 * Note : this macro must be present only once per shared library since it
 * defines the CATSysTSDllGetClassObject exported symbol.
 */
#define CATSysTSBeginClassObject \
 \
extern "C" HRESULT CATSysTSClassObject_Exported CATSysTSDllGetClassObject(const CLSID& iClsid, const IID& iInterfaceId, void ** ppv) \
{ \
	HRESULT hr = E_NOTIMPL;
	

#define CATSysTSAddClassObject(object)									\
	if (CATCmpGuid(&iClsid, &CLSID_##object)) {			\
		object * p##object = new object();									\
		hr = p##object->QueryInterface(iInterfaceId, ppv);	\
		p##object->Release();																\
		return hr;																					\
	}
	
#define CATSysTSAddClassObjectWithName(object, name)		\
	if (CATCmpGuid(&iClsid, &CLSID_##name)) {				\
		object * p##object = new object();									\
		hr = p##object->QueryInterface(iInterfaceId, ppv);	\
		p##object->Release();																\
		return hr;																					\
	}

#define CATSysTSEndClassObject \
	return hr; \
}


#endif // CATSysTSCreateInstance_h

