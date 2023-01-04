#ifndef CATICGMFuzzyExtrapol_h_
#define CATICGMFuzzyExtrapol_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

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

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMFuzzyExtrapol;

/**
* Class representing an operator that extrapolates a shell body with respect to surface curvature.
* Some border and internal details may be skipped for robustness purpose.
*<br>The edges to be extrapolated must belong to the boundary of the shell.
*<br>The extrapolation values can be different for each edge. A positive
* value defines an extrapolation along the outside direction of the shell.
*<br>Target bodies can be defined instead of distances.
*<br>The extrapolation gives a result that is continuous in curvature.
* To use it:
* <ul>
* <li>Create it with the <tt>CATCreateFuzzyExtrapolOpe</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
* <li>Run it
* <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*<li>Delete it after use  with the usual C++ <tt>delete</tt> operator.
*</ul> 
*/

class ExportedByCATGMOperatorsInterfaces CATICGMFuzzyExtrapol: public CATICGMTopOperator
{
public:
  /**
  * Constructor
  */
  CATICGMFuzzyExtrapol();

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
  virtual void Append( const CATLISTP(CATEdge) & iBoundaryEdges, CATLength iExtrapolValue ) = 0;

  /**
  * Appends an edge to extrapolate.
  * It replaces the current value of an already selected edges by <tt>iExtrapolValue</tt>.
  * @param iBoundaryEdge
  * The edge to append.
  * @param iExtrapolValue
  * The extrapolation value for the <tt>iBoundaryEdge</tt> edge.
  */
  virtual void Append( CATEdge * iBoundaryEdge, CATLength iExtrapolValue ) = 0;

  /**
  * Appends a wire to extrapolate.
  * It appends a wire to extrapolate of <tt>iExtrapolValue</tt>.
  * @param iWire
  * The wire body to extrapolate
  * @param iExtrapolValue
  * The extrapolation value for the <tt>iWire</tt> wire.
  */
  virtual void Append( CATBody * iWire, CATLength iExtrapolValue) = 0;

  /**
  * Selects all the edges of the shell boundary and sets to them a common extrapolation value.
  * @param iExtrapolValue
  * The new current extrapolation value for all the edges of the shell boundary.
  * Only for input given as edges
  */
  virtual void SetDefaultExtrapolationValue( CATLength iExtrapolValue ) = 0;

  /**
  * Defines the propagation mode of the extrapolation value.
  * @param iPropagationMode
  * <dl>
  * <dt><tt>0</tt></dt><dd> No propagation of the extrapolation value.
  * <dt><tt>1</tt></dt><dd> Defines the automatic definition of the extrapolation value on an edge
  * to the one of its tangential adjacent edges.
  * This mode is used by default at the creation of the operator.
  * </dl>
  * Only for input given as edges
  */
  virtual void SetPropagationMode( short iPropagationMode ) = 0;

  /**
  * Defines whether the result should contain the whole extrapolated surface or only the extrapolated area.
  * @param iKeepOnlyExtrapolatedArea
  *<dl>
  *<dt><tt>0</tt></dt><dd> The whole extrapolated surface is returned.
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> The result contains the extrapolated area only.
  *</dl>
  */
  virtual void SetKeepOnlyExtrapolatedArea( short iKeepOnlyExtrapolatedArea ) = 0;

  /**
  * Defines whether holes should be removed from the skin or not
  * @param iRemoveHoles
  *<dl>
  *<dt><tt>0</tt></dt><dd> No special treatment for holes
  * This mode is used by default at the creation of the operator.
  *<dt><tt>1</tt></dt><dd> All detected holes are removed from the skin.
  *<dt><tt>2</tt></dt><dd> Remove holes whose boundaries include specified edges to extrapolate.
  *<dt><tt>3</tt></dt><dd> Leave intact holes whose boundaries are made of edges to extrapolate.
  * The other holes remain intact too.
  *</dl>
  * Only for C2 continuity
  */
  virtual void SetRemoveHoles( short iRemoveHoles ) = 0;

  /**
  * Defines the extrapolation behaviour around the extremities of the selected boundaries
  * @param iExtremitiesMode
  * <dl>
  * <dt><tt>0</tt></dt><dd> The extrapolation sides are tangent to the edges adjacent to the surface boundary
  *  This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> The extrapolation sides are normal to the original surface boundary.
  * </dl>
  */
  virtual void SetExtremitiesMode( short iExtremitiesMode ) = 0; 

  /**
  * Defines the level of approximation allowed for the reconstruction of the surfaces boundaries.
  * The more this level is high, the more boundaries can be approximated and the more robust is the operation.
  * @param iApproximateExtrapolationLevel
  * <dl>
  * <dt><tt>0</tt></dt><dd> The shape of extrapolated boundaries is preserved. Extrapolation distance is respected.
  *  This mode is used by default at the creation of the operator.
  * <dt><tt>1</tt></dt><dd> Some edges from the boundary may be merged and extrapolation distance may not be respected.
  * </dl>
  * Only for C2 continuity
  */
  virtual void SetApproximateExtrapolationLevel(short iApproximateExtrapolationLevel) = 0;

  /**
  * Defines the type of continuity for the extrapolation
  * @param iExtremitiesMode
  * <dl>
  * <dt><tt>1</tt></dt><dd> Tangent mode : G1 continuity
  * <dt><tt>2</tt></dt><dd> Curvature mode : C2 continuity. 
  * This mode is used by default at the creation of the operator.
  * </dl>
  */
  virtual void SetContinuityMode( short iContinuityMode ) = 0;

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
  virtual ~CATICGMFuzzyExtrapol(); // -> delete can't be called
};

/**
* Creates a Fuzzy extrapolation operator.
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
ExportedByCATGMOperatorsInterfaces CATICGMFuzzyExtrapol *CATCGMCreateFuzzyExtrapol(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iSkin);

#endif /* CATICGMFuzzyExtrapol_h_ */

