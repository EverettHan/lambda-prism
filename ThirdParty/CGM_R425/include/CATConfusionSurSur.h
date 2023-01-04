// COPYRIGHT DASSAULT SYSTEMES 2012
//=============================================================================
//
// CATConfusionSurSur.h
//   Class for the operator CATConfusionSurSur,
//   which determines whether two surfaces are confused within a specified loop
//   (of edge curves), subject to a specified tolerance.
//   Currently, only one edge-curve loop is permitted.
//   Note that the loop must not self-intersect, and, if inner loops are
//   subsequently permitted, none of the loops should self-intersect, or
//   intersect any other loops.
//
//=============================================================================
//
// 03/07/2012    Creation                                             XMH
// 31/08/2012    Added additional functionality.                      R1Y
//
//=============================================================================

#ifndef CATConfusionSurSur_H
#define CATConfusionSurSur_H

#include "CATMathDef.h"
#include "CATGeoOperator.h"
#include "Y30A3HGG.h"

#include "CATListOfCATPCurves.h"
#include "CATListOfCATEdgeCurves.h"
#include "CATSkillValue.h"

class CATGeoFactory;
class CATPCurve;
class CATEdgeCurve;
class CATSurface;

// Enum defining the states of confusion
// Warning: As this enum is streamed to the replay file, any new confusion types should be added to the end (and not inserted)
/**
 * Defines the states of confusion that are returned from the operator.
 * @param <tt>UNKNOWN</tt>
 * The state of surface confusion is unknown.
 * @param <tt>ERRORSTATE</tt>
 * An error has occurred, so surface confusion cannot be determined.
 * @param <tt>NOTCONFUSED</tt>
 * The Haussdorf distance between the two CATSurfaces on the region specified is NOT less than the
 * confusion tolerance.
 * @param <tt>CONFUSED</tt>
 * The Haussdorf distance between the two CATSurfaces on the region specified is less than the
 * confusion tolerance.
 * @param <tt>CANONICAL_SAME</tt>
 * The surfaces are canonical, and are deemed to be the same (so they are confused).
 * @param <tt>NONCLOSEDLOOPS</tt>
 * The gaps in both loops are too large, so surface confusion cannot be determined.
 * @param <tt>NOSAMPLINGPOINTS</tt>
 * It has not been possible to obtain any sampling points, so surface confusion cannot be determined.
 * @param <tt>THINLOOPS</tt>
 * Neither of the edge-curve loops is large enough to include sampling points, so surface confusion
 * cannot be determined.
 */
enum ConfusionType { UNKNOWN = -1, ERRORSTATE, NOTCONFUSED, CONFUSED, CANONICAL_SAME, NONCLOSEDLOOPS, NOSAMPLINGPOINTS, THINLOOPS };

/**
 * Class defining the operator testing the overlap of two CATSurfaces.
 *<br>Two surfaces are overlapping within a given tolerance if their
 * Haussdorf distance <tt>dH</tt> is less than this tolerance.<br>
 * <pre>
 * dH= MAX [ Max{Point1 in Surface1}Min{Point2 in Surface2} distance(Point1,Point2),
 *           Max{Point2 in Surface2}Min{Point1 in Surface1} distance(Point1,Point2) ]</pre>
 *<ul>
 *<li>The CATConfusionOperator is created with the @href CreateConfusionSurSur method and 
 * directly <tt>delete</tt>d. It is not streamable. 
 *<li>The operation is automatically done at the operator creation. 
 *<li>The result is accessed with <tt>GetConfusion</tt> method.
 *</ul>
 */
class ExportedByY30A3HGG CATConfusionSurSur : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATConfusionSurSur);
 public:

/**
 * Destructor.
 */
  virtual ~CATConfusionSurSur();
