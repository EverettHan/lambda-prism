//====================================================================
// Copyright Dassault Systemes Provence 2003, all rights reserved 
//====================================================================
//
// CATSobStream.h
//
//====================================================================
//
// Usage notes: Interface to stream subdivision objects
//
//====================================================================
// 28.04.2015 : RAQ : Ajout Set/GetCurrentPosition en lecture suite au RI 366698
// December, 2004 : RAQ : Ajout IsEndOfBuffer() et InitBuffer()
// January,  2004 : RAQ : Creation
//====================================================================
#ifndef CATSobStream_H
#define CATSobStream_H

#include "CATSobObjects.h"

#include "CATBoolean.h"
#include "CATDataType.h"

#include "CATSobDiag.h"
class CATSobMesh;

// Taille du buffer pour la lecture
#define SIZE_OF_BUFFER  512

//-------------------------------------------------------------------------------------------------------
//***** Some comments about bit per bit stream:
//
// - WriteBits and ReadBits methods take a facultative argument 'int iFirstBit = 0'.
// In both of these methods, the bits in bytes are ordered the following way:
//             _______________
// Byte       |_|_|_|_|_|_|_|_|
// Bit index   0 1 2 3 4 5 6 7
//
// - To use this interface, the only thing to do is implementing two protected methods:
// virtual CATSobDiag WriteCharImplement(const char* iBufferToWrite, const int iNbCharToWrite) = 0;
// virtual CATSobDiag ReadCharImplement(char* ioBuffer, const int iNbCharToRead, int& oNbCharRead) = 0;
//
//-------------------------------------------------------------------------------------------------------

class CATSobStream;
class ExportedByCATSobObjects CATSobStreamPosition
{
  friend class CATSobStream;
public:

  CATSobStreamPosition():m_BitPosition(0), m_BytePosition(0), m_NbReadBytesTotal(0) {}
  virtual ~CATSobStreamPosition() {}

protected:

  //---- Data :
  unsigned int m_BitPosition, m_BytePosition;
  unsigned int m_NbReadBytesTotal;
};


class ExportedByCATSobObjects CATSobStream
{
public:

  enum open_mode { in     = 0x01,
                   out    = 0x02,
                   binary = 0x04,
                   ascii  = 0x08 };

  virtual ~CATSobStream();

  virtual void Close() = 0;
  
  //Ecriture en Ascii
  virtual CATSobStream& operator<<(const int) { return *this; }
  virtual CATSobStream& operator<<(const double) { return *this; }
  virtual CATSobStream& operator<<(const float) { return *this; }
  virtual CATSobStream& operator<<(const char*) { return *this; }
  virtual CATSobStream& operator<<(const char) { return *this; }

  //Lecture en Ascii
  virtual CATSobStream& operator>>(int&) { return *this; }
  virtual CATSobStream& operator>>(double&) { return *this; }
  virtual CATSobStream& operator>>(float&) { return *this; }
  virtual CATSobStream& operator>>(char&) { return *this; }

  //Ecriture en Binaire
  virtual CATSobDiag WriteInt(const int);
  virtual CATSobDiag WriteUInt(const unsigned int);
  virtual CATSobDiag WriteFloat(const float);
  virtual CATSobDiag WriteDouble(const double);
  virtual CATSobDiag WriteShort(const short*, const int);
  virtual CATSobDiag WriteInt(const int*, const int);
  virtual CATSobDiag WriteUInt(const unsigned int*, const int);
  virtual CATSobDiag WriteFloat(const float*, const int);
  virtual CATSobDiag WriteDouble(const double*, const int);
  virtual CATSobDiag WriteCATULONG32(const CATULONG32*, const int);
  virtual CATSobDiag WriteChar(const char*, const int);
  virtual CATSobDiag WriteUChar(const unsigned char*, const int);
  
