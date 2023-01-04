#ifndef CATFrFTopologicalSweep_h_
#define CATFrFTopologicalSweep_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
* @CAA2Level L1
* @CAA2Usage U1
*/

#define CATFrFTopologicalSweep_ListPOfCATCurve CATLISTP(CATCurve)

/**
 * The type of sweep.
 * @param CATFrFTopologicalSweepType_Std
 * The unspec sweep (one guide, one profile).
 * @param CATFrFTopologicalSweepType_Segment
 * The segment sweep.
 * @param CATFrFTopologicalSweepType_Circle
 * The circle sweep.
 * @param CATFrFTopologicalSweepType_Multi
 * The multi-profile sweep.
 * @param CATFrFTopologicalSweepType_Conic
 * The conic sweep (each section is a conic; conic type may differ from
 * one section to another).
 * @nodoc
 * Internal use.
 * @param CATFrFTopologicalSweepType_Interpolation
 * The interpolation sweep (each section is computed by interpolation
 * between guides points).
 * @param CATFrFTopologicalSweepType_Blend
 * The blend sweep (each section is a blend section computed
 * between 2 guides points).
 */
typedef enum {
           CATFrFTopologicalSweepType_Std=0,
           CATFrFTopologicalSweepType_Segment,
           CATFrFTopologicalSweepType_Circle,
           CATFrFTopologicalSweepType_Multi,
           CATFrFTopologicalSweepType_Conic,
           CATFrFTopologicalSweepType_Interpolation,
           CATFrFTopologicalSweepType_Blend
          } CATFrFTopologicalSweepType;

/**
 * @nodoc
 * Internal use.
 */
typedef enum {CATFrFTopologicalSweepSegment_Unknown = 0 ,
              CATFrFTopologicalSweepSegment_Case1   = 1}
              CATFrFTopologicalSweepSegmentCase ;

/**
 * @nodoc
 * Internal use.
 */
typedef enum {CATFrFTopologicalSweepCircle_Unknown = 0 ,
              CATFrFTopologicalSweepCircle_Case1   = 1}
              CATFrFTopologicalSweepCircleCase ;
/**
 * @nodoc
 * Internal use.
 */
typedef enum {CATFrFTopologicalSweepConic_Unknown = 0 ,
              CATFrFTopologicalSweepConic_Case1   = 1}
              CATFrFTopologicalSweepConicCase ;
/**
 * @nodoc
 * Internal use.
 */
typedef enum {CATFrFTopologicalSweepInterpolation_Unknown = 0 ,
              CATFrFTopologicalSweepInterpolation_Case1   = 1}
              CATFrFTopologicalSweepInterpolationCase ;
/**
 * @nodoc
 * Internal use.
 */
typedef enum {CATFrFTopologicalSweepBlend_Unknown = 0 ,
              CATFrFTopologicalSweepBlend_Case1   = 1}
              CATFrFTopologicalSweepBlendCase ;
/**
 * @nodoc
 * Debug modes: 
 */
typedef enum {CATFrFTopologicalSweepDebug_Reset = 0,
              CATFrFTopologicalSweepDebug_ResetFactory,
              CATFrFTopologicalSweepDebug_ExplicitFactory,
              CATFrFTopologicalSweepDebug_RunGeometricOperator,
              // AssemblyMode: assemblage de surfaces sans 
              // resolution de topologie
              CATFrFTopologicalSweepDebug_RunInAssemblyMode,
              CATFrFTopologicalSweepDebug_RunInStandardMode,
              CATFrFTopologicalSweepDebug_ActiveCanonicSurfaces,
              CATFrFTopologicalSweepDebug_InactiveCanonicSurfaces,
              CATFrFTopologicalSweepDebug_KeepIntermediateGeometry,
              CATFrFTopologicalSweepDebug_DeleteIntermediateGeometry,
              CATFrFTopologicalSweepDebug_ImmediateFullDumpOnStandardOutput,
              CATFrFTopologicalSweepDebug_ImmediateLightDumpOnStandardOutput,
              CATFrFTopologicalSweepDebug_RunWithoutExtrapolationMode
             }
              CATFrFTopologicalSweepDebug_Mode ;

