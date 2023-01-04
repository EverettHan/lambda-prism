/* -*-C++-*- */

#ifndef CATlsoCSVLine_H
#define CATlsoCSVLine_H
/*
=============================================================================

RESPONSABLE  : PPU7

DESCRIPTION  : To manage Txt Lines

=============================================================================
*/

#include "CATCGMVirtual.h"
#include "PersistentCell.h"
#include "CATCGMHashTable.h"
#include "CATUnicodeString.h"

class CATCGMHashTableWithAssoc;
class CATCGMOutput;
class CATlsoAPRibbonFeatureCondition;
class CATlsoAPCuttingMethodFeatureCondition;

// @nocgmitf (do not create phase 2 interface)
class ExportedByPersistentCell CATlsoTxtLine : public CATCGMVirtual
{
  friend class CATlsoTxtFile;

public:

  // Constructor
  CATlsoTxtLine ();
  CATlsoTxtLine (CATUnicodeString & iLineString);

  // Destructor 
  virtual ~CATlsoTxtLine ();

  CATCGMNewClassArrayDeclare;

  CATlsoTxtLine * GetNextLine () const;
  
  // Casts
  virtual CATlsoAPRibbonFeatureCondition * CastToRibbonFeatureCondition ();
  virtual CATlsoAPCuttingMethodFeatureCondition * CastToCuttingMethodFeatureCondition ();

  void Dump (CATCGMOutput & oStr) const;

protected:
  // Set
  void SetLine (CATUnicodeString & iLineString);
  void SetNextLine (CATlsoTxtLine * iNextLine);

  // Get 
  CATUnicodeString GetLine () const;

private:
  CATlsoTxtLine * _pNextLine;
  CATUnicodeString  _Line;

};

#endif
