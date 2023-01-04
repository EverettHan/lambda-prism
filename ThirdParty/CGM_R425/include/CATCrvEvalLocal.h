#ifndef CATCrvEvalLocal_H
#define CATCrvEvalLocal_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATCrvEvalCommand.h"
#include "CATMathInline.h"

class CATMathPoint;
class CATMathVector;

/**
 * Class representing an object that handles the results of a multiple
 * evaluation of a point on a CATCurve.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATCrvEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATCurve</tt> interface. 
 * The objects returned
 * belong to the <tt>CATCrvEvalLocal</tt> and must not be deleted.
 * @see CATCurve, CATCrvEvalCommand
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATCrvEvalLocal
/*
#else
class ExportedByYP00IMPL CATCrvEvalLocal
#endif  
*/
{
public:
//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATCrvEvalLocal.
 */
  CATCrvEvalLocal();

/** @nodoc */
  CATCrvEvalLocal(const CATCrvEvalCommand &iCommand);

//=============================================================================
// SET METHODS
//=============================================================================
/**
 * Replaces the types of evaluation of a CATCrvEvalLocal.
 * @param iCommand
 * The command to copy.
 */
  void SetCommand(const CATCrvEvalCommand &iCommand);

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATCurve.
 * @param iPoint
 * The evaluated point.
 */
  void SetPoint (const CATMathPoint & iPoint);

/**
 * Sets the evaluation of the first derivative at a point of a CATCurve.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  void SetFirstDeriv (const CATMathVector & iFirstDeriv);

/**
 * Sets the evaluation of the second derivative at a point of a CATCurve.
  * @param iSecondDeriv
 * The evaluated second derivative.
 */
  void SetSecondDeriv(const CATMathVector & iSecondDeriv);

/**
 * Sets the evaluation of the third derivative at a point of a CATCurve.
  * @param iThirdDeriv
 * The evaluated third derivative.
 */
  void SetThirdDeriv (const CATMathVector & iThirdDeriv);

/**
 * @nodoc
 * Sets a given type evaluation at a point of a CATCurve.
 *<br>Note that this method does not performed any verifications.
 */
  INLINE void SetValue(CATCrvEvalCommand::Evaluations iEvaluation,
                       const double * iValue);
  /** @nodoc */
  INLINE void SetValue(CATCrvEvalCommand::Evaluations iEvaluation,
                       const double ix, const double iy, const double iz);

//=============================================================================
// GET METHODS
//=============================================================================

/**
 * Retrieves the evaluation of a point of a CATCurve.
 * @param ioPoint
 * The resulting point.
 */
  void GetPoint(CATMathPoint & ioPoint) const;

/**
 * Retrieves the evaluation of the first derivative at a point of a CATCurve.
 * @param ioFirstDeriv
 * The resulting first derivative.
 */
  void GetFirstDeriv (CATMathVector & oFirstDeriv) const;

/**
 * Retrieves the evaluation of the second derivative at a point of a CATCurve.
 * @param ioSecondDeriv
 * The resulting second derivative.
 */
  void GetSecondDeriv(CATMathVector & ioSecondDeriv) const;

/**
 * Retrieves the evaluation of the third derivative at a point of a CATCurve.
 * @param ioThirdDeriv
 * The resulting third derivative.
 */
  void GetThirdDeriv (CATMathVector & ioThirdDeriv) const;

/**
 * @nodoc
 * Retrieves a given type evaluation at a point of a CATCurve.
 *<br>Note that this method does not performed any verifications.
 * The result is an array[3] of doubles that belongs to the
 * CATCrvEvalLocal and must not be deleted.
 */
  INLINE const double * GetValue(CATCrvEvalCommand::Evaluations iEval) const;

/**
 * Retrieves all the evaluations at a point of a CATCurve.
 * @return
 * The result of the evaluation as an array of doubles belonging to the
 * CATCrvEvalLocal and must not be deleted. The 
 * <tt>iEval</tt> CATCrvEvalCommand::Evaluation
 * evaluation type is located at the <tt>3*iEval</tt> place. If an evaluation
 * is not asked for, the 3 doubles space is allocated, but not filled in.
 */
  INLINE const double * GetValues() const;

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
/** @nodoc */
  enum { ArraySize = CATCrvEvalCommand::CountEval} ;

// Evaluated command
  CATCrvEvalCommand  _Command;

// Array of results, sorted using the values of CATCrvEvalCommand::Evaluations
  double             _Results[3*ArraySize];
};

//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE void CATCrvEvalLocal::SetValue(CATCrvEvalCommand::Evaluations Eval,
                                      const double * Value)
{
   double *WhereToCopy = _Results + 3 * (int)Eval;
   WhereToCopy[0] = Value[0];
   WhereToCopy[1] = Value[1];
   WhereToCopy[2] = Value[2];
}

INLINE void CATCrvEvalLocal::SetValue(CATCrvEvalCommand::Evaluations Eval,
                                      const double ix,
                                      const double iy,
                                      const double iz)
{
   double *WhereToCopy = _Results + 3 * (int)Eval;
   WhereToCopy[0] = ix;
   WhereToCopy[1] = iy;
   WhereToCopy[2] = iz;
}

INLINE const double * CATCrvEvalLocal::GetValue(CATCrvEvalCommand::Evaluations Eval) const
{
  return (_Results + 3* (int) Eval);
}

INLINE const double * CATCrvEvalLocal::GetValues() const
{
  return _Results;
}
#endif
