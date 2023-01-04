#ifndef CGMVersionEnum_h
#define CGMVersionEnum_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//----------------------------------------------------------------------------------------------
// Pour l'implementation de la Table de correspondance de l'affectation des Levels
//----------------------------------------------------------------------------------------------
#include "CGMVersionDebug.h"
 
// Enumerate variables
// <<
#define CGMVersionMacroDefine(Level, VariableName, Resp, Date, Comment) \
  CGMVersionEnum_##VariableName,

enum CGMVersionEnum
  {
#include "CATCGMVersionDefine.h"

    CGMVersionEnumMAX
  };

#undef CGMVersionMacroDefine
#undef CATCGMVersionMacroDefine1_h
#undef CATCGMVersionMacroDefine2_h
#undef CATCGMVersionMacroDefine3_h
#undef CATCGMVersionMacroDefine4_h
#undef CATCGMVersionMacroDefine5_h  
#undef CATCGMVersionMacroDefine6_h  

#endif
