//* -*-c++-*- */
//===========================================================================
// Logical periodicity specification for Nurbs Curve and Surface
//     (NurbsSurface, NurbsCurve, PNurbs, Spline or PSpline)
//===========================================================================
// 
//  Core Integration is about
//    1) persistency (available on next data version CXR20 / R208)
//    2) propagation when transformed
//    3) loss when redefinition occured
//
//  Other propagation are depending on operations :
//     easier support for these CGM operations made with reproductible scenarios 
//    (as CGMReplay, Part Update, or applicative software sample..)
//
//  Logical periodicity is editable (Set,Reset) for restricted types :
//     NurbsSurface, NurbsCurve, PNurbs, Spline or PSpline
//
//  Logical periodicity is also browsable from :
//     CATExtrudedSurface   from direct pseudo-periodic profile (for U)
//         (aka TabulatedCylinder and RevolutionSurface)
//     CATProcOffsetSurface from original surface
//          with order of continuity minus one
//  Limitations about procedural pseudo-periodicity,
//     No EdgeCurve pseudo-periodicity
//  
//  This service does not check the numerical continuity.
// 
//===========================================================================
#ifndef CATCGMPeriodicityManager_H
#define CATCGMPeriodicityManager_H
 
#include "ExportedByGeometricObjects.h"
#include "CATCGMPeriodicityInfo.h"
#include "CATBoolean.h"
#include "CATMathInline.h"
#include "CATGeometry.h"

class CATCurve;
class CATSurface;
class CATCloneManager;
class CATCGMOutput;


/**
* Services to extend logical periodicity on geometrical Nurbs (Curve,PCurve,Surface).
*
* Propagation inside CGM Modeler is made when :
*<dl>
* <dt>Persistency</dt><dd>  is done  
* <dt>Clone and Transfo</dt><dd>  is done  
* <dt>Sweep </dt><dd> TODO
*</dl>
*
* Logical periodicity is lost by default as soon as :
*<dl>
* <dt>Direct definition </dt><dd> Is Modified    
*</dl>
*
* Some Indirect Browse Periodicity are deduced from native logical periodic geometry :
*
*    CATExtrudedSurface   from profile (for U)
*        (aka TabulatedCylinder and RevolutionSurface)
*
*    CATProcOffsetSurface from original surface
*        with order of continuity minus one
*/

class ExportedByGeometricObjects CATCGMPeriodicityManager
{
public :


  /**
  * Define a Periodicity on <tt>iCurve</tt> (NurbsCurve, PNurbs, Spline or PSpline).
  * @param iCurve restricted to (NurbsCurve, PNurbs, Spline or PSpline)
  *  The input geometrical curve.
  * @param iInfo
  *  The input periodicity information.
  */
  static void SetInfo( CATCurve * iCurve, const CATCGMPeriodicityInfo & iInfo );

  /**
  * Define a Periodicity on <tt>iSurface</tt>.
  * @param iSurface (NurbsSurface).
  *  The input geometrical surface.
  * @param iUorV
  *   <br><b>Legal values</b>:
  *   <dl><dt>TRUE</dt><dd>when specified along U parameter  .
  *   <dt>FALSE</dt><dd>when specified along V parameter  .
  * @param iInfo
  *  The input periodicity information.
  */
   static void SetInfo( CATSurface * iSurface, CATBoolean iUorV, const CATCGMPeriodicityInfo & iInfo );

  /**
  * Reset Periodicity information.
  * @param iGeometry (NurbsCurve, PNurbs, Spline, PSpline or NurbsSurface).
  *  The input geometrical curve or surface.
  */
   static void ResetInfo( CATGeometry * iGeometry );



