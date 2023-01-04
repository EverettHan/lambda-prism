#ifndef CATDistanceSignMode_H
#define CATDistanceSignMode_H


// COPYRIGHT DASSAULT SYSTEMES  2010

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 



/**
* Sign mode for distance computation.
* @param CATDistanceSignModeDefault
*   "Default" mode chosen by the operator as per documentation of the operator.
* @param CATDistanceSignModeZero
*   "Zero" mode: i.e. distance is zero if point is inside the volume of the body.
* @param CATDistanceSignModeSigned
*   "Signed" mode: i.e. Sign of distance is negative if point is inside the 
*   volume of the body and its absolute value is the distance of the point from 
*   the shell of the body.
* @param CATDistanceSignModeUnsigned
*   "Unsigned" mode: i.e. Sign of distance is never negative. The distance value
*   is always the distance of the point from the shell of the body.
*/

enum CATDistanceSignMode 
{ 
  CATDistanceSignModeDefault,
  CATDistanceSignModeZero, 
  CATDistanceSignModeSigned, 
  CATDistanceSignModeUnsigned,
};

#endif
