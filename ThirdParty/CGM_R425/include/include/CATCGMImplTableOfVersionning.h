#ifndef CATCGMImplTableOfVersionning_h
#define CATCGMImplTableOfVersionning_h
// COPYRIGHT DASSAULT SYSTEMES  1999
//----------------------------------------------------------------------------------------------
// Pour l'implementation de la Table de correspondance de l'affectation des Levels
//----------------------------------------------------------------------------------------------
#include "ExportedByCATMathStream.h"
#include "CGMVersionDebug.h"
class CATHashDico;

class ExportedByCATMathStream CATCGMImplTableOfVersionning
{
  // Look up
public:
  static short GetCurLevel(const char *variableName);
  static short SetCurLevel(const char *pVersion, short newLevel);
  static short ResetLevel(const char *pVersion);
  static void  ResetAllLevel();
  static short EndOfTable();

  static CGMVersionCore * GetTuples(int & NbTuples, CATHashDico ** ByName );

};

#endif
