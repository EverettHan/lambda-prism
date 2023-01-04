/* -*-c++-*- */
#ifndef CATCGMImplementClass_h_
#define CATCGMImplementClass_h_

#include "CATBaseUnknown.h"
#include "CATGeometryType.h"
#include "CATCGMNewClassArray.h"
#include "ObjectTypesCGM.h"

#ifndef NULL 
#define NULL 0
#endif
class CATCGMObject;
class CATCGMOutput;
class CATBaseUnknown;
class CATCGMContainer;


#define CATCGMImplementCOMMON(Class)                                                   \
int    Class::IsATypeOf(CATGeometricType TypeReference) const                          \
{                                                                                      \
static  CATGeometricType MaskIndex = 0x0000000F;                                       \
static  CATGeometricType MaskArray [8] =                                               \
{ 0x00000000, 0xF0000000, 0xFF000000, 0xFFF00000,                                      \
  0xFFFF0000, 0xFFFFF000, 0xFFFFFF00, 0xFFFFFFF0 };                                    \
    CATGeometricType Index        = TypeReference  & MaskIndex ;                       \
    CATGeometricType NewReference = TypeReference  & MaskArray[Index];                 \
    CATGeometricType NewToCompare = Class##GeoType & MaskArray[Index];                 \
    return ( NewReference == NewToCompare);                                            \
}                                                                                      \
CATGeometricType Class::GetVolatileType() const                                        \
{                                                                                      \
 return Class##GeoType;                                                                \
}                                                                                      \
size_t Class::GetStaticMemoryBytes() const                                             \
{                                                                                      \
 return sizeof(*this);                                                                 \
}                                                                                      \


//-----------------------------------------------------------------------------------------
//    Macros Pour Classes Abstraites  et Classes d'Implementation
//-----------------------------------------------------------------------------------------
#define CATCGMImplementClassNew(Class,TypeofClass,BaseClass,ImplClass,NbObjBlock)      \
CATCGMNewClassArray(Class,NbObjBlock,catcgmPoolGEOM)                                   \
CATCGMImplementCOMMON(Class)                                                           \
CATCGMObject *Class::NewSameType(CATCGMContainer * iContainer) const                   \
{                                                                                      \
  CATBaseUnknown* NewItf  = Class::CreationCGM(iContainer);                            \
  if (!NewItf) return NULL;                                                            \
  CATCGMObject  * NewImpl = (CATCGMObject*)NewItf->GetImpl();                          \
  return NewImpl;                                                                      \
}                                                                                      \
CATBaseUnknown* Class::CreationCGM(CATCGMContainer * iContainer)                       \
{                                                                                      \
  Class         * new_instance = new Class(iContainer);                                \
  if (!new_instance) return NULL;                                                      \
  CATBaseUnknown* new_itf      = new_instance->GetInterface();                         \
  if (!new_itf) new_instance->Release();                                               \
  return new_itf;                                                                      \
}                                                                                      \
CATImplementClass(Class,TypeofClass,BaseClass,ImplClass)


#define CATCGMImplementClass(Class,TypeofClass,BaseClass,ImplClass)                    \
   CATCGMImplementClassNew(Class,TypeofClass,BaseClass,ImplClass,100)   
 


//-----------------------------------------------------------------------------------------
//    Macros Pour Classes Abstraites  et Classes d'Implementation
//-----------------------------------------------------------------------------------------
#define CATCGMImplementClassTOPONew(Class,TypeofClass,BaseClass,ImplClass,NbObjBlock)  \
CATCGMNewClassArrayTOPODefine(Class,NbObjBlock)                                        \
CATCGMImplementCOMMON(Class)                                                           \
CATCGMObject *Class::NewSameType(CATCGMContainer * iContainer) const                   \
{                                                                                      \
  CATBaseUnknown* NewItf  = Class::CreationCGM(iContainer);                            \
  if (!NewItf) return NULL;                                                            \
  CATCGMObject  * NewImpl = (CATCGMObject*)NewItf->GetImpl();                          \
  return NewImpl;                                                                      \
}                                                                                      \
CATBaseUnknown* Class::CreationCGM(CATCGMContainer * iContainer)                       \
{                                                                                      \
  Class         * new_instance = new Class(iContainer);                                \
  if (!new_instance) return NULL;                                                      \
  CATBaseUnknown* new_itf      = new_instance->GetInterface();                         \
  if (!new_itf) new_instance->Release();                                               \
  return new_itf;                                                                      \
}                                                                                      \
CATImplementClass(Class,TypeofClass,BaseClass,ImplClass)


#define CATCGMImplementTOPOClass(Class,TypeofClass,BaseClass,ImplClass)                \
   CATCGMImplementClassNewTOPO(Class,TypeofClass,BaseClass,ImplClass,100)


//-----------------------------------------------------------------------------------------
//  CATCGMImplementClass_CATCGMBOAObject
//-----------------------------------------------------------------------------------------

#if defined ( CATCGMBOAObject )
#include "CATCGMImplementClass_CATCGMBOAObject.h"
#endif



#endif



