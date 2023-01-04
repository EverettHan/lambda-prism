#ifndef CATGeometrySubdType_H
#define CATGeometrySubdType_H
// COPYRIGHT DASSAULT SYSTEMES 2001
//=====================================================================================
//
// Auteurs: TCX   
// Date: 13/02/2002
//
// Description: Determine si un Type geometrique est une specialisation d'un autre
//
//=====================================================================================

#include "CATGeometricObjects.h"
#include "CATGeometryType.h"
#include "CATBoolean.h"

extern ExportedByCATGeometricObjects CATBoolean CATGeometrySubdType(CATGeometricType iSubType, 
                                                                    CATGeometricType iSuperType);


#endif
