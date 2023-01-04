/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//=============================================================================
//
// Table de hashage utilisee pour trier les CATGeometry d'un CATCGMObject
// suivant leur CATGeometricType
//
// Feb. 02  Creation                                              HCN
// Jul. 02  Deplacement de CATCGMV5Interoperability vers
//          GeometricObjectsCGM                                   HCN
//=============================================================================

#ifndef CATHashTableOfCATGeometricTypeEntry_H
#define CATHashTableOfCATGeometricTypeEntry_H

class CATGeometricTypeEntry;

#include "CATHTAB_Clean.h"
#define CATHTAB_Insert
#define CATHTAB_Locate
#define CATHTAB_PrintAddr
#define CATHTAB_PrintStats
#define CATHTAB_Remove
#define CATHTAB_RemoveAll
#define	CATHTAB_ApplyDelete
#define	CATHTAB_KeyLocate

#include "CATHTAB_Declare.h"

#include "ExportedByCATCGMFusion.h"

#undef  CATCOLLEC_ExportedBy
#define CATCOLLEC_ExportedBy ExportedByCATCGMFusion

CATHTAB_DECLARE( CATGeometricTypeEntry )


ExportedByCATCGMFusion unsigned int HashKeyCATGeometricTypeEntry(CATGeometricTypeEntry* inew);
ExportedByCATCGMFusion int CompareCATGeometricTypeEntry(CATGeometricTypeEntry* i1, CATGeometricTypeEntry *i2);



#endif
