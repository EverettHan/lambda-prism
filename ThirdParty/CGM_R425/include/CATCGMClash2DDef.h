//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2014
//=============================================================================
//
// CATClash2D:
//    Header file for the CATClash2D operator.
//
//=============================================================================
// Usage notes:
//=============================================================================
// 17/03/14 : XMH : Creation
// 02/07/14 : XMH : AddBody, Caller body id
// 25/07/14 : XMH : Implement 2D transform
// 10/07/15 : XMH : Interface changes to allow instances of bodies
//                  caller body id compulsory, inquiry using ID rather than body pointer
// 26/08/15 : XMH : Remove deprecated methods.
// 10/01/17 : F1Z : Region option review.
//=============================================================================
#ifndef CATCGMClash2DDef_H
#define CATCGMClash2DDef_H
namespace CATCGMClash2DDef_H
   {

  // CATCGMClash2DClassification describes how a pair of bodies clash
  // Warning: Since the enum is captured in the replay file DO NOT change the order or values of the items.
  /** Clash classification of a pair of bodies.
  * @param <tt>CATClash2D_Unknown</tt>
  * The classification is unknown.
  * @param <tt>CATClash2D_Error</tt>
  * The classification is not set as the operator encountered an error.
  * @param <tt>CATClash2D_NoClash</tt>
  * The bodies do not clash.
  * @param <tt>CATClash2D_Clash</tt>
  * The bodies clash in a region of penetration.
  * @param <tt>CATClash2D_Clash_Abut</tt>
  * The bodies clash along an edge of penetration.
  * @param <tt>CATClash2D_Contained</tt>
  * One body is entirely contained in the other body, and the borders do not touch.
  * @param <tt>CATClash2D_Contained_Abut</tt>
  * One body is entirely contained in the other body, and there is contact at a border.
  * @param <tt>CATClash2D_Clash_MaxPenDepthExceeded</tt>
  * The operator terminated early as the maximum penetration depth set by the user has been exceeded.
  * Only some clashes have been computed so the result is incomplete.
  */
   typedef enum
      {
      CATCGMClash2D_Unknown = -2,
      CATCGMClash2D_Error,                     // = -1
      CATCGMClash2D_NoClash,                   // =  0
      CATCGMClash2D_Clash,                     // =  1
      CATCGMClash2D_Clash_Abut,                // =  2
      CATCGMClash2D_Contained,                 // =  3
      CATCGMClash2D_Contained_Abut,            // =  4
      CATCGMClash2D_Clash_MaxPenDepthExceeded  // =  5
      } CATCGMClash2DClassification;

      // CATClash2DTransformMode describes how a transformation should be applied to a body
      // Warning: Since the enum is captured in the replay file DO NOT change the order or values of the items.
      /** Clash transformation mode.
      * @param <tt>CATClash2D_TransformReplace</tt>
      * The transform should replace the transform currently applied to the body.
      * @param <tt>CATClash2D_TransformConcatenate</tt>
      * The transform should be concatentated with the transform currently applied to the body.
      */
   typedef enum
      {
      CATCGMClash2D_TransformReplace     = 0,
      CATCGMClash2D_TransformConcatenate = 1
      } CATCGMClash2DTransformMode;

   }
#endif
