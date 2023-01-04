#ifndef CATICGMTopClashOperator_h_
#define CATICGMTopClashOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATGeoFactory;
class CATTopClashOperatorExt;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopClashOperator;

/** 
 * Operator to detect whether two bodies clash. 
 * The intersection if any, can be computed.
 * By default, not to impede performances the intersection is not calculated.
 * The <tt>SetOnlyDiagnosticRequired</tt> method must be set to FALSE in order to generate a result, 
 * otherwise no result is generated.
 * <br>To use the CATICGMTopClashOperator:
 * <ul><li>Create it the <tt>CATCGMCreateTopClashOperator</tt> global function.
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the diagnosis with the <tt>GetDiagnostic</tt> method.
 * <li>Retrieve the intersection body, if any with the <tt>GetResult</tt> method. 
 * <li>Release with the usual C++ <tt>Release</tt> method after use.</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopClashOperator: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopClashOperator();

  /**
  * Specifies whether only the clash diagnosis is to be issued.
  * The intersection body is not computed if the method is not called or called but set to TRUE.
  * @param iOnlyDiagnostic
  * If TRUE, only the diagnosis is computed. The algorithm interrupts as soon as an intersection
  * between the two bodies is detected. NO RESULT is generated (the resulting body is NULL).
  */
  virtual void SetOnlyDiagnosticRequired(CATBoolean iOnlyDiagnostic) = 0;

#ifdef CATIACGMV5R22

  /**
   * Applies only when the diagnosis is required.
   * Tests the inclusion of a domain of one body inside a volume of the other.
   * By default, the inclusion is tested.
   * @param iTestVolmeInclusion
   * If TRUE, the operator tests the inclusion of a domain of one body inside a volume of the other.
   * If FALSE, and a domain of one body is inside a volume of the other, without touching the faces, GetDiagnostic returns FALSE.
  */
  virtual void SetTestVolumeInclusion(CATBoolean iTestVolumeInclusion) = 0;

#endif

  /**
  * Returns the clash diagnosis.
  * @return
  * TRUE if the two bodies clash.
  */
  virtual CATBoolean GetDiagnostic() = 0;

  /**
  * Returns the body resulting from the clash operation. This body can be of any dimension.
  * @return
  * The created body.
  */
  virtual CATBody *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopClashOperator(); // -> delete can't be called
};

/**
 * Creates an operator to test the clash of two bodies and possibly generate the intersection between the two bodies.
 * Just testing whether the bodies clash is performed through the <tt>SetOnlyDiagnosticRequired</tt> method.
 * Not using this method or using it with the FALSE option generates a result (if any).
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The CATTopData.
 * @param iBody1
 * The first body.
 * @param iBody2
 * The second body.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To release with the <tt>Release</tt> method.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopClashOperator *CATCGMCreateTopClashOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody1,
  CATBody *iBody2);

#endif /* CATICGMTopClashOperator_h_ */
