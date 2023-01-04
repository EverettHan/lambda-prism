#ifndef __CATMacForIUnknown
#define __CATMacForIUnknown     42500

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "JS0CORBA.h"
#include "CATFillDictionary.h"  // Includes CATBaseUnknown.h
#include "CATMetaClass.h"
#include "CATMacForCodeActivation.h"
#include "CATOMInitializer.h"   // CATOMInitializerProlog / CATOMInitializerEpilog
#include "DSYExport.h"
#include <stdio.h>
#include <atomic>

/**
 * @nodoc
 */
#ifndef Exported
#define Exported DSYExport
#endif

/**
 * @nodoc
 */
#ifndef Imported
#define Imported DSYImport
#endif

#ifndef _MK_FWNAME_
/**
 * @nodoc
 */
#define CATLicenseOptionId NULL
#else
/**
 * @nodoc
 */
#define _guillemets_prec(arg) #arg
/**
 * @nodoc
 */
#define _guillemets(arg) _guillemets_prec(arg)
/**
 * @nodoc
 */
#define CATLicenseOptionId _guillemets(_MK_FWNAME_)
#endif

#if __cplusplus >= 202002L
/** @nodoc */
#define CATMacAttributeLikely       [[likely]]
/** @nodoc */
#define CATMacAttributeUnlikely     [[unlikely]]
#else
/** @nodoc */
#define CATMacAttributeLikely
/** @nodoc */
#define CATMacAttributeUnlikely
#endif

#if defined(_MSC_VER)
/** @nodoc */
#define CATMacAttributeNoInline     __declspec(noinline)
#else
/** @nodoc */
#define CATMacAttributeNoInline     __attribute__((noinline))
#endif


/**
 * @nodoc
 * internal macros used to create extensions
 */
#define MacCreateImplementation(Class)					\
return(NULL);
/**
 * @nodoc
 */
#define MacCreateDataExtension(Class)					\
return(new Class);
/**
 * @nodoc
 */
#define MacCreateCodeExtension(Class)					\
MacCreateDataExtension(Class)
/**
 * @nodoc
 */
#define MacCreateCacheExtension(Class)					\
MacCreateDataExtension(Class)
/**
 * @nodoc
 */
#define MacCreateTransientExtension(Class)					\
MacCreateDataExtension(Class)


/**
 * @nodoc
 * Calls QueryInterface in a more concise form and checks that the returned
 * pointer is compatible with the requested interface.
 * @param interfac
 *   Interface name
 * @param object
 *   Pointer to the object or to the interface for which <tt>interfac</tt>
 *   is requested
 * @return The pointer to the requested interface.
 */
#define CATMacQI(interfac,object)					\
((interfac *)dsy::internal::QueryMacQI((const CATBaseUnknown *)((object)->GetImpl()),	\
   		        interfac::ClassId()))

/**
 * @nodoc
 * Returns the pointer to the implementation.
 * To be used only in an extension code.
 * @param impl
 *   Implementation class name
 */
#define CATMacGetImpl(impl)	((impl *)GetImpl())

/** @nodoc Trigger a compilation error for BOA classes that don't inherit from the interface */
#define BOAMustDerivateFromInterface(interfac,extension) [[maybe_unused]] interfac* dummy = (extension*)NULL;

/**
 * Macro used to declare a BOA.
 * <b>Role</b>: Declares a class that implements an interface when this class
 * derives from the interface class. This is known as the basic
 * object adaptor (BOA). Use this macro in the source (.cpp) file
 * of the class that implements the interface.
 * @param interfac
 *   Interface name
 * @param extension
 *   Class name which implements the interface
 */
#define CATImplementBOA(interfac,extension)                             \
extern "C" Exported IUnknown *						\
		CreateBOA##interfac##extension(CATBaseUnknown *pt,	\
					       CATBaseUnknown *delegue)	\
{                                                \
   BOAMustDerivateFromInterface(interfac,extension) \
                                                                        \
   return(ToCreateBOA(pt,delegue,extension::MetaObject(),IID_##interfac,\
            extension::CreateItself));                                  \
}                                                                       \
                                                                        \
