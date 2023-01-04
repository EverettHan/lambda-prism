#ifndef CATCGMCockpitTable_h
#define CATCGMCockpitTable_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
#include "CATCGMCockpit.h"

#include "CATSysSimpleHashTable.h"
#include "CATListOfCATCGMCockpit.h"
 
class CATCGAreport_Measures;
class CATCGAMeasureGlobal;

//------------------------------------------------------------------------
// CATCGMCockpitTable
//------------------------------------------------------------------------
class  ExportedByCATMathematics  CATCGMCockpitTable : protected CATSysSimpleHashTable
{
public:
  CATCGMNewClassArrayDeclare;


  /** @nodoc */
  CATCGMCockpitTable(int  iCSIDepth, int dim=4096);

  /** @nodoc */
  ~CATCGMCockpitTable();

  /** @nodoc */
  int                  Insert(CATCGMCockpit & iLocation);
  
  /** @nodoc */
  CATCGMCockpit      * Locate(CATCGMCockpit & iLocation) const;

  /** @nodoc */
  CATCGMCockpit      * GetByIndex(CATULONG32 iIndex) const;

  INLINE CATULONG32    GetNumberOfIndex() const ;      

  /** @nodoc */
  void ApplyDelete();

  CATLISTP(CATCGMCockpit) _TableIndex;


  /** @nodoc */
  void Insert(CATCGAreport_Measures & iMeasure );
 
  int              _CSIDepth; // Filter for Local HashTable HT

protected :

  // IndexTable
  CATULONG32       _Counter;

private:

  friend class CATCGAMeasure;
	friend class CATCGAMeasureGlobal;

  /** @nodoc */
  CATCGMCockpitTable(const CATCGMCockpitTable&);

  /** @nodoc */
  CATCGMCockpitTable& operator=(const CATCGMCockpitTable&);
};


INLINE CATULONG32 CATCGMCockpitTable::GetNumberOfIndex() const
{ return (CATULONG32) this->CATSysSimpleHashTable::Size(); }     



#endif
