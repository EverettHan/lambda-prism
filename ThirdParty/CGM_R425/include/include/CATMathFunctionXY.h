#ifndef CATMathFunctionXY_H
#define CATMathFunctionXY_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFunctionGeneral.h"

#include "CATMathFunctionXYType.h"

#include "CATMathInterval.h"
#include "CATTolerance.h"

#define CATMathFunctionXYR20Interface
// #define CATMathFunctionXYR24Interface "voir si activation possible R23 avec regles CAA. voir impact sur CATSapCompositionFunctionXY"

class CATMathSetOfPointsND;
class CATMathIntervalND;
class CATMathInterval2D;
class CATMathAttrList;
class CATMathFunctionX;
class CATMathPoint2D;
class CATMathVector2D;
class CATMathAttrScaleOption;
class CATSoftwareConfiguration;



/**
 * Class representing a scalar function of two variables.
 *  <pre> F: RxR   -> R
 *          (x,y)  -> F(x,y)
 * </pre>
 */ 
class ExportedByYN000FUN CATMathFunctionXY : public CATMathFunctionGeneral 
{

 public:
  
 virtual ~CATMathFunctionXY() ;

  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
/**
 * Tests if <tt>this</tt> CATMathFunctionXY derives from a class (given by a numerical value).
 * @param iType
 * The numerical value representing the class type.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathFunction is a type of <tt>iType</tt>,
 * <tt>FALSE</tt> otherwise.
 */
   virtual CATBoolean     IsATypeOf                          (const CATMathFunctionXYTypeId    iType      ) const;

/** 
 * Evaluates <tt>this</tt> CATMathFunctionXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double          Eval                               (const double                   & iX         ,
                                                              const double                   & iY         ) const = 0;

 /** 
 * Evaluates the first partial derivative with respect to the first variable of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the first variable.
 */
  virtual double          EvalFirstDerivX                    (const double                   & iX         ,
                                                              const double                   & iY         ) const;

 /** 
 * Evaluates the first partial derivative with respect to the second variable of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the second variable.
 */
  virtual double          EvalFirstDerivY                    (const double                   & iX         ,
                                                              const double                   & iY         ) const;
 
 /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double          EvalSecondDerivX2                  (const double                   & iX         ,
                                                              const double                   & iY         ) const;

  /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double          EvalSecondDerivXY                  (const double                   & iX         ,
                                                              const double                   & iY         ) const;

