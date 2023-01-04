// Utility class for basic geometric operations SMT1 2016


#ifndef CATGEOUTILITY_H
#define CATGEOUTILITY_H

// Base class
#include "CATCGMVirtual.h"

// ExportedBy
#include "Y3DYNOPE.h"

#include "CATCGMOperator.h"
#include "CATCGMVirtual.h"

#include "CATSetOfCrvParams.h"
#include "CATMathFunctionX.h"
#include "CATCrvLimits.h"
#include "CATMathNormal.h"
#include "CATSurParam.h"
#include "CATMathVector.h"
#include "CATMathVector2D.h"
#include "CATMath2x2Matrix.h"


class CATSoftwareConfiguration;

class CATGeoFactory;
class CATGeometry;
class CATPoint;
class CATCurve;
class CATPCurve;
class CATSurface;
class CATInclusionPtCrv;

// ---------------------------------------------------------------------------------------------------------
class ExportedByY3DYNOPE CATGeoUtility : public CATCGMVirtual
{
public:

  // Methods to for casting to non-const
  static CATGeometry* GetAsGeometry(const CATGeometry*);
  static CATPoint* GetAsPoint(const CATPoint*);
  static CATCurve* GetAsCurve(const CATCurve*);
  static CATSurface* GetAsSurface(const CATSurface*);

  static CATGeometry* GetAsGeometryOK(const CATGeometry*); // for cases where the cast is validated OK
  static CATPoint* GetAsPointOK(const CATPoint*); // for cases where the cast is validated OK
  static CATCurve* GetAsCurveOK(const CATCurve*); // for cases where the cast is validated OK
  static CATSurface* GetAsSurfaceOK(const CATSurface*); // for cases where the cast is validated OK

  static void Lock(const CATCurve*);
  static void UnLock(const CATCurve*);
  static void Lock(const CATSurface*);
  static void UnLock(const CATSurface*);

  static const CATCurve* CATCGMNativeInterfaceImpl(const CATCurve*);
  static const CATSurface* CATCGMNativeInterfaceImpl(const CATSurface*);

  static CATGeoFactory* GetFactory(const CATGeometry* iGeom); // cast to non-const then get factory

  static void FindIndices(const CATMathSetOfLongs & iSet, CATMathSetOfLongs &ioIndices, CATLONG32 iElement);

  // Checks if iPCurve and iSurParam are defined on the same surface and uses CATInclusionPtPCrv. Returns TRUE if any solutions are found and stores them in ioParam
  static CATBoolean PCurveContainsSurParam(      CATGeoFactory            * iFactory,
                                                 CATSoftwareConfiguration * iConfig,
                                           const CATPCurve                * iPCurve,
                                           const CATSurParam              & iSurParam,
                                                 CATSetOfCrvParams        & ioParam,
                                           const CATTolerance             & iTolObject);

  static CATBoolean IsFilletTrackAndContact(const CATPCurve * iPCrv1,
                                            const CATPCurve * iPCrv2);

  static CATBoolean FindMinimalAngle(CATGeoFactory            * iFactory,
                                     CATSoftwareConfiguration * iConfig,
                                     const CATPCurve * iPCrv1,
                                     const CATCrvLimits &iLim1,
                                     const CATPCurve * iPCrv2, 
                                     const CATCrvLimits &iLim2,
                                     CATCrvParam & ioCrvPar1,
                                     CATCrvParam & ioCrvPar2);

  // S9L24102016 : Start
  //------------------------------------------------------------------------------
  // Check whether a given surface is developable or not
  //------------------------------------------------------------------------------
  static CATBoolean IsDevelopableSurface(CATGeoFactory             * ipFactory,
    CATSoftwareConfiguration  * ipConfig,
    CATSurface                * ipSurface);
  // S9L24102016 : End

private:

  static CATBoolean IsFilletTrackAndContact_Order(const CATPCurve * iPCrv1,
                                                  const CATPCurve * iPCrv2);

};

// ---------------------------------------------------------------------------------------------------------
class ExportedByY3DYNOPE CATGeoCGMReplayUtility : public CATCGMVirtual
{
public:

  static CATBoolean IsUnderCGMReplay(const CATCGMOperator * iOp);
};


class MinAngleFunc : public CATMathFunctionX
{
public:

    MinAngleFunc(CATGeoFactory            * iFactory,
                 CATSoftwareConfiguration * iConfig,
                 const CATPCurve          * iPC1,
                 const CATCrvLimits       & iLim1,
                 const CATPCurve          * iPC2,
                 const CATCrvLimits       & iLim2);

    ~MinAngleFunc();

    virtual CATMathClassId IsA() const {return "MinAngleFunc";}
    virtual CATMathFunctionX * Duplicate() const {return NULL;}

    CATBoolean IsOption(const CATMathOption iOption) const;
    virtual double Eval           (const double & iT) const;

    virtual double EvalFirstDeriv (const double & iT) const;

    void GetCrvParams(const double & iT, 
        CATCrvParam & ioCrvPar1,
        CATCrvParam & ioCrvPar2) const;

protected:

    CATGeoFactory            * _Factory;
    CATSoftwareConfiguration * _Config;
    const CATPCurve * _PC[2];
    CATSurface * _Supp[2];
    CATCrvLimits _Lim1,_Lim2;
    CATInclusionPtCrv * _Incl;
    CATMathNormal _Normal[2];
    double _Scale;
};


class TangentSpaceBaseChange
{
public:
    TangentSpaceBaseChange(      CATSurface  * iSurface,
                           const CATSurParam & iSurParam);

    void SetParam(const CATSurParam & iSurParam);

    void Convert3DToLocal2D(const CATMathVector &i3DTan, CATMathVector2D & io2DTan);
    void ConvertLocal2DTo3D(const CATMathVector2D &i2DTan, CATMathVector & io3DTan);

    void Convert3DToOrtho2D(const CATMathVector &i3DTan, CATMathVector2D & io2DTan);
    void ConvertOrtho2DTo3D(const CATMathVector2D &i2DTan, CATMathVector & io3DTan);

    void ConvertLocal2DToOrtho2D(const CATMathVector2D &i2DLocal, CATMathVector2D & io2DOrtho);
    void ConvertOrtho2DToLocal2D(const CATMathVector2D &i2DOrtho, CATMathVector2D & io2DLocal);

private:

    CATSurface * _Surface;
    CATMathVector _DU,_DV,_B[2];
    CATMath2x2Matrix _BaseChange, _InvBaseChange;

};

#endif // CATGEOUTILITY_H
