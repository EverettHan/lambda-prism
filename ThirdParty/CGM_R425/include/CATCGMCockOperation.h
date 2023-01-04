#ifndef CATCGMCockOperation_h
#define CATCGMCockOperation_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
#include "CATSysSimpleHashTable.h"
#include "CATListOfCATCGMCockOperation.h"
#include "CATUnicodeString.h"
#include "CATDataType.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"
#include "CATMathematics.h"
#include "CATThrowForNullPointer.h"
 
class CATCGAMeasure;

class  ExportedByCATMathematics CATCGMCockOperation
{ 
public :
  CATCGMNewClassArrayDeclare;

  CATCGMCockOperation(const char *  iStackOperation,  const char *  iStackOperationDomain );

  CATCGMCockOperation(const CATUnicodeString &  iStackOperationDomain );

  ~CATCGMCockOperation() ;

  CATBoolean operator == (const CATCGMCockOperation & iOther) const ;

  CATUINTPTR HashValue()   { return _Key; }
 
  // IndexTable
  CATULONG32     _IndexTable;

  // Key Management
  CATUnicodeString  _OperationDomain;

  // Instance management
  CATULONG64      _NbRun;
 
  // MeanRuns
  CATULONG64     _NbRunByLevel;  
  CATULONG64     _NbRunTypesByLevel;
 
private :
  
  friend class     CATCGMCockOperationTable;
  CATUINTPTR       _Key;  

  CATCGMCockOperation (CATCGMCockOperation &);    
  CATCGMCockOperation& operator=(CATCGMCockOperation&);  
};

extern ExportedByCATMathematics int SortCATCGMCockOperationByString(CATCGMCockOperation *left, CATCGMCockOperation *right);


 


//------------------------------------------------------------------------
// CATCGMCockOperationTable
//------------------------------------------------------------------------
class  ExportedByCATMathematics  CATCGMCockOperationTable : protected CATSysSimpleHashTable
{
public:
  CATCGMNewClassArrayDeclare;


  /** @nodoc */
  CATCGMCockOperationTable(int dim=4096);

  /** @nodoc */
  ~CATCGMCockOperationTable();

  /** @nodoc */
  int                  Insert(CATCGMCockOperation & iLocation);

  /** @nodoc */
  CATCGMCockOperation      * Locate(CATCGMCockOperation & iLocation) const;

  /** @nodoc */
  CATCGMCockOperation      * GetByIndex(CATULONG32 iIndex) const;

  INLINE CATULONG32    GetNumberOfIndex() const ;      

  /** @nodoc */
  void ApplyDelete();

  /** @nodoc */
  CATLISTP(CATCGMCockOperation) _TableIndex;

protected :

  // IndexTable
  CATULONG32              _Counter;

private:

  friend class CATCGAMeasure;

  /** @nodoc */
  CATCGMCockOperationTable(const CATCGMCockOperationTable&);

  /** @nodoc */
  CATCGMCockOperationTable& operator=(const CATCGMCockOperationTable&);
};


INLINE CATULONG32 CATCGMCockOperationTable::GetNumberOfIndex() const
{ return (CATULONG32) this->CATSysSimpleHashTable::Size(); }     

 
/** @nodoc */
unsigned int CATCGMCockOperationTable_HashKey(void* inew); 

/** @nodoc */
int          CATCGMCockOperationTable_Compare(void* i1, void *i2);

 


#endif
