#ifndef CATSysTSMacForIUnknown_h
#define CATSysTSMacForIUnknown_h

// COPYRIGHT DASSAULT SYSTEMES 2004

#include <stdio.h>
#include "CATSysTSObjectModeler.h"
#include "CATSysTSMetaClass.h"
#include "CATSysTSFillDictionary.h"

/**
 * @nodoc
 */
#ifdef  _AIX_SOURCE
#define Exported  
#else
#define Exported DSYExport
#endif
/**
 * @nodoc
 */
#ifdef  _AIX_SOURCE
#define Imported
#else
#define Imported DSYImport
#endif

#include "DSYExport.h"
/**
 * @nodoc
 * internal macros 
 */
#define MacCreateCATSysTSImplementation(Class) \
return(NULL);
/**
 * @nodoc 
 * internal macros 
 */
#define MacCreateCATSysTSDataExtension(Class)	\
  return(new Class);

#define MacCreateCATSysTSCacheExtension(Class)	\
  return(new Class);


/**
 * Declares an interface class.
 * <b>Role</b>: Declares that the current class is an interface.
 * Use this macro in the class header file in conjunction with @href CATSysTSImplementInterface
 * in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATSysTSDeclareInterface(InterfaceName)					\
																\
	public :													\
		InterfaceName(CATBoolean iFullyThreadSafe);				\
		static CATSysTSMetaClass * __stdcall MetaObject();		\
		static const char * __stdcall ClassName()

/**
 * Declares an interface class.
 * <b>Role</b>: Declares that the current class is an interface class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATSysTSDeclareInterface.
 * in the class header file.
 * End it with a semicolon.
 * @param InterfaceName
 *   Interface class name
 * @param BaseInterface
 *   Interface class from which <tt>InterfaceName</tt> derives 
 */
#define CATSysTSImplementInterface(InterfaceName, BaseInterface)									\
																									\
InterfaceName::InterfaceName(CATBoolean iFullyThreadSafe) : BaseInterface(iFullyThreadSafe) {}		\
																									\
