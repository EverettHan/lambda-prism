#ifndef CATIPGMHybProject_h_
#define CATIPGMHybProject_h_

// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Protected
 * @usage U3
 */

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMHybOperatorImp.h"
#include "CATCollec.h"
#include "CATHybDef.h"

class CATExtHybProject;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMHybProject;

/**
* Class defining the operator that projects a body on another one.
* It follows the general frame of all operator and satisfies to the smart mechanism: the
* input bodies are not modified. A new resulting body is created, 
* possibly sharing data with the input bodies.
*<ul>
* <li>CATIPGMHybProject is created with the <tt>CATPGMCreateTopProject</tt> global function.
* It must be
* directly released with the <tt>Release</tt> method after use.
* It is not streamable. 
* <li>The intersection can be restricted on a given domain on each body with the methods
* <tt>SetFirstDomainToIntersect</tt> and <tt>SetSecondDomainToIntersect</tt>
*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory.
*</ul>
* @see CATPGMCreateTopProject
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMHybProject: public CATIPGMHybOperatorImp
{
public:
  /**
   * Constructor
   */
  CATIPGMHybProject();

  /** @nodoc  */
  // (Empty macro in customer release mode; no effect on generated code)
  virtual int Run() = 0;

  /**
    * Defines which domain of the first body must be projected.
    * @param iDomain
    * The pointer to the domain to project.
    */
  virtual void SetDomainToProject(CATDomain *iDomain) = 0;

  /**
    * Defines on which domain of the second body the projection is done.
    * @param iDomain
    * The pointer to the domain on which to project.
    */
  virtual void SetDomainSupport(CATDomain *iDomain) = 0;

  /**
    * Returns the maximum distance of projection for a given domain of the resulting body.
    * @param iDomainOfResultBody
    * The pointer to the domain.
    * @return
    * The distance.
    */
  virtual double GetDistance(CATDomain *iDomainOfResultBody) = 0;

 /** @nodoc
   * Asks operator to suppress domains in wich all cells result from flatten operation.
   * <br> This option is not active by default.
   * @param yes_or_no
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> Desactivate mode.
   *     <dt><tt>1</tt><dd> Activate mode.</dl>
   */
  virtual void SetSuppressFlattenDomainMode(int yes_or_no = 1) = 0;

  /** @nodoc
   * Returns suppress flatten domain mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> Mode isn't active.
   *     <dt><tt>1</tt><dd> Mode is active.</dl>
   */
  virtual int GetSuppressFlattenDomainMode() const = 0;

  // In case LayDown Wire On Shell, we can precise the faces on the support
  // default is : all the faces are take into account
  /** 
   * Specifies the faces of the support body on which the projection should be done.
   * <br> By default, all faces are taken into account.
   * @param iCoveredFaces
   * The faces on which the projection should be done.
   */
  virtual void SetCoveredFaces(CATLISTP(CATFace) &iCoveredFaces) = 0;

  /** @nodoc
   * returns if faces have been specified.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No faces specified.
   *     <dt><tt>1</tt><dd> Faces have been specified.</dl>
   */
  virtual int IsCoveredFacesActive() const = 0;

  /**
   * Specify a maximum distance for the solution(s) to be kept. By default all the solutions
   * are returned.
   * @param iMaxDistance
   * The maximum distance.
   */
  virtual void SetMaxDistanceValue(double iMaxDistance) = 0;

  /** @nodoc
   * Returns the maximum distance that has been set.
   * <br> This method should not be called if a maximum distance hasn't been set.
   * @return 
   * The value of maximum distance.
   */
  virtual double GetMaxDistanceValue() const = 0;

  /** @nodoc
   * Returns if a maximum distance has been set.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No maximum distance.
   *     <dt><tt>1</tt><dd> Maximum distance has been set.</dl>
   */
  virtual int IsMaxDistanceActive() const = 0;

  /** @nodoc 
   * Returns the type of operation.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>PROJECTION</tt><dd> Operator performs a projection.
   *     <dt><tt>POSAGE</tt><dd> Operator performs a laydown.</dl>
   */
  virtual CATHybProjectionContext GetContext() = 0;

  /** @nodoc 
   * Changes type of operation. 
   * <br> Default operation is a projection.
   * @param iContext
   * <br><b>Legal values</b>:
   * <dl><dt><tt>PROJECTION</tt><dd> Operator performs a projection.
   *     <dt><tt>POSAGE</tt><dd> Operator performs a laydown.</dl>
   */
  virtual void SetContext(CATHybProjectionContext iContext) = 0;

  /** @nodoc
   * Asks operator to perform simplification of the result.
   * <br> This option is not active by default.
   * @param iSimplification
   * <br><b>Legal values</b>:
   * <dl><dt><tt>TRUE</tt><dd> Mode is active.
   *     <dt><tt>FALSE</tt><dd> Mode isn't active</dl>
   */
  virtual void SetSimplificationMode(CATBoolean iSimplification) = 0;

  /** @nodoc 
   * Returns simplification mode.
   * @return 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>TRUE</tt><dd> Mode is active.
   *     <dt><tt>FALSE</tt><dd> Mode isn't.</dl>
   */
  virtual CATBoolean GetSimplificationMode() const = 0;

 /** @nodoc
  * Checks if result is completely laid down.
  * <br> To be called after having run operator.
  * @return 
  * <br><b>Legal values</b>:
  * <dl><dt><tt>TRUE</tt><dd> Result is totally laid down.
  *     <dt><tt>FALSE</tt><dd> Result isn't totally laid down.</dl>
  */
  virtual CATBoolean IsCompletelyLaidDown() = 0;

  /** @nodoc  
  * Internal use.
  */
  virtual CATExtHybProject *GetHybProjectExtensible() const = 0;

  /** @nodoc
   * Asks operator to perfom smoothing of wires to project.
   * <br> This option is not active by default.
   * @param iSmooth
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No Smoothing. 
   *     <dt><tt>1</tt><dd> Smooth for tangency continuity. 
   *     <dt><tt>2</tt><dd> Smooth for curvature continuity .</dl>
   */
  virtual void SetNewSmoothing(CATLONG32 iSmooth) = 0;

  /** @nodoc 
   * Returns smoothing mode.
   * @param oSmooth 
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No Smoothing. 
   *     <dt><tt>1</tt><dd> Smooth for tangency continuity. 
   *     <dt><tt>2</tt><dd> Smooth for curvature continuity .</dl>
   */
  virtual void GetNewSmoothing(CATLONG32 &oSmooth) = 0;

  /** @nodoc
   * Asks operator to do a 3D cleaning of result wires, when smoothing mode is active. 
   * <br> By default a 2D cleaning is applied.
   * @param iOutputWireCleaning3DMode
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> 2D cleaning. 
   *     <dt><tt>1</tt><dd> 3D cleaning. </dl>
   */
  virtual void SetOutputWireCleaning3DMode(CATLONG32 iOutputWireCleaning3DMode) = 0;

  /** @nodoc 
   * Returns 3D cleaning mode.
   * @param oOutputWireCleaning3DMode
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> 2D cleaning. 
   *     <dt><tt>1</tt><dd> 3D cleaning. </dl>
   */
  virtual void GetOutputWireCleaning3DMode(CATLONG32 &oOutputWireCleaning3DMode) = 0;

  /** @nodoc 
   * Set the extrapolation mode 
   * for the extrapolation of the projection result wire on the SupportSurface
   * @param iExtrapolationMode
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No Extrapolation. 
   *     <dt><tt>1</tt><dd> Extrapolation in tangency continuity. </dl>
   *     <dt><tt>1</tt><dd> Extrapolation in curvature continuity. </dl>
   */
  virtual void SetExtrapolationMode(short iExtrapolationMode = 0) = 0;

  /** @nodoc 
   * Get the extrapolation mode 
   * for the extrapolation of the projection result wire on the SupportSurface
   * @param iExtrapolationMode
   * <br><b>Legal values</b>:
   * <dl><dt><tt>0</tt><dd> No Extrapolation. 
   *     <dt><tt>1</tt><dd> Extrapolation in tangency continuity. </dl>
   *     <dt><tt>1</tt><dd> Extrapolation in curvature continuity. </dl>
   */
  virtual void GetExtrapolationMode(short &oExtrapolationMode) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMHybProject(); // -> delete can't be called
};

#endif /* CATIPGMHybProject_h_ */
