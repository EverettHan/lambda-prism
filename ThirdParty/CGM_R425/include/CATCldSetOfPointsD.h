//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldSetOfPointsD
//==============================================================================================================
// Creation: JLH - 06-Apr-2000
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldSetOfPointsD_H
#define CATCldSetOfPointsD_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldSetOfPoints.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSetOfPointsD ;
#else
extern "C" const IID IID_CATCldSetOfPointsD ;
#endif

/**
 * CATGeoFactory interface to create a CATCldSetOfPointsD (double).
 * This is a dummy interface to heritate of some general
 * mechanism of the Object Modeler.
 */
class ExportedByCATGMGeometricInterfaces CATCldSetOfPointsD : public CATCldSetOfPoints
{
  CATDeclareInterface ;

public:

} ;

CATDeclareHandler (CATCldSetOfPointsD, CATCldSetOfPoints) ;

#endif
