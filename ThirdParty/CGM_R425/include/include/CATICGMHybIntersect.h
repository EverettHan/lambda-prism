#ifndef CATICGMHybIntersect_h_
#define CATICGMHybIntersect_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybOperatorImp.h"

class CATExtHybIntersect;
class CATDomain;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybIntersect;

/**
* Class defining the operator that intersects two bodies.
* <br>
* This operator operates on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
* <ul>
*  <li><tt>CATICGMHybIntersect</tt> is created with the <tt>CATCGMCreateTopIntersect</tt> global function.
*  <li>It must be released with the <tt>Release</tt> method after use.
*  <li>It is not streamable. 
*  <li>The intersection can be restricted on a given domain on each body with the methods
*    <tt>SetFirstDomainToIntersect</tt> and <tt>SetSecondDomainToIntersect</tt>
*  <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*  <li>When two coplanar skins are intersected, the returned body is a wire body along the boundary 
* of the intersection.
* </ul>
* @see CATCGMCreateTopIntersect
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybIntersect: public CATICGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATICGMHybIntersect();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

  /**
    * Defines which domain of the first body must be intersected.
    * @param iDomainOnFirstBody
    * The pointer to the domain to intersect.
    */
  virtual void SetFirstDomainToIntersect(CATDomain *iDomainOnFirstBody) = 0;

  /**
    * Defines which domain of the second body must be intersected.
    * @param iDomainOnSecondBody
    * The pointer to the domain to intersect.
    */
  virtual void SetSecondDomainToIntersect(CATDomain *iDomainOnSecondBody) = 0;

#ifdef CATIACGMV5R23
  /**
  * (De)activates the detection of cells which are tangent to each other.
  * The tangent cells are retrieved by using the <tt>GetTangentDesignCells</tt> method.
  * <pre>
  * pIntersectOpe->SetWarningOnTangentDesign(1);
  *  ...
  * pIntersectOpe->Run();
  * CATBody *pBody =  pIntersectOpe->GetResult();
  * if  (pIntersectOpe->IsResultTangentDesign())
  * {
  *       CATLISTP(CATCell)  ListOfCells;
  *       pIntersectOpe->GetTangentDesignCells(ListOfCells);
  * ...
  * }
  * </pre>
  * @param yes_or_no
  * <ul>
  * <li>0: deactivates the "tangent design" mode
  * <li>1: activates the "tangent design" mode.
  * </ul>
  */
  virtual void SetWarningOnTangentDesign(int yes_or_no = 1) = 0;

  /**
  * Retrieves the tangent design mode.
  * @return
  * <ul>
  * <li>0: the "tangent design" mode is not activated
  * <li>1: the "tangent design" mode is activated.
  * </ul>
  */
  virtual int GetTangentDesignMode() const = 0;

  /**
  * Retrieves the result of the tangent design analysis.
  * @return
  * <ul>
  * <li>0: no tangent cells have been detected
  * <li>1: tangent cells have been detected.
  * </ul>
  */
  virtual int IsResultTangentDesign() const = 0;

  /**
  * Retrieves the list of tangent cells.
  * <pre>
  * pIntersectOpe->SetWarningOnTangentDesign(1);
  * ...
  * pIntersectOpe->Run();
  * CATBody *pBody =  pIntersectOpe->GetResult();
  * if  (pIntersectOpe->IsResultTangentDesign())
  * {
  *   CATLISTP(CATCell)  ListOfCells;
  *   pIntersectOpe->GetTangentDesignCells(ListOfCells);
  *   ...
  * }
  * </pre>
  * @param oListOfCells
  * The list of tangent cells.
  * @return
  * <ul>
  * <li>0: no tangent cells have been detected
  * <li>1: tangent cells have been detected.
  * </ul>
  */
  virtual int GetTangentDesignCells(CATLISTP(CATCell) &oListOfCells) const = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybIntersect(); // -> delete can't be called
};

#endif /* CATICGMHybIntersect_h_ */
