#include "CATDataType.h"
#include "CATMathFunctionX.h"
#include "CATMathQuinticX.h"
#include "CATMathNormal.h"

class CATSurface;
class CATMathSetOfPointsND;

class G1DeformationErrorAngleFunc : public CATMathFunctionX
{
public:
    
    G1DeformationErrorAngleFunc(CATSurface * iSupport,
                           CATMathSetOfPointsND* iParameters,
                           CATMathSetOfPointsND* iPoints,
                           CATMathSetOfPointsND* iTangent,
                           CATMathSetOfPointsND* iSecondDerivatives,
                           double iRadius,
                           CATLONG32 iArcIndex, CATLONG32 iTrackIndex, CATLONG32 iCentreIndex);

    ~G1DeformationErrorAngleFunc();

    virtual CATMathClassId IsA() const {return "G1DeformationErrorAngleFunc";}
    virtual CATMathFunctionX * Duplicate() const {return NULL;}

    virtual double Eval           (const double & iT) const;

    virtual double EvalFirstDeriv (const double & iT) const;

protected:

    CATSurface * _Support;
    CATMathNormal _Normal;
    CATMathQuinticX _TrackQuintic[2], _CentreQuintic[3];
    double _StartParam;
    double _Radius;


};


class G1DeformationErrorRadiusFunc : public CATMathFunctionX
{
public:
    
    G1DeformationErrorRadiusFunc(CATSurface * iSupport,
                           CATMathSetOfPointsND* iParameters,
                           CATMathSetOfPointsND* iPoints,
                           CATMathSetOfPointsND* iTangent,
                           CATMathSetOfPointsND* iSecondDerivatives,
                           double iRadius,
                           CATLONG32 iArcIndex, CATLONG32 iTrackIndex, CATLONG32 iCentreIndex);

    virtual CATMathClassId IsA() const {return "G1DeformationErrorRadiusFunc";}
    virtual CATMathFunctionX * Duplicate() const {return NULL;}

    virtual double Eval           (const double & iT) const;

    virtual double EvalFirstDeriv (const double & iT) const;

protected:

    CATSurface * _Support;
    CATMathQuinticX _TrackQuintic[2], _CentreQuintic[3];
    double _StartParam;
    double _Radius;
};

class G1DeformationErrorGapFunc : public CATMathFunctionX
{
public:
    
    G1DeformationErrorGapFunc(CATSurface * iSupport,
                           CATMathSetOfPointsND* iParameters,
                           CATMathSetOfPointsND* iPoints,
                           CATMathSetOfPointsND* iTangent,
                           CATMathSetOfPointsND* iSecondDerivatives,
                           CATLONG32 iArcIndex, CATLONG32 iTrackIndex, CATLONG32 iContactIndex);

    virtual CATMathClassId IsA() const {return "G1DeformationErrorGapFunc";}
    virtual CATMathFunctionX * Duplicate() const {return NULL;}

    virtual double Eval           (const double & iT) const;

    virtual double EvalFirstDeriv (const double & iT) const;

protected:

    CATSurface * _Support;
    CATMathQuinticX _TrackQuintic[2], _ContactQuintic[3];
    double _StartParam;
};
