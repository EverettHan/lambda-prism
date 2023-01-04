#ifndef CATSurEvalCommand_H
#define CATSurEvalCommand_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
#include "CATDataType.h"
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATMathInline.h"

/**
 * Class representing a command for computing a multiple evaluation 
 * on points of a CATSurface.
 *<br>The evaluation types are not exclusive. You can ask for other types
 * by using the <tt>Order</tt> method, or put the command to 
 *<tt>No Evaluation</tt> with the <tt>Reset</tt> method. The evaluation is
 * performed by the <tt>Eval</tt> method of the CATSurface interface and results 
 * are handled by the <tt>CATSurEvalLocal</tt> class.
 * <br>Example:
 *<pre>
 * CATSurEvalLocal EvalResult;
 * CATSurEvalCommand Command;
 * Command.OrderEvalPoint();
 * Command.OrderFirstDeriv();
 * CATSurParam Parameter ;
 * Surface->GetStartLimit(Parameter) ;
 * Surface->Eval(Parameter, Command, EvalResult) ; // Evaluate point and first derivatives.
 * </pre>
 * @see CATSurface, CATSurEvalLocal, CATSurEvalResult
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSurEvalCommand
/*
#else
class ExportedByYP00IMPL CATSurEvalCommand
#endif  
*/
{
public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs a command with no specified evaluation.
 */
  INLINE CATSurEvalCommand();

/**
 * Copy constructor.
 */
  INLINE CATSurEvalCommand(const CATSurEvalCommand &iCommandToCopy);

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * Resets all the specified evaluation on a CATSurface.
 *<br>After this, no evaluation will be performed with this command.
 */
  INLINE void Reset();

/**
 * Adds the point evaluation to <tt>this</tt> CATSurEvalCommand.
 */
  INLINE void OrderEvalPoint();

/**
 * Adds the first derivatives evaluation to <tt>this</tt> CATSurEvalCommand.
 */
  INLINE void OrderEvalFirstDeriv();

/**
 * Adds the normal evaluation to <tt>this</tt> CATSurEvalCommand.
 */
  INLINE void OrderEvalNormal();

/**
 * Adds the second derivatives evaluation to <tt>this</tt> CATSurEvalCommand.
 */
  INLINE void OrderEvalSecondDeriv();

/**
 * Adds the third derivatives evaluation to <tt>this</tt> CATSurEvalCommand.
 */
  INLINE void OrderEvalThirdDeriv();

//------------------------------------------------------------
// Get the orders on the command
//------------------------------------------------------------
/**
 * Tests whether the point evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */

  INLINE CATLONG32 IsSetToEvalPoint()       const;
  
/**
 * Tests whether the first derivatives evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalFirstDeriv()  const;

/**
 * Tests whether the normal evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalNormal()      const;

/**
 * Tests whether the second derivatives evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalSecondDeriv() const;

/**
 * Tests whether the third derivatives evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalThirdDeriv()  const;

/** @nodoc */
  enum Evaluations
    {
      Point          = 0,
      FirstDerivU    = 1,
      FirstDerivV    = 2,
      Normal         = 3,
      SecondDerivU2  = 4,
      SecondDerivUV  = 5,
      SecondDerivV2  = 6,
      ThirdDerivU3   = 7,
      ThirdDerivU2V  = 8,
      ThirdDerivUV2  = 9,
      ThirdDerivV3   = 10
    };

/**
 * Tests whether a specified evaluation belongs to <tt>this</tt> CATSurEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEval(Evaluations iTestEvaluation) const;






  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //               N O N - C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

//=============================================================================
// GENERAL DEFINITIONS
//=============================================================================


/** @nodoc */
  enum    { CountEval     = 11 }  ;


/** @nodoc */
  CATSurEvalCommand(CATLONG32 iCommand);


/**
 * @nodoc
 * Adds a specified evaluation to the CATSurEvalCommand.
 *<br> For a partial derivative, it also adds the other derivatives
 * of the same order.
 */
  INLINE void OrderEval(Evaluations iAskedEvaluation);


//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Internal data is a CATLONG32 and is used with masks
  CATLONG32 _Flags;

	/** @nodoc */
  enum Commands
    { 
      ResetFlag             = 0,
      EvalPoint             = 1,
      EvalFirstDerivatives  = 2,
      EvalNormal            = 4,
      EvalSecondDerivatives = 8,
      EvalThirdDerivatives  = 16
      }; 

// Array for translation of value Evaluations to flags
  static const Commands sFlagsForEval[CountEval];

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE CATSurEvalCommand::CATSurEvalCommand()
{
  _Flags= EvalPoint;
}

INLINE CATSurEvalCommand::CATSurEvalCommand(const CATSurEvalCommand &Command)
{
  _Flags=Command._Flags;
}


INLINE void CATSurEvalCommand::Reset()
{
  _Flags= ResetFlag;
}

INLINE void CATSurEvalCommand::OrderEvalPoint()
{
  _Flags  |= EvalPoint;
}

INLINE void CATSurEvalCommand::OrderEvalFirstDeriv()
{
  _Flags  |= EvalFirstDerivatives;
}

INLINE void CATSurEvalCommand::OrderEvalNormal()
{
  _Flags  |= EvalNormal;
}

INLINE void CATSurEvalCommand::OrderEvalSecondDeriv()
{
  _Flags  |= EvalSecondDerivatives;
}

INLINE void CATSurEvalCommand::OrderEvalThirdDeriv()
{
  _Flags  |= EvalThirdDerivatives;
}

// Ask for a special evaluation
INLINE void CATSurEvalCommand::OrderEval(Evaluations AskedEvaluation)
{
  _Flags |= sFlagsForEval[AskedEvaluation];
}

//------------------------------------------------------------
// Return what is ordered
//------------------------------------------------------------
INLINE CATLONG32 CATSurEvalCommand::IsSetToEvalPoint() const
{
  return (_Flags & EvalPoint) ? 1 : 0;
}

INLINE CATLONG32 CATSurEvalCommand::IsSetToEvalFirstDeriv() const
{
  return (_Flags & EvalFirstDerivatives) ? 1 : 0;
}

INLINE CATLONG32 CATSurEvalCommand::IsSetToEvalNormal() const
{
  return (_Flags & EvalNormal) ? 1 : 0;
}

INLINE CATLONG32 CATSurEvalCommand::IsSetToEvalSecondDeriv() const
{
  return (_Flags & EvalSecondDerivatives) ? 1 : 0;
}

INLINE CATLONG32 CATSurEvalCommand::IsSetToEvalThirdDeriv() const
{
  return (_Flags & EvalThirdDerivatives) ? 1 : 0;
}

INLINE CATLONG32 CATSurEvalCommand::IsSetToEval(Evaluations Eval) const
{
  return ( _Flags & (sFlagsForEval[Eval])) ? 1 : 0;
}

#endif
