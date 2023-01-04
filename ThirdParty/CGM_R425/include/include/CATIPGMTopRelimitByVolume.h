#ifndef CATIPGMTopRelimitByVolume_h_
#define CATIPGMTopRelimitByVolume_h_

// COPYRIGHT DASSAULT SYSTEMES 2010

/**
 * @level Protected
 * @usage U1
 */

#include "CATGMModelInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATTopRelimitByVolumeContextForFastRun;

extern ExportedByCATGMModelInterfaces IID IID_CATIPGMTopRelimitByVolume;

/**
* Operator to trim a shell or a wire by a volume.
 * The generated result is made up of the portions of the input shell or wire which are
 * inside or outside the input volume. <br>
 * The body to be trimmed can be a multi-domain body. The domains making up the input body do 
 * not have necessarily to be of the same type. For example, the input body can contain a mixture of shells
 * and lumps.<br>
 * All the cells of the input body are trimmed by the volume and the portions to be kept
 * are to be specifed by using the <tt>SetSelectionType</tt> method. Resulting sub-elements
 * can be merged.
 * <p>
* The CATIPGMTopRelimitByVolume operator is not streamable. 
* <p>
* The CATIPGMTopRelimitByVolume operator is a multi-run operator: <br>
* the methods to set parameters as well as the <tt>Run</tt> and <tt>GetResult</tt> methods
* can be called several times from the same operator.
*  @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBodyToRelimit
* A pointer to the body to be trimmed or relimited.
* @param iSolidBody
* A pointer to the solid used as trimming object.
* @return [out, IUnknown#Release]
 */ 
class ExportedByCATGMModelInterfaces CATIPGMTopRelimitByVolume: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMTopRelimitByVolume();
  /**
 * @nodoc
 */
  virtual CATBoolean GetCheckJournal() const = 0;

 /**
 * Retrieves the type of selection (inside, outside or boundary)
 * @return
 * <ul>
 *   <li> 0 - no result is generated
 *   <li> 1 - the skin which is inside the volume is kept
 *   <li> 2 - the skin which is outside the volume is kept
 *   <li> 3 - all the sub-elements are kept
 *   <li> 4 - the skin which is on the volume boundary is kept
 * </ul>
 */
  virtual CATLONG32 GetSelectionType() const = 0;

  /**
  * @nodoc
  */
  virtual void SetComputationOfBoundary(CATBoolean iBoundary) = 0;

  /**
  * @nodoc
  */
  virtual void SetJournalMode(CATLONG32 iMode) = 0;

 /**
 * @nodoc
 */
  virtual void SetCheckJournal(CATBoolean iCheckMode) = 0;

/**
 * Specifies the portions of the input body to be kept.
 * @param
 * <ul>
 *   <li> 0 - no result is generated
 *   <li> 1 - the skin which is inside the volume is kept
 *   <li> 2 - the skin which is outside the volume is kept
 *   <li> 3 - all the sub-elements are kept
 *   <li> 4 - the skin which is on the volume boundary is kept
 * </ul>
 */
  virtual void SetSelectionType(CATLONG32 iSelectionType) = 0;

  /**
  * @nodoc
  * Returns the context for fast run specific of CATIPGMTopRelimitByVolume operator.
  * @param iGetOnly
  * If FALSE and context doesn't exist, it is created.
  * @return
  * The context for fast run.
  */
  virtual CATTopRelimitByVolumeContextForFastRun *GetTopRelimitByVolumeContextForFastRun(
    CATBoolean iGetOnly = FALSE) = 0;

  /**
  * Runs the operator.
  */
  virtual int Run() = 0;
 
 /**
  * Retrieves the trimmed result.
  * @param ioJournal
  * The journal of operations
  * @return
  * The generated result.
  */
  virtual CATBody *GetResult(CATCGMJournalList *ioJournal) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopRelimitByVolume(); // -> delete can't be called
};

#endif /* CATIPGMTopRelimitByVolume_h_ */
