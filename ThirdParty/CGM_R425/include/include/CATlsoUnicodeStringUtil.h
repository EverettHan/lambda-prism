#ifndef CATlsoUnicodeStringUtil_H
#define CATlsoUnicodeStringUtil_H

//=============================================================================
// CATlsoUnicodeStringUtil
// 
// responsable: PPU7
// 
//   Classe utilitaire pour l'object CATUnicodeString.
// Ne contient que des methodes statiques.
//=============================================================================

#include "PersistentCell.h"
#include "CATUnicodeString.h"
#include "CATListOfCATUnicodeString.h"

class ExportedByPersistentCell CATlsoUnicodeStringUtil
{

public:

  // returns TRUE if iSeparator was found in iStringToSeparate
  // Output oSeparatedString contains the separated CATUnicodeString using iSeparator.
  static CATBoolean Separate (CATUnicodeString & iStringToSeparate, CATUnicodeString & iSeparator, CATListOfCATUnicodeString & oSeparatedString);

};

#endif

