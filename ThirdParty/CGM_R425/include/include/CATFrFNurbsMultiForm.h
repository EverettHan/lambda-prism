#ifndef CATFrFNurbsMultiForm_H
#define CATFrFNurbsMultiForm_H

// COPYRIGHT DASSAULT SYSTEMES 2009
/** @CAA2Required */
/*---------------------------------------------------------------------*/
/* DON'T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  */
/* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME */
/*---------------------------------------------------------------------*/
//
// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATFrFNurbsMultiForm:
// Inherit from CATMathNurbsMultiForm.
// Mathematical class of monoparametric NURBS.
// The CATFrFNurbsMultiForm is a set of forms (each form being equivalent to
// a monoparametric NURBS) with the same knot vector.
// It can be used for free NURBS (Dimension = 3) or for NURBS on a non specified
// support (Dimension = 2).
// This class allows working on non C2 NURBS because of its mathematical
// definition. It can also be regarded as an advanced NURBS library.
//
// For more details on Basic Operators/Constructor for NurbsMultiForm see CATMathNurbsMultiForm.h
//
// Constructors  :     - Basic Constructors
//                     - Constructor  by Concatenation of NurbsMultiForms
//                     - Constructors with NurbsCurve(s)
//                     - Constructor  with a NurbsSurface
//                     - Constructor  with a NurbsBipar
//                     - Constructor  with points and derivatives
//                     - Constructor  with equations for each arc
//
// Basic methods :     - AddForms
//                     - InvertForms
//
// Advanced methods :  - CheckContinuity
//                     - MakeContinuity
//                     - ParametricExtend
//                     - OptimiseContinuities
//                     - OptimiseDegree
//                     - ChangeKnotVector
//                     - Desextrapol
//
// Geometric methods : - InterpolToNurbsSurface
//                     - ConvertToC2NurbsCurves
//                     - ConvertToC2PNurbs
//
// Transfert methods : - Break
//                     - CATTransfertCnCurve
//                     - ContinuityCn
//                     - CreateCurve
//                     - Split
//
// Debug methods :     - VisuPoles
//
//==========================================================================
//      /97 DHN Creation
//      /98 RLA Transfert - Interfaces
// 05/04/12 NLD Smart indentation
//              Time/Space stable constructors numbering in consistency with implementation
//              Add Init(), Init09(), Init13(), Init15(), Init17(), Init25()
//              Add CATFrFNurbsMultiFormConstructor_27 (real copy constructor; old one is a fake one)
//              Add destructor
//              default values CATSqrtEpsg replaced by CATGetDefaultTolerance().LargeEpsgForLengthTest()
//              (same value in standard scale, detected by XScale dynamic check tools at other scales)
// 22/04/15 NLD Link comments from deprecated constructors to modern constructors
//              constructors reordering: deprecated ones at the end
// 28/04/15 NLD ParametricExtend() now returns a diagnostic
// 27/05/16 JSX Add a BasicOptimiseContinuities_Private Methode for basic OptimiseContinuity
//==========================================================================
#include "CATIACGMLevel.h"

#include "YP00IMPL.h"

#include "CATMathDiagnostic.h"

#include "CATMathPoint.h"
#include "CATMathSetOfPoints.h"
#include "CATMathLimits.h"

#include "CATMathNurbsMultiForm.h"
#include "CATKnotVector.h"

#include "CATCurve.h"
#include "CATNurbsCurve.h"
#include "CATPNurbs.h"
#include "CATNurbsSurface.h"
#include "CATSurLimits.h"
#include "CATCrvLimits.h"

#include "CATGeoFactory.h"

#include "CATTolerance.h"

class CATMathNurbsBipar;
class CATFrFNurbsBipar;
class CATSoftwareConfiguration;
 
