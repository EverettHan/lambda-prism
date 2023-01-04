#ifndef CATSysTSMacForTie_h
#define CATSysTSMacForTie_h

/* COPYRIGHT DASSAULT SYSTEMES 2004 */

#include "CATSysTSBaseUnknown.h"
#include "CATSysTSObjectModeler.h"

class ExportedByCATSysTSObjectModeler CATSysTSTIEInternal {
	
	public :

		/** 
		 * QueryInterface for TIE objects.
		 * iComponentImplementation : pointer to the component implementation
		 * iImplementationMeta      : pointer to interface implementation metaclass
		 * oNecessaryDataForTIE     : pointer to the NecessaryData.ForTIE
		 *		NecessaryData.ForTIE points
		 *					- for TIE on implementation base : to the implementation base
		 *					- for TIE on data extension : to the data extension
		 **/ 
		static HRESULT Tie_Construct(CATSysTSBaseUnknown * iComponentImplementation, CATSysTSMetaClass * iImplementationMeta, 
									 CATSysTSBaseUnknown * (*iCreationFunc)(), CATSysTSBaseUnknown *& oNecessaryDataForTIE);

		/** 
		 * QueryInterface for TIE objects.
		 *
		 * iData : pointer to the NecessaryData.ForTIE
		 *		NecessaryData.ForTIE points:
		 *					to the implementation base,	for TIE on implementation base
		 *					to the data extension,	for TIE on data extension
		 * iid : the requested interface iid
		 * ppv : the returned object
		 **/ 
		static HRESULT Tie_Query(CATSysTSBaseUnknown * iData, const IID& iid, void **ppv);
	
		/** 
		 * AddRef for TIE objects
		 *
		 * ioCRef : current TIE reference counter
		 * iData : pointer to the NecessaryData.ForTIE
		 *		NecessaryData.ForTIE points:
		 *					to the implementation base,	for TIE on implementation base
		 *					to the data extension,	for TIE on data extension
		 *					(ptstat points to the code extension)
		 **/
		static ULONG Tie_AddRef(LONG& ioCRef, CATSysTSBaseUnknown * iData);

		/** 
		 * Release for TIE objects.
		 *
		 * iThis : current TIE
		 * oDestruct: set to TRUE if the tie object must be deleted, FALSE otherwise 
		 * ioData : the NecessaryData.ForTIE
		 *		NecessaryData.ForTIE points:
		 *					to the implementation base,	for TIE on implementation base
		 *					to the data extension,	for TIE on data extension
		 **/
		static ULONG Tie_Release(LONG& ioCRef, CATSysTSBaseUnknown *& ioData, CATBoolean& oDestruct);
};

/**
 * @nodoc
 * Declaration of the common TIE members.
 */
#define CATSysTSDeclareCommonTIEMembers

/**
 * @nodoc
 * Declaration of the specific members for TIE which do not derive from CATSysTSBaseUnknown.
 */
#define CATSysTSDeclareNotBaseUnknownTIEMembers \
	CATSysTSTypeOfData NecessaryData; \
	LONG m_cRef;

/**
 * @nodoc
 * Declaration of the methods specific to TIE.
 */
#define CATSysTSDeclareTIEMethods(interface, classe) \
	TIE##interface##classe(CATSysTSBaseUnknown *pBaseImplImpl, CATBoolean iFullyThreadSafe); \
	private :	\
	virtual ~TIE##interface##classe();	\
	public :

/**
 * @nodoc
 * Declaration of the IUnknown methods for TIE.
 */
#define CATSysTSDeclareIUnknownMethodsForTIE \
	virtual HRESULT __stdcall QueryInterface(const IID &iid, void **ppv); \
	virtual ULONG __stdcall AddRef(); \
	virtual ULONG __stdcall Release();

/**
 * @nodoc
 * Declaration of the CATSysTSBaseUnknown methods for TIE.
 */
#define CATSysTSDeclareCATSysTSBaseUnknownMethodsForTIE \
	static CATSysTSMetaClass * __stdcall MetaObject(); \
	virtual CATSysTSMetaClass * __stdcall GetMetaObject() const;

/**
 * @nodoc
 * Initialization of the common static TIE members.
 */
#define CATSysTSDefineCommonTIEMembers(interface, classe)

/**
 * @nodoc
 * Implementation of the constructor of a TIE deriving from CATSysTSBaseUnknown.
 */
#define CATSysTSImplementTIEConstructor(interface, classe) \
TIE##interface##classe::TIE##interface##classe(CATSysTSBaseUnknown *pBaseImpl, CATBoolean iFullyThreadSafe) : interface(FALSE) { \
	CATSysTSTIEInternal::Tie_Construct(pBaseImpl,classe::MetaObject(),classe::CreateItself,NecessaryData.ForTIE); \
}

/**
 * @nodoc
 * Implementation of the constructor of a TIE NOT deriving from CATSysTSBaseUnknown.
 */
#define CATSysTSImplementNotBaseUnknownTIEConstructor(interface, classe) \
TIE##interface##classe::TIE##interface##classe(CATSysTSBaseUnknown *pBaseImpl, CATBoolean iFullyThreadSafe) : m_cRef(1) { \
	CATSysTSTIEInternal::Tie_Construct(pBaseImpl,classe::MetaObject(),classe::CreateItself,NecessaryData.ForTIE); \
}

