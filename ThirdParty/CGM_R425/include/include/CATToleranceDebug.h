#ifndef CATToleranceDebug_H
#define CATToleranceDebug_H

#include "YN000MAT.h"
// COPYRIGHT DASSAULT SYSTEMES  2007
//
// Special access to CATTolerance debug tools
// (a ne pas interfacer en R204)
//
// 04/05/2013 EB A ne pas deployer. Fondé sur des a priori sur le stream erronés 
/*typedef*/ // pkc 26/04/2017 typedef inutile en C++, warning compilation 
enum CATToleranceDebug_Action
{
  CATToleranceDebug_XScaleDefectsInit
 ,CATToleranceDebug_OldScenarioBegin
 ,CATToleranceDebug_OldScenarioEnd
};

extern "C" ExportedByYN000MAT 
void CATToleranceDebug(CATToleranceDebug_Action iAction) ;
#endif
