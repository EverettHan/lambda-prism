/* -*-C++-*-*/
#ifndef CATFatEdgeFixed_H
#define CATFatEdgeFixed_H
// COPYRIGHT DASSAULT SYSTEMES 2003
//----------------------------------------------------------------------------------------------
// Fat Edge :
//   Activable par variable d'environnement
//             ou par versionning
//----------------------------------------------------------------------------------------------
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"

class CATSoftwareConfiguration;

// iFatEdgeLevel=1: base level of fix (R13 SP3)
// iFatEdgeLevel=2: next level of fix (tbd)

extern ExportedByCATMathStream CATBoolean CATFatEdgeFixed(CATSoftwareConfiguration * iConfig,
                                                          const int iFatEdgeLevel = 1        );

#endif

