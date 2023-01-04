#ifndef CATIPGMTopCompatible_h_
#define CATIPGMTopCompatible_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopMultiResult.h"

class CATBody;
class CATGeoFactory;
class CATTopData;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMTopCompatible;

/**
 * Class representing the topological operator which performs a compatible Boolean union of bodies.
 * <ul>
 * <li>Create it with the <tt>CATPGMCreateTopCompatibleForCGM</tt> or <tt>CATPGMCreateTopCompatibleForCVM</tt> global function.
 * <li>Run it ( only one time ).
 * <li>Get the resulting body with the <tt>GetResult</tt> method. 
 * If you do not want to keep this resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Release it after use with the <tt>Release</tt> method. 
 * </ul>
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible: public CATIPGMTopMultiResult
{
public:
  /**
   * Constructor
   */
  CATIPGMTopCompatible();

  /**
   * Activates suppress mode : in the case of a failure to integrate a body,
   * the operation continues with the remaining bodies. Any bodies which were
   * not integrated on the first pass get integrated together (where possible)
   * The results are returned as multiple bodies, with their own journals.
   * <br> This option is not activated by default. If activated, NonManifold
   * results <b>must</b> be authorised.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> Throw an error if a compatible operation fails.
   *     <dt><tt>1</tt><dd> Continue on error, and return multiple bodies</dl>
   */
  virtual void SetSuppressMode(int yes_or_no = 1) = 0;

  /**
  * Returns the suppress mode.
  * @return
  * <br><b>Legal values</b>:
  * <dl><dt><tt>0</tt><dd> suppress mode not active.
  *     <dt><tt>1</tt><dd> suppress mode is active.</dl>
  */
  virtual int  GetSuppressMode() const = 0;
  
  /**
  * @nodoc
  * Activate or deactivate  the imprint follow up mode.
  */
  virtual void SetImprintFollowUpMode(CATBoolean iImprintFollowUpMode) = 0;

  /**
  * @nodoc
  * Check if the imprint follow up mode is active or not.
  */
  virtual CATBoolean GetImprintFollowUpMode() const = 0;

  /**
  * @nodoc
  * Activate or deactivate the volume journal mode.
  */
  virtual void SetVolumeJournalMode(CATBoolean iVolumeJournalMode) = 0;

  /**
  * @nodoc
  * Check if the volume journal mode is active or not.
  */
  virtual CATBoolean GetVolumeJournalMode() const = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMTopCompatible(); // -> delete can't be called
};

/**
* Creates the manifold body resulting from the compatible boolean union of two bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody1
* A pointer to the first body.
* @param iBody2
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatibleForCGM(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody1,
  CATBody *iBody2);

/**
* @nodoc
* Creates the manifold body resulting from the compatible boolean union of a list of bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBodyList
* A pointer to the list of body to union
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatibleForCGM(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) *iBodyList);

//******************************************************************
// DEPRECATED, PLEASE DO NOT USE !!!
//******************************************************************
/**
* @nodoc
* Creates a body, which may be non-manifold, resulting from the compatible boolean union of two bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody1
* A pointer to the first body.
* @param iBody2
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatibleForCVM(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody1,
  CATBody *iBody2);

//******************************************************************
// DEPRECATED, PLEASE DO NOT USE !!!
//******************************************************************
/**
* @nodoc
* Creates a body, which may be non-manifold, resulting from the compatible boolean union of a list of bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody1
* A pointer to the first body.
* @param iBody2
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatibleForCVM(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATLISTP(CATBody) *iBodyList);

//******************************************************************
// DEPRECATED, PLEASE DO NOT USE !!!
//******************************************************************
/** (ld2)
* @nodoc
* Creates a body, which may be non-manifold, resulting from the compatible boolean union of two bodies.
* @param iFactory
* A pointer to the factory of the resulting body. 
* @param iTopData
* A pointer to the topological data.
* @param iBody1
* A pointer to the first body.
* @param iBody2
* A pointer to the second body.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatibleFull(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody1,
  CATBody *iBody2);

//******************************************************************
// DEPRECATED, PLEASE DO NOT USE !!!
//******************************************************************
/** (U29)
* @nodoc
* Creates a body resulting from the compatible boolean union of two bodies.
*  @param ipFactory
*    A pointer to the factory of the resulting body. 
*  @param ipTopData
*    A pointer to the topological data.
*  @param iBodyList
*    A pointer to the list of body to union.
*  @param iNonManifoldAuthorized
*    Flag to authorize full elements.
*  @param iJournalFull
*    Flag to specify if all the cells of the journal are expected.
* @return [out, IUnknown#Release]
* The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
*/
ExportedByCATGMOperatorsInterfaces CATIPGMTopCompatible *CATPGMCreateCompatible_Kernel(
  CATGeoFactory *ipFactory,
  CATTopData *ipTopData,
  CATLISTP(CATBody) *ipBodyList,
  CATBoolean iNonManifoldAuthorized = FALSE,
  CATBoolean iFullJournal = FALSE);

#endif /* CATIPGMTopCompatible_h_ */
