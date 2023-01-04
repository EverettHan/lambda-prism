// Sep 10   Optimization by structure Buffer64A                    PR

#ifndef CATMathStreamBits_H
#define CATMathStreamBits_H


#include "ExportedByCATMathStream.h"
#include "CATMathStreamImpl.h"
#include "CATMathInline.h"

//#ifdef NurbsCompactOptimPR
#include "CATArithTypes.h"

#define PAGE64 0x200
struct Buffer64A         // alignee sur 0x10 octets
{
  ulla  U64[PAGE64];     // 4Ko
  short Bdx;             // numero de bit dans ulla
  short Udx;             // numero de cet ulla
};
//#endif

class ExportedByCATMathStream CATMathStreamBits
{
public:
  enum FlowType { Stream, Unstream };

  CATMathStreamBits();
  CATMathStreamBits(CATMathStreamImpl * ioStream, FlowType iFlowType);
  ~CATMathStreamBits();

  INLINE CATULONG64 GetMask(unsigned short iStartIndex, unsigned short iEndIndex);

  void WriteBitsCleared(CATULONG64 iBits, unsigned short iStartIndex, unsigned short iEndIndex);
//  void WriteBitsCleared64(CATULONG64 iBits);
  void EndWrite();

  void ReadBits(CATULONG64 & ioBits, unsigned short iStartIndex, unsigned short iEndIndex);
  void ReadBitsUncleared(CATULONG64 & ioBits, unsigned short iStartIndex, unsigned short iEndIndex);
//#ifdef NurbsCompactOptimPR
  INLINE CATMathStreamImpl* GetStreamImpl ();
  INLINE Buffer64A*         GetBuffer64A  ();
//#endif 

private:

  void WriteBuffer();
  void ReadBuffer();

 /* union ULONG64AsByte
  {
    CATULONG64 ulong64;
    unsigned char byte[8];
  };*/

/*  struct Buffer
  {
    unsigned char Byte;
    short Index;//[0..8] = nb bits written or read
  };
*/
  struct Buffer64
  {
    //ULONG64AsByte ULONG64;
  union ULONG64AsByte
  {
    CATULONG64 ulong64;
    unsigned char byte[8];
  } ULONG64;
    short Index;//[0..8] = nb bits written or read
  };

  CATMathStreamImpl * _Stream;
  Buffer64  _Buffer64;
//#ifdef NurbsCompactOptimPR
  Buffer64A _Buffer64A;
//#endif
  FlowType  _FlowType;
};

//#ifdef NurbsCompactOptimPR
INLINE CATMathStreamImpl* CATMathStreamBits::GetStreamImpl ()
{
  return _Stream;
}

INLINE Buffer64A* CATMathStreamBits::GetBuffer64A ()
{
  return &_Buffer64A;
}
//#endif
/*
INLINE CATULONG64 CATMathStreamBits::GetMask(unsigned short iStartIndex, unsigned short iEndIndex)
{

  CATULONG64 Mask = 0xFFFFFFFFFFFFFFFFULL >> iStartIndex;
  CATULONG64 Tmp = 0xFFFFFFFFFFFFFFFFULL << (64 - iEndIndex);
  Mask &= Tmp;
  return Mask;
}
*/

#endif
