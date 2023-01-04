#ifndef CATCGMAttrId_H
#define CATCGMAttrId_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

#include "CATBaseUnknown.h"
#include "YP0LOGRP.h"
#include "CATDataType.h"
#include "CATBoolean.h"
#include "CATUnicodeString.h"


class CATCGMAttribute;
class CATCGMAttributeDef;
/** 
 * Internal use for the macro of the attribute definition.
 * <br>Do not use directly.
 */
typedef  CATCGMAttribute * (*CATCGMConstrAttr)();

/**
 * Class defining the identifiers of an attribute class.
 */
class ExportedByYP0LOGRP CATCGMAttrId 
{
public :
/** 
 * Returns the attribute class name.
 * @return
 * The attribute class name relative to <tt>this</tt> CATCGMAttrId.
 */
  const char * GetAttributeClassName() const {return localname;};

/** 
 * Returns the application name .
 * @return
 * The logical name of the physical load module conaining the class.
  */
  const char * GetDomainName()         const {return Application;};

  /** 
  * Returns the attribute id from a name and a domain name.
  * @param iAttr
  * The attribute name.
  * @param iDomainName
  * The logical name of the physical load module conaining the class.
  * @return
  * The corresponding attribute id.
  */
  static const CATCGMAttrId* FindAttrId(const char* iAttr, const char* iDomainName);
  
  /** @nodoc */
  const char      * localname;
  /** @nodoc */
  const char      * Application;
  /** @nodoc */
  CATCGMAttrId    * fromAttr;
  /** @nodoc */
  CATLONG32         version;
  /** @nodoc */
  CATCGMConstrAttr  creatorOfAttribute;
  /** @nodoc */
  short             IsRegistred;


    /** @nodoc */
  CATBoolean        _WithFullName;
  /** @nodoc */
  CATUnicodeString  _FullName;

  /** @nodoc */
  void SecureInit( const char               *  localname  ,
                   const char               *  Application,
                         CATCGMAttrId       *  fromAttr   ,
                         CATLONG32             version    ,
                         CATCGMConstrAttr      Ctor       ,
                         short                 IsRegistred,
                         CATCGMAttributeDef *& iDef       );

  /** @nodoc */
  void SecureInit( const char               *  localname  ,
                   const char               *  Application,
                         CATCGMAttrId       *  fromAttr   ,
                         CATLONG32             version    ,
                         int                   iMustUnstreamForLightBRepMode,
                         CATCGMConstrAttr      Ctor       ,
                         short                 IsRegistred,
                         CATCGMAttributeDef *& iDef       );

  /** @nodoc */
  void SecureInit( const char               *  localname  ,
                   const char               *  Application,
                         CATCGMAttrId       *  fromAttr   ,
                         CATLONG32             version    ,
                         int                   iMustUnstreamForLightBRepMode,
                         int                   iMustStreamForStreamCompact,
                         CATCGMConstrAttr      Ctor       ,
                         short                 IsRegistred,
                         CATCGMAttributeDef *& iDef       );



  /** @nodoc */
  void GetFullName(CATUnicodeString & oFullName) const;

};


/**
 * @nodoc
 * Defines the identifier corresponding to an attribute class name.
 */
#define UAIDName(attr) attr::_UAID
/**
 * Defines the identifier corresponding to an attribute class name.
 */
#define UAIDPtr(attr)  attr::GetId()


/**
 * Declares the attribute .
 * This must be called in the header file of your own attribute class.
 * @param iChild
 * Your new class.
 * @param iParent
 * From which the new attribute class derives.
 */
#define CATCGMDeclareAttribute(iChild, iParent)                           \
private :                                                                 \
  static CATCGMAttributeDef * iChild##Def;                                \
  static short                iChild##_SecureInit;                        \
protected :                                                               \
  friend CATCGMAttribute * iChild##_CreateAttribute();                    \
public :                                                                  \
  static short  CATCGMAttrIdSecureInit();                                 \
  static        CATCGMAttrId          _UAID;                              \
  static const  CATCGMAttrId        * GetId();                            \
  virtual const CATCGMAttrId       * GetCGMAttrId() const;                \
  virtual const CATCGMAttributeDef * GetAttributeDef() const

