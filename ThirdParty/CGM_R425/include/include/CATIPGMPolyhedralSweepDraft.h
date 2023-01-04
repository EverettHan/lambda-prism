#ifndef CATIPGMPolyhedralSweepDraft_h_
#define CATIPGMPolyhedralSweepDraft_h_

// COPYRIGHT DASSAULT SYSTEMES 2018

#include "CATGMOperatorsInterfaces.h"
#include "CATIPGMPolyTopOperator.h"
#include "CATErrorDef.h"

#include "ListPOfCATVertex.h"
#include "CATListOfDouble.h"

class CATBody;
class CATGeoFactory;
class CATTopData;
class CATVertex;
class CATMathPlane;
class CATMathDirection;

extern ExportedByCATGMOperatorsInterfaces IID IID_CATIPGMPolyhedralSweepDraft;

/**
* Class defining an operator that creates a polyhedral sweep surface from a wire body composed of polycurves
* <ul>
*     <li> A <tt>CATIPGMPolyhedralSweepDraft</tt> operator is created with the <tt>CATPGMCreatePolyhedralSweepDraft</tt> global function.
*     <li> It is the user's responsibility to release the operator after it has been used.
*     <li> The results are retrieved by the <tt>Get</tt> methods.
* </ul>
*/

class ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralSweepDraft: public CATIPGMPolyTopOperator
{
public:

  /**
   * Constructor
   */
  CATIPGMPolyhedralSweepDraft();

  //=============================================================================
  // Profile Settings
  //=============================================================================
    
  //=============================================================================
  // **** 2 complementary ways to define the shape of the SweepDraft ****
  //
  // 1. Define a global profile (constant SweepDraft) and/or local profiles (variable SweepDraft) at specified locations.
  // In this case, all the profiles have to contain the same number of linear segments to define as many variable strips,
  // and the sign of all the angles associated to one strip has to be constant ...
  // ... to define the side (left or right) of the strip according to the wire orientation and the draft direction
  // No way in this mode to associate any offset plane as target for any strip.
  //
  // 2. Define successive strips (historic definition for constant angular SweepDraft only)
  // This way allows to define 2 modes for each strip : "by Length" or "Up to" an offset plane from the original one.
  // Strips can be defined in addition to global and/or local profiles previously defined according to 1.
  //=============================================================================

    
  // -----------------------------------------------------------------------------------------
  // 1. "Profile by profile" definition (compliant with both constant and variable SweepDraft)
  // -----------------------------------------------------------------------------------------
  
  /**
  * Defines (in one shot) the complete multi-linear profile as a succession of couples (angle + length)
  * This method is compliant with both constructors, the reference plane defining a pulling direction from its own normal.
  * @param iSegmentRadianAngles
  * For each strip generated from a linear segment of this profile, 
  * the sign of the associated angle specifies one single side according to the wire orientation and the draft direction :
  * on the left (positive angle) or on the right (negative angle)
  * all values in the range [ -CATPI, CATPI ] will be accepted
  * @param iSegmentLengths
  * list of unsigned lenghts associated to the segments of the profile, parallel to iSegmentRadianAngles
  * This setting doesn't allow to specify any offset plane as target.
  * Returns E_FAIL if the profile is badly defined (different sizes or nul size)
  */
  virtual HRESULT SetGlobalProfile(const CATListOfDouble & iSegmentRadianAngles, const CATListOfDouble & iSegmentLengths) = 0;

  /**
  * Sets the specific body (different from the input wire and maybe exact) containing the vertices on which local profiles are defined
  * @param iSpecBody
  * Body containing vertices with local profiles, if those vertices don't belong to the input wire
  * If this body is not set, the operator won't take into account local profiles defined on vertices which don't belong to the input wire
  * For variable SweepDraft only (no sense for constant SweepDraft defined by SetGlobalProfile)
  */
  virtual void SetBodyOfVerticesWithLocalProfiles(CATBody * iSpecBody) = 0;

