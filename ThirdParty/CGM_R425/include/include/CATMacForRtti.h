#ifndef __CATMacForRtti
#define __CATMacForRtti

/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATMacForIUnknown.h"

/**
 * @nodoc
 * Declares a "rtti" class.
 * Use this macro in the class header file in conjunction with @href CATImplementRttiClass in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATDeclareRttiClass                                            \
protected :                                                            \
   static CATMetaClass  *  __stdcall MetaObject();                     \
   CATMetaClassStaticCheck                                             \
public :                                                               \
   virtual const char  *             IsA() const;                      \
   virtual int                       IsAKindOf(const char *) const;    \
   static const char *     __stdcall ClassName()

/**
 * @nodoc
 */
#define CATBeginImplementRttiClass(Class)                                     \
const char *Class::IsA() const                                                \
{                                                                             \
   return(MetaObject()->IsA());                                               \
}                                                                             \
int Class::IsAKindOf(const char *ident) const                                 \
{                                                                             \
   return(MetaObject()->IsAKindOf(ident));                                    \
}                                                                             \
const char * __stdcall Class::ClassName()                                     \
{                                                                             \
   return(MetaObject()->IsA());                                               \
}                                                                             \
CATMetaClass * __stdcall Class::MetaObject()                                  \
{                                                                             \
   ExportedByJS0CORBA CATMetaClass *fct_RetrieveMetaObject(const char *,      \
               TypeOfClass, CATMetaClass *, const char *, const char *,long); \
   static CATMetaClass *meta_object = 0;                                      \
   if (!meta_object)                                                          \
   {                                                                          \
       CATMetaClass * BaseMetaOc = 0;

/**
 * @nodoc
 */
#define CATEndImplementRttiClass(Class)                                       \
       meta_object = fct_RetrieveMetaObject(#Class,Implementation,            \
          BaseMetaOc, "CATNull",CATLicenseOptionId,sizeof(Class));            \
   }                                                                          \
   return(meta_object);                                                       \
}


/**
 * @nodoc
 * Defines a "Rtti" base class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareRttiClass in the class header file.
 * End it with a semicolon.
 * @param Class
 *   The name of the class
 */
#define CATImplementRttiBaseClass(Class)                                      \
CATBeginImplementRttiClass(Class)                                             \
CATEndImplementRttiClass(Class)


/**
 * @nodoc
 * Defines a "Rtti" class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareRttiClass in the class header file.
 * End it with a semicolon.
 * @param Class
 *   The name of the class
 * @param Basemeta
 *   The class from which <tt>Class</tt> Rtti and C++ derives.
 */
#define CATImplementRttiClass(Class,Basemeta)                                 \
CATBeginImplementRttiClass(Class)                                             \
BaseMetaOc = Basemeta::MetaObject();                                          \
Basemeta * DerivationCheck = (Class*) NULL;                                   \
CATEndImplementRttiClass(Class)


/**
 * @nodoc
 * Declares a class.
 * Use this macro in the class header file in conjunction with @href CATImplementClass_Deprec 
 * in the class source (.cpp) file.
 * End it with a semicolon.
 */
#define CATDeclareClass_Deprec      CATDeclareClass


/**
 * @nodoc
 * Defines an implementation class.
 * Use this macro in the class source (.cpp) file in conjunction with @href CATDeclareClass_Deprec
 * in the class header file
 * End it with a semicolon.
 */
#define CATImplementClass_Deprec(Class,Basemeta)                              \
CATMetaClass * __stdcall Class::GetMetaObject() const                         \
{                                                                             \
   return(MetaObject());                                                      \
}                                                                             \
                                                                              \
const CLSID & __stdcall Class::ClassId()                                      \
{                                                                             \
   return(MetaObject()->GetClassId());                                        \
}                                                                             \
const char * __stdcall Class::ClassName()                                     \
{                                                                             \
   return(MetaObject()->IsA());                                               \
}                                                                             \
const char *Class::IsA() const                                                \
{                                                                             \
   return(MetaObject()->IsA());                                               \
}                                                                             \
int Class::IsAKindOf(const char *ident) const                                 \
{                                                                             \
   return(MetaObject()->IsAKindOf(ident));                                    \
}                                                                             \
                                                                              \
CATBaseUnknown *Class::CreateItself()                                         \
{                                                                             \
   return(NULL);                                                              \
}                                                                             \
                                                                              \
CATMetaClass * __stdcall Class::MetaObject()                                  \
{                                                                             \
   ExportedByJS0CORBA CATMetaClass *fct_RetrieveMetaObject(const char *,      \
               TypeOfClass, CATMetaClass *, const char *, const char *,long); \
                                                                              \
   if (!meta_object)                                                          \
   {                                                                          \
      meta_object = fct_RetrieveMetaObject(#Class,Implementation,             \
        Basemeta::MetaObject(),"CATNull",CATLicenseOptionId,sizeof(Class));   \
   }                                                                          \
   return(meta_object);                                                       \
}                                                                             \
CATMetaClass *Class::meta_object = NULL


#endif // __CATMacForRtti
