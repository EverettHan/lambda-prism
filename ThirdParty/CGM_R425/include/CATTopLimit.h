#ifndef CATTopLimit_H
#define CATTopLimit_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 



/**
 * The extremity used in a topological operation.
 * @param CatLimStart
 * The extremity associated with the start offset for a prism, with the start vertex 
 * of the profile wire for a revolution, with the start vertex of the center wire for a sweep.
 * @param CatLimEnd
 * The extremity associated with the end offset for a prism, with the end vertex 
 * of the profile wire for a revolution, with the end vertex of the center wire for a sweep
 */
enum CATTopLimit 
{ CatLimStart, CatLimEnd };

#endif
