/* CATEdgeCurveTransientExtrapolManager:
 *   See comments in the implementation class 
 *   CATCXEdgeCurveTransientExtrapolManager.
 */

#ifndef CATEdgeCurveTransientExtrapolManager_h
#define CATEdgeCurveTransientExtrapolManager_h

#include "YP0LOGRP.h"
#include "CATCGMOperator.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdgeCurve;
class CATBody;

class CATEdgeCurveTransientExtrapolManager
{
public:
  virtual ~CATEdgeCurveTransientExtrapolManager() {};
  virtual double GetTransientMaxGap() =0;
  virtual void RequestTransientExtrapol(CATEdgeCurve * EC, CATLONG32 & permission) =0;
  virtual void Unextrapolate() =0;
};

#endif
