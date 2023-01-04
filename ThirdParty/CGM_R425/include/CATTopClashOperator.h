#ifndef CATTopClashOperator_H
#define CATTopClashOperator_H

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
* @level Protected
* @usage U3
*/

#include "CATIACGMLevel.h" // automatic treatment EB_2014_04_16
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"

class CATGeoFactory;
class CATBody;
class CATTopData;
class CATTopClashOperatorExt;

/** 
 * Operator to detect whether two bodies clash. 
 * The intersection if any, can be computed.
 * By default, not to impede performances the intersection is not calculated.
 * The <tt>SetOnlyDiagnosticRequired</tt> method must be set to FALSE in order to generate a result, 
 * otherwise no result is generated.
 * <br>To use the CATTopClashOperator:
 * <ul><li>Create it the <tt>CATCreateTopClashOperator</tt> global function.
 * <li> <tt>Run</tt> the operator
 * <li>Retrieve the diagnosis with the <tt>GetDiagnostic</tt> method.
 * <li>Retrieve the intersection body, if any with the <tt>GetResult</tt> method. 
 * <li>Delete with the usual C++ <tt>delete</tt> operator after use.</ul>
 */
class ExportedByCATTopologicalObjects CATTopClashOperator : public CATTopOperator
{
  CATCGMVirtualDeclareClass(CATTopClashOperator);

protected:
  /**
  * @nodoc
  */
  CATTopClashOperator(CATGeoFactory * iFactory, CATTopData * iTopData, CATTopClashOperatorExt * iExtensible);

public:

  virtual ~CATTopClashOperator();

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
  virtual CATBody * GetResult() = 0;

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
 * @return
 * The pointer to the created operator. To delete with the usual C++ <tt>delete</tt> operator after use.
 */
ExportedByCATTopologicalObjects CATTopClashOperator * CATCreateTopClashOperator(
  CATGeoFactory * iFactory,
  CATTopData * iTopData,
  CATBody * iBody1,
  CATBody * iBody2);

#endif

