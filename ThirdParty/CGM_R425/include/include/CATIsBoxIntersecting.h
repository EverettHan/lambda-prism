//===================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//===================================================================
//
// CATIsBoxIntersecting
// 
//
//===================================================================
// Usage notes : Determine if the internal boxes, possibly offseted,
// of a Curve intersect a 3D Box.
//===================================================================

#ifndef CATIsBoxIntersecting_H
#define CATIsBoxIntersecting_H
#include "Y30UIUTI.h"

#include "CATBoolean.h"
#include "CATCurve.h"
#include "CATCrvLimits.h"
#include "CATMathBox.h"
#include "CATSoftwareConfiguration.h"

ExportedByY30UIUTI CATBoolean CATIsBoxIntersecting(const CATCurve * iCrv,
                                                   CATCrvLimits &iCrvLim,
                                                   CATMathBox &iMBox, double iOffset = 0.0);

ExportedByY30UIUTI CATBoolean CATIsBoxIntersecting(CATSoftwareConfiguration * iConfig,
                                                   const CATCurve * iCrv,
                                                   CATCrvLimits &iCrvLim,
                                                   CATMathBox &iMBox, double iOffset = 0.0);

#endif
