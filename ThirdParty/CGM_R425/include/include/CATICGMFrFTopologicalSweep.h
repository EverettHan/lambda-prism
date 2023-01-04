#ifndef CATICGMFrFTopologicalSweep_h_
#define CATICGMFrFTopologicalSweep_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATIACGMLevel.h"
#include "CATGMOperatorsInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATFrFTopologicalSweepDef.h"
#include "CATDataType.h"

class CATBody;
class CATCompositeLaw;
class CATFrFMovingFrame;
class CATFrFSweepChecker;
class CATGeometry;
class CATLaw;
class CATMathAxis;
class CATMathDirection;
class CATSectionSolverEngine;
class CATSoftwareConfiguration;
class CATSweep;
class CATMathPoint;
class CATLISTP(CATCurve);
class CATLISTP(CATVertex);
class CATLISTP(CATGeometry);

extern ExportedByCATGMOperatorsInterfaces IID IID_CATICGMFrFTopologicalSweep;

/**
 * Class representing the topological operator that computes swept surfaces.
 * <br>A sweep operation is defined by:
 * <ul><li> One or several guides that are along the sweeping direction.
 * <li>One profile that is swept, or several profiles thru which the swept surface passes. 
 * In case of segment or circle profile, the profile is implicitely given.
 * <li>Optionally a spine curve, that defines the sweeping plane (also called moving frame @href CATMovingFrameType ).
 * </ul>
 * This operator can create, according to the chosen options:
 * <ul>
 * <li> Unspec sweep: one profile, one guide
 * <li> BiRail sweep: one profile, two guides
 * <li> Segment sweep: Define:
 * <ul><li>A1, A2: Angle Laws
 * <li>R: Radius Law
 * <li>LG, MG, FG: Limit, Middle, Functional Guide
 * <li>R1, R2: Length Laws
 * <li>LS, MS, FS: Limit, Middle, Functional Surface
 *</ul>
 * The following describes the needed inputs for each case: 
 * <pre> 
 *          R2         R1
 * Case 1: <--*-----*----->   2 Limit Guides L1 and L2
 * ------     L2    L1        2 Length Laws  (giving values R1 and R2)
 *
 *
 *           R2  LG  R1
 * Case 2:  <-----*----->      1 Limit Guide LG + 1 Functional Guide FG
 * ------        A \           2 Length Laws R1 and R2 + 1 Angle Law A
 *                  *FG
 *
 *
 * Case 3:   LG    MG
 * ------     *-----*-----      1 Limit Guide LG + 1 Middle Guide MG
 *
 *
 *           R2  LG  R1
 * Case 4:  <-----*----->      1 Limit Guide LG (PCurve)
 * ------       |---|S         2 Length Laws R1 and R2 +
 *                A            1 Angle Law A (% Surface Reference)
 *
 * </pre>
 * <li>Circle sweep: For the same notations as those for the segment sweep, 
 * <pre>
 * Case 1: *-----*-----*     3 Limit Guides L1 L2 and L3
 * ------  L1    L2    L3    No Laws
 *
 *
 *
 * Case 2:  *----------*      2 Limit Guides L1 and L2
 * ------   L1    \    L2     1 Radius Law R
 *                 R
 *
 *
 * Case 3:   F*
 * ------     |A1 *
 *            |  / o           1 Middle Guide + 1 Functional Guide
 *            | /A2 o          2 Angular Laws A1 and A2
 *           M*------*
 *
 *
 * Case 4:       ---           1 Middle Guide
 * ------      | R|  |         1 Radius Law R
 *            |   *   |
 *             |     |
 *               ---
 *
 *
 *           A1  MG  A2
 * Case 5:  <-----*----->      1 Middle Guide MG
 * ------       |---|S         2 Angle Laws A1 and A2 (% Surface Reference)
 *                R            1 Radius Law
 *
 *     
 *             o
 *        L1 o   o        
 * Case 6:  *     * L2        2 Limit Guides L1 and L2
 * ------  ! o   o             1 Reference Surface
 *         !   o   
 *         !
 *         ! Reference Surface 
 *
 * </pre>
 * <li>Conic sweep: For the same notations as those for the segment or circle 
 * sweep, 
 * <pre>
 * Case 1:                     5 Limit Guides L1 to L5
 * ------ 
 *  L1   
 *   *
 *    o
 *     o
 *       * L2
 *          o    
 *             o  L3 
 *                *   
 *                   o   L4      L5
 *                       *  o  o  *
 *
 * Case 2:                     4 Limit Guides L1 to L4
 * ------                      1 Slope (angle law % reference surface)
 *
 *  L1   
 *   *
 *    o
 *     o
 *       * L2
 *         o
 *            o  L3 
 *               *
 *                   o                    
 *                        o             L4
 *                               o   o  *----------------------- slope 
 *                                 -    angle
 *                                   -
 *                                     -
 *                                       - reference surface
 *                      
 * Case 3:                     3 Limit Guides
 * ------                      2 Slopes (angle law % reference surface)
 *                      
 *  L1   
 *  !*
 *  ! o
 *  !  o
 *  !    o
 *  !       o    
 *  !          o  L2 
 *  !             *   
 *  !                o 
 *  !                     o         L3
 *  o                            o  *----------------------- slope 
 *  slope                          -    angle
 * (angle + reference)               -
 *                                     -
 *                                       - reference surface
 *                      
 * Case 4:                     2 Limit Guides
 * ------                      2 Slopes (angle law % reference surface)
 *                             1 Rho Law
 *  L1   
 *  !*
 *  ! o
 *  !  o
 *  !    o
 *  !       o    
 *  !          o  
 *  !             o              L2  
 *  !                 o   o  o  o  *----------------------- slope 
 *  slope                          -    angle
 * (angle + reference)               -
 *                                     -
 *                                       - reference surface
 *                      
 * </pre>
 *</ul>
 *<br>
 * The CATICGMFrFTopologicalSweep operator follows the global frame of the topological operators 
 * and satisfies the smart mechanism: 
 * the input bodies are not modified. A new resulting body is created, 
 * possibly sharing data with the input bodies.
 *<ul>
 * <li>A CATICGMFrFTopologicalSweep operator is created with the <tt>CATCGMCreateFrFTopologicalSweep</tt> global method:
 * It must be directly released with the <tt>Release</tt> method after use. It is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.  
 *<li>In both cases, the result is accessed with the <tt>GetResult</tt> method. If you do not want 
 * to keep the resulting body, use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory.
 *</ul> 
 */
