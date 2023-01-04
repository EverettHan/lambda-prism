// COPYRIGHT DASSAULT SYSTEMES 1997 
//==========================================================================
//
// CATBreakSurface:
// Interface class of the Break Surface Operator.
//
//==========================================================================
//
// Usage notes:
//
//========================================================================== 
// July. 97     Creation                       CEN
//========================================================================== 
//
#ifndef CATBreakSurface_H
#define CATBreakSurface_H
//
#include "CATGMOperatorsInterfaces.h"
#include "CATMathDef.h"
#include "CreateBreakSurface.h"
#include "CATCGMVirtual.h"
#include "CATSkillValue.h"
#include "CATCollec.h"

//
class CATSurface;
class CATSoftwareConfiguration;
class CATCrvLimits;
class CATGeoFactory;
class CATPCurve;
class CATPointOnSurface;
class CATLISTP(CATPCurve );


enum CATKindOfBreakApproximation {MonoPatch=0,KeepInitialSegmentation};


//-----------------------------------------------------------------------------
/**
 *  Class defining the geometric operator that breaks a surface along a CATPCurve.
 *<ul>
 *<li>CATBreakSurface is created with the <tt>CreateBreakSurface</tt> method, but is not streamable. 
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically done. 
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li>The results are accessed thanks to iterators, that allow to handle
 * multiple solutions.
 *</ul>
*/
class ExportedByCATGMOperatorsInterfaces CATBreakSurface  : public CATCGMVirtual
{
  public :

    virtual              ~CATBreakSurface();
	/**
	* Operates.
	*/
    virtual int /*void*/         Run()=0;
 /**
 * Defines the part of the surface that will be computed and kept.
 *<br>To be used for breaking operation with a CATPCurve that is not a CATPline.
 *@param iNoKeepMin
 * <dl><dt><tt>1</tt></dt> <dd> The surface kept is the surface with the minimum (U,V) parameters.
 * <dt><tt>2</tt></dt> <dd> The surface kept is the surface with the maximum (U,V) parameters.
 *</dl>
 */ 
   virtual void           NoKeepSide  (CATLONG32 &iNoKeepMin)=0;
 
/**
 *  Defines the authorized increment of the degree of the resulting surfaces.
 *<br>To be used for breaking operation with a CATPCurve that is not a CATPline.
 *<br>  By default the resulting surfaces have a degree  equal to the one of the initial surface
 * this method enables you to increase the degree of the resulting surfaces  up to 
 *<tt>Initial surface degree + iDelta</tt> in order to better fit the initial shape .
 */
   virtual void           EnableDeltaDegree(CATLONG32 &iDelta)=0;  
   
/**
 *  If Spliting curve is not an isoparametric curve of the surface to be split,
 *  an approximation is done. Default option of this approximation gives mono-patch
 *  results (iMode=MonoPatch). Else you can ask to keep the initial segmentation (iMode
 *  =KeepInitialSegmentation). Only patch limits in the direction of split which are
 *  not crossed by the spliting curve will be kept. Note that no arcs can be smaller
 *  than input tolerance (default tolerance is 0.03mm).
 */
   virtual void           SetApproximationMode(CATKindOfBreakApproximation iMode)=0;  

  /**
  * Defines the tolerance between the initial and final shapes.
  *<br>To be used for breaking operation with a CATPCurve that is not a CATPline.
  *<br>This is just to give a deviation order
  */  
   virtual void           SetTolerance(double &Tol)=0;   
      
/** 
 * Defines the limits of the PCurve.
 */  
  virtual void SetPCurveLimits(CATCrvLimits * iPCLimits) = 0;

/** 
 * Returns the number of resulting surfaces.
 */
    virtual CATLONG32         GetNumberOfBreakSurfaces()          const=0;

/**
 * Initializes the iterator of the resulting surfaces.
 */
    virtual void         BeginningBreakSurface()                  =0;

/**
 * Skips to the next resulting surface.
 */
    virtual CATBoolean   NextBreakSurface()                       =0;

/** 
* Creates a resulting surface.
*/
    virtual CATSurface * GetBreakSurface()                   const=0;

/**
 * Modifies an already existing surface to be a result of the operator.
 
    virtual void         SetGlobalBreakSurface(CATSurface *) = 0;
*/
/**
 *@nodoc
 *Deprecated
 */
 virtual void RelaxTangencyImposition(short,short)=0;

/**
 * Disconnect the tangency imposition along the breaking P-Curve
 */
 virtual void RelaxTangencyImposition()=0;
};

#endif
