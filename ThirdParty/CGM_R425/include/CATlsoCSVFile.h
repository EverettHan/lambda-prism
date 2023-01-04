/* -*-C++-*- */

#ifndef CATlsoCSVFile_H
#define CATlsoCSVFile_H
/*  
=============================================================================

RESPONSABLE  : V. Bouvier

DESCRIPTION  : To manage Reading/Writing on CSV Files

=============================================================================
*/

#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATListOfCATUnicodeString.h"

class CATCGMHashTableWithAssoc;
class CATUnicodeString;
class CATlsoCSVLine;
class CATCGMOutput;

// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATlsoCSVFile : public CATCGMVirtual
{

public:

  // constructeur a partir d'un CATBody initial, d'un CATTopOperator )
  CATlsoCSVFile(CATUnicodeString & iFileURL);

  CATlsoCSVFile(CATListOfCATUnicodeString & iLineList);

  // destructeur 
  virtual ~CATlsoCSVFile();

  //TCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  CATlsoCSVLine * Next(CATlsoCSVLine * iCurrentCSVLine = NULL) const;

  void Dump(CATCGMOutput & oStr) const;

  //Methods
private:
  void Parsing(CATUnicodeString & iFileURL);
  void Parsing(CATListOfCATUnicodeString & iLineList);
  void CreateOneLineFromUnicodeString(CATUnicodeString & lineUS, CATlsoCSVLine *& ioPreviousLine);

  //Data
private:
  CATlsoCSVLine   * _pFirstLine;
  CATlsoCSVLine   * _pLastLine;
};

#endif
