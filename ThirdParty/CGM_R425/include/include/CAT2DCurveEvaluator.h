//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2017
//=============================================================================
// CAT2DCurveEvaluator :
// Function from R to R2, thus representing a curve in 2D.
//=============================================================================
// 03/02/17 F1Z : Creation
// 24/03/17 F1Z : Add the possibility to add a current domain.
// 27/03/17 F1Z : Add the possibility to duplicate the curve.
// 22/08/18 JSX : Remove duplication method
// 17/04/20 F4E : Add IsBuildFromAccurate()
// 09/02/21 Q48 : Add ComputeLength
// 09/02/21 Q48 : Remove SetCurDomain (available in CATBasis2DCurveEvaluator)
// 12/10/21 Q48 : Begin to remove GetCurDomain / GetMaxDomain methods
// 12/10/21 Q48 : Remove EvalDistortion (unused)
// DD/MM/YY
//=============================================================================
// Note: Can be moved into advanced mathematics

#ifndef CAT2DCurveEvaluator_H
#define CAT2DCurveEvaluator_H

// C++ 11
//#include "CATGeoOpVirtual.h"
#include "CATMathVirtual.h"

// Special API
#include "CATSysErrorDef.h"
#include "CATBoolean.h"

// Mathematics
#include "CATMathConstant.h"
#include "CATMathDef.h"

// GMModelInterfaces
#include "CATGMModelInterfaces.h"

// Temp
#include "CATCivilCurveArchiTEMP.h"

class CATMathPoint2D;
class CATMathVector2D;

class ExportedByCATGMModelInterfaces CAT2DCurveEvaluator
{
public:
  //-----------------------------------------------------------------------
  //- Object Management
  //-----------------------------------------------------------------------
  
  CAT2DCurveEvaluator();
  virtual ~CAT2DCurveEvaluator();

  //-----------------------------------------------------------------------
  //- Information
  //-----------------------------------------------------------------------
  /**
  * Returns the class name of <tt>this</tt>  CAT2DCurveEvaluator.
  * @return
  * A pointer to the class name.
  */
  virtual CATMathClassId IsA() const;

  /**
  * Tests if <tt>this</tt> CAT2DCurveEvaluator derives from a class (given by its name).
  * @param iClassId
  * The name of the class.
  * @return
  * The result of the test.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if <tt>this</tt> CAT2DCurveEvaluator is a kind of <tt>iClassId</tt>,
  * <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsAKindOf(const CATMathClassId iClassId) const;

  /**
  * Tests if an evaluator is available for <tt>this</tt> CAT2DCurveEvaluator.
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
  * <br><b>Legal values</b>: <tt>TRUE</tt> if the evaluation is available for <tt>this</tt> CAT2DCurveEvaluator,
  * <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean IsOption (const CATMathOption iOption) const = 0;

  //-----------------------------------------------------------------------
  //- Domain
  //-----------------------------------------------------------------------

#ifndef Q48_RemoveSetDomain
  /**
  * Set the current domain.
  * @return
  * S_OK if the provided limits are inside the max domain, S_FALSE otherwise (and the given limits are not set)
  */
  virtual HRESULT   SetCurDomain (const double            iStart      ,
                                  const double            iEnd        )       = 0;
#endif

#ifndef Q48_RemoveGetCurDomain
  /**
  * Return the current domain.
  */
  virtual HRESULT   GetCurDomain (      double          & oStart      ,
                                        double          & oEnd        ) const CATMathFinal;
#endif

#ifndef Q48_RemoveGetMaxDomain
  /**
  * Return the domain where the curve can be evaluated.
  */
  virtual HRESULT   GetMaxDomain (      double          & oStart      ,
                                        double          & oEnd        ) const CATMathFinal;
#endif

  virtual HRESULT GetDomain(double & oDomainLow,
                            double & oDomainUpp) const = 0;

  virtual CATBoolean IsBuiltFromAccurate() const;


  //-----------------------------------------------------------------------
  //- Eval - Function
  //-----------------------------------------------------------------------

   virtual HRESULT Eval           (const double            iT          ,
                                         double            oPt      [2]) const = 0;

   virtual HRESULT EvalFirstDeriv (const double            iT          ,  
                                         double            oTgt     [2]) const = 0;

   virtual HRESULT EvalSecondDeriv(const double            iT          , 
                                         double            oSec     [2]) const = 0;

   virtual HRESULT EvalThirdDeriv (const double            iT          ,  
                                         double            oThird   [2]) const = 0;

  //-----------------------------------------------------------------------
  //- Eval - 2DCurve
  //-----------------------------------------------------------------------

  virtual HRESULT EvalPoint      (const double            iT          ,
                                        CATMathPoint2D    & oPt        ) const = 0;

  virtual HRESULT EvalTangent    (const double            iT          ,
                                        CATMathVector2D & oTgt        ) const = 0;

  virtual HRESULT EvalCurvature  (const double            iT          ,
                                        CATMathVector2D & oCurv       ) const = 0;

  virtual HRESULT EvalCurvature  (const double            iT          ,
                                        double          & oCurv       ) const = 0;

  //virtual HRESULT EvalDistortion (const double             iT         ,
  //                                      double           & oDistortion) const = 0;

  //-----------------------------------------------------------------------
  //- Utilities
  //-----------------------------------------------------------------------
  
  /**
  * Compute the integral along the curve between iMin and iMax
  */
  virtual HRESULT ComputeLength(const double   iMin,
                                const double   iMax,
                                      double & oLength) const = 0;
};
#endif
