#ifndef CATICGMDynThickness_h_
#define CATICGMDynThickness_h_

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

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMDynThickness;

/**
 * Interface representing the topological operator of thickness.
 * A thickness operation blows or shrinks the faces of a volume.
 * Each face may have its own offset value. The offset values
 * may be negative: the body is shrunk.
 * This operator can also be used to offset a shell. In this case, it is recommended to use the
 * SetSharpBorderMode API with the optimization parameter.
 * As all the topological operators, the input objects are not modified. The resulting body is
 * a new one, that you can get by using the <tt>CATICGMDynOperator::GetResult</tt> method.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATCGMCreateDynThickness</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resultin body with the <tt>GetResult</tt> method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMDynThickness: public CATICGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATICGMDynThickness();

  /**
 * Defines the offset value for a given list of faces of a body to thick.
 * @param iSpecialOffset
 * The list of the pointers to faces. The faces must belong to the body to thick.
 * @param iOffset
 * The offset value for the faces of <tt>iSpecialOffset</tt>. If <tt>iOffset < 0</tt>,
 * the faces are shrunk.
 */
  virtual void Append(
    const CATLISTP(CATFace) &iSpecialOffset,
    CATLength iOffset) = 0;

  /**
 * Defines the offset value that applies to all the body to thicken.
 * @param iOffsetValue
 * The offset value for all the faces. If <tt>iOffsetValue <0 </tt>,
 * the faces are shrunk.
 */
  virtual void SetDefaultOffsetValue(CATLength iOffsetValue) = 0;

  /**
  * Defines how borders are transformed in the neighborhood of sharp edges.
  * @param iSharpBorderOptimisation
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Optimization not required
  * <dt>1</dt><dd>Optimization required (the skin is handled like a volume)
  * </dl>
  */
  virtual void SetSharpBorderMode(short iSharpBorderOptimisation) = 0;

  /**
 * Defines the state of the resulting body.
 * @param iOnOrOff
 * The state of the resulting body. 
 */
  virtual void SetFreezeMode(CATBodyFreezeMode iOnOrOff) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMDynThickness(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * Creates a CATICGMDynThickness operator.
 * <br>To define the offset
 * values for each face, use the <tt>CATICGMDynThickness::Append</tt> method.
 * @param iForResultingBody
 * The pointer to the factory of the geometry for the creation of the resulting body. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iPart
 * The pointer to the 3D CATBody to operate.
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATICGMDynThickness *CATCGMCreateDynThickness(
  CATGeoFactory *iContainer,
  CATTopData *iTopData,
  CATBody *iPart);

#endif /* CATICGMDynThickness_h_ */
