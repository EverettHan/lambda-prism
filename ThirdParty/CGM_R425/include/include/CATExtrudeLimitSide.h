#ifndef CATExtrudeLimitSide_H
#define CATExtrudeLimitSide_H

/** @CAA2Required */ 
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
// COPYRIGHT DASSAULT SYSTEMES  2012

/**
 * @nodoc
 * The side of the limiting geometry where the extrusion should stop
 * @param  NegativeSide
 * The normal to the limiting geometry and the direction of extrusion are in opposite way
 * @param  NoSide
 * NoSide is defined. We don't take into account the side.
 * @param  PositiveSide
 * The normal to the limiting geometry and the direction of extrusion are in opposite way
 */
typedef enum  
{ 
  CATExtrudeLimitNegativeSide = -1, 
  CATExtrudeLimitSideUnset    = 0, 
  CATExtrudeLimitPositiveSide = 1
}
CATExtrudeLimitSide;

#endif
