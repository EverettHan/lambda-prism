// COPYRIGHT DASSAULT SYSTEMES 2003

/* CATCGMInternalTol:
 * Abstract class giving access to the internal tolerances
 * associated to a CATGeoFactory.
 */

#ifndef CATCGMInternalTol_h
#define CATCGMInternalTol_h

#include "YP00IMPL.h"                    

class ExportedByYP00IMPL CATCGMInternalTol
{
public:
  CATCGMInternalTol();
  virtual ~CATCGMInternalTol();

  virtual double GetG1UserTolerance() =0;
  virtual double GetMaxMergeTolerance() =0;
  virtual double GetEdgeCurveTransientMaxGap() =0;
};

#endif