   /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double          EvalSecondDerivY2                  (const double                   & iX         ,
                                                              const double                   & iY         ) const;
   
/** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double          EvalThirdDerivX3                   (const double                   & iX         ,
                                                              const double                   & iY         ) const;

/** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double          EvalThirdDerivX2Y                  (const double                   & iX         ,
                                                              const double                   & iY         ) const;

/** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double          EvalThirdDerivXY2                  (const double                   & iX         ,
                                                              const double                   & iY         ) const;

/** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double          EvalThirdDerivY3                   (const double                   & iX         ,
                                                              const double                   & iY         ) const;

/** 
 * Evaluates simultaneously the value, and all the first, second and third partial derivatives
 * of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param oF
 * The value of <tt>this</tt> CATMathFunctionXY.
 * @param oFx
 * The value of the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param oFy
 * The value of the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param oFx2
 * The value of the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFxy
 * The value of the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFy2
 * The value of the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFx3
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFx2y
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFxy2
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFy3
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 */
  virtual void            EvalUpToThirdDeriv                 (const double                     iX         ,
                                                              const double                     iY         ,
                                                                    double                   & oF         ,   
                                                                    double                   & oFx        ,
                                                                    double                   & oFy        ,
                                                                    double                   & oFx2       ,
                                                                    double                   & oFxy       ,
                                                                    double                   & oFy2       ,
                                                                    double                   & oFx3       ,
                                                                    double                   & oFx2y      ,
                                                                    double                   & oFxy2      ,
                                                                    double                   & oFy3       ) const;
 /** 
 * Evaluates simultaneously all third partial derivatives
 * of <tt>this</tt> CATMathFunctionXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathFunctionXY is evaluated.
 * @param oFx3
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFx2y
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFxy2
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param oFy3
 * The value of the third partial derivative of <tt>this</tt> CATMathFunctionXY.
 */
  virtual void            EvalAllThirdDerivs                 (const double                     iX         ,
                                                              const double                     iY         ,
                                                                    double                   & oFx3       ,
                                                                    double                   & oFx2y      ,
                                                                    double                   & oFxy2      ,
                                                                    double                   & oFy3       ) const;
/**
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionXY or/and its partial derivatives.
 * <br><b>Precondition</b>:The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * @param iOptions
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * </dl>
 * @param ioF
 * A pointer to the value of <tt>this</tt> CATMathFunctionXY.
 * @param ioFx
 * A pointer to the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param ioFy
 * A pointer to the first partial derivative of <tt>this</tt> CATMathFunctionXY. 
 * @param ioFx2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param ioFxy
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * @param ioFy2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 */
  virtual void            Eval                               (const double                     u          ,
                                                              const double                     v          ,
                                                              const CATMathOption              iOptions   ,
                                                                    double                  *  ioF        ,
                                                                    double                  *  ioFx       = 0,
                                                                    double                  *  ioFy       = 0,
                                                                    double                  *  ioFx2      = 0,
                                                                    double                  *  ioFxy      = 0,
                                                                    double                  *  ioFy2      = 0) const;
   
 /**
 * Simultaneously evaluates <tt>this</tt> CATMathFunctionXY or/and its partial derivatives 
 * on a regular grid of points.
 * <br><b>Precondition</b>: The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * <tt>oF[Ny*i+j]</tt> contains the evaluation of <tt>this</tt> at <tt>(x_i,y_j)</tt>.
 * @param iDomain
 * The 2D-interval of definition of the grid <tt>[xStart,xEnd] x [yStart,yEnd]</tt>. 
 * @param iNbPoints
 * The array of 2 longs, stating the number of points of the grid in each direction <tt>x</tt>
 * and <tt>y</tt>. If <tt>iNbPoints[0]=1</tt> and <tt>iNbPoints[1]=1</tt>, there is only one
 * evaluation made at the parameter <tt>(xStart,xStart)</tt>
 * @param iOptions
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * </dl>
 * @param ioF
 * The array of the evaluations of <tt>this</tt> CATMathFunctionXY.
 * @param ioFx
 * The array of the first partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points. 
 * @param ioFy
 * The array of the first partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points. 
 * @param ioFx2
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 * @param ioFxy
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 * @param ioFy2
 * The array of the second partial derivative of <tt>this</tt> CATMathFunctionXY at the grid points.
 */ 
  virtual void            Eval                               (const CATMathIntervalND        & iDomain    ,
                                                              const CATLONG32               *  iNbPoints  ,
                                                              const CATMathOption              iOptions   ,
                                                                    double                  *  ioF        ,
                                                                    double                  *  ioFx       = 0,
                                                                    double                  *  ioFy       = 0,
                                                                    double                  *  ioFx2      = 0,
                                                                    double                  *  ioFxy      = 0,
                                                                    double                  *  ioFy2      = 0) const;

  //---------------------------------------------------------------------
  // Linear combination creation
  //
  // Returns a function representing the linear combination
  // iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]
  // WARNING : the returned pointer must be deleted by the caller
  // --------------------------------------------------------------------
  // see forward
 /**
  * Returns a function representing the linear combination of other CATMathFunctionXYs.
  * <tt>iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]</tt>.
  * <br>WARNING : the returned pointer must be deleted by the caller
  */
  friend ExportedByYN000FUN 
          CATMathFunctionXY * CreateCombination              (const CATLONG32                  iN         ,
                                                              const CATMathFunctionXY      **  iFunc      ,
                                                              const double                  *  iCoef      ,
                                                              const double                     iConstant  );



