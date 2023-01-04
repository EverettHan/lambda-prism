#ifndef CATLaw_h
#define CATLaw_h

// #define CATLawInterfaceR19 "TestNLD XScale. ne jamais activer en release r18"

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 
#include "CATIACGMLevel.h"
#define CATLawInterfaceR19

#include "CATICGMObject.h"
#include "CATEvalCommand.h"
#include "CATMathDef.h"
#include "CATMathLimits.h"
#include "CATMathFunctionX.h"
#include "CATGeoFactory.h"
#include "ExportedByCATGMGeometricInterfaces.h"
class CATMathSetOfPointsND;
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATLaw ;
#else
extern "C" const IID IID_CATLaw ;
#endif

/**
 * Base interface representing the laws.
 *<br>A law is a function <tt>L</tt> of one parameter <tt>iT</tt> on a given 1D interval
 * <tt>[iTmin,iTmax]</tt>.
 */
class ExportedByCATGMGeometricInterfaces CATLaw : public CATICGMObject
{
  CATDeclareInterface;

public:
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/**
 * Retrieves the definition interval of <tt>this</tt> CATLaw.
 * @param ioTMin
 * The lower bound value.
 * @param ioTMax
 * The upper bound value.
 */
  virtual void              GetDefinitionInterval          (       double              & ioTMin               ,
                                                                   double              & ioTMax               )    const = 0;

/**
 * Retrieves the extremum values of the law.
 * @param ioMin
 * The minimum law value <tt>ioMin= min(L(t))</tt>.
 * @param ioMax
 * The maximum law value <tt>ioMax= max(L(t))</tt>.
 */
  virtual void              GetExtremums                    (      double              & ioMin                ,
                                                                   double              & ioMax                )          = 0;


/**
 * Returns the number of constraint parameters.
 * @return
 * The number of constraint parameters.
 */
  virtual CATLONG32         GetNumberOfConstraintParameters ()                                                     const = 0 ;

 /**
 * Returns a constraint parameter.
 * @param iIndex
 * The index (beginning at <tt>0</tt>) of the constraint parameter.
 */
  virtual double            GetOneConstraintParameter       (const CATLONG32             iIndex               )    const = 0 ;

  //- Read all constraint parameters.
  // Returns constraints count and pointer on parameters, this pointer must be
  // DELETED afterwards (NULL if constraints count = 0).
/**
 * Returns the constraint parameters.
 * <br>The internal values are copied into the output array.
 * @param ioNumberOfConstraints
 * The index (beginning at <tt>0</tt>) of the constraint parameter.
 * @return
 * The array of the constraint parameter values. The array is allocated by the method, and
 * must be deallocated by the caller. If <tt>ioNumberOfConstraints==0</tt>, the array is not
 * allocated.
 */
  virtual double          * GetConstraintParameters         (      CATLONG32           & ioNumberOfConstraints)    const = 0 ;

  //-------------------------------------------------------------------------
  //- Search for the arc (iArcRank) corresponding a given parameter T.
  // A arc is the Sub-Law between two constraints.
  // iArcRank = 1 indicates the arc following the index 0 constraint
  // parameter.
  // if T = one constraint parameter, the following arc is given.
  //-------------------------------------------------------------------------

/**
 * Returns the constraint index nearest to a given parameter.
 * @param iT
 * The parameter value.
 * @return
 * The index (beginning at 0) of the nearest constraint.
 */
  virtual CATLONG32         LocateConstraint                (const double                iT                   )    const = 0 ;

  //-------------------------------------------------------------------------
  //- Evaluators.
  //-------------------------------------------------------------------------
/**
 * Evaluates <tt>this</tt> law.
 * @param iT
 * The parameter value where to evaluate.
 * @return
 * The corresponding law value (<tt>L(iT)</tt>).
 */
  virtual double            Eval                            (const double                iT                   )    const = 0 ;

 /**
 * Evaluates the first derivative of <tt>this</tt> law.
 * @param iT
 * The parameter value where to evaluate.
 * @return
 * The first derivative value (<tt>L'(iT)</tt>).
 */
  virtual double            EvalFirstDeriv                  (const double                iT                   )    const = 0 ;
 /**
 * Evaluates the second derivative of <tt>this</tt> law.
 * @param iT
 * The parameter value where to evaluate.
 * @return
 * The second derivative value (<tt>L''(iT)</tt>).
 */
  virtual double            EvalSecondDeriv                 (const double                iT                   )    const = 0 ;
 /**
 * Evaluates the third derivative of <tt>this</tt> law.
 * @param iT
 * The parameter value where to evaluate.
 * @return
 * The third derivative value (<tt>L'''(iT)</tt>).
 */
  virtual double            EvalThirdDeriv                  (const double                iT                   )    const = 0 ;






  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  
/**
 * @nodoc
 */
  virtual CATMathDiagnostic GetParametersForALawValue       (      double                iLawValue            ,
                                                                   CATMathSetOfPointsND &ioParameters         ,
                                                             const double                iTolerance           )          = 0;

/** @nodoc 
* Deprecated.
*/
  virtual CATMathDiagnostic GetParametersForALawValue       (      double                iLawValue            ,
                                                                   CATMathSetOfPointsND &ioParameters         )          = 0;


/**
 * @nodoc
 */
  virtual CATLONG32          LocateArc                      (const double                iT                   )          = 0 ;

/**
 * @nodoc
 * Scales the definition interval.
 * @param iNewTMin
 * The new lower bound value.
 * @param iNewTMax
 * The new upper bound value.
 */
  virtual void               ScaleDefinitionInterval        (const double                iNewTMin             ,
                                                             const double                iNewTMax             )          = 0;

