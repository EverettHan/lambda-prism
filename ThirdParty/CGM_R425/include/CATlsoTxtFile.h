/* -*-C++-*- */

#ifndef CATlsoTxtFile_H
#define CATlsoTxtFile_H
/*
=============================================================================

RESPONSABLE  : PPU7

DESCRIPTION  : To manage Reading/Writing on Txt Files

=============================================================================
*/

#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATListOfCATUnicodeString.h"

class CATUnicodeString;
class CATCGMOutput;
class CATlsoTxtLine;

class ExportedByPersistentCell CATlsoTxtFile : public CATCGMVirtual
{

public:
  // Constructor
  CATlsoTxtFile ();

  // Destructor 
  virtual ~CATlsoTxtFile ();

  //TCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  CATlsoTxtLine * Next (CATlsoTxtLine * iCurrentCSVLine = NULL) const;

  void Parsing (CATUnicodeString & iFileURL);
  void Parsing (CATListOfCATUnicodeString & iLineList);

  void Dump (CATCGMOutput & oStr) const;

protected:
  virtual CATlsoTxtLine * CreateOneLine (CATUnicodeString & iLineUS);

private:
  void InitializeUnicodeStringFromCharWithoutEndLine (const char* const iString, const int iLength, CATUnicodeString & ioUnicodeString);
  void CreateOneLineFromUnicodeString (CATUnicodeString & iLineUS, CATlsoTxtLine *& ioPreviousLine);

  //Data
private:
  CATlsoTxtLine * _pFirstLine;
  CATlsoTxtLine * _pLastLine;
};

#endif
