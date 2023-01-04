#ifndef CATCompactStreamBits_H
#define CATCompactStreamBits_H
//
// COPYRIGHT DASSAULT SYSTEMES 2003
//
//===================================================================
// December 2003 - ALA - Creation
//===================================================================
//
#include "CATMathStream.h"
#include "CompactFunction.h"


class ExportedByCompactFunction CATCompactStreamBits  
{
  public:
	//
	  // return 0 if OK
	virtual int  Read(const unsigned short NbBits, unsigned char *buf, int FirstBit = 0)  = 0;
	  // return 0 if OK
	virtual int ReadDouble(double &oV) = 0;
	//
	// note that a write is effective only after a flush() operation !!
	  // return 0 if OK
	virtual int  Write(const unsigned short NbBits, const unsigned char *buf, int FirstBit = 0) = 0;
	  // return 0 if OK
	virtual int  WriteDouble(const double &iV) = 0;
	  //
	/////////////////////////////
	// flush()  write effectively  ...
	// return the number of bytes writen since last flush or begining
	virtual int Flush() = 0;
};
#endif