/**
 * @nodoc
 * Data access modes: (very restricted use)
 */
typedef enum { CATFrFTopologicalSweepDataAction_SetCGMLevelForImplicitSpine =0,
               CATFrFTopologicalSweepDataAction_GetTopologicalSweepAdvancedParams,
               CATFrFTopologicalSweepDataAction_SetTopologicalSweepAdvancedParams,
               CATFrFTopologicalSweepDataAction_SetDebugParam1,
               CATFrFTopologicalSweepDataAction_GetDebugParam1,
               CATFrFTopologicalSweepDataAction_SetDebugParam2,
               CATFrFTopologicalSweepDataAction_GetDebugParam2,
               CATFrFTopologicalSweepDataAction_SetDebugParam3,
               CATFrFTopologicalSweepDataAction_GetDebugParam3,
               CATFrFTopologicalSweepDataAction_SetDebugParam4,
               CATFrFTopologicalSweepDataAction_GetDebugParam4
             }
              CATFrFTopologicalSweepDataAction ;

/**
* @nodoc
*  Internal behaviour modes:
*/
typedef enum {CATFrFTopologicalSweepBehaviour_Reset = 0,
              CATFrFTopologicalSweepBehaviour_ResetFrameType,
              CATFrFTopologicalSweepBehaviour_GetFrameType,
              CATFrFTopologicalSweepBehaviour_MovingFrameType,
              CATFrFTopologicalSweepBehaviour_FinalFrameType,
              CATFrFTopologicalSweepBehaviour_ResetHomogenization,
              CATFrFTopologicalSweepBehaviour_ActiveHomogenization,
              CATFrFTopologicalSweepBehaviour_InactiveHomogenization,
              // Note: Profiles Homogenization is active by default,
              // in standard mode
              CATFrFTopologicalSweepBehaviour_ActiveProfilesHomogenization,
              CATFrFTopologicalSweepBehaviour_InactiveProfilesHomogenization,
              // standard coupling is by curvilinear length
              CATFrFTopologicalSweepBehaviour_StandardCouplingProfilesHomogenization,
              // D1 coupling means coupling, in each domain, vertices of G0 and
              // not G1 continuity (each domain being limited by 2 guides if any);
               CATFrFTopologicalSweepBehaviour_D1CouplingProfilesHomogenization,
              // D1 and then D2 coupling means that after D1 coupling, 
              // D2 coupling is done (vertices of G1 and not G2 continuity) in
              // each domain defined by D1 coupling
              CATFrFTopologicalSweepBehaviour_D1AndThenD2CouplingProfilesHomogenization,
              // Vertex coupling means coupling in each domain limited
              // by 2 guides, vertex number i of first profile with 
              // vertex number i of each profile
              CATFrFTopologicalSweepBehaviour_VertexCouplingProfilesHomogenization,
              CATFrFTopologicalSweepBehaviour_ActiveGuidesHomogenization,
              CATFrFTopologicalSweepBehaviour_InactiveGuidesHomogenization,
              CATFrFTopologicalSweepBehaviour_InactiveCheckOperands,
              CATFrFTopologicalSweepBehaviour_ActiveBasicCheckOperands,
              CATFrFTopologicalSweepBehaviour_ActiveAdvancedCheckOperands,
              CATFrFTopologicalSweepBehaviour_ActiveCompleteCheckOperands,// Basic + Advanced
              // Detection of twisted surfaces
              // Note: Twist detection is inactive by default,
              // in standard mode
              CATFrFTopologicalSweepBehaviour_ResetTwistDetection,
              CATFrFTopologicalSweepBehaviour_ActiveTwistDetection,
              CATFrFTopologicalSweepBehaviour_InactiveTwistDetection,
              // Relimitation by profiles already done on spine
              CATFrFTopologicalSweepBehaviour_AssumeSpineAlreadyRelimitedByProfiles,
              // GetMovingFrame() behaviour
              CATFrFTopologicalSweepBehaviour_ResetMovingFrameMode,
              CATFrFTopologicalSweepBehaviour_GetMovingFrameMode,
              CATFrFTopologicalSweepBehaviour_FinalMovingFrameMode,
              CATFrFTopologicalSweepBehaviour_UltimateMovingFrameMode,
              CATFrFTopologicalSweepBehaviour_InitialMovingFrameMode,
              // InternalLayDown behaviour
              CATFrFTopologicalSweepBehaviour_ActiveInternalLayDownDuringClean,
              CATFrFTopologicalSweepBehaviour_ActiveExplicitInternalLayDown,
              //
              CATFrFTopologicalSweepBehaviour_GimmeAnyResult,
              CATFrFTopologicalSweepBehaviour_AddC0VerticesInErrorInTwistedAreas,
              CATFrFTopologicalSweepBehaviour_ForcedProtoBoundarySurface
              }
              CATFrFTopologicalSweepBehaviour_Mode ;