/** @nodoc */
  CATConfusionSurSur(CATGeoFactory * iFactory);

 /**
  * Sets the limits of the two surfaces for <tt>this</tt> CATConfusionSurSur operator.
  * @param iSurLimits1
  * The limits for the first surface.
  * If the pointer to the surface limits is null, or if the surface limits are invalid,
  * then the surface limits are not modified.
  * @param iSurLimits2
  * The limits for the second surface.
  * If the pointer to the surface limits is null, or if the surface limits are invalid,
  * then the surface limits are not modified.
  */
  virtual void SetSurfaceLimits(const CATSurLimits * const iSurLimits1,
                                const CATSurLimits * const iSurLimits2) = 0;

 /**
  * Sets the numbers of sampling lines in the two directions of the sampling surface
  * for <tt>this</tt> CATConfusionSurSur operator.
  * @param iNumLinesU
  * The number of sampling lines in the U-parameter direction of the sampling surface.
  * If the supplied value is less than 1 then the number of points is set to 1.
  * @param iNumLinesV
  * The number of sampling lines in the V-parameter direction of the sampling surface.
  * If the supplied value is less than 1 then the number of points is set to 1.
  */
  virtual void SetNumLinesUV(const CATLONG32 iNumLinesU,
                             const CATLONG32 iNumLinesV) = 0;

 /**
  * Sets the numbers of sampling points on each sampling line in the two directions of
  * the sampling surface for <tt>this</tt> CATConfusionSurSur operator.
  * @param iNumPointsPerLineU
  * The number of sampling points on each sampling line in the U-parameter direction of
  * the sampling surface.
  * If the supplied value is less than 1 then the number of lines is set to 1.
  * @param iNumPointsPerLineV
  * The number of sampling points on each sampling line in the V-parameter direction of
  * the sampling surface.
  * If the supplied value is less than 1 then the number of lines is set to 1.
  */
  virtual void SetNumPointsPerLineUV(const CATLONG32 iNumPointsPerLineU,
                                     const CATLONG32 iNumPointsPerLineV) = 0;

 /**
  * Sets the confusion tolerance for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @param iConfusionTolerance
  * The confusion tolerance.
  * If, within the edge-curve loops, the maximum distance between the two surfaces is
  * less than the confusion tolerance then the surfaces are deemed to be confused;
  * otherwise, they are deemed to be not confused.
  * If the supplied value is not positive then the stored value is not changed.
  */
  virtual void SetConfusionTolerance(const double iConfusionTolerance) = 0;

/**
  * Sets the flag that indicates whether to check for identical canonical surfaces for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @param iCheckForIdenticalCanonicals
  * The flag that indicates whether to check for identical canonical surfaces.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if checks for identical canonical surfaces
  * are to be performed, <tt>FALSE</tt> otherwise.
  * If checks are to be performed, they are carried out before the sampling algorithm.
  * Further, if the two surfaces are deemed to be identical, the confusion state is set
  * to be <tt>CONFUSED</tt> (and the sampling algorithm is not carried out).
  * The default value for this parameter is <tt>TRUE</tt>.
  */
  virtual void SetCheckForIdenticalCanonicals(const CATBoolean iCheckForIdenticalCanonicals = TRUE) = 0;

 /**
  * Sets the maximum allowable gap in the edge-curve loop for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @param iMaxAllowableGapInLoop
  * The maximum allowable gap in the edge-curve loop.
  * If the supplied value is not positive then the stored value is not changed.
  * This parameter is to be used only for debugging purposes.
  */
  virtual void SetDebugMaxAllowableGapInLoop(const double iMaxAllowableGapInLoop) = 0;

 /**
  * Sets the tolerance for the intersection operator for two p-curves for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @param iIntersectionTolerance
  * The tolerance for the intersection operator for two p-curves.
  * If the supplied value is not positive then the stored value is not changed.
  * This parameter is to be used only for debugging purposes.
  */
  virtual void SetDebugIntersectionTolerance(const double iIntersectionTolerance) = 0;

 /**
  * Sets the minimum distance between sampling points for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @param iMinDistBetweenSamplingPoints
  * The minimum distance between sampling points.
  * If the supplied value is not positive then the stored value is not changed.
  * This parameter is to be used only for debugging purposes.
  */
  virtual void SetDebugMinDistBetweenSamplingPoints(const double iMinDistBetweenSamplingPoints) = 0;

  /**
  * Sets the tolerance for checking whether a point lies within a loop of p-curves for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @param iDebugPointInLoopTolerance
  * The tolerance for checking whether a point lies within a loop of p-curves.
  * If the supplied value is not positive then the stored value is not changed.
  * This parameter is to be used only for debugging purposes, and can be used only in debug mode.
  */
  virtual void SetDebugPointInLoopTolerance(const double iDebugPointInLoopTolerance) = 0;

   /**
  * Returns the numbers of sampling lines in the two directions of the sampling surface
  * for <tt>this</tt> CATConfusionSurSur operator.
  * @param oNumLinesU
  * The number of sampling lines in the U-parameter direction of the sampling surface.
  * @param oNumLinesV
  * The number of sampling lines in the V-parameter direction of the sampling surface.
  */
  virtual void GetNumLinesUV(CATLONG32 & oNumLinesU,
                             CATLONG32 & oNumLinesV) const = 0;

 /**
  * Returns the limits of the two surfaces for <tt>this</tt> CATConfusionSurSur operator.
  * @param oSurLimits1
  * The limits for the first surface.
  * @param oSurLimits2
  * The limits for the second surface.
  */
  virtual void GetSurfaceLimits(CATSurLimits & oSurLimits1,
                                CATSurLimits & oSurLimits2) const = 0;

 /**
  * Returns the numbers of sampling points on each sampling line in the two directions of
  * the sampling surface for <tt>this</tt> CATConfusionSurSur operator.
  * @param oNumPointsPerLineU
  * The number of sampling points on each sampling line in the U-parameter direction of
  * the sampling surface.
  * @param oNumPointsPerLineV
  * The number of sampling points on each sampling line in the V-parameter direction of
  * the sampling surface.
  */
  virtual void GetNumPointsPerLineUV(CATLONG32 & oNumPointsPerLineU,
                                     CATLONG32 & oNumPointsPerLineV) const = 0;

