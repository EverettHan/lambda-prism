#include "CATIPGMVirtualImplDeclare.h"

  // ---------- CATMathInterpol

  virtual void DisableInsertion();

  virtual void SetBestParametrization(CATBoolean iEnable);

  virtual void SetTolQualityFactor(double Factor);

  virtual void SetExactPoints(
    const CATLONG32 *iTabIndex,
    const CATLONG32 iNbIndex,
    CATLONG32 *oTabOfIndexExit);

  virtual void SetMaxSquareSecondDeriv(double iMaxSquareSecondDeriv);

  virtual void SetInternalMinLength(double iInternalMinLength);

  virtual void SetSkipAll(CATBoolean iSkipAll);

  virtual void SetCleanOutput(CATBoolean iCleanOutput);

  virtual void SetPointsRemoval(CATBoolean iPointsRemoval);

  virtual void SetMaxDepth(
    CATLONG32 iMaxDepth,
    CATLONG32 iExtraAcceptableDepth,
    double iExtraTolerance,
    CATLONG32 iStrategy,
    double iMinLength);

  virtual void SetC1DiscontinuitiesDetection();

  virtual void SetCutOnC1Discontinuities(double iSinAngleTol);

  virtual void SetCheckEnergy(CATBoolean iBool);

  virtual void SetDetectInvalidArcs(CATLONG32 iEnable, double iTolerance);

  virtual void SetTightenArcIntoDomain(CATLONG32 iEnable, double iTolerance);

  virtual double GetMaxError();

  virtual void ComputeMaxError(
    CATMathSetOfPointsND &iParameters,
    CATMathSetOfPointsND &iPoints,
    CATMathSetOfPointsND &iTangents,
    CATMathSetOfPointsND &iSecondDerivatives,
    CATMathSetOfPointsND *iCorrespondingParams,
    double &oMaxErr,
    double &oMaxSquareDev);

  virtual int GetNbOfC1Discontinuities();

  virtual void GetC1Discontinuities(int *ioC1Discontinuities);

  virtual void GetInvalidArcs(CATMathSetOfLongs &oIndexes);

  virtual void GetPiece(
    int iIndex,
    CATMathSetOfPointsND &iParameters,
    CATMathSetOfPointsND &iPoints,
    CATMathSetOfPointsND &iTangents,
    CATMathSetOfPointsND &iSecondDerivatives,
    CATMathSetOfPointsND &oParametersPiece,
    CATMathSetOfPointsND &oPointsPiece,
    CATMathSetOfPointsND &oTangentsPiece,
    CATMathSetOfPointsND &oSecondDerivativesPiece);

  virtual CATLONG32 GetDiagnostic();

  virtual void ComputeData(
    double iParam,
    double *ioP,
    double *ioT,
    double *ioC,
    int iOrientation);

  virtual void SetOKScaleReviewed();

