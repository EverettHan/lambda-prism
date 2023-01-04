#ifndef CATICGMThickenOp_h_
#define CATICGMThickenOp_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATDynOperatorDef.h"
#include "CATCollec.h"

class CATBody;
class CATEdge;
class CATGeoFactory;
class CATGeometry;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMThickenOp;

/**
* Class defining the topological operator that thickens a skin body into a volume body.
* <br>A global offset value can be defined on the body, or faces to thicken can be individually chosen as well
* as the corresponding offset values.
*<br>
* This operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the
* input body is not modified. A new resulting body is created, 
* possibly sharing data with the input body. A CATICGMThickenOp operator is not streamable.
* To use it:
*<ul>
* <li>Create it with the <tt>CATCGMCreateThickenOp</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
* <li>Run it
* <li>Get the result with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*<li>Release the operator with the <tt>Release</tt> method after use.
*</ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATICGMThickenOp: public CATICGMTopOperator
{
public:
   /**
   * Constructor
   */
   CATICGMThickenOp();

   /**
   * This API must not be used.
   * Defines offsets on individual faces.
   * @param iFaces
   * The list of pointer to the faces.
   * @param iOffset1
   * The smaller value of the offset in the side of the natural orientation of the skin.
   * @param iOffset2
   * The larger value of the offset in the side of the natural orientation of the skin.
   */
   virtual        void       Append                                 (const CATLISTP(CATFace)         & iFaces                   ,
                                                                           double                      iOffset1                 ,
                                                                           double                      iOffset2                 = 0.) = 0;

   /**
   * Defines how borders are transformed in the neighborhood of sharp edges.
   * @param iSharpBorderOptimisation
   * <br><b>Legal values:</b>
   * <dl><dt>0</dt><dd>Optimization not required
   * <dt>1</dt><dd>Optimization required (Skin handled like a Volume)
   * </dl>
   * This option has no effect when SetCleverRibbonComputation() is set to 1.
   * Default value for optimisation is 1. (Optimization required).
   */
   virtual        void       SetSharpBorderMode                     (       short                      iSharpBorderOptimisation ) = 0;

   /**
   * Defines a Boolean operation between a given body and the result of 
   * <tt>this</tt> operator.
   * @param iOpType
   * The boolean operation type.
   * @param iOperandBody
   * The pointer to the body representing the first operand of the Boolean operation. 
   * The second operand is the result of the thicken.
   * @param iReport
   * A pointer to the journal corresponding to the Boolean operation. This journal can be different
   * from the journal of the thicken operation itself. If <tt>NULL</tt>, the Boolean journal
   * is not written.
   */
   virtual        void       SetBooleanOperation                     (      CATDynBooleanType          iOpType                  ,
                                                                            CATBody                  * iOperandBody             ,
                                                                            CATCGMJournalList        * iReport                  = 0) = 0;

   /**
   * Activates an enhanced algorithm (recommended).
   * @param iCleverRibbonComputation
   * Enhanced algorithm is activated if 1 is specified, otherwise it is not activated.
   */
   virtual        void       SetCleverRibbonComputation              (      short                      iCleverRibbonComputation = 1) = 0;

   /**
   * Runs <tt>this</tt> operator.
   * @return
   * The diagnosis of the computation.
   * <br><b>Legal values</b>: <tt>1</tt> if the computation failed, <tt>0</tt> otherwise. 
   */
   virtual        int        Run                                     () = 0;

   /**
   * Returns the created thickened body.
   * @return
   * The pointer to the result of <tt>this</tt> operator.
   * If you do not want to keep the resulting body, 
   * use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory, after the operator deletion.
   */
   virtual        CATBody  * GetResult                               () = 0;

   /**
   * Returns the body created from the Boolean operation between a given body and the thickened body.
   * @return
   * The pointer to the Boolean result.
   * If you do not want to keep the resulting body, 
   * use the @href CATICGMContainer#Remove method to remove it from the 
   * geometric factory, after the operator deletion.
   */
   virtual        CATBody * GetBooleanResult                         () = 0;

protected:
   /**
   * Destructor
   */
   virtual ~CATICGMThickenOp(); // -> delete can't be called
};

/**
* Creates an operator that thickens a skin body with inside and outside offset values.
* @param iFactory
* The pointer to the factory of the geometry.
* @param iTopData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled.
* @param iBody
* The pointer to the skin body to thicken.
* @param iOffset1
* The smaller value of the offset in the side of the natural orientation of the skin.
* @param iOffset2
* The larger value of the offset in the side of the natural orientation of the skin.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATICGMThickenOp *CATCGMCreateThickenOp(
                                                          CATGeoFactory     * iFactory, 
                                                          CATTopData        * iTopData, 
                                                          CATBody           * iBody, 
                                                          double              iOffset1, 
                                                          double              iOffset2 );

#endif /* CATICGMThickenOp_h_ */