CATSysTSMetaClass * __stdcall InterfaceName::MetaObject() {											\
																									\
	ExportedByCATSysTSObjectModeler CATSysTSMetaClass * CATSysTSFindOrCreateMetaObject(const char * iName, CATSysTSTypeOfClass iType, const GUID * iClassGuid, CATSysTSMetaClass * pBaseMeta, const char * iExtendedMeta);\
	static CATSysTSMetaClass * s_meta_object = CATSysTSFindOrCreateMetaObject(#InterfaceName,CATSysTSInterface,&IID_##InterfaceName,BaseInterface::MetaObject(),0); \
	return s_meta_object; 																			\
}																									\
																									\
const char * __stdcall InterfaceName::ClassName()	{												\
   return MetaObject()->IsA();																		\
}																									\
static int InitMetaObjectName##InterfaceName = CATSysTSFillDictionary::InitMetaClasses(InterfaceName::MetaObject())

/**
 * Declares an implementation or extension class.
 * <b>Role</b>: Declares that the current class is either
 * an implementation or an extension class.
 * The class must derive from @href CATSysTSBaseUnknown.
 * Use this macro in the class header file in conjunction with @href CATSysTSImplementClass
 * in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATSysTSDeclareClass													\
																				\
	public :																	\
		virtual CATSysTSMetaClass * __stdcall GetMetaObject() const;			\
		static CATSysTSMetaClass * __stdcall MetaObject();						\
		static CATSysTSBaseUnknown * CreateItself();							\
		static const CLSID & __stdcall ClassId();								\
		static const char * __stdcall ClassName()


/**
 * Begins an implementation or extension definition sequence.
 * <b>Role</b>: Begins a macro sequence for <tt>Class</tt> to declare that it implements
 * interfaces as an extension of the <tt>Impmeta</tt> class.
 * Replaces the @href CATSysTSImplementClass macro when <tt>Class</tt> extends several
 * implementation classes.
 * To be used in conjunction with the @href CATSysTSAddClassExtension macro to declare other
 * extended implementation classes and 
 * @href CATSysTSEndImplementClass macro to end the class declaration sequence.
 * Use this macro in the <tt>Class</tt> source (.cpp) file.
 * Do not end it with a semicolon.
 * @param Class
 * 	The current implementation or extension class
 * @param Typeofclass
 * 	The extension type
 * 	<br><b>Legal values</b>: it can be set to <tt>CATSysTSImplementation</tt> or <tt>CATSysTSDataExtension</tt>
 * @param BaseMeta
 * 	The class from which <tt>Class</tt> CNext-derives.
 * @param Impmeta
 * 	The implementation class for which <tt>Class</tt> is an extension. Must be set to <tt>CATSysTSNull</tt>
 */
#define CATSysTSBeginImplementClass(Class, Typeofclass, BaseMeta, Impmeta)									\
																											\
CATSysTSMetaClass * __stdcall Class::GetMetaObject() const {												\
   return MetaObject();																						\
}																											\
																											\
const CLSID & __stdcall Class::ClassId() {																	\
   return MetaObject()->GetClassId();																		\
}																											\
																											\
const char * __stdcall Class::ClassName() {																	\
   return MetaObject()->IsA();																				\
} 																											\
																											\
CATSysTSBaseUnknown * Class::CreateItself() {																\
   MacCreate##Typeofclass(Class)																			\
}																											\
																											\
CATSysTSMetaClass * __stdcall Class::MetaObject() {															\
 ExportedByCATSysTSObjectModeler CATSysTSMetaClass * CATSysTSFindOrCreateMetaObject(const char * iName, CATSysTSTypeOfClass iType, const GUID * iClassGuid, CATSysTSMetaClass * pBaseMeta, const char * iExtendedMeta);                       \
                                                                                                            \
    static CATSysTSMetaClass * s_meta_object = []() -> CATSysTSMetaClass * {								\
		const char * ExtendedMeta = ((Typeofclass==CATSysTSDataExtension)||(Typeofclass==CATSysTSCacheExtension))?(#Impmeta):(0);\
		CATSysTSMetaClass * _meta_object = CATSysTSFindOrCreateMetaObject(#Class, Typeofclass, NULL, BaseMeta::MetaObject(), ExtendedMeta)
		
		
/**
 * Ends an extension declaration sequence.
 * <b>Role</b>: Ends the declaration sequence for the <tt>Class</tt> class which implements
 * interfaces as an extension of several other implementation classes.
 * To be used in conjunction with @href CATSysTSBeginImplementClass macro to begin
 * the extension declaration sequence and
 * @href CATSysTSAddClassExtension macro to declare other
 * extended implementation classes.
 * Use this macro in the <tt>Class</tt> source (.cpp) file.
 * Do not end it with a semicolon.
 * @param Class
 *   The current extension class
 */
#define CATSysTSEndImplementClass(Class)			\
       return _meta_object;									\
   }();												\
   return(s_meta_object);							\
}


/**
 * Declares an implementation or extension class.
 * <b>Role</b>: Declares that the current class is either
 * an implementation or an extension class.
 * The class must derive from CATSysTSBaseUnknown.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATSysTSDeclareClass
 * in the class header file.
 * End it with a semicolon.
 * @param Class
 *   The name of the class
 * @param Typeofclass
 *   The class type.
 *   <br><b>Legal values:</b>: it can be set to <tt>CATSysTSImplementation</tt> or <tt>CATSysTSDataExtension</tt>
 * @param BaseMeta
 *   The class from which <tt>Class</tt> CNext-derives.
 *   <br><b>Legal values:</b>: it makes sense for implementation classes only.
 *   Set it to the name of the CNext base class for an implementation, and to
 *   @href CATSysTSBaseUnknown or <tt>CATSysTSNull</tt> for the three extension types
 * @param Impmeta
 *   The class for which <tt>Class</tt> is an extension.
 *   <br><b>Legal values:</b>: it makes sense for extension classes only.
 *   Set it to the implementation class name for the three extension types,
 *   and to <tt>CATSysTSNull</tt> for an implementation
 */
#define CATSysTSImplementClass(Class, Typeofclass, BaseMeta, Impmeta)	\
CATSysTSBeginImplementClass(Class, Typeofclass, BaseMeta, Impmeta);		\
CATSysTSEndImplementClass(Class)

class ExportedByCATSysTSObjectModeler CATSysTSBOAInternal {
	public :
	
		/** 
		 * BOA construction
		 *
		 * pBaseImpl : pointer to the implementation base
		 **/ 
		static IUnknown * CreateBOA(CATSysTSBaseUnknown * iComponentImplementation, CATSysTSMetaClass * iImplementationMeta, 
									CATSysTSBaseUnknown * (*iCreationFunc)());	
};

/**
 * Macro used to declare a BOA.
 * <b>Role</b>: Declares a class that implements an interface when this class
 * derives from the interface class. This is known as the basic
 * object adaptor (BOA). Use this macro in the source (.cpp) file
 * of the class that implements the interface.
 * @param interfaceName
 *   Interface name
 * @param className
 *   Class name which implements the interface
 */
#define CATSysTSImplementBOA(interfaceName, classe)																						\
																																		\
extern "C" Exported IUnknown * CATSysTSCreate##interfaceName##classe(CATSysTSBaseUnknown * pBaseImpl, CATBoolean iFullyThreadSafe) { 	\
	return CATSysTSBOAInternal::CreateBOA(pBaseImpl,classe::MetaObject(),classe::CreateItself);											\
}																																		\
																																		\
static int InitMetaObj##interfaceName##classe = CATSysTSFillDictionary::InitMetaClasses(classe::MetaObject(),interfaceName::MetaObject())

#endif // CATSysTSMacForIUnknown_h
