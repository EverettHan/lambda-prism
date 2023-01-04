#ifndef CATPower_H
#define CATPower_H
// COPYRIGHT DASSAULT SYSTEMES 2008
//==========================================================================
//
// CATPower: optimized power computation for double value
// 
// dedicated to Cat Power
//==========================================================================
//
// Usage notes:
//==========================================================================
// 04/02/08 NLD Creation
// 15/10/15 NLD Parenthesage de securite complet autour des arguments
//==========================================================================

// CATPower(double doublevalue, int       intpower) : power intpower    of doublevalue 
// CATPower(double doublevalue, double doublepower) : power doublepower of doublevalue 
#define CATPower(doublevalue, intpower)\
 ((intpower)==0? 1.0 : ((intpower)==1) ? (doublevalue) : pow((double)(doublevalue),(double)(intpower)))
#endif
//
