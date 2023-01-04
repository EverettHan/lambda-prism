//===========================================================================
// Copyright Dassault Systemes Provence 2004, All Rights Reserved 
//===========================================================================
//
// CATSobFStream.h
//
//===========================================================================
//
// Usage notes: Default stream for files
//
//===========================================================================
// 28.04.2015 : RAQ : Ajout SetPositionInCurrentBuffer suite au RI 366698
// October, 2005 : RAQ : Ajout fonction Open(...)
// June,    2004 : RAQ : Creation
//===========================================================================
#ifndef CATSobFStream_H
#define CATSobFStream_H

#include "CATSobStream.h"

class CATUnicodeString;

#include "CATSobObjects.h"

class ExportedByCATSobObjects CATSobFStream: public CATSobStream
{
public:

  CATSobFStream(const char* iFileName, int iMode);

  virtual ~CATSobFStream();

  //Ouverture d'un fichier
  virtual int Open(const char* iFileName, int iMode);
  
  //Test d'ouverture
  virtual int IsOpen();

  //Fermeture du stream
  virtual void Close();

  //Seek & Tell
  void Seek(const int iOffset, const int iOrigine);
  int Tell();

  //Eof
  int Eof();

  //Les modes
  void SetMode(int iMode);

  //Pour la lecture et l'écriture en ascii, c'est plus pratique
  virtual CATSobStream& operator<<(const int);
  virtual CATSobStream& operator<<(const double);
  virtual CATSobStream& operator<<(const float);
  virtual CATSobStream& operator<<(const char*);
  virtual CATSobStream& operator<<(const char);

  virtual CATSobStream& operator>>(int&);
  virtual CATSobStream& operator>>(double&);
  virtual CATSobStream& operator>>(float&);
  virtual CATSobStream& operator>>(char&);

  //Lecture d'une ligne
  CATSobDiag GetLine(char* ioBuffer, const int iBufferSize, const char iDelimiter = '\n');

protected:

  virtual CATSobDiag WriteCharImplement(const unsigned char*, const int);
  virtual CATSobDiag ReadCharImplement(unsigned char* iBuffer, const int iNbChar, unsigned int& oNbCharRead);

  virtual CATSobDiag SetPositionInCurrentBuffer(const unsigned int iLocalByteIndexFromBeginning, unsigned char* iopBuffer, const unsigned int iMaxBytesToRead,
                                                              unsigned int& oByteIndexInBuffer, unsigned int& oSizeUsedInBuffer);

private:

  // Copy constructor and equal operator
  CATSobFStream(CATSobFStream&);
  CATSobFStream& operator=(CATSobFStream&);

  unsigned int _FileID;
  CATUnicodeString* _FileName;
  int _NbCharRead;  //Pour Seek et Tell
  char _DecimalSeparatorChar;
  unsigned int _OffsetPosInStream, _CurrentStartBlockPosInStream, _CurrentEndBlockPosInStream;
};


#endif

