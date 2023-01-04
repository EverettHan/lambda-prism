/**
 * @COPYRIGHT DASSAULT SYSTEMES 2002
 */
/* -*-c++-*- */
//=============================================================================
//
// Classe representant une liste d'objets de meme CATGeometricType
//
// Feb. 02  Creation                                                      HCN
// Jul. 02  Passage du parametre de GetVision de
//          CATICGMObject en CATICGMUnknown pour le cas des
//          CATGeoFactory                                                 HCN
// Jul. 02  Deplacement de CATCGMV5Interoperability vers
//          GeometricObjectsCGM                                           HCN
// Dec. 03  Parametre CATLISTP(CATICGMObject)* pour GetVision(...)        HCN
//=============================================================================
#ifndef CATGeometricTypeEntry_H
#define CATGeometricTypeEntry_H

#include "ExportedByCATCGMFusion.h"
#include "CATCGMNewArray.h"
#include "CATGeometryType.h"
#include "CATListOfCATGeometricTypeEntry.h"
#include "CATListOfCATICGMObjects.h"
#include "CATListOfCATICGMUnknowns.h"
#include "CATDataType.h"

class CATHashTabCATGeometricTypeEntry;


class ExportedByCATCGMFusion CATGeometricTypeEntry
{
public:
  CATGeometricTypeEntry(CATGeometricType iType);
  ~CATGeometricTypeEntry();
  
  static void GetVision(CATICGMUnknown*                   ipICGMUnknown,
                        CATHashTabCATGeometricTypeEntry*& ioHTGeoTypes,
                        CATLISTP(CATGeometricTypeEntry)*& ioListOfGeoTypes,
                        CATLISTP(CATICGMObject)*          ipPreCalculatedAllLinks = NULL);

  const char * TypeName();
  int  IsATypeOf(CATGeometricType iTypeReference) const;

  CATGeometricType         _Type;
  CATLISTP(CATICGMUnknown) _Instances;
  CATULONG32             _Cumulated;

  CATCGMNewClassArrayDeclare;
};



#endif
