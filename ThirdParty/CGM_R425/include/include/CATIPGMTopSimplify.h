#ifndef CATIPGMTopSimplify_h_
#define CATIPGMTopSimplify_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Protected
 * @usage U3
 */

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATLISTP(CATCell);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSimplify;

/**
* Class representing the operator that "simplifies" a body or a part of a body.
* <br>
* The simplification operation consists in removing the cells which are not needed 
* for a consistent body topology. 
* <br>
* This operation applies to 3D, 2D and 1D bodies:
* <ul>
* <li>In a solid made up of several cells of CATVolume type, volumes can be merged. The faces between the volumes
* to be simplified are then removed while some faces and edges are merged.
* <li>In a skin made up of several cells of CATFace type, faces can be merged. The edges between the faces
* to be simplified are then removed while some edges are merged.
* <li>In a wire made up of several cells of CATEdge type, edges can be merged.
* The vertices between the edges to be simplified are then removed. 
* </ul>
* The simplification is achieved as far as the geometric modeler rules are satisfied, for example, the C2 continuity
* criteria must be fulfilled all over the faces to be simplified on a skin.
* <br>The CATIPGMTopSimplify operator follows the global frame of the topological operators
* and satisfies the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>A CATIPGMTopSimplify operator is created with the <tt>CATPGMCreateTopSimplify</tt> global function.
* It must be directly released with the <tt>Release</tt> method after use. 
* It is not streamable. 
*<li>The computation is done by the <tt>Run</tt> function. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric container, after the operator deletion.
*</ul>
*<ul>
* <li>Volumes , faces or edges can be simplified.
* <li>During the simplification, new cells are created to replace several adjacent cells 
* linked to the same or equivalent geometry. For example, if a skin made up of two faces
* relying on the same surface is simplified, a new face replacing the two initial faces is created
* <li>The simplification can only be done between adjacent cells of the same domain
* <li>The simplification of edges bordering faces can only be achieved from a 3D or 2D body whose 
* volumes or faces have already been simplified. This case is unlikely to happen as
* the simplication process operates for the cells of all dimensions in a body.
* <li>To specify which part of the body is to be simplified, you can use either <tt>SetCellsToRemove</tt> or
* <tt>SetCellsToSimplify</tt>. However these methods are mutually exclusive. For example, to simplify 
* a solid, you must define either the faces to be removed or the volumes to be simplified.
* <li>To enhance performance, it is strongly recommended to use the <tt>SetCellsToSimplify</tt> 
* method, if you want to simplify only some cells and not the whole body.
*</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSimplify: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSimplify();

  /**
  * Defines the cells to simplify.
  * @param iCellsToSimplify
  * The list of cells to simplify. This restricts the simplification to these cells only.
  * This method can not be called together with the <tt>SetCellsToRemove</tt> method.
  */
  virtual void SetCellsToSimplify(CATLISTP(CATCell) &iCellsToSimplify) = 0;

  /**
  * Defines the cells to remove during simplification.
  * @param iCellsToRemove
  * The list of cells to remove. This restricts the simplification to the cells bounded
  * to these cells only.
  * This method can not be called together with the <tt>SetCellsToSimplify</tt> method.
  */
  virtual void SetCellsToRemove(CATLISTP(CATCell) &iCellsToRemove) = 0;

  /**
   * Runs <tt>this</tt> operator.
   */
  virtual int Run() = 0;

  /**
  * Returns a pointer to the resulting body.
  * <br> Must be called after the <tt>Run</tt> method only once. A second call returns a <tt>NULL</tt>
  * pointer.
  * @return
  * The pointer to the resulting body. Use @href CATICGMContainer#Remove if you do not want to keep it.
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Defines the state of the resulting body.
  * @param iMode
  * The state of the resulting body. 
  * <br><b>Legal values</b>:
  * <dl>
  * <dt>0</dt><dd>The resulting CATBody is not frozen: it can be modified afterwards.
  * <dt>1</dt><dd>The resulting CATBody is frozen: it cannot be modified afterwards.
  * </dl>
  */
  virtual void SetFreezeMode(short iMode = 1) = 0;

  /**
  * @nodoc 
  */
  virtual void SetSpecialMode(const int iSpecialMode) = 0;

  /**
  * Turns on tolerant simplification.
  * The tolerance is specified as a multplier of the model resolution and is used solely
  * to compare the closeness of two surfaces.  Edge gaps may exceed this tolerance, but may
  * not be larger than 100 * model resolution.
  * Currently only simplification of basic canonical surfaces (Planes, Cylinders, Cones, 
  * Spheres and Tori) are supported.
  * @param iRelativeTolerance
  * The value by which to multiply the model resolution.  The permissible values range from 1e-9 to 100.
  */
  virtual void EnableTolerantSimplification(double iRelativeTolerance) = 0;

  #ifdef CATIACGMR418CAA
  /**
  * Enables the maximum simplification regime. In some scenarious better simplification may 
  * be achieved at the expense of a slight performance degradation of the operator. 
  */
  virtual void EnableMaximalSimplification() = 0;
  #endif

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSimplify(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopSimplify operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToSimplify
 * The pointer to the body to simplify.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSimplify *CATPGMCreateTopSimplify(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodyToSimplify);

#endif /* CATIPGMTopSimplify_h_ */
