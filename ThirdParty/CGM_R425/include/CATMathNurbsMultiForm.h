#ifndef CATMathNurbsMultiForm_H
#define CATMathNurbsMultiForm_H
/** @CAA2Required */
//***********************************************************************
//* DON T DIRECTLY INCLUDE THIS HEADER IN YOUR APPLICATION CODE. IT IS  *
//* REQUIRED TO BUILD CAA APPLICATIONS BUT IT MAY DISAPPEAR AT ANY TIME *
//***********************************************************************

// COPYRIGHT DASSAULT SYSTEMES 1997
//==========================================================================
//
// CATMathNurbsMultiForm:
//
// Mathematical class of monoparametric NURBS.
// The CATMathNurbsMultiForm is a set of forms (each form being equivalent to
// a monoparametric NURBS) with the same knot vector.
// It can be used for free NURBS (Dimension = 3) or for NURBS on a non specified
// support (Dimension = 2).
// This class allows working on non C2 NURBS because of its mathematical
// definition. It can also be regarded as an advanced NURBS library.
//
// Constructors  :     - Basic Constructors
//                     - Constructor by Concatenation of NurbsMultiForms
//                     - Constructor  with   NurbsCurve(s)               (see CATMathNurbsMultiFormConstructor_07)
//                     - Constructor  with a NurbsSurface                (see CATMathNurbsMultiFormConstructor_13)
//                     - Constructor  with a NurbsBipar                  (see CATMathNurbsMultiFormConstructor_11)
//                     - Constructor  with   points and derivatives      (see CATMathNurbsMultiFormConstructor_03)
//
// Basic methods :     - GetDimension
//                     - GetKnotVector
//                     - GetNumberOfCPs
//                     - GetIndexOffset
//                     - GetNumberOfCPsByForm
//                     - GetNumberOfForms
//                     - GetOneControlPoint
//                     - GetOneWeight
//                     - GetOneForm
//                     - IsRational
//                     - IsClosed
//                     - SetOneControlPoint
//                     - SetOneWeight
//                     - GetPolygonLength
//                     - SetLimits
//                     - GetLimits
//                     - GetEquations
//                     - GetMultiEquations
//                     - GetGlobalEquation
//
// Evaluators :        - Eval
//
// Advanced methods :  - ActiveSplit
//                     - DecreaseDegree
//                     - Explode
//                     - KnotInsertion
//                     - IncreaseDegree
//                     - Invert
//                     - NaturalKnotRemoval
//                     - ChangeParametricSpace
//                     - RemoveWeights
//                     - SetWeights
//                     _ ChangeKnotMultiplicities (protected)
//                     _ RemovePeriodicity

//
// Geometric methods : - ConvertToNthNurbsCurve
//                     - ConvertToNurbsCurve
//                     - ConvertToPNurbs
//                     - SetGlobalNurbsCurve
//                     - SetGlobalPNurbs
//
// Debug methods :     - Dump
//
//==========================================================================
// ??/??/?? DHN,
//          NDN,
//          DR  Creation
// ??/07/06 DR  Changements de signatures R18 pour CATTolerance
// 22/05/07 NLD _TolObject est defini hors du bloc specifique R18
//              SetTolerance()
//              On supprime l'argument iTolObject du copy constructeur
// 17/03/08 NLD On evite les methodes inline du type {instruction} dans lesquelles le debugger ne rentre pas
// 27/03/12 NLD Ajout Init(),
//              InitWithSetOfPointsND(), InitByHermiteInterpolation(), InitWithCurve(),
//              InitWithSetOfPoints(), InitWithBipar(), InitWithSurface()
// 06/04/12 NLD Ajout numérotation stable des constructeurs
// 12/04/12 NLD Ajout GetSoftwareConfiguration()
//              _TolObject et _Config ne sont plus publics
// 16/04/12 NLD Ajout SetSoftwareConfiguration()
//              afin de faciliter les cas - rares mais embetants - de création par le constructeur
//              par défaut d'un objet ensuite recopié par copy constructor, et dont la configuration
//              est transmise, et la compatibilité avec le systeme de detection des configurations
//              absentes, on rend publique cette méthode
// 05/11/12 NLD Ajout CATMathNurbsMultiFormConstructor_15 pour perfos
// 14/05/14 NLD Ajout Clear()
//              Smart indent
//              Homogeneisation des notations
// 20/07/15 NLD Ajout CATMathNurbsMultiFormDumper
// 19/05/21 SMT1 New data and methods for insertion
//              - ReduceMultiplicities()
//              - IncreaseMultiplicities()
//              - SetNewControlPoints()
//              - AllocateNewControlPoints()
//              - IncreaseDegreeViaBezierPatches()
//              - MultipleKnotInsertionViaInsertionMatrix()
//              - DoKnotInsertion()
//              - ComputeInsertionMatrixBlocks()
//              - CreateKnotInsertionMatrix()
//              - ApplyElementaryKnotInsertionMatrix()
//              - _InsertionMatrix;
//              - _CoefBufferSize, _CoefBuffer1, _CoefBuffer2
//              - _KnotBufferSize, _NewKnots, _MultBuffer, _NewMultBuffer
//              - _MaxNbCP, _CpArray1, _CpArray2, _CpBuffer
//              - _WorkMult
//==========================================================================
#include "CATIACGMLevel.h"
#include "YP00IMPL.h"

