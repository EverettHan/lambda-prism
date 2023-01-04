/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2019 
/**
* @nodoc
*/
//===========================================================================
//
// Avr. 2019   Creation Classe mere des objets Geometric             QF2
//
//===========================================================================
#ifndef CATGeometryHTab_H
#define CATGeometryHTab_H

// CATGeometryHTab  ? 
#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMHashTable.h"
#include "CATCollec.h"
#include "CATCGMNewArray.h"
#include "CATGeometryType.h"
#include "CATSysBoolean.h"
#include "CATGeomHashTableBase.h"

class CATGeometry;
class CATCellManifoldHashTable;
class CATDeclarativeManifoldHashTable;
class CATGeometryHTab;
class CATCGMOutput;
class CATCGMStream;
class CATICGMContainer;
class CATCellManifoldGroupHashTable;
class CATLISTP(CATGeometry);

//
typedef		int	         (*LSOCompareFunction) ( CATGeometry *, CATGeometry * );	
typedef		unsigned int (*LSOHashKeyFunction) ( CATGeometry * ) ;
//


//// --------------------------------------------------------------------------------
//// ** Heritage protégé ! **
//// --------------------------------------------------------------------------------
//// Class Abstraite  [ Deplacée vers GMModelInterface week 18 Y2020 ]
//// --------------------------------------------------------------------------------
//class ExportedByCATTopologicalObjects CATGeomHashTableBase : virtual protected CATCGMHashTable 
//{
//public :
//  // Destructor
//  virtual ~CATGeomHashTableBase();
//  // surchage du new et du delete
//  CATCGMNewClassArrayDeclare;
//
//  virtual CATGeometricType GetType() const = 0;
//
//  
//  // --------------------------------------------
//  // Basic Access
//  // --------------------------------------------
//  CATGeometry * operator[](int iPos) const;    
//  CATGeometry * Get(int iPos)        const;
//  void        * Locate(const CATGeometry * ipGeom) const;
//  CATGeometry * KeyLocate(unsigned int iKey) const; 
//  CATGeometry * Next(const CATGeometry * ipGeom)   const;
//  int           LocateReturnPos(const CATGeometry* ipGeom) const;
//
//  void          RemoveAll();
//  int           Size() const;
//
//  // -----------------------------------------------------------------
//  // Avanced Use
//  // -----------------------------------------------------------------
//  // Return common cells with iCellHT and this. 
//  // Restriction : iCellHT and oIntersectionHT must be same type than this or throw
//  int Intersection(const CATGeomHashTableBase & iGeomHT, CATGeomHashTableBase &oIntersectionHT) const;
//
//  // Test if at least one cell is common to both hash table.
//  CATBoolean  IsIntersecting(const CATGeomHashTableBase &iGeoHT) const;
//  // Test the equality between the two HT, the order doesnt matter.
//  CATBoolean  IsSameAs (const CATGeomHashTableBase &iGeoHT) const;
//  // Test if all cells of iGeoHT are included in this.
//  // Convention : return FALSE if iGeoHT is empty.
//  CATBoolean  Contains (const CATGeomHashTableBase &iGeoHT) const;
//
//   
//  // ConvertTo
//  // ------------------------------------------------------
//  void ConvertTo(CATCGMHashTable &oCellHT)         const;
//  void ConvertTo(CATLISTP(CATGeometry) &oGeomList) const;
//
//  // GetAs
//  // ------------------------------------------------------
//  virtual CATGeometryHTab                 * GetAsGeometryHT()     const;
//  virtual CATCellManifoldHashTable        * GetAsCellManifoldHT() const;
//  virtual CATCellManifoldGroupHashTable   * GetAsCMGroupHT()      const;
//  virtual CATDeclarativeManifoldHashTable * GetAsDeclarativeHT()  const;
//  
//  // Const GetAs 
//  // -----------------------------------------------------
//  const CATCGMHashTable & GetAsCGMHashTable() const; // read only access
//
//  // ---------------------------------------------------------------
//  // Debug && Stream 
//  // ---------------------------------------------------------------
//  virtual void Dump (CATCGMOutput &oOut,  const char *iName=NULL) const;
//  virtual void Write(CATCGMStream &ioStr) const;
//  virtual void Read (CATCGMStream &ioStr, CATICGMContainer *iFactory);
//
//
//  // HashTable Fonction
//  static unsigned int HashKeyGEO_Function(CATGeometry * ipGeom);
//  static int CompareGEO_Function(CATGeometry * ipGeom1, CATGeometry *ipGeom2);
//
//protected :
//  // Constructor
//  explicit CATGeomHashTableBase(int iExpectedSize=0, LSOHashKeyFunction ipHashKeyFunction=HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CompareGEO_Function);
//  // Copy-constructor
//  CATGeomHashTableBase(const CATGeomHashTableBase & iGeomHT);
//  
//  int     Insert(CATGeometry * ipGeom);  
//  int     Remove(CATGeometry * ipGeom);
//
//  // Union / Diff
//  int Insert(const CATGeomHashTableBase & iGeometryHT);
//  int Remove(const CATGeomHashTableBase & iGeometryHT);
//
//  // Operators =
//  CATGeomHashTableBase & operator =(const CATGeomHashTableBase & iGeometryHT);
//
//};



// --------------------------------------------------------------------------------
// ** Heritage Public ** 
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects  CATGeometryHTab : public CATGeomHashTableBase 
{

public:
  // Constructor
  explicit CATGeometryHTab(int iExpectedSize=0, LSOHashKeyFunction ipHashKeyFunction=CATGeomHashTableBase::HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CATGeomHashTableBase::CompareGEO_Function);
  // constructor from list
  CATGeometryHTab(const CATLISTP(CATGeometry) &iGeomList, LSOHashKeyFunction ipHashKeyFunction=CATGeomHashTableBase::HashKeyGEO_Function, LSOCompareFunction ipCompareFunction=CATGeomHashTableBase::CompareGEO_Function);
  // Copy-constructor
  CATGeometryHTab(const CATGeometryHTab & iGeomHT);
  // Destructor
  virtual ~CATGeometryHTab();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // return CATGeometry dimension 
  virtual CATGeometricType GetType() const;
  

  // --------------------------------------------
  // Insert/Remove Methods
  // --------------------------------------------
  int   Insert(CATGeometry * ipGeom);  
  int   Insert(const CATLISTP(CATGeometry)  & iGeomList); 
  int   Insert(const CATGeometryHTab        & iGeomHT);

  int   Remove(CATGeometry * ipGeom);
  int   Remove(const CATLISTP(CATGeometry)  & iGeomList); 
  int   Remove(const CATGeometryHTab        & iGeomHT);   

  // ConvertTo
  // --------------------------------------------
  

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATGeomHashTableBase & operator =(const CATGeometryHTab & iGeomHT);

  // GetAs
  // --------------------------------------------  
  virtual CATGeometryHTab * GetAsGeometryHT() const;
      

// ----------------------------------------------------------------
// Protected call
protected:
  CATGeometryHTab & operator =(const CATLISTP(CATGeometry) &iGeomList);

};


//#define CATHashTabCATGeometry CATGeometryHTab

#endif 
