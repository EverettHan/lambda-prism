#ifndef CATFastRunDbgTools_H
#define CATFastRunDbgTools_H

// divers debug et mise au point pour FastRun
// doit pouvoir etre utilise ds le code CGM "pur", le code MechMod/GN, le code "applis"

#include "ExportedByCATTopologicalObjects.h"

#include "CATBooleanDef.h"
#include "CATUnicodeString.h"
#include "CATBoolean.h"

class CATBody;

class ExportedByCATTopologicalObjects CATFastRunDbgTools
{
public: 

  static boolean CGM_FASTRUN_ZYVA() ;

  static void ResetNbFastRunEffectifs() ;
  static void UnsetNbFastRunEffectifs() ;
  static void IncrementeNbFastRunEffectifs() ;
  static int ReadNbFastRunEffectifs() ;

};

#endif





