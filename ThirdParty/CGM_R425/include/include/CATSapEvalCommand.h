#ifndef CATSapEvalCommand_H
#define CATSapEvalCommand_H

//===============================================================================
// Copyright Dassault Systemes Provence 2008-2009, All Rights Reserved 
//===============================================================================
//HISTO:
// Fevrier 2009 RNO : Update Perfo + Suppression Courbure
// Fevrier 2008  RNO : Creation


#include "CATIAV5Level.h"
#include "CATDataType.h"

//Pour l'export
#include "CATSapApprox.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
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
 * CATSapEvalCommand Command;
 * Command.OrderEvalPoint();
 * Command.OrderFirstDeriv();
 * CATSurParam Parameter ;
 * Surface->GetStartLimit(Parameter) ;
 * Surface->Eval(Parameter, Command, EvalResult) ; // Evaluate point and first derivatives.
 * </pre>
 * @see CATSobMesh, CATSurEvalLocal, CATSurEvalResult
 */
//#if defined ( CATIAV5R10 )

#define SMALLISBEAUTIFULL "Utilise un char a la place d'un tableau de Boolean"

class ExportedByCATSapApprox CATSapEvalCommand

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
  INLINE CATSapEvalCommand();

/**
 * Copy constructor.
 */
  INLINE CATSapEvalCommand(const CATSapEvalCommand &iCommandToCopy);

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * Resets all the specified evaluation on a CATSobMesh.
 *<br>After this, no evaluation will be performed with this command.
 */
  INLINE void Reset();

/**
 * Adds the point evaluation to <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalPoint();

/**
 * Adds the first derivatives evaluation to <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalFirstDeriv();

/**
 * Adds the normal evaluation to <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalNormal();

/**
 * Adds the second derivatives evaluation to <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalSecondDeriv();
/**
 * Adds the evaluation to of Principal Curvature <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalPrincipalCurvatures() ;

/**
 * Adds the third derivatives evaluation to <tt>this</tt> CATSapEvalCommand.
 */
  INLINE void OrderEvalThirdDeriv();

//------------------------------------------------------------
// Get the orders on the command
//------------------------------------------------------------
/**
 * Tests whether the point evaluation belongs to <tt>this</tt> CATSapEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */

  INLINE CATLONG32 IsSetToEvalPoint()       const;
  
/**
 * Tests whether the first derivatives evaluation belongs to <tt>this</tt> CATSapEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalFirstDeriv()  const;

/**
 * Tests whether the normal evaluation belongs to <tt>this</tt> CATSapEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalNormal()      const;

/**
 * Tests whether the second derivatives evaluation belongs to <tt>this</tt> CATSapEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalSecondDeriv() const;
  
/**
 * Tests whether the third derivatives evaluation belongs to <tt>this</tt> CATSapEvalCommand.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 *<dl><dt> 0 <dd> if it does not belong to the command.
 *    <dt> 1 <dd> if it belongs to the command.</dl>
 */
  INLINE CATLONG32 IsSetToEvalThirdDeriv()  const;
#ifdef SMALLISBEAUTIFULL
  //no doc !!
  INLINE char GetCommandAsFLAG() const;
#endif
private:
#ifdef SMALLISBEAUTIFULL
#define      SapNOEVAL                 0
#define      SapEvalPoint              1
#define      SapEvalFirstDerivatives   2
#define      SapEvalNormal             4
#define      SapEvalSecondDerivatives  8
#define      SapEvalThirdDerivatives      16
  char _Flags;//OUI DOIT ETRE PUBLIC 

#else
#define      SapEvalPoint              0
#define      SapEvalFirstDerivatives   1
#define      SapEvalNormal             2
#define      SapEvalSecondDerivatives  3
#define      SapEvalPrincipalCurvatures   4
#define      SapEvalThirdDerivatives      5
#define      SapEnumEval                6 //Number of Possible Eval
  CATBoolean _Flags[SapEnumEval];
#endif
	/** @nodoc */
  

// Array for translation of value Evaluations to flags
 // static const Commands sFlagsForEval[CountEval];

};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
#ifdef SMALLISBEAUTIFULL
INLINE char CATSapEvalCommand::GetCommandAsFLAG() const
{
  return(_Flags);
}
#endif

