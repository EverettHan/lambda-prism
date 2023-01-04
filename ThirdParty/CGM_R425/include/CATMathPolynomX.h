#ifndef CATMathPolynomX_H
#define CATMathPolynomX_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#include "YN000FUN.h"

#include "CATMathDef.h"
#include "CATMathFoundationX.h"

#include "CATTolerance.h"
#include "CATIACGMLevel.h"

#define CATPolynomXR19NbStaticCoeff 6

class  CATMathInterval;
class CATMathStream;
/**
 * Class defining the real polynom of one variable.
 */
class ExportedByYN000FUN CATMathPolynomX : public CATMathFoundationX
{
 public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  /**
   * Constructs a polynom of one variable.
   * @param iDeg
   * The degree of the polynom.
   * @param iCoeff
   * The array of the coefficients such that:
   * <br><tt>   pol=Sum_{i=0..iDeg}  iCoef[i] X^i </tt>.
   * @param iShift
   * Internal use.
   */
   CATMathPolynomX(const CATLONG32 iDeg = 0, const double *iCoef = 0, const double iShift=0.);



/**
 * Copy constructor.
 */
  CATMathPolynomX(const CATMathPolynomX & iToCopy);

  /**
   * Modifies the coeficients of <tt>this</tt> CATMathPolynomX.
   * @param iNewDeg
   * The new value of the degree.
   * @param iNewCoef
   * The array of the new coefficients such that:
   * <br><tt>   pol=Sum_{i=0..iDeg}  iCoef[i] X^i </tt>.
   */
  void SetCoefficients(const CATLONG32 iNewDeg = 0, const double *iNewCoef = 0);
  
  /**
   * Returns the degree of <tt>this</tt> CATMathPolynomX.
   * @return
   * The degree.
   */
  CATLONG32 GetDegree() const{return _degree;};

/**
 * Retrieves the coefficients of <tt>this</tt> CATMathPolynomX.
 * @param ioCoeff
 * The array (previously allocated) of the coefficients.
 * <br><tt>   pol=Sum_{i=0..iDeg}  ioCoef[i] X^i </tt>.</tt>.
 */
  void GetCoefficients(double * ioCoeff) const;

