/* -*-c++-*- */
#ifndef CATCX_FREEZE_h
#define CATCX_FREEZE_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Convergence des anomalies dans la gestion du Freeze
// Pour un processus progressif de convergence de Code
//-----------------------------------------------------------------------------
// Fev 00      TCX pour convergence rapide
//-----------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"
#include "CATMathDef.h"
#include "CATBooleanDef.h"
#include "CATCGMBuildDebug.h"

class CATCGMObject;
class CATTrace;

class ExportedByCATCGMFusion CATCX_FREEZE 
{
public:

  static void Error(CATCGMObject *object, const char context[], CATBoolean ForceThrow, CATBoolean ForcePotDeVin=FALSE,
    const char *iFile = NULL, const int iLine = 0 );
  
  //-----------------------------------------------------------------------------
  // Permettre une desactivation temporaire
  //-----------------------------------------------------------------------------
  static CATBoolean TemporayChange(CATBoolean NewActiveMode );

private:
  static CATBoolean IsOn(const char * *forODT);

  static char       *_filename;
  static int         _InitDone;
  static CATTrace  * _CATCX_FREEZE;
  static CATBoolean  _NoMessage;
};

#if defined ( CATCGMBuildDebug )
#define CATCX_FREEZE_ERROR(object,context,ForceThrow)  CATCX_FREEZE::Error(object,context,ForceThrow,FALSE,__FILE__,__LINE__)
#define CATCX_FREEZE_PotDeVin(object,context)          CATCX_FREEZE::Error(object,context,FALSE,TRUE,__FILE__,__LINE__)
#else
#define CATCX_FREEZE_ERROR(object,context,ForceThrow)  CATCX_FREEZE::Error(object,context,ForceThrow,FALSE,NULL,0)
#define CATCX_FREEZE_PotDeVin(object,context)          CATCX_FREEZE::Error(object,context,FALSE,TRUE,NULL,0)
#endif

#endif
