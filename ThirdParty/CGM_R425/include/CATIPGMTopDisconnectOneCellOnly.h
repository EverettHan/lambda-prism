#ifndef CATIPGMTopDisconnectOneCellOnly_h_
#define CATIPGMTopDisconnectOneCellOnly_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATDynOperatorDef.h"
#include "CATDOCODef.h" // Only for old callers of this, in case they used the DOCO enums.

class CATBody;
class CATCGMOutput;
class CATCGMStream;
class CATCell;
class CATExtCGMReplay;
class CATExtTopOperator;
class CATGeoFactory;
class CATString;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopDisconnectOneCellOnly;

/**
 * Class defining the operator which disconnects one cell only, of the input body,  by the given operand.
 * If the operand doesn't intersect the cell to disconnect, the returned result is the input body.
 * <br>
 * The <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: the input bodies are not modified. The resulting body is equal to 
 * the first input body, or is a new created body, possibly sharing data with the input bodies.
 * <ul>
 * <li>A <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator is created with the <tt>CATCreateDisconnectOneCellOnly</tt>
 * global function: It must be directly deleted after use with the usual C++ <tt>delete</tt> operator. 
 * It is not streamable. 
 * <li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometry factory. 
 * </ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMTopDisconnectOneCellOnly: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopDisconnectOneCellOnly();

  //Setters
  virtual void SetExtrapolationMode(CATDynExtrapolationMode iExtrapolMode) = 0;

  virtual void SetExtrapolationLimit(CATDynExtrapolationLimit iLimit) = 0;

  virtual void UseSmartProjection(CATBoolean iUseSmartProjection) = 0;

  virtual void SetImprintFollowUpMode(CATBoolean iImprintFollowUpMode) = 0;

  //Getters
  virtual CATBoolean IsSmartProjectionUsed() = 0;

  virtual CATBoolean GetImprintFollowUpMode() const = 0;

  /**
  * Activates (before Run) the option associating information of filiation to each result cell
  * whose the dimension is conform to the disconnection type (volumic or surfacic)
  * In case of a volumic disconnection, this option allows to retrieve the filiation of volumes (not candidate for reporting in the Journal)
  * In all cases, this option allows also to locate a result sub-cell of a subdivided cell in the different half-spaces defined by the oriented disconnecting bodies
  *  @return
  * returns TRUE only if this option is available, else returns FALSE
  */
  virtual CATBoolean EnableResultCellsFiliationInfoRequest() = 0;

  /**
   * Retrieves the original data as parents of a given result cell, after disconnection
   * The dimension of the result cell has to be conform to the way the disconnection has been defined (volumic or surfacic)
   *  @param iResultCell
   *    a CATCell respecting the disconnection dimension and belonging to the result CATBody
   *    Only one type is expected here according to the operation definition:
   *         CATVolumeType if the operation consists in partitioning the matter of a volumic body
   *         CATFaceType if the operation consists in partitioning a surfacic body or the outer/inner shell of a volumic body
   *
   *  @param oOriginalCell
   *    The pointer to the single parent CATCell belonging to the input body to disconnect
   *    with the same dimension than iResultCell (CATVolume or CATFace)
   *    3 different types of filiation here:
   *         1. The original CATCell is untouched by the operation, then reused in the result body: iResultCell = oOriginalCell
   *         2. The original CATCell is touched on its boundary, as neighbor of another CATCell to disconnect
   *         3. The original CATCell is subdivided into several result CATCell
   * 
   *            In this last case, the result cell comes also from at least one disconnecting bodies (see the next argument comment)
   *
   *  @param oDisconnectingBodies
   *    The list of input disconnecting bodies subdividing the current original cell (third case of the previous argument comment)
   *    this list is empty in case of untouched cell, or simple modification of cell without any subdivision.
   *
   *  @param oDisconnectingOrientations
   *    list parallel to oDisconnectingBodies,
   *    associating a relative orientation to each disconnecting body crossing and subdividing the current original cell,
   *    in order to identify the half-space containing the current sub-cell from the current oriented disconnecting body
   *
   *  @return
   *    returns TRUE if the filiation information has been correctly retrieved and returned
   *    returns FALSE:
   *      if this method is called before the Run()
   *      if the "ResultCellsFiliationInfoRequest" has not been enabled before the Run() or had returned FALSE (not available)
   *      if the result cell is not belonging to the result CATBody
   *      if the result cell has not the expected dimension
   *      if no original CATCell has been retrieved as single parent of iResultCell
   */
  virtual CATBoolean GetFiliationInfoFromResultCell(CATCell* iResultCell, CATCell*& oOriginalCell, CATLISTP(CATBody)& oDisconnectingBodies, CATListOfInt& oDisconnectingOrientations) = 0;


protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopDisconnectOneCellOnly(); // -> delete can't be called
};

/**
 * Creates a <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator.
 * @param ipFactory
 * The factory of the geometry. 
 * @param ipTopData
 * The pointer to the data defining the software configuration and the journal. 
 * If the journal inside <tt>ipTopData</tt> is <tt>NULL</tt>, it is not filled.
 * @param ipBodyToDisconnect
 * The pointer to the input body to disconnect, containing the following cell.
 * @param ipCellToDisconnect
 * The pointer to the cell (Volume, Face, etc.) to disconnect, contained in the previous body.
 * @param ipDisconnectingBody
 * The pointer to the operand body which will be used to disconnect the previous cell.
 * @return
 * The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToDisconnect,
  CATCell *ipCellToDisconnect,
  CATBody *ipDisconnectingBody);

/**
 * Creates a <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator.
 *  @param ipFactory
 *    The factory of the geometry. 
 *  @param ipTopData
 *    The pointer to the data defining the software configuration and the journal. 
 *    If the journal inside <tt>ipTopData</tt> is <tt>NULL</tt>, it is not filled.
 *  @param ipBodyToDisconnect
 *    The pointer to the input body to disconnect, containing the following cells.
 *  @param ipCellToDisconnect
 *    The pointer to the cell (Volumes, Faces, etc.) to disconnect, contained in the previous body.
 *  @param iDisconnectingBodies
 *   The pointers to the operand bodies which will be used to disconnect the previous cell.
 *  @return
 *    The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToDisconnect,
  CATCell *ipCellToDisconnect,
  const CATLISTP(CATBody) &iDisconnectingBodies);

/**
 * Creates a <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator.
 *  @param ipFactory
 *    The factory of the geometry. 
 *  @param ipTopData
 *    The pointer to the data defining the software configuration and the journal. 
 *    If the journal inside <tt>ipTopData</tt> is <tt>NULL</tt>, it is not filled.
 *  @param ipBodyToDisconnect
 *    The pointer to the input body to disconnect, containing the following cells.
 *  @param iCellsToDisconnect
 *    The pointer to the cells (Volumes, Faces, etc.) to disconnect, contained in the previous body.
 *    All the cells should have the same dimension !!
 *  @param iDisconnectingBodies
 *   The pointers to the operand bodies which will be used to disconnect the previous cell.
 *  @return
 *    The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToDisconnect,
  const CATLISTP(CATCell) &iCellsToDisconnect,
  const CATLISTP(CATBody) &iDisconnectingBodies);

/**
 * Creates a <tt>CATIPGMTopDisconnectOneCellOnly</tt> operator.
 *  @param ipFactory
 *    The factory of the geometry. 
 *  @param ipTopData
 *    The pointer to the data defining the software configuration and the journal. 
 *    If the journal inside <tt>ipTopData</tt> is <tt>NULL</tt>, it is not filled.
 *  @param ipBodyToDisconnect
 *    The pointer to the input body to disconnect.   For this create function,
 *    we will disconnect all cells directly owned by this body provided that they have the same dimension.
 *  @param iDisconnectingBodies
 *   The pointers to the operand bodies which will be used to disconnect the previous cell.
 *  @return
 *    The pointer to the created operator. To delete after use with the usual C++ <tt>delete</tt> operator.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMTopDisconnectOneCellOnly *CATPGMCreateDisconnectOneCellOnly(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATBody *ipBodyToDisconnect,
  const CATLISTP(CATBody) &iDisconnectingBodies);

#endif /* CATIPGMTopDisconnectOneCellOnly_h_ */
