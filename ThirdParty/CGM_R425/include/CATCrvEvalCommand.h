#ifndef CATCrvEvalCommand_H
#define CATCrvEvalCommand_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
#include "CATDataType.h"
#include "CATMathInline.h"


//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
/**
 * Class representing a command for computing a multiple evaluation 
 * on points of a CATCurve.
 *<br>The evaluation is
 * performed by the <tt>Eval</tt> method of the CATCurve interface and results 
 * are handled by the <tt>CATCrvEvalLocal</tt> class.
 * <br>Basic evaluators can be directly used as in the following examples:
 *<pre>
 * CATCrvEvalLocal EvalResult;
 * CATCrvParam Parameter ;
 * Curve->GetStartLimit(Parameter) ;
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalPoint                , EvalResult) ; // Evaluate point
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalFirstDerivative      , EvalResult) ; // Evaluate first  derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalSecondDerivative     , EvalResult) ; // Evaluate second derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalThirdDerivative      , EvalResult) ; // Evaluate third  derivative
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToFirstDerivative  , EvalResult) ; // Evaluate all    derivatives up to first  derivative 
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToSecondDerivative , EvalResult) ; // Evaluate all    derivatives up to second derivative 
 * Curve->Eval(Parameter, CATCrvEvalCommand::EvalUpToThirdDerivative  , EvalResult) ; // Evaluate all    derivatives up to third  derivative 
 * </pre>
 * The evaluation types are not exclusive. You can ask for other types
 * by using the <tt>Order</tt> method, or put the command to 
 *<tt>No Evaluation</tt> with the <tt>Reset</tt> method. 
 * @see CATCurve, CATCrvEvalLocal, CATCrvEvalResult
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATCrvEvalCommand
/*
#else
class ExportedByYP00IMPL CATCrvEvalCommand
#endif  
*/
{
public:
//=============================================================================
// GENERAL DEFINITIONS
//=============================================================================
/**
 * The command for the evaluation (3D point) of a point on a curve.
 */
  static const  CATCrvEvalCommand EvalPoint; 
 /**
 * The command for the evaluation of the curve first derivative only.
 */
  static const  CATCrvEvalCommand EvalFirstDerivative; 
  /**
 * The command for the evaluation of the curve second derivative only.
 */
  static const  CATCrvEvalCommand EvalSecondDerivative; 
  /**
 * The command for the evaluation of the curve third derivative only.
 */
  static const  CATCrvEvalCommand EvalThirdDerivative; 
  /**
 * The command for all the evaluations of the curve up to the first derivative.
 */
  static const  CATCrvEvalCommand EvalUpToFirstDerivative; 
    /**
 * The command for all the evaluations of the curve up to the second derivative.
 */
  static const  CATCrvEvalCommand EvalUpToSecondDerivative; 
    /**
 * The command for all the evaluations of the curve up to the third derivative.
 */
  static const  CATCrvEvalCommand EvalUpToThirdDerivative; 


/** @nodoc */
  enum Evaluations
    {
      Point        = 0,
      FirstDeriv   = 1,
      SecondDeriv  = 2,
      ThirdDeriv   = 3
    };

  /** @nodoc   */
  enum {CountEval   = 4 }; 


//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs a command with no specified evaluation.
 */
  INLINE CATCrvEvalCommand();

/**
 * Copy constructor.
 */
  INLINE CATCrvEvalCommand(const CATCrvEvalCommand &iCommandToCopy);


/**
 * @nodoc
 * Deprecated.
 */
  CATCrvEvalCommand(CATLONG32 );

//=============================================================================
// SET AND GET METHODS
//=============================================================================

/**
 * Resets all the specified evaluations on a CATCurve.
 *<br>After this, no evaluation will be performed on the curve.
 */
  INLINE void Reset();

/**
 * Adds the point evaluation to <tt>this</tt> CATCrvEvalCommand.
 */
  INLINE void OrderEvalPoint();

/**
 * Adds the first derivative evaluation to <tt>this</tt> CATCrvEvalCommand.
 */
  INLINE void OrderEvalFirstDeriv();

/**
 * Adds the second derivative evaluation to <tt>this</tt> CATCrvEvalCommand.
 */
  INLINE void OrderEvalSecondDeriv();

/**
 * Adds the third derivative evaluation to <tt>this</tt> CATCrvEvalCommand.
 */
  INLINE void OrderEvalThirdDeriv();


/**
 * Adds a specified evaluation to <tt>this</tt> CATCrvEvalCommand.
 * @nodoc
 * @param iAskedEvaluation
 * The required evaluation.
 */
  INLINE void OrderEval(Evaluations iAskedEvaluation);

//------------------------------------------------------------
// Get the orders on the command
//------------------------------------------------------------ 
/**
 * Tests whether the point evaluation belongs to <tt>this</tt> CATCrvEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalPoint()       const;
  
/**
 * Tests whether the first derivative evaluation belongs to <tt>this</tt> CATCrvEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalFirstDeriv()  const;
  
/**
 * Tests whether the second derivative evaluation belongs to <tt>this</tt> CATCrvEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalSecondDeriv() const;
  
/**
 * Tests whether the third derivative evaluation belongs to <tt>this</tt> CATCrvEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalThirdDeriv()  const;
  
/**
 * Tests whether a specified evaluation belongs to <tt>this</tt> CATCrvEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values:</b>
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEval(Evaluations iTestEvaluation) const;

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Internal data is a CATLONG32 and is used with masks
  CATLONG32 _Flags;
/** @nodoc */
  enum Commands
    { 
      ResetFlag                = 0,
      EvalPointFlag            = 1,
      EvalFirstDerivativeFlag  = 2,
      EvalSecondDerivativeFlag = 4,
      EvalThirdDerivativeFlag  = 8
      }; 
// Array for conversion of value Evaluations to Flag
/** @nodoc */
  static const Commands sFlagsForEval[CountEval];

};


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATCrvEvalCommand::CATCrvEvalCommand()
{
  _Flags= EvalPointFlag;
}

