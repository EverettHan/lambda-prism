/* -*-c++-*- */
#ifndef CATCGMEventType_H
#define CATCGMEventType_H
// COPYRIGHT DASSAULT SYSTEMES  2002
//============================================================================
//  Managing event from Geometric Modeler 
//============================================================================
// Feb. 04 CatCGMEvent_UnlinkByOperator                                  HCN
//============================================================================

#include "ExportedByGeometricObjects.h"
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATUnicodeString;

enum CATCGMEventType
{
  CatCGMEvent_StreamSizeObject    = 0x00000001,
  CatCGMEvent_TopologyCompletion  = 0x00000002,
  CatCGMEvent_GraphicModification = 0x00000004,
  CatCGMEvent_RemoveComponent     = 0x00000008,
  CatCGMEvent_ExplicitChange      = 0x00000010,
  CatCGMEvent_Extrapolation       = 0x00000020,
  CatCGMEvent_ImplicitFactoryLife = 0x00000040,
  CatCGMEvent_GenericNamed        = 0x00000080,
  CatCGMEvent_FactoryOpen         = 0x00000100,
  CatCGMEvent_FactorySave         = 0x00000200,
  CatCGMEvent_FactoryClose        = 0x00000400,
  CatCGMEvent_Persistent          = 0x00000800,
  CatCGMEvent_Callback            = 0x00001000, // Old Management ...
  CatCGMEvent_UnlinkByOperator    = 0x00002000,
  CatCGMEvent_KeepUselessGeometry = 0x00004000,
  CatCGMEvent_KeepInvalidVIF      = 0x00008000,
  CatCGMEvent_NotSpecified        = 0x80000000
};

ExportedByGeometricObjects void CATCGMEventTypeDump(ostream & ioDump,         const CATCGMEventType iWhen);
ExportedByGeometricObjects void CATCGMEventTypeDump(CATUnicodeString & ioDump, const CATCGMEventType iWhen);


#endif
