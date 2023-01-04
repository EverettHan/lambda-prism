#ifndef CATListOfProjectionCrvSur_H
#define CATListOfProjectionCrvSur_H

// COPYRIGHT DASSAULT SYSTEMES  1999

#include "CATMathDef.h"
#include "Y30E3PMG.h"
#include "CATCGMOperator.h"
#include "CATListOfCATPCurves.h"

class CATCurve;
class CATPCurve;
class CATSurface;

/**
 * Class defining the operator of projection of a list of CATCurves onto a
 * list of CATSurfaces. Curves must lay on Surfaces.
 *<br> The projection can be orthogonal or directional.
 * The resulting object is a list of CATPCurves. 
 *<ul>
 *<li>The CATListOfProjectionCrvSur operator is created with the <tt>CreateProjection</tt> 
 * method and directly <tt>delete</tt>d.
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
class ExportedByY30E3PMG CATListOfProjectionCrvSur : public CATCGMOperator  
{
  CATCGMVirtualDeclareClass(CATListOfProjectionCrvSur);
  public :
/**
 * Use the <tt>CreateProjection</tt> global method.
 */
    CATListOfProjectionCrvSur (CATGeoFactory * factory);

/**
 * Destructor.
 */
    virtual                      ~CATListOfProjectionCrvSur ();

/**
 * Creates the list of curves on surface and returns the number of PCurves of the list.
 * @return
 * The created list of PCurves table on surface. 
 * A new list of PCurves table is created each time this method is called.
 * If you do not want to keep the created curve, use the @href CATICGMContainer#Remove method.
 */
    virtual CATLONG32                 GetPCurveList           (CATLISTP(CATPCurve)**&) = 0;

    /**
 * Set the tolerance to be used
 */
    virtual void                 SetTolerance            (double) = 0; 

 /**
 * @nodoc
 * Return the Maximum distance of the projected curves to the Surface
 */
    virtual double GetMaxDistanceFromSurface() = 0;
    virtual double GetMaxDistanceFromSurface (CATLONG32 & oCurveIndex)=0;
    virtual double GetMaxDistanceFromSurface (CATLONG32 & oCurveIndex, CATLONG32 & oSurfaceIndex)=0;
};
  
#include "CreateProjection.h"

#endif





