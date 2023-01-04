#ifndef CATMathStream_h
#define CATMathStream_h
// COPYRIGHT DASSAULT SYSTEMES  1999
/**
 * @CAA2Level L1
 * @CAA2Usage U1
 */ 

#include "CATIACGMLevel.h"
#include "CATIAV5Level.h"

#include "ExportedByCATMathStream.h"
#include "CATCGMVirtual.h"

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif

#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class istream;
#endif

#include "CATBoolean.h"
#include "CATMathStreamDef.h"
#include "CATDataType.h"
#include "CATCGMNewArray.h"
#include "CATMathInline.h"

class CATMathStreamImpl;
class CATStream;
class CATMathBox;
class CATMathPoint;
class CATMathVector2D;
class CATMathVector;
class CATMath3x3Matrix;
class CATMathTransformation;
class CATMathPlane;
class CATMathAxis;
class CATUuid;
class CATSoftwareConfiguration;


/**
 * Base class of the stream and unstream operations.
 */
class ExportedByCATMathStream CATMathStream : public CATCGMVirtual 
{
public:
  
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
  //
  //            C A A             M E T H O D S
  //
  //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

 /**
  * Constructs CATMathStream for stream operation (read and write acces are allowed).
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(CATMathStreamImpl* ipImpl = NULL);

 /**
  * Constructs CATMathStream for read only stream operation.
  * @param iBuffer
  *  The memory area directly acceded for the read operation.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(void*              iBuffer,
                size_t             iSizeBuffer,
                CATMathStreamImpl* ipImpl = NULL);
  
 /**
  * Constructs CATMathStream for write only stream operation.
  * @param ioFile
  * The stream on which the stream is saved.
  * @param iInitialNumberOfBytes
  *  The initial memory size of internal buffer in bytes.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use. Do not change the default value.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(ostream&           ioFile,
                size_t             iInitialNumberOfBytes = 0,
                const CATBoolean   iEnableByAddress = FALSE,
                CATMathStreamImpl* ipImpl = NULL);
  
 /**
  * Constructs CATMathStream for read only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * <br>The first acces of the stream may be done with <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseWriteStreamHeader</tt>.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(istream&           ioFile,
                CATMathStreamImpl* ipImpl = NULL);

 /**
  * Constructs CATMathStream for read only or write only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStream.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use. Do not change the default value.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(const char*            iFilename,
                const CATCGMStreamType iAcces,
                const CATBoolean       iEnableByAddress = FALSE,
                CATMathStreamImpl*     ipImpl = NULL);

 /**
  * Constructs CATMathStream for stream operation.
  * @param iInitialNumberOfBytes
  *  The initial number of bytes for internal buffer.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStream.
  * @param iEnableByAddress
  *  Reserved for future use. Do not change the default value.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(size_t                 iInitialNumberOfBytes,
                const CATCGMStreamType iAcces,
                const CATBoolean       iEnableByAddress = FALSE,
                CATMathStreamImpl*     ipImpl = NULL);

 /**
  * @nodoc
  * Constructs CATMathStream for read only or write only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read or writen.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStream.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use. Do not change the default value.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(CATStream&             iDirectStreaming,
                const CATCGMStreamType iAcces,
                const CATBoolean       iEnableByAddress = FALSE,
                CATMathStreamImpl*     ipImpl = NULL);

 /**
  * @nodoc
  * Constructs CATMathStream for read only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read.
  * @param iSizeStream
  *  The size in bytes of <tt>iDirectStreaming</tt>.
  * @param ipMathStreamImpl
  *  Internal use only. Do not change the default value.
  */
  CATMathStream(CATStream&         iDirectStreaming,
                size_t             iSizeStream,
                CATMathStreamImpl* ipImpl = NULL);

 /**
  * Destructor
  */
  virtual ~CATMathStream();

 /**
  * Clear the Contents of the current Stream.
  */
  void Clear();
  
 /**
  * Returns the length of <tt>this</tt>.
  * @return
  * The length.
  */
  size_t GetLength() const;
  
 /**
  * Returns the current position.
  */
  size_t GetCurrentPosition() const;

 /**
  * Skips of a given length.
  */
  void Advance(size_t iSiz);

 /**
  * Resets the position to the beginning.
  */
  void Reset();

