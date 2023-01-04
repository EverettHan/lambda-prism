// COPYRIGHT DASSAULT SYSTEMES 2010, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBitField.h
//
//===================================================================
//
// Usage notes: 
//
//===================================================================
//
// Mars 2010  Creation: ZFI
//===================================================================

#ifndef CATPolyBitField_H
#define CATPolyBitField_H

#include "PolyStream.h"
#include "CATErrorDef.h"
#include "CATPolyBuckets_T.h"

class CATMathStream;

class ExportedByPolyStream CATPolyBitField
{
public:
  CATPolyBitField();
  virtual ~CATPolyBitField();

public:    
  HRESULT WriteBits(unsigned char* iBits,
                    unsigned int iNbBits);
  
  HRESULT ReadBits(unsigned char* ioBits,
                   unsigned int iNbBits);

  HRESULT WriteBit(unsigned char iBit);
  HRESULT ReadBit(unsigned char& oBit);

  HRESULT WriteIndex(const unsigned int iIndex, const unsigned int iBoundingIndex);
  HRESULT ReadIndex(const unsigned int iBoundingIndex, unsigned int& oIndex);

  HRESULT WriteFloat(const float iFloat);
  HRESULT ReadFloat(float& oFloat);

  HRESULT WriteUInt(const unsigned int iX);
  HRESULT ReadUInt(unsigned int& oX);

  HRESULT WriteFloat(const float iFloat, const float iFloatRef);
  HRESULT ReadFloat(const float iFloatRef, float& oFloat);

  HRESULT WriteFloats(const float* iFloats,const unsigned int iNbFloats);
  HRESULT ReadFloats(float* oFloats,  const unsigned int iNbFloats);

  HRESULT WriteFloats(const float* iFloats, const float* iFloatsRef, const unsigned int iNbFloats);
  HRESULT ReadFloats(const float* iFloatsRef, float* oFloats,  const unsigned int iNbFloats);

  HRESULT Rewind();

  HRESULT Stream(CATMathStream& iStream)const;
  HRESULT Unstream(CATMathStream& iStream);
  unsigned int GetSize()const;

  unsigned int GetNbBits() const ;

  inline HRESULT Allocate (unsigned int iNbBits);


private:  
   class Specialize_CATPolyBuckets_T (CATBucketsUChars, unsigned char);

private:
  //for read
  unsigned int _NumRBitLocal;
  unsigned int _NumUChar;
  unsigned char* _UCharsBuffer;
  unsigned int _NbUChars;

  //for write
  CATBucketsUChars _UCharsBuckets;
  unsigned int _NumWBitLocal;

  //for work
  unsigned char* _Bits;
  unsigned int _NbBits;
};

//inline
inline HRESULT CATPolyBitField::Allocate (unsigned int iNbBits)
{
  if (_NbBits<iNbBits)
  {
    _NbBits = iNbBits;

    delete[] _Bits;
    _Bits = new unsigned char[_NbBits];
  }
  return S_OK;
}

#endif