// Class describing a set of forms, each form being equivalent to
// a monoparametric NURBS. All the forms have the same knot vector.
// This class can be used to describe 3D or 2D Nurbs.
// DS internal developers can use this class to manage non-C2 Nurbs but
// CAA developers are required to use the public Nurbs toolkit (CATICGMMathNurbsCurveTools.h
// and CATICGMMathNurbsSurfaceTools).
//
class ExportedByYP00IMPL CATFrFNurbsMultiForm : public CATMathNurbsMultiForm
{
  public :

    //
    //-------------------  Basic Methods -------------------
    //
    //               (Nota: CATFrFNurbsMultiFormConstructor_* is a stable numbering in implementation file,
    //                NEVER to be changed; may also be useful under XRef tool; NLD040412)
    //
    //                                                               CATFrFNurbsMultiFormConstructor_01
    /**
    * @nodoc
    * Default constructor
    */
    CATFrFNurbsMultiForm();


    //                                                               CATFrFNurbsMultiFormConstructor_19
    /**
    *  @nodoc
    *  Constructs a CATFrFNurbsMultiForm.
    *  @param iConfig
    *  The software configuration.
    *  @param iSetOfPoints
    *  The array of set of points. There is one set of points per form.
    *  @param iIsRational
    *  <b>Legal values</b>:
    *  <dl>
    *  <dt><tt>FALSE</tt><dd>if it is not rational.
    *  <dt><tt>TRUE</tt><dd>if it is rational.
    *  </dl>
    *  @param iKnotVector
    *  The knot vector for all the forms.
    *  @param iDimension
    *  The dimension. To create a "P" multiform, the dimension  must be set to 2 but the CATMathSetOfPoints in 
    *  input must be specified as set of 3D points (the third coordinate to be set to 0.)
    *  @param iNumberOfForms
    *  The number of forms.
    *  @param iweights
    *  The weight array. If each form has n control points, the weight array contains the n 
    *  weights of the first form, then the n weights of the second form, and so on...
    *  @param iTolObject
    *  The tolerance.
    */
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints      **  iSetOfPoints         ,
                          const CATLONG32                 & iIsRational          ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const double                   *  iWeights             = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_17
    //  constructor from control points and knot vector (ne plus utiliser)
    /**
    * @nodoc
    * Do not use.
    */
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iIsRational          ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const double                   *  iWeights             = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );


    //                                                               CATFrFNurbsMultiFormConstructor_15
    //  constructor (bezier form)
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iNumberOfCPsByForm   ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_09
    //  Constructor with equations for each arc
    //  --> Result is a C0 uniform multiform
    //  PolCoef is the array of the polynomial coefficients
    //  If the dimension is D, and the number of Arcs is N, and
    //  the Degree is d, PolCoef will be :
    //  (d+1) coefficients for the first dimension and for the first arc then
    //  (d+1) coefficients for the second dimension and for the first arc ...
    //  (d+1) coefficients for the Dth dimension and for the first arc then
    //  (d+1) coefficients for the first dimension and for the second arc then
    //  (d+1) coefficients for the second dimension and for the second arc ...
    //  (d+1) coefficients for the Dth dimension and for the second arc then...
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATLONG32                 & iNbArcs              ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iDegree              ,
                          const double                   *  PolCoef              ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_21
    //  constructor from a CATFrFNurbsBipar
    //  iDir=1 : direction U
    //  iDir=2 : direction V
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathNurbsBipar        *  iMathNurbsBipar      ,
                          const CATLONG32                 & iDir                 ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()

                         );

    //------------------------------------------------------------
    //  destructor
    virtual ~CATFrFNurbsMultiForm();

    //------------------------------------------------------------
    // Operator '=' (overloaded)
    CATFrFNurbsMultiForm & operator = (const CATFrFNurbsMultiForm &iNurbsMultiForm);

    //------------------------------------------------------------
    //                                                               CATFrFNurbsMultiFormConstructor_26
    //  Copy constructor (This is the old fake copy constructor; NLD050412)
    CATFrFNurbsMultiForm              (const CATMathNurbsMultiForm & ToCopy);


    //------------------------------------------------------------
    //                                                               CATFrFNurbsMultiFormConstructor_27
    //  Copy constructor (This is the real copy constructor; new one added NLD050412)
    CATFrFNurbsMultiForm              (const CATFrFNurbsMultiForm & ToCopy);


    //------------------------------------------------------------
    // AddForms (concatenation with another CATFrFNurbsMultiForm having
    // the same knot vector)
    void AddForms                     (const CATMathNurbsMultiForm &);

    //------------------------------------------------------------
    // Reverse the order of the forms
    void InvertForms();

    //
    //------------------- Advanced Constructors -------------------
    //

    //                                                               CATFrFNurbsMultiFormConstructor_07
    //
    //  Constructor from points and their derivatives.
    //  Each point is an arc limit of the multiform.
    //  Works only for degree 3 and 5. In case of degree 3, iSndDer
    //  must be a NULL pointer.
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATMathSetOfPointsND     *  iPoints              ,
                          const CATMathSetOfPointsND     *  iFstDer              ,
                          const CATMathSetOfPointsND     *  iSndDer              = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );


    //                                                               CATFrFNurbsMultiFormConstructor_11
    //  constructor from a curve and its limits 
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATCurve                 *  iCurve               ,
                          const CATCrvLimits             *  iCrvLim              = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_13
    //  constructor from a set of homogenised nurbs curves
    //  (nurbs curves with the same knot vector)
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATNurbsCurve           **  iCurve               ,
                          const CATLONG32                 & iNbOfCurves          ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_23
    //  constructor from a CATNurbsSurface and its limits 
    //  iDir=1 : direction U
    //  iDir=2 : direction V
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATLONG32                 & iDir                 ,
                          const CATNurbsSurface          *  iSurface             ,
                          const CATSurLimits             *  iSurLimits           = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_04
    //  constructor (by concatenation of n multiforms)
    //  -> the degrees are homogenized and the knot vectors are
    //     concatenated. 
    //  -> if one of the nurbs multiform to concatenate is rational,
    //     the constructed one is also rational.
    //  -> MultiForm must have the same number of forms
    //  -> It is possible to specify a tolerance for the concatenation used
    //     to check the distance between two multiforms to concatenate. If
    //     this distance is greater than the tolerance, the concatenation is
    //     impossible (error). In the other case, there can be a deformation
    //     (less than the given tolerance) in order to get C0.
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathNurbsMultiForm   **  iTabOfNurbsMultiForms,
                          const CATLONG32                 & iNbOfNurbsMultiForms ,
                                double                      Tolerance            = CATGetDefaultTolerance().LargeEpsgForLengthTest(),
                                CATLONG32                   G1Concatenation      = 0,
                          const CATTolerance & iTolObject                        = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_05
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATFrFNurbsMultiForm    **  iTabOfNurbsMultiForms,
                          const CATLONG32                 & iNbOfNurbsMultiForms ,
                                double                      Tolerance            = CATGetDefaultTolerance().LargeEpsgForLengthTest(),
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_25
    //  constructor (extract)
    CATFrFNurbsMultiForm (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathNurbsMultiForm     & iMathNurbsMultiForm  ,
                                CATLONG32                   isid                 ,
                                CATLONG32                   isens                ,
                                CATLONG32                   iExtractOrder        = 1,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //
    //------------------- Advanced Methods (NURBS Library) -------------------
    //
    // Check Continuity
    // Check if a given knot of a multiform is or could be C1 or C2 in a given
    // tolerance of deformation.
    // The method returns the computed continuity.
    //
    CATLONG32 Check_Cn   (const double                    & Tol_deform           ,
                          const CATLONG32                 & iKnotIndex           ,
                          const CATLONG32                 & iContinuity          );

    // Check Continuity
    // Check if the whole multiform is or could be C1 or C2 in a given
    // tolerance of deformation.
    // The method gives the number NCut of discontinuities (nor C1 neither C2).
    // The array oIcut gives the indices of the knots where the discontinuities
    // were found.
    //
    void  Check_Global_Cn(const double                    & Tol_deform           ,
                          const CATLONG32                 & iContinuity          ,
                                CATLONG32                 & oNcut                ,
                                CATLONG32                *& oIcut                );

    // Make Continuity
    // Check if a given knot of a multiform is or could be in a given
    // tolerance of deformation C1 or C2.
    // The method returns the computed continuity.
    //
    void   Make_Cn       (const double                    & Tol_deform           ,
                          const CATLONG32                 & iKnotIndex           ,
                          const CATLONG32                 & iContinuity          );

    // NormalReparametrisationForC1
    // This method changes the parametrisation of a C0 multiform in order
    // to make possible C1, the parametric length of the multiform also
    // becomes equivalent with its geometric length (ds/du near 1.)
    //
    void NormalReparametrisationForC1
                         (      CATLONG32                   IsAlreadyC1          = 0);

    // Optimise Continuities
    // (cf "Data Reduction Strategy for Splines" by Lyche and Morken)
    // This method optimises the multiplicities of the different knots
    // (A knot value can be removed) in the given tolerance. If OnlyCnMode
    // value is set to n>0, the computation for a given knot value will be
    // stopped when Cn continuity is reached. The user can also specify some
    // knot values with non modifiable multiplicities (Unoptimised knots).
    //
    // return ratio of deviation that has been done
    double OptimiseContinuities
                         (const double                    & iTolerance           ,
                                CATLONG32                   iOnlyCnMode          = 0,
                                CATLONG32                   iNbOfUnoptimised     = 0,
                                CATLONG32                *  iUnoptimisedKnotsIndices = NULL,
                                CATLONG32                   iMode                = 0); // iMode set to 0 for the old mode, 1 otherwise

    // Optimise Degree
    // This method optimises the degree of the multiform in the given tole-
    // rance, the output degree will be greater than or equal to the given
    // min degree.
    // The deviation is returned.
    double OptimiseDegree(const double                    & iTolerance           ,
                                CATLONG32                   iMinDegree           = 1);
  
    // Parametric Extension
    // This method extends the parametric domain of validity of the NURBS.
    // The new NURBS has the same parametrisation and oversets the old
    // geometry. The knot extremity and its new knot value are given as
    // inputs of the methods. So iKnotRank value can only be 1 or the last
    // knot number.
    //
    CATMathDiagnostic  ParametricExtend(const CATLONG32   & iKnotRank            ,
                                        const double      & iNewKnotValue        );

    // ChangeKnotVector
    // This method change the knot vector of the Nurbs while trying
    // to keep the shape of the original curve. This is done by minimizing
    // the L2 norm of the curve's derivate.
    //  WARNING : this method could lead to important deviation.
    //  ioContinuityLeft and ioContinuityRight possible values are 0,1,2.
    //  Default value is 0 which implie C0 continuity.
    //  If you impose some continuities at ends of the multiform,
    //  be aware of the number of freedom degree of your result
    //  KnotVector : NewNumberOfCPs >= ioContinuityLeft + ioContinuityRight + 2
    //  WARNING : if there is not enough freedom degree, nothing will be done.
    void ChangeKnotVector(const CATKnotVector            *  iNewKV               ,
                                CATLONG32                   iContinuityLeft      = 0,
                                CATLONG32                   iContinuityRight     = 0);

    // Desextrapol
    // If the IndexOffset is not null and the multiform is limited,
    // this method trims the multiform according to the current limits and 
    // sets the IndexOffset to null.
    // else does nothing.
    void Desextrapol     (                                                       );


    // 
    //--------------- Creation or Modification of Geometry -------------------
    // 
    // Create or modify a Nurbs Surface with a MultiForm and a KnotVector.
    // This method is based on Hermitt interpolation. Note that if a NULL
    // pointer is given for the knot vector, the parametrisation is 
    // automaticaly computed. The result is a C2 nurbs surface.
    CATNurbsSurface *InterpolToNurbsSurface
                         (      CATGeoFactory            *  iFactory             ,
                                CATKnotVector            *  iLongitudinalKV      ,
                                CATNurbsSurface          *  iNurbsSur            = NULL);

    CATNurbsSurface *InterpolToNurbsSurface
                         (      CATGeoFactory            *  iFactory             ,
                                CATKnotVector            *  iLongitudinalKV      ,
                             // double *tf,double *tl,
                                CATMathSetOfPointsND     *                       ,
                                CATNurbsSurface          *  iNurbsSur            = NULL);

    // Like the previous one but the result is a quintic nurbs
    CATNurbsSurface *QuinticInterpolToNurbsSurface
                         (      CATGeoFactory            *  iFactory             ,
                                CATMathSetOfPointsND     *& W                    ,       // Points
                                CATMathSetOfPointsND     *& T                    ,       // Tangentes
                                CATMathSetOfPointsND     *& C                    ,       // Derivée Secondes
                                CATNurbsSurface          *  iNurbsSur            = NULL,
                                int                         DimOfPoint           = 3   , // =3 (ou 4 si le poids est à interpoler)
                                int                      *  iCont                = NULL  // Continuite du vecteur nodal de la nurbs à construire
                         );
    // Modifies a curve by extrapolation of its data.
    // Warning : the equations of the curve are not computed (they are
    // not supposed to change during the extrapolation).
    void ExtrapolANurbsCurve(   CATNurbsCurve            *  NurbsToExtrapol      );

    // Modifies a PCurve by extrapolation of its data.
    // Warning : the equations of the curve are not computed (they are
    // not supposed to change during the extrapolation).
    void ExtrapolAPNurbs (      CATPNurbs                *  NurbsToExtrapol      );

    // Create a set of Nurbs Curves with a MultiForm (if just one form).
    // All the curves here created are at least C2 everywhere.
    // It is possible to define a tolerance of miinimal 3D size for
    // the geometric elements created.
    CATNurbsCurve **ConvertToC2NurbsCurves
                         (      CATGeoFactory            *  iFactory             ,
                                CATLONG32                 & oNbCurves            ,
                                double                      iTol                 = 0.0
                         );
    // Create a set of Nurbs Curves with a MultiForm
    // All the curves here created are at least C2 everywhere.
    // It is possible to define a tolerance of miinimal 3D size for
    // the geometric elements created.
    // The option of repametrisation allows to adjust the global 
    //  normal parametrisation between two consecutive non-C2 knots
    //(these portions are frequently independantly exploded )
    // iModeReparam =CatAutomaticReparameterization force the new parametrisation
    // The allocated size of oNonC2KnotIndexes  can be NbKnots -2
    // (NULL pointer if NbKnots =2)
    // The significant elements in output is for i=0 ; i<oNbCurves-1
     CATNurbsCurve **ConvertToC2NurbsCurves
                         (      CATGeoFactory            *  iFactory             ,
                                CATLONG32                 & oNbCurves            ,
                                CATLONG32                *  oNonC2KnotIndexes    ,
                          const CATParameterizationOption   iParameterizationOption = CatKeepParameterization,
                                double                      iTol                 = 0.0);

    // Create a set of PNurbs with a MultiForm (if just one form)
    // All the curves here created are at least C2 everywhere.
    // It is possible to define a tolerance of miinimal 3D size for
    // the geometric elements created.
    CATPNurbs **ConvertToC2PNurbs
                         (      CATGeoFactory            *  iFactory             ,
                                CATSurface               *                       ,
                                CATLONG32                 & oNbCurves            ,
                                double                      iTol                 = 0.0
                         );

    // Create a set of PNurbs with a MultiForm (if just one form)
    // All the curves here created are at least C2 everywhere.
    // It is possible to define a tolerance of miinimal 3D size for
    // the geometric elements created.
    // The option of repametrisation allows to adjust the global
    //  normal parametrisation between two consecutive non-C2 knots
    // (these portions are frequently independantly exploded)
    // iParameterizationOption =CatAutomaticReparameterization force the new parameterization
    // The allocated size of oNonC2KnotIndexes  can be NbKnots -2
    // (NULL pointer if NbKnots =2)
    // The significant elements in output is for i = 0; i < (oNbCurves - 1)
    CATPNurbs **ConvertToC2PNurbs
                         (      CATGeoFactory            *  iFactory             ,
                                CATSurface               *                       ,
                                CATLONG32                 & oNbCurves            ,
                                CATLONG32                *  oNonC2KnotIndexes    ,
                          const CATParameterizationOption   iParameterizationOption = CatKeepParameterization,
                                double                      iTol                 = 0.0);

    //  Cut the initial multiform into to a given continuous sub-multiform.
    //  multiformes[iF] will be the iF multiform.
    CATLONG32 ConvertToContinuousNurbsMultiFormes
                         (      CATLONG32                   expectedContinuity   ,
                                CATLONG32                 & nbContinuousMultiForms,
                                CATFrFNurbsMultiForm    **& continuousMultiforms ,
                                CATFrFNurbsBipar         *  bipar                = NULL,
                                CATLONG32                   option               = 0);
                                                              // We can no more modify this class since it has been declared CAA2 ,
                                                              // because of a nodoc method from CATLiss.
                                                              // lire au lieu de "isNearlyContinuous" l'argument "option"
                                                              // Things should change in CXR11.
                                                              // As long as we must guarante this interface stability.
                                                              // here is the way we proceed :
                                                              // - the unit number indicated the kind of continuity we expect :
                                                              //    * 0 if we want analytical continuity,
                                                              //    * 1 if we accept want to apply the "C1-MixteMode",
                                                              //    * 2 if we accept G-continuity according to numerical criteria
                                                              //    * 3 if we accept C-continuity according to numerical criteria
                                                              // - the ten-number indicates if we want to cut closed geometry.
                                                              //    * 0 if we do not cut closed geometry,
                                                              //    * 1 if we cut closed geometry.
                                                              // -----------------------------------------------------------------
                                                              // Mais non Pierre (53.1FIXPARTPRG),
                                                              // avec CAA2 non Level1 on peut faire ce qu'on veut dans la classe
                                                              //   NLD050412
                                                              // -----------------------------------------------------------------

    // rlad
    //
    //--------------- Transfert methods -------------------
    //
    // recherche rapide de discontinuites inferieures a iCont
    void      ContinuityCn
                         (      CATLONG32                 & iCont                ,
                                CATLONG32                 & oNcut                ,
                                CATLONG32                *& oIcut                );

    // decoupage de la multiforme sur noeuds avec bloc lim
    void      Break      (      CATLONG32                 & iNcut                ,
                                CATLONG32                *  iIcut                ,
                                double                    & iStartParm           ,
                                double                    & iEndParm             ,
                                CATFrFNurbsMultiForm    **  oCutcrv              ,
                          const CATTolerance              & itol                 );


    // creation d'une CATNurbsCurv a partir d'une multiforme
    void      CreateCurve(      CATGeoFactory            *  iFactory             ,
                                CATNurbsCurve            *& oCATCrv              );

    // decoupage sur les discontinuites inferieures a iCont
    void      CATTransfertCnCurve
                         (      CATGeoFactory            *  iFactory             ,
                                CATLONG32                 & iCont                ,
                                double                    & iStartPar            ,
                                double                    & iEndPar              ,
                                CATLONG32                 & oNcrv                ,
                                CATNurbsCurve           **& oCATCrv              ,
                          const CATTolerance              & itol                 );
    // rlaf


    //
    //--------------- Debug methods -------------------
    //
    // visu pour debug
    // dans les 2 dernieres methodes, au 1er appel, les variables
    // (sauf la factory!) doivent etre initialisees a 0
    void VisuPoles       (      CATGeoFactory            *  iFactory             );
    void VisuPoles       (      CATGeoFactory            *  iFactory             ,
                                CATCartesianPoint       **& VisuPt               ,
                                CATLONG32                 & NbVisuPt             );

    // Visu de tous les poles et leur liens,
    void VisuPoles       (      CATGeoFactory            *  iFactory             ,
                                CATCartesianPoint       **& ioVisuPt             ,
                                CATLONG32                 & ioNbVisuPt           ,
                                CATLine                 **& ioVisuLine           ,
                                CATLONG32                 & ioNbVisuLine         );

    //
    //------------------- Deprecated Constructors -----------------
    //
    //                                                               CATFrFNurbsMultiFormConstructor_18
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration     (CATFrFNurbsMultiFormConstructor_19)).
    */
    CATFrFNurbsMultiForm (const CATMathSetOfPoints      **  iSetOfPoints         ,
                          const CATLONG32                 & iIsRational          ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const double                   *  iWeights             = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_16
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_17)
    */
    CATFrFNurbsMultiForm (const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iIsRational          ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const double                   *  iWeights             = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );


    //                                                               CATFrFNurbsMultiFormConstructor_14
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_15)
    */
    CATFrFNurbsMultiForm (const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iNumberOfCPsByForm   ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_08
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_09)
    */
    CATFrFNurbsMultiForm (const CATLONG32                 & iNbArcs              ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iDegree              ,
                          const double                   *  PolCoef              ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                        );

    //                                                               CATFrFNurbsMultiFormConstructor_20
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_21)
    */
    CATFrFNurbsMultiForm (const CATMathNurbsBipar        *  iMathNurbsBipar      ,
                          const CATLONG32                 & iDir                 ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_06
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_07)
    */
    CATFrFNurbsMultiForm (const CATKnotVector            *  iKnotVector          ,
                          const CATMathSetOfPointsND     *  iPoints              ,
                          const CATMathSetOfPointsND     *  iFstDer              ,
                          const CATMathSetOfPointsND     *  iSndDer              = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );


    //                                                               CATFrFNurbsMultiFormConstructor_10
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_11)
    */
    CATFrFNurbsMultiForm (const CATCurve                 *  iCurve               ,
                          const CATCrvLimits             *  iCrvLim              = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_12
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_13)
    */
    CATFrFNurbsMultiForm (const CATNurbsCurve           **  iCurve               ,
                          const CATLONG32                 & iNbOfCurves          ,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_22
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_23)
    */
    CATFrFNurbsMultiForm (const CATLONG32                 & iDir                 ,
                          const CATNurbsSurface          *  iSurface             ,
                          const CATSurLimits             *  iSurLimits           = NULL,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_02
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_04)
    */
    CATFrFNurbsMultiForm (const CATMathNurbsMultiForm   **  iTabOfNurbsMultiForms,
                          const CATLONG32                 & iNbOfNurbsMultiForms ,
                                double                      Tolerance            = CATGetDefaultTolerance().LargeEpsgForLengthTest(),
                                CATLONG32                   G1Concatenation      = 0,
                          const CATTolerance & iTolObject = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_03
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_05)
    */
    CATFrFNurbsMultiForm (const CATFrFNurbsMultiForm    **  iTabOfNurbsMultiForms,
                          const CATLONG32                 & iNbOfNurbsMultiForms ,
                                double                      Tolerance            = CATGetDefaultTolerance().LargeEpsgForLengthTest(), 
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );

    //                                                               CATFrFNurbsMultiFormConstructor_24
    /**
    * @nodoc
    * Do not use (use constructor with CATSoftwareConfiguration)(see CATFrFNurbsMultiFormConstructor_25)
    */
    CATFrFNurbsMultiForm (const CATMathNurbsMultiForm     & iMathNurbsMultiForm  ,
                                CATLONG32                   isid                 ,
                                CATLONG32                   isens                ,
                                CATLONG32                   iExtractOrder        = 1,
                          const CATTolerance              & iTolObject           = CATGetDefaultTolerance()
                         );