INLINE CATCrvEvalCommand::CATCrvEvalCommand(const CATCrvEvalCommand &Command)
{
  _Flags=Command._Flags;
}


INLINE void CATCrvEvalCommand::Reset()
{
  _Flags= ResetFlag;
}

INLINE void CATCrvEvalCommand::OrderEvalPoint()
{
  _Flags  |= EvalPointFlag;
}

INLINE void CATCrvEvalCommand::OrderEvalFirstDeriv()
{
  _Flags  |= EvalFirstDerivativeFlag;
}

INLINE void CATCrvEvalCommand::OrderEvalSecondDeriv()
{
  _Flags  |= EvalSecondDerivativeFlag;
}

INLINE void CATCrvEvalCommand::OrderEvalThirdDeriv()
{
  _Flags  |= EvalThirdDerivativeFlag;
}

// Ask for a special evaluation
INLINE void CATCrvEvalCommand::OrderEval(Evaluations AskedEvaluation)
{
  _Flags |= sFlagsForEval[AskedEvaluation];
}

//------------------------------------------------------------
// Return what is ordered
//------------------------------------------------------------
INLINE CATLONG32 CATCrvEvalCommand::IsSetToEvalPoint() const
{
  return (_Flags & EvalPointFlag) ? 1 : 0;
}

INLINE CATLONG32 CATCrvEvalCommand::IsSetToEvalFirstDeriv() const
{
  return (_Flags & EvalFirstDerivativeFlag) ? 1 : 0;
}


INLINE CATLONG32 CATCrvEvalCommand::IsSetToEvalSecondDeriv() const
{
  return (_Flags & EvalSecondDerivativeFlag) ? 1 : 0;
}

INLINE CATLONG32 CATCrvEvalCommand::IsSetToEvalThirdDeriv() const
{
  return (_Flags & EvalThirdDerivativeFlag) ? 1 : 0;
}

INLINE CATLONG32 CATCrvEvalCommand::IsSetToEval(Evaluations Eval) const
{
  return ( _Flags & (sFlagsForEval[Eval])) ? 1 : 0;
}

#endif
