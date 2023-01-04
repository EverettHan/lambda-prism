#include "CATIPGMMathInterpolImplDefine.h"

// ---------- CATMathCleverInterpol

void CATCGM_ITF_IMPL_CLASS::Run(
    CATMathSetOfPointsNDWithVectors &iSet,
    CATMathSetOfPointsND &oParameters,
    CATMathSetOfPointsND &oPoints,
    CATMathSetOfPointsND &oTangents,
    CATMathSetOfPointsND &oSecondDerivatives)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.Run(
    iSet,
    oParameters,
    oPoints,
    oTangents,
    oSecondDerivatives);
}

CATBoolean CATCGM_ITF_IMPL_CLASS::AddPointAtParam(
    CATLONG32 &Narc,
    double w0,
    CATMathSetOfPointsND *ioParameters,
    CATMathSetOfPointsND *ioPoints,
    CATMathSetOfPointsND *ioTangents,
    CATMathSetOfPointsND *ioSecondDerivatives,
    CATLONG32 iReconvergeDeltaParam)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.AddPointAtParam(
    Narc,
    w0,
    ioParameters,
    ioPoints,
    ioTangents,
    ioSecondDerivatives,
    iReconvergeDeltaParam);
}

/* Already defined in a parent class
void CATCGM_ITF_IMPL_CLASS::ComputeData(
    double iParam,
    double *ioP,
    double *ioT,
    double *ioC,
    int iOrientation)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.ComputeData(
    iParam,
    ioP,
    ioT,
    ioC,
    iOrientation);
}
*/

CATLONG32 CATCGM_ITF_IMPL_CLASS::RunSingular(
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
    short TangentConstraint)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.RunSingular(
    P0,
    P1,
    Liberties,
    T0,
    T1,
    C0,
    C1,
    delta,
    qualitytol,
    tol,
    TangentConstraint);
}

double CATCGM_ITF_IMPL_CLASS::SingularQuality(
    double delta,
    double *P0,
    double *P1,
    double *T0,
    double *T1,
    double *C0,
    double *C1)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.SingularQuality(
    delta,
    P0,
    P1,
    T0,
    T1,
    C0,
    C1);
}

double CATCGM_ITF_IMPL_CLASS::ShapeQuality(
    double delta,
    double *P0,
    double *T0,
    double *C0,
    double *P1,
    double *T1,
    double *C1)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.ShapeQuality(
    delta,
    P0,
    T0,
    C0,
    P1,
    T1,
    C1);
}

void CATCGM_ITF_IMPL_CLASS::UseSurSurWithInitsSettings()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.UseSurSurWithInitsSettings();
}

double CATCGM_ITF_IMPL_CLASS::BorderConstraint(
    double delta,
    double *P0,
    double *P1,
    double *T0,
    double *T1,
    double *C0,
    double *C1)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.BorderConstraint(
    delta,
    P0,
    P1,
    T0,
    T1,
    C0,
    C1);
}

double CATCGM_ITF_IMPL_CLASS::TangentConstraint(double *T0, double *T1)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.TangentConstraint(T0, T1);
}

void CATCGM_ITF_IMPL_CLASS::SetValidityDomain(const CATMathIntervalND *iDomain)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetValidityDomain(iDomain);
}

