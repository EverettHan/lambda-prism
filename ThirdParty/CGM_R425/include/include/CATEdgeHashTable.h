#ifndef CATEdgeHashTable_h
#define CATEdgeHashTable_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES  2010

//===========================================================================
//
// Mar. 2000   Creation                         JJ3
//
// April 2018  Modification ( Heritance from CATCellHashTable )  QF2
//
//===========================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATFaceHashTable.h" // -> CATCellHashTableCGM
#include "ListPOfCATCell.h"
#include "ListPOfCATEdge.h"

class CATEdge;
class CATCellHashTableCGM;

// --------------------------------------------------------------------------------
// Derivation de CATCellHashTable (QF2)
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATEdgeHashTable : public CATCellHashTableCGM
{

public : 
  // Constructor
  explicit CATEdgeHashTable(int iExpectedSize=0, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // Constructor from list
  CATEdgeHashTable(const ListPOfCATEdge &iEdgeList, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // Copy-constructor
  CATEdgeHashTable(const CATEdgeHashTable & iEdgeHT);

  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // Destructor
  virtual ~CATEdgeHashTable();

  // return Edge dimension 
  virtual short GetDimType() const;
  virtual CATGeometricType GetType() const;

  // CATCellHashTable Methods
  // ------------------------------------
  CATEdge * operator[](int iPos) const;
  int       Insert(CATEdge * ipEdge);    
  CATEdge * Get(int iPos) const;
  void *    Locate(CATEdge * ipEdge) const;
  CATEdge * KeyLocate(unsigned int iKey) const; 
  int       Remove(CATEdge * ipEdge);
  CATEdge * Next(CATEdge * ipEdge) const;
  /**
  * -----------------------------------------------------------------
  * Mother Class Public Methods
  * -----------------------------------------------------------------
  * int     Size() const;
  * void    RemoveAll();
  * int     LocateReturnPos(CATCell * ipCell) const;
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
  **/
      
  // CATEdgeHashTable Methods
  // -------------------------------------    
  using CATCellHashTableCGM::Remove;
  int Remove(const ListPOfCATEdge   & iEdgeList); 
  
  int Insert(const ListPOfCATEdge   & iEdgeList); 
  int Insert(const CATEdgeHashTable & iEdgeHT);  

  // ConvertTo
  // --------------------------------------------
  using CATCellHashTableCGM::ConvertTo;
  void ConvertTo(ListPOfCATEdge &oEdgeList) const;

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATCellHashTableCGM & operator =(const CATEdgeHashTable & iEdgeHT);

  // GetAs
  // --------------------------------------------
  virtual CATEdgeHashTable * GetAsEdgeHT() const;


protected :
   // CATEdgeHashTable & operator =(const int & iAnything);
   CATEdgeHashTable & operator =(const ListPOfCATEdge &iEdgeList);

};


// Pour l'instant comme ca a cause de probleme de link ... 
//class ExportedByCATTopologicalObjects CATEdgeHashTable
//{
//  public : 
//    CATEdgeHashTable(int iExpectedSize = 0);
//    ~CATEdgeHashTable();
//
//    int       Insert(CATEdge* ipEdge);
//    int       Insert(CATEdgeHashTable* ipEdgeHT);
//    CATEdge*  Get(int iPos) const;
//    void*     Locate(CATEdge* ipEdge) const;
//    CATEdge*  KeyLocate(unsigned int iKey) const; 
//    int       Remove(CATEdge* ipEdge);
//    CATEdge*  Next(CATEdge* ipEdge) const;
//    int       Size() const;
//
//
//  private :
//
//    CATCGMHashTable * _HT;
//};



#endif // file
