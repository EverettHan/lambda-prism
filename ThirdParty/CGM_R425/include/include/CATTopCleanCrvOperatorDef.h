#ifndef CATTopCleanCrvOperatorDef_h_
#define CATTopCleanCrvOperatorDef_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

 /** 
 * Defines the control mode of the CATTopCleanCrvOperator.
 * @param CatTopCleanCrvDeformation
 * The process is run with an additional constraint of maximum deformation around the input wire. 
 *    In this case, it can happen that some required continuity constraints are not reached, producing
 * an error in the <tt>Run</tt> method.
 * @param CatTopCleanCrvContinuity
 * The priority is given to continuity order achievement, regardless of the geometric deformation.
 *    Some important deformation between the input body and the result may appear.
 */
enum CatTopCleanCrvPriorityMode
{ 
  CatTopCleanCrvDeformation,
  CatTopCleanCrvContinuity
};

 /** 
 * Defines the status of edges and vertices of the input wire.
 * These status may be obtained using respectively @href CATTopCleanCrvOperator#GetDescendantEdge 
 * and @href CATTopCleanCrvOperator#GetDescendantVertex methods.
 * @param CatTopCleanCrvCellDeleted
 * The input cell has no corresponding cell is the result wire.
 * @param CatTopCleanCrvCellMapped
 * The input cell has one and only one corresponding cell, of the same type, in the result wire.
 * @param CatTopCleanCrvCellMerged
 * The input cell has been merged with at least one other input cell, of the same type, 
 * into a cell, of the same type, of the output wire.
 */
enum CatTopCleanCrvCellStatus
{ 
  CatTopCleanCrvCellDeleted,
  CatTopCleanCrvCellMapped,
  CatTopCleanCrvCellMerged
};
 

/**
  * Defines the way to treat non-C2 edges.
  * @param CATTopCleanCrvNoC1ToC2Management
  * No special treatment is applied.
  * @param CATTopCleanCrvDefaultC1ToC2Management
  * Edges that need a modification 
  * and that are not C2 continuous are C2 continous in the result.
  * @param CATTopCleanCrvAllCurvesC1ToC2Management
  * All non-C2-continuous Edges are C2 continous in the result. 
  */
typedef enum 
{ 
  CATTopCleanCrvNoC1ToC2Management,
  CATTopCleanCrvDefaultC1ToC2Management,
  CATTopCleanCrvAllCurvesC1ToC2Management
} CATTopCleanCrvC1ToC2Management;

#endif /* CATTopCleanCrvOperatorDef_h_ */
