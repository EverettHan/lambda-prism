#ifndef CATPrintSetupOrientationTarget_H
#define CATPrintSetupOrientationTarget_H
#include "CATGMOperatorsInterfaces.h"

#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CATNestingOptimizationTarget.h"

class ExportedByCATGMOperatorsInterfaces CATPrintSetupOrientationTarget
{
public:
  CATPrintSetupOrientationTarget();
#ifndef _AIX_SOURCE
  virtual ~CATPrintSetupOrientationTarget();
  CATPrintSetupOrientationTarget(const CATPrintSetupOrientationTarget &);
  CATPrintSetupOrientationTarget(CATPrintSetupOrientationTarget &&);
  CATPrintSetupOrientationTarget& operator=(const CATPrintSetupOrientationTarget & iToCopy);
  CATPrintSetupOrientationTarget& operator=(CATPrintSetupOrientationTarget && iToCopy);
#endif

  void SetMinimizeSupportVolume(CATAngle iMinimalAngle, CATLength iMinimalHeight = 0.);
  CATBoolean GetMinimizeSupportVolume() const;
  CATBoolean GetMinimizeSupportVolume(CATAngle & oMinimalAngle) const;
  CATBoolean GetMinimizeSupportVolume(CATAngle & oMinimalAngle, CATLength &oMinimalHeight) const;

  void SetMinimizeBoundingBoxVolume();
  CATBoolean GetMinimizeBoundingBoxVolume() const;

  void SetMinimizeSupportArea();
  CATBoolean GetMinimizeSupportArea() const;

  CATBoolean IsTarget() const;

private:

  CATBoolean _MinimizeSupportVolume;
  CATBoolean _MinimizeBoundingBoxVolume;
  CATBoolean _MinimizeSupportArea;
  CATAngle _MinimalAngle;
  CATLength _MinimalHeight;
  CATBoolean _IsTarget;

};

#endif
