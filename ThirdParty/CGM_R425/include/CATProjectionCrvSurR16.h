#ifndef CATProjectionCrvSurR16_H
#define CATProjectionCrvSurR16_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATProjectionCrvSur.h"
#include "CATCreateProjection.h"
#include "CATMathDef.h"
#include "Y30E3PMG.h"
#include "CATGeoOperator.h"
#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"

class CATCurve;
class CATCrvLimits;
class CATPCurve;
class CATSurface;
class CATSurLimits;
class CATSurParam;
class CATCrvParam;
class CATPointOnSurface;
class CATCartesianPoint;
class CATMapX;
class CATMathBox;

/**
 * Class defining the operator of projection of a CATCurve onto a
 * CATSurface.
 *<br> The projection can be orthogonal or directional.
 * The resulting objects are points or curves. 
 *<ul>
 *<li>The CATProjectionCrvSur operator is created with the <tt>CreateProjection</tt> method and 
 * directly <tt>delete</tt>d with the usual C++ delete operator.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. The advanced mode also allows you to
 * run the same operator with different curves or surfaces.
 *<li>In both cases, the result is accessed with specific interators.
 *</ul>
 */
class ExportedByY30E3PMG CATProjectionCrvSurR16 : public CATProjectionCrvSur  
{
  public :
/**
 * 
 * Use the <tt>CreateProjection</tt> global method.
 */
    CATProjectionCrvSurR16 (CATGeoFactory * factory);

/**
 * Destructor.
 */
    virtual                      ~CATProjectionCrvSurR16 ();

/**
 * Returns the maximum orthogonal distance between the CATCurve and the 
 * CATSurface.
 * return
 * The distance.
 */
    virtual double                GetDistance        () = 0;


/**  */
   // Reads the maximum orthogonal distance between the initial curve !
   // and the current solution                              !
    virtual double                GetDistance        (const CATPCurve   * iPCurve,
                                                      const CATCrvLimits* iCrvLim) = 0;

/**
 * Returns the number of solution points of <tt>this</tt> CATProjectionCrvSur operator.
 * return
 * The number of points.
 */
    virtual CATLONG32             GetNumberOfPoints  () const = 0;

/**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
    virtual void                  BeginningPoint  () = 0;

/**
 * Skips to the next solution point of <tt>this</tt> CATProjectionCrvSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
    virtual CATBoolean            NextPoint   () = 0;

/**
 * Creates the next solution as a point on surface.
 * return
 * The pointer to the created point on curve. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the href CATICGMContainer#Remove method.
 */
    virtual CATPointOnSurface*    GetPointOnSurface  () const = 0;

/**
 * Creates the next solution point of <tt>this</tt> CATProjectionCrvSur operator.
 * return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the href CATICGMContainer#Remove method.
 */
    virtual CATCartesianPoint*    GetCartesianPoint   () const = 0;

/**
 * Returns the number of solution curves resulting of <tt>this</tt> CATProjectionCrvSur operator.
 * return
 * The number of curves.
 */
    virtual CATLONG32             GetNumberOfCurves  () const = 0;

/**
 * Initializes the iterator of the solution curves of <tt>this</tt> 
 * CATProjectionCrvSur operator.
 *<br>By default, the initialization is performed once the operator runs, 
 * and this is therefore only used to read the solutions again.
 */
    virtual void                  BeginningCurve () = 0;

/**
 * Skips to the next solution curve of <tt>this</tt> CATProjectionCrvSur operator.
 *<br>After <tt>BeginningCurve</tt>, it skips to the first curve. 
 * return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
    virtual CATBoolean            NextCurve    () = 0;

/**
 * Creates the next solution curve.
 * return
 * The pointer to the created curve. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the href CATICGMContainer#Remove method.
 */
    virtual CATCurve*             GetCurve            () = 0;

/**
 * Creates the next solution curve as a curve on surface.
 * return
 * The pointer to the created curve on surface. A new curve is created each time this method is called.
 * If you do not want to keep the created curve, use the href CATICGMContainer#Remove method.
 */
    virtual CATPCurve*            GetPCurve           () = 0;

/**
 * Maps the limitations of the next solution curve on the original curve.
 * param ioLim
 * The corresponding domain on the curve to projact.
 */
    virtual void                  GetLimitsOnCurve   (CATCrvLimits &ioLim) const = 0;
/**
 * Maps the limitations of the next solution curve on the original curve.
 * param ioStartParam
 * The parameter of the first limitation on the curve to project.
 * param ioEndParam
 * The parameter of the first limitation on the curve to project.
 */
    virtual void                  GetLimitsOnCurve   (CATCrvParam& ioStartParam,
                                                      CATCrvParam& ioEndParam  ) const = 0;

/**
 * Retrieves the limitations of the next resulting curve.
 * param ioLim
 * The domain of the next solution curve.
 */
    virtual void                  GetLimitsOnProjection   (CATCrvLimits &ioLim) = 0;

/**
 * Retrieves the limitations of the next resulting curve.
 * param ioStartParam
 * The parameter on the projection of the first limitation of the solution.
 * param ioEndParam
 * The parameter on the projection of the last limitation of the solution.
 */
    virtual void                  GetLimitsOnProjection   (CATCrvParam& ioStartParam,
                                                           CATCrvParam& ioEndParam  ) = 0;

/**
 * Retrieves the limits of the next resulting curve on the surface. 
 * param ioFirstParam
 * The surface parameter of the first limitation of the solution.
 * param ioLastParam
 * The surface parameter of the last limitation of the solution.
 */
    virtual void                  GetLimitsOnSurface (CATSurParam &ioFirstParam,
                                                      CATSurParam &ioLastParam ) const = 0;

/**
 * Maps a parameter on the curve to project to a parameter on the projection. 
 * <br>The PCurve must be previously created.
 * param iCrvParam
 * The parameter on the curve to project.
 * param ioProjParam
 * The corresponding parameter on the projection.
 */
    virtual void                  GetMappingParam (CATCrvParam& iCrvParam,
                                                   CATCrvParam& ioProjParam ) = 0;


/**
* 
*/
    virtual CATMapX*               GetMapX () = 0;


