#ifndef CATSurEvalResult_H
#define CATSurEvalResult_H

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
#include "CATSurEvalCommand.h"
class CATMathGrid;
class CATMathGridOfPoints;
class CATMathGridOfVectors;
class CATSurEvalLocal;

/**
 * Class representing an object that handles the results of a grid
 * evaluation on points of a CATSurface.
 *<br>The definition of the evaluations to performed is declared in a
 *<tt>CATSurEvalCommand</tt> and the evaluation is performed by the
 *<tt>Eval</tt> method of the <tt>CATSurface</tt> interface. 
 * The objects returned
 * belong to the <tt>CATSurEvalResult</tt> and must not be deleted.
 * @see CATSurEvalCommand, CATSurface
 */
//#if defined ( CATIAV5R11 )
class ExportedByCATCGMGeoMath CATSurEvalResult : public CATCGMVirtual
/*
#else
#if defined ( CATIAV5R10 )
class ExportedByCATCGMGeoMath CATSurEvalResult
#else
class ExportedByYP00IMPL  CATSurEvalResult
#endif  
#endif  
*/
{
public:

//=============================================================================
// CONSTRUCTORS AND DESTRUCTOR
//=============================================================================
/**
 * Constructs an empty CATSurEvalResult.
 */
  CATSurEvalResult();

/**
 * Destructor.
 */
  virtual ~CATSurEvalResult();

//=============================================================================
// SET AND GET METHODS
//=============================================================================

/**
 * Retrieves the evaluation at a given point of a grid.
 *<br>Check that the command used for the evaluations are compatible.
 * @param iIndexPointU
 * The index starting at 0 of the point in the first direction of the grid.
 * @param iIndexPointV
 * The index starting at 0 of the point in the second direction of the grid.
 * @param ioResult
 * The point evaluation.
 */
  void GetLocalResult(CATLONG32 iIndexPointU, CATLONG32 iIndexPointV, CATSurEvalLocal & ioResult) const;

/**
 * Modifies the evaluation at a given point of a grid.
 *<br>Check that the command used for the evaluations are compatible.
 * @param iIndexPointU
 * The index starting at 0 of the point in the first direction of the grid.
 * @param iIndexPointV
 * The index starting at 0 of the point in the second direction of the grid.
 * @param iResult
 * The point evaluation.
 */
  void SetLocalResult(CATLONG32 iIndexPointU, CATLONG32 iIndexPointV, const CATSurEvalLocal & iResult);

//------------------------------------------------------------
// Getting all the grids to use them
//------------------------------------------------------------
/**
 * Returns the evaluation at the points of a surface grid.
 * @return
 * The grid of the corresponding mathematical definitions. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfPoints  & GetPoints();

/**
 * Returns the evaluation of the U first partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding first derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetFirstDerivU();
/**
 * Returns the evaluation of the V first partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding first derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetFirstDerivV();

/**
 * Returns the evaluation of the normals at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding normalized normals. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetNormals();

// Getting the second derivatives
/**
 * Returns the evaluation of the UU second partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding second derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetSecondDerivU2();

/**
 * Returns the evaluation of the UV second partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding second derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetSecondDerivUV();

/**
 * Returns the evaluation of the VV second partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding second derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetSecondDerivV2();

// Getting the third derivatives
/**
 * Returns the evaluation of the UUU third partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding third derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetThirdDerivU3();

/**
 * Returns the evaluation of the UUV third partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding third derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetThirdDerivU2V();

/**
 * Returns the evaluation of the UVV third partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding third derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetThirdDerivUV2();

/**
 * Returns the evaluation of the VVV third partial derivative at 
 * the points of a surface grid.
 * @return
 * The grid of the corresponding third derivatives. 
 * As part of <tt>this</tt>, it must not be directly deleted.
 * @exception
 * If this evaluation was not defined for the CATSurEvalResult.
 */
  CATMathGridOfVectors & GetThirdDerivV3();

//------------------------------------------------------------
// Releasing the unused memory
//------------------------------------------------------------
/**
 * Releases the memory unused by the internal grids of points and vectors of 
 * a CATSurEvalResult.
 */
  void Compress();

	/**
 * Defines the types of evaluation of a CATSurEvalResult.
 * @param iCommand
 * The command to copy.
 */
  virtual void SetCommand(const CATSurEvalCommand &iCommand);

/**
 * Defines the number of points where the evaluation of a CATSurEvalResult
 * has to be performed.
 *<br>This method must be called after the <tt>SetCommand</tt> method, in
 * order to allocate the correct amount of memory for the results.
 * @param iPointsInU
 * The number of points in the first direction of the surface .
 * @param iPointsInV
 * The number of points in the second direction of the surface.
 */
  virtual void SetNumberOfPoints(CATLONG32 iPointsInU, CATLONG32 iPointsInV);

//=============================================================================
// INTERNAL DATAS
//=============================================================================
protected:
// Last command given to the object
  CATSurEvalCommand      _CommandEvaluated;

// Array of pointers on CATMathGrid that handle the different results of evaluation.
// The first grid is a CATMathGridOfPoints, the other ones are CATMathGridOfVectors 
// One acceed to them in the array using the indices defined below as enumeration.
	/** @nodoc */
  enum { CountGrids = CATSurEvalCommand::CountEval};

  CATMathGrid         * _GridOfEvaluations[CountGrids];

};

#endif
