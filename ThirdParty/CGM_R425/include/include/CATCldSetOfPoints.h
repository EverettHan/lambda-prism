//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldSetOfPoints
//==============================================================================================================
// Creation: JLH - ??-???-1999
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldSetOfPoints_H
#define CATCldSetOfPoints_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATGeometry.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSetOfPoints ;
#else
extern "C" const IID IID_CATCldSetOfPoints ;
#endif

/**
 * CATGeoFactory interface to create a CATCldSetOfPoints.
 * This is a dummy interface to heritate of some general
 * mechanism of the Object Modeler.
 */
class ExportedByCATGMGeometricInterfaces CATCldSetOfPoints : public CATGeometry
{
  CATDeclareInterface ;

public:

} ;

CATDeclareHandler (CATCldSetOfPoints, CATGeometry) ;

#endif