CATOMInitializerProlog(Dico##interfac##extension)           \
  CATFillDictionary Dico##interfac##extension               \
			(extension::MetaObject(),interfac::MetaObject(),\
			(void *)CreateBOA##interfac##extension);        \
CATOMInitializerEpilog(Dico##interfac##extension)

/**
 * @nodoc
 * Declares an extension class.
 * <b>Role</b>: Declares a class as an extension of an implementation class
 * @param extension
 *   Class name which implements the extension
 */
#define CATImplementExtension(extension)    	                        \
extern "C" Exported IUnknown *						\
		CreateEXT##extension(CATBaseUnknown *pt,		\
				     CATBaseUnknown *delegue)		\
{                                                                       \
   return(ToCreateBOA(pt,delegue,extension::MetaObject(),		\
   		      extension::ClassId(),extension::CreateItself));	\
}                                                                       \
                                                                        \
CATOMInitializerProlog(DicoEXT##extension)                  \
  CATFillDictionary DicoEXT##extension                      \
		(extension::MetaObject(),extension::MetaObject(),   \
		(void *)CreateEXT##extension);                      \
CATOMInitializerEpilog(DicoEXT##extension)


/**
 * Declares an implementation or extension class.
 * <b>Role</b>: Declares that the current class is either
 * an implementation or an extension class.
 * The class must derive from @href CATBaseUnknown.
 * Use this macro in the class header file in conjunction with @href CATImplementClass
 * in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATDeclareClass                                     \
                                                            \
private :                                                   \
   CATMetaClassStaticCheck                                  \
public :                                                    \
   virtual CATMetaClass *  __stdcall GetMetaObject() const; \
   virtual const char *              IsA() const;           \
   virtual int                       IsAKindOf(const char *) const; \
   static CATMetaClass *   __stdcall MetaObject();          \
   static const CLSID &    __stdcall ClassId();             \
   static const char *     __stdcall ClassName();           \
   static CATBaseUnknown *CreateItself()


/**
 * @nodoc
 */
#define ToCreateMetaObject(Class,Typeofclass,Basemeta,Impmeta)		\
meta_object = dsy::internal::fct_RetrieveMetaObject(#Class,Typeofclass,		\
				     Basemeta::MetaObject(),#Impmeta,CATLicenseOptionId,sizeof(Class))


/**
 * @nodoc
 */
#if defined(CATIMPLEMENTCLASS_MUST_DERIVATE_FROM_CATBASEUNKNOWN)
// Once the migration is finished, 'CATDeclareClass' could be updated to use the qualifier 'override'
#define CATImplementClassMustDerivateFromCATBaseUnknown(Class)  static_assert(std::is_base_of<CATBaseUnknown, Class>::value, \
    " BADREM : 121026 CATImplementClass macro must be used with a class that derivates from CATBaseUnknown");
#else
#define CATImplementClassMustDerivateFromCATBaseUnknown(Class)
#endif


/** @nodoc CATMacMetaObjectMethodProlog.
 * [NOTE] The function 'Class::MetaObject' sets the 's_meta_object' static variable, potentially during static initialization phase.
 * However, there is no risk of initialization order fiasco, as 's_meta_object' is expected to be 'constant initialized';
 * that is, fully constructed before any other initialization of a static objects begins.
 * (Because it is a static instance of the std::atomic class, which uses a constexpr constructor)
 */
#define CATMacMetaObjectMethodProlog(Class)	                                    \
                                                                                \
CATMetaClass * __stdcall Class::MetaObject() {                                  \
    /* One reason for defining s_meta_object locally is to avoid warning C4251*/\
    static std::atomic<CATMetaClass *> s_meta_object {nullptr};                 \
    /* On architectures with a strong memory model, such as x86-64, */          \
    /* the code emitted for this atomic load is identical to a regular load */  \
    CATMetaClass * meta_object = s_meta_object.load(std::memory_order_acquire); \
    if (meta_object) CATMacAttributeLikely /* Fast path */ {                    \
        return meta_object;                                                     \
    }                                                                           \
    struct MetaObjectInit {                                                     \
        CATMacAttributeNoInline /* Performance: ensure that the compiler doesn't inline the initialization code */\
        /* may be useless on platforms on which 'CATMacAttributeLikely' is supported */\
        static CATMetaClass* DoMetaObjectInit(std::atomic<CATMetaClass *> & iMetaObjectAtomPtr) { \
                                                                                    \
            dsy::internal::om_guard _om_guard_;                                     \
            CATMetaClass * meta_object = iMetaObjectAtomPtr.load(std::memory_order_acquire);\
            if(meta_object) return meta_object; /* End of DCLP */


/** @nodoc CATMacMetaObjectMethodEpilog variables: initialized 'meta_object' + 'iMetaObjectAtomPtr' */
#define CATMacMetaObjectMethodEpilog(Class) \
            iMetaObjectAtomPtr.store(meta_object, std::memory_order_release);\
            return (meta_object);   \
        } /* End of MetaObjectInit::DoMetaObjectInit */     \
    };                              \
    return MetaObjectInit::DoMetaObjectInit(s_meta_object); \
}


/**
 * Begins an extension definition sequence.
 * <b>Role</b>: Begins a macro sequence for <tt>Class</tt> to declare that it implements
 * interfaces as an extension of the <tt>Impmeta</tt> class.
 * Replaces the @href CATImplementClass macro when <tt>Class</tt> extends several
 * implementation classes.
 * To be used in conjunction with the @href CATAddClassExtension macro to declare other
 * extended implementation classes and 
 * @href CATEndImplementClass macro to end the extension declaration sequence.
 * Use this macro in the <tt>Class</tt> source (.cpp) file.
 * Do not end it with a semicolon.
 * @param Class
 *   The current extension class
 * @param Typeofclass
 *   The extension type
 *   <br><b>Legal values</b>: it can be set to <tt>DataExtension</tt>,
 *   <tt>CodeExtension</tt>, <tt>CacheExtension</tt> or <tt>TransientExtension</tt>
 * @param Basemeta
 *   The class from which <tt>Class</tt> CNext-derives.
 *   <br><b>Legal values:</b>: must be set to @href CATBaseUnknown or <tt>CATNull</tt>
 * @param Impmeta
 *   The implementation class for which <tt>Class</tt> is an extension
 */
#define CATBeginImplementClass_Real(Class,Typeofclass,Basemeta,Impmeta)	\
									\
CATMetaClass * __stdcall Class::GetMetaObject() const			\
{									\
   return(MetaObject());			\
}									\
									\
const CLSID & __stdcall Class::ClassId()				\
{									\
   return(MetaObject()->GetClassId()); \
}									\
const char * __stdcall Class::ClassName()				\
{									\
   return(MetaObject()->IsA());		\
}									\
const char *Class::IsA() const						\
{									\
   return(MetaObject()->IsA());		\
}									\
int Class::IsAKindOf(const char *ident) const				\
{									\
   return(MetaObject()->IsAKindOf(ident)); \
}									\
									\
CATBaseUnknown *Class::CreateItself()					\
{									\
   MacCreate##Typeofclass(Class)					\
}									\
									\
CATMacMetaObjectMethodProlog(Class) \
                                    \
    CATImplementClassMustDerivateFromCATBaseUnknown(Class)  \
    ToCreateMetaObject(Class,Typeofclass,Basemeta,Impmeta)

/**
 * @nodoc
 * Internal use.
 */
#ifdef New_TIE_Invoke
namespace{template <typename Type> short TIE_IsCodeExtension();}
#define IsCodeExtensionImplementation(Class, Typeofclass) namespace{template <> inline short TIE_IsCodeExtension<Class>(){return Typeofclass==CodeExtension;};}
#endif

/**
 * Begins an extension definition sequence.
 * <b>Role</b>: Begins a macro sequence for <tt>Class</tt> to declare that it implements
 * interfaces as an extension of the <tt>Impmeta</tt> class.
 * Replaces the @href CATImplementClass macro when <tt>Class</tt> extends several
 * implementation classes.
 * To be used in conjunction with the @href CATAddClassExtension macro to declare other
 * extended implementation classes and 
 * @href CATEndImplementClass macro to end the extension declaration sequence.
 * Use this macro in the <tt>Class</tt> source (.cpp) file.
 * Do not end it with a semicolon.
 * @param Class
 *   The current extension class
 * @param Typeofclass
 *   The extension type
 *   <br><b>Legal values</b>: it can be set to <tt>DataExtension</tt>,
 *   <tt>CodeExtension</tt>, <tt>CacheExtension</tt> or <tt>TransientExtension</tt>
 * @param Basemeta
 *   The class from which <tt>Class</tt> CNext-derives.
 *   <br><b>Legal values:</b>: must be set to @href CATBaseUnknown or <tt>CATNull</tt>
 * @param Impmeta
 *   The implementation class for which <tt>Class</tt> is an extension
 */
#ifdef New_TIE_Invoke
#define CATBeginImplementClass(Class,Typeofclass,Basemeta,Impmeta) \
    IsCodeExtensionImplementation(Class, Typeofclass)\
	CATBeginImplementClass_Real(Class,Typeofclass,Basemeta,Impmeta)
#else
#define CATBeginImplementClass(Class,Typeofclass,Basemeta,Impmeta) \
	CATBeginImplementClass_Real(Class,Typeofclass,Basemeta,Impmeta)
#endif

/**
 * Ends an extension declaration sequence.
 * <b>Role</b>: Ends the declaration sequence for the <tt>Class</tt> class which implements
 * interfaces as an extension of several other implementation classes.
 * To be used in conjunction with @href CATBeginImplementClass macro to begin
 * the extension declaration sequence and
 * @href CATAddClassExtension macro to declare other
 * extended implementation classes.
 * Use this macro in the <tt>Class</tt> source (.cpp) file.
 * Do not end it with a semicolon.
 * @param Class
 *   The current extension class
 */
#define CATEndImplementClass(Class) \
CATMacMetaObjectMethodEpilog(Class) \
                                    \
static_assert(true, ""/*CATEndImplementClass requires an ending semicolon*/)


/**
 * Continues an extension declaration sequence.
 * <b>Role</b>: Declares that the current class is an extension of the <tt>impl</tt> class.
 * To be used in conjunction with the @href CATBeginImplementClass macro to begin
 * the extension declaration sequence and
 * @href CATEndImplementClass macro to end it.
 * Use this macro in the class source (.cpp) file.
 * Do not end it with a semicolon.
 * @param impl
 *   The implementation class for which the current class is an extension
 */
#define CATAddClassExtension(impl)					\
meta_object->SetExtensionOf(dsy::internal::fct_FindMetaObject(#impl))


/**
 * Declares an implementation or extension class.
 * <b>Role</b>: Declares that the current class is either
 * an implementation or an extension class.
 * The class must derive from CATBaseUnknown.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareClass
 * in the class header file.
 * End it with a semicolon.
 * @param Class
 *   The name of the class
 * @param Typeofclass
 *   The class type.
 *   <br><b>Legal values:</b>: it can be set to <tt>Implementation</tt>, <tt>DataExtension</tt>,
 *   <tt>CodeExtension</tt>, <tt>CacheExtension</tt> or <tt>TransientExtension</tt>
 * @param Basemeta
 *   The class from which <tt>Class</tt> CNext-derives.
 *   <br><b>Legal values:</b>: it makes sense for implementation classes and extensions in BOA mode.
 *   For an implementation, set it to the name of the CNext base class.
 *   For an extension implementing an interface in BOA mode, set it to the name of the interface.
 *   For other kind of extensions, set it to @href CATBaseUnknown or <tt>CATNull</tt>. 
 * @param Impmeta
 *   The class for which <tt>Class</tt> is an extension.
 *   <br><b>Legal values:</b>: it makes sense for extension classes only.
 *   Set it to the implementation class name for the three extension types,
 *   and to <tt>CATNull</tt> for an implementation
 */
#define CATImplementClass(Class,Typeofclass,Basemeta,Impmeta)		\
CATBeginImplementClass(Class,Typeofclass,Basemeta,Impmeta);		\
CATEndImplementClass(Class)

/**
 * @nodoc
 */
#define CATImplementClass_Deprecated(Class,Typeofclass,Basemeta,Impmeta)		\
CATBeginImplementClass_Real(Class,Typeofclass,Basemeta,Impmeta);		\
CATEndImplementClass(Class)


/**
 * @nodoc
 * Adds externally a supported implementation to a TIE extension
 * for a given interface.
 */
#define CATSupportImplementation(extension,impl,interf)			\
extern "C" Imported IUnknown *CreateTIE##interf##extension		\
		       (const CATBaseUnknown *, const CATBaseUnknown *);\
CATOMInitializerProlog(_Dico##impl##extension##interf)          \
  CATFillDictionary _Dico##impl##extension##interf(             \
		extension::MetaObject(),                                \
		interf::MetaObject(),#impl,                             \
		(void *)CreateTIE##interf##extension);                  \
CATOMInitializerEpilog(_Dico##impl##extension##interf)

/**
 * @nodoc
 * Adds externally a supported implementation to a BOA extension
 * for a given interface.
 */
#define CATSupportImplementationForBOA(extension,impl,interf)			\
extern "C" Imported IUnknown *CreateBOA##interf##extension(const CATBaseUnknown *, const CATBaseUnknown *); \
CATOMInitializerProlog(_Dico##impl##extension##interf)          \
  CATFillDictionary _Dico##impl##extension##interf(             \
		extension::MetaObject(),                                \
		interf::MetaObject(),#impl,                             \
		(void *)CreateBOA##interf##extension);                  \
CATOMInitializerEpilog(_Dico##impl##extension##interf)


/**
 * Declares an interface class.
 * <b>Role</b>: Declares that the current class is an interface.
 * Use this macro in the class header file in conjunction with @href CATImplementInterface
 * in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATDeclareInterface                             \
                                                        \
private :                                               \
   CATMetaClassStaticCheck                              \
public :                                                \
   static CATMetaClass * __stdcall MetaObject();        \
   static const IID &    __stdcall ClassId();           \
   static const char *   __stdcall ClassName()

/**
 * @nodoc
 */
#define CATBeginImplementInterface(Class, Basemeta, Alias)		\
									\
CATMacMetaObjectMethodProlog(Class) \
                                    \
    meta_object = new CATMetaClass(&IID_##Class,#Alias,		\
				     Basemeta::MetaObject(),NULL,	\
				     Interfaces)

#define CATImplementInterface_AddNamed(Alias) \
	 meta_object->SetAlias(#Alias);
	 
#define CATImplementInterface_AddLicensed \
	 meta_object->SetAuth(0);

#define CATImplementInterface_AddIntrospectable(ModuleName) \
	meta_object->SetIntroLibrary(#ModuleName);
	
#define CATImplementInterface_AddMandatoryAdapter(AdapterName) \
	meta_object->SetMandatoryAdapter(#AdapterName);

/**
 * @nodoc
 */
#define CATEndImplementInterface(Class, Basemeta, Alias)        \
                                                                \
    AddDictionary(&IID_##Class,&CLSID_CATMetaClass,             \
             #Alias,"MetaObject",NULL,(void *)meta_object);     \
    meta_object->SetFWname(CATLicenseOptionId);                 \
                                                                \
CATMacMetaObjectMethodEpilog(Class)                             \
                                                                \
const IID &  __stdcall Class::ClassId()                         \
{                                                               \
   return MetaObject()->GetClassId();                           \
}                                                               \
const char * __stdcall Class::ClassName()                       \
{                                                               \
   return MetaObject()->IsA();                                  \
}                                                               \
                                                                \
CATOMInitializerProlog(DicoMeta##Class)                         \
  CATFillDictionary DicoMeta##Class(IID_##Class,CLSID_CATMetaClass,\
                        (void *)Class::MetaObject());           \
CATOMInitializerEpilog(DicoMeta##Class)


/**
 * Declares an interface class.
 * <b>Role</b>: Declares that the current class is an interface class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareInterface.
 * in the class header file.
 * End it with a semicolon.
 * @param Class
 *   Interface class name
 * @param Basemeta
 *   Interface class from which <tt>Class</tt> derives 
 */
#define CATImplementInterface(Class, Basemeta)				\
CATBeginImplementInterface(Class,Basemeta,Class);			\
CATEndImplementInterface(Class,Basemeta,Class)


/**
 * @nodoc
 * Declares that the current class is a licensed interface class.
 * Use this macro in the source (.cpp) file of the class.
 * @param Class
 *   Interface class name
 * @param Basemeta
 *   Interface class from which <tt>Class</tt> derives 
 */
#define CATImplementLicensedInterface(Class, Basemeta)			\
CATBeginImplementInterface(Class,Basemeta,Class);				\
CATImplementInterface_AddLicensed								\
CATEndImplementInterface(Class,Basemeta,Class)


/**
 * @nodoc
 * Declares that the current class is an interface class.
 * Declares also an alias associated to the interface.
 * Use this macro in the source (.cpp) file of the class.
 * @param Class
 *   Interface class name
 * @param Basemeta
 *   Interface class from which <tt>Class</tt> derives 
 * @param Alias
 *   Alias name of the interface
 */
#define CATImplementNamedInterface(Class, Basemeta, Alias)		\
CATBeginImplementInterface(Class,Basemeta,Class);				\
CATImplementInterface_AddNamed(Alias)							\
CATEndImplementInterface(Class,Basemeta,Class)


/**
 * @nodoc
 * Declares that the current class is a licensed interface class.
 * Declares also an alias associated to the interface.
 * Use this macro in the source (.cpp) file of the class.
 * @param Class
 *   Interface class name
 * @param Basemeta
 *   Interface class from which <tt>Class</tt> derives 
 * @param Alias
 *   Alias name of the interface
 */
#define CATImplementNamedLicensedInterface(Class, Basemeta, Alias)	\
CATBeginImplementInterface(Class,Basemeta,Class);			\
CATImplementInterface_AddNamed(Alias)						\
CATImplementInterface_AddLicensed							\
CATEndImplementInterface(Class,Basemeta,Class)


#define CATImplementNamedLicensedIntrospectableInterface(Class, Basemeta, Alias, IntroLibrary)	\
CATBeginImplementInterface(Class,Basemeta,Class);			\
CATImplementInterface_AddLicensed							\
CATImplementInterface_AddNamed(Alias)						\
CATImplementInterface_AddIntrospectable(IntroLibrary) 		\
CATEndImplementInterface(Class,Basemeta,Class)

/**
 * @nodoc
 * Declares an interface class with a mandatory adapter.
 * <b>Role</b>: Declares that the current class is an interface class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareInterface.
 * in the class header file.
 * End it with a semicolon.
 * @param Class
 *   Interface class name
 * @param Basemeta
 *   Interface class from which <tt>Class</tt> derives 
 */
#define CATImplementInterfaceWithMandatoryAdapter(Class, Basemeta, MandatoryAdapter)				\
CATBeginImplementInterface(Class,Basemeta,Class);			            \
CATImplementInterface_AddMandatoryAdapter(MandatoryAdapter)						\
CATEndImplementInterface(Class,Basemeta,Class)

#define CATImplementLicensedInterfaceWithMandatoryAdapter(Class, Basemeta, MandatoryAdapter)			\
CATBeginImplementInterface(Class,Basemeta,Class);				\
CATImplementInterface_AddLicensed								\
CATImplementInterface_AddMandatoryAdapter(MandatoryAdapter)						\
CATEndImplementInterface(Class,Basemeta,Class)

/**
 * @nodoc
 * Declares a condition function which is run before creating the object instance
 * implementing an interface.
 * @param implementation
 *   Class  which implments <tt>interfac</tt>
 * @param interfac
 *   Interface name
 * @param condition
 *   Condition function
 */
#define CATImplementCondition(implementation,interfac,condition)    \
                                                                    \
CATOMInitializerProlog(DicoConditionFor##implementation##interfac)  \
  CATFillDictionary DicoConditionFor##implementation##interfac      \
	  		(#implementation,#interfac,NULL,(void *)condition);     \
CATOMInitializerEpilog(DicoConditionFor##implementation##interfac)


#undef _DSY_SYS_DUMMY_ALL_OS_DEFINED
#if defined(_WINDOWS_SOURCE) || defined(_HPUX_SOURCE) || defined(_LINUX_SOURCE) || defined(_MACOSX_SOURCE) || defined(_DARWIN_SOURCE) || (defined(_AIX_SOURCE) && (__xlC__ >= 0x0500)) || (defined(_SUNOS_SOURCE) && (defined(__SUNPRO_CC) && (__SUNPRO_CC > 0x420))) || defined(_MOBILE_SOURCE)

# define _DSY_SYS_DUMMY_ALL_OS_DEFINED
#endif // ALL

#ifdef _DSY_SYS_DUMMY_ALL_OS_DEFINED
/**
 * @nodoc
 */
# define CATDeclareAffect(interfac)                                                               \
                                                                                                  \
interfac##_var & __stdcall operator=(const CATBaseUnknown *base);

/**
 * @nodoc
 */
# define CATImplementAffect(interfac)                                                             \
                                                                                                  \
interfac##_var & __stdcall interfac##_var::operator=(const CATBaseUnknown *base)                  \
{                                                                                                 \
   CastTo((IUnknown *)base,IID_##interfac);                                                       \
   return(*this);                                                                                 \
}

/**
 * @nodoc
 */
#define CATDeclareInlineAffect(interfac)                                                          \
inline interfac##_var & __stdcall operator=(const CATBaseUnknown *base);

/**
 * @nodoc
 */
#define CATImplementInlineAffect(interfac)                                                        \
inline interfac##_var & __stdcall interfac##_var::operator=(const CATBaseUnknown *base)           \
{                                                                                                 \
   __CastTo((IUnknown *)base);                                                                    \
   return(*this);                                                                                 \
}

# if defined(_WINDOWS_SOURCE)

/**
 * @nodoc
 */
#   define CATImplementConv(interfac)                                                             \
  return((interfac *)CATBaseUnknown_var::GetPointer());
# else  // _WINDOWS_SOURCE
/**
 * @nodoc
 */
#   define CATImplementConv(interfac)                                                             \
  return((interfac *)CATBaseUnknown_var::operator CATBaseUnknown *());
# endif // _WINDOWS_SOURCE
#else // _DSY_SYS_DUMMY_ALL_OS_DEFINED
/**
 * @nodoc
 */
# define CATDeclareAffect(interfac)

/**
 * @nodoc
 */
# define CATImplementAffect(interfac)

/**
 * @nodoc
 */
#define CATDeclareInlineAffect(interfac)

/**
 * @nodoc
 */
#define CATImplementInlineAffect(interfac)

/**
 * @nodoc
 */
#   define CATImplementConv(interfac)                                                             \
  return((interfac *)CATBaseUnknown_var::operator CATBaseUnknown *());
#endif // _DSY_SYS_DUMMY_ALL_OS_DEFINED

/**
 * Declares a handler.
 * <b>Role</b>: Declares a handler, or smart pointer, for an interface,
 * in the interface header file.
 * @param interfac
 *   Interface name
 * @param baseclass
 *   Class from which the interface class derives.
 */
#define CATDeclareHandler(interfac,baseclass)                                                      \
                                                                                                   \
class interfac##_var : public baseclass##_var                                                      \
{                                                                                                  \
   private:                                                                                        \
      Exported void __stdcall __CastTo(IUnknown*pt);                                               \
   public:                                                                                         \
      inline interfac##_var();                                                                     \
      inline interfac##_var(CATBaseUnknown *base);                                                 \
      inline interfac##_var(interfac *base);                                                       \
      inline interfac##_var(const interfac##_var &base);                                           \
      inline interfac##_var(const CATBaseUnknown_var &base);                                       \
      inline interfac * __stdcall operator->() const;                                              \
      inline __stdcall operator interfac *() const;                                                \
      inline interfac##_var& __stdcall operator=(const CATBaseUnknown_var &base);                  \
      CATDeclareInlineAffect(interfac)                                                             \
};                                                                                                 \
                                                                                                   \
inline interfac##_var::interfac##_var():baseclass##_var()                                          \
{}                                                                                                 \
inline interfac##_var::interfac##_var(CATBaseUnknown *base) : baseclass##_var()                    \
{                                                                                                  \
    __CastTo(base);                                                                                \
}                                                                                                  \
inline interfac##_var::interfac##_var(interfac *base):baseclass##_var((baseclass *)base)           \
{}                                                                                                 \
inline interfac##_var::interfac##_var(const interfac##_var &base):baseclass##_var((baseclass*)base) \
{                                                                                                  \
    __CastTo((CATBaseUnknown *)base);                                                              \
}                                                                                                  \
inline interfac##_var::interfac##_var(const CATBaseUnknown_var &base): baseclass##_var()           \
{                                                                                                  \
    __CastTo((IUnknown *)base);                                                                    \
}                                                                                                  \
inline interfac * __stdcall interfac##_var::operator->() const                                     \
{                                                                                                  \
    return((interfac *)CATBaseUnknown_var::operator->());                                          \
}                                                                                                  \
inline __stdcall interfac##_var::operator interfac *() const                                       \
{                                                                                                  \
    CATImplementConv(interfac);                                                                    \
}                                                                                                  \
inline interfac##_var& __stdcall interfac##_var::operator=(const CATBaseUnknown_var &base)         \
{                                                                                                  \
    __CastTo((IUnknown *)base);                                                                    \
    return(*this);                                                                                 \
}                                                                                                  \
CATImplementInlineAffect(interfac)                                                                 \
                                                                                                   \
typedef interfac *interfac##_ptr

/**
 * Define a hanlder.
 * <b>Role</b>: Declares a handler, or smart pointer, for an interface,
 * in the interface source (.cpp) file.
 * @param interfac
 *   Interface name
 * @param baseclass
 *   Class from which the interface class derives.
 */
#define CATImplementHandler(interfac,baseclass) \
	void interfac##_var::__CastTo(IUnknown*pt) \
	{ \
		CastTo(pt,IID_##interfac); \
	}; 


/**
 * @nodoc
 */
#define CATUuidOf(InterfaceName) IID_##InterfaceName



/**
 * @nodoc
 * Declare a handler.
 */
#define	CATDefineHandler(Interface, Base)                                                    \
class Interface##_var :	public Base##_var {	                                             \
private:                                                                                     \
  inline void	__stdcall __CastTo(IUnknown*pt);                                             \
public:                                                                                      \
  inline Interface##_var();                                                                  \
  inline Interface##_var(CATBaseUnknown *base);                                              \
  inline Interface##_var(Interface *base);                                                   \
  inline Interface##_var(const Interface##_var &base);                                       \
  inline Interface##_var(const CATBaseUnknown_var& base);                                    \
  inline Interface* __stdcall	operator->() const;                                          \
  inline __stdcall operator Interface*() const;                                              \
  inline Interface##_var&	__stdcall operator=(const CATBaseUnknown_var& base);         \
  inline Interface##_var& __stdcall operator=(const CATBaseUnknown *base);                   \
};                                                                                           \
                                                                                             \
inline void __stdcall Interface##_var::__CastTo(IUnknown*pt)                                 \
{                                                                                            \
  CastTo(pt, CATUuidOf(Interface));                                                          \
}                                                                                            \
inline Interface##_var::Interface##_var():Base##_var()                                       \
{}                                                                                           \
inline Interface##_var::Interface##_var(CATBaseUnknown *base):Base##_var()                   \
{                                                                                            \
  __CastTo(base);                                                                            \
}                                                                                            \
inline Interface##_var::Interface##_var(Interface *base):Base##_var((Base*) base)            \
{                                                                                            \
}                                                                                            \
inline Interface##_var::Interface##_var(const Interface##_var &base):Base##_var((Base*) base)\
{                                                                                            \
  __CastTo((CATBaseUnknown*) base);                                                          \
}                                                                                            \
inline Interface##_var::Interface##_var(const CATBaseUnknown_var& base):Base##_var()         \
{                                                                                            \
  __CastTo((IUnknown*) base);                                                                \
}                                                                                            \
inline Interface* __stdcall Interface##_var::operator->() const                              \
{                                                                                            \
  return (Interface*) CATBaseUnknown_var::operator->();                                      \
}                                                                                            \
inline __stdcall Interface##_var::operator Interface*() const                                \
{                                                                                            \
  return (Interface*) CATBaseUnknown_var::operator CATBaseUnknown*();                        \
}                                                                                            \
inline Interface##_var&	__stdcall Interface##_var::operator=(const CATBaseUnknown_var& base) \
{                                                                                            \
  __CastTo((IUnknown*) base); return (*this);                                                \
}                                                                                            \
inline Interface##_var& __stdcall Interface##_var::operator=(const CATBaseUnknown *base)     \
{                                                                                            \
  __CastTo((IUnknown*) base); return(*this);                                                 \
}                                                                                            \
                                                                                             \
typedef	Interface *Interface##_ptr

namespace dsy
{
    namespace internal  // Internal use only
    {
        /** @nodoc Function that finds a meta-object */
        ExportedByJS0CORBA CATMetaClass* fct_FindMetaObject(char const*);
        /** @nodoc Function that creates a meta-object */
        ExportedByJS0CORBA CATMetaClass* fct_RetrieveMetaObject(char const*, TypeOfClass, CATMetaClass*, char const*, char const*, size_t);
        /** @nodoc */
        ExportedByJS0CORBA CATBaseUnknown* QueryMacQI(CATBaseUnknown const*, IID const&);
        
        /** @nodoc */
        struct om_guard {
            /** @nodoc */
            ExportedByJS0CORBA  om_guard();
            /** @nodoc */
            ExportedByJS0CORBA ~om_guard();
            /** @nodoc */
            om_guard & operator= (const om_guard &) = delete;
        private:
            void* _data[2];    // alignas(sizeof(void*))
        };
    }   // namespace internal
}   // namespace dsy

#endif // __CATMacForIUnknown
