#ifndef CATPGMTopSweepAdapter_h_
#define CATPGMTopSweepAdapter_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATICGMTopSweep;

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2003
//=============================================================================
//
// CATTopSweepAdapter
// Adapter for internal or forward releases enhancements of CATTopSweep not available on previous levels.
//
//                                                 Nicolas LOCHARD
//=============================================================================
// Usage notes:
//
//=============================================================================
// 26 10 06 NLD Creation
//              ForceMultipleViewingDirMode()
//=============================================================================
// Module definition for Windows
// Advanced topological operators
//=============================================================================
// Force multiple viewing direction moving frame mode on CATTopSweepOperator
// (this mode is available for a sweep without reference element and without pulling direction)
ExportedByCATGMOperatorsInterfaces void CATPGMForceMultipleViewingDirMode(CATICGMTopSweep *iTopSweepOperator);

// Force fill twist mode on CATTopSweepOperator
// (this mode is available for a simple sweep with no boolean operation, and if twist reduction mode is active)
ExportedByCATGMOperatorsInterfaces void CATPGMForceFillTwistMode(CATICGMTopSweep *iTopSweepOperator);

#endif /* CATPGMTopSweepAdapter_h_ */