/**
  * Returns the confusion tolerance for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @return
  * The confusion tolerance.
  */
  virtual double GetConfusionTolerance() const = 0;

/**
  * Returns the flag that indicates whether to check for identical canonical surfaces for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @return
  * The flag that indicates whether to check for identical canonical surfaces.
  * <br><b>Legal values</b>: <tt>TRUE</tt> if checks for identical canonical surfaces
  * are to be performed, <tt>FALSE</tt> otherwise.
  */
  virtual CATBoolean GetCheckForIdenticalCanonicals() const = 0;

 /**
  * Returns the maximum allowable gap in the edge-curve loop for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @return
  * The maximum allowable gap in the edge-curve loop.
  * This parameter is to be used only for debugging purposes.
  */
  virtual double GetDebugMaxAllowableGapInLoop() const = 0;

 /**
  * Returns the tolerance for the intersection operator for two p-curves for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @return
  * The tolerance for the intersection operator for two p-curves.
  * This parameter is to be used only for debugging purposes.
  */
  virtual double GetDebugIntersectionTolerance() const = 0;

 /**
  * Returns the minimum distance between sampling points for <tt>this</tt>
  * CATConfusionSurSur operator.
  * @return
  * The minimum distance between sampling points.
  * This parameter is to be used only for debugging purposes.
  */
  virtual double GetDebugMinDistBetweenSamplingPoints() const = 0;

 /**
  * Returns the tolerance for checking whether a point lies within a loop of p-curves for
  * <tt>this</tt> CATConfusionSurSur operator.
  * @return
  * The tolerance for checking whether a point lies within a loop of p-curves.
  * This parameter is to be used only for debugging purposes, and can be used only in debug mode.
  */
  virtual double GetDebugPointInLoopTolerance() const = 0;

/**
 * Returns the result of <tt>this</tt> CATConfusionSurSur operator.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>:
 * <dl>
 * <dt><tt>UNKNOWN</tt> <dd>The state of surface confusion is unknown.
 * <dt><tt>ERRORSTATE</tt> <dd>An error has occurred, so surface confusion cannot be determined.
 * <dt><tt>NOTCONFUSED</tt> <dd>The Haussdorf distance between the two CATSurfaces
 * on the region specified is NOT less than the confusion tolerance.
 * <dt><tt>CONFUSED</tt> <dd>The Haussdorf distance between the two CATSurfaces
 * on the region specified is less than the confusion tolerance.
 * <dt><tt>CANONICAL_SAME</tt> <dd>The surfaces are canonical, and are deemed to be the same
 * (so they are confused).</dl>
 * <dt><tt>NONCLOSEDLOOPS</tt> <dd>The gaps in both loops are too large, so surface confusion
 * cannot be determined.</dl>
 * <dt><tt>NOSAMPLINGPOINTS</tt> <dd>It has not been possible to obtain any sampling points,
 * so surface confusion cannot be determined.</dl>
 * <dt><tt>THINLOOPS</tt> <dd>Neither of the edge-curve loops is large enough to include
 * sampling points, so surface confusion cannot be determined.</dl>
 */
  virtual ConfusionType GetConfusion() const = 0;

/**
 * Returns the confidence level when the confusion result is <tt>CONFUSED</tt>.
 * @return
 * If the surfaces are confused, the confidence level is returned as a percentage
 * (namely, the percentage of the number of sampling points used relative to the maximum
 * number of possible sampling points); otherwise, zero is returned.
 * Note the if the confusion result is <tt>CANONICAL_SAME</tt> then a confidence level of
 * 100 is returned.
 * 
 */
  virtual double GetConfidenceLevel() const = 0;