/**
 * Automatic coupling types.
 * @param CATFrFTopologicalSweepAutomaticCoupling_Standard
 * Standard coupling: by curvilinear length.
 * @param CATFrFTopologicalSweepAutomaticCoupling_D1
 * D1 coupling: in each domain, coupling of the vertices of G0 and
 * not G1 continuity (each domain being limited by 2 guides if any).
 * @param CATFrFTopologicalSweepAutomaticCoupling_D1AndThenD2
 * D1 and then D2 coupling: after a D1 coupling, the
 * D2 coupling is done (vertices of G1 and not G2 continuity) in
 * each domain defined by the D1 coupling.
 * @param CATFrFTopologicalSweepAutomaticCoupling_VertexCoupling
 * Vertex coupling: coupling in each domain limited
 * by 2 guides, the vertex number i of the first profile with the 
 * vertex number i of each profile.
 */
typedef enum {  CATFrFTopologicalSweepAutomaticCoupling_Standard = 0,
                CATFrFTopologicalSweepAutomaticCoupling_D1,
                CATFrFTopologicalSweepAutomaticCoupling_D1AndThenD2,
                CATFrFTopologicalSweepAutomaticCoupling_VertexCoupling}
                CATFrFTopologicalSweepAutomaticCoupling_Type ;
/**
 * Moving Frame types:
 */
typedef enum { CATFrFTopologicalSweepMF_Default = 0,
               CATFrFTopologicalSweepMF_ParallelToPlane,
               CATFrFTopologicalSweepMF_Ortho,
               CATFrFTopologicalSweepMF_PseudoOrtho}
               CATFrFTopologicalSweepMF_Type ;

/**
 * The spine type.
 * @param CATFrFTopologicalSweepSpine_Explicit
 * The spine is explicitely given.
 * @param CATFrFTopologicalSweepSpine_Implicit
 * The spine is automatically computed in case of multi profiles sweep. 
 */
typedef enum { CATFrFTopologicalSweepSpine_Explicit = 0,
               CATFrFTopologicalSweepSpine_Implicit}
               CATFrFTopologicalSweepSpine_Type ;

/**
 * The continuity type.
 * @param CATFrFTopologicalSweepContinuity_C0
 * The point continuity (C0).
 * @param CATFrFTopologicalSweepContinuity_G1
 * The tangent continuity (G1).
 * @param CATFrFTopologicalSweepContinuity_G2
 * The curvature continuity (G2) (NOT TO BE USED).
 */
typedef enum { CATFrFTopologicalSweepContinuity_C0 = 0,
               CATFrFTopologicalSweepContinuity_G1 = 1,
               CATFrFTopologicalSweepContinuity_G2 = 2}
               CATFrFTopologicalSweepContinuity_Type ;

/**
 * The relative orientation.
 * @param CATFrFTopologicalSweepOrientation_Positive
 * Same orientation.
 * @param CATFrFTopologicalSweepOrientation_Negative
 * Opposite orientation.
 */
