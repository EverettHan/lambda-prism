#ifndef CATICGMSkinExtrapol_h_
#define CATICGMSkinExtrapol_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"
#include "CATIACGMLevel.h"

class CATBody;
class CATCGMJournalList;
class CATCurve;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATEdge;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMSkinExtrapol;

/**
 * Class representing an operator that extrapolates a shell body.
 *<br>The edges to extrapolate must be on the boundary of the shell, or 
 * must lie on a bounding edge of the shell.
 *<br>The extrapolation values can be different for each edge. A positive
 * value defines an extrapolation along the outside direction of the shell.
 *<br>The extrapolation gives a result that is continuous in curvature.
 * To use it:
 * <ul>
 * <li>Create it with the <tt>CATCGMCreateSkinExtrapol</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMSkinExtrapol: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMSkinExtrapol();

  /**
 * Sets the ability to later modify the resulting body.
 * @param iFreezeMode
 * The freeze mode.
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iFreezeMode) = 0;

  /**
 * Appends a list of edges to extrapolate.
 * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
 * @param iBoundaryEdges
 * The list of edges to append.
 * @param iExtrapolValue
 * The common extrapolation value for all the edges of the <tt>iBoundaryEdges</tt> list.
 */
  virtual void Append(const CATLISTP(CATEdge) &iBoundaryEdges, CATLength iExtrapolValue) = 0;

  /**
 * Appends an edge to extrapolate.
 * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
 * @param iBoundaryEdge
 * The edge to append.
 * @param iExtrapolValue
 * The extrapolation value for the <tt>iBoundaryEdge</tt> edge.
 */
  virtual void Append(CATEdge *iBoundaryEdge, CATLength iExtrapolValue) = 0;

  /**
 * Selects all the edges of the shell boundary and sets to them a common extrapolation value.
 * @param iExtrapolValue
 * The new current extrapolation value of the already selected edges.
 */
  virtual void SetDefaultExtrapolationValue(CATLength iExtrapolValue) = 0;

  /**
 * Defines the propagation mode of the extrapolation value.
 * @param iPropagationMode
 *<dl>
 *<dt><tt>0</tt></dt><dd> No propagation of the extrapolation value.
 *<dt><tt>1</tt></dt><dd> Defines the automatic definition of the extrapolation value on an edge
 * to the one of its tangential adjacent edges.
 * This mode is used by default at the creation of the operator.
 *</dl>
 */
  virtual void SetPropagationMode(int iPropagationMode) = 0;

#ifdef CATIACGMR214CAA
  /**
 * Defines the relimitation mode for all boundary extremities affected by the operator.
 * @param iNormalMode
 *<dl>
 *<dt><tt>0</tt></dt><dd> Extrapolate adjacent edges to cut the offset boundary.
 * This mode is enabled by default at the creation of the operator.
 *<dt><tt>1</tt></dt><dd> Add junction edges in the normal direction of boundary extremities.
 *</dl>
 */
  virtual void SetExtremitiesMode(int iNormalMode) = 0;
#endif

  /**
 * Returns the pointer to the resulting body.
 */
  virtual CATBody *GetResult() = 0;

  /**
 * Returns a pointer to the topological journal dedicated to <tt>this</tt> CATICGMSkinExtrapol operator.
 * <br>Only available if a journal was given at the creation of the operator.
 */
  virtual CATCGMJournalList *GetJournal() = 0;

  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMSkinExtrapol(); // -> delete can't be called
};

/**
 * Creates a skin extrapolation operator.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iSkin
 * The pointer to the skin body to extrapolate.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMSkinExtrapol *CATCGMCreateSkinExtrapol(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iSkin);

#endif /* CATICGMSkinExtrapol_h_ */
