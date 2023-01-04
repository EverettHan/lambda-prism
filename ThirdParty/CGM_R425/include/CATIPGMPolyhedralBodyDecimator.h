/*******************************************************************/
/*    Copyright (c) 2016-2020 by Spatial Corp.                     */
/*    All rights reserved.                                         */
/*    Protected by U.S. Patents 5,257,205; 5,351,196; 6,369,815;   */
/*                              5,982,378; 6,462,738; 6,941,251    */
/*    Protected by European Patents 0503642; 69220263.3            */
/*    Protected by Hong Kong Patent 1008101A                       */
/*******************************************************************/
#ifndef CATIPGMPolyhedralBodyDecimator_h_
#define CATIPGMPolyhedralBodyDecimator_h_


#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATExtTopOperator;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyhedralBodyDecimator;

/**
* Operator for decimating a polyhedral CATBody.
*
* <b>Role:</b> This operator produces a polyhedral CATBody with a reduced triangle count
* while maintaining a shape that is close to the shape of the input.  This operator
* currently only works for polyhedral CATBody inputs.
**/
class ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralBodyDecimator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMPolyhedralBodyDecimator();

  //=============================================================================
  // Settings
  //=============================================================================
  /**
   * Sets the chordal deviation that is not to be exceeded between the input and decimated CATBody instances.
   * Decimation stops when further processing would exceed this chordal deviation. 
   * @param iChordalDeviation
   *   The input chordal deviation.
   */
  virtual void SetChordalDeviation(const double iChordalDeviation) = 0;

  /**
   * Sets a flag to prevent the collapse and change of any bar that is not adjacent to two triangles
   * (either on the same surface or across an edge.)
   * By default the boundary-bars are not frozen.
   * @param iDoFreeze
   *   The input flag.
   */
  virtual void DoFreezeBoundaryBars(CATBoolean iDoFreeze) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyhedralBodyDecimator(); // -> delete can't be called
};

/**
 * Creates a CATIPGMPolyhedralBodyDecimator operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iBody
 * The pointer to the body to decimate.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralBodyDecimator *CATPGMCreatePolyhedralBodyDecimator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATIPGMPolyhedralBodyDecimator_h_ */
