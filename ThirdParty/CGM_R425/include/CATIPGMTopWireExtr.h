#ifndef CATIPGMTopWireExtr_h_
#define CATIPGMTopWireExtr_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopWire.h"

class CATBody;
class CATCGMJournalList;
class CATCrvLimits;
class CATCrvParam;
class CATCurve;
class CATEdge;
class CATEdgeCurve;
class CATGeoFactory;
class CATMacroPoint;
class CATPointOnEdgeCurve;
class CATVertex;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopWireExtr;

/** 
* Class representing the operator that creates a wire body from one or several curves. 
* <br>To use the CATIPGMTopWireExtr:
* <ul><li>Create it with one of the <tt>CATCreateTpoWire</tt> global methods. 
* You must order the input curves and precise the
* limits of each, as well as their relative orientation, such that the end of
* one curve (possibly reversed) is the beginning of the following.
* <br>Every created edge is positively oriented in the wire. 
* <li>If needed, tune some parameters with the <tt>SetXxx</tt> methods.
* <li> <tt>Run</tt> the operator
* <li>Retrieve the created body (frozen by default) with the <tt>GetResult</tt> method. 
* <li>Release the operator with the <tt>Release</tt> method after use.</ul>
* If there is only one closed curve, the operator creates a wire with two edges.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopWireExtr: public CATIPGMTopWire
{
public:
  /**
   * Constructor
   */
  CATIPGMTopWireExtr();

  virtual void SetResultInTargetBody(CATBody *iTB) = 0;

  virtual void GetSemiClosureParam(CATCrvParam &Param) = 0;

  virtual void SetSemiClosureParam(const CATCrvParam &Param) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopWireExtr(); // -> delete can't be called
};

/**
* Creates an operator to add a new edge at the end of an existing wire body.
* <br>To adhere to the smart mechanism, the input body is not modified. The
* touched cells are duplicated in the resulting body, which shares the
* non modified cells with the input body.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iBody
* The pointer to the body to modify. It must only contain one wire.
* @param iEndVertex
* The pointer to one extremity vertex.
* @param iExtrapolationCurve
* The pointer to the curve to add. The current limits of the curve define the
* extremity of the new edge.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopWireExtr *CATPGMCreateTopWire(
  CATGeoFactory *factory,
  CATTopData *iData,
  CATBody *iBody,
  CATVertex *iEndVertex,
  CATCurve *iExtrapolationCurve);

/**
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopWireExtr *CATPGMCreateTopOldWire(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  int iNbCurves,
  CATCurve **iCurves,
  CATCrvLimits *iLimits,
  short *iOrientations);

#endif /* CATIPGMTopWireExtr_h_ */