   /**
   * Returns the coefficients of <tt>this</tt> CATMathPolynomX.
   * @return
   * The array of the coefficients. As part of <tt>this</tt>, it must not be deallocated.
   */
  const double * GetCoefficients() const { return _coeff; };

/**
 * Returns the class name of <tt>this</tt>  CATMathPolynomX.
 * @return
 * A pointer to the name <tt>CATMathPolynomX</tt>.
 */
  virtual CATMathClassId IsA() const;

/**
 * Tests whether <tt>this</tt> CATMathPolynomX derives from a class (given by its name).
 * @param iClassId
 * The name of the class.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathPolynomX is a kind of <tt>iClassId</tt>,
 * <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;

/**
 * Tests whether <tt>this</tt> CATMathPolynomX derives from a class (given by a numerical value).
 * @param iClassId
 * The numerical value representing the class type.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathPolynomX is a type of <tt>iType</tt>,
 * <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean IsATypeOf(const CATMathFunctionXTypeId iClassId) const; 
   
/**
 * Tests whether an evaluator is available for <tt>this</tt> CATMathPolynomX.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivative of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivative of the function
 * <dt>OptionEvalThirdDeriv</dt>  <dd>  evaluation of the third derivative of the function
 * </dl>
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the evaluation is available for <tt>this</tt> CATMathPolynomX,
 * <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean IsOption(const CATMathOption iOption) const;

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
/** 
 * Evaluates <tt>this</tt> CATMathPolynomX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathPolynomX is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double Eval(const double & iT) const;

/** 
 * Evaluates the first derivative of <tt>this</tt> CATMathPolynomX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathPolynomX is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double EvalFirstDeriv (const double & iT) const;

/** 
 * Evaluates the second derivative of <tt>this</tt> CATMathPolynomX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathPolynomX is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double EvalSecondDeriv(const double & iT) const;

/** 
 * Evaluates the third derivative of <tt>this</tt> CATMathPolynomX.
 * @param iT
 * The variable value where <tt>this</tt> CATMathPolynomX is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double EvalThirdDeriv (const double & iT) const;

/** 
 * Simultaneously evaluates <tt>this</tt> CATMathPolynomX and its derivatives.
 * <br><b>Precondition</b>: The pointers
 * must have been previously allocated if you asked for the corresponding evaluation. 
 * @param iT
 * The variable value where <tt>this</tt> CATMathPolynomX is evaluated.
 * @param iOption
 * The type of evalution.
 * <br><b>Legal values</b>:
 * <dl> <dt>OptionEval   </dt>  <dd>  evaluation of the function
 * <dt>OptionEvalFirstDeriv   </dt>  <dd>  evaluation of the first derivatives of the function
 * <dt>OptionEvalSecondDeriv</dt>  <dd>  evaluation of the second derivatives of the function
 * <dt>sum of preceeding values</dt><dd> multiple evaluation.
 * </dl>
 * @param ioF
 * A pointer to the value of <tt>this</tt> CATMathPolynomX.
 * @param ioDf
 * A pointer to the first derivative of <tt>this</tt> CATMathPolynomX.
 * @param ioD2f
 * A pointer to the second derivative of <tt>this</tt> CATMathPolynomX.
 */
  virtual void Eval(const double         iT     ,
                    const CATMathOption  iOption,
                    double             * ioF    ,
                    double             * ioDf   = 0,
                    double             * ioD2f  = 0) const;
  
/** 
 * Simultaneously evaluates <tt>this</tt> CATMathPolynomX and its derivatives at regularly spaced values.
 * <br><b>Precondition</b>: The output arrays
 * must have been previously allocated if you asked for the corresponding evaluation.
 * @param iI
 * The interval containing the regularly spaced values.
 * @param iNbPoints
 * The number of values of <tt>iI</tt> where <tt>this</tt> CATMathPolynomX must be evaluated. 
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
 * The array of evaluations of <tt>this</tt> CATMathPolynomX at the regurlarly spaced values.
 * @param ioDf
 * The array of the first derivatives of <tt>this</tt> CATMathPolynomX at the regurlarly spaced values.
 * @param ioD2f
 * The array of the second derivatives of <tt>this</tt> CATMathPolynomX at the regurlarly spaced values.
 */
  virtual void Eval(const CATMathInterval & iI       ,
                    const CATLONG32         iNbPoints,
                    const CATMathOption     iOption  ,
                    double               *  ioF      ,
                    double               *  ioDf     = 0,
                    double               *  ioD2f    = 0) const;








  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<


   /**
   * @nodoc
   * Constucts a Hermite interpolation (iDeg=3 or iDeg=5).
   */
  CATMathPolynomX(const CATLONG32 iDeg, const CATMathInterval & iD, 
    const double *iStart, const double *iEnd, 
    const CATBoolean iShiftOption=0);  

  virtual ~CATMathPolynomX();
   /** @nodoc */
  CATCGMNewClassArrayDeclare;

   /** @nodoc */
  virtual CATMathFunctionX * Duplicate() const;

  /** @nodoc */
  virtual CATMathFunctionX * DeepDuplicate() const;

#if defined ( CATIACGMR216CAA )
  /** @nodoc  Not Published  */
  virtual CATMathFunctionX * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
#endif
  //-----------------------------------------------------------------
  // Stream 
  //-----------------------------------------------------------------
#if defined ( CATIACGMV5R21 )
   /**
    * @nodoc
    */
   virtual short GetStreamDomainType(char ioDomain[3]) const;
#else
   /**
    * @nodoc
    */
   virtual short GetStreamType() const;
#endif
   /** @nodoc */
  void Stream( CATMathStream& Str, const char iLabelReserved[] = "" ) const;
  /** @nodoc */
  virtual size_t  GetStaticMemoryBytes() const;  
  /** @nodoc */
   virtual size_t  GetDynamicMemoryBytes() const;   
   /** @nodoc */
  virtual CATBoolean _IsStreamable( const CATCGMStreamVersion iTargetVersion, CATBoolean & ioReversible ) const;

  //-----------------------------------------------------------------
  // Set Methods
  //-----------------------------------------------------------------
  
  /**
   * @nodoc
   * Modifies the Shift value.
   */
  void SetShift (const double iShift=0.){_Shift=iShift;};
  /**
   * @nodoc
   * Perform the formal shift to set the Shift value to 0.
   */
  void CancelShift ();

  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------

