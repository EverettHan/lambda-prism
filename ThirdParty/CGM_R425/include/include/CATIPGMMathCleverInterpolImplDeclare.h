#include "CATIPGMMathInterpolImplDeclare.h"

  // ---------- CATMathCleverInterpol

  virtual void Run(
    CATMathSetOfPointsNDWithVectors &iSet,
    CATMathSetOfPointsND &oParameters,
    CATMathSetOfPointsND &oPoints,
    CATMathSetOfPointsND &oTangents,
    CATMathSetOfPointsND &oSecondDerivatives);

  virtual CATBoolean AddPointAtParam(
    CATLONG32 &Narc,
    double w0,
    CATMathSetOfPointsND *ioParameters,
    CATMathSetOfPointsND *ioPoints,
    CATMathSetOfPointsND *ioTangents,
    CATMathSetOfPointsND *ioSecondDerivatives,
    CATLONG32 iReconvergeDeltaParam);

/* Already defined in a parent class
  virtual void ComputeData(
    double iParam,
    double *ioP,
    double *ioT,
    double *ioC,
    int iOrientation);
*/

  virtual CATLONG32 RunSingular(
    double *P0,
    double *P1,
    CATLONG32 Liberties,
    double *T0,
    double *T1,
    double *C0,
    double *C1,
    double &delta,
    double qualitytol,
    double tol,
    short TangentConstraint);

  virtual double SingularQuality(
    double delta,
    double *P0,
    double *P1,
    double *T0,
    double *T1,
    double *C0,
    double *C1);

  virtual double ShapeQuality(
    double delta,
    double *P0,
    double *T0,
    double *C0,
    double *P1,
    double *T1,
    double *C1);

  virtual void UseSurSurWithInitsSettings();

  virtual double BorderConstraint(
    double delta,
    double *P0,
    double *P1,
    double *T0,
    double *T1,
    double *C0,
    double *C1);

  virtual double TangentConstraint(double *T0, double *T1);

  virtual void SetValidityDomain(const CATMathIntervalND *iDomain);

