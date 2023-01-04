#ifndef CATIPGMDynTransformation_h_
#define CATIPGMDynTransformation_h_

// COPYRIGHT DASSAULT SYSTEMES 2019

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMDynOperator.h"
#include "CATMathConstant.h"
#include "CATMathDef.h"
#include "CATCGMDynTransformationReportMode.h"

class CATBody;
class CATMathLine;
class CATMathPlane;
class CATMathPoint;
class CATMathTransformation;
class CATMathVector;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMDynTransformation;

/**
* Class representing the topological operator that transforms a CATBody.
* <br>
* It follows the use frame of all operator and satisfies to the smart mechanism: the
* input body is not modified. A new resulting body is created, 
* possibly sharing data with the input one.
*<ul>
* <li>A CATIPGMDynTransformation is created with the <tt>CATPGMCreateDynTransformation</tt> global function:
* It must be
* directly released with the <tt>Release</tt> method.
* It is not streamable. 
*<li>Options can be precised with the <tt>SetXxx</tt> methods, before
* asking for the computation with the <tt>Run</tt> method. In particular, the operator can be re-use to
* transform the same body with different transformations; in this case, you can precise another journal to
* be filled, with the <tt>SetNewJournal</tt> method. 
*<li>The result is accessed with the <tt>GetResult</tt> method. 
*</ul>
* This operator is optimized and simplified with regards to the @href CATTransfoManager : The CATDynTransfomation
* operator chooses the best way to call the CATTransfoManager. In another way, the CATTransfoManager provides more
* options.
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMDynTransformation: public CATIPGMDynOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMDynTransformation();

  /**
	* Defines <tt>this</tt> CATIPGMDynTransformation as a translation.
	* @param iTranslationVector
	* The vector of the translation.
	*/
  virtual void SetTranslation(const CATMathVector &iTranslationVector) = 0;

  /**
	* @nodoc
	*  Deprecated, use now the signature 
	* <tt>SetRotation       (const CATAngle iAngle, const CATMathLine & iAxis) </tt>,
	* where the angle is in radian.
	* <br>Defines the CATIPGMDynTransformation as a rotation.
	* @param iOrigin
	* The origin of the plane perpendicular to the rotation axis.
	* @param iAxis
	* Direction of the rotation.
	* @param iAngle
	* Angle of the rotation (in degrees).
	*/
  virtual void SetRotation(
    const CATMathPoint &iOrigin,
    const CATMathVector &iAxis,
    CATAngle iAngle) = 0;

  /**
	* Defines <tt>this</tt> CATIPGMDynTransformation as a rotation.
	* @param iAngle
	* The angle of the rotation (in radians).
	* @param iAxis
	* The direction of the rotation.
	*/
  virtual void SetRotation(const CATAngle iAngle, const CATMathLine &iAxis) = 0;

  /**
	* Defines <tt>this</tt> CATIPGMDynTransformation as a symmetry.
	* @param iSymmetryPlane
	* The plane of symmetry.
	*/
  virtual void SetSymmetry(const CATMathPlane &iSymmetryPlane) = 0;

  /**
	* Defines <tt>this</tt> CATIPGMDynTransformation as an affinity.
	* @param iReflectPlane
	* The plane for the reflecting part of the affinity.
	* @param iRatio
	* The value of the ratio for the scaling part of the affinity.<br>
	* The value <tt>iRatio=-1</tt> is the only value allowed for the moment.
	* Use better the <tt>SetSymmetry</tt> method.
	*/
  virtual void SetAffinity(const CATMathPlane &iReflectPlane, CATLength iRatio) = 0;

  /**
	* Defines <tt>this</tt> CATIPGMDynTransformation as a scaling.
	* @param iOrigin
	* The origin of the scaling.
	* @param iRatio
	* The value of the scaling
	*/
  virtual void SetScaling(const CATMathPoint &iOrigin, CATLength iRatio) = 0;

  /**
	* Sets to <tt>this</tt> CATIPGMDynTransformation the parameters of a given transformation.
	* @param iTransformation
	* The mathematical definition of the transformation.
	*/
  virtual void SetTransformation(const CATMathTransformation &iTransformation) = 0;

  /**
	* Defines the type of follow-up of the modifications to write in the journal.<br>
    * This information is used by applications, depending on the type of operations they want to 
	* perform after calling the transformation. This information has no impact on the objects of the
	* geometric modeler itself.
	* @param iTypeOfFollowUp
	* The type of report mode.
	* <br><b>Legal values</b>:
	* <dl><dt><tt>CATCGMDynTransformationModification</tt></dt>
	* <dd>The transformation is seen as a modification: the body is always duplicated, but the application
	* wants to mask the input body for showing only the resulting body (case of an applicative
	* transformation). This is the default of a CATIPGMDynTransformation.
	* <dt><tt>CATCGMDynTransformationCreation</tt></dt>
	* <dd>The transformation is seen as a creation: The application keeps the input body and
	* the duplicated body, and wants to union them for example:
	* this is a typical case of an applicative operation of mirror.
	* </dl>
	*/
  virtual void SetReportMode(CATCGMDynTransformationReportMode iTypeOfFollowUp) = 0;

  /**
	 * Defines whether a CATCGMJournalInfo has to be added to the item corresponding to <tt>this</tt> operation.
	 * @param iTrueOrFalse
	 * <tt>TRUE</tt> if an additional information must be added to the item, <tt>FALSE</tt> otherwise. In case of
	 * adding the additional information, this information is put to 0.
	 */
  virtual void SetJournalInfo(CATBoolean iTrueOrFalse) = 0;

  /**
	 * Defines another journal to be filled after another run of <tt>this</tt> operator.
	 * @param iJournal
	 * The pointer to the new journal to be filled in another run. This can be used in case of
	 * pattern transformation, if you want that each occurence has a different journal. 
	 */
  virtual void SetNewJournal(CATCGMJournalList *iJournal) = 0;

  /**
   * Controls whether the operator will use full duplicate mode (false by
   * default). <br>By default, before the transformation is performed, the
   * operator checks for surfaces that will remain invariant under the
   * transformation. These surfaces are re-used in the output, rather than being
   * copied and transformed. Calling <tt>SetFullDuplicateMode(TRUE)</tt>
   * will make the operator skip this optimization step and create duplicates of
   * every input surface.
   * @param iYesOrNo If <tt>TRUE</tt>, sets the operator to full duplicate mode.
   */
  virtual void SetFullDuplicateMode(CATBoolean iYesOrNo) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMDynTransformation(); // -> delete can't be called
};

/**
* Creates a CATIPGMDynTransformation.
* @param iFactory
* The factory of the geometry. 
* @param iData
* The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
* is <tt>NULL</tt>, it is not filled. 
* @param iBodyToTransform
* The pointer to the body to transform. This body will not be modified. A new resulting
* body is created, that can be retrieved by the <tt>GetResult</tt> method.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynTransformation *CATPGMCreateDynTransformation(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodytoTransform);

/**
* @nodoc
* Deprecated. Use CATPGMCreateDynTransformation.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynTransformation *CATPGMDynCreateTransformation(
  CATGeoFactory *iFactory,
  CATTopData *iData,
  CATBody *iBodytoTransform);

/**
* @nodoc
* Deprecated. Use CATPGMCreateDynTransformation.
* @return [out, IUnknown#Release]
*/
ExportedByCATGMOperatorsInterfaces CATIPGMDynTransformation *CATPGMDynCreateTransformation(
  CATGeoFactory *iFactory,
  CATBody *iBodytoTransform,
  CATCGMJournalList *iJournal = NULL);

#endif /* CATIPGMDynTransformation_h_ */