   /** @nodoc */
  void GetFormalCoefficients(double * ioCoeff) const;

  /**
   * @nodoc
   * Returns the Shift value.
   */
   double GetShift ( ) const {return _Shift;};



   /**
 * @nodoc
 * Tests the monotony of <tt>this</tt> CATMathPolynomX.
 * @param iD
 * The interval on which the monotony is checked.
 * @param ioType
 * The type of monotony.
 * <br><b>Legal values</b>:
 * <dl><dt>0</dt><dd>Constant
 * <dt>-1</dt><dd>Decreasing
 * <dt>0</dt><dd>Increasing
 *</dl>
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> is monotonuous, <tt>FALSE</tt> otherwise.
 */
   CATBoolean IsMonotone(const CATMathInterval           & iD           ,
                               CATLONG32                 & ioType       ,
                         const CATTolerance              & iTolObject   = CATGetDefaultTolerance(),
                               CATMathAttrScaleOption   *  iScaleOption = NULL,
                               CATSoftwareConfiguration *  iConfig      = NULL
                        ) const;
  /** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
  
  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
/** 
 * Evaluates <tt>this</tt> CATMathPolynomX from values defined by an interval.
 * @param x
 * The interval containing the input values.
 * @return
 * The interval containing the values of <tt>this</tt> CATMathPolynomX.
 */
  virtual CATMathInterval Eval(const CATMathInterval & x) const;
/** 
 * Evaluates the first derivative of <tt>this</tt> CATMathPolynomX from values defined by an interval.
 * @param x
 * The interval containing the input values.
 * @return
 * The interval containing the values of the first derivative.
 */
  virtual CATMathInterval EvalFirstDeriv (const CATMathInterval & x) const;
 /** 
 * Evaluates the second derivative of <tt>this</tt> CATMathPolynomX from values defined by an interval.
 * @param x
 * The interval containing the input values.
 * @return
 * The interval containing the values of the second derivative.
 */
  virtual CATMathInterval EvalSecondDeriv(const CATMathInterval & x) const;
/** 
 * Evaluates the third derivative of <tt>this</tt> CATMathPolynomX from values defined by an interval.
 * @param x
 * The interval containing the input values.
 * @return
 * The interval containing the values of the third derivative.
 */
  virtual CATMathInterval EvalThirdDeriv (const CATMathInterval & x) const;

  
  //
  // Computes a good bound on the image of an interval I using the decomposition in orthogonal polynomials
  //
 
   /** @nodoc */
  virtual CATMathInterval ComputeOptimalImage    (const CATMathInterval          & I            ,
                                                  const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
                                                        CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                        CATSoftwareConfiguration*  iConfig      = NULL
                                                 ) const;
  /** @nodoc */
  virtual CATMathInterval ComputeImageByChebychev(const CATMathInterval          & ix         ,
                                                  const CATTolerance             & iTolObject    = CATGetDefaultTolerance()) const;
  

  //-----------------------------------------------------------------
  // - Integrate
  //-----------------------------------------------------------------
   /** @nodoc */
  virtual double Integrate(const CATMathInterval & D, const double tol) const;

  //-----------------------------------------------------------------
  //- Derivative
  //-----------------------------------------------------------------
   /** @nodoc */
  CATMathFunctionX * CreateDeriv () const;
  

