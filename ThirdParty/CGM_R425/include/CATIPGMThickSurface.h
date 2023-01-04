#ifndef CATIPGMThickSurface_h_
#define CATIPGMThickSurface_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"
#include "CATCollec.h"

class CATBody;
class CATEdge;
class CATFace;
class CATOpThickSurface;
class CATShell;
class CATTopData;
class CATLISTP(CATFace);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMThickSurface;

/**
	* Class defining the operator to thicken a body in two opposite directions
	* according to the offsets specified for the thickening operation.
	* <br>
	* <ul>
	* <li>A CATIPGMThickSurface operator is created with the 
	* <tt>CATPGMCreateThickSurface</tt> global function:
	* It must be directly released with the <tt>Release</tt> method after use.
	* It is not streamable. 
	*<li>Options must be specified with the appropriate methods, before
	* asking for the computation with the <tt>Run</tt> method. 
	*<li>The result is accessed with the <tt>GetResult</tt> method. If you do not want 
	* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
	* geometric factory.
	*</ul>
 */
class ExportedByCATGMOperatorsInterfaces CATIPGMThickSurface: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMThickSurface();

  /**
	 * Specifies the orientation of a shell belonging to the body to be thickened.
	 * @param iShellToThick
	 * The shell the orientation is to be specified.
	 * @param iCoefOriVsOffsetValues
	 * The value to be specified for the iCoefOriVsOffsetValues argument are
	 * (other values to be rejected)
	 * <ul>
	 * <li>iCoefOriVsOffsetValues = +1 - Reference orientations of the iOffset_1 and iOffset_2 values.
	 * <li>iCoefOriVsOffsetValues = -1 - Orientation opposite to the offset orientation.
	 * </ul>
	 * <br>
	 * Given Vn the normal vector of the CATShell and
     * given VOffset_1 the offset vector to obtain the Offset_1 skin.
	 * <br>VOffset_1 = (iCoefOriVsOffsetValues x iOffset_1 ) . Vn
     * <br>Given VOffset_2 the offset vector to obtain the Offset_2 skin.
	 * VOffset_2 = (iCoefOriVsOffsetValues x iOffset_2 ) . Vn
	 */
  virtual void SetCoefOriForShellToThick(
    CATShell *iShellToThick,
    short iCoefOriVsOffsetValues) = 0;

  /**
    * iG1HealingMode = TRUE or FALSE.
    */
  virtual void SetG1HealingMode(CATBoolean iG1HealingMode) = 0;

  /**
    * iG1HealingTolerance if iG1HealingMode is TRUE.
    */
  virtual void SetG1HealingTolerance(double iG1HealingTolerance) = 0;

  /**
	 * Retrieves the body to be thickened. 
	 */
  virtual CATBody *GetBodyToThick() = 0;

  /**
	 * Retrieves the first offset
	 */
  virtual double GetOffset_1() = 0;

  /**
	 * Retrieves the second offset
	 */
  virtual double GetOffset_2() = 0;

  /**
  * @nodoc
  * 
  */
  virtual void Append(CATFace *iFace, double iOffset1, double iOffset2) = 0;

  /**
  * @nodoc 
  * To activate/deactivate tangency propagation for faces with special offset values.
  * If not set, there is no propagation.
  */
  virtual void SetSpecialOffsetFacesPropagation(short iPropagation) = 0;

  /**
 * @nodoc
 * @param iFacesToRemove
 * @param iOffsetIndex (0/1)
 * 
 */
  virtual void SetMandatoryFacesToRemove(
    const CATLISTP(CATFace) &iFacesToRemove,
    short iOffsetIndex) = 0;

  /**
 * @nodoc
 * @param oTrickyFaces
 * @param iOffsetIndex (0/1)
 * 
 */
  virtual void GetTrickyFaces(CATLISTP(CATFace) &oTrickyFaces) = 0;

  // Retour de la liste exhaustive des faces posant probleme, 
  // accompagnee de la liste parallele de diagnostics
  virtual void GetAllTrickyFaces(
    CATLISTP(CATFace) &ioAllTrickyFaces,
    CATListOfInt &ioAllDiag) = 0;

  /**
 * @nodoc
 * @param oFacesToIgnore 
 * @param iOffsetIndex (0/1)
 * 
 */
  virtual void GetFacesToIgnore(CATLISTP(CATFace) &oFacesToIgnore, short iOffsetIndex) = 0;

/**
 * @nodoc
 * @param oFacesToRegularise
 * @param oDiag
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd>Regularisation not required [forbidden output value]
 * <dt>1</dt><dd>Optimization required for local curvature problem
 * <dt>2</dt><dd>Optimization required for singular point
 * <dt>3</dt><dd>Optimization required for extrapolation failure
 * </dl>
 */
  virtual void GetFacesToRegularise(
    CATLISTP(CATFace) &oFacesToRegularise,
    CATListOfInt &oDiag) = 0;

  /**
  * Defines if procedural Offset surfaces must be approximated and
  * replaced by NurbsSurface
	* @param iApproxOffsetMode
	* <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation not required
  * <dt>1</dt><dd>Approximation required in C1 mode
  * <dt>2</dt><dd>Approximation required in C2 mode
  * @param iPostProRequired
  * <br><b>Legal values:</b>
  * <dl><dt>0</dt><dd>Approximation required during Offset algorithm
  * <dt>1</dt><dd>Approximation required after Offset algorithm
  * </dl>
  */
  virtual void SetApproxOffsetMode(short iApproxOffsetMode, short iPostProRequired = 1) = 0;

  /**
  * Defines the tolerance for C1 approximation 
	* @param iTolC1
  * </dl>
  */
  virtual void SetToleranceForApproxC1(double iTolC1) = 0;

  /**
  * Defines the tolerance for C2 approximation 
	* @param iTolC2
  * </dl>
  */
  virtual void SetToleranceForApproxC2(double iTolC2) = 0;

  /**
   * If TRUE, side ribbons are simplified
   * Default value is FALSE.
   */
  virtual void SetRibbonSimplification(CATBoolean iRibbonSimplification) = 0;

  /**
  * @nodoc
  * same rules as TrimByThick when iAlignOnTrimByThickBehavior is set to 1
  * (allow unsolved topology...).
  */
  virtual void SetAlignOnTrimByThickBehavior(short iAlignOnTrimByThickBehavior=1) = 0;

  // Execution de l'operation ThickSurface OneStepVolume  (RunOperator ne doit servir qu'en mode
  // CGMReplay)
  virtual int Run() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMThickSurface(); // -> delete can't be called
};

/** 
	* Creates a CATIPGMThickSurface operator.
	* @param iTopData
  * Contains a CATSoftwareConfiguration and a CATCGMJournalList
	* @param iBodyToThick
	* The pointer to the body (p CATShells) to be thickened. 
	* @param iOffset_1
  * first offset value for iBodyToThick
	* @param iOffset_2
  * second offset value for iBodyToThick
  * There are 2 conditions about iOffset_1 and iOffset_2 :
	* <ul>
  * <li>they have the same orientation reference
  * <li>Second, they have to be different.
	*</ul>
 * @return [out, IUnknown#Release]
  */
ExportedByCATGMOperatorsInterfaces CATIPGMThickSurface *CATPGMCreateThickSurface(
  CATTopData *iTopData,
  CATBody *iBodyToThick,
  double iOffset_1,
  double iOffset_2,
  short iDefaultSideForAllShells = 1);

#endif /* CATIPGMThickSurface_h_ */