 /**
  * Get the CATMathStream contents in a memory area.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>, given to avoid overwriting.
  * @param iBuffer
  *  The memory area where bytes are copied.
  * @param ioSizeCopied
  *  Number of bytes copied in <tt>iBuffer</tt>.
  */
  void GetMemoryCopy(const size_t iSizeBuffer, void * ioBuffer, size_t & ioSizeCopied) const;

 /**
  * Writes the content of a stream on <tt>this</tt>.
  * @param iToWrite
  * The stream
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteStream(const CATMathStream& iToWrite, const char iReservedLabel[] = "");

 /**
  * Reads a stream on <tt>this</tt>.
  * @param iToRead
  * The stream to read.
  * @param iLengthToRead
  * the length of <tt>iToRead</tt>.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadStream(CATMathStream& iToRead, size_t iLengthToRead, const char iReservedLabel[] = "");

 /**
  * Open a CATMathStream for write acces.
  * @param oWhere
  *  internal parameter you must give back at <tt>CloseWriteStreamHeader</tt>.
  * @param oLevel
  *  internal parameter you must give back at <tt>CloseWriteStreamHeader</tt>.
  * @param iWithEndianFormat
  *  little big endian format is written, allowing interoperability between different Operating Systems
  */
  void OpenWriteStreamHeader(size_t& oWhere, short& oLevel, const short iWithEndianFormat = 1);

 /**
  * Open a CATMathStream for read acces.
  * @param oWhere
  *  internal parameter you must give back at <tt>CloseReadStreamHeader</tt>.
  * @param oLevel
  *  internal parameter you must give back at <tt>CloseReadStreamHeader</tt>.
  * @param iWithEndianFormat
  *  little big endian format is written, allowing interoperability between different Operating Systems
  */
  void OpenReadStreamHeader(size_t& oWhere, short& oLevel, const short iWithEndianFormat = 1);

 /**
  * Close a CATMathStream for write acces.
  * @param iWhere
  *  internal parameter given by <tt>OpenWriteStreamHeader</tt>.
  * @param iLevel
  *  internal parameter given by  <tt>OpenWriteStreamHeader</tt>.
  */
  void CloseWriteStreamHeader(const size_t iWhere, const short iLevel);

 /**
  * Close a CATMathStream for read acces.
  * @param iWhere
  *  internal parameter given by <tt>CloseReadStreamHeader</tt>.
  * @param iLevel
  *  internal parameter given by  <tt>CloseReadStreamHeader</tt>.
  */
  void CloseReadStreamHeader(const size_t iWhere, const short iLevel);

