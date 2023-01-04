#ifndef CATMathStreamDef_h
#define CATMathStreamDef_h

// COPYRIGHT DASSAULT SYSTEMES  1999
#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
//#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"

/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

/** 
 * Define the direction of the stream.
 * @param CatCGMStreamReadOnly
 * The stream is read and cannot be written.
 * @param CatCGMStreamWriteOnly
 * The stream is written and not read.
 * @param CatCGMStreamReadWrite
 * The stream can be written and read.
 */
enum CATCGMStreamType 
{
  CatCGMStreamReadOnly  = +28,
  CatCGMStreamWriteOnly = +11,
  CatCGMStreamReadWrite = +66
};


/** @nodoc */
enum CATCGMStreamStorage 
{ 
  CatCGMStream_istream   = +17,
  CatCGMStream_ostream   = +45,
  CatCGMStream_FileName  = +78,
  CatCGMStream_memory    = +57,
  CatCGMStream_CATStream = +66
};


#endif

