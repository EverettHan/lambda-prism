#ifndef CATIPGMTopSweepWireSkinCircle_h_
#define CATIPGMTopSweepWireSkinCircle_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopSweepWireSkin.h"

class CATLaw;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopSweepWireSkinCircle;

/**
 * @level Protected
 * @usage U1
 */
/**
 * Class defining the topological operator that creates a sweep between a skin body and a wire body.
 *<br>The sweep is defined by
 * <ul>
 * <li>a skin body, to which the generated sweep is tangent and defining the first extremity of the sweep.
 * <li>a wire guide, defining the second extremity.
 * <li>a spine wire body:  defines the moving plane (orthogonal to the spine) that is
 * swept along the spine. In this moving plane, the sweep is an arc of circle tangent to the skin body 
 * and limited by the wire body.
 * </ul>
 * As several solutions can be found, signatures are defined to distinguish them
 * <ul>
 * <li>signature with regards to the skin orientation: the solution is on the semi-space defined by the
 * normal to the skin, or in the opposite semi-space, or in both.
 * <li>signature with respect to the wire orientation: the wire, the normal to the skin and the tangent
 * to the profile are counter clockwise or not.
 * <li>for a same skin and wire signatures, the rank of the solution.
 * </ul>
 * This operator follows the general scheme of the topological operators producing several resulting bodies:
 * <ul>
 *<li> Create the operator with the global function <tt>CATTopCreateSweepWireSkinCircle</tt>,
 *<li> Set the parameters,
 *<li> Run,
 *<li> Get the resulting bodies (in this case, use the iterator on the resulting bodies, because
 * several bodies can be solution of the computation).
 *<li> Delete the operator.
 *</ul>
 * Sample:
 * <pre> 
 * CATIPGMTopSweepWireSkinCircle * pOp =  CATPGMCreateTopSweepWireSkinCircleVariable(factory, Skin, Wire, Spine, Law);
 * pOp->Run();
 * pOp->BeginningResult();
 * int nbBodies = pOp->GetNumberOfResults();
 * for (int iBody = 1 ; iBody <= nbBodies ; iBody ++)
 * {
 *   pOp->NextResult();
 *   CATBody * pCurBody = pOp->GetResult();
 * }  
 * pOp->Release();
 *</pre>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepWireSkinCircle: public CATIPGMTopSweepWireSkin
{
public:
  /**
   * Constructor
   */
  CATIPGMTopSweepWireSkinCircle();

  /** @nodoc */
  virtual int Run() = 0;

  /** @nodoc */
  virtual CATSweepProfileInfo *GetProfileInfo() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopSweepWireSkinCircle(); // -> delete can't be called
};

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepWireSkinCircle *CATPGMCreateTopSweepWireSkinCircle(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iSupportShell,
  CATBody *iGuide,
  CATBody *iSpine,
  double iRadius);

/** @nodoc
 * @return [out, IUnknown#Release]
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopSweepWireSkinCircle *CATPGMCreateTopSweepWireSkinCircle(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iSupportShell,
  CATBody *iGuide,
  CATBody *iSpine,
  CATLaw *iRadiusLaw,
  CATBoolean iRemoveGuide = FALSE,
  CATBoolean iRemoveSpine = FALSE);

#endif /* CATIPGMTopSweepWireSkinCircle_h_ */
