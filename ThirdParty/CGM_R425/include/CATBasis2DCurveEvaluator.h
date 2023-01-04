//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
// CATBasis2DCurveEvaluator :
// Function from R to R2, thus representing a curve in 2D.
//
// Inspired from CATMathBasisFunctionX. Scale option knowns since it is the curve.
// New class instead of two mathBasisFunction for evaluation optimisation.
//=============================================================================
// 03/02/17 F1Z : Creation
// 22/08/18 JSX : Remove duplication method
// 17/07/20 JSX : add SoftwareConfiguration
// 08/10/20 Q48 : small file tidy (override etc)
// 20/11/20 Q48 : small debug method
// 09/02/21 Q48 : Add ComputeLength (default implementation)
// 09/02/21 Q48 : Add CGMReplay stream/unstream/dump
// 11/03/21 Q48 : Add ComputeAngle
// 10/09/21 Q48 : Add ComputeShifting
// 10/09/21 Q48 : Add compare methods for CGMReplay validation (migration from global Compare)
// 10/09/21 Q48 : Remove ComputeLength --> forced to be implemented in dervied classes
// 12/10/21 Q48 : Begin to remove / refactor GetCurDomain / GetMaxDomain
// 12/10/21 Q48 : Split derivative evaluations (internal methods in derived classes)
// 23/12/21 Q48 : Add constructor for default domains
// 23/12/21 Q48 : Add ComputeCenterOfCircle (for TSCST operator)
// 23/12/21 Q48 : Add Debug visualisation methods
// 23/12/21 Q48 : Add traces in Compare methods
// DD/MM/YY
//=============================================================================

#ifndef CATBasis2DCurveEvaluator_H
#define CATBasis2DCurveEvaluator_H

// Base class (GMModelInterface)
#include "CAT2DCurveEvaluator.h"

// ExportedBy
#include "GeoAdvCurves.h"

// C++11
#include "CATGeoOpVirtual.h"

// Mathematics
#include "CATSoftwareConfiguration.h"
#include "CATTolerance.h"
#include "CATMathInterval.h"
class CATMathTransformation2D;

// GMModelInterfaces
#include "CATCivilCurveDef.h"

// Temp
#include "CATCivilCurveArchiTEMP.h"

// CGMReplay
class CATCGMOutput;
class CATCGMStream;
class CATGeoODTScaleManager;
class CATCivilCurveEvaluatorImp;

// Debug
#include "CATGeoOpDebugDeclare.h"
class CATMathFunctionX;
class CATGeoFactory;
class CATGeometry;
class CATPlane;
class CATSurParam;

class ExportedByGeoAdvCurves CATBasis2DCurveEvaluator: public CAT2DCurveEvaluator
{
  //-----------------------------------------------------------------------
  //- Constructors (general case)
  //-----------------------------------------------------------------------
protected:

  CATBasis2DCurveEvaluator(      CATSoftwareConfiguration * iConfig,
                           const CATTolerance             & iTol);

  //CATBasis2DCurveEvaluator(const CATTolerance             & iTol,
  //                               CATSoftwareConfiguration * iConfig,
  //                         const double                     iStartParam,
  //                         const double                     iEndParam,
  //                         const double                     iMinParam,
  //                         const double                     iMaxParam);

  CATBasis2DCurveEvaluator(      CATSoftwareConfiguration * iConfig,
                           const CATTolerance             & iTol,
                           const CATBasis2DCurveEvaluator * iEvalForDomain);

  //-----------------------------------------------------------------------
  //- Constructors (CGM replay)
  //-----------------------------------------------------------------------

  class CATBasis2DCurveEvaluatorData; // defined later in this lass
  CATBasis2DCurveEvaluator(const CATBasis2DCurveEvaluatorData & iBaseClassData);

public:

  virtual ~CATBasis2DCurveEvaluator();

  //-----------------------------------------------------------------------
  //- Information
  //-----------------------------------------------------------------------

public:
  
  virtual CATMathClassId IsA      ()                              const CATGEOOverride;
  virtual CATBoolean     IsAKindOf(const CATMathClassId iClassId) const CATGEOOverride;

  //-----------------------------------------------------------------------
  //- Set - interface
  //-----------------------------------------------------------------------

  //virtual HRESULT SetCurDomain(const double     iStart,
  //                             const double     iEnd,
  //                             const CATBoolean iForce = FALSE) CATGEOFinal;

  virtual HRESULT SetDomain(const double     iStart,
                            const double     iEnd,
                            const CATBoolean iForce = FALSE) CATGEOFinal;

  //-----------------------------------------------------------------------
  //- Get - interface
  //-----------------------------------------------------------------------

  //virtual double GetStartParam() const CATGEOFinal;
  //virtual double GetEndParam() const CATGEOFinal;

