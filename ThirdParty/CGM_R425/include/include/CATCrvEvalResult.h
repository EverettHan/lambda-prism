#ifndef CATCrvEvalResult_H
#define CATCrvEvalResult_H

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIAV5Level.h"
//#if defined ( CATIAV5R11 )
#include "CATCGMVirtual.h"
//#endif
//#if defined ( CATIAV5R10 )
#include "ExportedByCATCGMGeoMath.h"
/*
#else
#include "YP00IMPL.h"
#endif  
*/
#include "CATCrvEvalCommand.h"

class CATMathSetOf3DObjects;
class CATMathSetOfPoints;
class CATMathSetOfVectors;

/**
 * Class representing an object that handles the results of a multiple
 * evaluation on points of a CATCurve.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATCrvEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATCurve</tt> interface.
 * The objects returned
 * belong to the <tt>CATCrvEvalResult</tt> and must not be deleted.
 *<br>Sample
 */
//#if defined ( CATIAV5R11 )
class ExportedByCATCGMGeoMath CATCrvEvalResult : public CATCGMVirtual
/*
#else
#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATCrvEvalResult
#else
class ExportedByYP00IMPL CATCrvEvalResult
#endif  
#endif  
*/
{
public:

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATCrvEvalResult.
 */
  CATCrvEvalResult();

/**
  * Destructor.
  */
  virtual ~CATCrvEvalResult();

//=============================================================================
// SET AND GET METHODS
//=============================================================================
/**
 * Defines the types of evaluation of a CATCrvEvalResult.
 */
  virtual void SetCommand(const CATCrvEvalCommand &iCommand);

/**
 * Defines the number of points where the evaluation of a CATCrvEvalResult
 * has to be performed.
 *<br>This method must be called after the <tt>SetCommand</tt> method, in
 * order to allocate the correct amount of memory for the results.
 */
  virtual void SetNumberOfPoints(CATLONG32 iNbOfPoints);

//------------------------------------------------------------
// Getting all the sets to use them
//------------------------------------------------------------

/**
 * Returns the evaluation of the points of a CATCrvEvalResult.
 * @exception
 * If this evaluation was not defined for the CATCrvEvalResult.
 */
  CATMathSetOfPoints  & GetPoints();

/**
 * Returns the evaluation of the first derivative at the points of 
 * a CATCrvEvalResult.
 * @exception
 * If this evaluation was not defined for the CATCrvEvalResult.
 */
  CATMathSetOfVectors & GetFirstDeriv();

/**
 * Returns the evaluation of the second derivative at the points of 
 * a CATCrvEvalResult.
 * @exception
 * If this evaluation was not defined for the CATCrvEvalResult.
 */
  CATMathSetOfVectors & GetSecondDeriv();

/**
 * Returns the evaluation of the third derivative at the points of 
 * a CATCrvEvalResult.
 * @exception
 * If this evaluation was not defined for the CATCrvEvalResult.
 */
  CATMathSetOfVectors & GetThirdDeriv();

//------------------------------------------------------------
// Releasing the unused memory
//------------------------------------------------------------
/**
 * Releases the memory unused by the internal grids of points and vectors of 
 * a CATCrvEvalResult.
 */
  void Compress();

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Last command given to the object
  CATCrvEvalCommand      _CommandEvaluated;
  CATLONG32 _PointsCount ;

// Array of pointers on CATMathSetOf3DObjects that handle the different results
// of evaluation. The first set is a CATMathetOfPoints, the other ones are
// CATMathSetOfVectors.

// One acceed to them in the array using the indices defined below as enumeration. 
  enum  { CountSets = CATCrvEvalCommand::CountEval};

  CATMathSetOf3DObjects * _SetOfEvaluations[CountSets];

};

#endif