class ExportedByCATGMOperatorsInterfaces CATICGMFrFTopologicalSweep: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
                   CATICGMFrFTopologicalSweep             ();

  /**
 * Upgrade default operator settings.
 * (for historical and compatibility reasons old fashioned default settings are still active without this call).
 * Must be called immediatly after operator creation.
 * Level 1 default setting changes:
 * <ul>
 * <li>Twist detection is activated.
 * <li>Wrap detection is activated.
 * <li>All angles are defined in degree including in circular sweep case.
 * <li>In case of profile or guide support, internal laydown will be done.
 * </ul>
 * @param iSettingsLevel
 * the default settings level (if 0, always set the operator to the best so far default settings)
 */
  virtual void     SetUpgradedDefaultSettings             (int                           iSettingsLevel            = 0) = 0;

  /**
 * Explicit downgrade query for one upgraded setting.
 * (must be done between SetUpgradedDefaultSettings() and other specifications definition).
 * @param iSettingDowngrade
 * setting downgrade query
 */
  virtual void     SetDowngradeSetting                    (CATFrFTopologicalDowngradeSetting_Type
                                                                                         iSettingDowngrade         )    = 0;

  /**
 * Runs <tt>this</tt> operator.
 */
  virtual int      Run                                    ()                                                            = 0;

  /**
 * Returns the result of <tt>this</tt> operator.
 * @return
 * The pointer to the created body. You must delete it with the @href CATICGMContainer#Remove 
 * method if you do not want to keep it. 
 */
  virtual CATBody* GetResult                              ()                                                            = 0 ;

  /**
 * Defines the spine.
 * @param iSpine
 * The pointer to the CATCurve or the wire body defining the spine. For a multi profiles sweep,
 * if <tt>iSpine=NULL</tt> and if
 * <tt>iSpineType=CATFrFTopologicalSweepSpine_Implicit</tt>, the spine is automatically computed
 * using the input profiles.
 * @param iSpineType
 * The spine type.
 */
  virtual void     SetSpine                               (CATGeometry                *  iSpine                    ,
                                                           CATFrFTopologicalSweepSpine_Type
                                                                                         iSpineType                = CATFrFTopologicalSweepSpine_Explicit) = 0;

  /**
 * Returns the spine.
 * @return
 * The pointer to the input or computed spine. The computed (or implicit) spine belongs to
 * this operator and is deleted at the operator deletion.
 */
  virtual CATGeometry* GetSpine                           ()                                                            = 0;

  /**
 * Moving frame type definition.
 * @param   iMFViewingDir
 * Used as viewing direction
 *   (if not provided, an automatic viewing direction will
 *   be computed)
 * if type is CATFrFTopologicalSweepMF_ParallelToPlane:
 * @param   iMFDir
 * Used as plane normal
 * Moving frame is computed using spine provided by SetSpine()
 * or first guide if no spine provided)
 */
  virtual void     SetMovingFrameParms                    (CATFrFTopologicalSweepMF_Type iMFType                   ,
                                                           CATMathDirection*             iMFViewingDir             = NULL,
                                                           CATMathDirection*             iMFDir                    = NULL) = 0;

  /**
 * (temporary and restricted use).
 * Manages motion axis twist with a variable (local) viewing direction.
 * To be used only with following conditions;
 * <ul>
 * <li>Standard moving frame type (CATFrFTopologicalSweepMF_Ortho).
 * <li>Unspec sweep (with profile)
 * <li>Spine with a complex 3D curve
 * </ul>
 */
  virtual void     ForceVariableViewingDirMode            ()                                                            = 0;

  /**
 * Sets the simplification mode.
 * @param iSimplify
 * The simplification mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for simplifying the adjacent faces on the same surface
 * (typically plane), <tt>FALSE</tt> otherwise (default mode at the operator creation).
 */
  virtual void     SetSimplification                      (CATBoolean                    iSimplify                 = CATBoolean(1)) = 0;

  /**
 * Sets the plane detection mode.
 * @param iPlanesDetection
 * The plane detection mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for replacing planar surfaces by planes,
 * <tt>FALSE</tt> otherwise (default mode at the operator creation).
 */
  virtual void     SetPlanesDetection                     (CATBoolean                    iPlanesDetection          = CATBoolean(1)) = 0;

  /**
 * Sets the canonic surfaces detection mode (cones/cylinders/planes).
 * @param iCanonicSurfacesDetection
 * The canonic surface detection mode.
 * <br><b>Legal values</b>: <tt>TRUE</tt> for replacing nurbs surfaces by canonic surfaces,
 * <tt>FALSE</tt> otherwise (default mode at the operator creation).
 */
  virtual void     SetCanonicSurfacesDetection            (CATBoolean                    iCanonicSurfacesDetection = CATBoolean(1)) = 0;

  //-----------------------------------------------------------------------
  //--------------- Methods for Unspec Sweep only -------------------------
  //-----------------------------------------------------------------------
  /** 
 * Definition of profile positioning type for a sweep with one or two guides (Sweep unspec and birail).
 * @param iPositionType
 * The type of profile positioning.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>1</tt></dt><dd>The profile is moved according to the transformation of its
 * axes system to the axes system of the beginning of the guide.
 * It is possible to redefine the profile axis system
 * by using the <tt>SetProfilePosition</tt>. 
 * If not, the axis system of the beginning of the guide is used and
 * the sweep starts at the profile location (default mode).
 * <dt><tt>2</tt></dt><dd>The sweep surface passes thru the profile: the profile axes system is
 * computed by intersecting the mean profile plane and the guide. 
 * This mean profile plane must be perpendicular to the guide.
 * <dt><tt>3</tt></dt><dd>The profile axes system is automatically computed as follows:
 * <ul>
 * <li>The origin is the start point of the profile.
 * <li>The third (Z) direction is normal to the profile medium plane.
 * <li>The first (X) direction joins the start and end points of the profile and is normalized.
 * <li>The second (Y) direction is completed by the vectorial product <tt>Y = Z^X</tt>.
 * </ul>
 *<pre>     ^Y
 *     ! ****
 *     !*    *
 *     *--->X * </pre>
 * <dt><tt>4</tt></dt><dd>The sweep surface passes thru the profile. This is the same
 * as <tt>iPositionType=2</tt>, except that the mean profile plane need not 
 *                     intersect guide and be perpendicular to guide.
 * <dt><tt>5</tt></dt><dd> for two guides sweeps only: same as <tt>iPositionType=2</tt>,
 * except that the extremities of the profile are not moved to the intersection with guides
 *<pre>
 *                     * guide points, - profile points, o profile extremities
 *                     initial profile:
 *                     o----*--...--*---o 
 *                     current profile with iPositionType=2:
 *                         *o---...---o*  (zoomed)
 *                     moving profile with iPositionType=5:
 *                     o----*--...--*---o   </pre>
 * </dl>
 */
  virtual void     SetProfilePositionType                 (CATLONG32                     iPositionType             )    = 0;

  /**
 * Defines the axes system of the profile.
 * <br>To use in case of profile position type <tt>iPositionType=1</tt>.
 * @param iProfileAxis
 * The axes system of the profile.
 */
  virtual void     SetProfilePosition                     (CATMathAxis                *  iProfileAxis              )    = 0;

  /**
 * Retrieves the axes system of the profile (Sweep unspec.
 * @param oProfileAxis
 * The pointer to the input or computed axes system of the profile. 
 * The computed axes system belongs to
 * this operator and is deleted at the operator deletion.
 */
  virtual void     GetProfilePosition                     (CATMathAxis                *& oProfileAxis              )    = 0;

  // Access to current frame
  // (default: final frame, using reference element, and angle law)
  // use SetBehaviourMode(CATFrFTopologicalSweepBehaviour_MovingFrameType)
  // to obtain moving frame
  /**
 * Retrieves the moving frame at a given ratio parameter.
 * @param iLambda
 * The parameter <tt>0 <= iLambda <=1 </tt> indicating where the frame is retrieved.
 * @param oFrame
 * The moving frame, that may or may not have been allocated before call
 *  and must be deallocated after 
 */
  virtual void     GetFrame                               (double                        iLambda                   ,
                                                           CATMathAxis                *& oFrame                    )    = 0;

  /**
 * Defines a variable viewing direction (sweep unspec).
 * @param iReferenceElement
 * The pointer to the geometry (CATSurface, skin CATBody). The current point
 * is projected onto the reference element. The viewing direction is the normal
 * to the reference element at the projected point. 
 * <ul><li>In case of a plane, the
 * viewing direction is constant.
 * <li>In case of a skin body, the guide must lay on the reference element.
 * </ul>
 */
  virtual void     SetReferenceElement                    (CATGeometry                 * iReferenceElement         )    = 0;

  /**
 * Defines an angular law to rotate the moving frame around its <tt>Z</tt> axis.
 * @param iAngularLaw
 * The pointer to the angular law.
 * (historical behaviour: Angles must be given in radian for circular sweep, in degree for other types of sweep;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: Angles always given in degree)
 * 
 */
  virtual void     SetAngularLaw                          (CATCompositeLaw            *  iAngularLaw               )    = 0;

  /**
 * Defines an angular law to rotate the moving frame around its <tt>Z</tt> axis.
 * @param iAngularLaw
 * The pointer to the angular law.
 * (historical behaviour: Angles must be given in radian for circular sweep, in degree for other types of sweep;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: Angles always given in degree)
 */
  virtual void     SetAngularLaw                          (CATLaw                     *  iAngularLaw               )    = 0;

  //-----------------------------------------------------------------------
  //--------------- Methods for BiRail Sweep only -------------------------
  //-----------------------------------------------------------------------
  /** 
 * Defines the anchor points for profile positionning.
 * <br>Moving the anchor points
 * from their initial position to intersection points between the sweeping plane 
 * and the guides, defines the 3D transformation to apply to the initial profile.
 * Anchor points should be in the profile plane for correct behaviour of
 * profile positionning software.
 * @param iPoint1
 * The point to anchor on first guide.
 * @param iPoint2
 * The point to anchor on second guide.
 */
  virtual void     SetAnchorPoints                  (const CATMathPoint                & iPoint1                   ,
                                                     const CATMathPoint                & iPoint2                   )    = 0;

  /**
 * Defines the scaling mode to apply to the profile.
 * @param iScalingOption
 * The scaling option
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd> Inactive scaling
 * <dt>1</dt><dd> Active scaling (default mode).
 * </dl>
 */
  virtual void     SetProfileScalingOption                (CATLONG32                     iScalingOption            )    = 0;

  //-----------------------------------------------------------------------
  //--------------- Methods for Canonic profile sweep only:    ------------
  //--------------- Segment, Circle and Conic                  ------------
  //-----------------------------------------------------------------------
  /**
 * Defines the limiting guides of a segment or circle sweep.
 * According to the number of guides, an appropriate build method is chosen.
 * This choice can also be explicitely given for a circle sweep
 * by the <tt>SetSolutionChoice</tt> method.
 * @param iLimitGuides
 * The pointer to the list of pointers to the (wire body or curve) guides. 
 */
  virtual void     SetLimitGuides                         (CATLISTP(CATGeometry)      *  iLimitGuides              )    = 0 ;

  /**
 * Defines the references for the (start and end) angles measurement for a segment or circle sweep.
 *<br>To use according of the chosen sweep case.The sweep may not pass thru the functional guides.
 * @param iFunctionalGuides
 * The list of pointers to the one or two reference guides.
 */
  virtual void     SetFunctionalGuides                    (CATLISTP(CATGeometry)      *  iFunctionalGuides         )    = 0 ;

  /**
 * Defines the guide defining the center of the circle for a segment or circle sweep.
 * <br>To use according of the chosen sweep case.
 * @param iMiddleGuides
 * The list of pointers to the one middle guide.
 */
  virtual void     SetMiddleGuides                        (CATLISTP(CATGeometry)       * iMiddleGuides             )    = 0 ;

  /**
 * Defines the angular laws for defining limiting guides.
 *<br>To use according of the chosen sweep case.
 * @param iLaws
 * The array of the pointers to the laws. 
 * @param iNbLaws
 * The number of laws. 
 * (historical behaviour: Angles must be given in radian for circular sweep, in degree for other types of sweep;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: Angles always given in degree)
 */
  virtual void     SetAngularLaws                         (CATCompositeLaw            ** iLaws                     ,
                                                           int                           iNbLaws                   )    = 0 ;

  /**
 * Defines the angular laws for defining limiting guides.
 *<br>To use according of the chosen sweep case.
 * @param iLaws
 * The array of the pointers to the laws.
 * @param iNbLaws
 * The number of laws.
 * (historical behaviour: Angles must be given in radian for circular sweep, in degree for other types of sweep;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: Angles always given in degree)
 */
  virtual void     SetAngularLaws                         (CATLaw                     ** iLaws                     ,
                                                           int                           iNbLaws                   ) = 0 ;

  /**
 * Defines the angular laws for defining limiting guides.
 *<br>To use according of the chosen sweep case.
 * @param iLaws
 * The array of the pointers to the laws.
 * @param iNbLaws
 * The number of laws.
 * (Angles must be given in degree, including in circular sweep case)
 */
  virtual void     SetAngularLawsInDegree                 (CATLaw                    **  iLaws                     ,
                                                           int                           iNbLaws                   )    = 0 ;

  /**
 * Defines the length laws for a segment sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaws
 * The array of the pointers to the laws.
 * @param iNbLaws
 * The number of laws.
 */
  virtual void     SetLengthLaws                          (CATCompositeLaw           **  iLaws                     ,
                                                           int                           iNbLaws                   )    = 0 ;

  /**
 * Defines the length laws for a segment sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaws
 * The array of the pointers to the laws.
 * @param iNbLaws
 * The number of laws.
 */
  virtual void     SetLengthLaws                          (CATLaw                     ** iLaws                     ,
                                                           int                           iNbLaws                   )    = 0 ;

  /**
 * Defines the radius law of a circle sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaw
 * The pointer to the radius law.
 */
  virtual void     SetRadiusLaw                           (CATCompositeLaw            *  iLaw                      )    = 0 ;

  /**
 * Defines the radius law of a circle sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaw
 * The pointer to the radius law.
 */
  virtual void     SetRadiusLaw                           (CATLaw                     *  iLaw                      )    = 0 ;

  /**
 * Defines the rho law of a conic sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaw
 * The pointer to the rho law, defining the conic type.
 */
  virtual void     SetRhoLaw                              (CATCompositeLaw            *  iLaw                      )    = 0 ;

  /**
 * Defines the rho law of a conic sweep.
 *<br>To use according of the chosen sweep case.
 * @param iLaw
 * The pointer to the rho law, defining the conic type.
 */
  virtual void     SetRhoLaw                              (CATLaw                     *  iLaw                      )    = 0 ;

  /**
 * Defines a slope condition for a conic or a circle sweep.
 *<br>To use according of the chosen sweep case.
 * @param iGuideRank
 * The rank of the guide on which the slope condition applies
 * (first or last guide).
 * @param iReferenceElement
 * The pointer to the reference element (CATPlane or skin CATBody or wire CATBody)
 * defining the angular reference. For a null angle, conic will be tangent
 * to the plane or skin reference element, or to the line joining guide 
 * and a wire reference element. 
 * @param iAngleLaw
 * The pointer to the angle law.
 */
  virtual void     SetLimitGuideSlopeCondition            (int                           iLimitGuideRank           ,
                                                           CATGeometry                 * iReferenceElement         ,
                                                           CATCompositeLaw             * iAngularLaw               )    = 0 ;

  /**
 * Defines a slope condition for a conic or a circle sweep.
 *<br>To use according of the chosen sweep case.
 * @param iGuideRank
 * The rank of the guide on which the slope condition applies
 * (first or last guide).
 * @param iReferenceElement
 * The pointer to the reference element (CATPlane or skin CATBody or wire CATBody)
 * defining the angular reference. For a null angle, conic will be tangent
 * to the plane or skin reference element, or to the line joining guide 
 * and a wire reference element.
 * @param iAngleLaw
 * The pointer to the angle law.
 */
  virtual void     SetLimitGuideSlopeCondition            (int                           iLimitGuideRank           ,
                                                           CATGeometry*                  iReferenceElement         ,
                                                           CATLaw*                       iAngularLaw               )    = 0 ;

  /**
 * Defines the conic, circle or segment to keep if case of ambiguous case.
 * @param iSolutionChoice
 * The chosen part. Refer to the encyclopedia documentation.
 */
  virtual void     SetSolutionChoice                      (CATLONG32                     iSolutionChoice           )    = 0 ;

  /**
 * Defines limiting elements to be used instead of one or two length laws in a segment sweep.
 *<br>To use according of the chosen sweep case.
 * @param iNbElements
 * The number of limiting elements
 * <br><b>Legal values:</b>
 * <dl><dt>0</dt><dd> If no limiting element
 * <dt>1</dt><dd> If only one limiting element instead of first length law.
 * <dt>2</dt><dd> If two limiting elements (first one may be null).
 * </dl>
 * @param iLimitingElements
 * The array of pointers to the limiting elements (CATPlane).
 * Null elements may be given.
 */
  virtual void     SetLimitingElements                    (int                           iNbElements               ,
                                                           CATGeometry**                 iLimitingElements         )    = 0 ;

  /**
 * Defines cone option for segment sweep computation with reference element
 * (behaves like a draft computation).
 */
  virtual void     SetConeOption                          ()                                                            = 0 ;

  //-----------------------------------------------------------------------
  //--------------- Methods for Multiprofile Sweep only -------------------
  //-----------------------------------------------------------------------
  /**
 * Sets the continuity constraints on start and end profiles (for multi profiles sweep).
 * <br>The start and end profiles are not necessarily the first and last
 * profile of the list given at the operator creation.
 * @param iProfileRank
 * The rank (beginning at 1) of the profile to constraint.
 * @param iReferenceElement
 * The pointer to the reference element (CATPlane or skin CATBody) on which the profile
 * must lay. The sweep is tangent to a skin CATBody reference element and normal to 
 * a CATPlane reference element.
 * @param iContinuityCondition
 * The type of continuity constraint.
 */
  virtual void     SetProfileContinuityCondition          (int                            iProfileRank,
                                                           CATGeometry                  * iReferenceElement,
                                                           CATFrFTopologicalSweepContinuity_Type
                                                                                          iContinuityCondition     = CATFrFTopologicalSweepContinuity_G1
                                                                                                                      ) = 0 ;

  /**
 * Defines the profile automatic coupling mode.
 * @param iCouplingType
 * The coupling type.
 * @param iForceErrorOnImpossibleCoupling
 * The error management.
 * <br><b>Legal values:</b>
 * <dl><dt>FALSE</dt><dd> If the required coupling mode is not possible, the operator tries to couple
 * in a lower mode (the lowest mode is the coupling by curvilinear length).
 * <dt>TRUE</dt><dd> An error is thrown if the required coupling is not possible.
 * </dl>
 * @param iCoupleFirstVerticesOnImpossibleCoupling
 * The coupling strategy when coupling is impossible.
 * <br><b>Legal values:</b>
 * <dl><dt>FALSE</dt><dd> If the required coupling mode is not possible, the operator tries to couple
 * in a lower mode or raises an error (according to <tt>iForceErrorOnImpossibleCoupling</tt> param)
 * <dt>TRUE</dt><dd> The first vertices with same continuity of the corresponding domains are coupled, 
 * even if some vertices counts are different in these domains: vertices may be left in some domains.
 * </dl>
 */
  virtual void     SetProfileAutomaticCouplingMode        (CATFrFTopologicalSweepAutomaticCoupling_Type
                                                                                         iCouplingType,
                                                           CATBoolean                    iForceErrorOnImpossibleCoupling          = FALSE,
                                                           CATBoolean                    iCoupleFirstVerticesOnImpossibleCoupling = FALSE
                                                                                                                      ) = 0 ;

  /**
 * Sets the continuity constraints (for multi profiles sweep) for a guide.
 * @param iRankGuide
 * The rank (beginning at 1) of the guide to constraint.
 * @param iReferenceElement
 * The pointer to the reference element (CATPlane or skin CATBody) on which the guide
 * must lay. Each sweep moving section is tangent to a skin CATBody reference element and normal to 
 * a CATPlane reference element.
 * @param iContinuityCondition
 * The type of continuity constraint.
 */
  virtual void     SetGuideContinuityCondition            (int                           iRankGuide                ,
                                                           CATGeometry                 * iReferenceElement         ,
                                                           CATFrFTopologicalSweepContinuity_Type
                                                                                         iContinuityCondition      = CATFrFTopologicalSweepContinuity_G1
                                                                                                                   )    = 0 ;

  /**
 * Sets the profiles orientation (for multi profiles sweep).
 * @param iRankProfile
 * The rank (beginning at 1) of the profile.
 * @param iOrientation
 * The orientation of the profile: 
 * <br><b>Legal values</b>: <tt>CATFrFTopologicalSweepOrientation_Positive</tt>
 * to take the natural orientation of the profile,  
 * <tt>CATFrFTopologicalSweepOrientation_Negative</tt> for the opposite orientation.
 */
  virtual void     SetProfileOrientation                  (int                           iRankProfile,
                                                           CATFrFTopologicalSweepOrientation_Type
                                                                                         iOrientation              = CATFrFTopologicalSweepOrientation_Positive
                                                                                                                   )    = 0 ;

  /**
 * Sets the relimitation mode by the extremity profiles.
 * @param iRelimitationMode
 * The relimitation mode.
 */
  virtual void     SetRelimitationMode                    (CATFrFTopologicalSweepRelimitation_Type
                                                                                         iRelimitationMode         = CATFrFTopologicalSweepRelimitation_Off
                                                                                                                   )    = 0 ;

  /**
 * Defines additional guides to be used only for profile sections coupling.
 * @param iCouplingGuides
 * The list of pointers to the coupling guides (wire bodies).
 */
  virtual void     SetCouplingGuides                      (CATLISTP(CATGeometry)       * iCouplingGuides           )    = 0 ;

  /**
 * Gets vertices non coupled by automatic section vertices coupling.
 * @param oVertices
 * The list of non coupled section vertices.
 * @param oSectionNumbers
 * The list of section numbers for non coupled vertices.
 * @param oEdgeNumbers
 * The list of edge numbers for non coupled vertices (the vertex oVertices[i] is
 * between edge oEdgeNumbers[i] and edge 1+oEdgeNumbers[i])
 * @param oLevels
 * The list of discontinuity levels for non coupled vertices
 * (1 for C0 non C1 vertices, 2 for C1 non C2 vertices) 
 * @param oDomains
 * The list of domain numbers for non coupled vertices
 * (internal numerotation within current level management; same domain number
 * may be given during non C1 vertices management and during non C2 vertices 
 * management)
 */
  virtual void     GetNonCoupledSectionVertices           (CATLISTP(CATVertex)         * oVertices                 = 0,
                                                           CATListOfInt                * oSectionNumbers           = 0,
                                                           CATListOfInt                * oEdgeNumbers              = 0,
                                                           CATListOfInt                * oLevels                   = 0,
                                                           CATListOfInt                * oDomains                  = 0) = 0 ;

  /**
 * Internal use.
 * Defines the guide to be used for positionning the moving axis origin.
 * @param iChosenGuide
 * The guide chosen (that must belong to the set of limit or functional guides). 
 * @param iReferenceElement
 * The reference element chosen for normal computation. 
 */
  virtual void     ChooseOriginGuide                      (CATGeometry                 * iChosenGuide              ,
                                                           CATGeometry                 * iReferenceElement         = NULL) = 0 ;

  /**
 * Gets the initial area for the profile evaluated in a given parameter,
 * and the final area after application of the area law (if any).
 * @param iParam
 * The parameter value in which the area is to be computed.
 * @param iInitialArea
 * The profile area before deformation with area law.
 * @param iFinalArea
 * The profile area after deformation with area law.
 */
  virtual void     GetProfileArea                         (double                        iParam                    ,
                                                           double                      & oInitialArea              ,
                                                           double                      & oFinalArea                )    = 0 ;

  /**
 * Defines the area law for section deformation.
 * This option is available only with 0, 1 or 2 guides.
 * If the input sections do not fit with the area law, the surface will not
 * fit to these sections.
 */
  virtual void     SetAreaLaw                             (CATCompositeLaw            *  iAreaLaw                  ) = 0 ;

  /**
 * Defines the area law for section deformation.
 * This option is available only with 0, 1 or 2 guides.
 * If the input sections do not fit with the area law, the surface will not
 * fit to theses sections.
 */
  virtual void     SetAreaLaw                             (CATLaw                     *  iAreaLaw                  )    = 0 ;

