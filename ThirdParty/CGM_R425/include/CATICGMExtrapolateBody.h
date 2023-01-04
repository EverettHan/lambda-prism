#ifndef CATICGMExtrapolateBody_h_
#define CATICGMExtrapolateBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATCrvParam;
class CATCurve;
class CATDomain;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATLoop;
class CATMathBox;
class CATMathDirection;
class CATMathLine;
class CATMathPlane;
class CATMathPoint;
class CATMathVector;
class CATSurface;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMExtrapolateBody;

/**
* Class representing an operator that extrapolates 1D body (CATWire).
*<br>The wire can be extrapolated on a planar support (optional).
*<br>The extrapolation gives a result that is continuous in tangency. 
* To use it:
* <ul>
* <li>Create it with the <tt>CATCGMCreateExtrapolateBody</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
* <li>Run it
* <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*<li>Release the operator with the <tt>Release</tt> method after use.
*</ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMExtrapolateBody: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMExtrapolateBody();

  /**
    * Runs <tt>this</tt> operator.
    */
  virtual int Run() = 0;

  /** 
        * Specifies the extrapolation length.
        * @param iEndCell
        * The pointer to the cell to be extrapolated.
        * @param iLength
        * The extrapolation length.
    */
  virtual void SetLimitToExtrapolate(CATCell *iEndCell, double iLength) = 0;

  /**
        * Returns the pointer to the resulting body.
    */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMExtrapolateBody(); // -> delete can't be called
};

/**
 * Creates a CATICGMExtrapolateBody operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToExtrapol
 * The CATWire to be extrapolated.
 * @param iSupport
 * The surfacic support on which the CATWire is to be extrapolated. This option is
 * only available for planar supports.
 * @param iMinimumGap
 * The minimum gap. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMExtrapolateBody *CATCGMCreateExtrapolateBody(
  CATGeoFactory *iGeoFactory,
  CATTopData *iTopData,
  CATBody *iBodyToExtrapol,
  CATSurface *iSupport = NULL,
  double iMinimumGap = 0.);

#endif /* CATICGMExtrapolateBody_h_ */