typedef enum { CATFrFTopologicalSweepOrientation_Positive =  1,
               CATFrFTopologicalSweepOrientation_Negative = -1,
               CATFrFTopologicalSweepOrientation_Unknown  =  0,
             }
               CATFrFTopologicalSweepOrientation_Type ;
/**
 * The relimitations on the extremity profiles.
 * @param CATFrFTopologicalSweepRelimitation_Off
 * The sweep is not relimited on the extremity profiles.
 * @param CATFrFTopologicalSweepRelimitation_OnLimitProfiles
 * The sweep is not relimited on the extremity profiles.
 * @param CATFrFTopologicalSweepRelimitation_OnFirstProfile
 * The sweep is relimited only on the first input profile. 
 * @param CATFrFTopologicalSweepRelimitation_OnLastProfile
 * The sweep is relimited only on the last input profile.
 */
typedef enum {    CATFrFTopologicalSweepRelimitation_Off = 0,
               CATFrFTopologicalSweepRelimitation_OnLimitProfiles,
               CATFrFTopologicalSweepRelimitation_OnFirstProfile,
               CATFrFTopologicalSweepRelimitation_OnLastProfile }
               CATFrFTopologicalSweepRelimitation_Type ;
/**
 * @nodoc
 * The deviation computation.
 */
typedef enum { CATFrFTopologicalSweepDeviation_Max = 0,
               CATFrFTopologicalSweepDeviation_MaxOnGuides,
               CATFrFTopologicalSweepDeviation_MaxOnProfiles,
               CATFrFTopologicalSweepDeviation_OnOneGuide,
               CATFrFTopologicalSweepDeviation_OnOneProfile}
               CATFrFTopologicalSweepDeviation_Type ;

/**
 * The fill options associated to one or all filling areas. These options allow management of limit guiding curves
 * computation on sides of area to fill.
 * Limit curves may be spline curves, or similar curves (similar to main sweep master guide). 
 * Automatic curve means that limit curves are computed on sides
 * of area to fill according to best algorithm choice (it depends on main sweep type, on length law values, ...).
 * Force curve means that user asks for guiding curves computation on both sides, if possible, even though
 * standard algorithm would rather use no guide or only one guide.
 * No limit curve means that no limit curve will be conputed.
 */
typedef enum { CATFrFTopologicalSweepFill_NoFill_0                = 0,
               CATFrFTopologicalSweepFill_AutomaticSplineCurve_1  = 1,
               CATFrFTopologicalSweepFill_AutomaticSimilarCurve_2 = 2,
               CATFrFTopologicalSweepFill_ForceSplineCurve_3      = 3,
               CATFrFTopologicalSweepFill_ForceSimilarCurve_4     = 4,
               CATFrFTopologicalSweepFill_NoLimitCurve_5          = 5
             }
               CATFrFTopologicalSweepFill_Type;

/**
 * @nodoc
 * Internal use.
 * The untwist options.
 */

typedef enum {CATFrFTopologicalSweep_Untwist_0None                = 0,
              CATFrFTopologicalSweep_Untwist_1Compute             = 1,
              CATFrFTopologicalSweep_Untwist_2Reduction           = 2,
              CATFrFTopologicalSweep_Untwist_3AntiReduction       = 3,
              CATFrFTopologicalSweep_Untwist_4ReductionAndControl = 4
             } CATFrFTopologicalSweep_UntwistType ;

/**
 * The downgrade setting queries.
 * @param CATFrFTopologicalDowngradeSetting_NoLayDownRequest
 * There is no internal laywon implicit request.
 * @param CATFrFTopologicalDowngradeSetting_NoAngularLawsInDegree
 * There is no implicit degree angular law for circular sweeps.
 */
typedef enum { CATFrFTopologicalDowngradeSetting_NoLayDownRequest      = 1,
               CATFrFTopologicalDowngradeSetting_NoAngularLawsInDegree = 2
             }
               CATFrFTopologicalDowngradeSetting_Type ;


#endif /* CATFrFTopologicalSweep_h_ */
