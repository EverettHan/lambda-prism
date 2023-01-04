#ifndef CATICGMTopExtrude_h_
#define CATICGMTopExtrude_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATTopBooleanType.h"
#include "CATDataType.h"

class CATBody;
class CATCGMActivateDebug;
class CATCGMJournalList;
class CATError;
class CATGeoFactory;
class CATGeometry;
class CATTopData;
class CATLISTP(CATDomain);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMTopExtrude;

/**
 * Base class for of all the topological operators doing extrusions. 
 * <br>Extrusion operators deriving 
 * from this base class are used to build a prism, to revolve a profile about an axis 
 * or to sweep a profile along a guide.
 * <br> In addition to the extrusion creation, these operators provide the capability
 * to use a Boolean operation between a body (called trimming body), and the 
 * created extrusion. To obtain such result, use the <tt>SetOperation</tt>
 * and <tt>SetTrim</tt> methods. In this case, <tt>GetResult</tt> returns the
 * created extrusion limited by the trimming body, while <tt>GetBooleanResult</tt> returns the result of
 * the Boolean operation between the trimming body and the extrusion.
 */
class ExportedByCATGMOperatorsInterfaces CATICGMTopExtrude: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopExtrude();

  /**
 * Asks for the closure of the profile on a given body.
 * <br>The <tt>SetTrim</tt> method must then be called to define the triming body.
 */
  virtual void SetProfileClosure() = 0;

  /**
 * Asks for a Boolean operation between the extruded body and another (called trimming) body. 
 * @param iBoolType
 * The type of Boolean operation to perform after the extrusion. By default,
 * no Boolean operation is done.
 */
  virtual void SetOperation(CATTopBooleanType iBoolType = CatBoolNone) = 0;

  /**
 * Defines the triming body.
 * <br>The trimming body defines the body on which the profil must be closed.
 * Moreover, it defines the body used in the Boolean operation, if any.
 * Hence, this method must be called after either a <tt>SetProfileClosure</tt>,
 * or a <tt>SetOperation</tt> call. If both are invoked, only one trimming body
 * can be set.
 * @param iTrimBody
 * The pointer to the trimming body. 
 */
  virtual void SetTrim(CATBody *iTrimBody = NULL) = 0;

  /**
 * Defines the type of result to be output for <tt>this</tt> 
 * CATICGMTopExtrude operator.
 * @param iBothResultRequired
 * The type of result.
 * <dl><dt> <tt>CATBoolean(0)</tt></dt><dd> <tt>GetResult</tt> only returns the relimitated shape
 * <dt><tt>CATBoolean(1) </tt> </dt><dd> <ul> 
 *                    <li> <tt>GetResult</tt> returns the relimitated shape  
 *                      <li> <tt>GetBooleanResult</tt> returns the result of the Boolean operation
 *                                                     between the relimited shape and the trimming body.  
 *                       </ul>
 * </dl>
 */
  virtual void SetResultMode(CATBoolean iBothResultRequired = CATBoolean(0)) = 0;

#ifdef CATIACGMV5R23
  /**
 * Enables or disables the operator's thin-solid mode.  This mode allows you to input a
 * wire-body profile that will be automatically thickened in a direction normal
 * to the extrusion during the operation.  The result body will therefore be a solid.
 * @param iThinSolidMode
 * A value of TRUE enables thin-solid mode.
 * @param iIsNeutralFiber
 * A value of TRUE directs the operator to thicken equally on both sides of the profile.
 * @param iThinSolidThickness
 * The distance to thicken on each side of the profile.
 * @param
 * A list of wires within the profile for which the iThinSolidThickness values are used
 * in the reverse order.
 */
  virtual void SetThinSolidMode(
    const CATBoolean iThinSolidMode,
    const CATBoolean iIsNeutralFiber,
    const double iThinSolidThickness[2],
    CATLISTP(CATDomain) *iWireListWithReverseThinSolidSide = NULL) = 0;
#endif

  /**
 * Defines the simplication mode.
 * @param iSimplify
 * The simplication mode.
 * <br><b>Legal values</b>: <tt>CATBoolean(1)</tt> to simplify as much as possible the faces of the 
 * resulting body, <tt>CATBoolean(0)</tt> otherwise. By default, no simplication is done.
 */
  virtual void SetSimplification(CATBoolean iSimplify = CATBoolean(1)) = 0;

  /**
 * Defines the state of the resulting body.
 * @param iOnOrOff
 * The state of the resulting body. 
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

  /**
 * Returns the mode in which the resulting body is created.
 * @return
 * The state of the resulting body.
 */
  virtual CATBodyFreezeMode GetFreezeMode() const = 0;

  /**
 * Checks the consistency of the input operands.
 * @param ioNbError
 * The number of detected problems.
 * @param oErrors
 * The array of the pointers to the detected errors. 
 * <br>To be released with the <tt>Release</tt> method after use. 
 * @return
 * The result of the test.
 * <br><b>Legal values</b> <tt>0</tt> if a problem is detected, <tt>1</tt> otherwise.
 */
  virtual CATBoolean CheckOperands(CATLONG32 &oNbError, CATError **&oErrors) = 0;

  /**
 * Returns a pointer to the body resulting from the Boolean operation between the extrusion and a trimming body. 
 * <br>Available if <tt>SetResultMode(CATBoolean(1))</tt> has been invoked.
 * @return
 * The pointer to the created body. 
 * If you do not want to keep this body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 */
  virtual CATBody *GetBooleanResult() const = 0;

  /**
 * Returns a pointer to the topological Boolean journal dedicated to 
 * <tt>this</tt> CATICGMTopExtrude.
 * <br>The journal only contains the items relative to the Boolean operation. Available 
 * if <tt>SetResultMode(CATBoolean(1)) </tt> has been invoked.
 * @return
 * The pointer to the topological journal.
 */
  virtual CATCGMJournalList *GetBooleanJournal() const = 0;

  /**
 * Tests whether the trimming body is touched by the Boolean operation. 
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is touched, <tt>FALSE</tt> otherwise.
 */
  virtual CATBoolean IsResultInvariant() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopExtrude(); // -> delete can't be called
};

#endif /* CATICGMTopExtrude_h_ */