  //virtual double GetMinParam() const CATGEOFinal;
  //virtual double GetMaxParam() const CATGEOFinal;

//#ifdef Q48_RemoveGetCurDomain
//  //virtual HRESULT GetCurDomain(double & oStart,
//  //                             double & oEnd) const CATGEOFinal;
//#else
//  virtual HRESULT GetCurDomain(double & oStart,
//                               double & oEnd) const CATGEOOverride CATGEOFinal;
//#endif

//#ifdef Q48_RemoveGetMaxDomain
//  //virtual HRESULT GetMaxDomain(double & oStart,
//  //                             double & oEnd) const CATGEOFinal;
//#else
//   virtual HRESULT GetMaxDomain(double & oStart,
//                               double & oEnd) const CATGEOOverride CATGEOFinal;
//#endif

  //virtual CATMathInterval GetCurDomain() const CATGEOFinal;

   virtual HRESULT GetDomain(double & oDomainLow,
                             double & oDomainUpp) const CATGEOOverride CATGEOFinal;

  //-----------------------------------------------------------------------
  //- Eval - Function
  //-----------------------------------------------------------------------

public:

  virtual HRESULT EvalFirstDeriv(const double iT,
                                       double oTgt[2]) const CATGEOOverride CATGEOFinal;

  virtual HRESULT EvalSecondDeriv(const double iT,
                                        double oSec[2]) const CATGEOOverride CATGEOFinal;

  virtual HRESULT EvalThirdDeriv(const double iT,
                                       double oThird[2]) const CATGEOOverride CATGEOFinal;

private:

  virtual HRESULT EvalFirstDerivInt(const double iT,
                                          double oTgt[2]) const;

  virtual HRESULT EvalSecondDerivInt(const double iT,
                                           double oSec[2]) const;

  virtual HRESULT EvalThirdDerivInt(const double iT,
                                          double oThird[2]) const;


  //-----------------------------------------------------------------------
  //- Eval - 2DCurve
  //-----------------------------------------------------------------------

public:

  virtual HRESULT EvalPoint(const double           iT,
                                  CATMathPoint2D & oPt) const CATGEOOverride CATGEOFinal;

  virtual HRESULT EvalTangent(const double            iT,
                                    CATMathVector2D & oTgt) const CATGEOOverride CATGEOFinal;

  //virtual HRESULT EvalDistortion(const double   iT,
  //                                     double & oDistortion) const /*CATGEOOverride*/;

  virtual HRESULT EvalCurvature(const double            iT,
                                      CATMathVector2D & oCurv) const CATGEOOverride CATGEOFinal;

  virtual HRESULT EvalCurvature(const double   iT,
                                      double & oCurv) const CATGEOOverride CATGEOFinal;

  virtual HRESULT EvalThirdDeriv(const double            iT,
                                       CATMathVector2D & oThirdDeriv) const CATGEOFinal;

private:

  virtual HRESULT EvalCurvatureInt(const double            iT,
                                         CATMathVector2D & oCurv) const;

  //-----------------------------------------------------------------------
  //- Utilities
  //-----------------------------------------------------------------------
  
public:

  /**
  * Compute the integral along the curve between iMin and iMax
  */
  //virtual HRESULT ComputeLength(const double   iMin,
  //                              const double   iMax,
  //                                    double & oLength) const CATGEOOverride;

  //virtual HRESULT ComputeAngle(double & oAngle) const CATGEOFinal;

  virtual HRESULT ComputeAngle(const double   iMin,
                               const double   iMax,
                                     double & oAngle) const = 0;

protected:
  
   // Seems unnecessary but this way we force the derived classes to make the choice (default or specific implementation)
   virtual HRESULT ComputeAngleDefault(const double   iMin,
                                       const double   iMax,
                                             double & oAngle) const CATGEOFinal;
   
public:

  virtual double ComputeShifting() const;
  virtual HRESULT ComputeShifting(double & oShifting) const CATGEOFinal;

  virtual HRESULT ComputeCenterOfCircle(const double           iPar,
                                        const double           iCircleRadius,
                                              CATMathPoint2D & oCircleCenter) const CATGEOFinal;

  virtual HRESULT ComputeEndCircleData(CATMathPoint2D                 & oCircleStartPoint,
                                       CATMathPoint2D                 & oCircleCenter,
                                       double                         & oCircleRadius,
                                       CATCivilInput_ClockOrientation & oCircleOrientation) const CATGEOFinal;

protected:

  virtual HRESULT ComputeCircleData(const double                           iPar,
                                          CATMathPoint2D                 & oCircleStartPoint,
                                          CATMathPoint2D                 & oCircleCenter,
                                          double                         & oCircleRadius,
                                          CATCivilInput_ClockOrientation & oCircleOrientation) const CATGEOFinal;

  //-----------------------------------------------------------------------
  //- CGM replay
  //-----------------------------------------------------------------------

public:
  
