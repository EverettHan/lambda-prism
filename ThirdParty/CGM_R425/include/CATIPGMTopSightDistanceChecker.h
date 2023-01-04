#ifndef CATIPGMTopSightDistanceChecker_h_
#define CATIPGMTopSightDistanceChecker_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATLaw;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSightDistanceChecker;

/**
 * Creates an operator for checking the Sight Distance on a Wire
 * All the curves in the wire must be defined on same surface and it must be a PLANE.
 * To use the operator:
 * <ul><li>Create it with the <tt>CATPGMCreateTopSightDistanceChecker</tt> global function,
 * <li>Set parameters to tune its use,
 *    <ul><li>You must:
 *        <ul><li>SetSightDistance,
 *            <li>SetHeights for Eye and Hazard heights on road 
 *        </ul>
 *    <li>Optional:
 *        <ul><li>SetAcceptTangency
 *            <li>SetRevertDirectionOfCourse
 *        </ul>
 *    </ul>
 * <li>Run the operator ,
 * <li>Retrieve the results with the <tt>GetCheckResult</tt> method,
 * <li><tt>Release</tt> it after use with the usual C++ <tt>Release</tt> method.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSightDistanceChecker: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSightDistanceChecker();

  //-----------------------------------------------------------------------------
  //  Settings
  //-----------------------------------------------------------------------------
  /**
  * Set the Offset, above the curve for Driver and Hazard 
  */
  virtual void SetHeights(double iDriverEyeHeight, double iHazardHeight) = 0;

  /**
  * Set the distance between Driver and Hazard.
  *
  * N.B.: for performance we assume that the sight distance is constant along straight lines.
  * To avoid this assumption set boolean to false (default TRUE)
  */
  virtual void SetSightDistance( CATLaw * iSightDistanceLaw, CATBoolean iIsSightDistanceConstantAlongLines = TRUE ) = 0;

  /**
  * Set to TRUE to accept that the sight line is tangent to the curves.
  * Default is FALSE;
  */
  virtual void SetAcceptTangency(CATBoolean iTangencyAccepted = FALSE) = 0;

  /**
  * Set to TRUE to travel the wire in reverse direction than the default of the wire.
  * Or to FALSE to travel it in the wire natural course.
  * Default is FALSE
  */
  virtual void SetRevertDirectionOfCourse(CATBoolean iRevertDirectionOfCourse) = 0;

  //-------------------------------------------------------------------------
  // Result Access
  //-------------------------------------------------------------------------

/**
 * Returns a list of double which must be taken by pairs:
 * each pair is an interval of wire param where the sight line is broken.
 * If empty, the Sight Distance is respected everywhere.
 */
      virtual void GetCheckResult(CATListOfDouble *& oBreakingSightLineIntervalsOnWire) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSightDistanceChecker(); // -> delete can't be called
};


ExportedByCATGMOperatorsInterfaces CATIPGMTopSightDistanceChecker *CATPGMCreateTopSightDistanceChecker(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyWire);

#endif /* CATIPGMTopSightDistanceChecker_h_ */
