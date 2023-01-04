//===================================================================
// COPYRIGHT Dassault Systemes 2015/05/21
//===================================================================
// CATApproxClothoide.cpp
// Header definition of class CATApproxClothoide
//===================================================================
//
// Usage notes: Approximation of a clothoïde defined with the parameters given.
//
//===================================================================
// Historic:
// 25/05/15 F1Z : Creation
// 12/04/19 F4E : Add Circle-Circle case
// 24/07/19 F4E : Add CATCreateClothoideEval for circle-clotho-circle case
// 27/09/19 F4E : * Add missing CATCreateEvalutor for interface to be equivalent with Approx creation interfaces (request from CDS team)
// 21/11/19 F4E : Documentation update.
// 13/12/19 F4E : New Circle-Circle case: for a clothoide with constrained Length (thus second circle position is not constrained)
//                * Add CATComputeSecondCirclePosition: to determine 2nd circle position 
//                * Add new Approx creator for that case
//                * Add new Evaluator creator for that case
// 17/01/20 F4E : Documentation update
// 13/03/20 F4E : * move of clockwise   define
//                * Remove one useless CATCreateApproxClothoide
//                * doc correction
// 17/04/20 F4E : Move of function CATComputeSecondCirclePosition() to CATClothoideFunctions file
//                Indent
// 09/02/21 Q48 : Migrate to use CATBasis2DCurveEvaluator internally
// 07/06/21 Q48 : Remove unused interface methods (CATCreateClothoideEval)
// 23/12/21 Q48 : Remove unused interface methods (CATCreateClothoideEval)
//===================================================================

#ifndef CATApproxClothoide_H
#define CATApproxClothoide_H

//===================================================================

// Geometric Operators
#include "GeoAdvCurves.h"
#include "CATGeoOperator.h"

// Special API
#include "CATSysErrorDef.h"

#include "CATIPGMApproxClothoide.h"

// System
class CATSoftwareConfiguration;

// Mathematics
class CATMathPoint2D;
class CATMathVector2D;
class CATMathInterval; // F4E 24Jul19

// Geometric Object
class CATGeoFactory;
class CATCurve;
class CATSurface;

// Geometric operators
class CATBasis2DCurveEvaluator;

// Temp archi
#include "CATCivilCurveArchiTEMP.h"

//===================================================================

class ExportedByGeoAdvCurves CATApproxClothoide: public CATGeoOperator
{
   CATCGMVirtualDeclareClass(CATApproxClothoide);
public:
   //-----------------------------------------------------------------------------
   // Object Management
   //-----------------------------------------------------------------------------
   /**
   * @nodoc
   * Do not use this constructor. Use the creation method
   * <tt>CreateCATApproxClothoide</tt>.
   */
   CATApproxClothoide(CATGeoFactory * iFactory);

   /**
   * Destructor
   */
   virtual ~CATApproxClothoide ();

#ifndef Q48_RemoveAngleOptions
   //-----------------------------------------------------------------------------
   // Options Interface (Set)
   //-----------------------------------------------------------------------------
   /**
   * Set the domain in which the clothoide angle must lay.
   * <br> Currently, the operator is optimized for an angle between [0, 2PI]
   * and does not try to find solution for an angle>4PI.
   * @param iMinAngle
   * The minimum angle the clothoide can have.
   * @param iMaxAngle
   * The Maximum angle the clothoide can have.
   */
   virtual void    SetAngleDomain        (double           iMinAngle,
                                          double           iMaxAngle)        = 0;

   /**
    * Set the algorithm behavior in case two clothoids
    * can be defined with the input parameters and other options given.
    * <br> Note this only occurs when the shifting and the length are given.
    */
   virtual void    SetAngleToKeep        (CATBoolean       iSmallerAngle)    = 0;
#endif // Q48_RemoveAngleOptions

   //-----------------------------------------------------------------------------
   // Output Interface (Get)
   //-----------------------------------------------------------------------------

   /**
   * @return
   * <br>E_FAIL  If there was an operator issue during the computation.
   * <br>S_FALSE If the operator did not succeed because of the inputs & option given
   *             are not consistent (out of domain or does not described a clothoide respecting the options).
   * <br>S_OK    If the operator has not encountered any issue.
   */
   virtual HRESULT GetRunStatus()                                            = 0;

   /**
    * @return
    * TRUE If the solution is a point, FALSE if it is a curve.
    */
   virtual HRESULT IsAPoint              (CATBoolean     & iIsAPoint)        = 0;