  //-----------------------------------------------------------------
  //- Solve
  //-----------------------------------------------------------------
   /** @nodoc */
  virtual CATMathDiagnostic Solve(const CATMathInterval & D,
                                        CATMathSetOfPointsND & roots,
                                  const CATMathAttrList * attributes=0,
                                        CATSoftwareConfiguration* iConfig=NULL
                                 ) const;

/** @nodoc */
  friend ExportedByYN000FUN ostream & operator << (ostream& os, CATMathPolynomX & p);


// Modify polynom p(t)into p(alpha*t)
   /** @nodoc */
  void ApplyScalingOnVariable               (const double & alpha);

// Modify polynom p(t)into p(t+beta) by shift value modification 
   /** @nodoc */
  void ApplyShiftOnVariable                 (const double & beta);

// Modify polynom p(t)into p(t+beta) by coefficients modification
   /** @nodoc */
  void ApplyFormalShiftOnVariable           (const double & beta);

// Modify polynom p(t)into p(alpha*t+beta) by shift value modification 
   /** @nodoc */
  void ApplyLinearChangeOnVariable          (const double & alpha,const double & beta) ;

// Modify polynom p(t)into p(alpha*t+beta) by coefficients modification
   /** @nodoc */
  void ApplyFormalLinearChangeOnVariable    (const double & alpha,const double & beta) ;

// returns the polynom q(t)=p(alpha*t)
   /** @nodoc */
  CATMathPolynomX ScaleVariable             (const double & alpha) const;

// returns the polynom q(t)=p(t+beta) by shift value modification 
   /** @nodoc */
  CATMathPolynomX ShiftVariable             (const double & beta) const;
// returns the polynom q(t)=p(t+beta) by coefficients modification
   /** @nodoc */
  CATMathPolynomX FormalShiftVariable       (const double & beta) const;

// returns the polynom q(t)=p(alpha*t+beta) by shift value modification 
   /** @nodoc */
  CATMathPolynomX LinearChangeVariable      (const double & alpha,
                                             const double & beta) const;

// returns the polynom q(t)=p(alpha*t+beta) by coefficients modification
   /** @nodoc */
  CATMathPolynomX FormalLinearChangeVariable(const double & alpha,
                                             const double & beta) const;

// return 1 if P( startP+ t * (endP-startP) ) = Q( startQ+ t * (endQ-startQ))
// with tolerance tol on coefficients, 0 else
   /** @nodoc */
  friend ExportedByYN000FUN
  CATBoolean      IsConjuguate              (const CATMathPolynomX & P,
                                             const double          & startP,
                                             const double          & endP,
                                             const CATMathPolynomX & Q,
                                             const double          & startQ,
                                             const double          & endQ,
                                             const double            tol);


  //-----------------------------------------------------------------
  // Formal Treatment of polynoms (friend functions)
  // WARNING : all these functions return pointers, the corresponding
  //           objects must be DELETED afterwards.
  //-----------------------------------------------------------------

  //- Derivatives and primitive
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * FirstDeriv (const CATMathPolynomX * p);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * SecondDeriv(const CATMathPolynomX * p);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * ThirdDeriv (const CATMathPolynomX * p);
   /** @nodoc */
  // see forward
  friend ExportedByYN000FUN CATMathPolynomX * Primitiv   (const CATMathPolynomX * p,
                                                          const double c           );

  // Derivatives with a result already allocated

   /** @nodoc */
  friend ExportedByYN000FUN void              FirstDeriv (const CATMathPolynomX * p      ,
                                                                CATMathPolynomX * oResult);
   /** @nodoc */
  friend ExportedByYN000FUN void              SecondDeriv(const CATMathPolynomX * p      ,
                                                                CATMathPolynomX * oResult);

  // opposite : -pol
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Opposite   (const CATMathPolynomX * pol    );

  // sum with a double : pol + alpha
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Sum        (const CATMathPolynomX * pol    , const double            alpha  );
  // sum of two polynomials : pol1 + pol2
  /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Sum        (const CATMathPolynomX * pol1   , const CATMathPolynomX * pol2   );

  // difference with a double : pol - alpha
  /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Difference (const CATMathPolynomX * pol    , const double            alpha);

  // difference with a double : alpha - pol
  /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Difference (const double            alpha  , const CATMathPolynomX * pol);

  // difference of two polynomials : pol1-pol2
  /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Difference (const CATMathPolynomX * pol1   , const CATMathPolynomX * pol2);

  // product by a double : alpha * pol
  /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Product    (const CATMathPolynomX * pol    , const double            alpha);

  // product of two polynomials : pol1 * pol2
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Product    (const CATMathPolynomX * pol1   , const CATMathPolynomX * pol2);
  // product of two polynomials with a result already allocated
   /** @nodoc */
  friend ExportedByYN000FUN void              Product    (const CATMathPolynomX * pol1   , const CATMathPolynomX * pol2,
                                                                CATMathPolynomX * oResult);


  // square of a polynomial : pol^2
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Square     (const CATMathPolynomX * pol);

  // square of a polynomial with a result already allocated
   /** @nodoc */
  friend ExportedByYN000FUN void              Square     (const CATMathPolynomX * pol,
                                                                CATMathPolynomX * oResult);


