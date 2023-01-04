#ifndef CATCGMDynDraftDef_h_
#define CATCGMDynDraftDef_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U1 
 */ 

#include "CATIACGMLevel.h"

/**
 * The draft type.
 * @param CATDynBasic
 * The default mode.
 * @param CATDynAutoJoint
 * Not yet implemented.
 * @param CATDynFill
 * Not yet implemented.
 */
enum CATDynDraftType
{
  CATDynBasic,
  CATDynAutoJoint,
  CATDynFill
};

#ifdef CATIACGMR214CAA
/**
 * The Both Sides Draft type.
 * @param CATCATDrivingDriven
 * The default mode.
 * @param CATIdealSolutionWithRadius
 * Not yet implemented.
 * @param CATDynDraftIndependent
 * Draft on both sides for Parting equal to Neutral
 */
enum CATDynDraftBothSidesType
{
  CATDrivingDriven,
  CATIdealSolutionWithRadius,
  CATDynDraftIndependent
};
#else
/**
* The Both Sides Draft type.
* @param CATCATDrivingDriven
* The default mode.
* @param CATIdealSolutionWithRadius
* Not yet implemented.
*/
enum CATDynDraftBothSidesType
{
  CATDrivingDriven,
  CATIdealSolutionWithRadius
};
#endif

/**
 * The draft Previsualization.
 * @param CATDynWireInPrevisualization
 * To visualize the wire representing 
 * either the intersection of the neutral element with the initial body or the reflect lines.
 * @param CATDynWirePrevisualization
 * Same as previous with the difference that wire parts lying outside the faces are shown as well.
 * @param CATDynShellPrevisualization
 * To visualize the untrimmed draft shell, based on the wire defined previously.
 */
enum CATDynDraftPrevisualization
{
  CATDynWireInPrevisualization,
  CATDynWirePrevisualization,
  CATDynShellPrevisualization
};

/**
 * @nodoc
 */
enum CATDynDraftStepDraftMode
{
  CATDynDraftPerpendicular,
  CATDynDraftTapered
};

#endif /* CATCGMDynDraftDef_h_ */