/**
 * Returns whether the two surfaces are confused.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the two surfaces are confused,
 * <tt>FALSE</tt> otherwise.
 * 
 */
  virtual CATBoolean IsConfused() const = 0;

/**
 * Returns whether the two surfaces are not confused.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the two surfaces are not confused,
 * <tt>FALSE</tt> otherwise.
 * 
 */
  virtual CATBoolean IsNotConfused() const = 0;

/**
 * Returns whether the state of confusion between the two surfaces is unknown.
 * @return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if the state of confusion between the two surfaces is unknown,
 * <tt>FALSE</tt> otherwise.
 * 
 */
  virtual CATBoolean IsUnknownConfusion() const = 0;

/**
 * Returns the number of sampling points used in the confusion calculation.
 * @return
 * If the confusion result is <tt>CONFUSED</tt>, the number of sampling points (used in the calculation) is
 * returned; otherwise, zero is returned.
 */
  virtual CATLONG32 GetNumSamplingPointsUsed() const = 0;

/**
 * Returns the distance between the two surfaces.
 * @return
 * If the confusion type is <tt>NOTCONFUSED</tt>, the returned distance corresponds to points
 * on the two surfaces that are futher apart than the specified tolerance; if the confusion type
 * is <tt>CONFUSED</tt>, the returned distance is the maximum Haussdorf distance (between the two
 * surfaces) over the sampling points; otherwise, the returned distance is unreliable.
 */
  virtual double GetDistance() const = 0;

/**
 * Returns a surface parameter from the first surface.
 * @return
 * If the confusion type is <tt>NOTCONFUSED</tt>, the parameter corresponds to a point (on the
 * first surface) that is further from the second surface than the specified tolerance; if the
 * confusion type is <tt>CONFUSED</tt>, the returned surface parameter corresponds to a sampling
 * point (on the first surface) that is the maximum Haussdorf distance from the second surface;
 * otherwise, the contents of the surface parameter are unreliable.
 */
  virtual void GetSurParam1(CATSurParam & oSurParam1) const = 0;

/**
 * Returns a surface parameter from the second surface.
 * @return
 * If the confusion type is <tt>NOTCONFUSED</tt>, the parameter corresponds to a point (on the
 * second surface) that is further from the first surface than the specified tolerance; if the
 * confusion type is <tt>CONFUSED</tt>, the returned surface parameter corresponds to a sampling
 * point (on the second surface) that is the maximum Haussdorf distance from the first surface;
 * otherwise, the contents of the surface parameter are unreliable.
 */
  virtual void GetSurParam2(CATSurParam & oSurParam2) const = 0;
};

/**
 * Creates an operator for testing the overlap of two CATSurfaces.
 *<br>The region consider is bounded by a list of edgecurves which form a closed loop.
 * @param iFactory
 * The pointer to the factory of the surfaces.
 * @param iConfig
 * The software configuration.
 * @param iSurface1
 * The first surface.
 * @param iSurface2
 * The second surface.
 * @param iListOfPCurves1
 * List of CATPCurves on the first surface.
 * @param iListOfPCurves2
 * List of CATPCurves on the second surface.
 * @param iListOfEdgeCurves
 * List of CATEdgeCurves.
 * @param iListOfCrvLimits
 * List of limits of the CATEdgeCurves.
 * @param iConfusionTol
 * The maximum Haussdorf distance for deciding the overlap.
 * <br><b>Legal values</b>:
 * <dl><dt><tt>BASIC</tt> <dd>The operation is performed at the operator creation.
 *     <dt><tt>ADVANCED</tt>  <dd>Use the <tt>Run</tt> method to computes the operation.</dl>
 * @return
 * The pointer to the created operator. 
*/
ExportedByY30A3HGG CATConfusionSurSur * 
CATCreateConfusion(CATGeoFactory                * iFactory,
                   CATSoftwareConfiguration     * iConfig,
                   const CATSurface             * iSurface1,
                   const CATSurface             * iSurface2,
                   const CATListOfInt           & iListOfNbEdgesInLoop,
                   const CATLISTP(CATPCurve)    & iListOfPCurves1,
                   const CATLISTP(CATPCurve)    & iListOfPCurves2,
                   const CATLISTP(CATEdgeCurve) & iListOfEdgeCurves,
                   const CATLISTP(CATCrvLimits) & iListOfCrvLimits,
                   const double                 & iConfusionTol,
                   CATSkillValue                  iMode = BASIC);

#endif
