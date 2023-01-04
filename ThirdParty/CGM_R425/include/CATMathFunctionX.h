#ifndef CATMathFunctionX_H
#define CATMathFunctionX_H


// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFunctionGeneral.h"

#include "CATMathFunctionXType.h"
#include "CATMathInterval.h"
#include "CATTolerance.h"
#include "CATIACGMLevel.h"

// A garder jusqu'a deflaggage complet de tous sources l'utilisant
#define CATMathFunctionXR19Interface
#define CATMathFunctionXR19InterfaceComputeOptimalImage
#define CATMathFunctionXR20Interface

class CATMathAttrList;
class CATMathAttrScaleOption;
class CATMathConstraint;
class CATMathSetOfPointsND;
class CATSoftwareConfiguration;

/** @nodoc */
#define  FUNCTION 0
/** @nodoc */
#define  DERIVATE 1
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXSamplingPoints;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXConstraint;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXAbsoluteExtremum;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXInteriorExtremum;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXLimitValue;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXDiscretizationMethod;
/** @nodoc */
ExportedByYN000FUN extern const CATMathAttrId AttrFunctionXAbsoluteTolerance;


/**
 * Class representing a scalar function of one variable.
 *  <pre> F: R   -> R
 * x   -> F(x)
 * </pre>
 */ 
class ExportedByYN000FUN CATMathFunctionX : public CATMathFunctionGeneral 
{

 public:
  
  virtual ~CATMathFunctionX() ;
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 /**
 * Tests if <tt>this</tt> CATMathFunctionX derives from a class (given by a numerical value).
 * @param iClassId
 * The numerical value representing the class type.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathFunction is a type of <tt>iType</tt>,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean IsATypeOf(const CATMathFunctionXTypeId iType) const;
   
   //-----------------------------------------------------------------
   // Evaluators on doubles
   //----------------------------------------------------------------- 
 /** 
 * Evaluates <tt>this</tt> CATMathFunctionX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
 * @return
 * The result of the evaluation.
 */
   virtual double Eval           (const double & iT) const = 0;

 /** 
 * Evaluates the first derivative of <tt>this</tt> CATMathFunctionX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
 * @return
 * The result of the evaluation.
 */
   virtual double EvalFirstDeriv (const double & iT) const;

 /**
 * Evaluates the second derivative of <tt>this</tt> CATMathFunctionX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
 * @return
 * The result of the evaluation.
 */
   virtual double EvalSecondDeriv(const double & iT) const;

 /**
 * Evaluates the third derivative of <tt>this</tt> CATMathFunctionX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
 * @return
 * The result of the evaluation.
 */
   virtual double EvalThirdDeriv (const double & iT) const;


/** 
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionX and its derivatives.
 * <br><b>Precondition</b>: The pointers
 * must have been previously allocated if you asked for the corresponding evaluation. 
 * @param iT
 * The variable value where <tt>this</tt> CATMathFunctionX is evaluated.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * <dt>sum of preceeding values</dt><dd> multiple evaluation.
 * </dl>
 * @param ioF
 * A pointer to the value of <tt>this</tt> CATMathFunctionX.
 * @param ioDf
 * A pointer to the first derivative of <tt>this</tt> CATMathFunctionX.
 * @param ioD2f
 * A pointer to the second derivative of <tt>this</tt> CATMathFunctionX.
 */
   virtual void   Eval           (const double        iT      ,
                                  const CATMathOption iOption ,
                                        double        * ioF   ,
                                        double        * ioDf  = 0,
                                        double        * ioD2f = 0) const;

/** 
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionX and its derivatives at regularly spaced values.
 * <br><b>Precondition</b>: The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * @param iI
 * The interval containing the regularly spaced values.
 * @param iNbPoints
 * The number of values of <tt>iI</tt> where <tt>this</tt> CATMathFunctionX must be evaluated. 
 * If <tt>NbPoints = 1</tt>, the evaluations are made on the first value of <tt>iI</tt>.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * <dt>sum of preceeding values</dt><dd> multiple evaluation.
 * </dl>
 * @param ioF
 * The array of evaluations of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
 * @param ioDf
 * The array of the first derivatives of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
 * @param ioD2f
 * The array of the second derivatives of <tt>this</tt> CATMathFunctionX at the regurlarly spaced values.
 */
   virtual void   Eval           (const CATMathInterval  & iI       ,
                                  const CATLONG32          iNbPoints,
                                  const CATMathOption      iOption  ,
                                        double          *  ioF      ,
                                        double          *  ioDf     = 0,
                                        double          *  ioD2f    = 0) const;


