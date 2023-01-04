#ifndef CATPARAMCOMPUTER_H
#define CATPARAMCOMPUTER_H

//=============================================================================
//
// COPYRIGHT : DASSAULT SYSTEMES 1997
//
//  Definition of type used to manage the CrvParam and SurParam
//  The defined functions allows the transposition from global to local parameter
// and vice-versa.
//
//=============================================================================
//
// History
//
// Jun. 97   Jose CHILLAN (jch)    Creation            
//
//=============================================================================

class CATParamData;

// This function returns a global parameter computed from the arc number,
// a local position, and a pointer of the implementation
typedef double (*CATGlobalParamComputer)(const CATParamData & iPosition,
					 void               * iImplementation);

// This method sets the value of an arc number and position on the arc
// computed from the global parameter and a pointer on the object
typedef void (*CATLocalParamsComputer)(const double &iGlobalParameter,
				       void         *iImplementation, 
				       CATParamData &oPosition);

#endif