 /**
  * Writes an CATBoolean.
  * @param iBoolean
  * The CATBoolean to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteBoolean(const CATBoolean iBoolean, const char iReservedLabel[] = "");

 /**
  * Reads an CATBoolean.
  * @param iBoolean
  * The read CATBoolean. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadBoolean(CATBoolean& ioBoolean, const char iReservedLabel[] = "");

 /**
  * Writes an unsigned char.
  * @param iUChar
  * The unsigned char to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteUChar(const unsigned char iUChar, const char iReservedLabel[] = "");

 /**
  * Reads an unsigned char.
  * @param ioUChar
  * The read char. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadUChar(unsigned char& ioUChar, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of unsigned chars.
  * @param iUCharArray
  * The array of unsigned chars to write.
  * @param iNbCell
  * The count of unsigned chars to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteUChar(const unsigned char* iUCharArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads an array of unsigned chars.
  * @param ioArrayUChar
  * The array of unsigned chars to write.
  * @param iNbCell
  * The size of <tt>ioArrayUChar</tt>. If the the count of UChars to read is greater than <tt>iNbCell</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadUChar(unsigned char* ioArrayUChar, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes a short integer.
  * @param iShort
  * The short to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteShort(const short iShort, const char iReservedLabel[] = "");

 /**
  * Reads a short integer.
  * @param ioShort
  * The read short integer. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadShort(short& ioShort, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of short integers.
  * @param iShortArray
  * The array of shorts to write.
  * @param iNbCell
  * The count of shorts to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteShort(const short* iShortArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads an array of short integers.
  * @param ioArrayShort
  * The array of short integers to write.
  * @param iNbCell
  * The size of <tt>ioArrayShort</tt>. If the the count of short integers to read is greater than <tt>iNbCell</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadShort(short* ioArrayShort, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes an unsigned short integer.
  * @param iUShort
  * The unsigned short to write. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
   void WriteUShort(const unsigned short iUShort, const char iReservedLabel[] = "");

 /**
  * Reads an unsigned short integer.
  * @param ioUShort
  * The read unsigned short integer.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadUShort(unsigned short& ioUShort, const char iReservedLabel[] = "");

 /**
  * Writes a CATLONG32 integer.
  * @param iLong
  * The CATLONG32 to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteLong(const CATLONG32 iLong, const char iReservedLabel[] = "");

 /**
  * Reads a CATLONG32 integer.
  * @param ioLong
  * The read CATLONG32 integer.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadLong(CATLONG32& ioLong, const char iReservedLabel[] = "");
  
 /**
  * Writes a sequence of CATLONG32 integers.
  * @param iLongArray
  * The array of longs to write.
  * @param iNbCell
  * The count of longs to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteLong(const CATLONG32* iLongArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads a CATLONG32 integer.
  * @param ioLong
  * The read CATLONG32 integer.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadLong(CATLONG32* ioArrayLong, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes an CATULONG32  integer.
  * @param iULong
  * The CATULONG32  to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteULong(const CATULONG32 iULong, const char iReservedLabel[] = "");

 /**
  * Reads an CATULONG32  integer.
  * @param ioULong
  * The read unsigned short integer.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadULong(CATULONG32& ioULong, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of CATULONG32  integers.
  * @param iULongArray
  * The array of CATULONG32s to write.
  * @param iNbCell
  * The count of CATULONG32s to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteULong(const CATULONG32* iULongArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads an array of CATULONG32  integers.
  * @param ioArrayULong
  * The array of CATLONG32 integers to write.
  * @param iNbCell
  * The size of <tt>ioArrayULong</tt>. If the the count of CATLONG32 integers to read is greater than <tt>iNbCell</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadULong(CATULONG32* ioArrayULong , const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes a double.
  * @param iDouble
  * The double to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteDouble(const double iDouble, const char iReservedLabel[] = "");

 /**
  * Reads a double.
  * @param ioDouble
  * The read double.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadDouble(double& ioDouble, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of doubles.
  * @param iDoubleArray
  * The array of doubles to write.
  * @param iNbCell
  * The count of doubles to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteDouble(const double* iDoubleArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads an array of doubles.
  * @param ioArrayDouble
  * The array of doubles to write.
  * @param iNbCell
  * The size of <tt>ioArrayDouble</tt>. If the the count of doubles to read is greater than <tt>iNbCell</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadDouble(double* ioArrayDouble, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes a float.
  * @param iFloat
  * The float to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteFloat(const float iFloat, const char iReservedLabel[] = "");

 /**
  * Reads a float.
  * @param ioFloat
  * The read float.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadFloat(float& ioFloat, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of floats.
  * @param iFloatArray
  * The array of floats to write.
  * @param iNbCell
  * The count of floats to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteFloat(const float* iFloatArray, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Reads an array of floats.
  * @param ioArrayFloat
  * The array of floats to write.
  * @param iNbCell
  * The size of <tt>ioArrayFloat</tt>. If the the count of floats to read is greater than <tt>iNbCell</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadFloat(float* ioArrayFloat, const CATLONG32 iNbCell, const char iReservedLabel[] = "");

 /**
  * Writes a string.
  * @param iString
  * The string to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteString(const char* iString, const char iReservedLabel[] = "");

 /**
  * Reads a string.
  * @param ioString
  * The read string.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadString(char*& ioString, const char iReservedLabel[] = "");

 /**
  * Writes a CATMathBox.
  * @param iBox
  * The box to write. The box is written with floats, precision can be lost. 
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteBox(const CATMathBox& ioBox, const char iReservedLabel[] = "");

 /**
  * Reads a CATMathBox.
  * @param ioBox
  * The read box.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadBox(CATMathBox& ioBox, const char iReservedLabel[] = "");

 /**
  * Writes a CATMathPoint.
  * @param ioPoint
  * The CATMathPoint to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WritePoint(const CATMathPoint& ioPoint, const char iReservedLabel[] = "");

 /**
  * Reads a CATMathPoint.
  * @param ioPoint
  * The read CATMathPoint.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadPoint(CATMathPoint& ioPoint, const char iReservedLabel[] = "");
  
 /**
  * Writes a CATMathVector2D.
  * @param ioVector2D
  * The CATMathVector2D to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteVector2D(const CATMathVector2D& ioVector2D, const char iReservedLabel[] = "");

 /**
  * Reads a CATMathVector2D.
  * @param ioVector2D
  * The read CATMathVector2D.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadVector2D(CATMathVector2D& ioVector2D, const char iReservedLabel[] = "");
  
 /**
  * Writes a CATMathVector.
  * @param ioVector
  * The CATMathVector to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteVector(const CATMathVector& ioVector, const char iReservedLabel[] = "");
  
 /**
  * Reads a CATMathVector.
  * @param ioVector
  * The read CATMathVector.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadVector(CATMathVector& ioVector, const char iReservedLabel[] = "");

 /**
  * Writes a CATMath3x3Matrix.
  * @param ioMatrix
  * The CATMath3x3Matrix to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void Write3x3Matrix(const CATMath3x3Matrix& ioMatrix, const char iReservedLabel[] = "");

 /**
  * Reads a CATMath3x3Matrix.
  * @param ioMatrix
  * The read CATMath3x3Matrix.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void Read3x3Matrix(CATMath3x3Matrix& ioMatrix, const char iReservedLabel[] = "");
  
 /**
  * Writes a CATMathTransformation.
  * @param ioTransfo
  * The CATMathTransformation to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteTransformation(const CATMathTransformation& ioTransfo, const char iReservedLabel[] = "");
 
 /**
  * Reads a CATMathTransformation.
  * @param ioTransfo
  * The read CATMathTransformation.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadTransformation(CATMathTransformation& ioTransfo, const char iReservedLabel[] = "");
  
 /**
  * Writes a CATMathPlane.
  * @param ioPlane
  * The CATMathPlane to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WritePlane(const CATMathPlane& ioPlane, const char iReservedLabel[] = "");

 /**
  * Reads a CATMathPlane.
  * @param ioPlane
  * The read CATMathPlane.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadPlane(CATMathPlane& ioPlane, const char iReservedLabel[] = "");
  
 /**
  * Writes a CATMathAxis.
  * @param ioAxis
  * The CATMathAxis to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteAxis(const CATMathAxis& ioAxis, const char iReservedLabel[] = "");
  
 /**
  * Reads a CATMathAxis.
  * @param ioAxis
  * The read CATMathAxis.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadAxis(CATMathAxis& ioAxis, const char iReservedLabel[] = "");

 /**
  * Writes a CATUuid.
  * @param iid
  * The CATUuid to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteCATUuid(const CATUuid& iid, const char iReservedLabel[] = "");
  
 /**
  * Reads a CATUuid.
  * @param iid
  * The read CATUuid.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadCATUuid(CATUuid& iid, const char iReservedLabel[] = "");

 /**
  * Writes a CATSoftwareConfiguration.
  * @param iConfig
  * The CATSoftwareConfiguration to write.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void WriteConfig(const CATSoftwareConfiguration& iConfig, const char iReservedLabel[] = "");
  
 /**
  * Reads a CATSoftwareConfiguration.
  * @param iConfig
  * The read CATSoftwareConfiguration.
  * @param iReservedLabel
  * Reserved for future use. Do not change the default value.
  */
  void ReadConfig(CATSoftwareConfiguration& ioConfig, const char iReservedLabel[] = "");
  
 /**
  * @nodoc
  * For internal use only. Do not use.
  * Retrieve <tt>this</tt> internal data class instance.
  */
  INLINE void* GetImpl();

 /**
  * @nodoc
  * Do not use : for internal use only.
  */
  CATCGMNewClassArrayDeclare;

protected :

 /**
  * For internal use only. Do not use.
  * Internal data class;
  */
  CATMathStreamImpl* _pImpl;


 

private :

  /** @nodoc  forbidden functionnality */
  CATMathStream(const CATMathStream&);

  /** @nodoc   forbidden functionnality */
  CATMathStream& operator=(const CATMathStream&);
 

};

//-----------------------------------------------------------------------------
// GetImpl
//-----------------------------------------------------------------------------
INLINE void* CATMathStream::GetImpl()
{
  return (void*)_pImpl;
}
//-----------------------------------------------------------------------------

#endif

