#ifndef CATlsoVolumeUtil_H
#define CATlsoVolumeUtil_H

// ++++ Includes ++++
#include "PersistentCell.h"
#include "ListPOfCATCell.h"

// ++++ Predeclarations ++++
class CATCGMStream;
class CATEdge;
class CATGeoFactory;
class CATVolume;
class CATCellHashTable;

//=============================================================================
// CATlsoVolumeUtil
// 
// responsable: VB7
// 
// Classe utilitaire pour l'object CATVolume. Elle ne contient que des methodes
// statiques
//=============================================================================

class ExportedByPersistentCell CATlsoVolumeUtil
{
public:
  //---------------------------------------------------------------------------
  // METHODES STATIC
  //---------------------------------------------------------------------------

  // Stream
  static void StreamVolumeList(const ListPOfCATCell & iVolumeCellList, CATCGMStream& ioStr);
  static void StreamVolumeHT(const CATCellHashTable & iVolumeCellHT, CATCGMStream& ioStr);
  static void StreamVolume(const CATVolume * iVolume, CATCGMStream& ioStr);

  //Unstream
  static void UnStreamVolumeList(ListPOfCATCell & oVolumeList, CATCGMStream& ioStr, CATGeoFactory * iFactory);
  static void UnStreamVolumeHT(CATCellHashTable & oVolumeHT, CATCGMStream& ioStr, CATGeoFactory * iFactory);
  static CATVolume * UnStreamVolume(CATCGMStream& ioStr, CATGeoFactory * iFactory);
};

#endif //CATlsoVolumeUtil_H