  /**
  * Returns a function representing the linear combination of other CATMathFunctions.
   * <tt>iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]</tt>.
   * <br>WARNING : the returned pointer must be deleted by the caller
   */
  // see forward
  friend ExportedByYN000FUN CATMathFunctionX * CreateCombination(const CATLONG32           iN       , 
                                                                 const CATMathFunctionX ** iFunc    ,
                                                                 const double            * iCoef    , 
                                                                 const double              iConstant);

    /**
 * Tests if <tt>this</tt> CATMathFunctionX derives from a class (given by its name).
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathFunctionX is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;
 







  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

/** @nodoc */
   virtual CATMathInterval Eval           (const CATMathInterval & x) const;
/** @nodoc */
   virtual CATMathInterval EvalFirstDeriv (const CATMathInterval & x) const;
/** @nodoc */
   virtual CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
/** @nodoc */
   virtual CATMathInterval EvalThirdDeriv (const CATMathInterval & x) const;
/** 
   * @nodoc 
   * Interval evaluator of function and derivatives at the same time :
   * (performance are increased if redefined in derived classes)
   * iOptions is a command which contains which derivatives are requested
   * (usually, iOptions = OptionEvalInterval + OptionEvalFirstDerivInterval)
   */
   virtual void            Eval               (const CATMathInterval          & I            ,
                                               const CATMathOption              iOptions     ,
                                                     CATMathInterval         *  f            ,
                                                     CATMathInterval         *  df           = 0, 
                                                     CATMathInterval         *  d2f          = 0) const;

 
    /**
  * @nodoc
  * Computes a quite good interval containing the image of (I), thanks to a recursive process.
  */
   virtual CATMathInterval ComputeOptimalImage(const CATMathInterval          & I            ,
                                               const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                     CATSoftwareConfiguration*  iConfig      = NULL
                                              ) const;

  /**
   * Duplicates <tt>this</tt>. Must be implemented when defining a user CATMathFunctionX.
   */
   virtual CATMathFunctionX * Duplicate() const = 0;

   /**
   * Duplicates <tt>this</tt> as well as the pointers to the CATMathFunctionX 
    * referred to by <tt>this</tt>. Must be implemented when defining a user CATMathFunctionX.
   */
   virtual CATMathFunctionX * DeepDuplicate() const ;

#if defined ( CATIACGMR216CAA )
   /** @nodoc  Not Published  */
   virtual CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif

  //
  // Solver public interface
  //
  // iAttributes is a pointer to a list of attributes to pass options to the solver
  // (default is 0, i.e. no option).
  // The available attributes, defined from the CATMathAttrId
  // listed in the beginning of the file, are the following :
  // 
  // * CATMathAttrIntegerValue((CATMathAttrId) AttrFunctionXSamplingPoints, (CATLONG32) NbPoints)
  //     with this attribute, the sampling grid used by Solve 
  //     has NbPoints number of points.
  //
  // * CATMathContraint((CATMathAttrId) AttrFunctionXConstraint)
  //     rederive the base class CATMathConstraint to overload the Eval method.
  //
  // * AttrFunctionXDiscretizationMethod to force the discretization solver
  //
  // * AttrFunctionXAbsoluteTolerance to specify an absolute tolerance such that if the
  //   function is less than this tolerance on the domain D, it is considered as null
  //
  // The returned value is CATMathOK if all is OK, CATMathNullFunction is the function
  // vanishes on D.
   /**
   * @nodoc
   */
  virtual CATMathDiagnostic Solve      (const CATMathInterval          & D            ,
                                              CATMathSetOfPointsND     & roots        ,
                                        const CATMathAttrList         *  attributes   = 0,
                                              CATSoftwareConfiguration*  iConfig      = NULL
                                       ) const;


  // Lagrange Newton algorithm.
  // iD id the interval where the root is.
  // iF is the interval [function(Dmin), function(Dmax)] which must contain 0.
  // iDerivate indicate if we solve the function or its derivative.
  // ioResult is the initial point and the result.

    /**
   * @nodoc
   */
  virtual CATMathDiagnostic SolveNewton(const CATMathInterval          & iD           ,
                                        const CATMathInterval          & iF           ,
                                        const CATLONG32                & iDerivate    ,
                                              double                   & ioResult     ,
                                        const CATTolerance             & iTol         = CATGetDefaultTolerance(),
                                              CATMathAttrScaleOption  *  iScaleOption = NULL,
                                              CATSoftwareConfiguration*  iConfig      = NULL
                                       ) const;

