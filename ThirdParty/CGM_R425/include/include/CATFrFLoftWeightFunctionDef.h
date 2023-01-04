#ifndef CATFrFLoftWeightFunctionDef_H
#define CATFrFLoftWeightFunctionDef_H


//====================================================================
// Copyright Dassault Systemes Provence 2005, all rights reserved 
//====================================================================
// Usage notes:
//==========================================================================
// April,   2005 : ANR/FZA : Creation 
//==========================================================================

/**
 * The type of mixing law.
 * @param CATFrFLoftIdentityWeightFunction
 * Each profile has the same weight in the mixing law.
 * @param CATFrFLoftSWeightFunction
 * The parameterization of a profile has more weight in its neighborhood ("S" shaped law).
 */
typedef enum 
{
  CATFrFLoftIdentityWeightFunction = 1,
  CATFrFLoftSWeightFunction        = 2
}CATFrFLoftWeightFunctionDef;


#endif