  // linear combination : alpha1 * pol1 + alpha2 * pol2
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Combination(const CATMathPolynomX * pol1  ,
                                                          const CATMathPolynomX * pol2  ,
                                                          const double            alpha1,
                                                          const double            alpha2 );
  // linear combination : alpha1 * pol1 + beta * pol2 + alpha3 * pol3  
/** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX * Combination(const CATMathPolynomX * pol1  ,
                                                          const CATMathPolynomX * pol2  ,
                                                          const CATMathPolynomX * pol3  ,
                                                          const double            alpha1,
                                                          const double            alpha2 ,
                                                          const double            alpha3);
  

//
//- Overloaded operators
//
/** @nodoc */
                            CATMathPolynomX & operator =     (const CATMathPolynomX & p);
   /** @nodoc */
                            CATMathPolynomX   operator -     ();
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator +     (const CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator +     (const double          & a, const CATMathPolynomX & p);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator +     (const CATMathPolynomX & p, const double          & a);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator -     (const CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator -     (const double          & a, const CATMathPolynomX & p);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator -     (const CATMathPolynomX & p, const double          & a);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator *     (const CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator *     (const double          & a, const CATMathPolynomX & p);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator *     (const CATMathPolynomX & p, const double          & a);
   /** @nodoc */
  friend ExportedByYN000FUN CATMathPolynomX   operator /     (const CATMathPolynomX & p, const double          & a);
/** @nodoc */
  friend ExportedByYN000FUN void              operator +=    (      CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN void              operator +=    (      CATMathPolynomX & p, const double          & a);
   /** @nodoc */
  friend ExportedByYN000FUN void              operator -=    (      CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN void              operator -=    (      CATMathPolynomX & p, const double          & a);
   /** @nodoc */
  friend ExportedByYN000FUN void              operator *=    (      CATMathPolynomX & p, const CATMathPolynomX & q);
   /** @nodoc */
  friend ExportedByYN000FUN void              operator *=    (      CATMathPolynomX & p, const double          & a);

  // protected datas
 protected:
                             /** @nodoc */
  CATLONG32 _degree;
                             /** @nodoc */
  double  * _coeff;

                             /** @nodoc */
  CATLONG32 _nbcoeff;
  #ifdef CATPolynomXR19NbStaticCoeff
  double _staticcoeff_nodirectaccess[CATPolynomXR19NbStaticCoeff];
  #endif

                             /** @nodoc */
  double _Shift;

                             /** @nodoc */
  virtual CATMathFunctionX * FormalCompositionX(const CATMathFunctionX  * iF) const;

                             /** @nodoc */
  virtual CATMathFunctionX * FormalCombination (const CATLONG32           iN       ,
                                                const CATMathFunctionX ** iFunc    ,
                                                const double            * iCoef    , 
                                                const double              iConstant) const;

                             /** @nodoc */
  void NeedCoeffForDegree(const CATLONG32 degree);

 public:
// Takes the a_i's such that P(x) = sum a_i T_i(x) and returns the b_i's such that P(x) = sum b_i x^i
// where the T_i's are Chebyshev's polynomials
// N is the size of the arrays, it must be <= CHEBY_MAXDEGX+1 (=16)
                             /** @nodoc */
  static void ChebyshevToCanonical(const double * a, double * b, CATLONG32 N);

 private:



 friend CATBoolean ShiftCheck (const double iShift1, const double iShift2);

};

//----------------------------------------------------------------------------------------------------------------------------
// Forward declaration of friend functions
// (duplication here with default argument values for standard declaration on all platforms)
//----------------------------------------------------------------------------------------------------------------------------

/** @nodoc */
ExportedByYN000FUN CATMathPolynomX * Primitiv  (const CATMathPolynomX         *  p           , 
                                                const double                     c           = 0);

ExportedByYN000FUN CATBoolean        IsMonotone(const CATMathPolynomX         *  iPolynom    ,
                                                const CATMathInterval          & iD          ,
                                                      CATLONG32                & ioType      ,
                                                const CATTolerance             & iTolObject  ,
                                                      CATMathAttrScaleOption  *  iScaleOption,
                                                      CATSoftwareConfiguration*  iConfig
                                               ) ;


#endif
