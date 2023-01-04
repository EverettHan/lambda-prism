//==============================================================================================================
// COPYRIGHT DASSAULT SYSTEMES PROVENCE 1999
//==============================================================================================================
// CATCldSetOfPointsF
//==============================================================================================================
// Creation: JLH - 06-Apr-2000
// 24-03-2014 CGMOFF+CGMPRJ
//==============================================================================================================

#ifndef CATCldSetOfPointsF_H
#define CATCldSetOfPointsF_H

/**
 * @CAA2Level L0
 * @CAA2Usage U0
 */ 

#include "CATCldSetOfPoints.h"

#include "ExportedByCATGMGeometricInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMGeometricInterfaces IID IID_CATCldSetOfPointsF ;
#else
extern "C" const IID IID_CATCldSetOfPointsF ;
#endif

/**
 * CATGeoFactory interface to create a CATCldSetOfPointsF (float).
 * This is a dummy interface to heritate of some general
 * mechanism of the Object Modeler.
 */
class ExportedByCATGMGeometricInterfaces CATCldSetOfPointsF : public CATCldSetOfPoints
{
  CATDeclareInterface ;

public:

} ;

CATDeclareHandler (CATCldSetOfPointsF, CATCldSetOfPoints) ;

#endif
