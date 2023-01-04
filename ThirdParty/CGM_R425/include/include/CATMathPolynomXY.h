#ifndef CATMathPolynomXY_H
#define CATMathPolynomXY_H
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 
#include "CATIACGMLevel.h"

#include "YN000FUN.h"
#include "CATMathFoundationXY.h"
#include "CATMathInterval.h"
#include "CATMathPolynomX.h"
#include "CATMathDef.h"

#include "CATTolerance.h"

#ifdef CATIACGMV5R21
#include "CATMathInline.h"
#endif

class CATMathIntervalND;
class CATMathStream;
class CATMathAttrScaleOption;

#ifndef CATIACGMV5R21
// activated R19, deactivated R21 to save memory for massive degree 3 polynom use
#define CATPolynomXYR19NbStaticCoeff 36
#endif

#if defined(_WINDOWS_SOURCE) && defined(_M_IX86)
/** @nodoc */
#define CATMUTABLE mutable
#else
#define CATMUTABLE
#endif

/**
 * Class defining the real polynom of two variables.
 */
class ExportedByYN000FUN CATMathPolynomXY : public CATMathFoundationXY
{
 public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  //-----------------------------------------------------------------
  // Constructors
  //-----------------------------------------------------------------
  /**
    * Copy constructor.
    */
  CATMathPolynomXY(const CATMathPolynomXY & iToCopy);
 
   /**
    * Constructs a CATMathPolynomXY from a double entry array.
    * @param iDegX
    * The degree in the first variable
    * @param iDegY
    * The degree in the second variable.
    * @param iCoeff
    * The double entry array such that: 
    * <br><tt>pol=Sum_{i=0..iDegX, j=0..iDegY}  iCoeff[i][j] X^i Y^j</tt>.
     * @param iShiftX, iShiftY
     * Internal use.
    */
  CATMathPolynomXY(const CATLONG32 iDegX, const CATLONG32 iDegY, double **iCoeff, 
                   const double iShiftX=0., const double iShiftY=0.);
   /**
    * Constructs a CATMathPolynomXY from an array.
    * @param iDegX
    * The degree in the first variable
    * @param iDegY
    * The degree in the second variable.
    * @param iCoeff
    * The array such that: 
    * <br><tt>pol=Sum_{i=0..iDegX, j=0..iDegY}  iCoeff[i*(degY+1)+j] X^i Y^j</tt>.
    */
  CATMathPolynomXY(const CATLONG32 iDegX = 0, const CATLONG32 iDegY = 0, 
                   const double *iCoeff = 0,
                   const double iShiftX=0., const double iShiftY=0.);
  virtual ~CATMathPolynomXY();


  //-----------------------------------------------------------------
  // Set Global
  //-----------------------------------------------------------------
  /**
   * Modifies the coefficients of <tt>this</tt> CATMathPolynomXY.
     * @param iDegX
    * The degree in the first variable
    * @param iDegY
    * The degree in the second variable.
    * @param iCoef
    * The double entry array such that: 
    * <br><tt>pol=Sum_{i=0..iDegX, j=0..iDegY}  iCoeff[i][j] X^i Y^j</tt>.
   */
  void SetCoefficients(const CATLONG32 iDegX, const CATLONG32 iDegY, double **iCoef);

      /**
    * Modifies the coefficients of <tt>this</tt> CATMathPolynomXY.
    * @param iDegX
    * The degree in the first variable
    * @param iDegY
    * The degree in the second variable.
    * @param iCoef
    * The array such that: 
    * <br><tt>pol=Sum_{i=0..iDegX, j=0..iDegY}  iCoef[i*(degY+1)+j] X^i Y^j</tt>.
    */
  void SetCoefficients(const CATLONG32 iDegX = 0, const CATLONG32 iDegY = 0,
                       const double *iCoef = 0);
  //-----------------------------------------------------------------
  // Information methods
  //-----------------------------------------------------------------
#ifdef CATIACGMV5R21
  /**
    * From V5R21, returns the degree in the first variable.
    * @return
    * The degree.
    */

