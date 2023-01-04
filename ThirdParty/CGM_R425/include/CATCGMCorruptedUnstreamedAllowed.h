/* -*-c++-*- */
#ifndef CATCGMCorruptedUnstreamedAllowed_H_
#define CATCGMCorruptedUnstreamedAllowed_H_
// COPYRIGHT DASSAULT SYSTEMES  2000
//============================================================================
//   June. 00  Creation.       TYCX
//
//   -->  Dedicated to internal Use Only of Checker Behavior (ODT only)
//
//  We can increase requirements in Quality of genererated Geometry,
//    but we must also manage data generated with older Product,
//    we must allowed such bad old modelisation as input of our operators.
//
//  This service allows you to explicitly identify Input Geometry
//    which must not be taken into account in Factory Check()
//
//
// 08/11/07 NLD Ajout CATCGMCorruptedAllowedRestrictedUse()
//              pour XScale. (gestion des elements transformes a la lecture du modele)
//============================================================================
#include "ExportedByCATTopologicalObjects.h"

#include <CATBoolean.h>
class CATICGMObject;

extern "C" ExportedByCATTopologicalObjects void CATCGMCorruptedUnstreamedAllowed(CATICGMObject *object);

#endif