  //
  // Minimize public interface
  //
  // iAttributes is a pointer to a list of attributes to pass options to the solver
  // (default is 0, i.e. no option).
  // The available attributes, defined from the CATMathAttrId listed in the 
  // beginning of the file, are the following (there are not exclusive) :
  // 
  // * CATMathAttrIntegerValue((CATMathAttrId) AttrFunctionXSamplingPoints, (CATLONG32) NbPoints)
  //     with this attribute, the sampling grid used by Minimize
  //     has NbPoints number of points.
  //
  // * CATMathAttrString((CATMathAttrId) AttrFunctionXAbsoluteExtremum)
  //     find only the absolute extremum
  //
  // * CATMathAttrString((CATMathAttrId) AttrFunctionXInteriorExtremum)
  //     find only the minimum on which the gradient vanishes.
  //
  // * CATMathAttrDoubleValue((CATMathAttrId) AttrFunctionXLimitValue, (double) LimitValue)
  //     find only all the local minima under LimitValue.
  //
  // * CATMathAttrString((CATMathAttrId) AttrFunctionXDiscretizationMethod)
  //     use a discretization method to find the minima
  //
  //
  // The returned value is CATMathOK if all is OK, CATMathConstantFunction if the function
  // appears to be constant on D.
  //
     /**
   * @nodoc
   */
  virtual CATMathDiagnostic Minimize (const CATMathInterval          & D          ,
                                            CATMathSetOfPointsND     & oSolutions ,
                                      const CATMathAttrList         *  attributes = 0,
                                            CATSoftwareConfiguration*  iConfig    = NULL
                                     ) const;
    /**
   * @nodoc
   */
  virtual CATMathDiagnostic Maximize (const CATMathInterval          & D          ,
                                            CATMathSetOfPointsND     & oSolutions ,
                                      const CATMathAttrList         *  attributes = 0,
                                            CATSoftwareConfiguration*  iConfig    = NULL
                                     ) const;
    /**
   * @nodoc
   */
  virtual double Integrate           (const CATMathInterval          & D          ,
                                      const double                     tol        ) const;
     /**
   * @nodoc
   */
  virtual double IntegrateRelative   (const CATMathInterval          & D          ,
                                      const double                     tol        ) const;

  // N is the order of GaussLegendre integration, M the number of splits to do on D
  // Possible values of N are 2, 4, 6, 8, 10, 12, 16, 20
     /**
   * @nodoc
   */
  virtual double GaussLegendre       (const CATMathInterval          & D          ,
                                      const CATLONG32                  N          ,
                                      const CATLONG32                  M          ) const;

   /**
   * @nodoc
   */
  
  virtual CATMathFunctionX * CreateDeriv() const;

  //---------------------------------------------------------------------
  // Composition creation
  //
  // Create the FunctionX defined by : t-> Phi(F(t))
  // WARNING : The returned pointer must be deleted by the caller.
  //           When the returned pointer is deleted, iPhi and iF are not deleted
  // 
  //---------------------------------------------------------------------
  /**
   * @nodoc
   */
  static CATMathFunctionX * CreateCompositionX(const CATMathFunctionX * iPhi,
                                               const CATMathFunctionX * iF  );

  //---------------------------------------------------------------------
  // Composition creation with deletion
  //
  // Create the FunctionX defined by : t-> Phi(F(t))
  // WARNING : The returned pointer must be deleted by the caller.
  //           When the returned pointer is deleted, iPhi and iF are deleted
  // 
  //---------------------------------------------------------------------
  /**
   * @nodoc
   */
  static CATMathFunctionX * CreateCompositionXDel(CATMathFunctionX * iPhi,
                                                  CATMathFunctionX * iF  );

  //---------------------------------------------------------------------
  // Cubic Interpolation creation
  //
  // Create a Piecewise-cubic FunctionX F of class C2 with minimal energy
  // such that F(iParam[i]) = iValue[i] for 0<= i < iN
  //
  // WARNING : The returned pointer must be deleted by the caller.
  //---------------------------------------------------------------------
  
  /**
   * @nodoc
   */
  static CATMathFunctionX * CreateCubicInterpolation(const CATLONG32      iN         ,
                                                     const double      *  iParam     ,
                                                     const double      *  iValue     ,
                                                     const CATTolerance & iTolObject = CATGetDefaultTolerance());