   /**
   *  Retrieve the point of inflexion of the clothoide in UV space.
   */
   virtual HRESULT GetPoint              (CATMathPoint2D & oPoint )          = 0;

   /**
   * @param oCurve
   * The curve approximating the clothoïde.
   * <br>The object life of the object retrieved has to be handle by the caller.
   */
   virtual HRESULT GetCurve              (CATCurve *     & oCurve)           = 0;

   /**
    * Retrieve the clothoide properties of the curve computed.
    */
   virtual HRESULT GetClothoideProperties(double *         oA2       = NULL,
                                          double *         oLength   = NULL,
                                          double *         oRadius   = NULL,
                                          double *         oAngle    = NULL,
                                          double *         oShifting = NULL) = 0;

   /**
   * @nodoc
   * @nocgmitf
   * Create the geometric objects factory to represent the solution.
   **/
   virtual void       VisualizeSolution()                                    = 0;

   /**
   * Defines curve orientation when needed as input (e.g. for clothoid creation in between two circles)
   */
   enum ClockOrientation {CLOCKWISE = CATApproxClothoide_CLOCKWISE, ANTI_CLOCKWISE = CATApproxClothoide_ANTI_CLOCKWISE};


   /**
   * Defines the transition type in between two circles
   */
   enum CircleCircleTransition {OVE = CATApproxClothoide_OVE, REVERSE = CATApproxClothoide_REVERSE};
};

// ============================================================================================================================= //
//                                                            CREATE                                                             //
// ============================================================================================================================= //

/**
* Create an operator which computes approximation of a clothoïde defined through two parameters at least.
* <br> If more than two clothoide parameters are given, the operator checks the consistency of the result with them.
* @param iPt
* The point where the clothoïde start
* @param iDir
* The tangent where the clothoïde start
* @param iDirOrtho
* The orthogonal direction of iDir. It represents the direction of the clothoïde center of curvature.
* @param iSurface
* The surface support of the clothoide.
* @param iA2
* The clothoïde parameter a²
* <br> It belongs in [0, +Infinite[
* @param iRadius
* The radius of the clothoïde end extremity.
* <br> It belongs in ]0, +Infinite[
* @param iLength
* The length of the clothoïde
* <br> It belongs in[0, +Infinite[
* @param iAngle
* The final angle of the clothoïde
* <br> It is the angle between the clothoïde end extremity normal and
* the orthogonal direction.
* <br> For instance, angle=2PI will leads to a clothoide that makes a complete turn.
* <br> It belongs in [0, +Infinite[
* @param iShifting
* The shifting of the clothoïde.
* <br>It represents the min distance between
* the circle of the clothoïde end extremity with the
* line defined by the point and direction given.
* <br> It belongs in [0, 0.1957*Length] and [0, sqrt(iA2*pi)/2.0[
*/
ExportedByGeoAdvCurves CATApproxClothoide * CATCreateApproxClothoide(      CATGeoFactory            * iFactory            ,
                                                                       CATSoftwareConfiguration * iConfig             ,
                                                                 const CATMathPoint2D           & iPt                 ,
                                                                 const CATMathVector2D          & iDir                ,
                                                                 const CATMathVector2D          & iDirOrtho           ,
                                                                       CATSurface               * iSurface            ,
                                                                 const double                   * iA2          = NULL ,
                                                                 const double                   * iLength      = NULL ,
                                                                 const double                   * iRadius      = NULL ,
                                                                 const double                   * iAngle       = NULL ,
                                                                 const double                   * iShifting    = NULL );

/**
* Create an operator which computes approximation of a clothoïde defined by a line and a circle in 2D (the surface UV-Space).
* @param iLineOrigin
* A point on the line.
* @param iLineDir
* The direction of the line. The direction determines the direction of the clothoide.
* @param iCircleCenter
* The center of the circle.
* @param iCircleRadius
* The radius of the circle.
* @param iSurface
* The surface support of the clothoide.
*/
ExportedByGeoAdvCurves CATApproxClothoide * CATCreateApproxClothoide(      CATGeoFactory            * iFactory            ,
                                                                       CATSoftwareConfiguration * iConfig             ,
                                                                 const CATMathPoint2D           & iLineOrigin         ,
                                                                 const CATMathVector2D          & iLineDir            ,
                                                                 const CATMathPoint2D           & iCircleCenter       ,
                                                                       double                     iCircleRadius       ,
                                                                       CATSurface               * iSurface            );