 /**
 * Tests if <tt>this</tt> CATMathFunctionXY derives from a class (given by its name).
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathFunctionXY is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean      IsAKindOf                          (const CATMathClassId             iClassId   ) const;



  /**
  * @nodoc
  *
  * MultiEvaluator of f and its derivative on a non regular grid :
  * Evaluation of 
  *                F[i*xNbPoints+j] = Eval(xPoints[i],yPoints[j]), ...
  */
  virtual void            EvalGrid                           (      CATLONG32                  xNbPoints  ,
                                                              const double                  *  xPoints    ,
                                                                    CATLONG32                  yNbPoints  ,
                                                              const double                  *  yPoints    ,
                                                              const CATMathOption              iOptions   ,
                                                                    double                  *  ioF        , 
                                                                    double                  *  ioFx       = 0,
                                                                    double                  *  ioFy       = 0) const;
    

  /** 
 * Evaluates <tt>this</tt> CATMathFunctionXY for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @param iTolObject
 * The tolerance.
 * @return
 * The interval which contains the values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */
  virtual CATMathInterval Eval                               (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ,
                                                              const CATTolerance             & iTolObject = CATGetDefaultTolerance()) const;

  /** 
 * Evaluates the first partial derivative with respect to the first variable
 * for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @return
 * The interval which contains the first derivatives values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */ 
  virtual CATMathInterval EvalFirstDerivX                    (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ) const;
 /** 
 * Evaluates the first partial derivative with respect to the second variable
 * for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @return
 * The interval which contains the first derivative values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */ 
  virtual CATMathInterval EvalFirstDerivY                    (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ) const;
  /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @return
 * The interval which contains the second derivative values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */ 
  virtual CATMathInterval EvalSecondDerivX2                  (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ) const;
   /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY.
 * for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @return
 * The interval which contains the second derivative values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */ 
  virtual CATMathInterval EvalSecondDerivXY                  (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ) const;
  /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathFunctionXY .
 * for values defined by intervals.
 * @param Du
 * The interval containing the values along X.
 * @param Dv
 * The interval containing the values along Y.
 * @return
 * The interval which contains the second derivative values calculated from <tt>Du</tt> and <tt>Dv</tt>.
 */ 
  virtual CATMathInterval EvalSecondDerivY2                  (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ) const;

  
  /** 
  * @nodoc 
  * Interval evaluator of function and derivatives at the same time .
  * (performance are increased if redefined in derived classes)
  * iOptions is a command which contains which derivatives are requested
  * (usually, iOptions = OptionEvalInterval + OptionEvalFirstDerivInterval)
  */ 
  virtual void            Eval                               (const CATMathInterval          & Du         ,
                                                              const CATMathInterval          & Dv         ,
                                                              const CATMathOption              iOptions   ,
                                                                    CATMathInterval         *  f          ,
                                                                    CATMathInterval         *  fx         = 0,
                                                                    CATMathInterval         *  fy         = 0,
                                                                    CATMathInterval         *  fx2        = 0,
                                                                    CATMathInterval         *  fxy        = 0,
                                                                    CATMathInterval         *  fy2        = 0,
                                                              const CATTolerance             & iTol       = CATGetDefaultTolerance()) const;

  /**
  * @nodoc
  * Multi-evaluation of interval  on a regular grid of
  * Nu x Nv sub-squares  delimited by  [uStart,uEnd] x [vStart,vEnd].
  * WARNING : the pointer Images  must be previously allocated
  * Images[Nv*i+j] contains Eval(X_i,Y_j)
  */
  virtual void            Eval                               (const CATMathIntervalND        & iDomain    ,
                                                              const CATLONG32               *  NbIntervals,
                                                                    CATMathInterval         *  Images     ) const;