  /**
   * @nodoc
   */
   virtual CATLONG32 GetNumberOfVariables() const;


protected:
 
  /**
   * @nodoc
   */
  virtual CATMathInterval RComputeOptimalImage(const CATMathInterval & I          ,
                                               const CATMathInterval & Image      ,
                                               const CATLONG32         iDepth     ,
                                               const CATTolerance    & iTolObject = CATGetDefaultTolerance()) const;

  //---------------------------------------------------------------------
  // Composition creation
  //
  // Return the FunctionX defined by : t-> this(F(t)).
  // This method can be redefined in derived classes to support formal calculus
  // WARNING : The returned pointer must be deleted by the caller.
  //           When the returned pointer is deleted, iPhi and iF are not deleted
  // 
  //---------------------------------------------------------------------
  /**
   * @nodoc
   */
  virtual CATMathFunctionX * FormalCompositionX(const CATMathFunctionX * iF) const;

  //---------------------------------------------------------------------
  // Linear combination creation : 
  //
  // try to return a formal linear combination
  // iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i] of the same type
  // than the pointer "this".
  // Note : the pointer "this" is usually iFunc[0]. This mecanism is used to
  //        overload the creation of combination in derived classes.
  //        This method is usually called by the friend function CreateCombination
  // WARNING :  the returned pointer must be deleted by the caller of CreateCombination
  // --------------------------------------------------------------------
  /**
   * @nodoc
   */
  virtual CATMathFunctionX * FormalCombination(const CATLONG32           iN       ,
                                               const CATMathFunctionX ** iFunc    ,
                                               const double            * iCoef    ,
                                               const double              iConstant) const;

 /**
  * @nodoc
  * derive this method to tune the level of confidence of ComputeImageByChebyshev
  * and adjust the tradeoff between performance and reliability
  * it is better to decrease this parametre when the function is not very regular
  */

  virtual double             GetChebyshevConfidenceParametre() const;
  
 public:
  /**
  * @nodoc
  * Compute the first n coefficients of the chebyshev expansion of the function
  * ( Chebychev expansion is P = sum_{0<=i <=n} beta_{i} T_i(x))
  *
  * If we denote by c the returned pointer, we have
  * c[i] = beta_{i} is the i-th coefficient of the expansion
  * The returned pointer c must be deleted by the caller.
  */
          double           * ComputeChebyshevCoefficients(const CATMathInterval & D,
                                                                CATLONG32         n) const;


 /**
  * @nodoc
  * Computes in oJ an upper bound of the image of the function on the image D thanks to the chebyshev expansion.
  * Return 1 is it has succeed, 0 else (in this case, the chebyshev expansion is too bad to obtain an approximation
  * of the image from it).
  */
          CATBoolean         ComputeImageByChebyshev    (const CATMathInterval          & D ,
                                                               CATMathInterval          & oJ,
                                                         const CATTolerance             & iTolObject = CATGetDefaultTolerance(),
                                                               CATSoftwareConfiguration*  iConfig    = NULL                    ) const;


  /** @nodoc */
          CATBoolean         ComputeImageByChebyshev_old(const CATMathInterval & D ,
                                                               CATMathInterval & oJ) const;

// Creates an N-point Chebyshev approximation P of this on I such that (not assuredly but likely)

// | P(x)-Eval(x) | < eps
// Returns NULL if no good approximation found
// *** Deletion is up to caller ***
// N must be <= 16 and even, preferrably 4,6,8,12,16 (optimized values)
  /** @nodoc */
          CATMathFunctionX * ChebyshevApproximation     (const CATMathInterval & I  ,
                                                               CATLONG32         N  ,
                                                               double            eps) const;

 private:
//
// Integration private methods
//
  virtual double IntegrateAbsOrRel(const CATMathInterval & D         ,
                                   const double            tol       ,
                                   const CATBoolean        IsRelative) const;
  
  virtual double GaussLegendre    (const CATMathInterval & D         ,
                                   const CATLONG32         N         ) const;

};


//----------------------------------------------------------------------------------------------------------------------------
// Forward declaration of friend functions
// (duplication here with default argument values for standard declaration on all platforms)
//----------------------------------------------------------------------------------------------------------------------------

  /**
  * Returns a function representing the linear combination of other CATMathFunctions.
   * <tt>iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]</tt>.
   * <br>WARNING : the returned pointer must be deleted by the caller
   */
ExportedByYN000FUN
CATMathFunctionX * CreateCombination          (const CATLONG32                  iN                ,
                                               const CATMathFunctionX        ** iFunc             ,
                                               const double                   * iCoef             ,
                                               const double                     iConstant         = 0);

