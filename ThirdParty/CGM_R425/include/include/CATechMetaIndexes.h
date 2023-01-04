#ifndef CATechMetaIndexes_h
#define CATechMetaIndexes_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 
#include "ExportedByCATTechTools.h"
#include "CATSysSimpleHashTable.h"
#include "CATechMeta.h"
#include "CATMathStream.h"
#include "CATLISTV_CATechMeta.h"

struct CATechMetaIndex 
{
  CATCGMNewClassArrayDeclare;

  CATechMetaIndex(const CATechMeta & iMeta) : _Index(0), _Meta(iMeta) 
  {}

  CATechMeta     _Meta;
  CATLONG32      _Index; 
};

//------------------------------------------------------------------------
// CATechMetaIndexes
//------------------------------------------------------------------------
class  CATechMetaIndexes : public CATSysSimpleHashTable
{
public:

  /** @nodoc */
  CATechMetaIndexes(int dim=256);

  /** @nodoc */
  ~CATechMetaIndexes();

  /** @nodoc */
  int                  Insert(const CATechMeta & iMeta);

  /** @nodoc */
  CATechMetaIndex    * Locate(const CATechMeta & iMeta) const;

  /** @nodoc */
  void GetByIndex(const CATLONG32 Index, CATechMeta & ioLocation);

  static const CATechMeta Dummy;

  //--------------------------------------- 
  //  Save/Open
  //--------------------------------------- 
  void Save(CATMathStream &Str);
  void Open(CATMathStream &Str);


  /** @nodoc */
  void ApplyDelete();

private:

  CATLONG32            _MaxIndex; 

  CATLISTV(CATechMeta) _ForOpen;

  /** @nodoc */
  CATechMetaIndexes(const CATechMetaIndexes&);

  /** @nodoc */
  CATechMetaIndexes& operator=(const CATechMetaIndexes&);
};





//------------------------------------------------------------
// CATechMetaIndexes_ XXX 
//------------------------------------------------------------

/** @nodoc */
ExportedByCATTechTools unsigned int CATechMetaIndexes_HashKey(void* inew); 

/** @nodoc */
ExportedByCATTechTools int          CATechMetaIndexes_Compare(void* i1, void *i2);


#endif
