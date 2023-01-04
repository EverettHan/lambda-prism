/* -*-c++-*- */
#ifndef CATCXStreamKeepEvolution_H
#define CATCXStreamKeepEvolution_H
// COPYRIGHT DASSAULT SYSTEMES 1998
//=============================================================================
// CATCXStreamKeepEvolution :Identification d'une transaction de Tass 
//      (dedicated to Debug Mode with subd / IE)
//=============================================================================
// Jan. 01    ...                                             TCX
//=============================================================================
#include "ExportedByCATCGMFusion.h"      

// Pour implementation avec information de TimeStamp
ExportedByCATCGMFusion int CATCXStreamIsKeepingEvolution(); 


// Pour comparateur d'octets
ExportedByCATCGMFusion void CATCXStreamSetKeepingEvolution(); 
ExportedByCATCGMFusion void CATCXStreamUnsetKeepingEvolution(); 

#endif

