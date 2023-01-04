/* -*-c++-*- */
//===========================================================================
//
// Jan. 2010   Creation                                            PTO
//
// Feb. 2019   Modification     QF2 (Heritage protegé) + New methodes.
//
//===========================================================================
#ifndef CATCellManifoldGroupHashTable_H
#define CATCellManifoldGroupHashTable_H

#include "CATGeomHashTableBase.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATMathInline.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATCellManifoldGroup;

class ExportedByPersistentCell CATCellManifoldGroupHashTable :  public CATGeomHashTableBase // public CATCGMHashTable
{
public:
  // Constructor
  explicit CATCellManifoldGroupHashTable (int iEstimatedSize = 0);
  // constructor from list
  CATCellManifoldGroupHashTable(const ListPOfCATCellManifoldGroup & iCMGroupList);
  // Copy-constructor
  CATCellManifoldGroupHashTable(const CATCellManifoldGroupHashTable & iCMGroupHT);
  // Destructor 
  virtual ~CATCellManifoldGroupHashTable();
  // Surchage du new et du delete
  CATCGMNewClassArrayDeclare;
    
  virtual CATGeometricType GetType() const;

  // --------------------------------------------
  // Basic Access
  // --------------------------------------------
  CATCellManifoldGroup * operator[](int iPos) const;    
  CATCellManifoldGroup * Get(int iPos)        const;
  void                 * Locate(const CATCellManifoldGroup * ipCMGroup) const;
  CATCellManifoldGroup * KeyLocate(unsigned int iKey) const; 
  CATCellManifoldGroup * Next(const CATCellManifoldGroup * ipCMGroup)   const;
  int                    LocateReturnPos(const CATCellManifoldGroup* ipCMGroup) const;

  // Insert / Remove
  // --------------------------------------------
  int   Insert(CATCellManifoldGroup * ipCMGroup);
  int   Insert(const ListPOfCATCellManifoldGroup & iCMGroupList);
  int   Insert(const CATCellManifoldGroupHashTable & iCMGroupHT);

  int   Remove(CATCellManifoldGroup * ipCMGroup);
  int   Remove(const ListPOfCATCellManifoldGroup   & iCMGroupList);
  int   Remove(const CATCellManifoldGroupHashTable & iCMGroupHT);

  // Convert
  // -------------------------------------------
  using CATGeomHashTableBase::ConvertTo;
  void  ConvertTo(ListPOfCATCellManifoldGroup & oCMGroupList) const;

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATGeomHashTableBase & operator =(const CATCellManifoldGroupHashTable & iCMGroupHT);
  
  // GetAs
  // --------------------------------------------
  virtual CATCellManifoldGroupHashTable * GetAsCMGroupHT() const;

private: 
  static unsigned int HashKeyFunction(CATCellManifoldGroup * ipElem);
  static int CompareFunction(CATCellManifoldGroup * ipElem1, CATCellManifoldGroup * ipElem2);

  // Forbiden 
  CATCellManifoldGroupHashTable & operator =(ListPOfCATCellManifoldGroup & iCMGroupHT);
};



#endif 
