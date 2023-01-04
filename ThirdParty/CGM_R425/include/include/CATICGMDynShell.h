#ifndef CATICGMDynShell_h_
#define CATICGMDynShell_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMOperatorsInterfaces.h"
#include "CATICGMDynOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"

class CATTopData;
class CATBody;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynShell;

/**
 * Interface representing the topological operator of shell.
 * A shell operation is available on bodies containing volumes: it corresponds to
 * two thickness operations on the body, with two different
 * offset values, followed by a subtraction between
 * the results of the thicknes operations.
 * As all the topological operators, the input objects are not modified. The resulting body is
 * a new one, that you can get by using the <tt>CATICGMDynOperator::GetResult</tt> method.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateDynShell</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods.
 * <li>Run it
 * <li>Get the resulting GetResult method. If you do not want
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATICGMDynShell: public CATICGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynShell();

  /**
 * Sets a list of faces with null internal and external offset values.
 *<br> Very useful to define openings in the resulting body.
 * @param iOpening
 * The list of openings.
 */
  virtual void Append(const CATLISTP(CATFace) &iOpening) = 0;

  /**
 * Modifies the offset values for a list of faces of the body to shell.
 * @param iSpecialOffset
 * A list of faces.
 * @param iInternalSpecialOffset
 * The list of the corresponding internal offsets.
  * @param iExternalSpecialOffset
 * The list of the corresponding external offsets.
 */
  virtual void Append(
    const CATLISTP(CATFace) &iSpecialOffset,
    double iInternalSpecialOffset,
    double iExternalSpecialOffset) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynShell(); // -> delete can't be called
};

/**
 * Creates a CATICGMDynShell operator.
 *<br> At the creation, the same internal and external offsets are
 * given for all the faces of the body to shell. To change offset
 * values for given faces, use the <tt>CATICGMDynShell::Append</tt> method.
 * @param iFactory
 * The pointer to the factory of the geometry.
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt>
 * is <tt>NULL</tt>, it is not filled.
 * @param iBody
 * The pointer to the 3D body to shell.
 * @param iInternal
 * The offset value for the thickness operation leading to
 * volume to substract.<br>
 * May be negative, if the volume to substract is smaller
 * than the initial <tt>iBody</tt>.
 * @param iExternal
 * The offset value for the thickness operation leading to
 * the main volume<br>
 * May be negative, if the main volume is smaller
 * than the initial <tt>iBody</tt>. Notice that <tt>iExternal>iInternal</tt>.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynShell *CATCGMCreateDynShell(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATLength iInternal,
  CATLength iExternal);

#endif /* CATICGMDynShell_h_ */
