#ifndef CATIPGMHybIntersect_h_
#define CATIPGMHybIntersect_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"
#include "CATIACGMLevel.h"

class CATExtHybIntersect;
class CATShell;
class CATLISTP(CATCell);
/**
 * @level Protected
 * @usage U1
 */
extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybIntersect;

/**
* Class defining the operator that intersects two bodies.
*<br>
* This operator operates on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li><tt>CATIPGMHybIntersect</tt> is created with the <tt>CATPGMCreateTopIntersect</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The intersection can be restricted on a given domain on each body with the methods
* <tt>SetFirstDomainToIntersect</tt> and <tt>SetSecondDomainToIntersect</tt>
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*  <li>When two coplanar skins are intersected, the returned body is a wire body along the boundary 
* of the intersection.
*</ul>
* @see CATPGMCreateTopIntersect
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybIntersect: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybIntersect();

  /** 
  * @nodoc
  * Runs the operator (Empty macro in customer release mode; no effect on generated code).
  */
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

  /**
   * @nodoc
   * @param iYesOrNo
   * Set the boundary mode to the operator (internal use only).
   */
  virtual void SetBoundaryResultMode(int iYesOrNo = 1) = 0;

  /**
   * @nodoc
   * Get the boundary mode to the operator (internal use only).
   * @return 
   * The boundary mode:
   * <ul>
   * <li>0: the boundary mode is activated
   * <li>1: the boundary mode is deactivated.
   * </ul>
   */
  virtual int GetBoundaryResultMode() const = 0;

  /**
   * @nodoc
   * Set the OnShell Mode to the operator (internal use only).
   */
  virtual void SetOnShellMode(CATShell *Support, int iYesOrNo = 1) = 0;

  /**
   * @nodoc
   * Get the OnShell Mode to the operator (internal use only).
   */
  virtual int GetOnShellMode() const = 0;

  /** 
  * (De)activates the detection of cells which are tangent to each other.
  * The tangent cells are retrieved by using the <tt>GetTangentDesignCells</tt> method.
  * <pre>
  * pIntersectOpe->SetWarningOnTangentDesign(1);
  *  ...
  * pIntersectOpe->Run(); 
  * CATBody *pBody =  pIntersectOpe->GetResult();
  * if  (pIntersectOpe->IsResultTangentDesign())  
  *	{  
  *		  ListPOfCATCell  ListOfCells;  
  *		  pIntersectOpe->GetTangentDesignCells(ListOfCells); 
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
  *	{  
  *	  ListPOfCATCell  ListOfCells;  
  *	  pIntersectOpe->GetTangentDesignCells(ListOfCells); 
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

  /** @nodoc */
  virtual void SetBooleanOperationWillFollow(int yes_or_no = 1) = 0;

  /** @nodoc */
  virtual int IsBooleanOperationWillFollow() const = 0;

#ifdef CATIAR425

    /** @nodoc
    * Extrapolation mode
    * for the extrapolation of the intersection result wire on the SupportSurface
    * @param iExtrapolationMode
    * <br><b>Legal values</b>:
    * <dl><dt><tt>0</tt><dd> No Extrapolation.
    *     <dt><tt>1</tt><dd> Extrapolation in tangency continuity. </dl>
    *     <dt><tt>2</tt><dd> Extrapolation in curvature continuity. </dl>
    */
  void SetExtrapolationMode(short iExtrapolationMode = 0);
  void GetExtrapolationMode(short &oExtrapolationMode);

#endif

#ifdef CATIACGMV5R21
  /**
   * @nodoc
   *
   * Sets the state of single support mode. Typically, the edges in the
   * resulting wire can each contain several p-curves referring to several
   * differenct surfaces from the input bodies. In single support mode, the
   * operator chooses and retains as the geometry of each edge p-curves
   * referring to a surface in the reference body.  The reference body should
   * be one of the input bodies. Currently, also, the reference body should
   * contain only one surface.  Single support mode is only available when the
   * input bodies both contain 2D domains. The result of this operator
   * normally has lying-on links, but these are removed from the result in
   * single support mode.
   *
   * @param iYesOrNo
   * <ul>
   * <li>0: deactivates "single support" mode.
   * <li>1: activates "single support" mode.
   * </ul>
   * @param iReferenceBody
   * Body containing the surface geometry which will be referenced in the result.
   */
  virtual void SetSingleSupportMode(int iYesOrNo, CATBody *iReferenceBody) = 0;

  /**
   * @nodoc
   * Retrieves the values of the parameters for "single support" mode.
   * @param iReferenceBody
   * Body containing the surface geometry which will be referenced in the result.
   * @return
   * <ul>
   * <li>0: "single support" mode is not activated
   * <li>1: "single support" mode is activated.
   * </ul>
   */
  virtual int GetSingleSupportMode(CATBody *&oReferenceBody) const = 0;

#endif

  /** @nodoc  */
  virtual CATExtHybIntersect *GetHybIntersectExtensible() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybIntersect(); // -> delete can't be called
};

#endif /* CATIPGMHybIntersect_h_ */
