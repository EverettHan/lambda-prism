#ifndef CATSurTo2DGlobalPlanarMapping_H
#define CATSurTo2DGlobalPlanarMapping_H 

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * @level Protected
 * @usage U1
 */

#include "CATCreateSurTo2DCanonicalMapping.h"
#include "CATSurTo2DGlobalMapping.h"
#include "CATMathAxis.h" 

class CATSurLimits;
 

/**
 * Class defining the mapping between one set of surfaces and a
 * virtual  2 dimension space defined by an axis.
 * CATSurTo2DGlobalPlanarMapping is created with the @href CreatePlanarMapping
 * global function and deleled with the usual C++ <tt>delete</tt> operator.
 */
class CATSurTo2DGlobalPlanarMapping: public CATSurTo2DGlobalMapping
{ 
  CATCGMVirtualDeclareClass(CATSurTo2DGlobalPlanarMapping);
public :
	/**
      * @nodoc
      */
	CATSurTo2DGlobalPlanarMapping(CATGeoFactory *iFactory,const CATMathAxis &iAxis);
  
//#ifdef CATIAV5R13
  /**
   * @nodoc
   * Constructor - NOT TO BE USED
   */
   CATSurTo2DGlobalPlanarMapping(CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig,const CATMathAxis &iAxis);
//#endif	
	~CATSurTo2DGlobalPlanarMapping();
	/**
      * @nodoc
      */
	CATSurTo2DMapping *  CreateLocalMapping(CATSurface * iLocalReference ,
		const double & iRefOrientation,
		const CATSurLimits &iRefLimits) const; 

protected :

   /**
   * @nodoc
   */   
   virtual void GetCreatorId(CATString& oCreatorId, CATString& oSharedLibId) const;

   /**
   * @nodoc
   */   
   virtual void Write(CATCGMStream& Str) const;


private :
	
	/**
      * @nodoc
      */
	const CATMathAxis _Axis; 
	
};
#endif
