/* -*-c++-*- */
#ifndef CheckPotDeVin_h
#define CheckPotDeVin_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Levee de PotDeVin en erreurs severes
//-----------------------------------------------------------------------------
// Mars 00      TCX pour convergence rapide
//-----------------------------------------------------------------------------
#include "CATMathDef.h"
#include "CATBooleanDef.h"
#include "ExportedByCATCGMFusion.h"

class CATTrace;

class ExportedByCATCGMFusion CheckPotDeVin 
{
public:

  static CATBoolean IsOn();

  static void CleanAtExit();

private:

  static int         _InitDone;
  static CATTrace  * _CheckPotDeVin;
};

#endif
