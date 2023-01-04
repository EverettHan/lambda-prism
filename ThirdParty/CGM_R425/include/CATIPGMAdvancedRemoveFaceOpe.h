#ifndef CATIPGMAdvancedRemoveFaceOpe_h_
#define CATIPGMAdvancedRemoveFaceOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2013

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPersistentOperator.h"

#include "ListPOfCATFace.h"
#include "CATListOfInt.h"

class CATAdvancedRemoveFaceImpl;
class CATBody;
class CATFace;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMAdvancedRemoveFaceOpe;

/**
 * Class defining a topological operator which removes a set of faces from a volume or a skin.<br>
 * This operator does not change the dimension of the body: a volume remains a volume, a skin remains a skin.<br>
 * Note that the specified faces to be removed are not propagated, you need to provide a consistent set of faces.
 * The operation completes when the body can be closed by extrapolation of the faces which were adjacent to
 * the ones removed. Neighbouring faces extrapolations should not generate any tangency configuration.<br>
 * Unlike CATIPGMRemoveFace operator, CATIPGMPersistentOperator is able to apply special treatments
 * when it is judged necessary for the operation to succeed. For instance, local regularization can be applied
 * in order to avoid twisting of extrapolated geometries.<br>
 * To use this operator, you must:
 * <ul>
 * <li>Create it with the <tt>CATPGMCreateAdvancedRemoveFaceOpe</tt> global function
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> or <tt>Append</tt> methods.
 * <li>Run it
 * <li>Get the result with the <tt>GetResult</tt> method. If you do not want to keep the resulting body,
 *    use the @href CATICGMContainer#Remove method to remove it from the geometric factory, after the operator deletion.
 * <li>Release the operator with the <tt>Release</tt> method after use.
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedRemoveFaceOpe: public CATIPGMPersistentOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMAdvancedRemoveFaceOpe();

  /**
  * Appends a list of faces to be removed.
  * @param iFacesToRemove
  * The list of pointers to faces to remove.
  */
  virtual void Append(const CATLISTP(CATFace) &iFacesToRemove) = 0;

  /**
  * Appends a limiting body related to a face to be partially removed.
  * The limiting body must be mono-shell mono-face.
  * @param iFaceToRemove
  * The face to relimit.
  * @param iLimitingBody
  * The limiting body.
  * @param iOri
  * The orientation related to the shell indicating the side to remove.
  */
  virtual void AppendLimiting(
    CATFace *iFaceToRelimit,
    CATBody *iLimitingBody,
    CATOrientation iOri) = 0;

  /**
  * Allow a local smoothing of a tricky faces
  * @param iAllowLocalRegul
  * 0 - Regularization is disabled
  * 1 - Allow the operator to apply a regularization on the input body to avoid surfaces to twist when extrapolated.
  *     This mode is used by default at the creation of the operator.
  **/
  virtual void SetAllowLocalRegularization(short iAllowLocalRegularization) = 0;

  /**
  * Sets the deviation allowed by the user.
  * @param iDeviation
  * Represents the maximum value of the deviation. This value must be positive.
  * Default value is 100 * factory resolution
  **/
  virtual void SetDeviationAllowed(CATLength iDeviation) = 0;

  /**
  * Returns the complete list of faces when the operation cannot fully complete .
  * The list can include faces that could not be removed but also pathological closing faces.
  * @param oAllTrickyFaces
  * The list of tricky faces
  * @param oAllDiags
  * The list of diagnoses.
  */
  virtual void GetAllTrickyFaces(
    CATLISTP(CATFace) &oAllTrickyFaces,
    CATListOfInt &oAllDiags) = 0;

  /**
  * @nodoc
  * Appends a list of faces allowed to be removed
  * @param iCandidateFace
  * The list of pointers to faces to potentially remove.
  */
  virtual void AppendCandidate(const CATLISTP(CATFace) &iCandidateFaces) = 0;

  /**
  * @nodoc
  * Indicates that specified faces to remove are all fillets
  * @param iRemoveFilletsMode = 1 enables fillet dedicated treatments.
  * This mode is disabled by default.
  */
  virtual void SetRemoveFilletsMode(short iRemoveFilletsMode = 1) = 0;

  /**
  * @nodoc
  * Performance mode.
  * Allow the use of performance optimizations if operation is judged localized enough.
  * Available only for fillet removal.
  */
  virtual void SetTryLocalRemoveFace(short iTryLocalRemoveFace) = 0;

  /**
  * @nodoc
  * Allow the operator to return a partial result if some subsets
  * of connected faces cannot be removed.
  * Tricky faces can be retrieved by calling GetAllTrickyFaces() method.
  */
  virtual void SetPartialRemoveFaceAllowed(short iPartialRemoveFaceAllowed) = 0;

  /**
  * @nodoc
  * Enables or disables twist detection.
  * @param iTwistDetection
  * 0 - Twist detection is disabled : result body may lie on twisted surfaces.
  * 1 - Twist detection is enabled : face removal fails if at least one of the extrapolated surfaces is twisted
  *     This mode is used by default at the creation of the operator.
  */
  virtual void SetTwistDetection(short iTwistDetection) = 0;

  /**
  * @nodoc
  * Indicates if the Delta of the RemoveFace has to be computed
  * /!\ Incompatible with Partial mode
  */
  virtual void SetDeltaShapeComputation(short iDeltaShapeComputation) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMAdvancedRemoveFaceOpe(); // -> delete can't be called
};

// ---------------------
// CATCreateRemoveFaceOpe
// ---------------------
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedRemoveFaceOpe *CATPGMCreateAdvancedRemoveFaceOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iReferenceBody);

/** @nodoc */
ExportedByCATGMOperatorsInterfaces CATIPGMAdvancedRemoveFaceOpe *CATPGMCreateAdvancedRemoveFaceOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iReferenceBody);

#endif /* CATIPGMAdvancedRemoveFaceOpe_h_ */
