#ifndef CATICGMTopSweepSkinSkinSegment_h_
#define CATICGMTopSweepSkinSkinSegment_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopMultiResult.h"
#include "CATDynFilletRibbon.h"

class CATShell;
class CATSweepInit;
class CATSweepProfileInfo;
class CATSweepTopOp;
class CATICGMTopSweepSkinSkinSegment;
class CATWire;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopSweepSkinSkinSegment;

/**
 * Class defining the topological operator that creates a sweep between a two skin bodies.
 *<br>The sweep is defined by
 * <ul>
 * <li>a skin body, to which the generated sweep is tangent and defining the first extremity of the sweep.
 * <li>a skin body, to which the generated sweep is tangent and defining the second extremity of the sweep..
 * <li>a spine wire body:  defines the moving plane (orthogonal to the spine) that is
 * swept along the spine. 
 * </ul>
 * As several solutions can be found, signatures are defined to distinguish them
 * <ul>
 * <li>signature with regards to the skin orientation: the solution is on the semi-space defined by the
 * normal to the skin, or in the opposite semi-space, or in both.
 * <li>for a same skin1 and skin2 signatures, the rank of the solution.
 * </ul>
 * This operator follows the general scheme of the topological operators producing several resulting bodies:
 * <ul>
 *<li> Create the operator with the global function @href CATCGMCreateTopSweepSkinSkinSegment 
 *<li> Set the parameters,
 *<li> Run,
 *<li> Get the resulting bodies (in this case, use the iterator on the resulting bodies, because
 * several bodies can be solution of the computation).
 *<li> Release the operator with the <tt>Release</tt> method.
 *</ul>
 * Sample:
 * <pre> 
 * CATICGMTopSweepSkinSkinSegment * pOp = CATCGMCreateTopSweepSkinSkinSegment(factory,Skin1,Skin2,Spine);
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
class ExportedByCATGMOperatorsInterfaces CATICGMTopSweepSkinSkinSegment: public CATICGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATICGMTopSweepSkinSkinSegment();

  /**
 * Defines the signature of the desired results with regards to the first skin orientation.
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
  virtual void SetFirstShellOrientation(const int iOrientation) = 0;

  /**
 * Defines the signature of the desired results with regards to the second skin orientation.
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
  virtual void SetSecondShellOrientation(const int iOrientation) = 0;

  /**
 * Defines the signature of the desired results with regards to the first coulped orientation.
 * @param iOrientation
 * The orientation of the trihedron defined by the the spine, the normal to the first skin and
 * the tangent to the profile.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 */
  virtual void SetFirstCoupledOrientation(const int iOrientation) = 0;

  /**
 * Defines the signature of the desired results with regards to the second coulped orientation.
 * @param iOrientation
 * The orientation of the trihedron defined by the the spine, the normal to the second skin and
 * the tangent to the profile.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 */
  virtual void SetSecondCoupledOrientation(const int iOrientation) = 0;

  /**
 * Retrieves the signature relative to the current resulting body.
 * @param ioFirstShellOrientation
 * The signature with regards to the first skin orientation.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The results are in the semi-space defined by the normal to the skin.
 * <dt><tt>-1</tt></dt><dd> The results are in the semi-space defined by the opposite to the normal to the skin.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The results change of semi-space along the spine. 
 * </dl>
 * @param ioSecondShellOrientation
 * The signature with regards to the second skin orientation.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The results are in the semi-space defined by the normal to the skin.
 * <dt><tt>-1</tt></dt><dd> The results are in the semi-space defined by the opposite to the normal to the skin.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The results change of semi-space along the spine. 
 * </dl>
 * @param oCoupledFirstOrientation
 * The orientation of the trihedron defined by the the spine, the normal to the first skin and
 * the tangent to the profile.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 * @param oCoupledSecondOrientation
 * The orientation of the trihedron defined by the the spine, the normal to the second skin and
 * the tangent to the profile.
 *<br><b>Legal values</b>:
 * <dl>
 * <dt> <tt>1</tt></dt><dd> The output results are such that the triedron is counter clockwise.
 * <dt><tt>-1</tt></dt><dd> The output results are such that the triedron is clockwise.
 * <dt> <tt>0</tt></dt><dd> All the results must be output (<tt>1</tt>, <tt>-1</tt>, <tt>2</tt> cases all together).
 * <dt> <tt>2</tt></dt><dd> The orientation of the trihedron changes along the spine. 
 * </dl>
 * @param ioIndex
 * The rank (beginning at <tt>1</tt>) of the current body inside a given quadruple 
 * (<tt>ioFirstShellOrientation, ioSecondShellOrientation, oCoupledFirstOrientation, oCoupledSecondOrientation</tt>)
 */
  virtual void GetResultInformation(
    int &ioFirstShellOrientation,
    int &ioSecondShellOrientation,
    int &oCoupledFirstOrientation,
    int &oCoupledSecondOrientation,
    int &ioIndex) = 0;

  /**
 * Runs <tt>this</tt> operator.
 * <br>To retrieve the resulting bodies, use the iterator on the bodies provided by @href CATICGMTopMultiResult.
 */
  virtual int Run() = 0;

  /**
 * Defines the mode chosen for first skin
 * @param iMode
 * The segmentation mode (trim - no trim - trim on support)
 */
  virtual void SetFirstShellModeTrim(CATDynSegmentationMode iMode) = 0;

  /**
 * Defines the mode chosen for second skin
 * @param iMode
 * The segmentation mode (trim - no trim - trim on support)
 */
  virtual void SetSecondShellModeTrim(CATDynSegmentationMode iMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopSweepSkinSkinSegment(); // -> delete can't be called
};

/**
 * Creates a CATICGMTopSweepSkinSkinSegment operator.
 * @param iFactory
 * The pointer to the geometry factory that creates the result bodies.
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iFirstSupportShell
 * The pointer to the first skin body.
 * @param iSecondSupportShell
 * The pointer to the second skin body.
 * @param iSpine
 * The pointer to the spine body. Each segment section is in the plane normal to this spine curve.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 * operator.
 */
ExportedByCATGMOperatorsInterfaces CATICGMTopSweepSkinSkinSegment *CATCGMCreateTopSweepSkinSkinSegment(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iFirstSupportShell,
  CATBody *iSecondSupportShell,
  CATBody *iSpine);

#endif /* CATICGMTopSweepSkinSkinSegment_h_ */
