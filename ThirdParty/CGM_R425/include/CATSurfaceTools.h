#ifndef CATSurfaceTools_H
#define CATSurfaceTools_H

// COPYRIGHT DASSAULT SYSTEMES 2005
//
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */

#include "YP00IMPL.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"

class CATSurface;
class CATSurParam;

/**
 * Class to determine the type of a surface as well as its parameters 
 * (radius of a CATFilletSurface for example). 
 * To use it:
 * <ul>
 * <li>Create the CATSurfaceTools object by using its constructor.
 * <li>Use the <tt>Getxxx</tt> methods to retrieve the surface data. 
 * <li>Delete with the usual C++ <tt>delete</tt> operator after use.
 *</ul> 
 */  

class ExportedByYP00IMPL CATSurfaceTools : public CATCGMVirtual
{
public :
  /**
  * Constructor.
  * @param iSurface
  * The surface to be analyzed.
  */
  CATSurfaceTools(CATSurface* iSurface);
  /**
  * Destructor.
  */
  ~CATSurfaceTools();

 /**
 * Determines whether the surface is a CATFilletSurface.
 * If the surface is a CATFilletSurface, determines whether   
 * the radius is constant.
 * @param oHasConstantRadius
 * TRUE if the radius is constant, FALSE otherwise.
 * @return
 * FALSE if the surface is not a CATFilletSurface
 */
  CATBoolean GetConstantRadiusInfo(CATBoolean & oHasConstantRadius);

/**
 * Determines whether the surface is a CATFilletSurface.
 * If the surface is a CATFilletSurface, determines    
 * the radius for a given CATSurParam.
 * @param iParam
 * The CATSurParam which defines the point where the radius is to be computed.
 * @param oRadius
 * The radius.
 * @return
 * FALSE if the surface is not a CATFilletSurface
 */
  CATBoolean GetRadiusAtPoint(const CATSurParam &iParam, double &oRadius);

private:
  // data
  CATSurface* _Surface;

};



#endif