/**
 * @nodoc
 * @deprecated V5R12 CATCGMImplAttributeBRep
 * Defines the mapping between the attribute and the class name, the application name, the version.
 * <br>To be called in the souce (.cpp) of the header file of your attribute class.
 * @param iChild
 * Your new class.
 * @param iParent
 * From which the new attribute class derives.
 * @param iApp
 * The application name.
 * @param iVersion
 * The version number.
 */
#define CATCGMImplAttributeWithoutCreate(iChild, iParent, iApp, iVersion) \
CATCGMAttribute    * iChild##_CreateAttribute();                          \
CATCGMAttrId         iChild::_UAID;                                       \
CATCGMAttributeDef * iChild::iChild##Def;                                 \
short iChild##_SecureInit = iChild::CATCGMAttrIdSecureInit();             \
short iChild::CATCGMAttrIdSecureInit()                                    \
{                                                                         \
  static short result = 0;                                                \
  if ( result == 0 )                                                      \
   {                                                                      \
     result = iParent::CATCGMAttrIdSecureInit();                          \
     iChild::_UAID.SecureInit( #iChild , #iApp ,& iParent::_UAID ,        \
                               iVersion, &iChild##_CreateAttribute,       \
                                0, iChild::iChild##Def );                 \
   }                                                                      \
   return result;                                                         \
}                                                                         \
const CATCGMAttributeDef * iChild::GetAttributeDef() const                \
{                                                                         \
   return iChild##Def;                                                    \
}                                                                         \
const CATCGMAttrId * iChild::GetId()                                      \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
const CATCGMAttrId * iChild::GetCGMAttrId() const                         \
{                                                                         \
   return & iChild::_UAID ;                                               \
}

#define CATCGMImplAttribute(iChild, iParent, iApp, iVersion)              \
CATCGMImplAttributeWithoutCreate(iChild, iParent, iApp, iVersion)         \
CATCGMAttribute * iChild##_CreateAttribute()                              \
{                                                                         \
   CATCGMAttribute * NewAttr = new iChild ();                             \
   return NewAttr;                                                        \
}

/**
 * Defines the mapping between the attribute and the class name, the application name, the version. the LightBRepMode
 * <br>To be called in the souce (.cpp) of the header file of your attribute class.
 * @param iChild
 * Your new class.
 * @param iParent
 * From which the new attribute class derives.
 * @param iApp
 * The application name.
 * @param iVersion
 * The version number.
 * @param iMustUnstreamForLightBRepMode
 * Whether this attribute needs to be unstreamed when in BRep Mode (1) or not (0)
 */
#define CATCGMImplAttributeBRep(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode) \
 CATCGMImplAttributeBRepCompact(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode, 0)

/** @nodoc */
#define CATCGMImplAttributeBRepCompact(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode, iMustStreamForStreamCompact) \
CATCGMAttribute    * iChild##_CreateAttribute();                          \
CATCGMAttrId         iChild::_UAID;                                       \
CATCGMAttributeDef * iChild::iChild##Def;                                 \
short iChild##_SecureInit = iChild::CATCGMAttrIdSecureInit();             \
short iChild::CATCGMAttrIdSecureInit()                                    \
{                                                                         \
  static short result = 0;                                                \
  if ( result == 0 )                                                      \
   {                                                                      \
     result = iParent::CATCGMAttrIdSecureInit();                          \
     iChild::_UAID.SecureInit( #iChild , #iApp ,& iParent::_UAID ,        \
                               iVersion, iMustUnstreamForLightBRepMode,   \
                               iMustStreamForStreamCompact,               \
                               &iChild##_CreateAttribute, 0,              \
                               iChild::iChild##Def );                     \
   }                                                                      \
   return result;                                                         \
}                                                                         \
const CATCGMAttributeDef * iChild::GetAttributeDef() const                \
{                                                                         \
   return iChild##Def;                                                    \
}                                                                         \
const CATCGMAttrId * iChild::GetId()                                      \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
const CATCGMAttrId * iChild::GetCGMAttrId() const                         \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
CATCGMAttribute * iChild##_CreateAttribute()                              \
{                                                                         \
   CATCGMAttribute * NewAttr = new iChild ();                             \
   return NewAttr;                                                        \
}

/** 
 * @nodoc
 * @deprecated V5R12 CATCGMImplVirtualAttributeBRep
 *
 */
#define CATCGMImplVirtualAttribute(iChild, iParent, iApp, iVersion)       \
CATCGMAttribute    * iChild##_CreateAttribute();                          \
CATCGMAttrId         iChild::_UAID;                                       \
CATCGMAttributeDef * iChild::iChild##Def;                                 \
short iChild##_SecureInit = iChild::CATCGMAttrIdSecureInit();             \
short iChild::CATCGMAttrIdSecureInit()                                    \
{                                                                         \
  static short result = 0;                                                \
  if ( result == 0 )                                                      \
   {                                                                      \
     result = iParent::CATCGMAttrIdSecureInit();                          \
     iChild::_UAID.SecureInit( #iChild , #iApp ,& iParent::_UAID ,        \
                               iVersion, &iChild##_CreateAttribute, 0,    \
                               iChild::iChild##Def );                     \
   }                                                                      \
   return result;                                                         \
}                                                                         \
const CATCGMAttributeDef * iChild::GetAttributeDef() const                \
{                                                                         \
   return iChild##Def;                                                    \
}                                                                         \
const CATCGMAttrId * iChild::GetId()                                      \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
const CATCGMAttrId * iChild::GetCGMAttrId() const                         \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
CATCGMAttribute * iChild##_CreateAttribute()                              \
{                                                                         \
  return NULL;                                                            \
}


/** @nodoc */
#define        CATCGMImplVirtualAttributeBRep(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode)   \
        CATCGMImplVirtualAttributeBRepCompact(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode, 0)

/** @nodoc */
#define CATCGMImplVirtualAttributeBRepCompact(iChild, iParent, iApp, iVersion, iMustUnstreamForLightBRepMode, iMustStreamForStreamCompact) \
CATCGMAttribute    * iChild##_CreateAttribute();                          \
CATCGMAttrId         iChild::_UAID;                                       \
CATCGMAttributeDef * iChild::iChild##Def;                                 \
short iChild##_SecureInit = iChild::CATCGMAttrIdSecureInit();             \
short iChild::CATCGMAttrIdSecureInit()                                    \
{                                                                         \
  static short result = 0;                                                \
  if ( result == 0 )                                                      \
   {                                                                      \
     result = iParent::CATCGMAttrIdSecureInit();                          \
     iChild::_UAID.SecureInit( #iChild , #iApp ,& iParent::_UAID ,        \
                               iVersion, iMustUnstreamForLightBRepMode,   \
                               iMustStreamForStreamCompact,               \
                               &iChild##_CreateAttribute, 0,              \
                               iChild::iChild##Def );                     \
   }                                                                      \
   return result;                                                         \
}                                                                         \
const CATCGMAttributeDef * iChild::GetAttributeDef() const                \
{                                                                         \
   return iChild##Def;                                                    \
}                                                                         \
const CATCGMAttrId * iChild::GetId()                                      \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
const CATCGMAttrId * iChild::GetCGMAttrId() const                         \
{                                                                         \
   return & iChild::_UAID ;                                               \
}                                                                         \
CATCGMAttribute * iChild##_CreateAttribute()                              \
{                                                                         \
  return NULL;                                                            \
}


  /** @nodoc */
#include "TIE_CATICGMDomainBinder.h"

/** 
 * Maps the application of the attribute.
 * @param Application
 * The application name.
 */

#ifdef CATIAR420

#define AppDef(Application)                                               \
class Application##Ext : public CATICGMDomainBinder                       \
{                                                                         \
  CATDeclareClass;                                                        \
public :                                                                  \
  virtual const char* GetDomainName();                                    \
};                                                                        \
const char* Application##Ext::GetDomainName()                             \
{                                                                         \
  return #Application ;                                                   \
}                                                                         \
CATImplementClass( Application##Ext, CacheExtension, CATICGMDomainBinder, Application);\
CATImplementBOA( CATICGMDomainBinder, Application##Ext);

#else

#define AppDef(Application)                                               \
class Application##Ext : public CATBaseUnknown                            \
{                                                                         \
  CATDeclareClass;                                                        \
public :                                                                  \
  virtual const char* GetDomainName();                                    \
};                                                                        \
const char* Application##Ext::GetDomainName()                             \
{                                                                         \
  return #Application ;                                                   \
}                                                                         \
CATImplementClass( Application##Ext, CodeExtension, CATBaseUnknown, Application);\
TIE_CATICGMDomainBinder( Application##Ext )

#endif

#endif