    /**
    * 
    * Retrieves the index of starting and ending points of the current curve
    * among the imposed points.  
    * Do not use for directional projection
    */
    virtual void GetStartingPointsIndex( CATLONG32 &oBegin, CATLONG32 &oEnd ) = 0;

    /**
    * 
    * Retrieves the index of starting and ending points of the current point
    * among the imposed points.  
    * Do not use for directional projection
    */
    virtual void GetPointsIndex( CATLONG32 &oBegin, CATLONG32 &oEnd ) = 0;

    /**
 * Tests whether the curve is entirely projected.  
 * return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is entirely projected, <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean            IsComplete () const = 0;

/**
 * Tests whether the curve is partially projected.  
 * return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is partially projected, <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean            IsPartial () const = 0;

/**
 * Tests whether the curve is entirely lying on the surface.  
 * return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is entirely laying, <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean            IsCompletelyOnSurface () = 0;

/**
 * Tests whether the curve is partially lying on the surface.
 * return
 * The result of the test.
 * <br><b>Legal values</b>: <tt>TRUE</tt> if it is partially laying, <tt>FALSE</tt> otherwise.
 */
    virtual CATBoolean            IsPartiallyOnSurface () = 0;

/**
 * Asks for the closest projection solution (<tt>ADVANCED</tt> mode).
 * <br> The operator only outputs the closest projection.
 */
    virtual void                  SetClosestProjection () = 0;

/**
 * Asks for the points to be indexed as the curves (<tt>ADVANCED</tt> mode).
 */
    virtual void                  SetPointsIndexing (CATBoolean iPointIndexing = TRUE) = 0;

/**
 * Set the maximal distance between a pint and its projected (<tt>ADVANCED</tt> mode).
 * <br> The operator only outputs the  projection under the distance.
 */
    virtual void                  SetMaximalDistance (double MaxDist) = 0;
    /**
    * Sets the "LayDown" mode. In "LayDown" mode, the operator returns a projection result
    * only if the distance between each point of the curve and its projection
    * is smaller than <tt>iLayDownDistance</tt>. 
    * <br> This API can only be used in <tt>ADVANCED</tt> mode and is available only in
    * normal projections.
    */
    virtual void                   SetLayDown(double iLayDownDistance) = 0;


/**
 * Asks for cusp cut setting (<tt>ADVANCED</tt> mode).
 * param iBool
 * <br><b>Legal values</b>: <tt>TRUE</tt> if operator cuts solution on cusp points, <tt>FALSE</tt> otherwise.
 */
    virtual void                  SetCuspCut(CATBoolean iBool) = 0;
/**
 * Asks for the all the solutions (<tt>ADVANCED</tt> mode).
 * <br> To call after a <tt>Run</tt> with <tt>SetClosestProjection</tt>.
 */
    virtual void                  UnSetClosestProjection () = 0;

/**
 *Asks for the projection solution not closed (<tt>ADVANCED</tt> mode).
 * <br> The operator only outputs projection not closed.
 */
    virtual void                  SetNoClosedProjection() = 0;



/**
 * Asks for the projection on a new CATSurface (<tt>ADVANCED</tt> mode).
 * param iOnNewSurface
 * The pointer to the new surface. 
 */
    virtual void                  SetSurface (CATSurface * iOnNewSurface) = 0;

/**
 * Modifies the surface domain to take into account for <tt>this</tt> CATIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current surface 
 * limitations.  
 * param iNewSurfaceLimits
 * The new limitations of the surface, <tt>NULL</tt> to take the current limitations.
 */
    virtual void                  SetLimits  (CATSurLimits * iNewSurfaceLimits) = 0;

/**
 * Asks for the projection of a new CATCurve (<tt>ADVANCED</tt> mode).
 * param iNewCurveToProject
 * The pointer to the new curve.
 */
    virtual void                  SetCurve  (CATCurve * iNewCurveToProject) = 0;

/**
 * Modifies the curve domain to take into account for <tt>this</tt> CATIntersectionCrvSur
 * operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current curve 
 * limitations.  
 * param iNewCurveLimits
 * The new limitations of the curve, <tt>NULL</tt> to take the current limitations.
 */
    virtual void                  SetLimits  (CATCrvLimits*iNewCurveLimits) = 0;

/**
 * 
 * Sets the initial point (u,v,w) for projection.
 */
    virtual void                  SetInitialPoint      (const CATSurParam& iSurParam,
                                                        const CATCrvParam& iCrvParam) = 0; 

/**
 * 
 * resets the inital point to NULL.
 */
    virtual void                  ResetInitialPoint      () = 0; 

/**
 * 
 * takes into account bounding boxes.
 */
    virtual void                  SetBoxes    (const CATMathBox &iSurBox, const CATMathBox &iCrvBox) = 0; 

};
  
#include "CreateProjection.h"

#endif





