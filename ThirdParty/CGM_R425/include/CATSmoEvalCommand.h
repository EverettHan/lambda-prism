#ifndef CATSmoEvalCommand_H
#define CATSmoEvalCommand_H

//===============================================================================
// Copyright Dassault Systemes Provence 2007, All Rights Reserved 
//===============================================================================



#include "CATIAV5Level.h"
#include "CATDataType.h"

//Pour l'export
#include "CATSmoOperators.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
/**
 * Class representing a command for computing a multiple evaluation 
 * on points of a CATSobMesh.
 *<br>The evaluation types are not exclusive. You can ask for other types
 * by using the <tt>Order</tt> method, or put the command to 
 *<tt>No Evaluation</tt> with the <tt>Reset</tt> method. The evaluation is
 * performed by the <tt>Eval</tt> method of the CATSobMesh interface and results 
 * are handled by the <tt>CATSurEvalLocal</tt> class.
 * <br>Example:
 *<pre>
 * CATSurEvalLocal EvalResult;
 * CATSmoEvalCommand Command;
 * Command.OrderEvalPoint();
 * Command.OrderFirstDeriv();
 * CATSurParam Parameter ;
 * Surface->GetStartLimit(Parameter) ;
 * Surface->Eval(Parameter, Command, EvalResult) ; // Evaluate point and first derivatives.
 * </pre>
 * @see CATSobMesh, CATSurEvalLocal, CATSurEvalResult
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATSmoOperators CATSmoEvalCommand

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
  inline CATSmoEvalCommand();

/**
 * Copy constructor.
 */
  inline CATSmoEvalCommand(const CATSmoEvalCommand &iCommandToCopy);

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * Resets all the specified evaluation on a CATSobMesh.
 *<br>After this, no evaluation will be performed with this command.
 */
  inline void Reset();

/**
 * Adds the point evaluation to <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalPoint();

/**
 * Adds the first derivatives evaluation to <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalFirstDeriv();

/**
 * Adds the normal evaluation to <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalNormal();

/**
 * Adds the second derivatives evaluation to <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalSecondDeriv();
/**
 * Adds the evaluation to of Principal Curvature <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalPrincipalCurvatures() ;

/**
 * Adds the third derivatives evaluation to <tt>this</tt> CATSmoEvalCommand.
 */
  inline void OrderEvalThirdDeriv();

//------------------------------------------------------------
// Get the orders on the command
//------------------------------------------------------------
/**
 * Tests whether the point evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */

  inline CATLONG32 IsSetToEvalPoint()       const;
  
/**
 * Tests whether the first derivatives evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEvalFirstDeriv()  const;

/**
 * Tests whether the normal evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEvalNormal()      const;

/**
 * Tests whether the second derivatives evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEvalSecondDeriv() const;
  
  
  /**
 * Tests whether the Principal Curvatures Evaluations belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEvalPrincipalCurvatures() const;

/**
 * Tests whether the third derivatives evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEvalThirdDeriv()  const;

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
 * Tests whether a specified evaluation belongs to <tt>this</tt> CATSmoEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  inline CATLONG32 IsSetToEval(Evaluations iTestEvaluation) const;






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
  CATSmoEvalCommand(CATLONG32 iCommand);

enum Commands
    { 
      ResetFlag             = 0,
      EvalPoint             = 1,
      EvalFirstDerivatives  = 2,
      EvalNormal            = 4,
      EvalSecondDerivatives = 8,
      EvalPrincipalCurvatures = 16,
      EvalThirdDerivatives  = 32
      }; 
/**
 * @nodoc
 * Adds a specified evaluation to the CATSmoEvalCommand.
 *<br> For a partial derivative, it also adds the other derivatives
 * of the same order.
 */
  inline void OrderEval(Evaluations iAskedEvaluation);

  //enum    { CountEval     = 11 }  ;
//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Internal data is a CATLONG32 and is used with masks
  CATLONG32 _Flags;

	/** @nodoc */
  

// Array for translation of value Evaluations to flags
  static const Commands sFlagsForEval[CountEval];

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
inline CATSmoEvalCommand::CATSmoEvalCommand()
{
  _Flags= EvalPoint;
}

inline CATSmoEvalCommand::CATSmoEvalCommand(const CATSmoEvalCommand &Command)
{
  _Flags=Command._Flags;
}


inline void CATSmoEvalCommand::Reset()
{
  _Flags= ResetFlag;
}

inline void CATSmoEvalCommand::OrderEvalPoint()
{
  _Flags  |= EvalPoint;
}

inline void CATSmoEvalCommand::OrderEvalFirstDeriv()
{
  _Flags  |= EvalFirstDerivatives;
}

inline void CATSmoEvalCommand::OrderEvalNormal()
{
  _Flags  |= EvalNormal;
}

inline void CATSmoEvalCommand::OrderEvalSecondDeriv()
{
  _Flags  |= EvalSecondDerivatives;
}

inline void CATSmoEvalCommand::OrderEvalPrincipalCurvatures() 
{
  _Flags  |= EvalPrincipalCurvatures;
}
 
inline void CATSmoEvalCommand::OrderEvalThirdDeriv()
{
  _Flags  |= EvalThirdDerivatives;
}

// Ask for a special evaluation
inline void CATSmoEvalCommand::OrderEval(Evaluations AskedEvaluation)
{
  _Flags |= sFlagsForEval[AskedEvaluation];
}

//------------------------------------------------------------
// Return what is ordered
//------------------------------------------------------------
inline CATLONG32 CATSmoEvalCommand::IsSetToEvalPoint() const
{
  return (_Flags & EvalPoint) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEvalFirstDeriv() const
{
  return (_Flags & EvalFirstDerivatives) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEvalNormal() const
{
  return (_Flags & EvalNormal) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEvalSecondDeriv() const
{
  return (_Flags & EvalSecondDerivatives) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEvalPrincipalCurvatures() const
{
  return (_Flags & EvalPrincipalCurvatures) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEvalThirdDeriv() const
{
  return (_Flags & EvalThirdDerivatives) ? 1 : 0;
}

inline CATLONG32 CATSmoEvalCommand::IsSetToEval(Evaluations Eval) const
{
  return ( _Flags & (sFlagsForEval[Eval])) ? 1 : 0;
}

#endif
