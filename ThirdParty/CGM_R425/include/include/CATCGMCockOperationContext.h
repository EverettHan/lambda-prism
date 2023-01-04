#ifndef CATCGMCockOperationContext_h
#define CATCGMCockOperationContext_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
#include "CATCGMCockOperation.h"
#include "CATListOfCATCGMCockOperationContext.h"


//------------------------------------------------------------------------
// CATCGMCockOperationContext
//------------------------------------------------------------------------

class  ExportedByCATMathematics CATCGMCockOperationContext
{ 
public :
  CATCGMNewClassArrayDeclare;


  INLINE CATCGMCockOperationContext(int iDepthLevel,   CATCGMCockOperation * iOperation)
    : _Operation(iOperation)
    , _DepthLevel(iDepthLevel)
    , _IndexTable(0)
    , _RunHistory(0)
    , _NbRunWithTypes(0)
    {  if (  !iOperation  )  CATThrowForNullPointer(); } ;
 
  INLINE ~CATCGMCockOperationContext()    
    {} ;

  INLINE CATBoolean operator == (const CATCGMCockOperationContext & iOther) const  
  { return ( ( (*_Operation) == (*iOther._Operation) ) && ( _DepthLevel == iOther._DepthLevel ) ) ? TRUE : FALSE; }

  INLINE CATUINTPTR HashValue()  
  { return ( _Operation->HashValue() + _DepthLevel ) ; }
 
   // DepthLevel
   CATULONG32     _DepthLevel;

  // IndexTable
  CATULONG32     _IndexTable;

  // Instance management
  CATULONG64        _RunHistory;
  CATULONG32        _NbRunWithTypes;

  CATCGMCockOperation * _Operation;



private :

  CATCGMCockOperationContext (CATCGMCockOperationContext &);    
  CATCGMCockOperationContext& operator=(CATCGMCockOperationContext&);  
};



extern ExportedByCATMathematics int SortCATCGMCockOperationContextByString(CATCGMCockOperationContext *left, CATCGMCockOperationContext *right);
 

 

//------------------------------------------------------------------------
// CATCGMCockOperationContextTable
//------------------------------------------------------------------------
class  ExportedByCATMathematics  CATCGMCockOperationContextTable : protected CATSysSimpleHashTable
{
public:
  CATCGMNewClassArrayDeclare;


  /** @nodoc */
  CATCGMCockOperationContextTable(int dim=4096);

  /** @nodoc */
  ~CATCGMCockOperationContextTable();

  /** @nodoc */
  int                  Insert(CATCGMCockOperationContext & iLocation);

  /** @nodoc */
  CATCGMCockOperationContext      * Locate(CATCGMCockOperationContext & iLocation) const;

  /** @nodoc */
  CATCGMCockOperationContext      * GetByIndex(CATULONG32 iIndex) const;

  INLINE CATULONG32    GetNumberOfIndex() const ;      

  /** @nodoc */
  void ApplyDelete();

  /** @nodoc */
  CATLISTP(CATCGMCockOperationContext) _TableIndex;

protected :

  // IndexTable
  CATULONG32              _Counter;

private:

  friend class CATCGAMeasure;

  /** @nodoc */
  CATCGMCockOperationContextTable(const CATCGMCockOperationContextTable&);

  /** @nodoc */
  CATCGMCockOperationContextTable& operator=(const CATCGMCockOperationContextTable&);
};


INLINE CATULONG32 CATCGMCockOperationContextTable::GetNumberOfIndex() const
{ return (CATULONG32) this->CATSysSimpleHashTable::Size(); }     

 

/** @nodoc */
unsigned int CATCGMCockOperationContextTable_HashKey(void* inew); 

/** @nodoc */
int          CATCGMCockOperationContextTable_Compare(void* i1, void *i2);




#endif
