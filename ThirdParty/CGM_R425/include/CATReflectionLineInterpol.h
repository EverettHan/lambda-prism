#ifndef CATReflectionLineInterpol_h
#define CATReflectionLineInterpol_h

// COPYRIGHT DASSAULT SYSTEMES 2001
// Apr. 08 Versionning Classe mere                       P. Catel

#include "CATMathCleverInterpol.h"
#include "Y30C3XGG.h"

class CATSurface;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

class ExportedByY30C3XGG CATReflectionLineInterpol : public CATMathCleverInterpol
{
  CATCGMVirtualDeclareClass(CATReflectionLineInterpol);
public:

  CATReflectionLineInterpol(CATSoftwareConfiguration * iConfig,
                            const CATLONG32 iN,
                            CATMathImplicitSystem * iSystem,
                            const CATMathIntervalND * iDomain,
                            const double iTolerance,
                            const double iAcceptableTolerance,
                            const CATTolerance      & iTolObject = CATGetDefaultTolerance());

  virtual ~CATReflectionLineInterpol();

  void SetSurface(const CATSurface * iSurface);
  double GetSquare3DDistance(const double * iP0, const double * iP1,
                             double *& ioPosition0, double *& ioPosition1, 
                             CATBoolean iRequestData0, CATBoolean iRequestData1);

  /* 
  Modifies the way to control the quality of an arc made during interpolation :
  If Off, check if the arc satisfies the implicit system with respect to the tolerance
  If On, check if the (square of the) 3D distance between the approximated arc and the
  theoretical solution is less than the tolerance.
  Since the implicit system is homogeneous to curvatures, the first method (default one) has 
  no real sense.
  Please always call this option, with a reasonable tolerance such as Resolution * Resolution.
  */
  void Set3DQualityControl (CATBoolean iEnable=1);

protected:
  void CheckValidityOfPoint(CATMathSetOfPointsND & iSet,
                            const double * iP, double * ioT, double * ioC,
                            double iCosMin, CATBoolean & oIsSingularLeft);

  void CheckValidityOfLastPoint(const double * iP0, const double * iT0,
                                const double * iP1, double * ioT1, double * ioC1,
                                double iCosMin, CATBoolean & oIsSingularRight);

  double Quality(const double iRatio, 
                 const double iParam0, const double iParam1,
                 const double iDeltaParam, CATBoolean & ioCheckDomain);

  double QualityOpt (const double iParam0, const double iParam1,
                     const double iDeltaParam, CATBoolean & ioCheckDomain);

  void PrepareQualityOpt(const double * iP0, const double * iT0, const double * iC0,
                         const double * iP1, const double * iT1, const double * iC1,
                         const double iDeltaParam, CATBoolean iOnlyDelta);

private:

  CATReflectionLineInterpol();
  CATReflectionLineInterpol(const CATReflectionLineInterpol & iToCopy);
  void operator = (const CATReflectionLineInterpol & iToCopy);

  const CATSurface * _Surface;
  CATBoolean _Quality3D;
  
};


#endif