#ifdef CATIACGMR421CAA
  //-----------------------------------------------------------------------
  //--------------- Other methods not available for all kinds of sweeps ---
  //-----------------------------------------------------------------------
  /**
 * Retrieves the moving frame parameter where profile is positionned
 * (Unspec sweep, Multi profile sweep).
 * @param iProfileRank
 * The rank (beginning at 1) of the profile.
 * @return
 * parameter value between 0. and 1.
 */
  virtual double   GetProfileParameter                    (int                           iProfileRank              = 1) = 0 ;

#endif
  //-----------------------------------------------------------------------
  //--------------- General methods               -------------------------
  //-----------------------------------------------------------------------
  // Get All Profiles : computes and gives list of profiles
  // for a parameter value between 0. and 1. along guide
  // WARNING: calling software must delete result pointer
  // and every curve belonging to result list
  /**
 * Returns the computed curves at a given section of the sweep.
 * <br>The number of the curves depends on the number of edges
 * of the initial profiles and the number of guides.
 * @param iLambda
 * The parameter <tt>0 <= iLambda <=1 </tt> indicating where the curves are computed.
 * @return
 * The list of the pointers to the created curves. If you do not want to keep
 * the curves, use the @href CATICGMContainer#Remove method. <tt>Delete</tt> the
 * list after use.
 */
  virtual CATFrFTopologicalSweep_ListPOfCATCurve* GetAllProfiles(double                  iLambda                   )    = 0;