  /**
  * Query a Periodicity extension on <tt>iCurve</tt> .
  * @param iCurve  
  *  The input geometrical curve.
  * @param oInfo
  *  The output periodicity information.
  * @return
   * <br><b>Legal values</b>:
   * <dl><dt>TRUE</dt><dd>when explicit and specified periodicity information is found .
   * <dt>FALSE</dt><dd>otherwise
   *</dl>
  */
  static CATBoolean GetInfo( CATCurve * iCurve, CATCGMPeriodicityInfo & oInfo );


  /**
  * Query a Periodicity extension on <tt>iSurface</tt>.
  * @param iSurface .
  *  The input geometrical surface.
  * @param iUorV
  *   <br><b>Legal values</b>:
  *   <dl><dt>TRUE</dt><dd>when specified along U parameter  .
  *   <dt>FALSE</dt><dd>when specified along V parameter  .
  * @param oInfo
  *  The output periodicity information.
  * @return
   * <br><b>Legal values</b>:
   * <dl><dt>TRUE</dt><dd>when explicit and specified periodicity information is found .
   * <dt>FALSE</dt><dd>otherwise
   *</dl>
  */
   static CATBoolean GetInfo( CATSurface * iSurface, CATBoolean iUorV, CATCGMPeriodicityInfo & oInfo );


  /**
  * Query a Periodicity extension on this <tt>iGeometry</tt>.
  * @param iGeometry
  *  The input geometrical curve or surface.
  * @return
   * <br><b>Legal values</b>:
   * <dl><dt>TRUE</dt><dd>when explicit and specified periodicity information is found .
   * <dt>FALSE</dt><dd>otherwise
   *</dl>
  */
   static CATBoolean HasInfo( CATGeometry * iGeometry );



  /**
  * Test if Periodicity information is enabled on this predfined <tt>iGeometry</tt>.
  *   excluding procedural geometry (introduced for integration management).
  * @param iGeometry
  *  The input geometrical curve or surface.
  * @return
   * <br><b>Legal values</b>:
   * <dl><dt>TRUE</dt><dd>if type of geometry is Nurbs (Curve,PCurve,Surface) .
   * <dt>FALSE</dt><dd>otherwise
   *</dl>
  */
  static INLINE   CATBoolean IsSetPeriodicityEnabled( CATGeometry * iGeometry );

  /**
  * Dump Periodicity information.
  * @param iGeometry (NurbsCurve, PNurbs, Spline or PSpline or NurbsSurface).
  *  The input geometrical curve or surface.
  * @param os
  *  Dump stream.
  */
   static void Dump( CATGeometry * iGeometry , CATCGMOutput& os );
 
private :
  CATCGMPeriodicityManager();
  ~CATCGMPeriodicityManager();
  CATCGMPeriodicityManager(const CATCGMPeriodicityManager &iCopy);
  CATCGMPeriodicityManager& operator=(const CATCGMPeriodicityManager &iCopy);

};

 /**
* Test if Periodicity information is enabled on this <tt>iGeometry</tt>.
* @param iGeometry
*  The input geometrical curve or surface.
* @return
* <br><b>Legal values</b>:
* <dl><dt>TRUE</dt><dd>when explicit and specified periodicity information is found .
* <dt>FALSE</dt><dd>otherwise
*</dl>
*/
INLINE CATBoolean CATCGMPeriodicityManager::IsSetPeriodicityEnabled( CATGeometry * iGeometry )
{
  if ( ! iGeometry  || ! iGeometry->IsCGMV5() ) return FALSE;

  if (  iGeometry->IsATypeOf(CATNurbsSurfaceType)
    || iGeometry->IsATypeOf(CATPSplineType) 
    || iGeometry->IsATypeOf(CATSplineCurveType) 
    || iGeometry->IsATypeOf(CATPNurbsType) 
    || iGeometry->IsATypeOf(CATNurbsCurveType) ) return TRUE;

  return FALSE;
}

 /**
  * @nodoc 
  * BreakPoint
  */
extern "C" ExportedByGeometricObjects void catcgmperiodic(CATULONG32 tag);   


#endif
