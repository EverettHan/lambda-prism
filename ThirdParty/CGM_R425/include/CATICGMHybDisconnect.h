#ifndef CATICGMHybDisconnect_h_
#define CATICGMHybDisconnect_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMHybBoolean.h"

class CATExtHybDisconnect;
class CATCell;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMHybDisconnect;

/**
 * Class defining the operator that inserts vertices in a wire or skin body, or
 * inserts edges in a skin body.
 * <br>
 * The disconnect operation completes if the cutting body is laid down
 * on the body to be disconnected. The cutting body must have been created 
 * as lying on its support (as a point on curve or surface for example), 
 * otherwise it must be projected onto the body to be disconnected. 
 * The operator generates an exception if this condition is not fulfilled. 
 * When the cutting body is a 0D body immersed within a face but not laid down onto an edge, 
 * the body resulting from the Disconnect operation is the initial one, no vertex-in-face is created. 
 * When the cutting body is a 0D body laid down onto an edge, 
 * the resulting body does not contain any extra faces but vertices and edges are added. 
 * <br>
 * This operator follows the general frame of all operators and satisfies the smart mechanism: the
 * input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 * <ul>
 * <li>CATICGMHybDisconnect is created with the <tt>CATCGMCreateTopDisconnect</tt>,
 * <tt>CATCGMCreateTopDisconnectShell</tt> or <tt>CATCGMCreateTopDisconnectWire</tt> global functions.
 * It must be
 * directly released with the <tt>Release</tt> method after use.
 * It is not streamable. 
 * <li>The intersection can be restricted to a given domain on each body with the methods
 * <tt>SetFirstDomainToIntersect</tt> and <tt>SetSecondDomainToIntersect</tt>
 *<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul>
 * @see CATCGMCreateTopDisconnect
 * @see CATCGMCreateTopDisconnectWire
 * @see CATCGMCreateTopDisconnectShell
 */
class ExportedByCATGMOperatorsInterfaces CATICGMHybDisconnect: public CATICGMHybBoolean
{
public:
  /**
   * Constructor
   */
  CATICGMHybDisconnect();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

  /** 
    * Activates the query mode.
    * <br>To be called before the <tt>Run</tt> method.
    * @param iQueryMode
    * The activation of the query mode.
    * <br><b>Legal values</b>: 1 for rank + location activated (default value), 2 for rank activated, 0 for deactivated. 
    * The deactivation gives better performance.
    */
  virtual void SetQueryMode(int iQueryMode = 1) = 0;

  /** 
    * Returns the state of the query mode.
    * @return
    * The activation of the query mode.
    * <br><b>Legal values</b>: 1 for rank + location activated (default value), 2 for rank activated, 0 for deactivated. 
   */
  virtual int GetQueryMode() const = 0;

  /** 
   * Returns the location of the created cell.
   * <br>To be called after the <tt>Run</tt> method, if the query mode is activated.
   * @param iCell
   * The pointer to a created cell.
   * @return
   * The location of the cell with regards to the cutting body.
   * <br><b>Legal values</b>: <tt>1</tt> if it is at the left side, 
   * <tt>-1</tt> if it is at the right side.
   */
  virtual int GetCorrespondingSide(CATCell *iCell) = 0;

  /** 
   * Returns the rank of a created cell.
   * <br>To be called after the <tt>Run</tt> method, if the query mode is activated.
   * @param iCell
   * The pointer to a created cell.
   * @return
   * The corresponding rank. It may happen that several cells are generated on the same side of the
   * cutting object. If these cells are not directly connected, they are labelled by this method.
   */
  virtual int GetCorrespondingPackNumber(CATCell *iCell) = 0;

#ifdef CATIACGMR217CAA
  /**
   * Activates tracking of disconnecting cells.
   * Before calling Run, must be set to TRUE to be able to call GetDisconnectingCells after Run.
   * @param iTrackDisconnectingCells
   * <br><b>Legal values</b>:
   * <tt>TRUE</tt> to activate tracking of disconnecting cells, 
   * <tt>FALSE</tt> to deactivate tracking of disconnecting cells (default value).
   */
  virtual void SetTrackDisconnectingCells(CATBoolean iTrackDisconnectingCells) = 0;

  /**
   * Retrieve input disconnecting cells that lead to the construction of result cell.
   * To be called after Run, only if SetTrackDisconnectingCells(TRUE) was called before Run.
   * @param iResultCell
   * If the disconnecting element is a wire and the body to disconnect is a shell,
   * iResultCell must be an edge of the result body.
   * If the disconnecting element is a vertex and the body to disconnect is a wire,
   * iResultCell must be a vertex of the result body.
   * @param oDisconnectingCells
   * The output list.
   * If the disconnecting element is a wire and the body to disconnect is a shell,
   * oDisconnectingCells will contain all edges of the input disconnecting body that
   * lead to the construction of iResultCell.
   * If the disconnecting element is a vertex and the body to disconnect is a wire,
   * oDisconnectingCells will contain all vertices of the input disconnecting body that
   * lead to the construction of iResultCell
   */
  virtual void GetDisconnectingCells(
    CATCell *iResultCell,
    CATLISTP(CATCell) &oDisconnectingCells) = 0;
#endif

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMHybDisconnect(); // -> delete can't be called
};

#endif /* CATICGMHybDisconnect_h_ */
