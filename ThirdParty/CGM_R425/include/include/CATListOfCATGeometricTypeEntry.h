/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//=============================================================================
//
// Classe representant une liste de pointeurs vers des CATGeometricTypeEntry
//
// Feb. 02  Creation                                              HCN
// Jul. 02  Deplacement de CATCGMV5Interoperability vers
//          GeometricObjectsCGM                                   HCN
//=============================================================================

#ifndef CATListOfCATGeometricTypeEntry_H
#define CATListOfCATGeometricTypeEntry_H

#include "ExportedByCATCGMFusion.h"

class CATGeometricTypeEntry;

#include "CATCGMLISTP_Declare.h"

CATCGMLISTP_DECLARE(CATGeometricTypeEntry);

ExportedByCATCGMFusion int CGMTypeSortByName(CATGeometricTypeEntry* i1, CATGeometricTypeEntry *i2);
ExportedByCATCGMFusion int CGMTypeSortByNumberOfObjects(CATGeometricTypeEntry* i1, CATGeometricTypeEntry *i2);
ExportedByCATCGMFusion int CGMTypeSortByCumulated(CATGeometricTypeEntry* i1, CATGeometricTypeEntry *i2);


#endif
