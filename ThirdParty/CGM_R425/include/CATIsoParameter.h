#ifndef CATISOPARAMETER_H
#define CATISOPARAMETER_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
/**
 * The parameterization properties.
 * @param CATNotIsoParametric
 * The object is not parametric.
 * @param CATNotParNoDir
 * The object is not parametric.
 * @param CATIsoParamU
 * The first direction parameter .
 * @param CATIsoParamV
 * The second direction parameter.
 * @param CATIsoParBothDir
 * Both parameter directions are considered..
 */
enum CATIsoParameter
{
   CATNotIsoParametric = 0,
   CATIsoParNoDir      = 0,  
   CATIsoParamU        = 1,
   CATIsoParamV        = 2,
   CATIsoParBothDir    = 3   
}; 
#endif
