#ifndef CATICGMHLROperator_h_
#define CATICGMHLROperator_h_

// COPYRIGHT DASSAULT SYSTEMES 2014

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMOperator.h"

class CATBody;
class CATGeoFactory;
class CATHLROperatorImpl;
class CATHLRResult;
class CATMathPlane;
class CATMathTransformation;
class CATPlane;
class CATSoftwareConfiguration;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHLROperator;

/**
 * Class defining an operator that computes the edge visibility information of a model for the specified views.
 * A view is specified in terms of a <tt>CATMathPlane</tt> which defines the view direction and the projection support.
 * It is possible to define multiple views and then run the operator once.
 * <ul>
 *     <li> A <tt>CATICGMHLROperator</tt> operator is created with the <tt>CATCGMCreateHLROperator</tt> global functions.
 *     <li> It is the user's responsibility to release the operator after it has been used.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMHLROperator: public CATICGMOperator
{
public:
  /**
   * Constructor
   */
  CATICGMHLROperator();

  /**
 * Adds an instance of a <tt>CATBody</tt> to the input HLR scene.
 * This body can be contained by another factory than the input one,
 * but its scale has to be smaller or equal to the scale of the input factory.
 * @param iBody
 * The pointer to the <tt>CATBody</tt> to add to the scene.
 * @param iTransformation
 * The <tt>CATMathTransformation</tt> to apply on the input body.
 * @return
 * The unique integer value as the "Identifier" of the current instance (<tt>CATBody</tt> is associated with a specific position matrix).
 */
  virtual CATULONG32 AddBodyInstance(
    CATBody *iBody,
    CATMathTransformation const &iTransformation) = 0;

  /**
 * Adds a <tt>CATBody</tt> to the input HLR scene.
 * This body can be contained by another factory than the input one,
 * but its scale has to be smaller or equal to the scale of the input factory.
 * @param iBody
 * The pointer to the <tt>CATBody</tt> to add to the scene.
 * @param iTransformation
 * The pointer to the <tt>CATMathTransformation</tt> to apply to the input body.
 * @return
 * The unique integer value as the "Identifier" of the current instance.
 */
  virtual CATULONG32 AddBody(CATBody *iBody) = 0;

  /**
 * Activates the computation of clashes between different bodies of the scene.
 * The caller has to take into account the cost of this treatment and activate this mode only if the scene is known to contain overlapping bodies.
 * By default, the <tt>ClashComputationMode</tt> is disabled.
 */
  virtual void EnableClashComputationMode() = 0;

  /**
 * Defines a mathematical plane for a new view to be used in the next computation.
 * @param iProjectionPlane
 * The reference to the <tt>CATMathPlane</tt> which defines both the view direction and the projection support.
 */
  virtual void SetProjectionPlane(CATMathPlane const &iProjectionPlane) = 0;

  /**
   * Returns the current result of the HLR computation.
   * @return
   * A <tt>CATHLRResult</tt> pointer.
   * The caller has to release the <tt>CATHLRResult</tt> object after use.
   */
  virtual CATHLRResult *GetResult() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHLROperator(); // -> delete can't be called
};

/**
 * Creates an operator to compute the edge visibility information of a model for the specified views.
 * It is mandatory to call the <tt>SetProjectionPlane</tt> method at least once before running the operator.
 * @param iConfig
 * The pointer to the software configuration (versioning management).  
 * @param iFactory
 * The pointer to the factory to contain the output geometry.
 * @return
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMHLROperator *CATCGMCreateHLROperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig);

/**
 * Creates an operator to compute the edge visibility information of a model for the specified first/single view.
 * @param iConfig
 * The pointer to the software configuration (versioning management).  
 * @param iFactory
 * The pointer to the factory to contain the output geometry.
 * @param iProjectionPlane
 * The reference to the <tt>CATMathPlane</tt> in order to define the first/single view direction and the projection support.
 * @return
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMHLROperator *CATCGMCreateHLROperator(
  CATGeoFactory *iFactory,
  CATSoftwareConfiguration *iConfig,
  CATMathPlane const &iProjectionPlane);

#endif /* CATICGMHLROperator_h_ */
