#ifndef CATPointOnSurface_h
#define CATPointOnSurface_h

// COPYRIGHT DASSAULT SYSTEMES  1999

/**
 * @CAA2Level L1
 * @CAA2Usage U3
 */ 

#include "CATBaseUnknown.h"
#include "CATPoint.h"
class CATSurParam ;
class CATSurface ;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATPointOnSurface ;
#else
extern "C" const IID IID_CATPointOnSurface ;
#endif

  //CAA_Exposed CATIGemPointOnSurface
/** 
 * Interface representing a point lying on a surface.
 * <br><b>Role</b>: A CATPointOnSurface can be seen as 2 coordinates (called surface parameter) in the space of
 * the surface.
 *<br>A CATPointOnSurface is created through the <tt>CreatePointOnSurface</tt>
 * method of the <tt>CATGeoFactory</tt> interface  and deleted with the <tt>Remove</tt> method.
 */
class ExportedByCATGMGeometricInterfaces CATPointOnSurface : public CATPoint
{
  CATDeclareInterface;

public:
    //CAA_Exposed 
/**
 * Returns the corresponding parameter on the surface.
 * @param ioParam
 * The parameter.
 */
  virtual void GetParam(CATSurParam & ioParam ) const = 0 ;

/**
 * Modifies the parameter of <tt>this</tt> CATPointOnSurface.
 * @param iNewParam
 * The new parameter.
 */
  virtual void SetParam ( const CATSurParam & iNewParam ) = 0 ;

    //CAA_Exposed 
/**
 * Returns the underlying CATSurface of <tt>this</tt> CATPointOnSurface.
 * @return
 * A pointer to the surface.
 */ 
  virtual CATSurface* GetSurface( ) const = 0 ;
 
/**
 * Modifies the underlying CATSurface of </tt>this</tt> CATPointOnSurface.
 * @param iNewSupport
 * A pointer to the new surface.
 */ 
  virtual void SetSurface( CATSurface* iNewSupport ) = 0 ;



/** @nodoc */
  virtual CATSurParam GetParam( ) const = 0 ;

};

CATDeclareHandler(CATPointOnSurface,CATPoint);

#endif