  /**
  * @nodoc
  * Compute the first n x nn coefficients of the chebyshev expansion of the function
  * ( Chebychev expansion is P = sum_{0<=i <=n, 0<=j<=nn} beta_{i,j} T_i(x)T_j(y))
  *
  * The pointeur c must be allocated to (n+1)*(nn+1). We have
  * c[(n+1)*i+j] = beta_{i,j} is the (i,j) coefficient of the expansion
  */
          void            ComputeChebyshevCoefficients       (const CATMathInterval          & Du,
                                                              const CATMathInterval          & Dv,
                                                                    CATLONG32                  n ,
                                                                    CATLONG32                  nn,
                                                                    double                  *  c ) const;

  
  /**
  * @nodoc
  * Compute in oJ an upper bound of the image of the function on the image Du x Dv thanks to the chebyshev expansion.
  * Return 1 is it has succeed, 0 else (in this case, the chebyshev expansion is too bad to obtain an approximation
  * of the image from it).
  */
          CATBoolean      ComputeImageByChebyshev            (const CATMathInterval          & Du,
                                                              const CATMathInterval          & Dv,
                                                                    CATMathInterval          & oJ,
                                                              const CATTolerance             & iTolObject = CATGetDefaultTolerance()) const;

  /** @nodoc */
          CATBoolean      ComputeImageByChebyshev_old        (const CATMathInterval          & Du,
                                                              const CATMathInterval          & Dv,
                                                                    CATMathInterval          & oJ) const;


  /** @nodoc */
  virtual CATMathInterval ComputeOptimalImage                (const CATMathInterval          & Du           ,
                                                              const CATMathInterval          & Dv           ,
                                                              const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
#ifdef CATMathFunctionXYR24Interface
                                                                    CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                                    CATSoftwareConfiguration*  iConfig      = NULL
#else
                                                                    CATMathAttrScaleOption  *  iScaleOption = NULL
#endif
                                                             ) const;
  //-----------------------------------------------------------------
  // Minimize
  // Min F(x, y) where x and y are in the given Domain.
  // The minimization takes the bounds of the Domain in account.
  // Different options are available (absolute minimum/all minima ,
  // interior minimum, minimum with image lower than K)
  // The default method is a discretization method, using a specific
  // argument an interval method is accessible (safer about 50% slower).
  //-----------------------------------------------------------------
  /**
  * @nodoc
  */
  virtual CATMathDiagnostic Minimize                         (const CATMathInterval2D        & iDomain      ,
                                                                    CATMathSetOfPointsND     & roots        ,
                                                              const CATMathAttrList         *  attributes   = NULL,
                                                                    CATSoftwareConfiguration*  iConfig      = NULL
                                                             ) const;
    /**
    * @nodoc
    */
  virtual CATMathDiagnostic Maximize                         (const CATMathInterval2D        & iDomain      ,
                                                                    CATMathSetOfPointsND     & roots        ,
                                                              const CATMathAttrList         *  attributes   = 0,
                                                                    CATSoftwareConfiguration*  iConfig      = NULL
                                                             ) const;

  /**
  * @nodoc
  */
  virtual double          Integrate                          (const CATMathInterval          & Du           ,
                                                              const CATMathInterval          & Dv           ,
                                                              const double                     tol          ) const;
 /**
  * @nodoc
  */
  virtual double          IntegrateRelative                  (const CATMathInterval          & Du           ,
                                                              const CATMathInterval          & Dv           ,
                                                              const double                     tol          ) const;
   /**
  * @nodoc
  */
  virtual double          Integrate                          (const CATMathInterval          & Du           ,
                                                              const double                   & v            ,
                                                              const CATMathFunctionX        *  iF           ,
                                                              const double                     tol          ) const;
 /**
  * @nodoc
  */
  virtual double          IntegrateRelative                  (const CATMathInterval          & Du           ,
                                                              const double                   & v            ,
                                                              const CATMathFunctionX        *  iF           ,
                                                              const double                     tol          ) const;
  
  /**
  * @nodoc
  */
  virtual CATMathFunctionXY * CreateDerivX                   () const;

