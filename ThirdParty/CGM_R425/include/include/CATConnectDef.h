//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATConnectDef:
// All constants specification in CATConnect
//
// Connect operator includes constant radius fillet, variable radius fillet,
// edge-surface fillet, curve-surface fillet and chamfer.
//
//==========================================================================
//
// Usage notes:
// 
//
//========================================================================== 
// September 12, 1997     Creation                                    X. Liu
// November 6th, 1997     Added CATConnectTargetSupport               X. Liu
//========================================================================== 


#ifndef CATConnectDef_H
#define CATConnectDef_H

//-----------------------------------------------------------------------------
// 
// Support ID : 
// 
//-----------------------------------------------------------------------------

#include "CATConnectDefines.h"

//-----------------------------------------------------------------------------
// 
// Guide curve orientation :
// CATConnectGuideDoubleOrientaion is useful only for specifying
// connect solutions are to be searched in double sense.
// 
//-----------------------------------------------------------------------------

#define CATConnectGuideLeftOrientation          (-1)
#define CATConnectGuideRightOrientation           1
#define CATConnectGuideDoubleOrientation          0
#define CATConnectGuideOppositeSpineDirection   (-2)
#define CATConnectGuideSpineDirection             2

//-----------------------------------------------------------------------------
// 
// Connect surface orientation
//
//-----------------------------------------------------------------------------

#define CATConnectSurfaceCentripetalOrientation    1
#define CATConnectSurfaceCentrifugalOrientation  (-1)


//-----------------------------------------------------------------------------
// 
// Connect target support whose domain is to be reached
//
//-----------------------------------------------------------------------------

#define CATConnectDefaultSupport                   0
#define CATConnectTargetSupport                    1

#define CATConnectLowLimit                         1
#define CATConnectHighLimit                        2

#endif
