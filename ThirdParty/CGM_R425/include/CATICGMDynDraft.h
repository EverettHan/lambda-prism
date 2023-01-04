#ifndef CATICGMDynDraft_h_
#define CATICGMDynDraft_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynOperator.h"
#include "CATTopDefine.h"
#include "CATDynDraftDef.h"
#include "CATDynValidShell.h"

class CATBody;
class CATDynDraftDomain;
class CATGeoFactory;
class CATPlane;
class CATSurface;
class CATTopData;
class CATListPtrCATBody;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynDraft;

/**
 * Class defining the operator to draft faces of a 3D body.
 * <br>When working with castings and forgings, draft operations are needed to allow a part 
 * to be extracted from its mold. The parameters defining a drafting operation are:
 * <dl><dt>Pulling direction</dt><dd>The direction in which the mold of the part is extracted
 * <dt>Neutral element</dt><dd>The intersection between the neutral element and the faces to draft 
 * defines the neutral curve, where the body remains the same. 
 * On both sides of the neutral curve, matter is either added or subtracted, or both in some cases,
 * according to the pulling 
 * direction and the value of the angle. The neutral element does not need to split any of the selected faces.
 * However, the underlying surfaces have to intersect.
 * The neutral curve can also be directly defined by a reflect line computation, see @href CATDynDraftDomain.
 * <dt>Parting element</dt><dd>This optional element splits the faces in two sets. One must choose which
 * set of faces to draft
 * <ul><li> either  by defining an orientation value with respect to the parting element (called parting orientation)
 * <li> or, otherwise, by using the pulling direction.
 * </ul>
 * The parting element can be the same as the neutral element. 
 * There is at most one parting element associated with a CATICGMDynDraft operator.
 * <dt>Angle</dt><dd> The draft angle.
 * </dl> 
 *<br>A CATICGMDynDraft operator groups in a same operator several draft operations:
 * <ul><li>The CATDynDraftDomain groups all the faces to draft with regards to the same pulling direction,
 * <li>The CATDynDraftRibbon groups all the connected faces to draft with regards to the same pulling direction.
 * <li>The CATDynDraftAngle groups all the faces to draft with the same angle, 
 * defined with regards to the same pulling direction. At present, the operator does not support different
 * angle values.
 * </ul>
 * <br>By default, a ribbon is automatically propagated by following the tangential
 * continuity of its support.
 *<br>
 * The CATICGMDynDraft operator follows the global frame of the topological operators and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 *<ul>
 * <li>A CATICGMDynDraft operator is created with the <tt>CATCreateDynDraft</tt> global function:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>Options can be precised (such as the domain to draft) with the <tt>SetXxx</tt> and <tt>Add</tt> 
 * methods, before
 * asking for the computation with the <tt>Run</tt> method. The <tt>Add</tt> method can only be called once
 * for a draft operation.
 *<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 * @see CATDynDraftDomain, CATDynDraftRibbon, CATDynDraftAngle
 */
class ExportedByCATGMOperatorsInterfaces CATICGMDynDraft: public CATICGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynDraft();

  /**
 * Defines the parting element associated with <tt>this</tt> drafting operator.
 * @param iPartingElement
 * The pointer to the parting body. 
 * @param iPartingOrientation
 * The side of the parting element where the faces are drafted.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATOrientationUnknown</tt></dt><dd>The pulling direction defines the side.
 * <dt><tt>CATOrientationNegative</tt></dt>
 * <dd>The opposite of the natural orientation of the parting element.
 * <dt><tt>CATOrientationPositive</tt></dt>
 * <dd>The natural orientation of the parting element.
 * </dl>
 * @param iIsPartingUntil
 * In case of a parting element that does not intersect the faces to draft, <tt>iIsPartingUntil</tt> defines 
 * whether the parting element is used or not. By default, it is not. To be used in case of reflect line draft only.
 */
  virtual void Add(
    CATBody *iPartingElement,
    CATOrientation iPartingOrientation = CATOrientationUnknown,
    CATBoolean iIsPartingUntil = FALSE) = 0;

#ifdef CATIACGMV5R23
  /**
 * Specifies a body that defines the boundary for a draft operation.
 * @param iLimitingElement
 * The body to use as the limiting element.
 * @param iLimitingOrientation
 * The side of the limiting element on which the faces are drafted.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>CATOrientationUnknown</tt></dt><dd>The pulling direction defines the side.
 * <dt><tt>CATOrientationNegative</tt></dt>
 * <dd>The opposite of the natural orientation of the limiting element.
 * <dt><tt>CATOrientationPositive</tt></dt>
 * <dd>The natural orientation of the limiting element.
 * </dl>
 * @param iIsLimitingUntil
 * In case of a limiting element that does not intersect the faces to draft, <tt>iIsLimitingUntil</tt> defines 
 * whether the limiting element is used or not. By default, it is not.
 */
  virtual void AddLimiting(
    CATBody *iLimitingElement,
    CATOrientation iLimitingOrientation = CATOrientationUnknown,
    CATBoolean iIsLimitingUntil = FALSE) = 0;
#endif

  /**
 * Adds a domain to draft.
 * <br> The <tt>Add</tt> method can only be called once
 * for a draft operation.
 * @param iDraftDomain
 * The pointer to the domain to add to the drafting operation.
 */
  virtual void Add(CATDynDraftDomain *iDraftDomain) = 0;

  /**
 * Asks for the computation of the construction paths of the draft.
 * <br>To obtain the initial wire representing 
 * either the intersection of the neutral element with the initial body or the reflect lines. 
 * <br>Can be use in debug purpose, in order to understand the configuration.
 */
  virtual void SetPrevisualizationOnly() = 0;

#ifdef CATIACGMV5R23
  /**
 * Asks for the computation of the construction paths of the draft.
 * <br>Can be use in debug purpose, in order to understand the configuration.
 */
  virtual void SetPrevisualizationMode(CATDynDraftPrevisualization iMode) = 0;
#endif

  /**
 * Defines whether a draft ribbon can be branched into two ribbons.
 * <br>This may happen when the set of faces to draft is itself bifurcating.
 * @param iJunctionMode
 * The branch mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it can, <tt>FALSE</tt> otherwise.
 */
  virtual void SetJunctionMode(CATBoolean iJunctionMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynDraft(); // -> delete can't be called
};

/**
 * Creates a CATICGMDynDraft operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iPart
 * The pointer to the body to draft.
 * @param iType
 * The type of the draft operation.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynDraft *CATCGMCreateDynDraft(
  CATGeoFactory *iContainer,
  CATTopData *iData,
  CATBody *iPart,
  const CATDynDraftType iType);

#endif /* CATICGMDynDraft_h_ */
