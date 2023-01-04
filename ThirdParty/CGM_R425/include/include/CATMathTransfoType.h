#ifndef CATMathTransfoType_H
#define CATMathTransfoType_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Defines the type of transformation.
 * @param CATMathScaling
 * The transformation is a scaling.
 * @param CATMathRotation
 * The transformation is a rotation.
 */
typedef enum
{
  CATMathScaling = 1,
  CATMathRotation
}
CATMathTransfoType;

#endif
