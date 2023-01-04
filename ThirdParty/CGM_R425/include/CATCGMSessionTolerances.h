/* -*-c++-*- */
#ifndef CATCGMSessionTolerances_h
#define CATCGMSessionTolerances_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2001
//-----------------------------------------------------------------------------
//  Pour controle des Tolerances de la Session memoire
//-----------------------------------------------------------------------------
#include "ExportedByCATCGMFusion.h"
#include "CATBoolean.h"
#include "CATGeoFactory.h"  // CATCGMTolerancesCompatibility

class CATRootSharedDataCGM;

class ExportedByCATCGMFusion CATCGMSessionTolerances 
{
public:
  static void CGMSessionTolerancesInit();
  static CATCGMTolerancesCompatibility CompareTolerances(const CATRootSharedDataCGM *iFirst,
                                                         const CATRootSharedDataCGM *iSecond,
                                                         CATBoolean  iThrowIfComparableButNotIdentical );
  static int  CompareScale     (double iFirst, double iSecond);

  static CATBoolean RiskySessionTolerances (CATULONG32 iNbSessionScaleCalled);
//--------------------------------------------------------------------------------
private:
  static int          _InitDone;
  static CATULONG32   _NbSessionTolerancesCalls;
  static CATTolerance _Tolerance; //Added for Extreme Scale project

  friend class        CATRootSharedDataCGM; 
};


#endif