  /**
  * @nodoc
  */
  virtual CATMathFunctionXY * CreateDerivY                   () const;

   /**
  * @nodoc
  */
  virtual CATMathFunctionX * CreateIsoparX                   (const double                   & x            ) const;

  /**
  * @nodoc
  */
  virtual CATMathFunctionX * CreateIsoparY                   (const double                   & y            ) const;

  //---------------------------------------------------------------------
  // Composition creation  
  //
  // Create the FunctionX defined by : t-> Phi(F(t),G(t))
  // where Phi represents the FunctionXY "this", 
  // WARNING : The returned pointer must be deleted by the caller.
  //
  //---------------------------------------------------------------------
 /**
  * @nodoc
  */
  virtual CATMathFunctionX * CreateCompositionX              (const CATMathFunctionX        *  iF           ,
                                                              const CATMathFunctionX        *  iG           ) const;

  //--------------------------------------------------------------------
  // Convergence on nul gradient
  //
  // Use the newton iteration on the gradient to find a solution
  // 0 is returned if no solution where found
  // 1 is returned if a solution was found, the solution is (x,y)
  //----------------------------------------------------------------------
 
  /**
  * @nodoc
  */
  virtual CATBoolean      MinimizeNewton                     (      double                   & x            ,
                                                                    double                   & y            ,
                                                              const double                     xMin         ,
                                                              const double                     xMax         ,
                                                              const double                     yMin         ,
                                                              const double                     yMax         ,
                                                              const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
                                                                    CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                                    CATSoftwareConfiguration*  iConfig      = NULL
                                                             ) const;

 /**
  * @nodoc
  */
  virtual CATMathFunctionXY* Duplicate                       () const;

  /** @nodoc  Not Published  */
  virtual CATMathFunctionXY* DeepDuplicate                   () const;

#if defined ( CATIACGMR216CAA )
  /** @nodoc  Not Published  */
  virtual CATMathFunctionXY* DeepDuplicateWithTol            (const CATTolerance            *  ipTolObject  ) const ;
#endif

  /** @nodoc  Not Published  */
  virtual CATLONG32          GetNumberOfVariables            () const;

protected:
 /**
  * @nodoc
  */
  virtual CATMathInterval    RComputeOptimalImage            (const CATMathInterval          & Du           ,
                                                              const CATMathInterval          & Dv           ,
                                                              const CATMathInterval          & Image        ,
                                                              const CATLONG32                  iDepth       ,
                                                              const CATTolerance             & iTolObject   = CATGetDefaultTolerance()) const;


 /**
  * @nodoc
  */
  virtual CATMathFunctionXY * FormalCombination              (const CATLONG32                  iN           ,
                                                              const CATMathFunctionXY      **  iFunc        ,
                                                              const double                  *  iCoef        ,
                                                              const double                     iConstant    ) const;
 /**
  * @nodoc
  */
  virtual double              IntegrateAbsOrRel              (const CATMathInterval          & Du           ,
                                                              const CATMathInterval          & Dv           ,
                                                              const double                     tol          ,
                                                              const CATBoolean                 IsRelative   ) const;
   /**
  * @nodoc
  */
  virtual double              IntegrateAbsOrRel              (const CATMathInterval          & Du           ,
                                                              const double                   & v            ,
                                                              const CATMathFunctionX        *  iF           ,
                                                              const double                     tol          ,
                                                              const CATBoolean                 IsRelative   ) const;




public:
    
// Creates an MxN-point Chebyshev approximation P of this on slab IxJ such that (not assuredly but likely)
// | P(x,y)-Eval(x,y) | < eps
// Returns NULL if no good approximation found
// *** Deletion is up to caller ***
// M and N must be <= 16 and even, preferrably 4,6,8,12,16 (optimized values)
    /** @nodoc */
          CATMathFunctionXY * ChebyshevApproximation         (const CATMathInterval          & I            ,
                                                              const CATMathInterval          & J            ,
                                                                    CATLONG32                  M            ,
                                                                    CATLONG32                  N            ,
                                                                    double                     eps          ) const;



};