/**
 * @nodoc
 * Implementation of the TIE destructor.
 */
#define CATSysTSImplementTIEDestructor(interface, classe) \
TIE##interface##classe::~TIE##interface##classe() { \
	NecessaryData.ForTIE = NULL; \
}

/**
 * @nodoc
 * Implementation of the methods specific to TIE deriving from CATSysTSBaseUnknown.
 */
#define CATSysTSImplementTIEMethods(interface, classe) \
CATSysTSImplementTIEConstructor(interface, classe) \
CATSysTSImplementTIEDestructor(interface, classe)

/**
 * @nodoc
 * Implementation of the methods specific to TIE NOT deriving from CATSysTSBaseUnknown.
 */
#define CATSysTSImplementNotBaseUnknownTIEMethods(interface, classe) \
CATSysTSImplementNotBaseUnknownTIEConstructor(interface, classe) \
CATSysTSImplementTIEDestructor(interface, classe)

/**
 * @nodoc
 * Implementation of the IUnknown methods for TIE.
 */
#define CATSysTSImplementIUnknownMethodsForTIE(interface, classe) \
HRESULT __stdcall TIE##interface##classe::QueryInterface(const IID &iid, void **ppv) { \
	return (CATSysTSTIEInternal::Tie_Query(NecessaryData.ForTIE, iid, ppv)); \
} \
	\
ULONG __stdcall TIE##interface##classe::AddRef() { \
	return (CATSysTSTIEInternal::Tie_AddRef(m_cRef, NecessaryData.ForTIE)); \
} \
	\
ULONG __stdcall TIE##interface##classe::Release() { \
	CATBoolean mustDestruct = FALSE; \
	ULONG ref = CATSysTSTIEInternal::Tie_Release(m_cRef, NecessaryData.ForTIE, mustDestruct); \
	if (mustDestruct) delete this; \
	return ref; \
}

/**
 * @nodoc
 * Implementation of the CATSysTSBaseUnknown methods for TIE.
 */
#define CATSysTSImplementCATSysTSBaseUnknownMethodsForTIE(interface, classe) \
CATSysTSMetaClass * __stdcall TIE##interface##classe::MetaObject() { \
	ExportedByCATSysTSObjectModeler CATSysTSMetaClass * CATSysTSFindOrCreateMetaObject(const char * iName, CATSysTSTypeOfClass iType, const GUID * iClassGuid, CATSysTSMetaClass * pBaseMeta, const char * iExtendedMet); \
	static CATSysTSMetaClass * s_meta_object = CATSysTSFindOrCreateMetaObject(#interface, CATSysTSTIE, &IID_##interface, interface::MetaObject(),0); \
	return s_meta_object; \
} \
	\
CATSysTSMetaClass * __stdcall TIE##interface##classe::GetMetaObject() const { \
	return (MetaObject()); \
}

/**
 * @nodoc
 * Implementation of the CATSysTSBaseUnknown methods for TIE.
 */
#define CATSysTSImplementCATSysTSBaseUnknownMethodsForNotBaseUnknownTIE(interface, classe) \
CATSysTSMetaClass * __stdcall TIE##interface##classe::MetaObject() { \
	ExportedByCATSysTSObjectModeler CATSysTSMetaClass * CATSysTSFindOrCreateMetaObject(const char * iName, CATSysTSTypeOfClass iType, const GUID * iClassGuid, CATSysTSMetaClass * pBaseMeta, const char * iExtendedMet); \
	static CATSysTSMetaClass * s_meta_object = CATSysTSFindOrCreateMetaObject(#interface, CATSysTSTIE, &IID_##interface, NULL,NULL); \
	return s_meta_object; \
} \
	\
CATSysTSMetaClass * __stdcall TIE##interface##classe::GetMetaObject() const { \
	return (MetaObject()); \
}

/**
 * @nodoc
 * Implementation of the creation function of the TIE.
 */
#define CATSysTSImplementTIECreation(interface, classe) \
extern "C" Exported IUnknown *CreateTIE##interface##classe(CATSysTSBaseUnknown *pBaseImpl, CATBoolean iFullyThreadSafe) { \
	return NULL; \
} \
extern "C" Exported IUnknown *CATSysTSCreate##interface##classe(CATSysTSBaseUnknown *pBaseImpl, CATBoolean iFullyThreadSafe) { \
	return ((IUnknown *) new TIE##interface##classe(pBaseImpl, iFullyThreadSafe)); \
}

/**
 * @nodoc
 * Implementation of the creation function of the TIEchain.
 */
#define CATSysTSImplementTIEchainCreation(interface, classe) \
extern "C" Exported IUnknown *CreateTIE##interface##classe(CATSysTSBaseUnknown *pt = NULL) { \
	return NULL; \
} \
extern "C" Exported IUnknown *CATSysTSCreate##interface##classe(CATSysTSBaseUnknown *pt = NULL) { \
	return NULL; \
}

/**
 * @nodoc
 */
#define CATSysTSTie_MethodCaller() NecessaryData.ForTIE

	
#endif // CATSysTSMacForTie_h
