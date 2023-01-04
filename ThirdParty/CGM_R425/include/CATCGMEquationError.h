/* -*-c++-*- */
#ifndef CATCGMEquationError_H
#define CATCGMEquationError_H
#include "CATCGMEquation.h"
#include "CATBaseUnknown.h"
#include "ExportedByCATCGMFusion.h"
#include "CATDataType.h"
//-----------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES 2000
//-----------------------------------------------------------------------------
// Pour une bonne gestion des Equations sur Curve/Pcurve/Surface/Law
// Les Anomalies Severes qui ne sont acceptees dans le mode minimal sont :
//
//  1) Oubli d'ouverture de Lock/OpenEquation
//      Curve    :  GetEquation/GetGlobalEquation          sans Lock ou OpenEquation
//      PCurve   :  GetEquationUV/GetGlobalEquationUV      sans Lock ou OpenEquation
//      Law      :  GetGlobalEquation                      sans Lock ou OpenEquation
//      Surface  :  GetEquation/GetGlobalEquation          sans Lock ou OpenEquation
//
//  2) Oubli de fermeture par Unlock
//
//  3) Non correlation Lock/Unlock --> (par exemple trop de Unlock...)
// 
// On acceptera toutefois les nettoyages d'equations si l'objet est en cours d'effacement
//
//-----------------------------------------------------------------------------
#include "CATCGMBuildDebug.h"
#include "ExportedByCATCGMFusion.h"

class CATCGMObject;
ExportedByCATCGMFusion void CATCXEquationError(const CATCGMObject *iCGMObject,const char context[],char *iFile, int iLine);

#if defined ( CATCGMBuildDebug )
#define CATCGMEquationError(iCGMObject,context)        CATCXEquationError(iCGMObject,context,__FILE__,__LINE__)
#define CATCGMEquationErrorContext(iCGMObject,context) CATCXEquationError(iCGMObject,context,__FILE__,__LINE__)
#else
#define CATCGMEquationError(iCGMObject,context)        CATCXEquationError(iCGMObject,context,NULL,0)
#define CATCGMEquationErrorContext(iCGMObject,context) CATCXEquationError(iCGMObject,context,NULL,0)
#endif

ExportedByCATCGMFusion void CATCGMEquationAddRef(const CATCGMObject *iCGMObject, const void *iDebugUsage=NULL,
														   CATLONG32 ctr=0, const CATULONG32  increment=0);

ExportedByCATCGMFusion void CATCGMEquationRelease(const CATCGMObject *iCGMObject,const void *iDebugUsage=NULL,
															CATLONG32 ctr=0, const CATULONG32  increment=0);

#endif
