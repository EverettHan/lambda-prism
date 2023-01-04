#ifndef CATMathDebugScale_h
#define CATMathDebugScale_h
//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 2007
//
// Access to declared scale ** for debug purposes before full migration on CATTolerance **
//
// Scale is accessible if 3 variables defined:
// export CGMBigScaleON=1                  <---- standard declaration
// export CGMScaleValue=??? (scale value)  <---- standard declaration
// export CGMDebugScale=1                  <---- new debug declaration specific to this object
// otherwise Scale is set to 1.0
// 
// Scale is also available through CATMathDebugScale() with same settings but CGMDebugScale inactive,
// if a mail has been send through CATMathStackScale()
// This mail must be unstacked at end of treatment, even if exception is raised,
// through CATMathUnstackScale()
//=============================================================================
// Abstract Class     : No
// Template Code      : No
// Inline Functions   : Yes
//=============================================================================
//
// History
//
// 18/12/07 NLD XScale. Creation. CATMathDebugScale()
// 07/02/08 NLD XScale. Ajout _AnchorDebugScale
// 16/09/09 NLD XScale. Ajout CATMathStackScaleMail() et CATMathUnstackScale()
//              Attention leurs usages doivent etre limites et securises, et en particulier
//              il est recommande d'utiliser les macros CATTry/CATCatch afin
//              d'assurer le depilage du mail en cas d'exception
//=============================================================================
#include <CATMathematics.h>
extern "C" ExportedByCATMathematics double CATMathDebugScale() ;
extern ExportedByCATMathematics const void*  _AnchorDebugScale ;

// Stacks a mail containing Scale value on mail stack to make CATMathDebugScale() work
extern "C" ExportedByCATMathematics void CATMathStackScale(void* iSender, double iScale) ;
// Unstacks the mail containing Scale value on mail stack
// in order to check property, iSender must be the same as provided to previous symmetric CATMathStackScale call
extern "C" ExportedByCATMathematics void CATMathUnstackScale(void* iSender) ;
#endif
