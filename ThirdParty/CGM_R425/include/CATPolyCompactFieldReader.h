// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCompactFieldReader.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// Mars 2010  Creation: ZFI
//===================================================================

#ifndef CATPolyCompactFieldReader_H
#define CATPolyCompactFieldReader_H

#include "PolyMathContainers.h"
#include "CATErrorDef.h"

class ExportedByPolyMathContainers CATPolyCompactFieldReader
{
public:
  CATPolyCompactFieldReader();
  virtual ~CATPolyCompactFieldReader();

public:    
  HRESULT ReadBit(unsigned char& oBit);
  HRESULT ReadIndex(const unsigned int iBoundingIndex, unsigned int& oIndex);
  HRESULT ReadUInt(unsigned int& oX);
  HRESULT ReadFloat(float& oFloat);
  HRESULT ReadFloat(const float iFloatRef, float& oFloat);

  //new, test, ->double
public:
  HRESULT ReadFloats(float* oFloats, const unsigned int iNbFloats);
  HRESULT ReadFloats(float* oFloats, const unsigned int iNbFloats, const float iTol);

public:
  HRESULT SetFromCompactBuffer(const unsigned char* iBuffer, unsigned int iBufferSize);

private:
  //for read
  unsigned int _NumRBitLocal;
  unsigned int _NumUChar;
  const unsigned char* _UCharsBuffer;
  unsigned int _NbUChars;
};

#endif
