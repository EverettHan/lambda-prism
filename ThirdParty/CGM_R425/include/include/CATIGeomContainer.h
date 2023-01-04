#ifndef CATIGeomContainer_h
#define CATIGeomContainer_h


// COPYRIGHT DASSAULT SYSTEMES 1999

//class CATISolidContainer;

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATIGeomContainer ;
#else
extern "C" const IID IID_CATIGeomContainer ;
#endif
/**
 * CXR1 implementation only, do not use in CXR2.
 */
#include "CATBaseUnknown.h"
class ExportedByCATGMGeometricInterfaces CATIGeomContainer : public CATBaseUnknown
{
  CATDeclareInterface;
    
public:

  virtual void InitGes()=0 ;
  virtual CATIGeomContainer* CreateSolidContainer()=0 ;
    
};


CATDeclareHandler( CATIGeomContainer, CATBaseUnknown ) ;

#endif
