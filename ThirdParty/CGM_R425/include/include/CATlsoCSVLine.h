/* -*-C++-*- */

#ifndef CATlsoCSVLine_H
#define CATlsoCSVLine_H
/*  
=============================================================================

RESPONSABLE  : V. Bouvier

DESCRIPTION  : To manage CSV Lines

=============================================================================
*/

#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATCGMHashTable.h"

class CATCGMHashTableWithAssoc;
class CATUnicodeString;
class CATCGMOutput;

// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATlsoCSVLine : public CATCGMVirtual
{
  friend class CATlsoCSVFile;

public:

  // constructeur a partir d'un CATBody initial, d'un CATTopOperator )
  CATlsoCSVLine(CATUnicodeString & iLineString);

  // destructeur 
  virtual ~CATlsoCSVLine();

  //TCX (pour simplifier la vie AddRef-Release)
  CATCGMNewClassArrayDeclare;

  CATlsoCSVLine * GetNextLine() const;

  int Size() const;
  //iPos From 0 to Size-1
  CATUnicodeString * GetElement(int iPos) const;

  void Dump(CATCGMOutput & oStr) const;

protected:
  void SetNextLine(CATlsoCSVLine * iNextLine);

  //Methods
private:
  void Parsing(CATUnicodeString & iLineString);

  //Data
private:
  CATlsoCSVLine   * _pNextLine;
  CATCGMHashTable   _ElementHT;

};

#endif
