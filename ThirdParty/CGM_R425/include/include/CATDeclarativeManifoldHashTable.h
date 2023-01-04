/* -*-c++-*- */
//===========================================================================
//
// Jan. 2008   Creation                                            PTO
// 
// May  2019   Refonte/Derivation                                  QF2
//
//===========================================================================
#ifndef CATDeclarativeManifoldHashTable_H
#define CATDeclarativeManifoldHashTable_H

#include "CATGeomHashTableBase.h"
#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATMathInline.h"

class CATDeclarativeManifold;
class CATLISTP(CATDeclarativeManifold);

// --------------------------------------------------------------------------------
// class CATDeclarativeManifoldHashTable - Instantiable
// --------------------------------------------------------------------------------
class ExportedByPersistentCell CATDeclarativeManifoldHashTable : public CATGeomHashTableBase // idee : virtual + virtual protected CATGeometryHTab, 
{  
 /**
  * -----------------------------------------------------------------------------------------------------------------------------------------------------
  *  Idee:
  *    Si on veut deriver cette classe de CATGeometryHTab pour plus de souplesse, on peut utiliser l'heritage virtuel.
  *    Faire comme suit :
  *      CATGeomHashTableBase : virtual protected CATCGMHashTable
  *      CATGeometryHTable     : virtual public    CATGeomHashTableBase
  *      CATDeclManifoldHashTable : virtual public CATGeomHashTableBase, virtual protected CATGeometryHTab
  *      ( heritage multiple safe)
  *   
  *  De maniere generale, c'est un cas typique d'heritage virtuel, l'encapsulation mémoire de dérivation est purement inutile pour ce type de classes.
  *  To do : Integrer CATCellManifoldHashTable à cette architecture.
  * -----------------------------------------------------------------------------------------------------------------------------------------------------
  */
public:
  // Constructor
  explicit CATDeclarativeManifoldHashTable (int iExpectedSize=0, LSOHashKeyFunction ipHashKeyFunction=CATGeomHashTableBase::HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CATGeomHashTableBase::CompareGEO_Function);
  // constructor from list
  CATDeclarativeManifoldHashTable(const CATLISTP(CATDeclarativeManifold) &iDMList, LSOHashKeyFunction ipHashKeyFunction=CATGeomHashTableBase::HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CATGeomHashTableBase::CompareGEO_Function);
  // Copy-constructor
  CATDeclarativeManifoldHashTable(const CATDeclarativeManifoldHashTable & iDeclManifoldHT);
  // Destructor
  virtual ~CATDeclarativeManifoldHashTable();
  // surcharge du new et du delete
  CATCGMNewClassArrayDeclare;  

  virtual CATGeometricType GetType() const;

   // Basic Access
  // --------------------------------------------
  CATDeclarativeManifold * operator[](int iPos) const;    
  CATDeclarativeManifold * Get(int iPos)        const;
  void                   * Locate(CATDeclarativeManifold * ipDeclManifold) const;
  CATDeclarativeManifold * KeyLocate(unsigned int iKey) const; 
  CATDeclarativeManifold * Next(CATDeclarativeManifold * ipDeclManifold)   const;
  int                      LocateReturnPos(CATDeclarativeManifold* ipDeclManifold) const;

  // Insert / Remove
  int Insert(CATDeclarativeManifold* ipDeclarativeManifold);
  int Insert(const CATLISTP(CATDeclarativeManifold) &iDMList);
  int Insert(const CATDeclarativeManifoldHashTable  &iDManifoldHT);

  int Remove(CATDeclarativeManifold* ipDeclarativeManifold);
  int Remove(const CATLISTP(CATDeclarativeManifold) &iDMList);
  int Remove(const CATDeclarativeManifoldHashTable  &iDManifoldHT);

  // ---------------------------------------------------------------
  // ConvertTo
  // ---------------------------------------------------------------
  using CATGeomHashTableBase::ConvertTo;
  void  ConvertTo(CATLISTP(CATDeclarativeManifold) &oDeclManifoldList) const;

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATGeomHashTableBase & operator =(const CATDeclarativeManifoldHashTable & iDeclManifoldHT);

  // GetAs
  // --------------------------------------------
  virtual CATDeclarativeManifoldHashTable * GetAsDeclarativeHT() const;

  // CastTo 
  // -------------------------------------------
  const CATGeomHashTableBase & CastToGeometryHT() const; // safe

  
  /*static unsigned int HashKeyFunction(void* ipElem);
  static int CompareFunction(void* ipElem1, void* ipElem2);*/
    
// ----------------------------------------------------------------
// Protected call
protected:
  CATDeclarativeManifoldHashTable & operator =(const CATLISTP(CATDeclarativeManifold) &iDMList);

};


#endif 