INLINE CATSapEvalCommand::CATSapEvalCommand()
{
#ifdef SMALLISBEAUTIFULL
  _Flags=SapEvalPoint;
#else
  for(int i=0;i<SapEnumEval;i++)_Flags[i]=FALSE;
#endif
}

INLINE CATSapEvalCommand::CATSapEvalCommand(const CATSapEvalCommand &Command)
{
  #ifdef SMALLISBEAUTIFULL
  _Flags=Command._Flags;
#else
  for(int i=0;i<SapEnumEval;i++) _Flags[i]=Command._Flags[i];
#endif
}


INLINE void CATSapEvalCommand::Reset()
{ 
#ifdef SMALLISBEAUTIFULL
_Flags=SapNOEVAL;
#else
for(int i=0;i<SapEnumEval;i++)_Flags[i]=FALSE;
#endif
}

INLINE void CATSapEvalCommand::OrderEvalPoint()
{
  #ifdef SMALLISBEAUTIFULL
  _Flags  |= SapEvalPoint;
#else
  _Flags[SapEvalPoint]=TRUE;
#endif
}

INLINE void CATSapEvalCommand::OrderEvalFirstDeriv()
{
   #ifdef SMALLISBEAUTIFULL
  _Flags  |= SapEvalFirstDerivatives;
#else
  _Flags[SapEvalFirstDerivatives]=TRUE;
#endif
}

INLINE void CATSapEvalCommand::OrderEvalNormal()
{
#ifdef SMALLISBEAUTIFULL
  _Flags  |= SapEvalNormal;
#else
  _Flags[SapEvalNormal]=TRUE;
#endif
}

INLINE void CATSapEvalCommand::OrderEvalSecondDeriv()
{
#ifdef SMALLISBEAUTIFULL
  _Flags  |= SapEvalSecondDerivatives;
#else
  _Flags[SapEvalSecondDerivatives]=TRUE;
#endif
}


INLINE void CATSapEvalCommand::OrderEvalThirdDeriv()
{
#ifdef SMALLISBEAUTIFULL
  _Flags  |= SapEvalThirdDerivatives;
#else
  _Flags[SapEvalThirdDerivatives]=TRUE;
#endif
}

// Ask for a special evaluation
/*
INLINE void CATSapEvalCommand::OrderEval(Evaluations AskedEvaluation)
{
  _Flags |= sFlagsForEval[AskedEvaluation];
}
*/

//------------------------------------------------------------
// Return what is ordered
//------------------------------------------------------------
INLINE CATLONG32 CATSapEvalCommand::IsSetToEvalPoint() const
{
  #ifdef SMALLISBEAUTIFULL
   return (_Flags & SapEvalPoint);// ? 1 : 0;
#else

  return (_Flags[SapEvalPoint]);
#endif
}

INLINE CATLONG32 CATSapEvalCommand::IsSetToEvalFirstDeriv() const
{
    #ifdef SMALLISBEAUTIFULL
   return (_Flags & SapEvalFirstDerivatives);// ? 1 : 0;
#else

  return (_Flags[SapEvalFirstDerivatives]);
#endif
}

INLINE CATLONG32 CATSapEvalCommand::IsSetToEvalNormal() const
{
#ifdef SMALLISBEAUTIFULL
  return (_Flags & SapEvalNormal);// ? 1 : 0;
#else
  return (_Flags[SapEvalNormal]);
#endif
}

INLINE CATLONG32 CATSapEvalCommand::IsSetToEvalSecondDeriv() const
{
#ifdef SMALLISBEAUTIFULL
   return (_Flags & SapEvalSecondDerivatives);// ? 1 : 0;
#else
  return (_Flags[SapEvalSecondDerivatives]);
#endif
}


INLINE CATLONG32 CATSapEvalCommand::IsSetToEvalThirdDeriv() const
{
#ifdef SMALLISBEAUTIFULL
  return (_Flags & SapEvalThirdDerivatives);// ? 1 : 0;
#else
  return (_Flags[SapEvalThirdDerivatives]);
#endif
}

/*
INLINE CATLONG32 CATSapEvalCommand::IsSetToEval(Evaluations Eval) const
{
  return ( _Flags & (sFlagsForEval[Eval])) ? 1 : 0;
}
*/

#endif