/**
* Create an operator which computes approximation of a clothoïde defined in between two oriented circles in 2D (the surface UV-Space).
* We assume that the path goes from the first one to the second.
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iCircleCenter2
* The center of the second circle.
* @param iCircleRadius2
* The radius of the second circle.
* @param iSurface
* The surface support of the clothoide.
*/
ExportedByGeoAdvCurves CATApproxClothoide * CATCreateApproxClothoide(  CATGeoFactory                          * iFactory            ,
                                                                       CATSoftwareConfiguration               * iConfig             ,
                                                                 const CATMathPoint2D                         & iCircleCenter1      ,
                                                                 const double                                   iCircleRadius1      ,
                                                                 const CATApproxClothoide::ClockOrientation     iCircleOrientation1 ,
                                                                 const CATMathPoint2D                         & iCircleCenter2      ,
                                                                 const double                                   iCircleRadius2      ,
                                                                       CATSurface                             * iSurface            );


/**
* Create an operator which computes approximation of a clothoïde defined in between two oriented circles in 2D (the surface UV-Space)
* The second circle radius only is known and the clothoide length is constrained.
* N.B.: We assume that the path goes from the first circle to the second one AND that 
*             - in OVE     case : first circle is the one with largest radius
*             - in REVERSE case : first circle is the one witchmatches the negative part of the clothoide 
* @param iCircleCenter1
* The center of the first circle.
* @param iCircleRadius1
* The radius of the first circle.
* @param iCircleOrientation1
* The clockwise or anti-clockwise orientation of the first circle (direction of course).
* @param iStartPointOnCircle1
* The point on first circle where the clothoide starts
* @param iCircleRadius2
* The radius of the second circle.
* @param iTransitionType
* The transition type in betwen the two circles (OVE or REVERSE)
* @param iClothoideLength
* The length of the clothoide imposed in between the two circles.
* @param iSurface
* The surface support of the clothoide.
*/
ExportedByGeoAdvCurves CATApproxClothoide * CATCreateApproxClothoide(       CATGeoFactory                                  * iFactory            ,
                                                                            CATSoftwareConfiguration                       * iConfig             ,
                                                                      const CATMathPoint2D                                 & iCircleCenter1      ,
                                                                      const double                                           iCircleRadius1      ,
                                                                      const CATApproxClothoide::ClockOrientation             iCircleOrientation1 ,
                                                                      const CATMathPoint2D                                 & iStartPointOnCircle1,
                                                                      const double                                           iCircleRadius2      ,
                                                                      const CATApproxClothoide::CircleCircleTransition       iTransitionType     ,
                                                                      const double                                           iClothoideLength    ,
                                                                            CATSurface                                     * iSurface            );


/**
* Create an operator which computes approximation of a clothoïde defined by the two extremities points and initial tangent.
* <br> The surface support will be the PLine support.
* @param iStartPoint
* The start extremity of the clothoïd.
* @param iStartTangent
* The start extremity tangent of the clothoïd.
* @param iEndPoint
* The end extremity of the clothoïd.
* @param iSurface
* The surface support of the clothoide.
*/
ExportedByGeoAdvCurves CATApproxClothoide * CATCreateApproxClothoide(      CATGeoFactory            * iFactory            ,
                                                                       CATSoftwareConfiguration * iConfig             ,
                                                                 const CATMathPoint2D           & iStartPoint         ,
                                                                 const CATMathVector2D          & iStartTangent       ,
                                                                 const CATMathPoint2D           & iEndPoint           ,
                                                                       CATSurface               * iSurface            );

// ============================================================================================================================= //
//                                                            METHODS                                                            //
// ============================================================================================================================= //

