/* -*-c++-*- */
#ifndef CATGGAGeoAtExitCGM_h
#define CATGGAGeoAtExitCGM_h


#include "ExportedByCATCGMFusion.h"

//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
class ExportedByCATCGMFusion CATGGAGeoAtExitCGM
{
public :
   CATGGAGeoAtExitCGM();
   ~CATGGAGeoAtExitCGM();

   static int  onlyCATGGAGeoAtExit;
   static void InitForExit();
};

 
ExportedByCATCGMFusion extern int CATGGAGeoAtExit();


#endif
