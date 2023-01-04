#ifndef CATIPGMTopGeodesicPtPt_h_
#define CATIPGMTopGeodesicPtPt_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATMathVector;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopGeodesicPtPt;

/**
 * Class defining the operator that creates a geodesic line from two points.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Creates the operator with the <tt>CATPGMCreateGeodesicLinePtPt</tt> global function.
 *<li> Specifies the options by using the Setxxx methods.
 *<li> Runs with the <tt>Run</tt> method. 
 *<li> Gets the result body by the <tt>GetResult</tt> method. 
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopGeodesicPtPt: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopGeodesicPtPt();

  /**
    * Runs <tt>this</tt> operator. Returns 0 if the operation completes properly.
    */
  virtual int Run() = 0;

  /**
    * @nodoc
    */
  virtual CATBody *GetResult(CATCGMJournalList *iJourn) = 0;

  /**
    * Returns the resulting body.
    */
  virtual CATBody *GetResult() = 0;

  /**
    * Re-specifies the curve parameters.
    * @param ivect
    * The direction.
    * @param ilength
    * The length.
    * @param iinversion
    * To invert the direction.
    */
  virtual int SetParam(
    CATMathVector &ivect,
    double ilength,
    CATLONG32 iinversion) = 0;

  /**
    * Retrieves the curve parameters.
    * @param iovect
    * The direction.
    * @param iolength
    * The length.
    * @param ioinversion
    * <b>Legal values</b>: 
    *   <tt>0</tt>: a solution is found from start to end point. iovect is tangent 
    *    to the line at the start point.
    *   <tt>1/tt>: a solution is found from end to start point. iovect is tangent 
    *    to the line at the end point.
    */
  virtual int GetParam(
    CATMathVector &iovect,
    double &iolength,
    CATLONG32 &ioinversion) = 0;

  /**
    * Adds a given length at the extremities of the line.
    * @param ilength1
    * From the start point.
    * @param ilength2
    * From the end point.
    */
  virtual int SetLength(double ilength1 = 0, double ilength2 = 0) = 0;

  /** 
   * Defines the tolerance of the geometrically coincident elements to be taken 
   * into account by <tt>this</tt> operator on start and end points.
   * The default value is the factory resolution, 
   * and it is strongly recommended to keep it.
   * @param itolerance
   * The tolerance.
   */
  virtual void SetTolerance(double itolerance) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopGeodesicPtPt(); // -> delete can't be called
};

//
/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopGeodesicPtPt *CATPGMCreateTopGeodesicPtPt(
  CATGeoFactory *iFacto,
  CATTopData *iData,
  CATBody *iPtOrig,
  CATBody *iPtFin,
  CATBody *iShellSupport);

#endif /* CATIPGMTopGeodesicPtPt_h_ */
