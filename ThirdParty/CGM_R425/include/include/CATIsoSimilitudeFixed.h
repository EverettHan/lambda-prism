/* -*-C++-*-*/
#ifndef CATIsoSimilitudeFixed_H
#define CATIsoSimilitudeFixed_H
// COPYRIGHT DASSAULT SYSTEMES 2003
//----------------------------------------------------------------------------------------------
// Iso Similitude : correction of iso similitude for scaling in transfo manager
//   Activable through environnment variable or versionning
// iIsoSimilitudeLevelFixed : 
// - 0 correction a partir R18SP3
// - 1 correction a partir R19GA
//----------------------------------------------------------------------------------------------
#include "YP00IMPL.h"
#include "CATBoolean.h"

class CATCloneManager;
class CATTransfoManager;

// Test if transformation is a similitude ( non isometry ) and correction is active
extern ExportedByYP00IMPL CATBoolean CATIsoSimilitudeFixed ( const CATTransfoManager & iTransfoManager );

// Test if correction for clone manager / transfo manager are active
extern ExportedByYP00IMPL CATBoolean CATTransfoManagerFixed ( const CATCloneManager & iTransfoManager              ,
                                                              const int               iIsoSimilitudeLevelFixed = 1 );

#endif

