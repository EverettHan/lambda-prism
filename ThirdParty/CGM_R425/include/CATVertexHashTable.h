#ifndef CATVertexHashTable_h
#define CATVertexHashTable_h

/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2011

//===========================================================================
//
// Oct. 2011   Creation                         ZFC
//
// April 2018  Modification ( Heritance from CATCellHashTable )  QF2
//
//===========================================================================
#include "ExportedByCATTopologicalObjects.h"
#include "CATFaceHashTable.h" // -> CATCellHashTableCGM
#include "ListPOfCATCell.h"
#include "ListPOfCATVertex.h"

class CATVertex;

// --------------------------------------------------------------------------------
// Derivation de CATCellHashTable (QF2)
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATVertexHashTable : public CATCellHashTableCGM
{

public : 
  // Constructor
  explicit CATVertexHashTable(int iExpectedSize=0, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // Constructor from list
  CATVertexHashTable(const ListPOfCATVertex &iVertexList, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // Copy-constructor
  CATVertexHashTable(const CATVertexHashTable & iVertexHT);
  // Destructor
  virtual ~CATVertexHashTable();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // return Vertex dimension 
  virtual short GetDimType() const;
  virtual CATGeometricType GetType() const;

  // CATCGMHashTable Methods
  // ------------------------------------
  CATVertex * operator[](int iPos) const;
  int         Insert(CATVertex * ipVertex);    
  CATVertex * Get(int iPos) const;
  void *      Locate(CATVertex * ipVertex) const;
  CATVertex * KeyLocate(unsigned int iKey) const; 
  int         Remove(CATVertex * ipVertex);
  CATVertex * Next(CATVertex * ipVertex) const;

  /**
  * -----------------------------------------------------------------
  * Mother Class Public Methods
  * -----------------------------------------------------------------
  * int       Size() const;
  * void      RemoveAll();
  * int       LocateReturnPos(CATCell * ipCell) const;
  *
  * int         Intersection(const CATCellHashTableCGM & iCellHT, CATCellHashTableCGM &oIntersectionHT) const;
  * CATBoolean  IsSameAs    (const CATCellHashTableCGM &iCellHT) const;
  * CATBoolean  Contains    (const CATCellHashTableCGM &iCellHT) const;
  *
  * const CATCellHashTable & GetAsCellHT() const;
  *
  * void Dump (CATCGMOutput &oOut,  const char *iName=NULL) const;
  * void Write(CATCGMStream &ioStr) const;
  * void Read (CATCGMStream &iStr, CATICGMContainer *iFactory);
  *
  **/

  // CATVertexHashTable Methods
  // --------------------------------------------  
  int Insert(const ListPOfCATVertex   & iVertexList); 
  int Insert(const CATVertexHashTable & iVertexHT);  

  using CATCellHashTableCGM::Remove;
  int Remove(const ListPOfCATVertex   & iVertexList); 

  // ConvertTo
  // --------------------------------------------
  using CATCellHashTableCGM::ConvertTo;
  void ConvertTo(ListPOfCATVertex &oVertexList) const;

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATCellHashTableCGM & operator = (const CATVertexHashTable & iVertexHT);

  // GetAs
  // --------------------------------------------
  virtual CATVertexHashTable  * GetAsVertexHT() const;

 protected :
   //CATVertexHashTable & operator =(const int & iAnything);
   CATVertexHashTable & operator =(const ListPOfCATVertex & iVertexList);
};



#endif /* CATVertexHashTable_h */