  /**
  * Associates a local multi-linear profile as a succession of couples (angle + length) to a specific Vertex as location on the input wire
  * This method is compliant with both constructors, the reference plane defining a pulling direction from its own normal.
  * @param iSpecVertex
  * The input vertex (may be exact or PH) is supposed to be numerically lying on the input wire.
  * @param iSegmentRadianAngles
  * For each strip generated from a linear segment of this profile, 
  * the sign of the associated angle specifies one single side according to the wire orientation and the draft direction :
  * on the left (positive angle) or on the right (negative angle)
  * all values in the range [ -CATPI, CATPI ] will be accepted
  * Keep in mind that all the local profiles have to contain the same number of linear segments to define as many strips,
  * and the sign of all the angles associated to one strip has to be constant ...
  * ... to define the side (left or right) according to the wire orientation and the draft direction
  * @param iSegmentLengths
  * list of unsigned lenghts associated to the segments of the profile, parallel to iSegmentRadianAngles
  * This setting doesn't allow to specify any offset plane as target.
  * Returns E_FAIL if the profile is badly defined (nul vertex, different sizes or nul size)
  */
  virtual HRESULT SetLocalProfileAtVertex(CATVertex * iSpecVertex, const CATListOfDouble & iSegmentRadianAngles, const CATListOfDouble & iSegmentLengths) = 0;

  /**
  * Associates a common local profile to a set of vertices, as locations on the input wire
  * This API is equivalent to call SetLocalProfileAtVertex() API for each vertex of the input list.
  * Returns E_FAIL if the profile is badly defined (nul vertex, different sizes or nul size)
  */
  virtual HRESULT SetLocalProfileAtVertices(const ListPOfCATVertex & iSpecVertices, const CATListOfDouble & iSegmentRadianAngles, const CATListOfDouble & iSegmentLengths) = 0;


  // -------------------------------------------------------------------------------------------
  // 2. "Strip by strip" definition (constant angular parts of SweepDraft)
  // -------------------------------------------------------------------------------------------

  /**
  * Defines a new constant strip to sweep
  * This method is compliant with both constructors, the reference plane defining a pulling direction from its own normal
  * @param iWireSide
  * The side (CATSideLeft / CATSideRight) on which the ruled strip has to be generated, according to the wire orientation and the draft direction
  * @param iRadianAngle
  * The radian angle between the opposite direction ("draft" convention) and the strip to generate :
  * all values in the range [ 0., CATPI ] will be accepted
  * @param iStripLength
  * The constant positive Length of the future ruled strip from the previous wire
  * This value has to be greater than the model tolerant resolution (0.1 mm for NormalRange), else returns 0.
  * @return
  * The integer value associated to the new strip definition, equals to the number of recorded strips including this one.
  * If the strip is not correctly defined (unknown or full side, angle out of range, length smaller than the tolerant resolution ...), 
  * or if this method is called after Run(), then it returns 0
  */
  virtual int AddStripWithLength(CATSide iWireSide, double iRadianAngle, double iStripLength) = 0;

  /**
  * Defines a new strip to sweep, up to a target planar surface
  * This method requires to have instanciated the operator with a reference plane, else returns 0.
  * PLEASE NOTE that a target plane intersecting the guide (input wire or previous strip boundary if any) leads automatically to make the computation fail !
  * @param iWireSide
  * The side (CATSideLeft / CATSideRight) on which the ruled strip has to be generated, according to the wire orientation and the input direction
  * @param iRadianAngle
  * The radian angle between the opposite direction ("draft" convention) and the strip to generate :
  * all values in the range [ 0., CATPI] will be accepted, except for values between [ CATPIBY2 - CATTopSharpAngle, CATPIBY2 + CATTopSharpAngle]
  * @param iPlanarOffsetValue
  * The optional offset value to apply to the reference input plane
  * @return
  * The integer value associated to the new strip definition, equals to the number of recorded strips including this one.
  * If the strip is not correctly defined (no reference plane, unknown or full side, angle out of range...), 
  * or if this method is called after Run(), then it returns 0
  */
  virtual int AddStripUpToPlane(CATSide iWireSide, double iRadianAngle, double iPlanarOffsetValue=0.) = 0;

    
  //=============================================================================
  // Other Settings
  //=============================================================================

