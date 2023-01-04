#ifndef CATTessScan_h
#define CATTessScan_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATTessScan.
 */
#include "CATTessClay.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATTessScan ;
#else
extern "C" const IID IID_CATTessScan ;
#endif


class ExportedByCATGMGeometricInterfaces CATTessScan : public CATTessClay
{
  CATDeclareInterface;

public:

  
};
CATDeclareHandler(CATTessScan,CATTessClay);

#endif
