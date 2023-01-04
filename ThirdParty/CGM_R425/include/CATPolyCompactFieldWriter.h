// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCompactFieldWriter.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// Mars 2010  Creation: ZFI
//===================================================================

#ifndef CATPolyCompactFieldWriter_H
#define CATPolyCompactFieldWriter_H

#include "PolyMathContainers.h"
#include "CATErrorDef.h"
#include "CATPolyBuckets_T.h"

class ExportedByPolyMathContainers CATPolyCompactFieldWriter
{
public:
  CATPolyCompactFieldWriter();
  virtual ~CATPolyCompactFieldWriter();

public:    
  HRESULT WriteBit(unsigned char iBit);  
  HRESULT WriteIndex(const unsigned int iIndex, const unsigned int iBoundingIndex);
  HRESULT WriteUInt(const unsigned int iX);
  HRESULT WriteFloat(const float iFloat);
  HRESULT WriteFloat(const float iFloat, const float iFloatRef);

  //new, test->double
public:
  HRESULT WriteFloats(const float* iFloats, const unsigned int iNbFloats);
  HRESULT WriteFloats(const float* iFloats, const unsigned int iNbFloats, const float iTol);

public:
  HRESULT GetCompactBuffer(unsigned char*& oBuffer, unsigned int& oNbBytes)const;


public:
  unsigned int Size()const {return (unsigned int)_UCharsBuckets.Size();}

private:
  HRESULT WriteBits(unsigned char* iBits, unsigned int iNbBits);

private:  
  class Specialize_CATPolyBuckets_T (CATBucketsUChars, unsigned char);

private:
  //for write
  CATBucketsUChars _UCharsBuckets;
  unsigned int _NumWBitLocal;
};

#endif
