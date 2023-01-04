#ifndef CATIPGMExtrapolateBody_h_
#define CATIPGMExtrapolateBody_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMTopOperator.h"

class CATBody;
class CATCGMJournalList;
class CATCell;
class CATCrvParam;
class CATCurve;
class CATDomain;
class CATEdge;
class CATFace;
class CATGeoFactory;
class CATLoop;
class CATMathBox;
class CATMathDirection;
class CATMathLine;
class CATMathPlane;
class CATMathPoint;
class CATMathVector;
class CATSurface;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMExtrapolateBody;

/**
 * @level Protected
 * @usage U1
 */

/**
* Class representing an operator that extrapolates 1D body (CATWire).
*<br>The wire can be extrapolated on a planar support (optional).
*<br>The extrapolation gives a result that is continuous in tangency. 
* To use it:
* <ul>
* <li>Create it with the <tt>CATPGMCreateExtrapolateBody</tt> global function.
* <li>Tune it with appropriate options, using the <tt>SetXxx</tt> methods. 
* <li>Run it
* <li>Get the resulting body, using the <tt>GetResult</tt> method. If you do not want 
* to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
* geometric factory, after the operator deletion.
*<li>Release the operator with the <tt>Release</tt> method after use.
*</ul> 
*/
class ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolateBody: public CATIPGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATIPGMExtrapolateBody();

  /**
    * Runs <tt>this</tt> operator.
    */
  virtual int Run() = 0;

  /** 
    * @nodoc 
    *<p>Extrapolates the wire to a CATMathBox limit.
    *<br>The target.
    *<xmp>
    *                                   --------- (*iTargetBox)
    *                                   !       !
    *      .....                        !       ! 
    *   ...                             !       !
    * ..                                ---------
    *</xmp>  
    *<br>The wire after extrapolation.
    *<xmp>
    *                                   --------- (*iTargetBox)
    *                                   !       !
    *      .............................!.......!. 
    *   ...                             !       ! 
    * ..                                --------- 
    * </xmp>
    * @param iEndCell
    * The pointer to the cell to be extrapolated.
    * @param iTargetBox
    * The pointer to the CATMathBox to be used as an extrapolation limit.
    */
  virtual void SetLimitToExtrapolate(CATCell *iEndCell, CATMathBox *iTargetBox) = 0;

  /** 
        * @nodoc 
        *<p>Extrapolates the wire to a CATBody limit. A CATMathBox is used
        * to refine the computation.
        *<br>The target.
        *<xmp>
        *                                   --------- (*iTargetBody)
        *                                   !       !
        *      .....                        !       ! 
        *   ...                             !       !
        * ..                                ---------  
        *</xmp>
        *<br>The wire after extrapolation.
        * <xmp>
        *                                   --------- (*iTargetBody)
        *                                   !       !
        *      .............................!       ! 
        *   ...                             !       ! 
        * ..                                ---------  
        * </xmp>
        * @param iEndCell
        * The pointer to the cell to be extrapolated.
        * @param iTargetBox
        * The pointer to the CATMathBox to be used in order to refine the computation.
        * @param iTargetBody
        * The pointer to the body to be used as an extrapolation limit.
    */
  virtual void SetLimitToExtrapolate(
    CATCell *iEndCell,
    CATMathBox *iTargetBox,
    CATBody *iTargetBody) = 0;

  /** 
        * Specifies the extrapolation length.
        * @param iEndCell
        * The pointer to the cell to be extrapolated.
        * @param iLength
        * The extrapolation length.
    */
  virtual void SetLimitToExtrapolate(CATCell *iEndCell, double iLength) = 0;

  /** 
        * @nodoc 
        *<p>Specifies a target CATMathBox plus another CATMathBox to be translated to
        * the extrapolation end.
        *                                   ---------
        *         ---- (*iSourceBox)        !       !
        *  .......!.*!                      !       ! 
        *         ----                      !       !
        *                                   ---------  
        * After extrapolation
        *                                   --------- (*iTargetBox)
        *                                   !       !----
        *      .............................!.......!!  ! (*iSourceBox translated to extrapolation end) 
        *   ...                             !       !----
        *                                   ---------  
        * @param iEndCell
        * The pointer to the cell to be extrapolated.
        * @param iSourceBox
        * The CATMathBox to be translated.
        * @param iTargetBox
        * The target box.
    */
  virtual void SetLimitToExtrapolate(
    CATCell *iEndCell,
    CATMathBox *iSourceBox,
    CATMathBox *iTargetBox) = 0;

  /** 
        * @nodoc 
        * Specifies a target plane. The input CATMathPlane can be of any orientation
        * (the normal to the plane
        * is defined so that the scalar product with the extrapolation direction is positive).
        *<xmp>
        *    --                                !
        *   !  !  ------------->               !->
        *    --                                !     
        * </xmp>
        * <p> After extrapolation
        *<xmp>
        * 
        *                                       ! --
        *                                       !!  !  
        *                                       ! --
        * </xmp>
        * In addition, the source box which is translated can be rotated around
        * the optional revolution axis. See below:
        * <xmp>
        *            * !  * (points resulting from the revolution)
        *          P   !     *
        *         *    C     M : End point translated by the source box 
        *         . *  !  *       
        *              !      . <-- tg: end tangent
        * tgP--> .     !
        *              !       . 
        *       .      !           * <-- targetplane 
        *              !       * 
        *      .       !   *
        *              O  
        *     .    *    .
        *       *         . (. : plane normal)
        *</xmp>
        */
  virtual void SetLimitToExtrapolate(
    CATCell *iEndCell,
    CATMathBox *iSourceBox,
    CATMathPlane *iTargetPlane,
    CATMathLine *iRevolutionAxis = NULL) = 0;

  /** 
     * @nodoc 
     * Specifies a CATMathDirection in addition to the CATMathBox. 
     * The translated plane relimits the extrapolation after the CATMathBox.
    *<xmp>
    *            *              --
    * ............* -->        !  ! 
    *              *            --
    *               * (plane)
    *</xmp>
    *<p> After extrapolation
    *<xmp>
    *                           -- *
    * .........................!..!.* 
    *                           --   *
    *                                 * (translated plane)
    *</xmp>
    */
  virtual void SetLimitToExtrapolate(
    CATCell *iEndCell,
    CATMathDirection *iSourcePlaneDirection,
    CATMathBox *iTargetBox) = 0;

  /**
    * Returns the pointer to the resulting body.
    */
  virtual CATBody *GetResult() = 0;

  /**
    @nodoc 
    Returns the topological journal.
    */
  virtual CATCGMJournalList *GetTopReport() = 0;

  /** @nodoc  
	* Enables the replacement of internal edge and vertex in the case of a line 
    * extrapolation.
	* By default, there is no replacement.
	*/
  virtual void SetReplaceMode() = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMExtrapolateBody(); // -> delete can't be called
};

/**
 * Creates a CATIPGMExtrapolateBody operator.
 * @param iFactory
 * The factory of the geometry. 
 * @param iData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iData</tt> 
 * is <tt>NULL</tt>, it is not filled.
 * @param iBodyToExtrapol
 * The CATWire to be extrapolated.
 * @param iSupport
 * The surfacic support on which the CATWire is to be extrapolated. This option is
 * only available for planar supports.
 * @param iMinimumGap
 * The minimum gap. 
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMExtrapolateBody *CATPGMCreateExtrapolateBody(
  CATGeoFactory *iGeoFactory,
  CATTopData *iTopData,
  CATBody *iBodyToExtrapol,
  CATSurface *iSupport = NULL,
  double iMinimumGap = 0.);

#endif /* CATIPGMExtrapolateBody_h_ */
