#ifndef CATOGMCore_H
#define CATOGMCore_H
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2009
/**
 * @level Private
 * @usage U1
 */

//-------------------------------------------------------------------------------------------------
// Be Carefull about limited scope of this interface
//   high performance computation could not rely on central main memory management 
//
// Short term local transaction (change set acquisition)   
//    for extended N1 Operators on statefull modelisation
// Not to used by applied integration 
//    Dedicated to core kernel GM Component based modeler
//
// Cf  Oxxx Geomerical Modeler 
//-------------------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------------------
// Core Persistent Structure is structured by following Concepts
//
// -----------------------------------------------------
//    Content  
//       is made of 
//          Domain (by DomainType) 
//          may be by Content (through distinct Usage) 
//       is described by
//          USAGE (uselfull for Root Content)
//
// -----------------------------------------------------
//    Domain (persistent oriented) is 
//        acceded by set of Atoms 
//        defined by a DataContainer
//
//    Set is a tool, Interface to manipulate
//        a set of Atoms
//
// -----------------------------------------------------
//    Atom 
//      is defined by 
//         Head  [ MANDATORY ]
//         Data address
//         RunBind (void * ) depending from domain
//         and may be Links (between Atom)
//      is relative generated through
//          Domain or Set
//
//    Head is defined by :
//         DomainType
//         Intents
//         Key  
//
//    Key depending from Domain
//         from geometrical domain is defined by identifier (Tag) and a Type
//
//    Intent is State given from enumeration among :
//         ToCreate 
//         ToModify 
//         ToDelete
//
//----------------------------------------------------------------------------------------------
#include "ExportedByCATOGMCore.h"

#include "BigLittle.h" // Fw System , _ENDIAN_LITTLE 
#if   defined ( _ENDIAN_LITTLE )
#endif 
#include "CATDataType.h" // Fw SpecialAPI , CATULONGPTR
#include "CATMathInline.h" // Fw Mathematics , CATMathInline.h
 

typedef unsigned char CATOGMCORE_DOMAINTYPE;
#define CATOGMCORE_DOMAINTYPE_CATCGMObject          0x01
#define CATOGMCORE_DOMAINTYPE_CATCGMStreamAttribute 0x02
#define CATOGMCORE_DOMAINTYPE_CGMCONTAINER          0x03
#define CATOGMCORE_DOMAINTYPE_SIZE                  0x04

typedef unsigned char CATOGMCORE_INTENTSTATE;
#define CATOGMCORE_INTENTSTATE_TO_REMAIN    0x01
#define CATOGMCORE_INTENTSTATE_TO_CREATE    0x02
#define CATOGMCORE_INTENTSTATE_TO_UPDATE    0x04
#define CATOGMCORE_INTENTSTATE_TO_DELETE    0x08
 
typedef unsigned char CATOGMCORE_DUPLICATE;
#define CATOGMCORE_DUPLICATE_SHAREDATOMS 0x01
 
typedef unsigned char CATOGMCORE_OBJECTIVE;
#define CATOGMCORE_OBJECTIVE_Enumerate                 0x01
#define CATOGMCORE_OBJECTIVE_MaxMlcVersionOfInstances  0x02
#define CATOGMCORE_OBJECTIVE_PERSISTENCY               0x04
#define CATOGMCORE_OBJECTIVE_WithUNDO                  0x08
#define CATOGMCORE_OBJECTIVE_WithDependancies          0x10
 
typedef unsigned char CATOGMCORE_DIRTIFY;
#define CATOGMCORE_DIRTIFY_FreezeFederators 0x01
#define CATOGMCORE_DIRTIFY_FreezeManaged    0x02
#define CATOGMCORE_DIRTIFY_ManagedDirty     0x03
#define CATOGMCORE_DIRTIFY_ManagedByBlob    0x04
#define CATOGMCORE_DIRTIFY_AlwaysDirty      0x05
 
class  CATOGMCoreHead ;
class  CATOGMCoreAtom; 
class  CATOGMCoreSet; 
class  CATOGMCoreDomain; 
 

#endif
