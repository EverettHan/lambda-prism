#ifndef CATTessCloud_h
#define CATTessCloud_h

// COPYRIGHT DASSAULT SYSTEMES 1999

/**
 * CATGeoFactory interface to create a CATTessCloud.
 */
#include "CATTessClay.h"
#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATTessCloud ;
#else
extern "C" const IID IID_CATTessCloud ;
#endif


class ExportedByCATGMGeometricInterfaces CATTessCloud : public CATTessClay
{
  CATDeclareInterface;

public:

};
CATDeclareHandler(CATTessCloud,CATTessClay);

#endif
