/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 2000
//=============================================================================
//
// CATLawUtilities: header providing global methods on CATLaw
//
//=============================================================================
//
// Usage notes:
//
//=============================================================================
//  Aug. 00 ndn   Creation                                                  ndn
// 08 01 02 MNA : Ajout de la methode CreatePiecewiseConstantLaw
// 05 04 05 JSX : Ajout Argument icont a CreatePiecewiseLinearLaw
// 07 07 05 JSX : Ajout Methode CreateCloseSplineLaw & CreateLawAcrossClosure
// 23 01 08 NLD : Ajout SetScaleOption()
// 30 01 08 NLD : Ajout GetScaleOption()
// 03 02 11 sou : argument iFullApprox in Stream()
// 18 10 13 NLD : Ajout SplitALawDefaultParameterTolerance()
// 10 10 14 NLD : Smart indent
// 16 09 21 NLD : XScale: Ajout CreateClosedSplineLawWork() pour vehiculer ScaleOption
//                via loi d'entrée
//=============================================================================

#ifndef CATLawUtilities_H
#define CATLawUtilities_H

#include "CATPGMLawUtilities.h"

#include "Y30C3XGG.h"           //#include "YP00IMPL.h"

#include "CATMathLimits.h"
#include "CATDataType.h"
#include "CATTolerance.h"

class CATLaw;
class CATGeoFactory;
class CATCompositeLaw;
class CATSplineLaw;
class CATPCurveEquation;
class CATSurface;
class CATSoftwareConfiguration;
class CATCGMStream;

class ExportedByY30C3XGG  CATLawUtilities : public CATPGMLawUtilities
{
public:
  // Constructor
                    CATLawUtilities                   (      CATGeoFactory            * iFactory   ,
                                                             CATSoftwareConfiguration * iSoftConfig);

  // DO NOT USE ANYMORE FOLLOWING CONSTRUCTOR
                    CATLawUtilities                   (      CATGeoFactory            * iFactory   );

  // Destructor
  ~CATLawUtilities ();

  // Utilities

  // Split a Law with a parameter. The output array size is 2. If the split parameter
  // correspond to the beginning (or the end) of the law, then the first (or the second) law will be NULL.
  // Global parameterization is kept.
  // iParameterTolSplit is a tolerance on law parameter to avoid split beside borders or constraint parameters
  // iParameterTolSplit should be specified by calling software in a way compatible with all factory scales,
  // and consistent with law parameterization. see SplitALawDefaultParameterTolerance()
  CATLaw         ** SplitALaw                         (      double                     iSplitParameter      ,
                                                       const CATLaw                   * iLawToSplit          ,
                                                             double                     iParameterTolSplit   = CATGetDefaultTolerance().EpsgForLengthTest());

  // Gives back default parameter tolerance to use for SplitALaw.
  // By default law parameter behaviour is given by iPowerScaleX,
  // but if a law is specified, and if its scale behaviour has been specified through
  // a previous call to SetScaleOption(), or through inheritance from a former law with specified scale behaviour,
  // then we trust and use, the parameter scale behaviour given by law
  // (see below SetScaleOption() / GetScaleOption())

  // example:
  //   use SplitALawDefaultParameterTolerance(0) for a law parameterized on fixed interval [0, 1]
  //   use SplitALawDefaultParameterTolerance(1) for a law parameterized on curve length
  double            SplitALawDefaultParameterTolerance(      CATLONG32                  iPowerScaleX         = 0    ,
                                                       const CATLaw                   * iLawToSplit          = NULL
                                                      );

  // #define CATLawUtilities_TemporaryNotXScaleCompliantSplit
  #ifdef CATLawUtilities_TemporaryNotXScaleCompliantSplit
 /** @nodoc
 * @nocgmitf
 */
  // DO NOT USE - NOT XScale compliant - Use SplitALaw with tolerance depending on law parameterization
  CATLaw         ** SplitALengthLaw                   (      double                     iSplitParameter      ,
                                                       const CATLaw                   * iLawToSplit          ); // use internal iFactory to get the scaled value of epsg;

/** @nodoc
 * @nocgmitf
 */
  // DO NOT USE - NOT XScale compliant - Use SplitALaw with tolerance depending on law parameterization
  CATLaw         ** SplitAnAngleLaw                  (      double                      iSplitParameter      ,
                                                      const CATLaw                    * iLawToSplit          ); // use internal iFactory to get the scaled value of epsg;
  #endif
 
  // Create a composite law which is linear between to parameters.
  // iCont =  0 : G0Law
  // iCont = -1 : G-1Law : NbValues = 2*iNbParam  
  CATCompositeLaw * CreatePiecewiseLinearLaw         (      CATLONG32                   iNbParam             ,
                                                      const double                    * iParameter           ,
                                                      const double                    * iValue               ,
                                                            int                         iCont                = 0 );

  // Create a composite law which is linear between to parameters.
  CATCompositeLaw * CreatePiecewiseConstantLaw       (      CATLONG32                   iNbParam             ,
                                                      const double                    * iParameter           ,
                                                      const double                    * iValue               );
  
