#ifndef CATPrintSetupOrientationConstraint_H
#define CATPrintSetupOrientationConstraint_H
#include "CATGMOperatorsInterfaces.h"

#include "CATCollec.h"
#include "CATBoolean.h"
#include "CATMathTransformation.h"
#include "CATListOfDouble.h"

class ExportedByCATGMOperatorsInterfaces CATPrintSetupOrientationConstraint
{
public:
  CATPrintSetupOrientationConstraint();

#ifndef _AIX_SOURCE
  CATPrintSetupOrientationConstraint(const CATPrintSetupOrientationConstraint &);
  CATPrintSetupOrientationConstraint& operator =(const CATPrintSetupOrientationConstraint &);
  CATPrintSetupOrientationConstraint(CATPrintSetupOrientationConstraint &&);
  CATPrintSetupOrientationConstraint& operator =(CATPrintSetupOrientationConstraint &&);
  ~CATPrintSetupOrientationConstraint();
#endif

  // ===================================
  //    Fixed orientation 3D
  // ===================================
  void SetFixedOrientation();
  CATBoolean IsFreeOrientation() const;

  // ===================================
  //    Rotation2D for nesting
  // ===================================
  //ListAngle == NULL --> FreeRotation2D
  //ListAngle Empty   --> FixedRotation
  //ListAngle = {Angle1, Angle2, ...}: only Angle1, Angle2, ... are allowed. Angles are in radian for example: {CATPI, CATPIBy2}
#ifndef _AIX_SOURCE
  [[deprecated]] 
#endif
  void GetRotationList(CATListOfDouble &oListAngle, CATBoolean &oMirror) const;
#ifndef _AIX_SOURCE
  [[deprecated]]
#endif
  void SetRotationList(CATMath3x3Matrix const& iInitRotation, CATListOfDouble const* iListAngle, CATBoolean iMirror);

  // ===================================
  //    Rotation for nesting 2D
  // ===================================
  // Specify the step k of rotation 
  // Nesting operator will allow all rotation of 2pi*k/n with 0 <= k < n
  void SetRotationAngleStep(int n);
  int GetRotationAngleStep() const;

  CATBoolean IsFreeRotation2D() const;

  void SetMinTrayDistance(double);
  double GetMinTrayDistance() const;

  void SetMirror(CATBoolean iMirror);
  CATBoolean GetMirror()const;

  /**
   * Initial position of CATBody used for nesting (mostly useful for body with fixed orientation)
   */
  void SetInitialPlacement(CATMathTransformation const& iTransformation);
  CATMathTransformation const& GetInitialPlacement() const;

private:
  CATMathTransformation _InitPlacement;  
  double _MinTrayDistance;
  int _step;
  CATBoolean _FreeOrientation;
  CATBoolean _Mirror;
};

inline void CATPrintSetupOrientationConstraint::SetMinTrayDistance(double iMinTrayDistance)
{
  _MinTrayDistance = iMinTrayDistance;
}

inline double CATPrintSetupOrientationConstraint::GetMinTrayDistance() const
{
  return _MinTrayDistance;
}

inline void CATPrintSetupOrientationConstraint::SetInitialPlacement(CATMathTransformation const& iTransformation)
{
  _InitPlacement = iTransformation;
}

inline CATMathTransformation const& CATPrintSetupOrientationConstraint::GetInitialPlacement() const
{
  return _InitPlacement;
}

inline void CATPrintSetupOrientationConstraint::SetRotationAngleStep(int n)
{
  if (n >= 1)
    _step = n;
}

inline int CATPrintSetupOrientationConstraint::GetRotationAngleStep() const
{
  return _step;
}

inline void CATPrintSetupOrientationConstraint::SetMirror(CATBoolean iMirror)
{
  _Mirror = iMirror;
}

inline CATBoolean CATPrintSetupOrientationConstraint::GetMirror() const
{
  return _Mirror;
}

#endif
