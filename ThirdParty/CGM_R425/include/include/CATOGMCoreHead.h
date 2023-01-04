#ifndef CATOGMCoreHead_H
#define CATOGMCoreHead_H
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
// Core Persistent Structure  
//----------------------------------------------------------------------------------------------
#include "CATOGMCore.h"
 

//------------ ----------- ---------- 
//    Head is defined by :
//         DomainType
//         Intents
//         Key  
//------------ ----------- ---------- 
class ExportedByCATOGMCore CATOGMCoreHead 
{
public :

  union
  {
    struct  // CATOGMCORE_DOMAINTYPE_GEOMETRY et Cf CGMHeaderStream.h / CATCGMHeaderObjectStream
    {
      CATULONG32    _Tag;
      short         _Type;
    }
    _GEOMETRY;

    struct  // CATOGMCORE_DOMAINTYPE_GEOMETRY et Cf CGMHeaderStream.h / CATCGMHeaderObjectStream
    {
      CATULONG32    _SessionId;
    }
    _CGMCONTAINER ;

  }
  _Key;

  
  CATOGMCORE_DOMAINTYPE   _Domain;

  CATOGMCORE_INTENTSTATE  _Todo;


  /** HashKey */
  unsigned int  HashKey();

};

#endif
