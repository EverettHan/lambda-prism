#ifndef CATFaceHashTable_h
#define CATFaceHashTable_h
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
#include "CATCellHashTable.h"
#include "ListPOfCATCell.h"
#include "ListPOfCATFace.h"
#include "CATSysBoolean.h"
#include "CATGeometryType.h"

class CATFace;
class CATFaceHashTable;
class CATEdgeHashTable;
class CATVertexHashTable;
class CATCGMOutput;
class CATCGMStream;
class CATICGMContainer;
class CATGeomHashTableBase;
class CATLISTP(CATGeometry);

// --------------------------------------------------------------------------------
// Derivation protegee CATCellHashTable
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATCellHashTableCGM : /*virtual*/ protected CATCellHashTable
{
public :
  /** ---------------------------------------------------------------------
  * **Protected Contructor**
  *  This class is to be generic for Face, Edge and Vertex HashTable.
  *  It cannot be directly instanciate for now W16Y2018.
  *  ----------------------------------------------------------------------
  */

  // Destructor 
  virtual ~CATCellHashTableCGM();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // Get type according to cells dimension.
  virtual short GetDimType() const = 0;

  // Basic Access
  // --------------------------------------------
  CATCell * operator[](int iPos) const;
  CATCell * Get(int iPos) const;
  void *    Locate(CATCell * ipCell) const;
  CATCell * KeyLocate(unsigned int iKey) const; 
  CATCell * Next(CATCell * ipCell) const;
  int       Size() const;
  void      RemoveAll();
  int       LocateReturnPos(CATCell * ipCell) const;
  int       RemoveReturnPos(CATCell * ipCell);


  // Advanced use
  // --------------------------------------------
  // Return common cells with iCellHT and this. 
  // Restriction : iCellHT and oIntersectionHT must be same type than this or throw.  
  int         Intersection  (const CATCellHashTableCGM &iCellHT, CATCellHashTableCGM  &oIntersectionHT) const;
  int         Intersection  (const CATCellHashTableCGM &iCellHT, CATCellHashTable     &oIntersectionHT) const;
  // Test if at least one cell is common to both hash table.
  CATBoolean  IsIntersected(const CATCellHashTableCGM &iCellHT) const;
  // Test the equality between the two HT, the order doesnt matter.
  CATBoolean  IsSameAs  (const CATCellHashTableCGM &iCellHT) const;
  // Test if all cells of iCellHT are included in this.
  // Convention : return FALSE if iCellHT is empty.
  CATBoolean  Contains  (const CATCellHashTableCGM &iCellHT) const;

  // Pickout: insert cells if dimension corresponds.
  //     Ex : if this* is CATFaceHashTable type, 
  //          insert CATFace from iCellHTab.
  // --------------------------------------------------
  int  Pickout(const CATCellHashTableCGM &iCellHTab);
  int  Pickout(const CATCellHashTable &iCellHTab);
  int  Pickout(const ListPOfCATCell   &iCellList);

  // Remove Cell from HT.
  int Remove(const CATCellHashTable    & iCellHT);
  int Remove(const CATCellHashTableCGM & iCellHT);

  // ConvertTo
  // --------------------------------------------------
  void ConvertTo(ListPOfCATCell  & oCellList)       const;    
  void ConvertTo(CATLISTP(CATGeometry) & oGeomList) const; 
  void ConvertTo(CATCGMHashTable &oCellHT)          const;
  void ConvertTo(CATCellHashTable &oCellHT)         const;


  // ---------------------------------------------------------------
  // GetAs to use carefully
  // CATCellHashTable is not protected, it could be filled by 
  // any type of object. Make sure that your FaceHT is read only.
  // ---------------------------------------------------------------
  const CATCellHashTable & GetAsCellHT() const;

  // ---------------------------------------------------------------
  // GetAs...() child classes
  // ---------------------------------------------------------------
  virtual CATFaceHashTable   * GetAsFaceHT() const;
  virtual CATEdgeHashTable   * GetAsEdgeHT() const;
  virtual CATVertexHashTable * GetAsVertexHT() const;

  // ---------------------------------------------------------------
  // Debug && Stream 
  // ---------------------------------------------------------------
  void Dump (CATCGMOutput &oOut,  const char *iName=NULL) const;
  virtual void Write(CATCGMStream &ioStr) const;
  virtual void Read (CATCGMStream &iStr, CATICGMContainer *iFactory);
  virtual void PutColor(int iRed, int iGreen, int iBlue) const;

protected :

  // Constructor
  explicit CATCellHashTableCGM(int iExpectedSize=0, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);  
  // Copy-constructor
  CATCellHashTableCGM(const CATCellHashTableCGM & iCellHT);

  // Union 
  int Insert(const CATCellHashTableCGM & iCellHT);

  // Operators =
  CATCellHashTableCGM & operator =(const CATCellHashTableCGM & iCellHT);

};

// --------------------------------------------------------------------------------
// Derivation de CATCellHashTable (QF2)
// --------------------------------------------------------------------------------
class ExportedByCATTopologicalObjects CATFaceHashTable : public CATCellHashTableCGM
{

public : 
  // Constructor
  explicit CATFaceHashTable(int iExpectedSize=0, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);  
  // constructor from list
  CATFaceHashTable(const ListPOfCATFace &iFaceList, PFHashKeyFunction ipHashKeyFunction=::HashKeyFunction, PFCompareFunction ipCompareFunction=::CompareFunction);
  // Copy-constructor
  CATFaceHashTable(const CATFaceHashTable & iFaceHT);
  // Destructor
  virtual ~CATFaceHashTable();
  // surchage du new et du delete
  CATCGMNewClassArrayDeclare;

  // return Face dimension 
  virtual short GetDimType() const;
  virtual CATGeometricType GetType() const;

  // Main Methods
  // --------------------------------------------
  CATFace * operator[](int iPos) const;
  int       Insert(CATFace * ipFace);    
  CATFace * Get(int iPos) const;
  void *    Locate(CATFace * ipFace) const;
  CATFace * KeyLocate(unsigned int iKey) const; 
  int       Remove(CATFace * ipFace);
  CATFace * Next(CATFace * ipFace) const;

  // --------------------------------------------
  // CATCellHashTableCGM Methods
  // --------------------------------------------
  int Insert(const ListPOfCATFace   & iFaceList); 
  int Insert(const CATFaceHashTable & iFaceHT);

  using CATCellHashTableCGM::Remove;
  int Remove(const ListPOfCATFace & iFaceList); 

  // ConvertTo
  // --------------------------------------------
  using CATCellHashTableCGM::ConvertTo;
  void ConvertTo(ListPOfCATFace &oFaceList) const;
  

  // ---------------------------------------------------------------
  // Operators =
  // ---------------------------------------------------------------
  CATCellHashTableCGM & operator = (const CATFaceHashTable & iFaceHT);

  // GetAs
  // --------------------------------------------
  virtual CATFaceHashTable  * GetAsFaceHT() const;

  
// ----------------------------------------------------------------
// Protected call
protected:
  // CATFaceHashTable & operator =(const int & iAnything);
  CATFaceHashTable & operator =(const ListPOfCATFace &iFaceList);

};


#endif