  /** 
  * Enables the optional mode forcing the successive offset directions to be in common planes from the guide vertices,
  * in spite of variational angles and offset values due to different local profiles.
  * The default behavior (if this option is disabled) leads to create edges following the natural angular deviation due to the variable offset/angle values
  * This mode impacts the shape of the result surface between the guide and its offset,
  * and leads to create co-planar edges from profiles applied on guide vertices.
  */
  virtual void EnablePlanarProfileBehavior() = 0;
  
  /** 
  * Sets the mode to drive the offset behaviour to compute the boundary opposite to the guide wire,
  * impacting the shape (smooth or sharp) of the result surface between the guide and its offset.
  * This mode impacts only the convex (resp. concave) sharp vertices in case of outwards (resp. inwards) Offset value
  *   TRUE (default) leads to create a circular arc (according to the Minkowsky offset specification),
  *   FALSE leads to create a sharp vertex computed by extrapolation (in this case, the Offset value is not respected).
  */
  virtual void SetRoundedMode(CATBoolean iRoundedMode) = 0;
  
  /**
  * Extrapolates the Sweep Result from the free boundary of the last strip, beyond a Target Body.
  * Does nothing if this boundary is beyond the target body according to the last sweep draft direction 
  * The default behavior leads to extrapolate according to the last sweep angle if it's not orthogonal to the reference direction
  * @param iOptimizedMode
  * Advanced analysis leading to associate a local length to each vertex only if the extrapolation is really necessary
  * The activation of this option increases the CPU of the computation, but avoids to generate useless additional strip of Sweep,
  * and so may dicrease the CPU time in the following operations.
  */
  virtual void EnableExtrapolationBeyondTarget(CATBody * iTargetBody, CATBoolean iOptimizedMode=FALSE) = 0;

  /** 
  * Enables the optional mode starting the ribbon generation from an offset of the guide wire
  * @param iStartingRankInProfile
  * Position of the segment starting the ribbon in the profile definition
  * if 1 (default internal value), the ribbon generation starts at the guide wire
  * else, (iStartingSegmentPosition - 1) successive offset will be applied from the guide to compute the wire starting the sweep ribbon
  */
  virtual void StartRibbonFromRank(int iStartingRankInProfile) = 0;
  
  /** 
  * Enables the option completing the open ribbon to close it into a volume
  * This option is not compliant with any extrapolation request (see EnableExtrapolationBeyondTarget)
  * This option supposes that at least 2 segments are defined in the profile in order to generate at least 2 strips
  * If the missing strip (connecting the guide to the last boundary) intersects the ribbon, an error will be thrown.
  */
  virtual void EnableVolumeClosure() = 0;


  //=============================================================================
  // Get additional information after Run
  //=============================================================================
  /**
  * Retrieves the output boundary edges that are on the ribbon’s side corresponding to the input wire body.
  * @param oBoundaryEdges
  * The list of edges retrieved from the result boundary
  * @param oEdgesOriVsInputWire
  * The list of relative orientations of edges versus the input wire body orientation 
  * @param ioSweepSideVsOrientedEdges
  * optional pointer to get the side (left or right) of the sweep surface seen from the border edges according to their associated orientations
  */
  virtual void GetOutputReferenceBoundaryEdges(
    CATLISTP(CATCell) &oBoundaryEdges,
    CATListOfInt &oEdgesOriVsInputWire,
    CATSide *ioSweepSideVsOrientedEdges = NULL) = 0;

