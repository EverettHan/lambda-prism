#ifndef CATSKILLVALUE_H
#define CATSKILLVALUE_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * Defines the level of use of a geometric operator.
 * @param BASIC
 * The operation is run at the operator creation.
 * @param ADVANCED
 * The operation is delayed at the call of the <tt>Run</tt> method, 
 * so that advanced parameters can be tuned.
 */
enum CATSkillValue { BASIC, ADVANCED };

#endif
