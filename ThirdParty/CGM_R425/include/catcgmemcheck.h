/* -*-c++-*- */
#ifndef catcgmemcheck_h
#define catcgmemcheck_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2008
// CGM memory checker for memory corruption detection
//   origin RI 633364 : enovia 64 bits
//-----------------------------------------------------------------------------
#include "CATMathematics.h"

//-----------------------------------------------------------------------------
// memory checker : Entry Point for scan and check memory validity
//-----------------------------------------------------------------------------
extern "C" ExportedByCATMathematics void catcgmemcheck(const char iMsg[]="");

//-----------------------------------------------------------------------------
// memory checker : ANOMALY DETECTED
//-----------------------------------------------------------------------------
extern "C" ExportedByCATMathematics void catcgmemko();

//-----------------------------------------------------------------------------
// memory checker : signature for external function 
//-----------------------------------------------------------------------------
extern "C" { typedef void catcgmemchecker(); }  


#endif
