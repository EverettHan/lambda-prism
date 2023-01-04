// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
// Apr 00 Creation                       PSH
//
//=============================================================================
// Usage notes:
//  This operator is used to check if a surface is ruled and along which
//  direction
//  This implies that the corresponding parameters are curvilinear
//  Important: Non-curvilinear parameters are never considered as "ruled"
//             (i.e. logarithmic parameters along a straight line)
//
// Warning: For internal usage - limited to Fillet and Draft - only!!!
//=============================================================================
#ifndef CATIsRuledSurface_H
#define CATIsRuledSurface_H

// Useless code FDS , 2011/01/11
/* 
#include "Y30UIUTI.h"
#include "CATSoftwareConfiguration.h"

class CATGeoFactory;
class CATSurface;

enum CATRuleDiagnostic { CATNotRuled, CATRuledU, CATRuledV, CATRuledUV };

ExportedByY30UIUTI CATRuleDiagnostic CATIsRuledSurface
(CATGeoFactory *iFactory, CATSurface *iSurface);

ExportedByY30UIUTI CATRuleDiagnostic CATIsRuledSurface
(CATGeoFactory *iFactory, CATSoftwareConfiguration * iConfig, CATSurface *iSurface);

*/

#endif
