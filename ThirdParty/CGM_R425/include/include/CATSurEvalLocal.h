#ifndef CATSurEvalLocal_H
#define CATSurEvalLocal_H

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
#include "CATSurEvalCommand.h"
#include "CATMathInline.h"

class CATMathPoint;
class CATMathVector;

/**
 * Class representing an object that handles the results of a multiple
 * evaluation on a point of a CATSurface.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATSurEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATSurface</tt> interface. 
 * The objects returned
 * belong to the <tt>CATSurEvalLocal</tt> and must not be deleted.
 * @see CATSurEvalCommand, CATSurface 
 */
//#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSurEvalLocal
/*
#else
class ExportedByYP00IMPL CATSurEvalLocal
#endif  
*/
{
public:

/**
 * Constructs an empty CATSurEvalLocal.
 */
  CATSurEvalLocal();

/** @nodoc */
  CATSurEvalLocal(const CATSurEvalCommand &iCommand);

//------------------------------------------------------------
// Getting the result of the evaluation
//------------------------------------------------------------
/**
 * Retrieves the evaluation of a point.
 * @param ioPoint
 * The mathematical definition of the evaluated point.
 */
  void GetPoint(CATMathPoint & ioPoint) const;

/**
 * Retrieves the evaluation of the U first partial derivative at a point
 * of a CATSurface. 
 * @param ioDerivU
 * The vector of the U first partial derivative.
 */
  void GetFirstDerivU(CATMathVector & ioDerivU) const;

/**
 * Retrieves the evaluation of the V first partial derivative at a point
 * of a CATSurface. 
 * @param ioDerivV
 * The vector of the V first partial derivative.
 */
  void GetFirstDerivV(CATMathVector & ioDerivV) const;

/**
 * Retrieves the evaluation of the normal at a point
 * of a CATSurface.
 * @param ioNormal
 * The normalized normal.
 */
  void GetNormal(CATMathVector & ioNormal) const;

/**
 * Retrieves the evaluation of the UU second partial derivative at a point
 * of a CATSurface.
 * @param ioDerivU2
 * The vector of the UU second partial derivative.
 */
  void GetSecondDerivU2(CATMathVector & ioDerivU2) const;

/**
 * Retrieves the evaluation of the UV second partial derivative at a point
 * of a CATSurface. 
 * @param ioDerivUV
 * The vector of the UV second partial derivative.
 */
  void GetSecondDerivUV(CATMathVector & ioDerivUV) const;

/**
 * Retrieves the evaluation of the VV second partial derivative at a point
 * of a CATSurface.
 * @param ioDerivV2
 * The vector of the V2 second partial derivative.
 */
  void GetSecondDerivV2(CATMathVector & ioDerivV2) const;

/**
 * Retrieves the evaluation of the UUU third partial derivative at a point
 * of a CATSurface.
 * @param ioDerivU3
 * The vector of the UUU third partial derivative.
 */
  void GetThirdDerivU3 (CATMathVector & ioDerivU3) const;

/**
 * Retrieves the evaluation of the UUV third partial derivative at a point
 * of a CATSurface.
 * @param ioDerivU2V
 * The vector of the U2V third partial derivative.
 */
  void GetThirdDerivU2V(CATMathVector & ioDerivU2V) const;

/**
 * Retrieves the evaluation of the UVV third partial derivative at a point
 * of a CATSurface.
 * @param ioDerivUV2
 * The vector of the UV2 third partial derivative.
 */
  void GetThirdDerivUV2(CATMathVector & ioDerivUV2) const;

/**
 * Retrieves the evaluation of the VVV third partial derivative at a point
 * of a CATSurface.
 * @param ioDerivV3
 * The vector of the VVV third partial derivative.
 */
  void GetThirdDerivV3 (CATMathVector & ioDerivV3) const;

/**
 * @nodoc
 * Retrieves a given evaluation at a point of a CATSurface.
 *<br>Note that this method does not performed any verifications.
 * @return
 * The array[3] of doubles of the required evaluation, that belongs to the
 * CATSurEvalLocal and must not be deleted.
 */
  INLINE const double* GetValue(CATSurEvalCommand::Evaluations iEval) const;

/**
 * Retrieves all the evaluations defined in the CATSurEvalCommand.
 * @return
 * The array[] of doubles corresponding to the required evaluation, and that belongs to the
 * CATSurEvalLocal: it must not be deleted. The 
 * <tt>iEval</tt> CATSurEvalCommand::Evaluation
 * evaluation type is located at the <tt>3*iEval</tt> place. If an evaluation
 * is not asked for, the 3 doubles space is allocated, but not filled in. 
 */
  INLINE const double * GetValues() const;

/**
 * Replaces the type of evaluation of <tt>this</tt> CATSurEvalLocal.
 * @param iCommand
 * The command to copy.
 */
  void SetCommand(const CATSurEvalCommand &iCommand);

//------------------------------------------------------------
// Setting the results
//------------------------------------------------------------
/**
 * Sets the evaluation of a point on a CATSurface.
 * @param iPoint
 * The evaluated point.
 */
  void SetPoint (const CATMathPoint &iPoint);

/**
 * Sets the evaluation of the U first partial derivative at a point 
 * of a CATSurface.
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  void SetFirstDerivU(const CATMathVector &iDerivU);

/**
 * Sets the evaluation of the V first partial derivative at a point
 * of a CATSurface. 
 * @param iFirstDeriv
 * The evaluated first derivative.
 */
  void SetFirstDerivV(const CATMathVector &iDerivV);

/**
 * Sets the evaluation of the normal at a point
 * of a CATSurface. 
 * @param iNormal
 * The evaluated normal.
 */
  void SetNormal(const CATMathVector &iNormal);

/**
 * Sets the evaluation of the UU second partial derivative at a point
 * of a CATSurface.
 * @param iDerivU2
 * The evaluated second derivative.
 */
  void SetSecondDerivU2(const CATMathVector &iDerivU2);

/**
 * Sets the evaluation of the UV second partialderivative at a point
 * of a CATSurface. 
 * @param iDerivUV
 * The evaluated second derivative.
 */
  void SetSecondDerivUV(const CATMathVector &iDerivUV);

/**
 * Sets the evaluation of the VV second partial derivative at a point
 * of a CATSurface. 
 * @param iDerivV2
 * The evaluated second derivative.
 */
  void SetSecondDerivV2(const CATMathVector & iDerivV2);

/**
 * Sets the evaluation of the UUU third partial derivative at a point
 * of a CATSurface. 
 * @param iDerivU3
 * The evaluated third derivative.
 */
  void SetThirdDerivU3 (const CATMathVector & iDerivU3);

/**
 * Sets the evaluation of the UUV third partial derivative at a point
 * of a CATSurface. 
 * @param iDerivU2V
 * The evaluated third derivative.
 */
  void SetThirdDerivU2V(const CATMathVector & iDerivU2V);

/**
 * Sets the evaluation of the UVV third partial derivative at a point
 * of a CATSurface. 
 * @param iDerivUV2
 * The evaluated third derivative.
 */
  void SetThirdDerivUV2(const CATMathVector & iDerivUV2);

/**
 * Sets the evaluation of the VVV third partial derivative at a point
 * of a CATSurface. 
 * @param iDerivV3
 * The evaluated third derivative.
 */
  void SetThirdDerivV3 (const CATMathVector & iDerivV3);

/**
 * @nodoc
 * Sets a given type evaluation at a point of a CATSurface.
 *<br>Note that this method does not performed any verifications.
 */
  INLINE void SetValue(CATSurEvalCommand::Evaluations iEvaluation,
			   const double * iValue);



//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Size of the array ( in point and vector)
  enum { ArraySize = CATSurEvalCommand::CountEval} ;

// Evaluated command
  CATSurEvalCommand  _Command;

// Array of results, sorted using the values of CATSurEvalCommand::Evaluations
  double             _Results[3*ArraySize];

};


//=============================================================================
// INLINE IMPLEMENTATIONS
//=============================================================================
INLINE void CATSurEvalLocal::SetValue(CATSurEvalCommand::Evaluations Eval,
					  const double * Value)
{
  double *WhereToCopy=_Results + 3* (int) Eval;
  WhereToCopy[0]=Value[0];
  WhereToCopy[1]=Value[1];
  WhereToCopy[2]=Value[2];
} 

INLINE const double * CATSurEvalLocal::GetValue(CATSurEvalCommand::Evaluations Eval) const
{
  return (_Results + 3* (int) Eval);
}

INLINE const double * CATSurEvalLocal::GetValues() const
{
  return _Results;
}


#endif