  //Lecture en Binaire
  virtual CATSobDiag ReadDouble(double&);
  virtual CATSobDiag ReadShort(short* , const int);
  virtual CATSobDiag ReadInt(int*, const int);
  virtual CATSobDiag ReadUInt(unsigned int*, const int);
  virtual CATSobDiag ReadFloat(float*, const int);
  virtual CATSobDiag ReadDouble(double*, const int);
  virtual CATSobDiag ReadCATULONG32(CATULONG32*, const int);
  virtual CATSobDiag ReadChar(char*, const int);
  virtual CATSobDiag ReadUChar(unsigned char*, const int);


  //Pour le bit à bit
	CATSobDiag ReadBits(const unsigned short NbBits, unsigned char *buf, int iFirstBit = 0);
	CATSobDiag WriteBits(const unsigned short NbBits, const unsigned char *buf, int iFirstBit = 0); //Write effectif après Flush...
	
  CATSobDiag ReadFirstNBitsOfInt(const unsigned short iNbBits, int& oInt);
  CATSobDiag WriteFirstNBitsOfInt(const unsigned short iNbBits, const int iInt);
  
  CATSobDiag ReadFirstNBitsOfUInt(const unsigned short iNbBits, unsigned int& oUInt);
  CATSobDiag WriteFirstNBitsOfUInt(const unsigned short iNbBits, const unsigned int iUInt);

  CATSobDiag ReadFirstNBitsOfCATULONG32(const unsigned short iNbBits, CATULONG32& oCatULong32);
  CATSobDiag WriteFirstNBitsOfCATULONG32(const unsigned short iNbBits, const CATULONG32 iCatULong32);

  //Vidage du tampon
  CATSobDiag Flush();

	int GetNbBytesWritten();

  //Récupération de la position actuelle dans le stream
  virtual CATSobDiag GetCurrentPosition(CATSobStreamPosition*& opPosition);

  //Set de la position actuelle dans le stream
  virtual CATSobDiag SetCurrentPosition(const CATSobStreamPosition* ipNewPosition);


protected:

  CATSobStream(const int iMode);
  int IsEndOfBuffer();

  virtual CATSobDiag WriteCharImplement(const unsigned char* iBufferToWrite, const int iNbCharToWrite) = 0;
  virtual CATSobDiag ReadCharImplement(unsigned char* ioBuffer, const int iNbCharToRead, unsigned int& oNbCharRead) = 0;

  virtual CATSobDiag SetPositionInCurrentBuffer(const unsigned int iLocalByteIndexFromBeginning, unsigned char* iopBuffer, const unsigned int iMaxBytesToRead,
                                                unsigned int& oByteIndexInBuffer, unsigned int& oSizeUsedInBuffer) = 0;

  //Data used by nested classes
  short _IOMode;    //1 si ASCII, 0 sinon

private:

  // Copy constructor and equal operator
  CATSobStream (CATSobStream &);
  CATSobStream& operator=(CATSobStream&);

  //Pour le bit à bit
	void CopyBits(int                  NbBitsToCopy,
					      const unsigned char* iBuf,
					      int                  iPosiBuf,
					      unsigned char*       oBuf,
					      int                  iPosoBuf);

  //Ecriture par paquets
  CATSobDiag WriteCharOnBuffer(const char& aChar, const int iForceEmptyBuffer=0);
  CATSobDiag ReadCharFromBuffer(char& aChar);

  //Initilaisation du buffer
  void InitBuffer();


  int _NbWFreeBits;
	unsigned char _WUChar;
	int _NbRFreeBits;
	unsigned char _RUChar;
	unsigned int _NbWrittenBytes, _NbReadBytes;
  
  //Pour Lecture/Ecriture par paquets
  unsigned char _Buffer[SIZE_OF_BUFFER];
  unsigned int _BufferCounter, _SizeUsedInBuffer;
  CATBoolean _HasBeenFlushed;
};

// Fin de ligne
#define sdoendl "\n"

inline int CATSobStream::IsEndOfBuffer()
{
  return (_BufferCounter==_SizeUsedInBuffer);
}


#endif
