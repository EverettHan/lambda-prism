#ifndef __CATMacForRtti
#define __CATMacForRtti

/** @CAA2Required */
/**********************************************************************/
/* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPEAR AT ANY TIME */
/**********************************************************************/

// COPYRIGHT DASSAULT SYSTEMES 2012

#include "CATMacForIUnknown.h"
#ifndef _WINDOWS_SOURCE
#include <cstring>  // For strcmp. To be removed, cf deprecated macros R425
#endif


/**
 * @nodoc
 * @deprecated R425
 */
#define CATDeclareRttiClass                                \
public :                                                   \
   virtual const char  * IsA() const;                      \
   virtual int           IsAKindOf(const char *) const;    \
   static const char *   __stdcall ClassName()

/**
 * @nodoc
 * @deprecated R425
 */
#define CATImplementRttiBaseClass(Class)        \
const char *Class::IsA() const                  \
{                                               \
   return ClassName();                          \
}                                               \
int Class::IsAKindOf(const char *ident) const   \
{                                               \
   return !strcmp(ident, ClassName());          \
}                                               \
const char * __stdcall Class::ClassName()       \
{                                               \
   return #Class;                               \
}



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
#define CATImplementClass_Deprec(Class,Basemeta)                                \
CATMetaClass * __stdcall Class::GetMetaObject() const                           \
{                                                                               \
   return(MetaObject());                                                        \
}                                                                               \
                                                                                \
const CLSID & __stdcall Class::ClassId()                                        \
{                                                                               \
   return(MetaObject()->GetClassId());                                          \
}                                                                               \
const char * __stdcall Class::ClassName()                                       \
{                                                                               \
   return(MetaObject()->IsA());                                                 \
}                                                                               \
const char *Class::IsA() const                                                  \
{                                                                               \
   return(MetaObject()->IsA());                                                 \
}                                                                               \
int Class::IsAKindOf(const char *ident) const                                   \
{                                                                               \
   return(MetaObject()->IsAKindOf(ident));                                      \
}                                                                               \
                                                                                \
CATBaseUnknown *Class::CreateItself()                                           \
{                                                                               \
   return(NULL);                                                                \
}                                                                               \
                                                                                \
CATMacMetaObjectMethodProlog(Class)                                             \
                                                                                \
    meta_object = dsy::internal::fct_RetrieveMetaObject(#Class,Implementation,  \
            Basemeta::MetaObject(),"CATNull",CATLicenseOptionId,sizeof(Class)); \
                                                                                \
CATMacMetaObjectMethodEpilog(Class)                                             \
                                                                                \
static_assert(true, ""/*CATImplementClass_Deprec requires an ending semicolon*/)


#endif // __CATMacForRtti
