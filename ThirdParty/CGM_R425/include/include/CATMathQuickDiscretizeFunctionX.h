//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES  1997
//=============================================================================
//
// CATMathVectorialFunctionX:
// Abstract class used to define a set of functions from a domain inclued in
// R-->RN with F differentiable (C1) and N>=1.
//
//=============================================================================
//
// Usage notes:
// The result of the sample method is a set of points in RN and a set of points
// in R. 
// To use this class you will need to derivate
// this abstract class and define some evaluators on your concrete system
// of functions. You will have to code Eval method and it is also 
// strongly recommended to code EvalFirstDeriv.
// If you want to put some users constraints, you will need to derivative
// the abstract class CATMathConstraint and to code its evaluators.
//
//=============================================================================
// 29/05/08 NLD Suppression constructeur par defaut. bancal sans CATTolerance
// 05/06/18 NLD Mise au propre
//              - detabulation
//              - smart indent
//              Delibouxage
//              - _SquareInternalMinLength remplace à iso-fonctionnement la mal nommée _InternalMinLength
//=============================================================================


#ifndef CATMathQuickDiscretizeFunctionX_H
#define CATMathQuickDiscretizeFunctionX_H

class CATMathInterval;
class CATMathSetOfPointsND;
class CATMathAttrList;
class CATMathIntervalND;
class CATSoftwareConfiguration;

#include "YN000FUN.h"

#include "CATMathConstraint.h"
#include "CATMathVectorialFunctionX.h"
#include "CATMathDef.h"
#include "CATMathInterval.h"
#include "CATMathIntervalND.h"
#include "CATMathDiagnostic.h"
#include "CATMathAttrDecomposition.h"
// Diagnostic
#include "CATMathStopDiagnostic.h"
#include "CATMathVector.h"

#include "CATCGMNewArray.h"

ExportedByYN000FUN extern const CATMathAttrId AttrDomainPoint;
ExportedByYN000FUN extern const CATMathAttrId AttrStopParam;

typedef enum
{
   INSIDE, CONFUSED, OUTSIDE
} CATPointLocation;


//-----------------------------------------------------------------------------
class ExportedByYN000FUN CATMathQuickDiscretizeFunctionX : public CATMathVectorialFunctionX
{ 
public:  
   //----------------------------------------------------------  
   //  Constructor (iN is the number of functions of the system)
   //----------------------------------------------------------
   CATMathQuickDiscretizeFunctionX (      CATSoftwareConfiguration   * iSoftwareConfiguration,
                                    const CATLONG32                    iN                    ,
                                    const CATTolerance               & iTol                  = CATGetDefaultTolerance());
   //----------------------------------------------------------
   //  Default Constructor 
   //----------------------------------------------------------
public:
   //------------
   //  Destructor
   //------------
   ~CATMathQuickDiscretizeFunctionX ();
   CATCGMNewClassArrayDeclare;

           void                 SetInternalMinLength (      double                   iMinLength    );

   //-----------------------------------------------------------------
   // Information methods
   //-----------------------------------------------------------------
   
   //  Compute the sampling method :
   //   Given a iDomain of parameters in R (ex: [Domain[0], Domain[1]]),
   //   the Sample method finds a set of sorted points Xi on the curve
   //   and a set of sorted parameters, all contained by the iDomain.
   //   The mode of repartition of the points and the density are given by the
   //   iAttributes argument.
   //   The CATMathDiagnostic is CATMathOK if the Sample found a set of points.
   //   Otherwise a failure diagnostic is given.
   //   The GetDiagnostic method give you the reason of the end of the sampling.
           CATMathDiagnostic    QuickSample          (const CATMathInterval        & iDomain       ,
                                                      const CATMathIntervalND      & iDomain3D     ,
                                                            double                   iStart        ,
                                                            double                *  iStartPoint   ,
                                                            CATMathSetOfPointsND   & oSetOfPoints  );
   
   // Evaluators: iX is a point in R.
   //  . oFX = F(iX) is the image of iX by F. oFX is in RN and is already allocated. 
   //  . oDFX is the derivative of F at iX and is in RN and is already allocated. 
   //  . oD2FX is the second derivative of F at iX and is in RN and is already allocated. 
   //  . oTX is the normed tangent at iX and is in RN and is already allocated.
   virtual void                 Eval                 (const double                   iX            ,
                                                            double                *  oFX           ) const;
   virtual void                 EvalSecondDeriv      (const double                   iX            ,
                                                            double                *  D2FX          ) const;
   virtual CATBoolean           EvalPoint            (const double                   iX            ,
                                                            double                *  oFX           ,
                                                            CATPointLocation      *  oPosition     = NULL ) const = 0;

