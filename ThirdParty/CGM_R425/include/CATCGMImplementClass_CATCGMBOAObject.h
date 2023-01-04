/* -*-c++-*- */
#ifndef CATCGMImplementClass_CATCGMBOAObject_h_
#define CATCGMImplementClass_CATCGMBOAObject_h_

#include "CATBaseUnknown.h"
#include "CATGeometryType.h"
#include "CATCGMNewClassArray.h"
#include "ObjectTypesCGM.h"

class CATCGMObject;
class CATCGMOutput;

#ifndef NULL 
#define NULL 0
#endif
class CATCGMObject;
class CATBaseUnknown;
class CATCGMContainer;


// Pour TIE BOA


#define CATCGMImplementNewSameType(Class,iClassInterface) \
CATCGMObject *Class::NewSameType(CATCGMContainer * iContainer) const                \
{                                                                                   \
  TIECGM##iClassInterface * newTie = new TIECGM##iClassInterface();                 \
  if (!newTie ) return NULL;                                                        \
  Class* new_instance = newTie->GetData();                                          \
  if (!new_instance) return NULL;                                                   \
  new_instance->SetInterface( newTie);                            \
  return new_instance;                                                              \
}

#define CATCGMImplementCreationCGM(Class,iClassInterface) \
CATBaseUnknown* Class::CreationCGM(CATCGMContainer * iContainer)                    \
{                                                                                   \
  TIECGM##iClassInterface * newTie = new TIECGM##iClassInterface();                 \
  if (!newTie ) return NULL;                                                        \
  Class* new_instance = newTie->GetData();                                          \
  if (!new_instance) return NULL;                                                   \
  new_instance->SetInterface(newTie);                            \
  CATBaseUnknown* new_itf = new_instance->GetInterface();                           \
  if (!new_itf) new_instance->Release();                                            \
  return new_itf;                                                                   \
}                                                                                   

#define CATCGMImplementBasicBOAClassNew(Class,TypeofClass,BaseClass,iClassInterface,NbObjBlock) \
CATCGMNewClassArray(Class,NbObjBlock,catcgmPoolGEOM)                        \
CATCGMNewClassArray(TIECGM##iClassInterface,NbObjBlock,catcgmPoolGEOM)     	\
CATCGMImplementCOMMON(Class) \
CATImplementClass(Class,TypeofClass,BaseClass,ImplClass)



#define CATCGMImplementBOAClassNew(Class,TypeofClass,BaseClass,iClassInterface,NbObjBlock) \
CATCGMImplementBasicBOAClassNew(Class,TypeofClass,BaseClass,iClassInterface,NbObjBlock); \
CATCGMImplementNewSameType(Class,iClassInterface) \
CATCGMImplementCreationCGM(Class,iClassInterface) 


#endif



