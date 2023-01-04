//====================================================================================
// CATDOCODef.h : Definitions for DisconnectOneCellOnly operator.
//------------------------------------------------------------------------------------
// 14/04/2016  G5S  Creation
// 31/05/2016  U29  Modification
// 03/02/2016  G5S  File no longer needed because we use CATDynOperatorDef.h for the enums
//                  and the errors are defined in the .cpp files for which they're used.  
//====================================================================================
#ifndef CATDOCODef_h_
#define CATDOCODef_h_
#include "CATDynOperatorDef.h"

//********************************************************
//                   Enums
//********************************************************
#define CATDOCOExtrapolationMode CATDynExtrapolationMode
#define CATDOCOExtrapolationLimit CATDynExtrapolationLimit
#define DOCO_NO_EXTRAPOLATION DYN_NO_EXTRAPOLATION
#define DOCO_TANGENT_DIRECTION DYN_TANGENT_DIRECTION
#define DOCO_CURVATURE_EXTRAPOLATION DYN_CURVATURE_EXTRAPOLATION
#define DOCO_BODYBOUNDINGBOX DYN_BODYBOUNDINGBOX
#define DOCO_THRUNEXTCONNECTED DYN_THRUNEXTCONNECTED

#endif /* CATDOCODef_h_ */
