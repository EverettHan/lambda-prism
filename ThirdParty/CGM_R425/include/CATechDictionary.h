#ifndef CATechDictionary_h
#define CATechDictionary_h
/* -*-c++-*- */
// COPYRIGHT DASSAULT SYSTEMES 2006
/**
 * @level Private
 * @usage U1
 */
//------------------------------------------------------------ 
// Small metadata for genuine Extract/Redo infrastructure
//------------------------------------------------------------ 
#include "CATCGMKernel.h"
#include "CATSysSimpleHashTable.h"
#include "CATechWord.h"

void               CATech_LateTypeToRunTime_Clean();

//------------------------------------------------------------------------
// CATechDictionary
//------------------------------------------------------------------------
class  CATechDictionary : public CATSysSimpleHashTable
{
public:

  /** @nodoc */
  CATechDictionary(int dim=256);

  /** @nodoc */
  ~CATechDictionary();

  /** @nodoc */
  int                  Insert(CATechWord & iLocation);

  /** @nodoc */
  CATechWord      * Locate(CATechWord & iLocation) const;

  /** @nodoc */
  void ApplyDelete();

private:

  /** @nodoc */
  CATechDictionary(const CATechDictionary&);

  /** @nodoc */
  CATechDictionary& operator=(const CATechDictionary&);
};





//------------------------------------------------------------
// CATechDictionary_ XXX 
//------------------------------------------------------------

/** @nodoc */
ExportedByCATCGMKernel unsigned int CATechDictionary_HashKey(void* inew); 

/** @nodoc */
ExportedByCATCGMKernel int          CATechDictionary_Compare(void* i1, void *i2);


#endif
