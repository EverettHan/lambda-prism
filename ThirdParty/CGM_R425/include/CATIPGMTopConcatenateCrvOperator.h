#ifndef CATIPGMTopConcatenateCrvOperator_h_
#define CATIPGMTopConcatenateCrvOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATCell;
class CATGeometry;
class CATSurface;
class CATWire;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopConcatenateCrvOperator;

/**
 * Class defining the operator to reduce the number of edges of a wire body.
 * <br>This reduction is done if a vertex is C2 continuous from both incident edges. In such case,
 * a single edge is created and replaces the two initial edges in the result.
 * This operator follows the general scheme of the topological operators:
 * <ul>
 *<li> Create the operator with the global function <tt>CATPGMCreateTopConcatenateCrvOperator</tt>, which defines
 * the wire to transform
 *<li> Set the parameters
 *<li> Run
 *<li> Get the resulting body
 *<li> Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopConcatenateCrvOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopConcatenateCrvOperator();

  //
  // ADVANCED mode settings
  //-----------------------
  //
  // The following setting methods follow the creation of a CATIPGMTopConcatenateCrvOperator,
  // (see CATPGMCreateTopConcatenateCrvOperator global function)
  //
  /**
  * Defines the tolerance for the continuity in curvature 
  * @param iTolerance
  * The tolerance value. By default, it is set to the factory resolution.
  */
  virtual CATLONG32 SetTolerance(double iTolerance) = 0;

  /**
  * Defines the underlying surface on which wire edges are described and must be concatened.
  * The edges of teh result body will have a single PCurve representation on iSurface.
  * @param iSurface
  * The pointer to the surface.
  * @return
  * Not null in case of error.
  */
  virtual CATLONG32 SetSurface(CATSurface *iSurface) = 0;

  /**
  * @nodoc
  * do not use
  * transformation through operator
  */
  virtual CATCell *GetDescendant(CATCell *iCell) = 0;

  /**
	* Allows you to access the maximum deformation resulting from the geometric concatenation.
	* This deformation is the sum of the C0 concatenation, of the optimisation of the deformation
  * due to the optimisation of the continuities. 
  * This is an evaluation of the max-distance on the control points, what means, it is an upper
  * bound of the exact max-distance (Hausdorf's distance). They should have a similar size.
	*/
  virtual void GetDeformation(double &oDeformation) = 0;

  /**
	* Allows you to access the minimum deformation to concatenate the wire into one curve.
  * This method has to be called after the Run() and is valid only with one curve concatenation.
  * 
	*/
  virtual void GetThresholdValue(double &oThresholdValue) = 0;

  /**
	* impose to concatenate the list of input curves into one curve.
	* The default mode is the concatenation into several curves according to the tolerance
	*/
  virtual void SetOneCurveConcatenationMode(CATLONG32 iMode = 1) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopConcatenateCrvOperator(); // -> delete can't be called
};

//
// creation of operator (ADVANCED mode)
//-------------------------------------
/**
* Creates a topological operator to concatenate :
* @param iFactory
* The factory that creates the resulting body.
* @param iTopData
* The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iWireBody
* The wire which edges will be merged at C2 continuity vertices,
* @return [out, IUnknown#Release]
* A pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopConcatenateCrvOperator *CATPGMCreateTopConcatenateCrvOperator(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody);

#endif /* CATIPGMTopConcatenateCrvOperator_h_ */
