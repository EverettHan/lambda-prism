// COPYRIGHT DASSAULT SYSTEMES 1997
//===================================================================
//
// CATCurveOrientationStabilizer
//  CATNurbsSurface
//
//===================================================================
// 17th Jul 2003        		Creation							PRG (implementation)
//                                                et XGN (specs)
//===================================================================

#ifndef CATCurveOrientationStabilizer_H
#define CATCurveOrientationStabilizer_H

#include "Y30UIUTI.h"

class CATCurve;
class CATSoftwareConfiguration;

#include "CATCrvLimits.h"
#include "CATTolerance.h"

//-------------------------------------------------------------------
// Etant donne une courbe et un domaine sur cette courbe (on fournit des limites),
// le but de ce service est d'affecter à la courbe une orientation qui est stable
// dans l'espace.
// Cette orientation n'a donc pas vraiment de sens d'un point de vue pratique,
// elle ne sera utilisee que dans des cas rares de l'intersection surface/surface
// on on ne sait pas determiner d'orientation avec les normale des surfaces
// (normales paralles donc pas de triedre direct).
// 
// 
//-------------------------------------------------------------------
// GetStabilizedOrientation is a global function that returns :
//    0 if the computation has succeeded,
//    or 1 otherwise.
//
//Do not use - Use the method with a CATSoftwareConfiguration
ExportedByY30UIUTI CATLONG32 GetStabilizedOrientation(const CATCurve*     iCurve,
                                                 const CATCrvLimits& iCrvLimits,
                                                 CATLONG32&               ioOrientation,
                                                 const CATTolerance & nTol); // +1 if we chose the parametric orientation
                                                                      // -1 if we chose the opposite orientation to the parametric one
                                                                      // 0  if our computation does not enable us to take any decision. 
ExportedByY30UIUTI CATLONG32 GetStabilizedOrientation(CATSoftwareConfiguration * iConfig,
                                                      const CATCurve*     iCurve,
                                                 const CATCrvLimits& iCrvLimits,
                                                 CATLONG32&               ioOrientation,
                                                 const CATTolerance & nTol); // +1 if we chose the parametric orientation
                                                                      // -1 if we chose the opposite orientation to the parametric one
                                                                      // 0  if our computation does not enable us to take any decision. 


#endif
