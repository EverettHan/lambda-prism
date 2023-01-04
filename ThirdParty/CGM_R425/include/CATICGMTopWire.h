#ifndef CATICGMTopWire_h_
#define CATICGMTopWire_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMGeoToTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATCrvLimits;
class CATCurve;
class CATEdge;
class CATEdgeCurve;
class CATGeoFactory;
class CATMacroPoint;
class CATPointOnEdgeCurve;
class CATVertex;
class CATWire;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopWire;

/** 
* Class representing the operator that creates a wire body from one or several curves. 
* <br>To use the CATICGMTopWire:
* <ul><li>Create it with one of the <tt>CATCGMCreateTopWire</tt> global function. 
* You must order the input curves and precise the
* limits of each, as well as their relative orientation, such that the end of
* one curve (possibly reversed) is the beginning of the following.
* <br>Every created edge is positively oriented in the wire. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li>DRelease the operator with the <tt>Release</tt> method after use.</ul>
* If there is only one closed curve, the operator creates a wire with two edges.
*/
class ExportedByCATGMOperatorsInterfaces CATICGMTopWire: public CATICGMGeoToTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopWire();

  /**
	 * Runs <tt>this</tt> operator.
	 */
  virtual int Run() = 0;

  /**
	* Asks for the closure of the wire.
	* <br> The start extremity of the first curve and 
    * the end extremity of the last curve must be the same.
	*/
  virtual void ForceWireClosure() = 0;

#ifdef CATIACGMR420CAA	
  /**
	* Asks for the wire to be marked infinite.
	* <br> The input can only be a single linear curve defined on a plane.
	*/
  virtual void MakeWireInfinite() = 0;

#endif   
  /**
	* Returns the pointer to the wire of the resulting body.
	* @return
	* The pointer to the wire of the resulting body. Remember that the whole body is retrieved with
	* the <tt>GetResult</tt> method, and you must manage its deletion if you do not want to keep it.
	*/
  virtual CATWire *GetWire() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopWire(); // -> delete can't be called
};

/**
	* Creates an operator to build a wire body from several curves.
	* @param iFactory
	* The pointer to the factory of the geometry.
    * @param iData
    * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
    * is <tt>NULL</tt>, it is not filled. 
	* @param iNbCurves
	* The number of curves to assemble in the wire.
	* @param iCurves
	* The array <tt>[iNbCurves]</tt> of pointers to the curves used to define the wire.
    * @param iLimits
	* The array <tt>[iNbCurves]</tt> of the limits for each curve.
	* @param iOrientations
	* The array <tt>[iNbCurves]</tt> of the relative orientation for each curve.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>1</tt></dt><dd>The curve is used in is original orientation.
	* <dt><tt>-1</tt></dt><dd>The curve is used with an opposite orientation.
	* </dl>
	* Combine with <tt>iLimits</tt>, these specifications must insure that the end of
    * one curve (possibly reversed) is the beginning of the following.
	* Every created edge is positively oriented in the wire.
          * @return [out, IUnknown#Release]
    * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
	*/
ExportedByCATGMOperatorsInterfaces CATICGMTopWire *CATCGMCreateTopWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  int iNbCurves,
  CATCurve **iCurves,
  CATCrvLimits *iLimits,
  short *iOrientations);

#endif /* CATICGMTopWire_h_ */
