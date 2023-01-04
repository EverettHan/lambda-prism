#ifndef CATIPGMBodyExtremumCoord_h_
#define CATIPGMBodyExtremumCoord_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopBodyExtremum.h"
#include "CATExtremumCoordCrvDef.h"
#include "CATDir.h"

class CATBody;
class CATCGMJournalList;
class CATMathPoint;
class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMBodyExtremumCoord;

/**
 * The type of extremum.
 * @param CATMax
 * The extremum in the direction.
 * @param CATMin
 * The extremum in the opposite direction.
 */
//enum CATMinMax
// {CATMinimum, CATMaximum};
//-----------------------------------------------------------------------------
/**
* Class defining the operator that compute the farest points of a body in a given direction.
*<br>
* The CATIPGMBodyExtremumCoord operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input body is not modified. The result is a body
* containing vertices (for isolated solutions), wires or skins.
*<ul>
* <li>A CATIPGMBodyExtremumCoord operator is created with the <tt>CATCreateAllBodyExtremumCoord</tt> 
* global method. It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
*<li>The computation is done with the <tt>Run</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord: public CATIPGMTopBodyExtremum
{
public:
  /**
   * Constructor
   */
  CATIPGMBodyExtremumCoord();

  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

  /**
 * nodoc.
 */
  virtual void GetOnlyExtremum(CATLONG32 &oOnly) = 0;

  /**
 * nodoc
 */
  virtual void SetOnlyExtremum(CATLONG32 iOnly) = 0;

  /**
 * Returns the value of the extremum in the choosen direction.
 * @return
 * The value.
 */
  virtual double GetExtremum() = 0;

  /**
 * Returns the created body.
 * @return
 * The pointer to the created body containing the vertices, wires or surfaces representing
 * the body extremum.
 */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMBodyExtremumCoord(); // -> delete can't be called
};

//-----------------------------------------------------------------------------
/**
 * @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord *CATPGMCreateBodyExtremumCoord(
  CATBody *iBody,
  MinMax iTypeOfExtremum,
  Direction iDirection,
  CATCGMJournalList *iJournal = NULL);

//-----------------------------------------------------------------------------
/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord *CATPGMCreateBodyExtremumCoord(
  CATBody *iBody,
  CATTopData *iData,
  MinMax iTypeOfExtremum,
  Direction iDirection);

//-----------------------------------------------------------------------------
/**
 * @nodoc
 * Creates the operator to compute the extremum of a body in one direction.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iBody
 * The pointer to the body.
 * @param iTypeOfExtremum
 * The type of extremum. Minimum or maximum.
 * @param iDirection
 * The direction.
 * @param iPtOrig
 * The origin to compute the distance get by GetExtremum method. default (0,0,0).
 * @param iJournal
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not filled in.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord *CATPGMCreateDirBodyExtremumCoord(
  CATGeoFactory *iFactory,
  CATBody *iBody,
  CATMinMax iTypeOfExtremum,
  const CATMathVector &iDirection,
  const CATMathPoint &iPtOrig,
  CATCGMJournalList *iJournal = NULL);

//-----------------------------------------------------------------------------
/**
 * @nodoc
 * Creates the operator to compute the extremum of a body in one direction.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iBody
 * The pointer to the body.
 * @param iTypeOfExtremum
 * The type of extremum. Minimum or maximum.
 * @param iDirection
 * The direction.
 * @param iPtOrig
 * The origin to compute the distance get by GetExtremum method. default (0,0,0).
 * @param iJournal
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not filled in.
* @return [out, IUnknown#Release]
 * The pointer to the created operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord *CATPGMCreateDirBodyExtremumCoord(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATMinMax iTypeOfExtremum,
  const CATMathVector &iDirection,
  const CATMathPoint &iPtOrig);

//-----------------------------------------------------------------------------
/**
 * @nodoc
 * Creates the operator to compute the extremum of a body in one direction.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iBody
 * The pointer to the body.
 * @param iTypeOfExtremum
 * The type of extremum. Minimum or maximum.
 * @param iDirection
 * The direction.
 * @param iPtOrig
 * The origin to compute the distance get by GetExtremum method. default (0,0,0).
 * @param iJournal
 * The pointer to the journal. If <tt>NULL</tt>, the journal is not filled in.
 * @return
 * The pointer to the created operator. To <tt>delete</tt> after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMBodyExtremumCoord *CATPGMCreateDirNewBodyExtremumCoord(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATMinMax iTypeOfExtremum,
  const CATMathVector &iDirection,
  const CATMathPoint &iPtOrig);

#endif /* CATIPGMBodyExtremumCoord_h_ */