  // Create a closed spline law without value defines at closure.
  CATSplineLaw    * CreateClosedSplineLaw            (      CATSplineLaw              * iLaw                 ,
                                                            int                         ValueAtClosure       );

  CATSplineLaw    * CreateClosedSplineLaw1           (      double                      StartEndParam     [2],
                                                            CATLONG32                   iNbParam             ,
                                                            double                    * iParameter           ,
                                                            double                    * iValue               ,
                                                            double                      iTolX                ,
                                                            double                      iTolF                );

  // Create a spline Law across a closure.  
  //  [ inputSpline Lw1 ][Domain where law is not defined.][intputSplineLaw2]
  // The closure is at the start od spline 1 and the end of spline 2
  // Value at closure can be removed
  // The output is 2 spline laws, on same domains, but representing a continous shape at closure 
  void              CreateLawAcrossClosure           (      CATLaw                    * iLaw              [2],
                                                            int                         UseValueAtClosure    ,
                                                            CATLaw                   ** oLaw                 );

  // Invert a Law.
  CATLaw          * InvertALaw                       (const CATLaw                    * iLawToInvert         );

  // Visualize a law.
  // create a Pcurve
  //  with p(w)= (w,iLaw(w)) or (iLawX(w),iLaw(w))
  CATPCurveEquation * VisualizeALaw                  (const CATLaw                    * iLaw                 ,
                                                      const CATSurface                * iSupport             ,
                                                      const CATLaw                    * iLawX                = 0);

  // Create a CompositeLaw from an array of CATLaw. Convert is exact and the definition
  // interval of the returned law is the sum of each input law interval.
  CATCompositeLaw * ConvertToCompositeLaw            (      CATLONG32                   iNbLaw               ,
                                                      const CATLaw                   ** iLawToConvert        );

  // Return a streamable law. An approximation of the law can be needed in some cases. This
  // approximation will be done within the input tolerance (law must be at least C2 piecewise).
  // The returned pointer is equal to the input law if there is no need of approximation. Else
  // it will point to the approximated law. Life-cycle of the returned law has to be handled by
  // caller.
  // If iStr==NULL then approximation of input law is always done.
  // iTol approximation tolerance
  // iFullApprox = TRUE, implies that constituent laws are approximated over complete interval [0,1]. This can avoid problems occuring
  // due to extrapolation of partially approximated law
  CATLaw         * Stream                            (const CATLaw                    * iLawToStream         ,
                                                      const CATCGMStream              * iStr                 ,
                                                            double                      iTol                 ,
                                                      const CATBoolean                  iFullApprox          = FALSE);

  // AJD: Very similar to Stream method above
  // But, This approximates the given law using CATCheapApproxFunctionXByPiecewisePol
  CATCompositeLaw* CheapApproximate                  (      CATLaw                    * iLawToApproximate    );

  // Current Limitation: the iAddLaw should be of basic type (all kind of law except CATCompositeLaw).
  // iInitialLaw can be of any type
  // iInitialLaw and iAddLaw have to share the same parametrization space
  CATLaw         * AddLaw                            (const CATLaw                    * iInitialLaw          ,
                                                      const CATLaw                    * iAddLaw              );

  // Return the square of the input law, i.e. ReturnLaw->Eval(t)= CATSqure(InitialLaw->Eval)
  CATLaw         * SquareLaw                         (const CATLaw                    * iInitialLaw          );
  
  void             DumpLaw                           (const CATLaw                    * iLaw                 );

  // Definition of law behaviour with respect to factory scale
  // iPowerScaleX : factory scale power for law parameter
  // iPowerScaleF : factory scale power for law value
  void             SetScaleOption                    (      CATLaw                    * iLaw                 ,
                                                            CATLONG32                   iPowerScaleF         ,
                                                            CATLONG32                   iPowerScaleX         ,
                                                            CATLONG32                   iReviewed            = 0) ;
  
  // Query      of law behaviour with respect to factory scale
  // returns 0 if scale attributes not previously set
  CATLONG32        GetScaleOption                    (      CATLaw                    * iLaw                 ,
                                                            CATLONG32                 & oPowerScaleF         ,
                                                            CATLONG32                 & oPowerScaleX         ,
                                                            CATLONG32                 & oReviewed            ) ;

private:
 /** @nodoc
 * @nocgmitf
 */
  CATSplineLaw    * CreateClosedSplineLawWork        (      double                      StartEndParam     [2],
                                                            CATLONG32                   iNbParam             ,
                                                            double                    * iParameter           ,
                                                            double                    * iValue               ,
                                                            // N.B iTolX and iTolF ignored if iLawForScaleOption not NULL
                                                            CATLaw                    * iLawForScaleOption   ,
                                                            double                      iTolX                ,
                                                            double                      iTolF                );

private:
  CATGeoFactory            * _Factory;
  CATSoftwareConfiguration * _SoftwareConfiguration;
};

#endif