#include "CATDataType.h"
#include "CATTolerance.h"

#include "CATMathPoint.h"
#include "CATMathSetOfPoints.h"
#include "CATMathSetOfVectors.h"

#include "CATKnotVector.h"

#include "CATCGMVirtual.h"

#include "CATCurve.h"
#include "CATNurbsCurve.h"
#include "CATPNurbs.h"
#include "CATNurbsSurface.h"
#include "CATSurLimits.h"
#include "CATCrvLimits.h"
#include "CATGeoFactory.h"

#include "CATParameterizationOption.h"


class CATMathNurbsBipar;
class CATMathPolynomX;
class CATMathFunctionX;
class CATMathNxNBandSymMatrix;
class CATMathMxNMatrix;
class CATMathMxNBandMatrix;
class CATMathSparseMxNMatrix;
class CATSoftwareConfiguration;
class CATMathNurbsMultiFormSpecialImpl;

//-----------------------------------------------------------------------------
class ExportedByYP00IMPL CATMathNurbsMultiForm : public CATCGMVirtual
{
  friend class CATMathNurbsMultiFormSpecialImpl;
  friend class CATMathNurbsMultiFormDumper;

  public :

    //
    //-------------------  Basic Constructors -------------------
    //
    //  default constructor
    //               (Nota: CATMathNurbsMultiFormConstructor_* is a stable numbering in implementation file,
    //                NEVER to be changed; may also be useful under XRef tools; NLD060412)
    //
    //                                                               CATMathNurbsMultiFormConstructor_01
    //  default constructor
    //  (call should be replaced by a constructor with full data definition or at least by CATMathNurbsMultiFormConstructor_15) 
    CATMathNurbsMultiForm(
                         );

