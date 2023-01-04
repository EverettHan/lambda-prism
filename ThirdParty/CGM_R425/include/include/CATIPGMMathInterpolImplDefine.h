#include "CATIPGMVirtualImplDefine.h"

// ---------- CATMathInterpol

void CATCGM_ITF_IMPL_CLASS::DisableInsertion()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.DisableInsertion();
}

void CATCGM_ITF_IMPL_CLASS::SetBestParametrization(CATBoolean iEnable)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetBestParametrization(iEnable);
}

void CATCGM_ITF_IMPL_CLASS::SetTolQualityFactor(double Factor)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetTolQualityFactor(Factor);
}

void CATCGM_ITF_IMPL_CLASS::SetExactPoints(
    const CATLONG32 *iTabIndex,
    const CATLONG32 iNbIndex,
    CATLONG32 *oTabOfIndexExit)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetExactPoints(
    iTabIndex,
    iNbIndex,
    oTabOfIndexExit);
}

void CATCGM_ITF_IMPL_CLASS::SetMaxSquareSecondDeriv(double iMaxSquareSecondDeriv)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetMaxSquareSecondDeriv(iMaxSquareSecondDeriv);
}

void CATCGM_ITF_IMPL_CLASS::SetInternalMinLength(double iInternalMinLength)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetInternalMinLength(iInternalMinLength);
}

void CATCGM_ITF_IMPL_CLASS::SetSkipAll(CATBoolean iSkipAll)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetSkipAll(iSkipAll);
}

void CATCGM_ITF_IMPL_CLASS::SetCleanOutput(CATBoolean iCleanOutput)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetCleanOutput(iCleanOutput);
}

void CATCGM_ITF_IMPL_CLASS::SetPointsRemoval(CATBoolean iPointsRemoval)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetPointsRemoval(iPointsRemoval);
}

void CATCGM_ITF_IMPL_CLASS::SetMaxDepth(
    CATLONG32 iMaxDepth,
    CATLONG32 iExtraAcceptableDepth,
    double iExtraTolerance,
    CATLONG32 iStrategy,
    double iMinLength)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetMaxDepth(
    iMaxDepth,
    iExtraAcceptableDepth,
    iExtraTolerance,
    iStrategy,
    iMinLength);
}

void CATCGM_ITF_IMPL_CLASS::SetC1DiscontinuitiesDetection()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetC1DiscontinuitiesDetection();
}

void CATCGM_ITF_IMPL_CLASS::SetCutOnC1Discontinuities(double iSinAngleTol)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetCutOnC1Discontinuities(iSinAngleTol);
}

void CATCGM_ITF_IMPL_CLASS::SetCheckEnergy(CATBoolean iBool)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetCheckEnergy(iBool);
}

void CATCGM_ITF_IMPL_CLASS::SetDetectInvalidArcs(CATLONG32 iEnable, double iTolerance)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetDetectInvalidArcs(iEnable, iTolerance);
}

void CATCGM_ITF_IMPL_CLASS::SetTightenArcIntoDomain(CATLONG32 iEnable, double iTolerance)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetTightenArcIntoDomain(iEnable, iTolerance);
}

double CATCGM_ITF_IMPL_CLASS::GetMaxError()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetMaxError();
}

void CATCGM_ITF_IMPL_CLASS::ComputeMaxError(
    CATMathSetOfPointsND &iParameters,
    CATMathSetOfPointsND &iPoints,
    CATMathSetOfPointsND &iTangents,
    CATMathSetOfPointsND &iSecondDerivatives,
    CATMathSetOfPointsND *iCorrespondingParams,
    double &oMaxErr,
    double &oMaxSquareDev)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.ComputeMaxError(
    iParameters,
    iPoints,
    iTangents,
    iSecondDerivatives,
    iCorrespondingParams,
    oMaxErr,
    oMaxSquareDev);
}

int CATCGM_ITF_IMPL_CLASS::GetNbOfC1Discontinuities()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetNbOfC1Discontinuities();
}

void CATCGM_ITF_IMPL_CLASS::GetC1Discontinuities(int *ioC1Discontinuities)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetC1Discontinuities(ioC1Discontinuities);
}

void CATCGM_ITF_IMPL_CLASS::GetInvalidArcs(CATMathSetOfLongs &oIndexes)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetInvalidArcs(oIndexes);
}

void CATCGM_ITF_IMPL_CLASS::GetPiece(
    int iIndex,
    CATMathSetOfPointsND &iParameters,
    CATMathSetOfPointsND &iPoints,
    CATMathSetOfPointsND &iTangents,
    CATMathSetOfPointsND &iSecondDerivatives,
    CATMathSetOfPointsND &oParametersPiece,
    CATMathSetOfPointsND &oPointsPiece,
    CATMathSetOfPointsND &oTangentsPiece,
    CATMathSetOfPointsND &oSecondDerivativesPiece)
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.GetPiece(
    iIndex,
    iParameters,
    iPoints,
    iTangents,
    iSecondDerivatives,
    oParametersPiece,
    oPointsPiece,
    oTangentsPiece,
    oSecondDerivativesPiece);
}

CATLONG32 CATCGM_ITF_IMPL_CLASS::GetDiagnostic()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  return HandledObject.GetDiagnostic();
}

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

void CATCGM_ITF_IMPL_CLASS::SetOKScaleReviewed()
{
  CATCGM_ITF_CONCRETE_CLASS &HandledObject = (CATCGM_ITF_CONCRETE_CLASS &)_InternalData.GetHandledObject();
  HandledObject.SetOKScaleReviewed();
}