/**
* Computes the two clothoids parameters from a Line-Clotho-Circle-Clotho-Line configuration.
* <br/>
* This method can return self intersecting solution. To avoid self-intersecting solution,
* one must check the sum of the two clothoids final angle is lower than the angle between the two orthogonal directions.
* <br/>
* The solution returned will always be the one going toward the line intersection.
* @param iPtLine1
* A point of the first line.
* @param iDirLine1
* The direction of the first line. The sign is not used.
* @param iDirOrtho1
* The orthogonal direction of iDirLine1. It represents the direction of the first clothoïde center of curvature.
* @param iPtLine2
* A point of the second line.
* @param iDirLine2
* The direction of the second line. The sign is not used.
* @param iDirOrtho2
* The orthogonal direction of iDirLine2. It represents the direction of the second clothoïde center of curvature.
* @param iLengthClotho1
* The length of the first clothoid
* @param iLengthClotho2
* The length of the second clothoid
* @param iRadius
* The radius of the circle arc between the two clothoids.
* @param oClotho1OnLine1
* The starting point of the first clothoid on the first line.
* @param oCenterCircle
* The position of the center of the circle between the two clothoids.
* @param oClotho2OnLine2
* The starting point of the second clothoid on the second line.
* @param oSelfIntersection
* Equals TRUE if the solution is self-intersecting, FALSE otherwise.
* @param oEndPointsConfused
* Equals TRUE if the arc between the two clothoids is smaller than the resolution, FALSE otherwise.
* @return 
* <br>E_FAIL  If there was an issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the final angle is too high, the clothoid length under the resolution)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByGeoAdvCurves HRESULT              CATComputeParamClothoide(      CATSoftwareConfiguration * iConfig           ,
                                                                 const CATTolerance             & iTol              ,
                                                                 const CATMathPoint2D           & iPtLine1          ,
                                                                 const CATMathVector2D          & iDirLine1         ,
                                                                 const CATMathVector2D          & iDirOrtho1        ,
                                                                 const CATMathPoint2D           & iPtLine2          ,
                                                                 const CATMathVector2D          & iDirLine2         ,
                                                                 const CATMathVector2D          & iDirOrtho2        ,
                                                                 const double                     iLengthClotho1    ,
                                                                 const double                     iLengthClotho2    ,
                                                                 const double                     iRadius           ,
                                                                       CATMathPoint2D           & oClotho1OnLine1   ,
                                                                       CATMathPoint2D           & oCenterCircle     ,
                                                                       CATMathPoint2D           & oClotho2OnLine2   ,
                                                                       CATBoolean               & oSelfIntersection ,
                                                                       CATBoolean               & oEndPointsConfused);

/**
* Computes the two clothoids parameters from a Circle-Clotho-Line-Clotho-Circle configuration.
* @param iCircleCenter1
* The center of the first circle
* @param iCircleRadius1
* The radius of the first circle
* @param iLineLeftFromCircle1
* The position of the intermediare line from Circle1
* @param iCircleCenter2
* The center of the second circle
* @param iCircleRadius2
* The radius of the second circle
* @param iLineLeftFromCircle2
* The position of the intermediare line from Circle2
* @param iLengthClotho1
* The length of the clothoid starting from the first circle
* @param iLengthClotho2
* The length of the clothoid starting from the second circle
* @param oClotho1OnLine
* The starting point of the first clothoid on the intermediate line.
* @param oClotho2OnLine
* The starting point of the second clothoid on the intermediate line.
* @param oDirClotho1
* The starting direction of the first clothoid
* @param oDirClotho2
* The starting direction of the second clothoid
* @return 
* <br>E_FAIL  If there was an issue during the computation.
* <br>S_FALSE If the operator did not succeed because of the inputs & option given
*             are not consistent (ex: the final angle is too high, the clothoid length under the resolution)
* <br>S_OK    If the operator has not encountered any issue.
*/
ExportedByGeoAdvCurves HRESULT              CATComputeParamClothoide(      CATSoftwareConfiguration * iConfig             ,
                                                                 const CATTolerance             & iTol                ,
                                                                 const CATMathPoint2D           & iCircleCenter1      ,
                                                                 const double                     iCircleRadius1      ,
                                                                 const CATBoolean                 iLineLeftFromCircle1,
                                                                 const CATMathPoint2D           & iCircleCenter2      ,
                                                                 const double                     iCircleRadius2      ,
                                                                 const CATBoolean                 iLineLeftFromCircle2,
                                                                 const double                     iLengthClotho1      ,
                                                                 const double                     iLengthClotho2      ,
                                                                       CATMathPoint2D           & oClotho1OnLine      ,
                                                                       CATMathPoint2D           & oClotho2OnLine      ,
                                                                       CATMathVector2D          & oDirClotho1         ,
                                                                       CATMathVector2D          & oDirClotho2         );



/**
* @nodoc
* @nocgmitf
*/
ExportedByGeoAdvCurves void Remove (CATApproxClothoide * & ioApproxClothoOp);

//-----------------------------------------------------------------------

#endif