    //  enhanced (and fake) default constructor
    //                                                               CATMathNurbsMultiFormConstructor_15
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATTolerance              & iTolObject         
                         );

    //  Constructor with attributes
    //  -> One set of points by form. Note that if we want to create a "P"
    //     multiform, the dimension is set to 2 but the CATMathSetOfPoints in
    //     input are 3D (the third coordinate is set to 0.)
    //  -> If each form has n control points, the weights array contains the n
    //     weights of the first form, then the n weights of the second form,
    //     and so on...
    //Do not use
    //                                                               CATMathNurbsMultiFormConstructor_09
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATMathSetOfPoints      **  iSetOfPoints       ,
                          const CATLONG32                 & iIsRational        ,
                          const CATKnotVector            *  iKnotVector        ,
                          const CATLONG32                 & iDimension         ,
                          const CATLONG32                 & iNumberOfForms     ,
                          const double                   *  iWeights           = NULL ,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    //  constructor from a CATMathNurbsBipar
    //  iDir=1 : direction U
    //  iDir=2 : direction V
    //                                                               CATMathNurbsMultiFormConstructor_11
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATMathNurbsBipar        *  iMathNurbsBipar    ,
                          const CATLONG32                 & iDir               ,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                          );
    //  destructor
    virtual ~CATMathNurbsMultiForm();

    // Operator '=' (overloaded) 
    virtual CATMathNurbsMultiForm& operator = (const CATMathNurbsMultiForm &iNurbsMultiForm);

    //
    //------------------- Advanced Constructors -------------------
    //
    //  Constructor from points and their derivatives.
    //  Each point is an arc limit of the multiform.
    //  Works only for degree 3 and 5. In case of degree 3, iSndDer
    //  must be a NULL pointer.
    //  OptimiseContinuity : 0 means results will have a C0 nodal vector (but C2 mathematicaly and faster).
    //                                                               CATMathNurbsMultiFormConstructor_03
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATKnotVector            *  iKnotVector        ,
                          const CATMathSetOfPointsND     *  iPoints            ,
                          const CATMathSetOfPointsND     *  iFstDer            ,
                          const CATMathSetOfPointsND     *  iSndDer            = NULL,
                                CATLONG32                   OptimiseContinuity = 1,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    //  Hermite Interpolation.
    //  Constructor from points and eventually derivatives at the two
    //  extremities (if CATMathSetOfPointsNDTwoTangents).
    //  Each point is an arc limit of the multiform.
    //  The result is a cubic multiform. The dimension will be 3 and
    //  the number of forms will be the dimension of the set of points
    //  divided by 3.
    //  It is possible to impose a parameter for each point of the set.
    //                                                               CATMathNurbsMultiFormConstructor_05
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATMathSetOfPointsND     *  iPoints            ,
                          const double                   *  iParameters        = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );


    //  constructor from a curve and its limits
    //                                                               CATMathNurbsMultiFormConstructor_07
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATCurve                 *  iCurve             ,
                          const CATCrvLimits             *  iCrvLim            = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    //  constructor from a CATNurbsSurface and its limits 
    //  iDir=1 : direction U
    //  iDir=2 : direction V
    //                                                               CATMathNurbsMultiFormConstructor_13
    CATMathNurbsMultiForm(      CATSoftwareConfiguration *  iConfig            ,
                          const CATLONG32                 & iDir               ,
                          const CATNurbsSurface          *  iSurface           ,
                          const CATSurLimits             *  iSurLimits         = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    //
    //-------------------  Deprecated Constructors (DO NOT USE) -------------------
    //
    // Do not use (use constructor CATMathNurbsMultiFormConstructor_09 with CATSoftwareConfiguration)
    //                                                               CATMathNurbsMultiFormConstructor_08
    CATMathNurbsMultiForm(const CATMathSetOfPoints      **  iSetOfPoints       ,
                          const CATLONG32                 & iIsRational        ,
                          const CATKnotVector            *  iKnotVector        ,
                          const CATLONG32                 & iDimension         ,
                          const CATLONG32                 & iNumberOfForms     ,
                          const double                   *  iWeights           = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                          )  ;

    // Do not use (use constructor CATMathNurbsMultiFormConstructor_11 with CATSoftwareConfiguration)
    //                                                               CATMathNurbsMultiFormConstructor_10
    CATMathNurbsMultiForm(const CATMathNurbsBipar        *  iMathNurbsBipar    ,
                          const CATLONG32                 & iDir               ,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()

                          );

    // Do not use
    //                                                               CATMathNurbsMultiFormConstructor_14
    CATMathNurbsMultiForm(const CATMathNurbsMultiForm     & iMathNurbsMultiForm
                         );

    // Do not use (use constructor CATMathNurbsMultiFormConstructor_03 with CATSoftwareConfiguration)
    //
    //                                                               CATMathNurbsMultiFormConstructor_02
    CATMathNurbsMultiForm(const CATKnotVector            *  iKnotVector        ,
                          const CATMathSetOfPointsND     *  iPoints            ,
                          const CATMathSetOfPointsND     *  iFstDer            ,
                          const CATMathSetOfPointsND     *  iSndDer            = NULL,
                                CATLONG32                   OptimiseContinuity = 1,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    // Do not use (use constructor CATMathNurbsMultiFormConstructor_05 with CATSoftwareConfiguration)
    //                                                               CATMathNurbsMultiFormConstructor_04
    CATMathNurbsMultiForm(const CATMathSetOfPointsND     *  iPoints            ,
                          const double                   *  iParameters        = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );


    // Do not use (use constructor CATMathNurbsMultiFormConstructor_07 with CATSoftwareConfiguration)
    //                                                               CATMathNurbsMultiFormConstructor_06
    CATMathNurbsMultiForm(const CATCurve                 *  iCurve             ,
                          const CATCrvLimits             *  iCrvLim            = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    // Do not use (use constructor CATMathNurbsMultiFormConstructor_13 with CATSoftwareConfiguration)
    //                                                               CATMathNurbsMultiFormConstructor_12
    CATMathNurbsMultiForm(const CATLONG32                 & iDir               ,
                          const CATNurbsSurface          *  iSurface           ,
                          const CATSurLimits             *  iSurLimits         = NULL,
                          const CATTolerance              & iTolObject         = CATGetDefaultTolerance()
                         );

    //
    //-------------------  Basic Methods ------------------- 
    //

    //
    //-------------- Evaluators ------------------- 
    //
    virtual void Eval                                          (const double                    & iLocalParam        ,
                                                                const CATLONG32                 & iArcRank           ,
                                                                const CATCrvEvalCommand         & iCommand           ,
                                                                      CATMathPoint             *  oPoint             ,
                                                                      CATMathVector            *  oFirstDeriv        = NULL,
                                                                      CATMathVector            *  oSecondDeriv       = NULL) const;

    virtual void Eval                                          (const double                    & iLocalParam        ,
                                                                const CATLONG32                 & iArcRank           ,
                                                                const CATLONG32                 & iFormRank          ,
                                                                const CATCrvEvalCommand         & iCommand           ,
                                                                      CATMathPoint             *  oPoint             ,
                                                                      CATMathVector            *  oFirstDeriv        = NULL,
                                                                      CATMathVector            *  oSecondDeriv       = NULL) const;

    virtual void                       Eval                    (const double                    & iLocalParam        ,
                                                                const CATLONG32                 & iArcRank           ,
                                                                const CATCrvEvalCommand         & iCommand           ,
                                                                      double                   *  oPoint             ,
                                                                      double                   *  oFirstDeriv        = NULL,
                                                                      double                   *  oSecondDeriv       = NULL) const;

    virtual void                       Eval                    (const double                    & iLocalParam        ,
                                                                const CATLONG32                 & iArcRank           ,
                                                                const CATLONG32                 & iFormRank          ,
                                                                const CATCrvEvalCommand         & iCommand           ,
                                                                      double                   *  oPoint             ,
                                                                      double                   *  oFirstDeriv        = NULL,
                                                                      double                   *  oSecondDeriv       = NULL) const;

    virtual void                       EvalND                  (const double                    & iLocalParam        ,
                                                                const CATLONG32                 & iArcRank           ,
                                                                const CATCrvEvalCommand         & iCommand           ,
                                                                      double                   *  ioPoint            ,
                                                                      double                   *  ioFirstDeriv       = NULL,
                                                                      double                   *  ioSecondDeriv      = NULL) const;
//==========================================================================
// GetGlobal equation  for one Form (0<=iFormIndex<_NumberOfForms)
//
//===================================================================
    virtual void                       GetGlobalEquation        (const CATLONG32                  iFormIndex         ,
                                                                       CATMathFunctionX        *& oFx                ,
                                                                       CATMathFunctionX        *& oFy                ,
                                                                       CATMathFunctionX        *& oFz                )       const;

// To get the equations of the MultiForm for one form (0 <= iNbForm <_NumberOfForms)
    virtual void                       GetEquations             (      CATLONG32                  iFormIndex         ,
                                                                       CATMathPolynomX        **  Fx                 ,
                                                                       CATMathPolynomX        **  Fy                 ,
                                                                       CATMathPolynomX        **  Fz                 ,
                                                                       CATMathPolynomX        **  Fw                 = NULL) const;

// To get the equations of the MultiForm for all the form.
// To use this method for a for a CATFrFMultiform Multi:
//    1/ CATLONG32 Nbarcs = (Multi.GetKnotVector())->GetNumberOfArcs();
//    2/ CATLONG32 NumberOfForms = (Multi.GetNumberOfForms())
//    3/ For each CATMathPolynomX **Fx,....,**Fw ,
//       Fx(yz or w) = new CATMathPolynomX *[NumberOfForms*NbArcs];
//    Then : Multi.GetMultiEquations (Fx, Fy, Fz, Fw);
//    gives in output NumberOfForms*Nbarcs CATMathPolynomX as follows:
//
//    Fx[0],...........,Fx[Nbarcs-1],Fx[Nbarcs],....Fx[Nbarcs +Nbarcs-1],
//    <----------------------------> <---------------------------------->
//            First Form                     Second Form
//    ....................................................................
//    Fx[Nbarcs*(NumberOfForm-1)],.....,Fx[Nbarcs*NumberOfForm-1)]
//    <------------------------------------------------------------>
//                          Last Form

    virtual void                       GetMultiEquations        (      CATMathPolynomX        **  Fx                 ,
                                                                       CATMathPolynomX        **  Fy                 ,
                                                                       CATMathPolynomX        **  Fz                 ,
                                                                       CATMathPolynomX        **  Fw                 = NULL) const;

    // Compute the length of the polygon made of the control points
    // (eventualy between two global parameters)
    virtual double                     GetPolygonLength         (                                                    )       const;

    virtual double                     Get3DPolygonLength       (      double                     Start              ,
                                                                       double                     End                ,
                                                                       CATSurface              *  Support            = NULL) const;

    // Is the MultiForm closed (regarding to the given tolerance) ?
    virtual CATLONG32                  IsClosed                 (const double                   & iTolerance         )       const;
    //
    //------------------- Data Access Methods -------------------
            CATSoftwareConfiguration * GetSoftwareConfiguration ()                                                           const
      {
       return _Config;
      };
    //
    // Is the MultiForm rational ?  // 0 -> no , 1 -> yes
    virtual CATLONG32                  IsRational               ()                                                           const
      {
       return _IsRational;
      };

    // Get the dimension of the MultiForm : 2 for  P-MultiForm
    //                                      3 for 3D-MultiForm
    virtual CATLONG32                  GetDimension             ()                                                           const
      {
       return _Dimension;
      };

    // Read the number of control points
    virtual CATLONG32                  GetNumberOfCPs           ()                                                           const
      {
       return (_NumberOfForms*(_KnotVector->GetNumberOfControlPoints()));
      };

    // Read the number of control points per form
    virtual CATLONG32                  GetNumberOfCPsByForm     ()                                                           const
      {
       return (_KnotVector->GetNumberOfControlPoints());
      };

    // Read the number of forms
    virtual CATLONG32                  GetNumberOfForms         ()                                                           const
      {
       return _NumberOfForms;
      };

    // ----- Read one form  ----------
    // The result is a multiform with only one form.
    virtual CATMathNurbsMultiForm    * GetOneForm               (      CATLONG32                  iFormIndex         )       const;

    // Read the control points
    virtual CATMathPoint             * GetControlPoints         ()                                                           const
      {
       return _tabOfCPs;
      };
  
    virtual CATMathPoint               GetOneControlPoint       (      CATLONG32                  iRankOfPoint       ,
                                                                       CATLONG32                  iRankOfForm        )       const
      {
       return _tabOfCPs[iRankOfForm - 1 + _NumberOfForms*(iRankOfPoint-1)];
      };

    // Read the knot vector
    virtual CATKnotVector            * GetKnotVector            ()                                                           const
      {
       return _KnotVector;
      };
  
    virtual CATLONG32                  GetIndexOffset           ()                                                           const
      {
       return _Offset;
      };

    // Read the weights (if the multiform is rational)
    virtual double                   * GetWeights               ()                                                           const
      {
       double * Weights = NULL;
       if (_IsRational)
          Weights = _Weights;
       return Weights;
      };

    virtual double                     GetOneWeight             (      CATLONG32                   iRankOfPoint      ,
                                                                       CATLONG32                   iRankOfForm       )       const
      {
       double Weight = 0.0;
       if (_IsRational)
           Weight = _Weights[iRankOfForm - 1 + _NumberOfForms*(iRankOfPoint-1)];
       return Weight;
      };

    virtual void                       GetLimits                (      double                    & oStart            ,
                                                                       double                    & oEnd              )       const
      {
       oStart = oEnd = 0.0;
       if (_IsLimited)
         {
          oStart = _Start;
          oEnd = _End;
         }
       else
         {
          const double * Knots = NULL;
          _KnotVector->GetKnots(Knots);
          CATLONG32 NbKnots = _KnotVector->GetNumberOfKnots();
          if (Knots)
            {
             oStart = Knots[0];
             oEnd   = Knots[NbKnots-1];
            }
         }
      };

    virtual CATLONG32                  IsLimited                ()                                                           const
      {
       return _IsLimited;
      };

    //
    //-------------- Data Modification Methods -------------------
    //
    //  Set : modification of an existing CATMathNurbsMultiForm
    //  The arrays of Control Points and Weights have to be stored
    //  in this way :
    //  iPoints[0] = Form[0]ControlPoint[0],
    //  iPoints[1] = Form[1]ControlPoint[0],...,
    //  iPoints[i+j*iNumberOfForms] = Form[i]ControlPoint[j] , ...

    virtual void                       Set                      (const CATMathPoint             *  iPoints           ,
                                                                 const CATLONG32                 & iIsRational       ,
                                                                 const CATKnotVector            *  iKnotVector       ,
                                                                 const CATLONG32                 & iDimension        ,
                                                                 const CATLONG32                 & iNumberOfForms    ,
                                                                 const double                   *  iWeights          ,
                                                                 const CATTolerance             *  iTolObject        = &CATGetDefaultTolerance()
                                                                );

    virtual void                       SetLimits                (const double                    & Start             ,
                                                                 const double                    & End               )
      {
       _IsLimited = 1;
       _Start     = Start;
       _End       = End;
      };
 
    virtual void                       SetIndexOffset           (const CATLONG32                 & iNewOffset        )
      {
       _Offset = iNewOffset;
      };

    virtual void                       SetOneControlPoint       (const CATLONG32                 & iRankOfPoint      ,
                                                                 const CATLONG32                 & iRankOfForm       ,
                                                                 const CATMathPoint              & pt                )
      {
       _tabOfCPs[iRankOfForm - 1 + _NumberOfForms*(iRankOfPoint-1)] = pt;
      };

    virtual void                       SetOneWeight             (const CATLONG32                 & iRankOfPoint      ,
                                                                 const CATLONG32                 & iRankOfForm       ,
                                                                 const double                    & iWeight           )
      {
       _Weights[iRankOfForm - 1 + _NumberOfForms*(iRankOfPoint-1)] = iWeight;
      };


    //
    //------------------- Advanced Methods (NURBS Library) -------------------
    //
    // Reverse the orientation of the multiform
    virtual void                       Invert                   ();

    // Increase the degree (general case)
    virtual void                       IncreaseDegree           (const CATLONG32                 & iDeltaDegree      );

    // Increase the degree (special case when current degree is 1, and only 2 knots, and not rational case)
    virtual void                       IncreaseDegreeFromOne    (      CATLONG32                   iDeltaDegree      );

    // Decrease the degree
    // WARNING : This method can lead to important deviation.
    //           ioContinuityLeft and ioContinuityLeft = 0,1,2
    // iContinuity* is the continuity you want to keep at the end.
    // Left is the beginning (in parameter), Right the end.
    // IF THERE ISN'T ENOUGH FREEDOM DEGREE, NOTHING IS DONE.
    virtual void                       DecreaseDegree           (const CATLONG32                 & iDeltaDegree      ,
                                                                       CATLONG32                   iContinuityLeft   = 0,
                                                                       CATLONG32                   iContinuityRight  = 0);

    // Modify the degree
    // WARNING : if the new degree is smaller than the current degree, this
    //           method can lead to important deviation.
    // iContinuity* is the continuity you want to keep at the end.
    // Usefull only if you want to decrease the degree.
    // Left is the beginning (in parameter), Right the end.
    // IF THERE ISN'T ENOUGH FREEDOM DEGREE, NOTHING IS DONE.
    virtual void                       SetDegree                (const CATLONG32                 & NewDegree         ,
                                                                       CATLONG32                   iContinuityLeft   = 0,
                                                                       CATLONG32                   iContinuityRight  = 0);

    // Remove a knot.
    // If the delta of multiplicity is equal to the multiplicity of
    // the specified knot value, this one is suppressed from the knot
    // vector.
    //
    virtual void                       NaturalKnotRemoval       (const double                    & iKnotValue        ,
                                                                 const CATLONG32                 & DeltaMultiplicity );

    // Insert a Knot
    // If the knot value already exists in the knot vector, its multiplicity
    // is increased until the specified multiplicity.
    // Note that the CATEpsg tolerance is used in order to test the equality
    // of two knot values.
    // if iTolKnotConfusion is specified as a positive value,
    // an error is thrown if the knot insertion introduces a arc that is
    // parametrically shorter than this tolerance.
    virtual void                       KnotInsertion            (const double                    & iKnotValue        ,
                                                                 const CATLONG32                 & Multiplicity      ,
                                                                       double                      iTolKnotConfusion = 0.);
    // New 17.5.21 SMT1 Not widely used yet
    // KnotRemoval method using the KnotInsertionMatrix M and least squares to solve Min(M * c_new-c_old) on the control points.
    // Doesn't introduce numerical noise for control points that are known to be unchanged.
    // PseudoInverse of IncreaseMultiplicities. Seems to produce significantly different result from existing methods.
            void                       ReduceMultiplicities       (const CATULONG32                 * DeltaMultiplicity );

    // New 17.5.21 SMT1 Not widely used yet
    // KnotRemoval method using the KnotInsertionMatrix M to compute M * c_old=c_new for the control points.
    // Doesn't introduce numerical noise for control points that are known to be unchanged.
    // Numerically different, but conceptally identical result to existing methods.
            void                       IncreaseMultiplicities       (const CATULONG32               * DeltaMultiplicity ); 
    
    // Active Split  (break)
    // The user specifies a couple of knot values. The multiform
    // is splitted with a new parametrisation beginning at the first
    // knot value and ending at the second. The algorithm is based
    // on knot insertion.
    // if iTolKnotConfusion is specified as a positive value,
    // an error is thrown if the split introduces a arc that is
    // parametrically shorter than this tolerance.
    virtual void                       ActiveSplit              (const double                   *  iLimitsKnotValues ,
                                                                       double                      iTolKnotConfusion = 0.0);

    // Explode  (multiple break)
    // The multiform is exploded into n new multiforms, the user specifies
    // the (n-1) knot values where the original multiform is to be broken.
    // The knot values must be given in the increasing parameter order.
    // The new multiforms are returned via an array of multiforms. The algorithm
    // is based on knot insertion.
    //

    // Mise en format non periodique de la Nurbs
            void                       RemovePeriodicity        ();

    // Relimitation element geometrique equivalent
            void                       Relimit                  (      CATCurve                 *  MyNurbs           );

            CATMathNurbsMultiForm   ** Explode                  (const double                   *  iBreakKnotValues  ,
                                                                 const CATLONG32                 & iNumberOfBreakKnotValues);


    // Change Parametric Space
    // This method changes the knot values of the multiform by
    // affine transformation. The form is not changed. The new knot vector
    // of the multiform will begin at the new first knot value (given as
    // an input) and end at the new last one (also given as an input).
    //
    virtual void                       ChangeParametricSpace    (const double                    & iNewFirstKnotValue,
                                                                 const double                    & iNewLastKnotValue );

    // RemoveWeights
    // This method removes the weigths of the multiform
    // if iCheckWeights=0, this method removes the weigths of the multiform
    // if iCheckWeights=1, this method checks if all the weights are the same
    // before removing the weigths of the multiform. If all the weights are not
    // the same this method does nothing and returns 1
    // Returns 0 if the weigths are removed.
            int                        RemoveWeights            (      int                         iCheckWeights     = 0);

    // SetWeights
    // This method adds weigths to a non rational multiform
    // For a rational multiform, this method changes the weigths
    // if iWeights=NULL the weigths are equal to 1.
            void                       SetWeights               (      double                   *  iWeights          = NULL);


    //
    //--------------- Creation or Modification of Geometry -------------------
    //
    // Create a Nurbs Curve with a MultiForm (if just one form)
    virtual CATNurbsCurve            * ConvertToNurbsCurve      (      CATGeoFactory            *                    );

    // Create a Nurbs Curve with the nth form of the MultiForm
    virtual CATNurbsCurve            * ConvertToNthNurbsCurve   (      CATGeoFactory            *                    ,
                                                                       int                         iFormIndex        );

    // Modify an existing Nurbs Curve with a MultiForm
    // By default, the parameterization of the NURBS is modified to better
    // fit internal criteria. CatKeepParameterization will keep the original
    // parametrization.
    virtual void                       SetGlobalNurbsCurve      (      CATNurbsCurve            *  MyNurbs            ,
                                                                       CATParameterizationOption   iParameterizationOption = CatAutomaticParameterization);

    // Create a PNurbs with a MultiForm
    virtual CATPNurbs             *    ConvertToPNurbs          (      CATGeoFactory            *                     ,
                                                                       CATSurface               *                     );

    // Modify an existing PNurbs with a MultiForm
    // By default, the parameterization of the NURBS is modified to better
    // fit internal criteria. CatKeepParameterization will keep the original
    // parametrization.
    virtual void                       SetGlobalPNurbs          (      CATPNurbs                *  MyNurbs            ,
                                                                       CATParameterizationOption   iParameterizationOption = CatAutomaticParameterization);

    //--------------- Internal  methods -------------------
    // Insert many Knots
    // If one of the knot values already exists in the knot vector,
    // its multiplicity increases until the specified multiplicity.
    // Note that the CATEpsg tolerance is used in order to test the equality
    // of two knot values.
    // Using the default value iTolKnotConfusion, we do not change the behaviour of this software.
    // Using it, it will consider is as the confusion tolerance with an existing knot :
    //        if there already exists a knot within this tolerance, we will throw an error.
    // If iTolKnotConfusion is specified as a positive value,
    // an error is thrown if the knot insertions introduces a arc that is
    // parametrically shorter than this tolerance.
    //
    virtual void                       MultipleKnotInsertion    (const double                   *  iKnotValues        ,
                                                                 const CATLONG32                *  iMultiplicities    ,
                                                                 const CATLONG32                 & iNbOfInsertions    ,
                                                                 double                            iTolKnotConfusion  = 0.0);

    //--------------- Debug methods -------------------
    // 
    // dump pour debug
    virtual void                       Dump                     ();


    // Method that checks if a bipare is rational or not.
    // It returns 0 if no error has occured during the analysis.
    // The diagnostic equals :
    //    - 0 if the nurbs is not built as rational (_IsRational==0)
    //    - a positive value otherwise :
    //            1 if the weights are all the same
    //            2 if the weights are the same in U (not rational in u)
    //            3 if the weights are the same in V (not rational in v)
    //            4 if the weights are different in both directions
            CATLONG32                  CheckRationality         (      CATLONG32                 & diagnostic         );

    // methode qui permet d'avoir le bloc d'encombrement d'un arc de multiforme
    // rend 0 si le traitement se passe correctement
    // iNumPatchU commence a 1
    // iTolerance est le gras a ajouter a la boite d'encombrement
    // l'argument makeMeasureOnC0Geom permet s'il est value a 1, d'inserer
    // des noeuds C0 sur la MF et d'avoir ainsi une mesure plus precise du
    // bloc d'encombrement (traitement plus cher en CPU si MultiForm non C0, duplication de la MultiForm et
    // insertion de noeud).
    //  Demander une evolution si utilisation massive (centraliser ce service dans une
    //  classe afin d'optimiser les perfos (KnotInsersions massives))
    virtual CATLONG32                  ArcBox                   (      CATLONG32                   iNumArc             ,
                                                                       double                      iTolerance          ,
                                                                       CATMathBox                & box                 ,
                                                                       CATLONG32                   makeMeasureOnC0Geom = 0);

    // Calcul de la boite d'encombrement sur l'ensemble de la multiforme.
    // La courbe est forcement dans le volume d'encombrement des points de controle
    virtual CATLONG32                  ComputeMFMaxBox          (      double                      iTolerance          ,
                                                                       CATMathBox                & box                 );
    //Ajout MNA
    virtual void                ChangeKnotVectorAndReturnMatrix (const CATKnotVector            *  iNewKV              ,
                                                                       CATMathNxNBandSymMatrix  *& oFirstMemberMat     ,
                                                                       CATMathMxNMatrix         *& oSecondMemberMat    );

            void                       GetTolerance             (const CATTolerance             *& iTolObject          ) const;

            void                       SetTolerance             (const CATTolerance              & iTolObject          = CATGetDefaultTolerance());

            void                       SetSoftwareConfiguration (      CATSoftwareConfiguration *  iConfig             );

  protected :
    //  If you want to change globaly the KnotVector
    //  of your CATMathNurbsMultiForm (used for degree reduction).
    //  WARNING : This method can lead to important modification.
    //  If you impose some continuities at ends of the multiform,
    //  be aware of the number of freedom degree of your result
    //  KnotVector : NewNumberOfCPs >= iContinuityLeft + iContinuityRight + 2
    //  WARNING : if there is not enough freedom degree, nothing will be done.
            void               ChangeKnotValuesAndMultiplicities(const CATKnotVector            *  iNewKV              ,
                                                                       CATLONG32                   SameKnots           ,
                                                                       CATLONG32                   iContinuityL        = 0,
                                                                       CATLONG32                   iContinuityR        = 0);

           
            void               ChangeKnotValuesAndMultiplicities(const CATKnotVector            *  iNewKV              ,
                                                                       CATMathNxNBandSymMatrix  *& oFirstMemberMat     ,
                                                                       CATMathMxNMatrix         *& oS                  );

            void               Clear                            ();

            void               SetNewControlPoints              (      CATMathPoint             *  iNewCp              );
            void               AllocateNewControlPoints         (      CATMathPoint             *& ioCPArray           ,
                                                                       CATLONG32                   iSize               ,
                                                                       CATLONG32                   iNbForms            ,
                                                                       double                   *& ioWeights           );

   private:

            void               Init                             (      CATSoftwareConfiguration *  iConfig             ,
                                                                 const CATTolerance             *  iTolObject         );


            void               InitWithSetOfPointsND            (const CATKnotVector            *  iKnotVector        ,
                                                                 const CATMathSetOfPointsND     *  iPoints            ,
                                                                 const CATMathSetOfPointsND     *  iFstDer            ,
                                                                 const CATMathSetOfPointsND     *  iSndDer            ,
                                                                       CATLONG32                   iOptimiseContinuity
                                                                );


            void               InitByHermiteInterpolation       (const CATMathSetOfPointsND     *  iPts               ,
                                                                 const double                   *  iParameters        );


            void               InitWithCurve                    (const CATCurve                 *  iCurve             ,
                                                                 const CATCrvLimits             *  iCrvLim
                                                                );
            void               InitWithSetOfPoints              (const CATMathSetOfPoints      **  iSetOfPoints       ,
                                                                 const CATLONG32                 & iIsRational        ,
                                                                 const CATKnotVector            *  iKnotVector        ,
                                                                 const CATLONG32                 & iDimension         ,
                                                                 const CATLONG32                 & iNumberOfForms     ,
                                                                 const double                   *  iWeights
                                                                );


            void               InitWithBipar                    (const CATMathNurbsBipar        *  iMathNurbsBipar    ,
                                                                 const CATLONG32                 & iDir
                                                                );


            void               InitWithSurface                  (const CATLONG32                 & iDir               ,
                                                                 const CATNurbsSurface          *  iSurface           ,
                                                                 const CATSurLimits             *  iSurLimits
                                                                );

            //Explicit bruteforce: Turn everything into Bezier patches, explicitly increase degree, and convert back
            void               IncreaseDegreeViaBezierPatches   (const CATLONG32                 & iDeltaDegree       );

            //Use KnotInsertionMatrix for KnotInsertion
            void               MultipleKnotInsertionViaInsertionMatrix
                                                                (const double                   *  iKnotValues        ,
                                                                 const CATLONG32                *  iMultiplicities    ,
                                                                 const CATLONG32                 & iNbOfInsertions    ,
                                                                       double                      iTolKnotConfusion  = 0.0);

            //Use KnotInsertionMatrix to update control points
            void               DoKnotInsertion                  (      CATLONG32                   NbKnots            ,
                                                                       CATLONG32                *  SmallMultiplicities,
                                                                       CATLONG32                *  LargeMultiplicities,
                                                                 const double                   *  Knots              );

            //Computes 'identity blocks' of insertion matrix, i.e. regions where control points can remain unchanged
            void               ComputeInsertionMatrixBlocks     (      CATLONG32                   iSmallNbKnots      ,
                                                                       CATLONG32                   iLargeNbKnots      ,
                                                                       CATLONG32                   iDegree            ,
                                                                       CATLONG32                *  iSmallMult         ,
                                                                       CATLONG32                *  iLargeMult         ,
                                                                       CATLONG32                *& ioBlockRows        ,
                                                                       CATLONG32                *& ioBlockColumns     );

             void              CreateKnotInsertionMatrix        (      CATLONG32                    FullNbKnots       ,
                                                                       CATLONG32                    FullNewNbKnots    ,
                                                                       CATLONG32                    Degree            ,
                                                                       double                    *  FullKnots         ,
                                                                       double                    *  FullNewKnots      ,
                                                                       CATLONG32                 *  iSmallMult        ,
                                                                       CATLONG32                 *  iLargeMult        );

            //void ElementaryKnotInsertionMatrix(CATLONG32 k, CATLONG32 mu, CATLONG32 iNewKnot, double *iKnots, double *iNewKnots, 
            //    CATLONG32 *iMult, CATLONG32 *iNewMult, CATMathSparseMxNMatrix *& oSparseElementaryMatrix, 
            //   int * EndOfline, int * Column, double * Values);

             //Auxiliary method for CreateKnotInsertionMatrix
             void              ApplyElementaryKnotInsertionMatrix(     CATLONG32                    k                 ,
                                                                       CATLONG32                    mu                ,
                                                                       CATLONG32                    iNewKnot          ,
                                                                       double                    *  iKnots            ,
                                                                       double                    *  iNewKnots         ,
                                                                       CATLONG32                 *  iMult             ,
                                                                       CATLONG32                 *  iNewMult          ,
                                                                       double                    *  iCoef             ,
                                                                       double                    *  oCoef             );

  
  protected:

    //------------------- Data -------------------
  public :
  protected :
    const   CATTolerance             * _TolObject    ;
            CATSoftwareConfiguration * _Config       ;
            double                   * _Weights      ;

            CATMathPoint             * _tabOfCPs     ;

            CATKnotVector            * _KnotVector   ;

            CATLONG32                  _Dimension    ;
            CATLONG32                  _Offset       ;
            CATLONG32                  _NumberOfForms;
            CATLONG32                  _IsRational   ;  // 0 : No, 1 : Yes
            // -- Limits (not mandatory) --
            CATLONG32                  _IsLimited    ;  // 0 : No, 1 : Yes,
                                                        // 2:yes and empty domain of validity
            double                     _Start        ;  // if limited and the domain of validity is not empty
            double                     _End          ;  // if limited and the domain of validity is not empty


     private:
          // Added data for Knot insertion and evaluation; SMT1
          CATMathMxNBandMatrix       * _InsertionMatrix;

          CATLONG32                    _CoefBufferSize;
          double                     * _CoefBuffer1,
                                     * _CoefBuffer2;

          CATLONG32                    _KnotBufferSize;
          double                     * _NewKnots;
          CATLONG32                  * _MultBuffer,
                                     * _NewMultBuffer;

          CATLONG32                    _MaxCPxMF;
          double                     * _CpArray1,
                                     * _CpArray2;
          CATMathPoint               * _CpBuffer;
          double                     * _WeightsBuffer;

          CATMathNurbsMultiForm mutable * _WorkMult ;
};

#endif