  //
  // Evaluator of Value and derivatives at the same time :
  //
/**
 * @nodoc
 * Simultaneously evaluates the law and its derivatives.
 */
  virtual void               Eval                           (const double             *  iT                   ,
                                                             const CATLONG32             iNbrOfParam          ,
                                                             const CATEvalCommand        iCmd                 ,
                                                                   double              * oValue               ,
                                                                   double              * oSlope               = 0,
                                                                   double              * oSecondDeriv         = 0,
                                                                   double              * oThirdDeriv          = 0) const = 0 ;
  
  //-------------------------------------------------------------------------
  //- Evaluators on one arc:
  // An arc is the Sub-Law between two constraints, the parameter T is not 
  // necessary between these two constraints. 
  //-------------------------------------------------------------------------
  /** @nodoc */
  virtual double             Eval                           (const CATLONG32             iArcRank             ,
                                                             const double                iT                   ) const = 0 ;
    /** @nodoc */
  virtual double             EvalFirstDeriv                 (const CATLONG32             iArcRank             ,
                                                             const double                iT                   ) const = 0 ;
    /** @nodoc */
  virtual double             EvalSecondDeriv                (const CATLONG32             iArcRank             ,
                                                             const double                iT                   ) const = 0 ;
    /** @nodoc */
  virtual double             EvalThirdDeriv                 (const CATLONG32             iArcRank             ,
                                                             const double                iT                   ) const = 0 ;

  //
  // Evaluator on one arc of Value and derivatives at the same time :
  //
    /** @nodoc */
  virtual void               Eval                           (const CATLONG32             iArcRank             ,
                                                             const double             *  iT                   ,
                                                             const CATLONG32             iNbrOfParam          ,
                                                             const CATEvalCommand        iCmd                 ,
                                                                   double             *  oValue               ,
                                                                   double             *  oSlope               = 0,
                                                                   double             *  oSecondDeriv         = 0,
                                                                   double             *  oThirdDeriv          = 0) const = 0 ;

  //-------------------------------------------------------------------------
  //- Equations management
  //-------------------------------------------------------------------------
/** @nodoc */
  virtual void               OpenEquation                   ()                                                     const = 0;
  /** @nodoc */
  virtual void               CloseEquation                  ()                                                     const = 0;
  /** @nodoc */
  virtual void               GetEquation                    (const CATLONG32             iArcRank             ,
                                                             const CATMathFunctionX   *& oF                   )    const = 0;
  /** @nodoc */
  virtual void               GetGlobalEquation              (const CATMathFunctionX   *& oF                   )    const = 0;

  //-------------------------------------------------------------------------
  //- Read whether the Law is periodic.
  //-------------------------------------------------------------------------
/**
 * @nodoc
 * Tests whether <tt>this</tt> law is periodic.
 * @return
 * The result of the test.
 * <br><b>Legal values</b></tt>: <tt>TRUE</tt> is it is, <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean         IsPeriodic                     ()                                                     const = 0;

  //-------------------------------------------------------------------------
  //- Set the Law periodic (the period is the definition interval)
  //  iPeriodic = 0 : the law is not periodic  
  //  iPeriodic = 1 : the law is periodic  
  //-------------------------------------------------------------------------
/** @nodoc */
  virtual void               SetPeriodic                    (const CATLONG32             iPeriodic            = 1)       = 0;

  //-------------------------------------------------------------------------
  //- Read global continuity.
  //  0 --> C0
  //  1 --> C1
  //  n --> Cn
  //-------------------------------------------------------------------------
  /** @nodoc */
  virtual CATLONG32          GetGlobalContinuity            ()                                                     const = 0;
  /** @nodoc */
  virtual CATLONG32          GetGlobalContinuity            (      double                iTolPt               )    const = 0;

  /** @nodoc */
  virtual CATLONG32          GetConstraintContinuity        (const CATLONG32             iIndex               )    const = 0 ;
  /** @nodoc */
  virtual CATLONG32          GetConstraintContinuity        (const CATLONG32             iIndex               ,
                                                                   double                iTolPt               )    const = 0 ;


  //-------------------------------------------------------------------------
  //- Duplicate the Law
  //-------------------------------------------------------------------------
  /** @nodoc */
  virtual CATLaw          *  Duplicate                     (       CATGeoFactory      *  iFactory             )     const = 0;

  //-------------------------------------------------------------------------
  //- Apply a scaling to the Law
  //-------------------------------------------------------------------------
/** @nodoc */
  virtual void               ApplyScaling                  (        double               iRatio               )           = 0;

  //-------------------------------------------------------------------------
  //- Read the scaling value
  //-------------------------------------------------------------------------
/** @nodoc */
  virtual double             GetScalingValue               ()                                                       const = 0;
 
#ifdef CATLawInterfaceR19
   //-------------------------------------------------------------------------
   // Scale management
   // iPowerScaleX: factory scale power for law parameter
   // iPowerScaleF: factory scale power for law value
   //-------------------------------------------------------------------------
   virtual void              SetScalePowerXScalePowerF     (        CATLONG32             iPowerScaleX        ,
                                                                    CATLONG32             iPowerScaleF        ,
                                                                    CATLONG32             iReviewed           = 0)        = 0 ;
   // returns 0 if not previously set
   virtual CATLONG32         GetScalePowerXScalePowerF     (        CATLONG32           & oPowerScaleX        ,
                                                                    CATLONG32           & oPowerScaleF        ,
                                                                    CATLONG32           & oReviewed           )           = 0 ;
#endif
};

CATDeclareHandler(CATLaw,CATICGMObject);

#endif