  INLINE CATLONG32 GetDegreeX() const;
#else
  /**
    * Up to V5R20, returns the degree in the first variable.
    * @return
    * The degree.
    */

  CATLONG32 GetDegreeX() const;
#endif



#ifdef CATIACGMV5R21
   /**
    * From V5R21, returns the degree in the second variable.
    * @return
    * The degree.
    */
  INLINE CATLONG32 GetDegreeY() const;
#else
   /**
    * Up to V5R20, returns the degree in the second variable.
    * @return
    * The degree.
    */
  CATLONG32 GetDegreeY() const;
#endif

  /**
  * Tests whether <tt>this</tt> CATMathPolynomXY derives from a class (given by its name).
  * @param iClassId
  * The name of the class.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathPolynomXY is a kind of <tt>iClassId</tt>,
  * <tt>FALSE</tt> otherwise.
  */
  CATBoolean IsAKindOf(const CATMathClassId iClassId) const;

#ifdef CATIACGMV5R21
  /**
  * Tests if <tt>this</tt> CATMathPolynomXY derives from a class (given by a numerical value).
  * @param iType
  * The numerical value representing the class type.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CATMathPolynomXY is a type of <tt>iType</tt>,
  * <tt>FALSE</tt> otherwise.
  */
  CATBoolean IsATypeOf(const CATMathFunctionXYTypeId iType) const;
#endif

      /**
 * Tests whether an evaluator is available for <tt>this</tt> CATMathPolynomXY.
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
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the evaluation is available for <tt>this</tt> CATMathPolynomXY,
 * <tt>FALSE</tt> otherwise.
 */
  CATBoolean IsOption(const CATMathOption iOption) const;

   /**
 * Returns the class name of <tt>this</tt>  CATMathPolynomXY.
 * @return
 * A pointer to the name <tt>CATMathPolynomX</tt>.
 */
  CATMathClassId IsA() const;

/**
 * Returns the coefficients of <tt>this</tt> CATMathPolynomXY.
 * @return
 * The array of the coefficients. As part of <tt>this</tt>, it must not be deallocated.
 */
  const double * GetCoefficients() const;

  //-----------------------------------------------------------------
  // Evaluators on doubles
  //-----------------------------------------------------------------
/** 
 * Evaluates <tt>this</tt> CATMathPolynomXY.
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The result of the evaluation.
 */
  virtual double Eval(const double & iX, const double & iY) const;

   /** 
 * Evaluates the first partial derivative with respect to the first variable of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the first variable.
 */
  virtual double EvalFirstDerivX(const double & iX, const double &iY) const;
   /** 
 * Evaluates the first partial derivative with respect to the second variable of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the first partial derivative with respect to the second variable.
 */
  virtual double EvalFirstDerivY(const double & iX, const double & iY) const;

    /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivX2(const double & iX, const double & iY) const;
    /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivXY(const double & iX, const double & iY) const;
      /** 
 * Evaluates the second partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the second partial derivative.
 */
  virtual double EvalSecondDerivY2(const double & iX, const double & iY) const;
  
   /** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double EvalThirdDerivX3(const double & iX, const double & iY) const;
   /** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double EvalThirdDerivX2Y(const double & iX, const double & iY) const;
   /** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double EvalThirdDerivXY2(const double & iX, const double & iY) const;
   /** 
 * Evaluates the third partial derivative of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @return
 * The value of the third partial derivative.
 */
  virtual double EvalThirdDerivY3(const double & iX, const double & iY) const;

