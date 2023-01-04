#ifndef CATICGMTopSweepWireSkin_h_
#define CATICGMTopSweepWireSkin_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopMultiResult.h"

class CATSweepProfileInfo;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSweepWireSkin;

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
 *<li> Create the operator with the global function @href CATCGMCreateTopSweepWireSkinCircle 
 *<li> Set the parameters,
 *<li> Run,
 *<li> Get the resulting bodies (in this case, use the iterator on the resulting bodies, because
 * several bodies can be solution of the computation).
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 * Sample:
 * <pre> 
 * CATICGMTopSweepWireSkinCircle * pOp =  CATCGMCreateTopSweepWireSkinCircle(factory,Skin,Wire,Spine);
 * pOp->Run();
 * pOp->BeginningResult();
 * int nbBodies = pOp->GetNumberOfResults();
 * for (int iBody = 1 ; iBody <= nbBodies ; iBody ++)
 * {
 *   pOp->NextResult();
 *   CATBody * pCurBody = pOp->GetResult(pReport);
 * }  
 * pOp->Release();
 *</pre>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopSweepWireSkin: public CATICGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATICGMTopSweepWireSkin();

  /**
 * Defines the signature of the desired results with regards to the skin orientation.
 * @param iOrientation
 * The semi-space to which the solution belongs.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The results are in the semi-space defined by the normal to the skin.
 * <dt><tt>-1</tt></dt><dd> The results are in the semi-space defined by the opposite to the normal to the skin.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The results change of semi-space along the spine. 
 * </dl>
 */
  virtual void SetShellOrientation(const int iOrientation) = 0;

  /**
 * Defines the signature of the desired results with regards to the wire orientation.
 * @param iOrientation
 * The orientation of the trihedron defined by the the wire, the normal to the skin and
 * the tangent to the profile.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 */
  virtual void SetGuideOrientation(const int iOrientation) = 0;

  /**
 * Retrieves the signature relative to the current resulting body.
 * @param ioShellOrientation
 * The signature with regards to the skin orientation.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The results are in the semi-space defined by the normal to the skin.
 * <dt><tt>-1</tt></dt><dd> The results are in the semi-space defined by the opposite to the normal to the skin.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The results change of semi-space along the spine. 
 * </dl>
 * @param ioWireOrientation
 * The signature with regards to the wire orientation.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 * @param ioIndex
 * The rank (beginning at <tt>1</tt>) of the current body inside 
 * a given couple (<tt>ioShellOrientation, ioWireOrientation</tt>)
 */
  virtual void GetResultInformation(
    int &ioShellOrientation,
    int &ioWireOrientation,
    int &ioIndex) = 0;

  /**
 * Runs <tt>this</tt> operator.
 * <br>To retrieve the resulting bodies, use the iterator on the bodies provided by @href CATICGMTopMultiResult.
 */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSweepWireSkin(); // -> delete can't be called
};

#endif /* CATICGMTopSweepWireSkin_h_ */