  //For Auto-Parallel
  //Returns a set of MathPoints for a single param on InputCurve at specified offsets
  //along GeodesicCurve. Implemented in CATGeodesicParallelFunction 
  virtual CATBoolean            EvaluatePoint        (const double                   iX            ,
                                                            CATMathSetOfPointsND **  ioSolutionPts ,
                                                            CATMathSetOfPointsND **  ioGeometryData) const;
  virtual CATMathSetOfPointsND* GetSolutionPoints    ();
  virtual void                  SetEndEdgeInformation(      double                   iParam        ,
                                                            CATBoolean               iSuccess      );
  virtual void                  SetSupportFacesList  (      CATListPV              & iSupSurfList  );

  virtual CATBoolean            EvalPointAndDeriv    (const double                   iX            ,
                                                            double                *  oFX           ,
                                                            double                *  oDFX          ) const;
  virtual CATBoolean            EvalDerivAtPoint     (const double                   iX            ,
                                                            double                *  oDFX          ) const;
  virtual CATBoolean            EvalTangentAtPoint   (const double                   iX            ,
                                                            double                *  oTX           );
   
   
  // Step calculation : find step at point iXcur.
          double                EvalStep             (const double                   iX            ,
                                                            double                   d             ,
                                                            double                   f             );
   
  // Permits to specify a domain in which the evaluation can be done
          void                  SetDomain            (const CATMathInterval        & iDomain       );

  // Override default number of steps or discretization
          void                  SetNumberOfSteps     (const CATLONG32                n             );

          CATLONG32             GetNumberOfSteps     ();

          void                  SetDiscretizationParamSample
                                                     (const CATListOfDouble        & ParamList     );

          void                  SetUserSag           (      double                   iUserSag      );

  // Tolerance of computation - only for some derivative classes (i.e. GeodesicParallel)
  virtual void                  SetTolerance         (      double                   tol           );

  // Modified   by REN : DEC 15,2005
  // Used for validation of geodesic distance for coupling curve
  // used to access Geodesic PtDir ope( of AdvancedTopologicalOpe FW) from CATCouplingParallel Ope ( GeometricOperators FW)
  virtual void                  CouplingCrvValidationCheckOn();

          void                  SetInfo              (      double                   iLength       ,
                                                            double                   iSurParU      ,
                                                            double                   iSurParV      ,
                                                      const CATMathVector          & itangent      );
          void                  GetInfo              (      double                *  oLength       ,
                                                            double                *  oSurParU      ,
                                                            double                *  oSurParV      ,
                                                            CATMathVector         *  otangent      );

   ////////////////
   // Protected  //
   ////////////////
protected:
   
   virtual CATBoolean ContinueDichotomy(double iParam0, double iParam1);
   
  // CATSoftwareConfiguration   *_SoftwareConfiguration;   
   
   ////////////////
   // Private    //
   ////////////////
private:
            void                RecordPoint          (const double                   iX            ,
                                                            double                *  iPointX       ,
                                                            CATMathSetOfPointsND   & ioSet2        );

            CATBoolean          ComputeBorderPoint   (      double                 & X             ,
                                                            double                   Step          )  ;

            void                RefineSetOfPoint     (      CATMathSetOfPointsND   & ioSetOfPoints );

            double              GetSquareSag         (      CATMathSetOfPointsND   & iSetOfPoints  ,
                                                            int                      iIndex        );

            CATBoolean          InsertPoint          (      CATMathSetOfPointsND   & ioSetOfPoints ,
                                                            int                      iIndex        );

            CATBoolean          EvalAndCheckPoint    (const double                   iX            ,
                                                            double                *  oFX           ,
                                                            CATPointLocation      *  oPosition     = NULL ) const;

//double          * _FunctionAtCurrentPoint;
//double          * _FirstDerivAtCurrentPoint;
//double          * _FunctionAtNextPoint;
//double          * _FirstDerivAtNextPoint;
  double          * _TMPTable;
  CATLONG32         _NbStep;
  CATMathIntervalND _Domain3D;
  double            _SquareInternalMinLength; // NLD050618 remplace à iso-fonctionnement la mal nommée _InternalMinLength
   
  CATBoolean        _IsDiscretizationGiven;
  double          * _DiscretizationParamSample;

  // Modified by REN : DEC 15,2005
  double            _Length;
  double            _SurParU;
  double            _SurParV;
  CATMathVector     _tangent;
  double            _UserSag;
   
};
#endif
