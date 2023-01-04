/* -*-c++-*- */
//===========================================================================
//
// Jan. 2008   Creation                                            PTO
// 
// Feb. 2019   Modification     QF2 (Heritage protegé) + New methodes.
//
//===========================================================================
#ifndef CATCellManifoldHashTable_H
#define CATCellManifoldHashTable_H

// #include "CATCGMHashTable.h"
#include "CATGeomHashTableBase.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATMathInline.h"
#include "ListPOfCATCellManifold.h"

class CATCellManifold;

/**
*  ** PROTECTED Inheritance ! **
**/
class ExportedByPersistentCell CATCellManifoldHashTable : public CATGeomHashTableBase // protected CATCGMHashTable
{
public:
  // Constructor
  explicit CATCellManifoldHashTable (int iEstimatedSize = 0);
  // Destructor
  virtual ~CATCellManifoldHashTable();
  // constructor from list
  CATCellManifoldHashTable(const ListPOfCATCellManifold &iCellManifoldList);
  // Copy-constructor
  CATCellManifoldHashTable(const CATCellManifoldHashTable & iCellManifoldHT);
  // Surcharge new / delete
  CATCGMNewClassArrayDeclare;

  virtual CATGeometricType GetType() const;


  CATCellManifold * operator[](int iPos) const;
  CATCellManifold * Get(int iPos) const;
  void            * Locate(const CATCellManifold * ipCM) const;
  int               LocateReturnPos(const CATCellManifold * ipCM) const;
  CATCellManifold * KeyLocate(unsigned int iKey) const;   
  CATCellManifold * Next(const CATCellManifold * ipCellManifold) const;

  int   Insert(CATCellManifold * ipCellManifold);
  int   Insert(const ListPOfCATCellManifold & iCMList);
  int   Insert(const CATCellManifoldHashTable & iCMHashTab);

  int   Remove(CATCellManifold * ipCellManifold);
  int   Remove(const ListPOfCATCellManifold   & iCMList);
  int   Remove(const CATCellManifoldHashTable & iCMHashTab);

  using CATGeomHashTableBase::ConvertTo;
  void ConvertTo(ListPOfCATCellManifold &oCellManifoldList) const;

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATGeomHashTableBase & operator =(const CATCellManifoldHashTable & iCellManifoldHT);
  
  // GetAs
  // --------------------------------------------
  virtual CATCellManifoldHashTable * GetAsCellManifoldHT() const;

  // ------------------------------------------------------------------
  // Hash & Compare Function - internal use
  // ------------------------------------------------------------------
  static unsigned int HashKeyFunction(CATCellManifold * ipCM);
  static int CompareFunction(CATCellManifold * ipCM1, CATCellManifold * ipCM2);

private :
  CATDeclarativeManifoldHashTable & operator =(const ListPOfCATCellManifold &iCMList);
};



#endif 
