#ifndef CATIPGMHybAssemble_h_
#define CATIPGMHybAssemble_h_

// COPYRIGHT DASSAULT SYSTEMES 2020

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"

class CATExtHybAssemble;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybAssemble;

/**
* Class defining the operator that assembles two bodies.
*<br>
* This operator operates on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATIPGMHybAssemble is created with the CATPGMCreateTopAssemble global function. 
* It must be released with the <tt>Release</tt> method after use
* It is not streamable.
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopAssemble
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybAssemble: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybAssemble();

  /** 
   * @nodoc
   * No longer available.
   */
  virtual void SetBorderMode(int yes_or_no = 1) = 0;

  /**
   * @nodoc
   * No longer available.
   */
  virtual int GetBorderMode() const = 0;

  /** 
   * @nodoc
   * No longer available.
   */
  virtual void SetFirstPassMode(int yes_or_no = 1) = 0;

  /**
   * @nodoc
   * No longer available.
   */
  virtual int GetFirstPassMode() const = 0;

  /**
   * Activates simplify mode: operator tries to simplify result.
   * <br> This option is not activated by default.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No simplification of result.
   *     <dt><tt>1</tt><dd> Simplification of result.</dl>
   */
  virtual void SetSimplifyMode(int yes_or_no = 1) = 0;

  /**
   * Returns simplify mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No simplification of result.
   *     <dt><tt>1</tt><dd> Simplification of result.</dl>
   */
  virtual int GetSimplifyMode() const = 0;

  /**
   * Activates suppress mode : in the case of invalid cells, 
   * operator does a second pass after having removed them.
   * Invalid cells may be retrieved with method GetSupressBody.
   * <br> This option is not activated by default.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No assemble with invalid cells.
   *     <dt><tt>1</tt><dd> Force assemble with invalid cells.</dl>
   */
  virtual void SetSuppressMode(int yes_or_no = 1) = 0;

  /**
   * Returns the suppress mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> suppress mode not active.
   *     <dt><tt>1</tt><dd> suppress mode is active.</dl>
   */
  virtual int GetSuppressMode() const = 0;

  /**
   * Retrieves the suppressed cells in a body.
   * @return
   * The suppressed body: the body contains all suppressed cells.
   */
  virtual CATBody *GetSuppressBody() = 0;

  /** 
   * @nodoc
   * Activates angle mode: operator checks that angle value is lower than a maximum value.
   * <br> This option is not activated by default and only concerns assemble of wires.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> angle mode not active.
   *     <dt><tt>1</tt><dd> angle mode is active.</dl>
   */
  virtual void SetAngleMode(int yes_or_no = 1) = 0;

  /** 
   * @nodoc
   * Returns the angle mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> angle mode not active.
   *     <dt><tt>1</tt><dd> angle mode is active.</dl>
   */
  virtual int GetAngleMode() const = 0;

  /** 
   * @nodoc
   * Sets the maximum value of angle for angle mode.
   * <br> The value by default is 180°.
   * @param iMaxAngle
   * Maximum value of angle.
   */
  virtual void SetAngleValue(CATAngle iMaxAngle) = 0;

  /** 
   * @nodoc
   * Returns maximum value of angle.
   * @return 
   * Maximum value of angle.
   */
  virtual CATAngle GetAngleValue() const = 0;

  /** 
   * @nodoc
   * No longer available
   */
  virtual void SetAllAngleErrorInOneShot(int yes_or_no = 1) = 0;

  /** 
   * @nodoc
   * No longer available
   */
  virtual int GetAllAngleErrorInOneShotMode() const = 0;

  /** 
   * @nodoc
   * No longer available
   */
  virtual void SetQuickMode(int yes_or_no = 1) = 0;

  /** 
   * Retrieves merged cells in a body (to use after run).
   * @return
   * The body containing all merged edges.
   */
  virtual CATBody *GetAllMergedEdges() = 0;

  /**
  * Specifies a list of cells to be merged in a local join.
  * @param iCellsToMerge
  * The cells to be merged.
  */
  virtual void SetCellsToMerge(const CATLISTP(CATCell) &iListOfCells) = 0;

  /**
   * Specifies border cells of different skins to assemble to match up,
   * in order to avoid unnecessary calculations.
   * @param iMatchingCells
   * The border cells of the skins that are matching together.
   */
  virtual void SetMatchingCells(const CATLISTP(CATCell) &iMatchingCells) = 0;

  /**
   * @nodoc
   * Specifies border cells of different skins to assemble to match up,
   * in order to avoid unnecessary calculations.
   * @param iMatchingCells
   * The border cells of the skins that are matching together.
   */
  virtual void SetMatchingCells(CATLISTP(CATCell) *iMatchingCells) = 0;
  
  /**
   * Activates Volume creation mode: if the resulting skin is closed,
   * operator creates and returns the volume bounded by this skin.
	 * @param iVolumeCreation
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> No volume creation.
   *     <dt><tt>TRUE</tt><dd> Volume creation if result is closed.</dl>
   */
  virtual void SetVolumeCreationMode(CATBoolean iVolumeCreation = FALSE) = 0;

  /**
   * @nodoc
   * Asks operator not to remove small edges.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> Small edges are removed.
   *     <dt><tt>1</tt><dd> Small edges are not removed.</dl>
   */
  virtual void SetKeepSmallEdges(int yes_or_no = 1) = 0;

  /** 
   * @nodoc
   * Returns small edges mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> mode not active: small edges are removed.
   *     <dt><tt>1</tt><dd> mode is active: small edges are not removed.</dl>
   */
  virtual int GetKeepSmallEdgesMode() const = 0;

  /** @nodoc  
   * Internal use.
   */
  virtual CATExtHybAssemble *GetHybAssembleExtensible() const = 0;

  /**
   * Activates SeparateBodies mode : in the case of more than one resulting domain,
   * each domain is returned in a different body.
   * Resulting bodies may be retrieved calling <tt>NextResult</tt> before each call to GetResult.
   * <br> This option is not activated by default.
   * @param iSeparateBodiesMode
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> All domains will be in the same body.
   *     <dt><tt>TRUE</tt><dd> One body for each domain.</dl>
   */
  virtual void SetReturnSeparateBodies(CATBoolean iSeparateBodiesMode) = 0;

  /** @nodoc
   * Decide if 2 edges belonging to the same input CATShell can be stitched together or not.
   * This option shouldn't be used in the case of wire assembly.
   * @param iMergeEdgesFromSameShell
   * <br><b>Legal values</b>:
   * <tt>1</tt> to allow 2 edges from the same shell to be stitched together, 
   * <tt>0</tt> to forbid 2 edges from the same shell to be stitched together.
   */
  virtual void SetMergeEdgesFromSameShell(short iMergeEdgesFromSameShell) = 0;

  /** @nodoc
   * Use this function to decide which CATCurve must be used when trying to stitch an edge with the other edges.
   * By default, the operator uses the CATPCurve that represents the edge on its face.
   * By calling SetUseEdgeCurveForMerge(1) before run, the CATEdgeCurve of the edge will be used instead.
   * This can have an effect on the final result,
   * especially in cases where the geometric gap of the CATEdgeCurve is big.
   */
  virtual void SetUseEdgeCurveForMerge(short iUseEdgeCurveForMerge) = 0;

  /**
   * Option to split edges according to the convexity.  
   * <br> This option is activated by default.  Deactivating it improves performance.
   * @param iConvexitySplitter
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> Edges will not be split according to the convexity.  This should improve performance.
   *     <dt><tt>TRUE</tt><dd>  Edges will be split according to the convexity.</dl>
   */
  virtual void SetConvexitySplitter(CATBoolean iConvexitySplitter) = 0;

  /**
   * Option to populate output journals.
   * <br> This option is activated by default.  Deactivating it improves performance.
   * @param iJournalsRequired
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> We will not populate the output journals.  This should improve performance.
   *     <dt><tt>TRUE</tt><dd>  We populate the output journals.</dl>
   */
  virtual void SetJournalsRequired(CATBoolean iJournalsRequired) = 0;

  /*
   * Option to record the merged edges.
   * <br> This option is activated by default.  Deactivating it improves performance.   
   * @param iAllMergedEdgesRequired
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> We will not record the merged edges.  This should improve performance.
   *     <dt><tt>TRUE</tt><dd>  We record edges that have been merged.</dl>
   */
  virtual void SetAllMergedEdgesRequired(CATBoolean iAllMergedEdgesRequired) = 0;

  /** @nodoc
   // set treatment with Simplification of the Result (to use before run)
   // default value is : 0  --> No Simplification of the Result
   // other value : 1 --> simplification only between 2 modified faces of 2 different bodies.
   // other value : 2 --> simplification between faces of 2 different bodies including merged faces with common edge on the 2 bodies
   */
  virtual void SetSimplifyModeForNoChange(int yes_or_no = 2) = 0;

  /** @nodoc
   // get if Simplification of the Result has been activated
   // default value is : 0  --> No Simplification of the Result
   // other value : 1 --> simplification only between 2 modified faces of 2 different bodies.
   // other value : 2 --> simplification between faces of 2 different bodies including merged faces with common edge on the 2 bodies
   */
  virtual int GetSimplifyModeForNoChange() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybAssemble(); // -> delete can't be called
};

#endif /* CATIPGMHybAssemble_h_ */
