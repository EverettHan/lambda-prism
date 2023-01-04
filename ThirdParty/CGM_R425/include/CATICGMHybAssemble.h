#ifndef CATICGMHybAssemble_h_
#define CATICGMHybAssemble_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATIACGMLevel.h"

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybOperatorImp.h"
#include "CATMathConstant.h"
#include "ListPOfCATCell.h"

class CATExtHybAssemble;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybAssemble;

/**
* Class defining the operator that assembles two bodies.
*<br>
* This operator operates on the 2D (CATShell), 1D (CATWire) and 0D (CATVertexInVolume)
* domains of a CATBody.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATICGMHybAssemble is created with the CATCGMCreateTopAssemble global function. 
* It must be released with the <tt>Release</tt> method after use.
* It is not streamable. 
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATCGMCreateTopAssemble
*/
class ExportedByCATGMOperatorsInterfaces CATICGMHybAssemble: public CATICGMHybOperatorImp
{
public:
 /**
  * Constructor
  */
  CATICGMHybAssemble();

  virtual int Run() = 0;

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
   * Activates Volume creation mode: if the resulting skin is closed,
   * operator creates and returns the volume bounded by this skin.
	 * @param iVolumeCreation
   * <br><b>Legal values</b>:
   * <dl><dt><tt>FALSE</tt><dd> No volume creation.
   *     <dt><tt>TRUE</tt><dd> Volume creation if result is closed.</dl>
   */
  virtual void SetVolumeCreationMode(CATBoolean iVolumeCreation = FALSE) = 0;

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

   
#ifdef CATIACGMR421CAA
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
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybAssemble(); // -> delete can't be called
};

#endif /* CATICGMHybAssemble_h_ */
