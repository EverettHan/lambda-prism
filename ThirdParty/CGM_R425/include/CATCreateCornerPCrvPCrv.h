// COPYRIGHT DASSAULT SYSTEMES 1998
//=================================================================================
//
// CreateCornerPCrvPCrv :
// creation of an operator of corner between two PCurves
//
//=================================================================================
// Usage Notes:
//
// KLX 28/05/03 : commentaire de CCK sur Sign1 et Sign2
//
// Pour faire le corner, on fait deux offsets de PCurve1 etPCurve2
// de rayon Radius. L'intersection de ces deux offsets donne le centre du cercle.
//
// Il faut donc savoir dans quelle direction on va faire les offsets.
// Ces directions sont donnees par Sign1 et Sign2 valant +1 ou -1 :
//
// Placons-nous en un point donne de PCurve1.
// Soit Normal = la normale au support en ce point.
//      Tgt1   = tgte a PCurve1 en ce point, qui donne l'orientation de PCurve1
// La direction de l'offset de PCurve1 est alors Dir = Sign1 * (Normal ^ Tgt1).
//
//=================================================================================

#ifndef CATCREATECORNERPCRVPCRV_H 
#define CATCREATECORNERPCRVPCRV_H 

#include "Y300IINT.h"
#include "CATSkillValue.h"
#include "CATMathDef.h"

class CATCornerPCrvPCrv ;
class CATGeoFactory ;
class CATPCurve ;
class CATPointOnSurface ;
class CATSoftwareConfiguration;

ExportedByY300IINT CATCornerPCrvPCrv *CATCreateCornerPCrvPCrv (
                                                            CATGeoFactory       *Factory,
                                                            CATSoftwareConfiguration *iConfig,
                                                            CATPCurve           *PCurve1, 
                                                            CATPCurve           *PCurve2, 
                                                            CATPointOnSurface   *PPoint, 
                                                            CATPositiveLength   &Radius,
                                                            CATSkillValue       iMode = BASIC
                                                            ) ;

ExportedByY300IINT CATCornerPCrvPCrv *CATCreateCornerPCrvPCrv (
                                                            CATGeoFactory       *Factory,
                                                            CATSoftwareConfiguration *iConfig,
                                                            CATPCurve           *PCurve1,
							    int                 Sign1,
                                                            CATPCurve           *PCurve2, 
							    int                 Sign2,
                                                            CATPositiveLength   &Radius,
                                                            CATSkillValue       iMode = BASIC
                                                            ) ;

ExportedByY300IINT void Remove (CATCornerPCrvPCrv *iOperatorToRemove) ;

#endif


