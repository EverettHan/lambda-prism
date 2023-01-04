#ifndef CATIPGMDynThickness_h_
#define CATIPGMDynThickness_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATCollec.h"
#include "CATMathDef.h"
#include "CATCGMJournal.h"

class CATTopData;
class CATBody;
class CATCGMJournalInfo;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynThickness;

/**
 * @level Protected
 * @usage U1
 */
//  FreezeMode --> CATBodyFreezeMode.h
/**
 * Interface representing the topological operator of thickness.
 * A thickness operation blows or shrinks the faces of a volume.
 * Each face may have its own offset value. The offset values
 * may be negative: the body is shrunk.
 * This operator can also be used to offset a shell. In this case, it is recommended to use the
 * SetSharpBorderMode API with the optimization parameter.
 * As all the topological operators, the input objects are not modified. The resulting body is
 * a new one, that you can get by using the <tt>CATIPGMDynOperator::GetResult</tt> method.
 * To use it:
 *<ul>
 * <li>Create it with the <tt>CATPGMCreateDynThickness</tt> global function.
 * <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
 * <li>Run it
 * <li>Get the resultin body with the <tt>GetResult</tt> method. If you do not want 
 * to keep these resulting body, use the @href CATICGMContainer#Remove method to remove them from the 
 * geometric factory, after the operator deletion.
 *<li>Release the operator with the <tt>Release</tt> method after use.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMDynThickness: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynThickness();

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

  /**
 * @nodoc
 * Internal use.
 * Modifies the type of the journal items created during <tt>this</tt> CATIPGMThick operation.
 * @param iTypeForFaceCreation
 * The item type.
 * @param iAdditionalInfo
 * The pointer to an additional information. If <tt>NULL</tt>, no additional information is added.
 */
  virtual void SetJournalTypeForFaceOffset(
    CATCGMJournal::Type iTypeForFaceCreation,
    CATCGMJournalInfo *iAdditionalInfo = NULL) = 0;

  /**
 * @nodoc
 * @param iFacesToRemove
 * 
 */
  virtual void SetMandatoryFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove) = 0;

  /**
 * @nodoc
 * @param iFacesToRemove
 * 
 */
  virtual void SetCandidateFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove) = 0;

  /**
 * @nodoc
 * @param oTrickyFaces
 * 
 */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  /**
 * @nodoc
 * @param oFacesToIgnore
 * 
 */
  virtual void GetFacesToIgnore(CATLISTP(CATFace) &oFacesToIgnore) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynThickness(); // -> delete can't be called
};

// Creation EntryPoints
/**
 * Creates a CATIPGMDynThickness operator.
 * <br>To define the offset
 * values for each face, use the <tt>CATIPGMDynThickness::Append</tt> method.
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
ExportedByCATGMOperatorsInterfaces CATIPGMDynThickness *CATPGMCreateDynThickness(
  CATGeoFactory *iContainer,
  CATTopData *iTopData,
  CATBody *iPart);

#endif /* CATIPGMDynThickness_h_ */