 /** 
 * Evaluates simultaneously the value, and all the first, second and third partial derivatives
 * of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param oF
 * The value of <tt>this</tt> CATMathPolynomXY.
 * @param oFx
 * The value of the first partial derivative of <tt>this</tt> CATMathPolynomXY. 
 * @param oFy
 * The value of the first partial derivative of <tt>this</tt> CATMathPolynomXY. 
 * @param oFx2
 * The value of the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFxy
 * The value of the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFy2
 * The value of the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFx3
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFx2y
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFxy2
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFy3
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 */
  virtual void EvalUpToThirdDeriv(const double iX, const double iY,
                                 double & oF, double & oFx,  double & oFy,
                          double & oFx2, double & oFxy, double & oFy2,
                          double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const; 
 /** 
 * Evaluates simultaneously all third partial derivatives
 * of <tt>this</tt> CATMathPolynomXY .
 * @param iX
 * The value of the first variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param iY
 * The value of the second variable where <tt>this</tt> CATMathPolynomXY is evaluated.
 * @param oFx3
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFx2y
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFxy2
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param oFy3
 * The value of the third partial derivative of <tt>this</tt> CATMathPolynomXY.
 */
  virtual void EvalAllThirdDerivs(const double iX, const double iY, double & oFx3, double & oFx2y, double & oFxy2, double & oFy3) const;
 /**
 * Simultaneously evaluates <tt>this</tt> CATMathPolynomXY or/and its partial derivatives.
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
 * A pointer to the value of <tt>this</tt> CATMathPolynomXY.
 * @param ioFx
 * A pointer to the first partial derivative of <tt>this</tt> CATMathPolynomXY. 
 * @param ioFy
 * A pointer to the first partial derivative of <tt>this</tt> CATMathPolynomXY. 
 * @param ioFx2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param ioFxy
 * A pointer to the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 * @param ioFy2
 * A pointer to the second partial derivative of <tt>this</tt> CATMathPolynomXY.
 */
   virtual void Eval(const double iX, const double iY, 
                     const CATMathOption iOptions,
                     double * ioF,
                     double * ioFx =0, double * ioFy=0,
                     double * ioFx2=0, double *ioFxy=0, double *ioFy2=0) const;
   
 /**
 * Simultaneously evaluates <tt>this</tt> CATMathPolynomXY or/and its partial derivatives 
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
 * The array of the evaluations of <tt>this</tt> CATMathPolynomXY.
 * @param ioFx
 * The array of the first partial derivative of <tt>this</tt> CATMathPolynomXY at the grid points. 
 * @param ioFy
 * The array of the first partial derivative of <tt>this</tt> CATMathPolynomXY at the grid points. 
 * @param ioFx2
 * The array of the second partial derivative of <tt>this</tt> CATMathPolynomXY at the grid points.
 * @param ioFxy
 * The array of the second partial derivative of <tt>this</tt> CATMathPolynomXY at the grid points.
 * @param ioFy2
 * The array of the second partial derivative of <tt>this</tt> CATMathPolynomXY at the grid points.
 */ 
   virtual void Eval(const CATMathIntervalND & iDomain, const CATLONG32 * NbPoints,
                     const CATMathOption iOptions,
                     double * ioF,
                     double * ioFx =0, double * ioFy=0,
                     double * ioFx2=0, double * ioFxy=0, double * ioFy2=0) const;












  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
   /** @nodoc */
  CATCGMNewClassArrayDeclare;


    /**
   * @nodoc
   * Modifies the Shift value.
   */
   void SetShiftX (const double iShiftX=0.);
    /**
   * @nodoc
   * Modifies the Shift value.
   */

   void SetShiftY (const double iShiftY=0.);
    /**
   * @nodoc
   * Modifies the Shift value.
   */

   void SetShiftXY (const double iShiftX=0., const double iShiftY=0. );
  /**
   * @nodoc
   * Perform the formal shift to set the Shift value to 0.
   */
  void CancelShifts ();


   /** @nodoc */
  int GetDirectComponents(const int iSizeOfComponents, const CATMathFunctionGeneral **ioComponents) const;
   /** @nodoc */
  CATMathFunctionXY * Duplicate() const;
   /** @nodoc */
  CATMathFunctionXY * DeepDuplicate() const ;
#if defined ( CATIACGMR216CAA )
   /** @nodoc */
  CATMathFunctionXY * DeepDuplicateWithTol(const CATTolerance *ipTolObject) const ;
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


    /**
   * @nodoc
   * Returns the Shift value.
   */
  double GetShiftX () const;

    /**
   * @nodoc
   * Modifies the Shift value.
   */
  double GetShiftY () const;


 private:
 /** @nodoc */
  CATLONG32 _degreeX, _degreeY;
 /** @nodoc */
  double * _coeff;
 /** @nodoc */
#ifndef CATIACGMV5R21
  //unused
  CATMUTABLE CATINTPTR *_CoeffAlloc;
#endif
 /** @nodoc */
  double _ShiftX, _ShiftY ;
  #ifdef CATPolynomXYR19NbStaticCoeff
  double _staticcoeff_nodirectaccess[CATPolynomXYR19NbStaticCoeff];
  #endif

 public:



  //-----------------------------------------------------------------
  // Evaluators on intervals
  //-----------------------------------------------------------------
   /** @nodoc */
   virtual CATMathInterval Eval(const CATMathInterval & Du,
     const CATMathInterval & Dv, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;

   /** @nodoc */
  virtual CATMathInterval EvalFirstDerivX(const CATMathInterval & Du,
                                          const CATMathInterval & Dv) const;
   /** @nodoc */
  virtual CATMathInterval EvalFirstDerivY(const CATMathInterval & Du,
                                          const CATMathInterval & Dv) const;  
   /** @nodoc */
  virtual CATMathInterval EvalSecondDerivX2(const CATMathInterval & Du,
                                            const CATMathInterval & Dv) const;
   /** @nodoc */
  virtual CATMathInterval EvalSecondDerivXY(const CATMathInterval & Du,
                                            const CATMathInterval & Dv) const;  
   /** @nodoc */
  virtual CATMathInterval EvalSecondDerivY2(const CATMathInterval & Du,
                                            const CATMathInterval & Dv) const;  
  
  /** @nodoc */
  virtual void Eval(const CATMathInterval & Du, const CATMathInterval & Dv,
    const CATMathOption iOptions,CATMathInterval * f,CATMathInterval * fx , 
    CATMathInterval * fy,CATMathInterval * fx2, CATMathInterval * fxy, 
    CATMathInterval * fy2, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;

  // Compute a quite good interval containing the image of (Du,Dv), thanks to chebychev transformation
   
  /** @nodoc */
  virtual CATMathInterval ComputeOptimalImage(const CATMathInterval          & Du           , 
                                              const CATMathInterval          & Dv           ,
                                              const CATTolerance             & iTolObject   = CATGetDefaultTolerance(),
#ifdef CATMathFunctionXYR24Interface
                                                    CATMathAttrScaleOption  *  iScaleOption = NULL,
                                                    CATSoftwareConfiguration*  iConfig      = NULL
#else
                                                    CATMathAttrScaleOption  *  iScaleOption = NULL
#endif
                                             ) const;
 /** @nodoc */
  virtual CATMathInterval ComputeImageByChebychev(const CATMathInterval & ix, const CATMathInterval & iy, const CATTolerance & iTolObject=CATGetDefaultTolerance()) const;

 

  /**
  * @nodoc
  *
  * MultiEvaluator of f and its derivative on a non regular grid :
  * Evaluation of 
  *                F[i*xNbPoints+j] = Eval(xPoints[i],yPoints[j]), ...
  */
  virtual void EvalGrid(CATLONG32 xNbPoints, const double * xPoints, CATLONG32 yNbPoints, const double * yPoints,
    const CATMathOption iOptions,
    double * ioF,
    double * ioFx =0, double * ioFy=0) const;

  /** @nodoc */
  virtual CATMathPolynomXY ProductXXtoXY(const CATMathPolynomX & PX, const CATMathPolynomX & PY) const;


  //-----------------------------------------------------------------
  // Formal Treatment of polynoms (friend functions)
  // WARNING : all these functions return pointers, the corresponding
  //           objects must be DELETED afterwards.
  //-----------------------------------------------------------------
  // polynomial of one variable q(y)=p(x,y) for x fixed
   /** @nodoc */
  CATMathFunctionX * CreateIsoparX(const double & x) const;
  // polynomial of one variable q(x)=p(x,y) for y fixed
   /** @nodoc */
  CATMathFunctionX * CreateIsoparY(const double & y) const;


  // formal derivation with respect to one variable
   /** @nodoc */
  CATMathFunctionXY * CreateDerivX() const;
   /** @nodoc */
  CATMathFunctionXY * CreateDerivY() const;


  // sum with a double : pol + alpha
   /** @nodoc */
friend ExportedByYN000FUN CATMathPolynomXY * 
   Sum(const CATMathPolynomXY * pol, const double & alpha);
  // sum of two polynomials : pol1 + pol2
/** @nodoc */
friend ExportedByYN000FUN CATMathPolynomXY * 
   Sum(const CATMathPolynomXY * pol1, const CATMathPolynomXY * pol2);

  // product by a double : alpha * pol
/** @nodoc */
friend ExportedByYN000FUN CATMathPolynomXY * 
   Product(const CATMathPolynomXY * pol, const double & alpha);

  // linear combination : alpha * pol1 + beta * pol2
/** @nodoc */
friend ExportedByYN000FUN CATMathPolynomXY * 
   Combination(const CATMathPolynomXY * pol1, const CATMathPolynomXY * pol2,
               const double & alpha, const double & beta);
  // linear combination : alpha * pol1 + beta * pol2 + gamma * pol3  
/** @nodoc */
friend ExportedByYN000FUN CATMathPolynomXY * 
   Combination(const CATMathPolynomXY * pol1,
               const CATMathPolynomXY * pol2,
               const CATMathPolynomXY * pol3,
               const double & alpha,
               const double & beta,
               const double & gamma);
  
  // overloading <<
/** @nodoc */ 
friend ExportedByYN000FUN ostream & 
   operator << (ostream& os, CATMathPolynomXY & p);
//
//- Overloaded operators
//
/** @nodoc */
  CATMathPolynomXY & operator = (const CATMathPolynomXY & p);
/** @nodoc */
  friend ExportedByYN000FUN void operator +=
    (CATMathPolynomXY & p, const CATMathPolynomXY & q);
   /** @nodoc */
  friend ExportedByYN000FUN void operator +=
    (CATMathPolynomXY & p, const double & a);
   /** @nodoc */
  friend ExportedByYN000FUN void operator -=
    (CATMathPolynomXY & p, const CATMathPolynomXY & q);
   /** @nodoc */
  friend ExportedByYN000FUN void operator -=
    (CATMathPolynomXY & p, const double & a);
   /** @nodoc */
  friend ExportedByYN000FUN void operator *=
    (CATMathPolynomXY & p, const double & a);
   /** @nodoc */ /* private; no export */
  friend void OperatorPlusEgalMoinsEgal_Private
    (CATMathPolynomXY & p, const CATMathPolynomXY & q, double SigneOperation) ;


//protected:
   /** @nodoc */
  virtual CATMathFunctionXY * FormalCombination(const CATLONG32 iN, 
                                                const CATMathFunctionXY ** iFunc,
                                                const double * iCoef, 
                                                const double iConstant) const;

private:

  CATMathInterval EvalIntervalSymX(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalIntervalPosX(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalIntervalNegX(const CATMathInterval & iDu, const CATMathInterval & iDv) const;

  CATMathInterval EvalFirstDerivXHiDegrees(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalFirstDerivXHiDegreesSub1(const CATMathInterval & Du, const CATMathInterval & Dv) const;
  CATMathInterval EvalFirstDerivXHiDegreesSub2(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivXHiDegreesSub3(const CATMathInterval & Du, const CATMathInterval & Dv) const; 

  CATMathInterval EvalFirstDerivXHiDegreesSym(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalFirstDerivXHiDegreesSymSub1(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivXHiDegreesSymSub2(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivXHiDegreesSymSub3(const CATMathInterval & Du, const CATMathInterval & Dv) const; 


  CATMathInterval EvalFirstDerivYHiDegrees(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalFirstDerivYHiDegreesSub1(const CATMathInterval & Du, const CATMathInterval & Dv) const;
  CATMathInterval EvalFirstDerivYHiDegreesSub2(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivYHiDegreesSub3(const CATMathInterval & Du, const CATMathInterval & Dv) const; 

  CATMathInterval EvalFirstDerivYHiDegreesSym(const CATMathInterval & iDu, const CATMathInterval & iDv) const;
  CATMathInterval EvalFirstDerivYHiDegreesSymSub1(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivYHiDegreesSymSub2(const CATMathInterval & Du, const CATMathInterval & Dv) const; 
  CATMathInterval EvalFirstDerivYHiDegreesSymSub3(const CATMathInterval & Du, const CATMathInterval & Dv) const; 



  void EvalFirstDeriv(const double u, const double v, double & fx, double & fy) const;
  void EvalAndFirstDeriv(const double u, const double v,
                         double & f, double & fx, double & fy) const;
  
  void EvalAndFirstAndSecondDeriv(const double u, const double v,
                                  double & f, double & fx, double & fy,
                                  double & fx2, double & fxy, double & fy2) const;

  void GridEval
     (const double uStart, const double uEnd, const double uDelta,
      const double vStart, const double vEnd, const double vDelta,
      const CATLONG32 Nu, const CATLONG32 Nv,
      double * f) const;

  void GridEvalFirstDeriv
     (const double uStart, const double uEnd, const double uDelta,
      const double vStart, const double vEnd, const double vDelta,
      const CATLONG32 Nu, const CATLONG32 Nv,
      double * fx, double * fy) const;

  void GridEvalAndFirstDeriv
     (const double uStart, const double uEnd, const double uDelta,
      const double vStart, const double vEnd, const double vDelta,
      const CATLONG32 Nu, const CATLONG32 Nv,
      double * f, double * fx, double * fy) const;

  void GridEvalAndFirstAndSecondDeriv
     (const double uStart, const double uEnd, const double uDelta,
      const double vStart, const double vEnd, const double vDelta,
      const CATLONG32 Nu, const CATLONG32 Nv,
      double * f, double * fx, double * fy, 
      double * fx2, double * fxy, double * fy2) const;
  
  void EvalAndFirstDeriv(const CATMathInterval & Du, const CATMathInterval & Dv,
                         CATMathInterval & f, CATMathInterval & fx, CATMathInterval & fy) const;
  
  void EvalAndFirstAndSecondDeriv(const CATMathInterval & Du, const CATMathInterval & Dv,
                                  CATMathInterval & f, CATMathInterval & fx, CATMathInterval & fy,
                                  CATMathInterval & fx2, CATMathInterval & fxy, 
                                  CATMathInterval & fy2) const;


  friend CATBoolean ShiftCheck (const double iShiftX1, const double iShiftX2,
    const double iShiftY1, const double iShiftY2);


  // Internal use only
  // Method used to perform internally a deep Horner scheme so as to compute all values of current
  // polynom up to third derivatives.
  // Be careful: some values returned must be re-scaled, for instance:
  //    d2P / dx^2 = 2. * oFx2by2.
  //    d3P / dx^3 = 6. * oFx3by6.
  void HornerSchemeUpToThird(const double & iX, const double & iY,
                              double & oF, double & oFx,  double & oFy,
                                     double & oFx2by2, double & oFxy, double & oFy2by2,
                                     double & oFx3by6, double & oFx2yby2, double & oFxy2by2, double & oFy3by6) const;

public:
// Modify polynomial p(u,v) into p(alpha*u,beta*v);
    /** @nodoc */
  void ApplyScalingOnVariables(const double & alpha, const double & beta);

//#ifdef CATIAV5R14
// Modify polynom p(t,u)into p(t+beta,u+gamma) by coefficients modification
   /** @nodoc */
  void ApplyFormalShiftOnVariable(const double & betaX,const double & betaY);
//#endif

};

#ifdef CATIACGMV5R21
INLINE CATLONG32 CATMathPolynomXY::GetDegreeX() const
 {
  return _degreeX;
 };
INLINE CATLONG32 CATMathPolynomXY::GetDegreeY() const
 {
  return _degreeY;
 };
#endif

#endif
