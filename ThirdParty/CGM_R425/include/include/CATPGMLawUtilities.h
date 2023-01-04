#ifndef CATPGMLawUtilities_h_
#define CATPGMLawUtilities_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATMathLimits.h"
#include "CATTolerance.h"

class CATCGMStream;
class CATCompositeLaw;
class CATGeoFactory;
class CATLaw;
class CATPCurveEquation;
class CATSoftwareConfiguration;
class CATSplineLaw;
class CATSurface;

//class ExportedByYP00IMPL 
class ExportedByCATGMModelInterfaces CATPGMLawUtilities: public CATCGMVirtual
{
public:
  /**
   * Constructor
   */
  CATPGMLawUtilities();

  /**
   * Destructor
   */
  virtual ~CATPGMLawUtilities();

  //Utilities
  //Split a Law with a parameter. The output array size is 2. If the split parameter
  // correspond to the beginning (or the end) of the law, then the first (or the second) law will be NULL.
  // Global parameterization is kept.
  // iParameterTolSplit is a tolerance on law parameter to avoid split beside borders or constraint parameters
  // iParameterTolSplit should be specified by calling software in a way compatible with all factory scales,
  // and consistent with law parameterization. see SplitALawDefaultParameterTolerance()
  virtual CATLaw **SplitALaw(
    double iSplitParameter,
    const CATLaw *iLawToSplit,
    double iParameterTolSplit = CATGetDefaultTolerance().EpsgForLengthTest()) = 0;

  // Gives back default parameter tolerance to use for SplitALaw.
  // By default law parameter behaviour is given by iPowerScaleX,
  // but if a law is specified, and if its scale behaviour has been specified through
  // a previous call to SetScaleOption(), or through inheritance from a former law with specified scale behaviour,
  // then we trust and use, the parameter scale behaviour given by law
  // (see below SetScaleOption() / GetScaleOption())
  // example:
  //   use SplitALawDefaultParameterTolerance(0) for a law parameterized on fixed interval [0, 1]
  //   use SplitALawDefaultParameterTolerance(1) for a law parameterized on curve length
  virtual double SplitALawDefaultParameterTolerance(
    CATLONG32 iPowerScaleX = 0,
    const CATLaw *iLawToSplit = NULL) = 0;

  //Create a composite law which is linear between to parameters.
  //iCont =  0 : G0Law
  //iCont = -1 : G-1Law : NbValues = 2*iNbParam  
  virtual CATCompositeLaw *CreatePiecewiseLinearLaw(
    CATLONG32 iNbParam,
    const double *iParameter,
    const double *iValue,
    int iCont = 0) = 0;

  //Create a composite law which is linear between to parameters.
  virtual CATCompositeLaw *CreatePiecewiseConstantLaw(
    CATLONG32 iNbParam,
    const double *iParameter,
    const double *iValue) = 0;

  //Create a closed spline law without value defines at closure.
  virtual CATSplineLaw *CreateClosedSplineLaw(CATSplineLaw *iLaw, int ValueAtClosure) = 0;

  virtual CATSplineLaw *CreateClosedSplineLaw1(
    double StartEndParam[2],
    CATLONG32 iNbParam,
    double *iParameter,
  double *iValue,
  double TolX,
  double TolF) = 0;

  //Create a spline Law across a closure.  
  //  [ inputSpline Lw1 ][Domaine where law is not defined.][intputSplineLaw2]
  // The closure is at the start od spline 1 and the end of spline 2
  // Value at closure can be removed
  // The output is 2 spline laws, on same domaines, but represanting a continous shape at closure 
  virtual void CreateLawAcrossClosure(CATLaw* iLaw[2], int UseValueAtClosure, CATLaw **oLaw) = 0;

  //Invert a Law.
  virtual CATLaw *InvertALaw(const CATLaw *iLawToInvert) = 0;

  //Visualize a law.
  // create a Pcurve
  //  with p(w)= (w,iLaw(w)) or (iLawX(w),iLaw(w))
  virtual CATPCurveEquation *VisualizeALaw(
    const CATLaw *iLaw,
    const CATSurface *iSupport,
    const CATLaw *iLawX = 0) = 0;

  //Create a CompositeLaw from an array of CATLaw. Convert is exact and the definition
  // interval of the returned law is the sum of each input law interval.
  virtual CATCompositeLaw *ConvertToCompositeLaw(
    CATLONG32 iNbLaw,
    const CATLaw **iLawToConvert) = 0;

  //Return a streamable law. An approximation of the law can be needed in some cases. This
  //approximation will be done within the input tolerance (law must be at least C2 piecewise).
  //The returned pointer is equal to the input law if there is no need of approximation. Else
  //it will point to the approximated law. Life-cycle of the returned law has to be handled by
  //caller.
  //If iStr==NULL then approximation of input law is always done.
  //iTol approximation tolerance
  //iFullApprox = TRUE, implies that constituent laws are approximated over complete interval [0,1]. This can avoid problems occuring
  //due to extrapolation of partially approximated law
  virtual CATLaw *Stream(
    const CATLaw *iLawToStream,
    const CATCGMStream *iStr,
    double iTol,
    const CATBoolean iFullApprox = FALSE) = 0;

  // AJD: Very similar to Stream method above
  // But, This approximates the given law using CATCheapApproxFunctionXByPiecewisePol
  virtual CATCompositeLaw *CheapApproximate(CATLaw *iLawToApproximate) = 0;

  //Current Limitation: the iAddLaw should be of basic type (all kind of law except CATCompositeLaw).
  //iInitialLaw can be of any type
  //iInitialLaw and iAddLaw have to share the same parametrization space
  virtual CATLaw *AddLaw(const CATLaw *iInitialLaw, const CATLaw *iAddLaw) = 0;

  //Return the square of the input law, i.e. ReturnLaw->Eval(t)= CATSqure(InitialLaw->Eval)
  virtual CATLaw *SquareLaw(const CATLaw *iInitialLaw) = 0;

  virtual void DumpLaw(const CATLaw *iLaw) = 0;

  // Definition of law behaviour with respect to factory scale
  // iPowerScaleX : factory scale power for law parameter
  // iPowerScaleF : factory scale power for law value
  virtual void SetScaleOption(
    CATLaw *iLaw,
    CATLONG32 iPowerScaleF,
    CATLONG32 iPowerScaleX,
    CATLONG32 iReviewed = 0) = 0;

  // Query      of law behaviour with respect to factory scale
  // returns 0 if scale attributes not previously set
  virtual CATLONG32 GetScaleOption(
    CATLaw *iLaw,
    CATLONG32 &oPowerScaleF,
    CATLONG32 &oPowerScaleX,
    CATLONG32 &oReviewed) = 0;

};

//DO NOT USE ANYMORE FOLLOWING CONSTRUCTOR
ExportedByCATGMModelInterfaces CATPGMLawUtilities *CATPGMCreateLawUtilities(CATGeoFactory *iFactory);

//Constructor
ExportedByCATGMModelInterfaces CATPGMLawUtilities *CATPGMCreateLawUtilities(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iSoftConfig);

#endif /* CATPGMLawUtilities_h_ */
