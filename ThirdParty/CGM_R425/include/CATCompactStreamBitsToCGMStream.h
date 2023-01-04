#ifdef _Coverage_GOO
#ifndef CATCompactStreamBitsToCGMStream_H
#define CATCompactStreamBitsToCGMStream_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// December 2003 - ALA - Creation
//===================================================================
//
#include "CATCompactStreamBits.h"
#include "CATMathStream.h"
#include "CompactFunction.h"

//
//
class ExportedByCompactFunction CATCompactStreamBitsToCGMStream : public CATCompactStreamBits
{
  public:
	//
	 CATCompactStreamBitsToCGMStream(CATMathStream *iCGMStream);
	 ~CATCompactStreamBitsToCGMStream();
	// return 0 if OK
	int  Read(const unsigned short NbBits, unsigned char *buf, int FirstBit = 0);
	// return 0 if OK
	int ReadDouble(double &oV);

	// note that a write is effective only after a flush() operation !!
	  // return 0 if OK
	int  Write(const unsigned short NbBits, const unsigned char *buf, int FirstBit = 0);
	  // return 0 if OK
	int  WriteDouble(const double &iV);


	/////////////////////////////
	// flush()  write effectively to the CATMathStream ...
	  // return 0 if OK
	int Flush();
	 //
	unsigned int GetNbBytesWritten();
	//
  private :
	//
	void CopyBits(	int NbBitsToCopy,
					const unsigned char *iBuf,
					int iPosiBuf,
					unsigned char *oBuf,
					int iPosoBuf);
	//
	int _NbWFreeBits;
	unsigned char _WUChar;
	int _NbRFreeBits;
	unsigned char _RUChar;
	unsigned int _NbBytesWritten;
	CATMathStream *_pCGMStream;
	//
};
#endif
#endif
