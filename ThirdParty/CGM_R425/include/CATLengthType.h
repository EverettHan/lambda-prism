#ifndef CATLengthType_H
#define CATLengthType_H

// COPYRIGHT DASSAULT SYSTEMES 2011

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * Specifies that a given length is absolute or relative.
 * @param CATLengthType_ABSOLUTE_L
 * The distance is an absolute value, but the sign indicates the direction on the wire for finding the vertex.
 * @param CATLengthType_RELATIVE_L
 * The distance is a fraction of the total length of the wire.  Since it is a fraction, its value must be equal
 * to or between -1 and 1. A throw is made if that condition is not met.
 */
enum CATLengthType 
{ 
  CATLengthType_ABSOLUTE_L = 0, 
  CATLengthType_RELATIVE_L = 1 
};

#endif 
