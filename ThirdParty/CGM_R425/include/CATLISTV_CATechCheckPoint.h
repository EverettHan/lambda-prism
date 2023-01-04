
#ifndef CATLISTV_CATechCheckPoint_H_
#define CATLISTV_CATechCheckPoint_H_

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */

#include "ExportedByCATTechTools.h"

class CATechCheckPoint;
 
/** ------------------------------------------------------------------------
 *                  CATechCheckPoint
 ------------------------------------------------------------------------ */

#include "CATLISTV_Clean.h"

#define  CATLISTV_Append

#include "CATLISTV_Declare.h"
 

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATTechTools

CATLISTV_DECLARE(CATechCheckPoint)


typedef CATLISTV(CATechCheckPoint) CATechCheckPoints;

 
#endif
