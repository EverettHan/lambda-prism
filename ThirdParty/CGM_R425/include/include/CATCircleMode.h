#ifndef CATCircleMode_h_
#define CATCircleMode_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1 
 */ 

/**
* The relimitation mode of the corner operator.
* @param Direct
* The corner is limited by the input wires. The shortest portion is kept.
* @param Complementary
* The corner is limited by the input wires. The longest portion is kept.
* @param Angular
* The length of the corner is defined by the angular sector, which reference is .
* In case of planar wires.
* @param Complete
* The corner is limited by the input wires. Both portions are kept. Default mode.
*/
typedef enum { Direct, Complementary, Angular, Complete} CATCircleMode;

#endif /* CATCircleMode_h_ */
