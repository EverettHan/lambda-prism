/* -*-c++-*- */
#ifndef CATCGMNativeInterface_H_
#define CATCGMNativeInterface_H_

// COPYRIGHT DASSAULT SYSTEMES 1999

//-------------------------------------------------------------------------------------
//   Pour une gestion fiable des references d'objects dans le modeleur CGM
// On doit privilegie l'interface native associee a l'implementation
//   si on veut exploiter cette information sur une duree assez longue 
//   jusqu'a la vie de l'object dans le container ou dans le Clear()
//-------------------------------------------------------------------------------------
#include "CATCGMDebug.h"
#include "CATCGMObject.h"
  
#define CATCGMNativeInterface(itf,CLASSNAME)  if ( itf ) itf = (CLASSNAME *)CATCGMObject::CATCGMNativeInterfaceImpl(itf)

#endif