//----------------------------------------------------------------------------------------------------------------------------
// DS Internal Use: static methods for extended data transmission with no CAA impact on class methods
//----------------------------------------------------------------------------------------------------------------------------
// N.B methods that should have been nodoc keep their old interface during SPs of same release
/** @nodoc */
// Calls SolveNewton() method on a function, with extended argument list
ExportedByYN000FUN
CATMathDiagnostic SolveNewtonFunctionX        (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & iD                ,
                                               const CATMathInterval          & iF                ,
                                               const CATLONG32                & iDerivate         ,
                                                     double                   & ioResult          ,
                                               const CATTolerance             & iTol              = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption      = NULL,
                                                     CATSoftwareConfiguration*  iConfig           = NULL
                                              ) ;

/** @nodoc */
// Deprecated, and should have been nodoc. use SolveNewtonFunctionX
ExportedByYN000FUN
CATMathDiagnostic SolveNewton                 (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & iD                ,
                                               const CATMathInterval          & iF                ,
                                               const CATLONG32                & iDerivate         ,
                                                     double                   & ioResult          ,
                                               const CATTolerance             & iTol              = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption      = NULL
                                                 //  CATSoftwareConfiguration*  iConfig           = NULL
                                       ) ;

/** @nodoc */
// Calls ComputeOptimalImage() method on a function, with extended argument list
ExportedByYN000FUN
CATMathInterval   ComputeOptimalImageFunctionX(const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & I                 ,
                                               const CATTolerance             & iTolObject        = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption      = NULL,
                                                     int                        iUseGeneralMethod = 0   , // to force use of general method in CATMathFunctionX class (not derived method)
                                                     CATSoftwareConfiguration*  iConfig           = NULL
                                              ) ;
/** @nodoc */
// Deprecated: use ComputeOptimalImageFunctionX
// Deprecated: use ComputeOptimalImage with other arguments
ExportedByYN000FUN
CATMathInterval   ComputeOptimalImage         (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & I                 ,
                                               const CATTolerance             & iTolObject        = CATGetDefaultTolerance(),
                                                     CATMathAttrScaleOption  *  iScaleOption      = NULL,
                                                     int                        iUseGeneralMethod = 0 // to force use of general method in CATMathFunctionX class (not derived method)
                                            //,      CATSoftwareConfiguration*  iConfig           = NULL
                                              ) ;

/** @nodoc */
ExportedByYN000FUN
CATSoftwareConfiguration* GetSoftwareConfigurationUnderComputeOptimalImage(const CATMathFunctionX* iFunction) ;
/** @nodoc */
ExportedByYN000FUN
CATSoftwareConfiguration* GetSoftwareConfigurationUnderSolve              (const CATMathFunctionX* iFunction) ;


/** @nodoc */
// CAUTION: migration from iFunction->Minimize() to MinimizeFunctionX(iFunction,...);
// must not be done if Minimize() method derived in derived function
// Calls Minimize() method on a function, with extended argument list
ExportedByYN000FUN
CATMathDiagnostic MinimizeFunctionX           (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & D                 ,
                                                     CATMathSetOfPointsND     & oSolutions        ,
                                               const CATMathAttrList         *  attributes        ,
                                                     CATSoftwareConfiguration*  iConfig           = NULL) ;

/** @nodoc */
// CAUTION: migration from iFunction->Maximize() to MaximizeFunctionX(iFunction,...);
// must not be done if Maximize() method derived in derived function
// Calls Maximize() method on a function, with extended argument list
ExportedByYN000FUN
CATMathDiagnostic MaximizeFunctionX           (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & D                 ,
                                                     CATMathSetOfPointsND     & oSolutions        ,
                                               const CATMathAttrList         *  attributes        ,
                                                     CATSoftwareConfiguration*  iConfig           = NULL) ;

/** @nodoc */
// Calls Solve() method on a function, with extended argument list
ExportedByYN000FUN
CATMathDiagnostic SolveFunctionX              (const CATMathFunctionX        *  iFunction         ,
                                               const CATMathInterval          & D                 ,
                                                     CATMathSetOfPointsND     & roots             ,
                                               const CATMathAttrList         *  attributes        ,
                                                     int                        iUseGeneralMethod = 0, // =1 to force use of general method in CATMathFunctionX class (not derived method)
                                                     CATSoftwareConfiguration*  iConfig           = NULL
                                              );

#endif

