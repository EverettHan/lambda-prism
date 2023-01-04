/* -*-c++-*- */
#ifndef CATCGMMacs_h
#define CATCGMMacs_h
#include "CATGeometryType.h"
#include "ObjectTypesCGM.h"
#include "CATBaseUnknown.h"
#include "CATCGMNewArray.h"
#include "CATMathStreamDef.h"
#include "Data_GeometricObjectsCGM.h"

class CATCGMObject;
class CATCGMContainer;

//-----------------------------------------------------------------------------------------
//    Macros Pour Classes Abstraites 
//        - FW System Macros
//-----------------------------------------------------------------------------------------
//    Macros Pour Classes Concretes 
//        - FW System Macros
//-----------------------------------------------------------------------------------------

#define CATCGMDeclareVirtualClass  CATDeclareClass

#define CATCGMDeclareClassBasic                         \
  CATDeclareClass;                                      \
  Data_GeometricObjectsCGM_Stream;                      \
  virtual int   IsATypeOf(CATGeometricType itp) const;  \
  virtual CATGeometricType GetVolatileType() const;     \
  virtual size_t  GetStaticMemoryBytes() const;         \
  CATCGMNewClassArrayDeclare

#define CATCGMDeclareClass    \
  CATCGMDeclareClassBasic ;   \
  virtual CATCGMObject *NewSameType(CATCGMContainer * iContainer) const ;           \
  static  CATBaseUnknown* CreationCGM(CATCGMContainer * iContainer)

#define CATCGMImplementVirtualClass(Class,TypeofClass,BaseClass,ImplClass)    \
CATImplementClass(Class,TypeofClass,BaseClass,ImplClass)

#endif



