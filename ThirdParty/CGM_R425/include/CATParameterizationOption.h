#ifndef CATPARAMETERIZATIONOPTION_H
#define CATPARAMETERIZATIONOPTION_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/**
 * The type of parameterization of a CATKnotVector linked to a CATNurbs.
 * @param CatKeepParameterization
 *   The CATKnotVector keeps its current parametrization.
 * @param CatAutomaticParameterization
 *   The parametrization of the CATKnotVector is globally changed, by taken into account
 * the length of the object it is used to parameterized.
 * If the nodal values of the CATKnotVector were (0,1,2,3) and the total length 
 * of the curve is 15, the nodal values will become (0,5,10,15), whatever 
 * the length of each segment is.   
 */
enum CATParameterizationOption
{
   CatKeepParameterization = 0,
   CatAutomaticParameterization = 1   
}; 
#endif
