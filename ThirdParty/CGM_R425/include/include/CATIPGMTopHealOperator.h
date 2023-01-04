#ifndef CATIPGMTopHealOperator_h_
#define CATIPGMTopHealOperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCurve;
class CATEdge;
class CATGeoFactory;
class CATMathPoint;
class CATShell;
class CATTopData;
class CATVertex;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopHealOperator;

/**
* Class defining the Topological Healing operator on body with given scars to be treated.
* Topological Healing will not modify the input surfaces, only the curves will be recomputed.
* Hence, only the tangency component gap will be healed, and the normal component will remain.
* Please use the Geometrical Healing in order to modify the surfaces and heal all components of the gaps.
*<br>
* The CATIPGMTopHealOperator operator follows the global frame of the topological operators 
* and satisfies the smart mechanism: the input bodies are not modified. A new resulting body 
* is created, possibly sharing data with the input body.
*<ul>
* <li>A CATIPGMTopHealOperator operator is created with the <tt>CATPGMCreateTopHealOperator</tt> global function:
* It must be directly deleted after use with the usual C++ <tt>delete</tt> operator. It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method.
*<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory. 
*</ul>
*/
/*
* The CATIPGMTopHealOperator operator doesn't support cutting information :
* it will throw an error if cutting information are detected on 
* CATCells to be healed.
* The CATIPGMTopHealOperator operator doesn't support LyingOn information.
* There is no check of such a situation, it is the caller responsability to avoid this.
*/
//class ExportedByTopExtLight CATIPGMTopHealOperator : public CATIPGMTopOperator
class ExportedByCATGMOperatorsInterfaces CATIPGMTopHealOperator: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopHealOperator();

  /**
 * Add a scar edge to heal.
 * @param iScarEdge
 * The pointer to the scar edge. This edge must belong to the input shell.
 * An error "Invalid imput data" is thrown if not.
 */
  virtual void AddScarEdge(CATEdge *iScarEdge) = 0;

  /**
 * Add a scar vertex to heal.
 * @param iScarVertex
 * The pointer to the scar vertex. This vertex must belong to the input shell.
 * An error "Invalid imput data" is thrown if not.
 */
  virtual void AddScarVertex(CATVertex *iScarVertex) = 0;

  /**
 * Add a frozen edge.
 * @param iFrozenEdge
 * The pointer to the frozen edge. A frozen edge must not be affected by the healing operator.
 * This edge must belong to the input shell. An error "Invalid input data" is thrown if not.
 */
  virtual void AddFrozenEdge(CATEdge *iFrozenEdge) = 0;

  /**
 * Method to call in order to filter the input edges to Heal.
 * @param iTriggerGapValue 
 * The edges added with the AddScarEdge method are not healed 
 * if their Gap is smaller than iGapValue.
 * The TriggerValue has to be greater than the resolution, otherwise
 * an error is thrown.
 */
  virtual void SetEdgeGapTriggerValue(double iTriggerGapValue) = 0;

  /**
 * Method to call in order to filter the input vertices to Heal.
 * @param iTriggerGapValue 
 * The vertices added with the AddScarVertex method are not healed 
 * if their Gap is smaller than iGapValue.
 * With the SetGlobalHealing method, the vertices are not healed 
 * if their Gap is smaller than iGapValue.
 * The TriggerValue has to be greater than the resolution, otherwise
 * an error is thrown.
 */
  virtual void SetVertexGapTriggerValue(double iTriggerGapValue) = 0;

  /**
 * Method to call in order to allow more surface extrapolation
 * This method should not be called by users who care for model data size
 * @param iLevelExtrapol 
 * Only iLevel == 1 is acceptable today.
 */
  virtual void SetSurfaceExtrapolationLevel(short iLevel) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopHealOperator(); // -> delete can't be called
};

/**
 * Creates a CATIPGMTopHealOperator operator with one shell to heal
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iPart
 * The pointer to the body to heal.
 * @param iShell
 * The pointer to the shell to heal.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopHealOperator *CATPGMCreateTopologicalHealing(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iPart,
  CATShell *iShell);

#endif /* CATIPGMTopHealOperator_h_ */