//----POUR RAISON DE COMPATIBILITE--------------------
//----PRIERE DE MIGRER VERS LES NOUVELLES INTERFACES--
//NE PLUS UTILISER - NE PLUS UTILISER - NE PLUS UTILISER
//NE PLUS UTILISER - NE PLUS UTILISER - NE PLUS UTILISER
  // Explode
  CATFrFNurbsMultiForm **Explode
                        (const  double                   *  iBrkKnotVal          ,
                         const  CATLONG32                 & iNbOfBrkKnotVal      )
    {
     return ((CATFrFNurbsMultiForm **)(CATMathNurbsMultiForm::Explode(iBrkKnotVal,
                                                                      iNbOfBrkKnotVal)
                                      ));
    };

  private :

  void Concatenate      (const CATMathNurbsMultiForm    **  iTabOfNurbsMultiForms,
                               CATLONG32                    iNbOfNurbsMultiForms ,
                               double                       Tolerance            ,/* = CATGetDefaultTolerance().LargeEpsgForLengthTest() */
                               CATLONG32                    G1Concatenation      = 0,
                         const CATTolerance               & iTolObject           = CATGetDefaultTolerance()
                        );


  // **** Common and mandatory initialization point and breakpoint **** NLD050412
  void Init();

  void Init09            (      CATSoftwareConfiguration *  iConfig              ,
                          const CATLONG32                 & iNbArcs              ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iDegree              ,
                          const double                   *  PolCoef              ,
                          const CATTolerance              & iTolObject
                         );


  void Init13            (      CATSoftwareConfiguration *  iConfig              ,
                          const CATNurbsCurve           **  iCurve               ,
                          const CATLONG32                 & iNbOfCurves          ,
                          const CATTolerance              & iTolObject
                         );

  void Init15            (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iNumberOfCPsByForm   ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const CATTolerance              & iTolObject
                         );
  void Init17            (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathSetOfPoints       *  iSetOfPoints         ,
                          const CATLONG32                 & iIsRational          ,
                          const CATKnotVector            *  iKnotVector          ,
                          const CATLONG32                 & iDimension           ,
                          const CATLONG32                 & iNumberOfForms       ,
                          const double                   *  iWeights             ,
                          const CATTolerance              & iTolObject
                         );

  void Init25            (      CATSoftwareConfiguration *  iConfig              ,
                          const CATMathNurbsMultiForm     & iMathNurbsMultiForm  ,
                                CATLONG32                   isid                 ,
                                CATLONG32                   isens                ,
                                CATLONG32                   iExtractOrder        ,
                          const CATTolerance              & iTolObject
                         );

  // *** "Basic" mode of OptimiseContinuities. Does not use an operator  JSX240616
  double BasicOptimiseContinuities_Private
                         (const double                    & iTolerance           ,
                                CATLONG32                   iOnlyCnMode          = 0,
                                CATLONG32                   iNbOfUnoptimised     = 0,
                                CATLONG32                *  iUnoptimisedKnotsIndices = NULL,
                                CATLONG32                   iModeVersion         = 0
                         );

};

//-----------------------------------------------------------------------------
//              Ajout de CATFrFNurbsMultiFormFreeLastUnConstructedObject(). NLD190607
//              To be called in case of exception thrown in constructor
//-----------------------------------------------------------------------------
extern "C" ExportedByYP00IMPL void CATFrFNurbsMultiFormFreeLastUnConstructedObject() ;

#endif
