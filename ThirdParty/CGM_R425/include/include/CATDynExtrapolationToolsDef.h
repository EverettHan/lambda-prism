#ifndef CATDynExtrapolationToolsDef_h_
#define CATDynExtrapolationToolsDef_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATIACGMLevel.h"

#ifdef CATIACGMR217CAA
/**
* Defines the mode of extrapolation during a cutting operation.
*<br>This is useful when the cutting body does not cut right through the body to cut, or
* vice versa in case of a trim operation.
* @param DYN_NO_EXTRAPOLATION
* No extrapolation is performed. In this case, the operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* @param DYN_TANGENT_DIRECTION
* If the cutting body does not cut right along the body to cut, the cutting body is 
* extrapolated along tangent direction to meet the body to cut.
* @param DYN_CURVATURE_EXTRAPOLATION
* If the cutting body does not cut right along the body to cut, the cutting body is 
* extrapolated preserving the original surface curvature.
*/
enum CATDynExtrapolationMode{ DYN_NO_EXTRAPOLATION, DYN_TANGENT_DIRECTION, DYN_CURVATURE_EXTRAPOLATION };
#else
/**
* Defines the mode of extrapolation during a cutting operation.
*<br>This is useful when the cutting body does not cut right through the body to cut, or
* vice versa in case of a trim operation.
* @param DYN_NO_EXTRAPOLATION
* No extrapolation is performed. In this case, the operator cannot find a solution
* if the cutting body does not cut right along the body to cut.
* @param DYN_TANGENT_DIRECTION
* If the cutting body does not cut right along the body to cut, the cutting body is 
* extrapolated to meet the body to cut
*/
enum CATDynExtrapolationMode{ DYN_NO_EXTRAPOLATION, DYN_TANGENT_DIRECTION };
#endif

//#ifdef CATIACGMR420CAA
/*
 * Define the extrapolation limit during a Split or DOCO. 
 * @param DYN_BODYBOUNDINGBOX
 * Extrapolate up to the bounding box of the body to cut.
 * @param DYN_THRUNEXTCONNECTED
 * The extrapolation result should only include parts of the extrapolation that are both
 * inside the body to cut and connected to the splitting body before extrapolation.
*/
enum CATDynExtrapolationLimit{ DYN_BODYBOUNDINGBOX, DYN_THRUNEXTCONNECTED};
//#endif

#endif /* CATDynExtrapolationToolsDef_h_ */
