#ifndef GeometricBasic_H
#define GeometricBasic_H

// COPYRIGHT DASSAULT SYSTEMES 1999

#include "CXMODEL.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATCrvParam.h"
#include "CATSurParam.h"

class CATMathVector;

class CATEdgeCurve;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATGeoFactory;
class CATMathLine;
class CATMathAxis;
class CATSoftwareConfiguration;

//------------------------------------------------------------------------------
// Compute the normal unit vector to a surface in a point defined by a given
// surface parameter
//------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATBoolean NormalOnSurface  // Returns true if normal vector is ok,
                                             // and false if normal vector is nought

(
 CATSurface    *iSurface      , // Surface
 CATSurParam   &iParmOnSurface, // Surface parameter
 CATMathVector &oVecNormal,     // Normal unit vector
 CATBoolean     iNormVec=1      // 1 if VecTangent must be normed, 0 else 
);

//------------------------------------------------------------------------------
// Compute the tangent unit vector to a given curve for a given curve parameter
//------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATBoolean TangentToCurve  // Returns true if tangent vector is k,
                                            // and false if tangent vector is nought

(
 CATCurve      *iCurve       , // Curve
 CATCrvParam   &iParmOnCurve , // Curve parameter
 CATMathVector &oVecTangent,   // Tangent unit vector
 CATBoolean     iNormTtgt=1    // 1 if VecTangent must be normed, 0 else 
);

//------------------------------------------------------------------------------
// Check if two PCurves in an EdgeCurve are confused according to UV parameter
// (test on mid point only)
//------------------------------------------------------------------------------

ExportedByCATTopologicalObjects CATBoolean PCConfusionInUV 
(
 CATEdgeCurve * EC, 
 CATPCurve * PC1, 
 CATPCurve * PC2,
 CATGeoFactory * iFactory,
 CATSoftwareConfiguration * SoftConf=NULL
 );

//------------------------------------------------------------------------------
// Build a CATMathAxis from a CATMathLine (Z axis along Line direction, same origin)
//------------------------------------------------------------------------------
ExportedByCATTopologicalObjects void BuildAxisFromLine(const CATMathLine& iLine, CATMathAxis& oAxis);

//------------------------------------------------------------------------------


#endif






