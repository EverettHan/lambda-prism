
/* -*-c++-*-*/
// COPYRIGHT DASSAULT SYSTEMES 1998 
//==========================================================================
//
// CATIdenticalSurSur:
// Abstract class of the identity of two surfaces. 
/**
 * Interface representing the operator for testing if two surfaces are 
 * identical.
 *<li>It is created with the <tt>CreateIdentical</tt>
 *<li>In case of <tt>BASIC</tt>
 * mode, the operation is automatically performed. 
 *<li>In case of <tt>ADVANCED</tt>
 * mode, the user may precise options with the <tt>SetXxx</tt> methods, before
 * asking for the computation with the <tt>Run</tt> method.
 *<li> The operator is removed from the memory with the <tt>Remove</tt> method.
 *</ul>
 */
//
//==========================================================================
//
// Usage notes:
// You may use this operator to find if two surface are identical before
// trying to intersect them.
//
//========================================================================== 
// May. 98     Creation                       P. Sebah
//========================================================================== 

#ifndef CATIdenticalSurSur_H
#define CATIdenticalSurSur_H

#include "Y30C3XGG.h"
#include "CATMathDef.h"
#include "CATGeoOperator.h"
#include "CATCreateIdentical.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATSurface;
class CATSurLimits;
class CATMathTransformation2D;

//-----------------------------------------------------------------------------
class ExportedByY30C3XGG CATIdenticalSurSur : public CATGeoOperator
{    
  CATCGMVirtualDeclareClass(CATIdenticalSurSur);
  public:
/**
 * Destructor.
 */
    virtual ~CATIdenticalSurSur();
/**
 * Destructor.
 */
    CATIdenticalSurSur(CATGeoFactory * iFactory);

/**
 * Set the surfaces 
 * Note : 
 * - This service is to be used to reuse the same operator with different surfaces.
 * - If called , it has to be called before any other service ( before "HoldDomain" for exemple ).
 */
    virtual void SetSurfaces (CATSurface *iSurface1, CATSurface *iSurface2) =0;
 

/**
 * Set the domains on each surface in <tt>ADVANCED</tt> mode.
 */
    virtual void HoldDomain (const CATSurLimits *iLimit1, const CATSurLimits *iLimit2) =0;
 

/**
 * Returns 1 if the two surfaces are identical and 0 otherwise.
 */
    virtual CATBoolean GetIdentity() const =0;  	

/**
 * Returns 1 if the two surfaces are identical with same normals and -1
 * if the normals are opposite.
 */
    virtual CATLONG32 GetNormalOrientation() const =0;

/**
 * Returns the change of mapping between the surface 1 and 2.
 */
    virtual void GetMapping12(CATMathTransformation2D * &oTransfo2D) =0;

/**
 * Returns the change of mapping between the surface 2 and 1.
 */
    virtual void GetMapping21(CATMathTransformation2D * &oTransfo2D) =0;

/**
 * Filter the surfaces to be tested based on a logical criterion
 * This service is done for performance purpose to avoid unecessary operator creation
 * Return TRUE if the 2 surfaces can not be identical ( in this case the operator has not to be created )
 * Return FALSE if the 2 surfaces may be identical ( in this case the operator has to be created )
 */
	static CATBoolean FilterSurfacesToTestTested (  CATSurface *iSurface1, CATSurface *iSurface2 );

};


#endif