//----------------------------------------------------------------------------------------------------------------------------
// Forward declaration of friend functions
// (duplication here with default argument values for standard declaration on all platforms)
//----------------------------------------------------------------------------------------------------------------------------
 /**
  * Returns a function representing the linear combination of other CATMathFunctionXYs.
  * <tt>iConstant + Sum_{i=0}^{iN-1} iCoef[i] * iFunc[i]</tt>.
  * <br>WARNING : the returned pointer must be deleted by the caller
  */
ExportedByYN000FUN
          CATMathFunctionXY * CreateCombination              (const CATLONG32                  iN           ,
                                                              const CATMathFunctionXY      **  iFunc        ,
                                                              const double                  *  iCoef        ,
                                                              const double                     iConstant    = 0.0);

//----------------------------------------------------------------------------------------------------------------------------
// DS Internal Use: static methods for extended data transmission with no CAA impact on class methods
//----------------------------------------------------------------------------------------------------------------------------
/** @nodoc */
// Deprecated: use MinimizeNewtonFunctionXY
// Deleted (no more used) NLD250516
/*
extern "C" ExportedByYN000FUN
          CATBoolean MinimizeNewton                          (const CATMathFunctionXY             *  iFunction   ,
                                                                    double                         & x           ,
                                                                    double                         & y           ,
                                                                    const double                     xMin        ,
                                                                    const double                     xMax        ,
                                                                    const double                     yMin        ,
                                                                    const double                     yMax        ,
                                                                    const CATTolerance             & iTol        ,
                                                                          CATMathAttrScaleOption  *  iScaleOption
                                                             ) ;
*/

/** @nodoc */
extern "C" ExportedByYN000FUN
          CATBoolean          MinimizeNewtonFunctionXY             (const CATMathFunctionXY       *  iFunction   ,
                                                                          double                   & x           ,
                                                                          double                   & y           ,
                                                                    const double                     xMin        ,
                                                                    const double                     xMax        ,
                                                                    const double                     yMin        ,
                                                                    const double                     yMax        ,
                                                                    const CATTolerance             & iTol        ,
                                                                          CATMathAttrScaleOption  *  iScaleOption,
                                                                          CATSoftwareConfiguration*  iConfig
                                                                   ) ;

/** @nodoc */
extern "C" ExportedByYN000FUN
             CATMathDiagnostic MinimizeFunctionXY                  (const CATMathFunctionXY       * iFunction  ,
                                                                    const CATMathInterval2D        & D         ,
                                                                          CATMathSetOfPointsND     & roots     ,
                                                                    const CATMathAttrList         *  attributes,
                                                                          CATSoftwareConfiguration*  iConfig   ) ;

/** @nodoc */
extern "C" ExportedByYN000FUN
             CATMathDiagnostic MaximizeFunctionXY                  (const CATMathFunctionXY       *  iFunction ,
                                                                    const CATMathInterval2D        & D         ,
                                                                          CATMathSetOfPointsND     & roots     ,
                                                                    const CATMathAttrList         *  attributes,
                                                                          CATSoftwareConfiguration*  iConfig
                                                                   ) ;

/** @nodoc */
/*extern "C" */ExportedByYN000FUN
             CATMathInterval ComputeOptimalImageFunctionXY         (const CATMathFunctionXY       *  iFunction         ,
                                                                    const CATMathInterval          & Du                ,
                                                                    const CATMathInterval          & Dv                ,
                                                                    const CATTolerance             & iTolObject        ,
                                                                          CATMathAttrScaleOption  *  iScaleOption      ,
                                                                          // to force use of general method in CATMathFunctionXY class (not derived method)
                                                                          int                        iUseGeneralMethod = 0,
                                                                          CATSoftwareConfiguration*  iConfig           = NULL
                                                                   ) ;

#endif
