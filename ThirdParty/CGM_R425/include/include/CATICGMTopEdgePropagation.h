#ifndef CATICGMTopEdgePropagation_h_
#define CATICGMTopEdgePropagation_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

/**
 * @CAA2Level L1
 * @CAA2Usage U3
*/

#include "CATGMModelInterfaces.h"
#include "CATICGMTopOperator.h"
#include "CATGeoFactory.h"
#include "CATTopEdgePropagationDiagnosis.h"
#include "CATTopDefine.h"

class CATEdge;
class CATFace;

extern ExportedByCATGMModelInterfaces IID IID_CATICGMTopEdgePropagation;

/**
 * Class representing the topological operator which performs an edge propagation on a body.
 * <ul>
 * <li>Create it with the CATCGMCreateTopEdgePropagation global function.
 * <li>Tune it with appropriate options, using the Setxxx methods. 
 * <li>Run it ( only one time ).
 * <li>Get the resulting body with the GetResult method. This body is made of a single wire which 
 * is the result of the propagation. If you do not want to keep this resulting body, 
 * use the @href CATICGMContainer#Remove method to remove it from the 
 * geometric factory, after the operator deletion.
 * <li>Optionally get the two propagation diagnoses with the GetDiagnoses method.
 * <li>Release the operator with the <tt>Release</tt> method. 
 * </ul>
*/
class ExportedByCATGMModelInterfaces CATICGMTopEdgePropagation: public CATICGMTopOperator
{
public:
  /**
   * Constructor
   */
  CATICGMTopEdgePropagation();

  /**
  * Defines the face to be used as a reference for the orientation of the resulting wire.
  * <br>This face must be bounded by the initial edge.
  * @param iReferenceFace
  * The reference face for the wire orientation.
  * <ul>
  * <li>In case the initial edge is a shell internal edge, this service is mandatory
  * for the result orientation.
  * <li>In case the initial edge is at the boundary of a single shell, 
  * this single shell is used as a reference face and this service is useless.
  * <li>In case the initial edge is at the boundary of several shells (non manifold
  * situation), this service is mandatory to define the result orientation and specify the
  * shell on which the propagation is carried out.
  * </ul>
  * <br>This service is meaningless if the input body contains wires.
  * @param iReferenceOrientation
  * <ul>
  * <li>If CATOrientationPositive , the reference orientation is the orientation of the reference face in the shell.
  * <li>If CATOrientationNegative , the reference orientation is the inverse of the orientation of the reference face in the shell.
  * </ul>
  */
  virtual void SetReferenceFace(
    CATFace *iReferenceFace,
    CATOrientation iReferenceOrientation = CATOrientationPositive) = 0;

  /** 
  * Defines the boundary propagation mode on shell.
  * <br>by default this mode is off.
  * @param iIsBoundaryModeActive
  * Specifies whether the propagation is restricted to the boundary of the shell.
  * <br><b>Legal values</b>: <tt>TRUE</tt> or, <tt>FALSE</tt>.
  * <br>In case this mode is on, the initial edge has to belong to the boundary
  * of the shell.
  * <br>This service is meaningless if the input body contains wires.
  */
  virtual void SetBoundaryMode(const CATBoolean iIsBoundaryModeActive) = 0;

  /**
  * Defines the continuity propagation mode.
  * @param iContinuity
  * <br><b>Legal values</b>:
  * <dl>
  * <dt><tt>CatC0</tt></dt><dd> Point continuity.
  * <dt><tt>CatC1</tt></dt><dd> Point and tangency continuity.
  * <dt><tt>CatC2</tt></dt><dd> Point, tangency and curvature continuity.
  * </dl>
  * <br>In case of point continuity and when boundary mode is off, propagation occurs
  * only around the reference face.
  * <br>The continuity evaluation does not take into account the junction edge
  * (continuity is evaluated on their neighbor).
  */
  virtual void SetContinuityMode(const CATResolutionType iContinuity) = 0;

  /**
  * Defines the tolerance propagation value for a continuity level.
  * @param iContinuity
  * Defines the continuity level.
  * <dl>
  * <dt><tt>CatC0</tt></dt><dd> Point tolerance in model unit.
  * <br> Value is restricted to interval [ 0.001 , 0.1 ] with 0.001 as default.
  * <dt><tt>CatC1</tt></dt><dd> Tangency tolerance in radians.
  * <br> Value is restricted to interval [ 0.00872665 radian , 0.0872665 ] with 0.00872665 as default. 
  * <br>Equivalent value in degree are [ 0.5 degree , 5. degree ].
  * <dt><tt>CatC2</tt></dt><dd>Curvature tolerance with no dimension.
  * <br>Value is stricly positive , restricted to interval ] 0 , 1 ] with 0.98 as default..
  * <br>Curvature value "c" is defined by : | R2 - R1 | / max ( |R1| , |R2| ) < ( 1 - c ) / c.
  * ( where R1 and R2 are the curvatures on both side ).
  * </dl>
  */
  virtual void SetTolerance(
    const CATResolutionType iContinuity,
    const double &iTolerance) = 0;

  /**
  * Gets the propagation diagnoses at each extremity of the output wire. 
  * @param oDiagnoses
  * This array is filled with two diagnoses corresponding to the start and end of the output wire.
  * @param oDiagnosesValue
  * If not <tt>NULL</tt> , this array must be allocated for two values.
  * <br>It is then filled with the two values corresponding to the limit reached 
  * at the start and end of the output wire.
  * <br><b>In case of</b>:
  * <dl>
  * <dt><tt>POINT_DISCONTINUITY</tt></dt><dd> The value is the lowest point discontinuity found.
  * <dt><tt>ANGULAR_DISCONTINUITY</tt></dt><dd> The value is the lowest angular discontinuity found.
  * <dt><tt>CURVATURE_DISCONTINUITY</tt></dt><dd> The value is the lowest curvature discontinuity found.
  * <dt><tt>for other value</tt></dt><dd> It is filled with 0 ( meaning less ).
  * </dl>
  */
  virtual void GetDiagnoses(
    CATTopEdgePropagationDiagnosis oDiagnoses[2],
    double *oDiagnosesValue = NULL) = 0;

protected:
  /**
   * Destructor
   */
  virtual ~CATICGMTopEdgePropagation(); // -> delete can't be called
};

/**
  * Creates a CATICGMTopEdgePropagation operator.
  * @param iFactory
  * The factory which creates the resulting body.
  * @param iTopData
  * The pointer to the data defining the configuration and the journal. If the journal inside <tt>iTopData</tt> 
  * is <tt>NULL</tt>, it is not filled. 
  * @param iBody
  * The body which contains the initial edge and where the propagation is carried out.
  * This body can be a 1D, 2D or 3D body.
  * <br>If the body is made of several domains, the propagation is performed only within a single domain 
  * ( the domain of the initial edge ).
  * @param iInitialEdge
  * The first edge to be concatenated.
  * @return [out, IUnknown#Release]
  * The pointer to the created operator. To be released with the <tt>Release</tt> method after use.
  */
ExportedByCATGMModelInterfaces CATICGMTopEdgePropagation *CATCGMCreateTopEdgePropagation(
  CATGeoFactory *iFactory,
  CATTopData *iTopData,
  CATBody *iBody,
  CATEdge *iInitialEdge);

#endif /* CATICGMTopEdgePropagation_h_ */