  /**
  * Retrieves the output boundary edges that are on the ribbon’s opposite side relatively to the input wire body.
  * @param oBoundaryEdges
  * The list of edges retrieved from the result boundary
  * @param oEdgesOriVsInputWire
  * The list of relative orientations of edges versus the input wire body orientation 
  * @param ioSweepSideVsOrientedEdges
  * optional pointer to get the side (left or right) of the sweep surface seen from the border edges according to their associated orientations
  */
  virtual void GetOutputOppositeBoundaryEdges(
    CATLISTP(CATCell) &oBoundaryEdges,
    CATListOfInt &oEdgesOriVsInputWire,
    CATSide *ioSweepSideVsOrientedEdges = NULL) = 0;

  /**
  * Retrieves the output boundary edges that are on the ribbon’s side corresponding to an input wire vertex.
  * All the returned information will be empty/null if the vertex is not an open wire extremity
  * @param oBoundaryEdges
  * The list of edges retrieved from the result boundary
  * @param oEdgesOriFromRefVertex
  * The list of relative orientations of edges coming from the input wire vertex
  * @param ioReferenceBorderVertex
  * optional pointer to retrieve the result border vertex corresponding to the input wire vertex
  * @param ioOppositeBorderVertex
  * optional pointer to retrieve the result border vertex opposite to the input wire vertex
  * @param ioSweepSideVsOrientedEdges
  * optional pointer to get the side (left or right) of the sweep surface seen from the border edges according to their associated orientations
  */
  virtual void GetOutputBoundaryEdgesFromInputVertex(
    CATVertex *iInputWireVertex,
    CATLISTP(CATCell) &oBoundaryEdges,
    CATListOfInt &oEdgesOriFromInputVertex,
    CATVertex **ioReferenceBorderVertex = NULL,
    CATVertex **ioOppositeBorderVertex = NULL,
    CATSide *ioSweepSideVsOrientedEdges = NULL) = 0;

  /**
  * Retrieves the output faces contained in the extrapolated part of the Sweep result body.
  * @param oExtrapolationFaces
  * The list of faces retrieved from the additional part of the Sweep result body
  * This list may be empty if the extrapolation has not been requested or was unnecessary
  * @return
  * The extrapolation diagnosis : 
  * S_OK if the extrapolation beyong target has been enabled without failure (even if the list is empty)
  * S_FALSE if the extrapolation has not been requested or has not been computed (if the computation failed before)
  * E_FAIL if the extrapolation was requested and necessary but failed
  */
  virtual HRESULT GetOutputExtrapolationFaces(
    CATLISTP(CATCell) &oExtrapolationFaces) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATIPGMPolyhedralSweepDraft(); // -> delete can't be called
};

/**
 * Creates a CATIPGMPolyhedralSweepDraft operator with a direction
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iWireBody
 * The pointer to the 1D body to guide the sweep
 * @param iDraftDirection
 * The mathematical direction to apply the draft angle (beginning from the opposite direction)
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralSweepDraft *CATPGMCreatePolyhedralSweepDraft(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  const CATMathDirection &iDraftDirection);

/**
 * Creates a CATIPGMPolyhedralSweepDraft operator with a reference plane
 * @param iFactory
 * The factory of the geometry. 
 * @param iTopData
 * The pointer to the data defining the software configuration and the journal. If the journal inside <tt>iTopData</tt> 
 * is <tt>NULL</tt>, it is not filled. 
 * @param iWireBody
 * The pointer to the 1D body to guide the sweep
 * @param iRefPlane
 * The mathematical plane giving the normal direction as reference to apply the angle (beginning from the opposite direction)
 * and defining the original plane to offset to limit strips
 * @return [out, IUnknown#Release]
 * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
 */
ExportedByCATGMOperatorsInterfaces CATIPGMPolyhedralSweepDraft *CATPGMCreatePolyhedralSweepDraft(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iWireBody,
  const CATMathPlane &iRefPlane);

#endif /* CATIPGMPolyhedralSweepDraft_h_ */
