#ifndef CATCGMCreateSketchGeodesic_h_
#define CATCGMCreateSketchGeodesic_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CATSkillValue.h"

class CATBody;
class CATFace;
class CATGeoFactory;
class CATMathVector;
class CATICGMSketchGeodesic;
class CATSurParam;
class CATTopData;

/**
* Creates a CATICGMSketchGeodesic operator 
* that computes the geodesic on a support from a start point, a direction and a length.
* @param iFactory
* The pointer to the factory of the resulting body.
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iSupportShell
* The pointer to the body defining the support of the geodesic. 
* @param iFaceSupportPoint
* The pointer to the face on which the start point is located.
* @param iParamPoint
* The pointer to the SurParam corresponding to the start point. 
* @param iTangent
* The pointer to the direction of the geodesic. 
* @param iLength
* The param iLength which specifies the length of the resulting geodesic. 
* @param iMode
* The operator mode.
* <dl><dt><tt>BASIC</tt> The operation is performed at the operator creation. NOT TO BE USED.
*     <dt><tt>ADVANCED</tt>Use the Run method. </dl>
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
//
ExportedByCATGMOperatorsInterfaces CATICGMSketchGeodesic *CATCGMCreateGeodesicPointDir(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iSupportShell,
  CATFace *iFaceSupportPoint,
  CATSurParam *iParamPoint,
  CATMathVector *iTangent,
  CATPositiveLength iLength,
  CATSkillValue iMode = BASIC);

#endif /* CATCGMCreateSketchGeodesic_h_ */
