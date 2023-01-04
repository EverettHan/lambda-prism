#ifndef CATFrFLoftMappingLawDef_H
#define CATFrFLoftMappingLawDef_H


//====================================================================
// Copyright Dassault Systemes Provence 2005, all rights reserved 
//====================================================================
// Usage notes:
//==========================================================================
// April,   2005 : ANR/FZA : Creation 
//==========================================================================



/**
 * The type of mapping law between two arcs.
 * @param CATFrFLoftLinearParamLaw
 * The weight function is based on the parameterization itself.
 * @param CATFrFLoftLinearArcLengthLaw
 * The weight function is based on the curvilinear abscissa.
 * @param CATFrFLoftLinearDistanceLaw
 * The distance between the extremity guides controls the parameterization.
 */
typedef enum
{
  CATFrFLoftLinearParamLaw     = 0,
  CATFrFLoftLinearArcLengthLaw = 1,
  CATFrFLoftLinearDistanceLaw  = 2
} CATFrFLoftMappingLawDef;


#endif




