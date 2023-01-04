/* -*-c++-*- */
#ifndef CATCGMSessionScale_h
#define CATCGMSessionScale_h
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2006
//-----------------------------------------------------------------------------
//  Static class to manage Scale of CGM Container
//  Scale 1 means Resolution = 1.e-3 and ModelSize = 1.e+6
//  Scale 100 means Resolution = 1.e-1 and ModelSize = 1.e+5
//  Scale 1.e-2 means Resolution = 1.e-5 and ModelSize = 1.e+3
//-----------------------------------------------------------------------------
#include "YN000MAT.h"
#include "CATBoolean.h"
#include "CATCGMScaleCategoryDef.h"
#include "CATDataType.h"

class ExportedByYN000MAT CATCGMSessionScale
{
public:
  //=================================================================
  // DO NOT USE ANYMORE in V6
  // DO NOT USE IT in a static initialization in V5
  // Those methods are for internal CGM usage in V6
  //=================================================================
  static double GetSessionScale();
  static int    CompareScale (double iScaleToCheck, CATCGMScaleCategory iScaleCategoryRef );
  static int    IsStandardScaleSession();
  static int    IsSmallScaleSession();
  static int    IsLargeScaleSession();

  //=================================================================
  // Those methods are ODT ONLY. 
  //=================================================================
  static double     GetInternalSessionScale(CATBoolean iTryAutoScaleOnFirstData, double iScaleOnFirstData);
  static CATBoolean IsTryAutoScaleOnFirstData();
  static void       SetTryAutoScaleOnFirstData();
  static CATBoolean RiskyResetSessionScale(CATULONG32 iNbSessionScaleCalled);

private:
  static double     _SessionScale;
  static CATBoolean _TryAutoScaleOnFirstData;
  static CATULONG32 _NbSessionScaleCalls;
  static CATULONG32 _SessionScale_InitDone;
};

#endif

