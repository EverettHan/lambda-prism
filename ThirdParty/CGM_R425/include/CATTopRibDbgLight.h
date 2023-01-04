/* -*-C++-*- */

#ifndef CATTopRibDbgLight_H
#define CATTopRibDbgLight_H

// COPYRIGHT DASSAULT SYSTEMES 1997

//------------------------------------------------------------------------------
//
// Debug utilities for CATTopRib
//
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Usage notes:
//
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
// Feb. 98    Creation methode                         A. State
// Dec  06    Split pour CATIA Light                   PRL
//------------------------------------------------------------------------------
#include "PersistentCell.h"


#include "CATCGMActivateDebug.h"         // pour que CATTopRibDbg suffise a l appelant

enum CATTopRibDebugBreakPoint 
{
  VerboseDebug,     // Must stay in first position because is the default
  TopRibDebug,
  FaceFaceDebug,
  SewingDebug,
  ExportDebug,
  ExtraDebug,
  InitDebug,
  R4ADebug,
  CheckDebug,
  RawTrackDebug,
  SyncTracksDebug,
  LastSolDebug,
  TopRlmDebug,
  ReorderDebug,
  SelfInterDebug,
  MatchingDebug,
  PartingDebug,
  PropagDebug,
  CutTrackDebug,
  RibEndDebug,
  VertexBlendDebug,
  RibConfusions,
  AbsorbtionDebug,
  BVDebug,
  VertexChamferDebug
};

//------------------------------------------------------------------------------
// Returns CATCGMActivateDebug* if Break Point is activated for this type of debug,
// returns NULL if not activated.
extern "C" ExportedByPersistentCell CATCGMActivateDebug* GetTopRibDebug(const CATTopRibDebugBreakPoint iBreakPointType=TopRibDebug);
// extern "C" ExportedByTopUtilLight void DeleteTopRibDebug();


#endif
