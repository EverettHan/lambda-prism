#ifndef CATICGMRemoveEdge_h_
#define CATICGMRemoveEdge_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"

class CATBody;
class CATEdge;
class CATTopData;
class CATLISTP(CATFace);
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMRemoveEdge;

/**
* Class defining a topological operator that extrapolates some edges of a skin in order to create an extra surface
* and fill in internal domains.
* The result is a 2D body in which some edges have been removed.
* The edges to be removed do not have necessarily to be all specified. For simple cases, the operator algorithm 
* is able to detect all the edges to be removed from one(or more) input edge(s). However,
* to make sure the operation completes, you must specify all the edges which are not continuous in tangency. 
* By default the operator detects the edges which are continuous in tangency and takes them into account for
* the extrapolation operation.<br>
* To use this operator, you must:
* <ul>
* <li>Create it with the CATCGMCreateRemoveEdge global function
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> or <tt>Append</tt> methods.
* <li>Run it
* <li>Get the result with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
* <li>Release the operator with the <tt>Release</tt> method after use.
* </ul> 
*
*/
class ExportedByCATGMOperatorsInterfaces CATICGMRemoveEdge: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMRemoveEdge();

  /**
  * Appends an edge to remove
  * @param iEdgeToRemove
  * The edge to remove.
  */
  virtual void Append(CATEdge *iEdgeToRemove) = 0;

  /**
  * Appends a list of Edges to remove
  * @param iEdgesToRemove
  * The list of pointers to Edges to remove.
  */
  virtual void Append(const CATLISTP(CATEdge) &iEdgesToRemove) = 0;

  /**
  * Mode de propagation en tangence : 1 = ON, 0 = OFF.
  */
  virtual void SetPropagationMode(short iPropagationMode) = 0;

  /**
  * Defines the state of the resulting body.
  * @param iOnOrOff
  * The state of the resulting body. 
  */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

  /**
  * Runs <tt>this</tt> operator.
  */
  virtual int Run() = 0;

  /**
  * Returns the pointer to the resulting body.
  * @return
  * The pointer to the resulting body, <tt>NULL</tt> if the operation failed. 
  * If you do not want to keep the resulting body, 
  * use the @href CATICGMContainer#Remove method to remove it from the 
  * geometric factory, after the operator deletion.
  */
  virtual CATBody *GetResult() = 0;

  /**
  * Returns the list of CATEdge that couldn't be removed.
  */
  virtual void GetAllTrickyEdges(CATLISTP(CATEdge) &oAllTrickyEdges) = 0;

#if defined (CATIACGMR215CAA)
  /**
  * Get the list of faces for which matter side has been reversed.
  * @param oReverseMatterOutputFaces
  * The list of reversed faces.
  */
  virtual void GetReverseMatterOutputFaces(
    CATLISTP(CATFace) &oReverseMatterOutputFaces) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMRemoveEdge(); // -> delete can't be called
};

/**
* Creates a CATICGMRemoveEdge operator.
* @param iFactory
* A pointer to the factory of geometric elements.
* @param iTopData
* A pointer to the topological data.
* @param iBody
* A pointer to the body.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATICGMRemoveEdge *CATCGMCreateRemoveEdge(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody);

#endif /* CATICGMRemoveEdge_h_ */