#ifndef CATIACGMR421CAA
  //-----------------------------------------------------------------------
  //--------------- Other methods not available for all kinds of sweeps ---
  //-----------------------------------------------------------------------
  /**
 * Retrieves the moving frame parameter where profile is positionned
 * (Unspec sweep, Multi profile sweep).
 * @param iProfileRank
 * The rank (beginning at 1) of the profile.
 * @return
 * parameter value between 0. and 1.
 */
  virtual double   GetProfileParameter                    (int                           iProfileRank              = 1) = 0 ;

  //-----------------------------------------------------------------------
  //--------------- General methods               -------------------------
  //-----------------------------------------------------------------------

#endif

  /**
 * Asks for the body closure. 
 *<br> To use in cases the closed and planar profiles for example.
 */
  virtual void     SetClosureMode                         ()                                                            = 0 ;

  /**
 * Checks the input data according to the sweep case.
 * @param iExpectedCase
 * The expected sweep case to test. If <tt>0</tt>, the method tries to determine
 * the appropriate case in function of the input arguments.
 * <br>Refer to the encyclopedia for the detailed options of the different sweep cases.
 * @return
 * The case number if it is relevant, <tt>0</tt> if the the case number is 
 * irrelevant, or if the inputs do not correspond to the specified case.
 */
  virtual CATLONG32 ValidateCaseNumber                    (CATLONG32                     iExpectedCase             = 0) = 0 ;

  /**
 * Defines the vertices limiting areas to eliminate from final sweep.
 * @param iStartVertices
 * The starting vertices for each areas to eliminate.
 * @param iEndVertices
 * The ending vertices for each area to eliminate.
 * The same number of vertices must be defined for start and end. The vertices must be located
 * on the first guide, but not necessarily logically related to it.
 */
 virtual void     SetAreasToEliminate                     (CATLISTP(CATVertex)          & iStartVertices           ,
                                                           CATLISTP(CATVertex)          & iEndVertices             ) = 0;

  /**
 * Defines the untwist mode, in which every twisted area will be computed.
 * @param iUntwistMode
 * The untwist mode. If <tt>0</tt>, no twisted areas computation.
 * If <tt>1</tt>, twisted areas will be computed and available.
 * If <tt>2</tt>, twisted areas will be computed and suppressed from the resulting body.
 * @param iRecoilDistance
 * The recoil curvilinear distance on master guide to be used
 * before and after each twisted area in suppress mode.
 */
 virtual void     SetUntwistMode                          (int                            iUntwistMode             ,
                                                           double                         iRecoilDistance          = 0.0) = 0 ;

  /**
 * Retrieves the limiting parameters of the twisted areas ot the wrap areas.
 * @param oTwistBegin
 * the beginning parameters of the twisted areas.
 * @param oTwistEnd
 * the ending parameters of the twisted areas.
 */
 virtual void     GetTwistedAreas                         (CATListOfDouble               & oTwistBegin             ,
                                                           CATListOfDouble               & oTwistEnd               ) = 0;

  /**
 * Defines the wrap detection mode.
 * @param iWrapDetection
 * The wrap detection mode. If <tt>0</tt>, no wrap computation.
 * If <tt>1</tt>, wrap areas will be computed.
 * (historical behaviour: must be called if wrap detection to be done;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: wrap detection is implicitly done)
 */
 virtual void     SetWrapDetection                        (int                             iWrapDetection          ) = 0 ;

  /**
 * Defines the twist detection mode.
 * @param iTwistDetection
 * The twist detection mode. If <tt>0</tt>, no twist detection.
 * If <tt>1</tt>, twists will be detected.
 * (historical behaviour: must be called if twist detection to be done;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: twist detection is implicitly done)
 */
 virtual void     SetTwistDetection                       (int                             iTwistDetection         ) = 0 ;

  /**
 * Asks for managing C0 vertices in topological computation error as pseudo-twisted areas centers.
 * (untwist and fill twist tools available).
 */
 virtual void     SetPseudoUntwistModeForC0VerticesInError()                                                         = 0;

  /**
 * Defines the twisted or removed areas filling mode
 * @param iFillTwistMode
 * The filling mode. If <tt>0</tt>, no fill.
 * If <tt>1</tt>, areas will be filled.
 * @param iFillTwistDefaultOption
 * The filling default option for all areas.
 */
 virtual void     SetFillTwist                            (int                             iFillTwistMode          = 0,
                                                           CATFrFTopologicalSweepFill_Type iFillTwistDefaultOption = CATFrFTopologicalSweepFill_NoFill_0
                                                          )                                                          = 0;

  /**
 * Defines a smooth option for moving frame and comb extraction.
 * @param iSmoothOption
 * The smoothing option
 * <br><b>Legal values</b>: <tt>0</tt> no smoothing will be done
 * (default mode at operator creation),
 * <tt>1</tt> smoothing will be done.
 */
 virtual void     SetSmoothOption                         (int                             iSmoothOption           = 0)    = 0 ;

  /**
 * Defines the smooth angle threshold. 
 * @param iSmoothAngleThreshold
 * The threshold for smooth (in radian); any angle below this value will be smoothed
 * if smooth option has been activated by SetSmoothOption method.
 * The default value, when method is not called, is the standard geometric modeler tangency continuity tolerance
 * (the equivalent in radian of 0.5 degree).
 */
  virtual void     SetSmoothAngleThreshold                (double                           iAngleThreshold        )       = 0 ;

  /**
 * Defines clean guides option, and clean parameter values. Pointers
 * to parameter values are to be given only when corresponding parameter
 * is redefined, otherwise, standard parameter value will be used. Pointers
 * may contain addresses of local variables that will be lost after call: 
 * parameter values will be copied by this method.
 * @param iCleanOption
 * The cleaning option
 * <br><b>Legal values</b>: <tt>0</tt> no cleaning will be done
 * (default mode at operator creation),
 * <tt>1</tt> cleaning will be done.
 * @param iCleanMaxDeformation
 * The pointer to max deformation authorized.
 * @param iCleanSmallCurvesMaxLength
 * The pointer to maximum length of curves to be kept.
 * @param iCleanCurvatureThreshold
 * The pointer to the curvature threshold.
 * This threshold, between 0.0 and 1.0, must not depend on factory scale.
 */
 virtual void     SetCleanGuidesOption                    (int                             iCleanOption            = 0,
                                                           double                        * iCleanMaxDeformation    = NULL,
                                                           double                        * iCleanSmallCurvesMaxLength = NULL,
                                                           double                        * iCleanCurvatureThreshold   = NULL) = 0;

  /**
 * Defines clean profiles option, and clean parameter values. 
 * Same as for guides
 */
 virtual void     SetCleanProfilesOption                  (int                             iCleanOption               = 0,
                                                           double                        * iCleanMaxDeformation       = NULL,
                                                           double                        * iCleanSmallCurvesMaxLength = NULL,
                                                           double                        * iCleanCurvatureThreshold   = NULL) = 0;

  /**
 * Asks for topological lay down to be done internally for all guides and profiles with support
 * surfaces.
 * @param iLayDownTolerance
 * The pointer to the lay down tolerance (maximum distance between wire to be laid down
 * and its support surface).
 * (historical behaviour: must be called if internal lay down to be done;
 * upgraded behaviour if SetUpgradedDefaultSettings() has been called: internal lay down is implicitly done)
 */
 virtual void     SetLayDownRequest                       (double                        * iLayDownTolerance       = NULL) = 0 ;

protected:
  /**
   * Destructor
   */
  virtual        ~CATICGMFrFTopologicalSweep              (); // -> delete can't be called
};

#endif /* CATICGMFrFTopologicalSweep_h_ */
