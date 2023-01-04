#ifndef CATIPGMRemoveEdgePlusOpe_h_
#define CATIPGMRemoveEdgePlusOpe_h_

// COPYRIGHT DASSAULT SYSTEMES 2016

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATEdge;
class CATRemoveEdgePlusImpl;
class CATLISTP(CATEdge);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMRemoveEdgePlusOpe;

/**
 * Class defining the topological operator that removes given Edges on a body.
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMRemoveEdgePlusOpe: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMRemoveEdgePlusOpe();

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
   * Propagate edge list according to tangency : 1 = ON, 0 = OFF.
   */
  virtual void SetPropagationMode(short iPropagationMode) = 0;

  /**
   * If ON, RemoveEge Operator keeps the trace of the border edges that have been removed
   * @param iKeepBorderEdges
   * 1 - ON 
   * 0 - OFF
   */
  virtual void SetKeepBorderEdges(short iKeepBorderEdges) = 0;

  /**
   * @nodoc
   * If ON, RemoveEdge Operator tries to independently remove connected subsets of edges
   * when RemoveEdge call on all the edges fails
   * @param iPartialRemoveEdgeAllowed
   * 0 - Partial result is disabled
   * 1 - The operator returns a best result on which a maximum number of edges has been removed.
   *     Consistency between the result and the list of tricky edges is guaranteed :
   *     The same operation without the tricky edges would return the exact same result.
   * 2 - Same as 1, but without the consistency check (performances)
   */
  virtual void SetPartialRemoveEdgeAllowed(short iPartialRemoveEdgeAllowed) = 0;

  /**
   * Returns the list of CATEdge that couldn't be removed.
   */
  virtual void GetAllTrickyEdges(CATLISTP(CATEdge) &oAllTrickyEdges) = 0;

  /**
   * Run the operator
   */
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMRemoveEdgePlusOpe(); // -> delete can't be called
};

// -----------------------
// CATCreateRemoveEdgePlus
// -----------------------
ExportedByCATGMOperatorsInterfaces CATIPGMRemoveEdgePlusOpe *CATPGMCreateRemoveEdgePlusOpe(
  CATGeoFactory &iFactory,
  CATTopData &iTopData,
  CATBody &iReferenceBody);

// -----------------------
// CATCreateRemoveEdgePlus
// -----------------------
ExportedByCATGMOperatorsInterfaces CATIPGMRemoveEdgePlusOpe *CATPGMCreateRemoveEdgePlusOpe(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iReferenceBody);

#endif /* CATIPGMRemoveEdgePlusOpe_h_ */
