#ifndef CATINTERSECTTRISUR_H
#define CATINTERSECTTRISUR_H

// COPYRIGHT DASSAULT SYSTEMES  2000

#include "CATMathDef.h"
#include "Y30C3XGG.h"
#include "CATCreateIntersection.h"
#include "CATGeoOperator.h"

class CATSurface;
class CATSurParam;
class CATSurLimits;
class CATCartesianPoint;
class CATPointOnSurface;

/**
 * Class defining the operator of the intersection of three surfaces.
 *<br>The operator outputs the isolated solutions points
 *<ul>
 *<li>The CATIntersectionTriSur operator is created with the <tt>CreateIntersection</tt> method and 
 * directly <tt>delete</tt>d.
 * It is is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed at the operator creation. 
 * In case of <tt>ADVANCED</tt>
 * mode, options can be precised with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method. 
 *<li>In both cases, the result is accessed with specific interators, one for the solution points,
 * another for the solution curves and a last one for the solution surfaces.
 *</ul>
 */
class ExportedByY30C3XGG CATIntersectionTriSur : public CATGeoOperator
{
  CATCGMVirtualDeclareClass(CATIntersectionTriSur);
 public:
/**
 * Use the <tt>CreateIntersection</tt> global method.
 */
   CATIntersectionTriSur(CATGeoFactory * factory) ;

/**
 * Destructor.
 */
   virtual ~CATIntersectionTriSur() ;

/**
 * Returns the number of solution points.
 * @return
 * The number of solutions.
 */
   virtual CATLONG32 GetNumberOfPoints() const = 0;

/**
 * Initializes the iterator of the resulting points.
 *<br>By default, the initialization is performed once the operator runs,
 * and this is therefore only used to read the solutions again.
 */
   virtual void BeginningPoint() = 0;

/**
 * Skips to the next solution point of <tt>this</tt> CATIntersectionTriSur operator.
 *<br>After <tt>BeginningPoint</tt>, it skips to the first point. 
 * @return
 * The existence of the next solution.
 * <br><b>Legal values</b>:
 *<dl><dt><tt>TRUE</tt> <dd>if there is a solution point
 *    <dt><tt>FALSE</tt> <dd>no more solution point.</dl>
 */
   virtual CATBoolean NextPoint() = 0;

/**
 * Retrieves the parameters on each surface of the next solution point of <tt>this</tt> CATIntersectionTriSur operator.
 * @param ioSurParam1
 * The parameter on the first surface.
 * @param ioSurParam2
 * The parameter on the second surface.
 * @param ioSurParam3
 * The parameter on the third surface.
 */
   virtual void GetSurParam( CATSurParam &ioSurParam1,
                             CATSurParam &ioSurParam2,
                             CATSurParam &ioSurParam3) = 0;
/**
 * Creates the next solution point on a surface of <tt>this</tt> CATIntersectionTriSur operator.
 * @param iSurface
 * The pointer to one of the intersecting surface.
 * @return
 * The pointer to the created point on surface. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
   virtual CATPointOnSurface * GetPointOnSurface(CATSurface *iSurface) = 0;

/**
 * Creates the next solution point of <tt>this</tt> CATIntersectionTriSur operator.
 * @return
 * The pointer to the created point. A new point is created each time this method is called.
 * If you do not want to keep the created point, use the @href CATICGMContainer#Remove method.
 */
   virtual CATCartesianPoint * GetCartesianPoint() = 0;


/**
 * Modifies the surface domains to take into account for <tt>this</tt>
 * CATIntersectionTriSur operator (<tt>ADVANCED</tt> mode).
 *<br> It does not change the current surface limitations.
 * @param iNewLimitsForSurface1
 * The pointer to the new domain of the first surface. If <tt>NULL</tt>, the current limitation of the first
 * surface is used.
 * @param iNewLimitsForSurface2
 * The pointer to the new domain of the second surface. If <tt>NULL</tt>, the current limitation of the second
 * surface is used.
 * @param iNewLimitsForSurface3
 * The pointer to the new domain of the third surface. If <tt>NULL</tt>, the current limitation of the third
 * surface is used.
 */
   virtual void SetLimits (CATSurLimits  * iNewLimitsForSurface1,
			  CATSurLimits  * iNewLimitsForSurface2,
        CATSurLimits  * iNewLimitsForSurface3) = 0;


/**
 * Runs <tt>this</tt> CATIntersectionTriSur operator in <tt>ADVANCED</tt> mode.
 */
   virtual int Run() = 0;

};

#include "CreateIntersection.h"

#endif
