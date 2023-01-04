#ifndef CATIPGMLimitingBodyCreatorOpe_h_
#define CATIPGMLimitingBodyCreatorOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2021

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDRepOperator.h"

#include "CATSurParam.h"
#include "CATCrvParam.h"

class CATFace;
class CATLimitingBodyCreatorImpl;
class CATVertex;
class CATCurve;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMLimitingBodyCreatorOpe;

/**
 * Class defining a topological operator which creates a limiting body in the context of fillet removal.<br>
 * This operator can be helpful when defining relimitations for e.g. <tt>RemoveFace</tt> operator.<br>
 * To use this operator, you must:
 * <ul>
 * <li>Create it with the <tt>CATPGMCreateLimitingBodyCreatorOpe</tt> global function.
 * <li>Define the fillet face and an appropriate position for the resulting limiting body,
 *     using the <tt>SetXxx</tt> methods (three different types of inputs available).
 * <li><tt>Run</tt> it.
 * <li>Get the result with the <tt>GetResult</tt> method.
 * <li>Delete the operator after use.
 * <li>If you do not want to keep the resulting body,
 *     use the @href CATICGMContainer#Remove method to remove it from the geometric factory, after the operator deletion.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMLimitingBodyCreatorOpe: public CATIPGMDRepOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMLimitingBodyCreatorOpe();

  /**
   * Sets the input body.
   * @param iInputBody
   */
  virtual void SetInputBody(CATBody *iInputBody) = 0;

  /**
   * Sets the fillet face to relimit.
   * @param iLimitedFace
   */
  virtual void SetLimitedFace(CATFace *iLimitedFace) = 0;

  /**
   * 1st use case: input SurParam representing
   * the point on the fillet surface
   * where the limiting body will be created.
   * @param iSurParam
   */
  virtual void SetSurParam(const CATSurParam &iSurParam) = 0;

  /**
   * 2nd use case: input curve and CrvParam representing
   * the point on the fillet surface
   * where the limiting body will be created.
   * Ignored in case of 1st use case input.
   * @param iCurve
   * @param iCrvParam
   */
  virtual void SetCurve(CATCurve *iCurve, const CATCrvParam &iCrvParam) = 0;

  /**
   * 3rd use case: input vertex representing
   * the point on the fillet surface
   * where the limiting body will be created.
   * Ignored in case of 1st or 2nd use case.
   * @param iVertex
   */
  virtual void SetVertex(CATVertex *iVertex) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMLimitingBodyCreatorOpe(); // -> delete can't be called
};

/**
* Creates a CATIPGMLimitingBodyCreatorOpe operator.
* @param iFactory
* A pointer to the factory.
* @param iTopData
* A pointer to the topological data.
* @param iInputBody
* A pointer to the input body.
* @return
* The operator.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMLimitingBodyCreatorOpe *CATPGMCreateLimitingBodyCreatorOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iInputBody = NULL,
  CATFace *iLimitedFace = NULL);

#endif /* CATIPGMLimitingBodyCreatorOpe_h_ */
