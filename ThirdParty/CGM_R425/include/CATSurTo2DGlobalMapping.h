#ifndef CATSurTo2DGlobalMapping_H
#define CATSurTo2DGlobalMapping_H
// COPYRIGHT DASSAULT SYSTEMES 1997

/**
 * @level Protected
 * @usage U1
 */

#include "Connect.h"
 
#include "CATIAV5Level.h"
#include "CATCGMVirtual.h"


#include "CATCGMOperator.h"
#include "CATSurTo2DMapping.h"
#include "CATCGMStream.h"
#include "CATString.h"
#include "CATCGMVirtual.h"


class CATSurface;  
class CATMathAxis;  
class CATSurLimits;
class CATSoftwareConfiguration;
  
/**
 * Class defining a consistant global mapping between a set of CATSurface and a
 * virtual  2 dimension space.
 * <br>This class is the base class for some supplied operators 
 * such as @href CATSurTo2DGlobalPlanarMapping,
 * but you must not derive it yourself.
 * <br>All global computations are done once when constructing the CATSurTo2DGlobalMapping.
 */
class ExportedByConnect CATSurTo2DGlobalMapping : public CATCGMOperator
{
  CATCGMVirtualDeclareClass(CATSurTo2DGlobalMapping);
public :
	/**
      * @nodoc
      */
	CATSurTo2DGlobalMapping(CATGeoFactory *iFactory);

    CATSurTo2DGlobalMapping(CATGeoFactory *iFactory,CATSoftwareConfiguration * iConfig);

	virtual ~CATSurTo2DGlobalMapping();

  
	 /**
      * @nodoc
      */
  virtual CATSoftwareConfiguration* GetSoftwareConfiguration() const;


	 /**
      * @nodoc
      */
	virtual CATSurTo2DMapping *  CreateLocalMapping(CATSurface * iLocalReference ,
		const double & iRefOrientation,
		const CATSurLimits &iRefLimits) const = 0;
    
	/**
      * @nodoc
      */
	virtual void RemoveLocalMapping(CATSurTo2DMapping * iLocalMapping ) ;
	
    /**
    * @nodoc
    */
    void Stream(CATCGMStream& Str, const char iLabelReserved[] = "" ) const;

    /**
    * @nodoc
    */   
    static void UnStream(CATCGMStream& Str, CATGeoFactory* iFactory, CATSurTo2DGlobalMapping *&oMapping, const char iLabelReserved[] = ""  );

	//----------------------
	// Set and Get Methods 
	//----------------------  

protected :
	
    /**
    * @nodoc
    */   
    virtual void GetCreatorId(CATString& oCreatorId, CATString& oSharedLibId) const;
	    
    /**
    * @nodoc
    */   
	virtual void Write(CATCGMStream& Str) const;

	/**
      * @nodoc
      */
	CATGeoFactory * _Factory;

private :
  CATSoftwareConfiguration * _Config;

};
#endif