  virtual CATBoolean Compare(const CATBasis2DCurveEvaluator * iRefEval,
                                   CATCGMOutput             * iOS) const CATGEOFinal;
  
  virtual CATBoolean Compare(const CATBasis2DCurveEvaluator * iRefEval,
                             const CATMathTransformation2D  * iTransfoOut,
                             const CATMathTransformation2D  * iTransfoRef,
                                   CATCGMOutput             * iOS) const CATGEOFinal;

protected:

  virtual CATBoolean CompareDomains() const;
  virtual CATBoolean CompareInt(const CATBasis2DCurveEvaluator * iRefEval,
                                const CATMathTransformation2D  * iTransfoOut,
                                const CATMathTransformation2D  * iTransfoRef,
                                      CATCGMOutput             * iOS) const = 0;

public:

   // Dump
   static void Dump(const CATBasis2DCurveEvaluator * iEval,
                          CATCGMOutput             & iOS);
    
   // Visualisation
   virtual CATGeometry* CreateGeometry(const CATCivilCurveEvaluatorImp * iEval,
                                             CATSoftwareConfiguration  * iConfig,
                                             CATPlane                  * iPlane) const;
    
   virtual void ParameterScan(      CATGeoFactory               * iFactory,
                              const CATCivilCurveDef::ParamType   iVar1,
                              const CATCivilCurveDef::ParamType   iVar2,
                              const CATCivilCurveDef::ParamType   iVar3);
    
   // Stream
   static void Stream(const CATBasis2DCurveEvaluator * iEval, 
                            CATCGMStream             & ioStream);

   static CATBasis2DCurveEvaluator* UnStream(      CATCGMStream             & ioStream,
                                                   CATSoftwareConfiguration * iConfig,
                                             const CATTolerance             & iTol,
                                             const CATGeoODTScaleManager    * iScaleManager);

private:

  virtual void Dump(CATCGMOutput & iOS) const CATGEOFinal;
   
protected:

  virtual void DumpInt(CATCGMOutput & iOS) const = 0;

  CATBoolean ComputeLimitParams(CATPlane    * iPlane,
                                CATSurParam   oLimitPar[]) const;

  virtual void Stream(CATCGMStream & ioStream) const CATGEOFinal;
  virtual void StreamProtected(CATCGMStream & ioStream) const = 0;

  //-----------------------------------------------------------------------
  //- Data storage class to ease streaming
  //-----------------------------------------------------------------------

protected:

  class CATBasis2DCurveEvaluatorData
  {
  public:
    CATBasis2DCurveEvaluatorData(      CATSoftwareConfiguration * iConfig,
                                 const CATTolerance             & iTol,
                                 const CATGeoODTScaleManager    * iScaleManager);

    virtual ~CATBasis2DCurveEvaluatorData();

    //void SetCurDomain(const double iStartParam,
    //                  const double iEndParam);

    //void SetMaxDomain(const double iMinParam,
    //                  const double iMaxParam);

    void SetDomain(const double iDomainLow,
                   const double iDomainUpp);

    CATSoftwareConfiguration* GetConfig() const;
    const CATTolerance & GetTol() const;

    const CATGeoODTScaleManager* GetScaleManager() const;

    const CATBoolean GetIsDomainSet() const;

    //const double GetStartParam() const;
    //const double GetEndParam() const;

    //const double GetMinParam() const;
    //const double GetMaxParam() const;

    const double GetDomainLow() const;
    const double GetDomainUpp() const;

  private:
    CATSoftwareConfiguration * _Config;
    const CATTolerance & _TolObject;

    const CATGeoODTScaleManager* _ScaleManager;

    CATBoolean _IsDomainSet;

    double _DomainLow;
    double _DomainUpp;
    //double _StartParam; // the current domain
    //double _EndParam;   // the current domain

    //double _MinParam; // the max domain
    //double _MaxParam; // the max domain
  };
 
  //-----------------------------------------------------------------------
  //- Data
  //-----------------------------------------------------------------------

protected:
    
  CATSoftwareConfiguration * _Config;
  //const short _CGMLevel;

  //CATLONG32 _CGMLevel;
  const CATTolerance & _TolObject;
  
private:
  
  CATBoolean _IsDomainSet;

  //double _StartParam; // the current domain
  //double _EndParam;   // the current domain

  //const double _MinParam; // the max domain
  //const double _MaxParam; // the max domain

  double _DomainLow;
  double _DomainUpp;

private:

  // scaled finite difference steps
  const double _h1;
  const double _h2;
  const double _h3;

  //-----------------------------------------------------------------------
  //- Debug
  //-----------------------------------------------------------------------

public:

  // Useful for analysis even outside GEOPDEBUG
  virtual void CreateMathFunctionUV(CATMathFunctionX *& oFuncU,
                                    CATMathFunctionX *& oFuncV) const;
};


#endif

