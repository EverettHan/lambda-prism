/* -*-c++-*- */

/**
 * @COPYRIGHT DASSAULT SYSTEMES 2005
 */

#ifndef CATMathStreamImpl_h
#define CATMathStreamImpl_h

//=============================================================================
// DESCRIPTION : Class implementing CATMathStream
//=============================================================================
// Apr.  05 HCN Creation
// May   05 HCN IsCompact(..) : _VersionNumber == CatCGMStream_V5R18GA
//              IsLossAllowed(...) _VersionNumber == CatCGMStream_V5R19GA
//
// 14/01/09     Split in Private original (V5R5) and 2004 Stream prototype
//              Bring new proposal of Stream Header
// Jul.  09 VUC Suppression du StreamCompact
// Sep   10 PR  Optimization with _pNurbsSurfaceBuffer and _Pool
// Oct.  16 KY1 Read Soft Config Service with argument to specify
//              Open or Closed Config
//=============================================================================

#include "CATIAV5Level.h"
#include "CATIACGMLevel.h"
#include "CATCGMStreamVersionUtilities.h" // A remplacer par class...
#include "CATMathStream.h"                // A remplacer par class...
#include "CATMathStreamVersionDef.h"


#include "stdio.h"

#define CGMSTR_SET_BIT_8( unsigned_char )           ( unsigned_char ) |= 0x80
#define CGMSTR_SET_BIT_7( unsigned_char )           ( unsigned_char ) |= 0x40
#define CGMSTR_SET_BIT_6( unsigned_char )           ( unsigned_char ) |= 0x20
#define CGMSTR_SET_BIT_5( unsigned_char )           ( unsigned_char ) |= 0x10
#define CGMSTR_SET_BIT_4( unsigned_char )           ( unsigned_char ) |= 0x08
#define CGMSTR_SET_BIT_3( unsigned_char )           ( unsigned_char ) |= 0x04
#define CGMSTR_SET_BIT_2( unsigned_char )           ( unsigned_char ) |= 0x02
#define CGMSTR_SET_BIT_1( unsigned_char )           ( unsigned_char ) |= 0x01

#define CGMSTR_SET_BIT_87( unsigned_char )          ( unsigned_char ) |= 0xC0
#define CGMSTR_SET_BIT_876( unsigned_char )         ( unsigned_char ) |= 0xE0
#define CGMSTR_SET_BIT_8765( unsigned_char )        ( unsigned_char ) |= 0xF0
#define CGMSTR_SET_BIT_87654( unsigned_char )       ( unsigned_char ) |= 0xF8
#define CGMSTR_SET_BIT_876543( unsigned_char )      ( unsigned_char ) |= 0xFC
#define CGMSTR_SET_BIT_8765432( unsigned_char )     ( unsigned_char ) |= 0xFE

#define CGMSTR_SET_BIT_21( unsigned_char )          ( unsigned_char ) |= 0x03
#define CGMSTR_SET_BIT_321( unsigned_char )         ( unsigned_char ) |= 0x07
#define CGMSTR_SET_BIT_4321( unsigned_char )        ( unsigned_char ) |= 0x0F
#define CGMSTR_SET_BIT_54321( unsigned_char )       ( unsigned_char ) |= 0x1F
#define CGMSTR_SET_BIT_654321( unsigned_char )      ( unsigned_char ) |= 0x3F
#define CGMSTR_SET_BIT_7654321( unsigned_char )     ( unsigned_char ) |= 0x7F

#define CGMSTR_SET_BIT_765( unsigned_char )         ( unsigned_char ) |= 0x70
#define CGMSTR_SET_BIT_654( unsigned_char )         ( unsigned_char ) |= 0x38
#define CGMSTR_SET_BIT_543( unsigned_char )         ( unsigned_char ) |= 0x1C
#define CGMSTR_SET_BIT_432( unsigned_char )         ( unsigned_char ) |= 0x0E





#define CGMSTR_BIT_8( unsigned_char )              (( unsigned_char ) & 0x80 )
#define CGMSTR_BIT_7( unsigned_char )              (( unsigned_char ) & 0x40 )
#define CGMSTR_BIT_6( unsigned_char )              (( unsigned_char ) & 0x20 )
#define CGMSTR_BIT_5( unsigned_char )              (( unsigned_char ) & 0x10 )
#define CGMSTR_BIT_4( unsigned_char )              (( unsigned_char ) & 0x08 )
#define CGMSTR_BIT_3( unsigned_char )              (( unsigned_char ) & 0x04 )
#define CGMSTR_BIT_2( unsigned_char )              (( unsigned_char ) & 0x02 )
#define CGMSTR_BIT_1( unsigned_char )              (( unsigned_char ) & 0x01 )

#define CGMSTR_BIT_87( unsigned_char )             (( unsigned_char ) & 0xC0 )
#define CGMSTR_BIT_876( unsigned_char )            (( unsigned_char ) & 0xE0 )
#define CGMSTR_BIT_8765( unsigned_char )           (( unsigned_char ) & 0xF0 )
#define CGMSTR_BIT_87654( unsigned_char )          (( unsigned_char ) & 0xF8 )
#define CGMSTR_BIT_876543( unsigned_char )         (( unsigned_char ) & 0xFC )
#define CGMSTR_BIT_8765432( unsigned_char )        (( unsigned_char ) & 0xFE )

#define CGMSTR_BIT_21( unsigned_char )             (( unsigned_char ) & 0x03 )
#define CGMSTR_BIT_321( unsigned_char )            (( unsigned_char ) & 0x07 )
#define CGMSTR_BIT_4321( unsigned_char )           (( unsigned_char ) & 0x0F )
#define CGMSTR_BIT_54321( unsigned_char )          (( unsigned_char ) & 0x1F )
#define CGMSTR_BIT_654321( unsigned_char )         (( unsigned_char ) & 0x3F )
#define CGMSTR_BIT_7654321( unsigned_char )        (( unsigned_char ) & 0x7F )

#define CGMSTR_BIT_76( unsigned_char )             (( unsigned_char ) & 0x60 )
#define CGMSTR_BIT_65( unsigned_char )             (( unsigned_char ) & 0x30 )
#define CGMSTR_BIT_54( unsigned_char )             (( unsigned_char ) & 0x18 )
#define CGMSTR_BIT_43( unsigned_char )             (( unsigned_char ) & 0x0C )
#define CGMSTR_BIT_32( unsigned_char )             (( unsigned_char ) & 0x06 )

#define CGMSTR_BIT_765( unsigned_char )            (( unsigned_char ) & 0x70 )
#define CGMSTR_BIT_654( unsigned_char )            (( unsigned_char ) & 0x38 )
#define CGMSTR_BIT_543( unsigned_char )            (( unsigned_char ) & 0x1C )
#define CGMSTR_BIT_432( unsigned_char )            (( unsigned_char ) & 0x0E )

#include "ExportedByCATMathStream.h"
#include "CATBoolean.h"
#include "CATErrorDef.h"
#include "CATMathStreamDef.h"
#include "CATCGMNewArray.h"
#include "CATBaseUnknown.h"
#include "CATCGMBuildDebug.h"
#include "CATCGMVirtual.h"
#include "CATDataType.h"
#include "CATListOfInt.h"
#include "CATThrowForNullPointer.h"
#include "CATMathInline.h"
#include "CATCGMStreamVersion.h"
#include "CATLISTV_CATBaseUnknown.h" 
#include "CATListPV.h" 
 
#include "CATLib.h"

#include "CATCGMMapCATULONGPTR.h"
#include "BigLittle.h"

#include "CATCGMUnknown.h"
#include "CATGMAdapter.h"


// NurbsCompact Optim PR
//#define NurbsCompactOptimPR

#include "CATCGMStreamControl.h"

struct CATMathStreamStats;
struct CATCGMHeaderObjectStream;
struct CATCGMAttrHeaderStream;
struct CATCGMHeaderUserAttrRef;

class CATMathStreamBlocs;
class CATCGMBinaryStream;
class CATSoftwareConfiguration;

struct CGMHeaderStream;
class CATMathBox;
class CATMathPoint;
class CATMathPointf;
class CATMathVector2D;
class CATMathVector;
class CATMathVectorf;
class CATMathAxis;
class CATMathStreamDump;
class CATMathStreamDumpImpl;
class CATTrace;
class CATCGMStream;
class CATCGMStreamImpl;
class CATCGMStreamCGMImpl;
class CATCGMStreamCoverageInteger;
class CATechSet;
class CATCGM_STREAM;
class CATechSet;
class CATechAttribute;

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

class CATICGMObject;
class CATExtCGMReplay;
class CATUuid;
class CATStream;
class CATCGMHashTableWithAssoc;
class CATCGMStreamCGMImpl;

#ifdef NurbsCompactOptimPR
class CATMathPoolThread;
#endif 

class CATMath3x3Matrix;
class CATMathTransformation;
class CATMathPlane;
class CATMathAdvancedBox;
 

#if defined ( CATCGMBuildDebug )
  
#define CATMathStreamReadingTooFar CATMathStreamImpl::ThrowOnReadingTooFar(__FILE__,__LINE__)
  
#define CATMathStreamInvalidValue  CATMathStreamImpl::InvalidValue(__FILE__,__LINE__)

#else // #if defined ( CATCGMBuildDebug )
  
#define CATMathStreamReadingTooFar CATMathStreamImpl::ThrowOnReadingTooFar(NULL,0)
  
#define CATMathStreamInvalidValue  CATMathStreamImpl::InvalidValue(NULL,0)

#endif // #if defined ( CATCGMBuildDebug ) ... #else ...


#define CATCGMStreamDumpComment( comment )                     \
  if (pStrImpl->DumpIsActive())                                \
     pStrImpl->DumpComment( comment );

#define CATCGMStreamDumpCommentBEGIN( comment )                \
{                                                              \
  if (pStrImpl->DumpIsActive())                                \
     pStrImpl->DumpCommentBegin( comment, 0 );

#define CATCGMStreamDumpXMLCommentBEGIN( XMLcomment, comment ) \
{                                                              \
  if (pStrImpl->DumpIsActive())                                \
  {                                                            \
    if (pStrImpl->DumpXMLFormat())                             \
      pStrImpl->DumpCommentBegin( XMLcomment, 0 );             \
    else                                                       \
      pStrImpl->DumpCommentBegin( comment, 0 );                \
  }

#define CATCGMStreamDumpCommentEND                             \
  if (pStrImpl->DumpIsActive())                                \
     pStrImpl->DumpCommentEnd();                               \
}

/**
* Base class of the stream and unstream operations.
*/
class ExportedByCATMathStream CATMathStreamImpl : public CATCGMUnknown 
{
public :

    
   /**
   *  In Case of Data Change inside Binary Format
   *     Changes are easily managed through default MACRO 
   *     of CATCGMStreamIsNewerThanOrEqualTo() 
   */
  INLINE CATCGMStreamVersion GetVersionNumber() const;



   /**
   *   Inside commercial composite documents (CATPart, CATShape, ... )
   *       and  CAA - Internal (NCGM, CGMReplay, PlayBack, ..) files 
   *   The format version is automatically managed internally 
   *      through labels assigned inside CATCGMStreamVersionLimited.h  
   *
   *   In other cases, the direct reuse of CATMathSream-CATCGMStream implementation outside CATGeoFactory 
   *      version is not yet assigned by previous context 
   *
   *   The NCGM management can easily be herited from above management
   *     
   *      CATMathStream  & Str;
   *
   *      CATMathStreamImpl* pImpl = (CATMathStreamImpl*)iStr.GetImpl();
   *      if ( ! pImpl ) CATThrowForNullPointer();
   *
   *      If (  CatCGMStream_UnknownVersion == pImpl->GetVersionNumber()  )
   *          pImpl->BootSingleVersion();
   * 
   *   CATCGMStreamVersion CurrentFormat = pImpl->GetVersionNumber();
   *
   */
  void  BootSingleVersion();


 /**
  * Constructs CATMathStreamImpl for stream operation (read and write acces are allowed).
  */
  CATMathStreamImpl(CATMathStream* ipItf);

 /**
  * Constructs CATMathStreamImpl for read only stream operation.
  * @param iBuffer
  *  The memory area directly acceded for the read operation.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>.
  */
  CATMathStreamImpl(void*          iBuffer,
                    size_t         iSizeBuffer,
                    CATMathStream* ipItf);
  
 /**
  * Constructs CATMathStreamImpl for write only stream operation.
  * @param ioFile
  * The stream on which the stream is saved.
  * @param iInitialNumberOfBytes
  *  The initial memory size of internal buffer in bytes.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  */
  CATMathStreamImpl(ostream&         ioFile,
                    size_t           iInitialNumberOfBytes,
                    const CATBoolean iEnableByAddress,
                    CATMathStream*   ipItf);
  
 /**
  * Constructs CATMathStreamImpl for read only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * <br>The first acces of the stream may be done with <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseWriteStreamHeader</tt>.
  */
  CATMathStreamImpl(istream&       ioFile,
                    CATMathStream* ipItf);

 /**
  * Constructs CATMathStreamImpl for read only or write only stream operation.
  * @param ioFile
  * The stream from which the stream is read.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStreamImpl.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  */
  CATMathStreamImpl(const char*            iFilename,
                    const CATCGMStreamType iAcces,
                    const CATBoolean       iEnableByAddress,
                          CATMathStream*   ipItf);

 /**
  * Constructs CATMathStreamImpl for stream operation.
  * @param iInitialNumberOfBytes
  *  The initial number of bytes for internal buffer.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStreamImpl.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  */
  CATMathStreamImpl(      size_t           iInitialNumberOfBytes,
                    const CATCGMStreamType iAcces,
                    const CATBoolean       iEnableByAddress,
                          CATMathStream*   ipItf);

 /**
  * @nodoc
  * Constructs CATMathStreamImpl for read only or write only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read or writen.
  * @param iAcces
  *  The kind of acces allowed on the CATMathStreamImpl.
  * <br>The first acces of the stream may be done with <tt>OpenReadStreamHeader</tt> or <tt>OpenWriteStreamHeader</tt>.
  * <br>The last acces of the stream may be done with <tt>CloseReadStreamHeader</tt> or <tt>CloseWriteStreamHeader</tt>.
  * @param iEnableByAddress
  *  Reserved for future use (do not change the default value)
  */
  CATMathStreamImpl(      CATStream&       iDirectStreaming,
                    const CATCGMStreamType iAcces,
                    const CATBoolean       iEnableByAddress,
                          CATMathStream*   ipItf);

 /**
  * @nodoc
  * Constructs CATMathStreamImpl for read only stream operation.
  * @param iDirectStreaming
  * The stream from which the stream is read.
  * @param iSizeStream
  *  The size in bytes of <tt>iDirectStreaming</tt>.
  */
  CATMathStreamImpl(CATStream&     iDirectStreaming,
                    size_t         iSizeStream,
                    CATMathStream* ipItf);

 
  virtual ~CATMathStreamImpl();

 
  CATCGMNewClassArrayDeclare;

//-----------------------------------------------------------------------------
// Clear...
//-----------------------------------------------------------------------------

 /**
  * Clear the Contents of the current Stream.
  */
  void Clear();

#ifdef NurbsCompactOptimPR
//-----------------------------------------------------------------------------
// Thread pool
//-----------------------------------------------------------------------------
  CATMathPoolThread* GetPool() const;
#endif
//-----------------------------------------------------------------------------
// Cast...
//-----------------------------------------------------------------------------

  virtual CATCGMStream*        CastToCATCGMStream();

  virtual CATCGMStreamImpl*    CastToCATCGMStreamImpl();
 
  virtual CATCGMStreamCGMImpl* CastToCATCGMStreamCGMImpl();

  INLINE void* GetItf();

  CATBoolean IsEqualTo(const CATMathStreamImpl* iCompare) const;

  int GetNumberOfStartingEqualBytes(const CATMathStreamImpl* iCompare) const;

  const char* IsFilenamed();

  void SetFilenamed( const char* iIsFilenamed );


//-----------------------------------------------------------------------------
// Position...
//-----------------------------------------------------------------------------
  
 /**
  * Returns the length of <tt>this</tt>.
  * @return
  * The length.
  */
  INLINE size_t GetLength() const;
  
 /**
  * Returns the current position.
  */
  INLINE size_t GetCurrentPosition() const;

 /**
  * Set the current position.
  */
  INLINE void SetCurrentPosition(size_t iIndex) ;
 /**
  * Skips of a given length.
  */
  INLINE void Advance(size_t iSiz);

 /**
  * Resets the position to the beginning.
  */
  INLINE void Reset();
  
 /**
  * Forbids the Write of the preceding portion of the CATStream
  * Permits the read of a part of the CATStream
  * Use it only if the CATStream is already containing information 
  * and after seeking to the correct index according to what you need
  */
  void InitCATStreamStartPosition();
//-----------------------------------------------------------------------------
// Stream...
//-----------------------------------------------------------------------------

 /**
  * Get the CATMathStreamImpl contents in a memory area.
  * @param iSizeBuffer
  *  The size in bytes of <tt>iBuffer</tt>, given to avoid overwriting.
  * @param iBuffer
  *  The memory area where bytes are copied.
  * @param ioSizeCopied
  *  Number of bytes copied in <tt>iBuffer</tt>.
  */
  void GetMemoryCopy(const size_t iSizeBuffer, void * ioBuffer, size_t & ioSizeCopied) const;

//-----------------------------------------------------------------------------
// Stream...
//-----------------------------------------------------------------------------

 /**
  * Writes the content of a stream on <tt>this</tt>.
  * @param iToWrite
  * The stream
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteStream(const CATMathStreamImpl& iToWrite, const char iReservedLabel[] = "");

 /**
  * Reads a stream on <tt>this</tt>.
  * @param iToRead
  * The stream to read.
  * @param iLengthToRead
  * the length of <tt>iToRead</tt>.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadStream(CATMathStreamImpl& iToRead, size_t iLengthToRead, const char iReservedLabel[] = "");

  void WriteWithStreamHeader(CATMathStreamImpl& ioStream, const short withEndianFormat = 1);

//-----------------------------------------------------------------------------
// Header...
//-----------------------------------------------------------------------------

 /**
  * Open a CATMathStreamImpl for write acces.
  * @param oWhere
  *  internal parameter you must give back at <tt>CloseWriteStreamHeader</tt>.
  * @param oLevel
  *  internal parameter you must give back at <tt>CloseWriteStreamHeader</tt>.
  * @param iWithEndianFormat
  *  little big endian format is written, allowing interoperability between different Operating Systems
  */
  void OpenWriteStreamHeader(size_t& oWhere, short& oLevel, const short iWithEndianFormat = 1);

 /**
  * Open a CATMathStreamImpl for read acces.
  * @param oWhere
  *  internal parameter you must give back at <tt>CloseReadStreamHeader</tt>.
  * @param oLevel
  *  internal parameter you must give back at <tt>CloseReadStreamHeader</tt>.
  * @param iWithEndianFormat
  *  little big endian format is written, allowing interoperability between different Operating Systems
  */
  void OpenReadStreamHeader(size_t& oWhere, short& oLevel, const short iWithEndianFormat = 1);

 /**
  * Close a CATMathStreamImpl for write acces.
  * @param iWhere
  *  internal parameter given by <tt>OpenWriteStreamHeader</tt>.
  * @param iLevel
  *  internal parameter given by  <tt>OpenWriteStreamHeader</tt>.
  */
  void CloseWriteStreamHeader(const size_t iWhere, const short iLevel);

 /**
  * Close a CATMathStreamImpl for read acces.
  * @param iWhere
  *  internal parameter given by <tt>CloseReadStreamHeader</tt>.
  * @param iLevel
  *  internal parameter given by  <tt>CloseReadStreamHeader</tt>.
  */
  void CloseReadStreamHeader(const size_t iWhere, const short iLevel);

  void OpenWriteObjectHeader(size_t& whereHeaderBegin, CATCGMHeaderObjectStream&   iHeader, const char iReservedLabel[] = "");
  
  void CloseWriteHeaderData(CATCGMHeaderObjectStream&   iHeader, const size_t whereHeaderBegin);
  
  void CloseWriteHeaderContainer(const size_t whereHeaderBegin);
  
  void CloseWriteHeaderDataContainer(const size_t whereHeaderBegin);
  
  /** @nodoc returned value specify Validity of InsideIdx */
  CATBoolean ReadHeaderObjectAt(size_t iCurIdx, CATCGMHeaderObjectStream& oHeader,
                                size_t& oNextIdx,
                                size_t& oBeginInsideIdx,
                                size_t& oAfterInsideIdx,
                                CATULONG32 iReferenceTag);
  
  /** @nodoc returned value specify Validity of InsideIdx */
  void PositionHeaderObjectAt(size_t iCurIdx, size_t* oNextIdx, short* oType, size_t* oDataSize, CATULONG32* oTag);
  
  void WriteHeaderUserAttrRef();
  
  void ReadHeaderUserAttrRef();
  
  void OpenWriteAttrHeader(size_t& whereHeaderBegin, const CATCGMAttrHeaderStream&   iHeader);
  
  void CloseWriteAttrHeader(const size_t whereHeaderBegin);
  
  void OpenReadAttrHeader(CATCGMAttrHeaderStream& oHeader, size_t& whereHeaderEnd,  short& level);
  
  void CloseReadAttrHeader(const size_t whereHeaderEnd, const short level);

  // Buffer check
  void OpenBufferCheckForWrite(size_t& oWhere, short& oLevel);
  void CloseBufferCheckForWrite(const size_t iWhere, const short iLevel, CATULONG64 & oCheckSum);

  void BufferCheckForRead(size_t iWhere, CATULONG64 & oCheckSum);

  // Insert data at specific position
  void OpenWriteInsertDataAt(size_t iPos, size_t iDataLength);
  void CloseWriteInsertDataAt(size_t iPos, size_t iDataLength, unsigned char*  iData);


//-----------------------------------------------------------------------------
// Boolean...
//-----------------------------------------------------------------------------

 /**
  *  Writes an CATBoolean.
  * @param iBoolean
  * The CATBoolean to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteBoolean(const CATBoolean iBoolean, const char iReservedLabel[] = "");

  /** @nodoc */
  void WriteListOfBoolean(const CATBoolean* iBooleanArray, const CATLONG32 iNbBooleans, const char iReservedLabel[] = "");

 /**
  *  Reads an CATBoolean.
  * @param iBoolean
  * The read CATBoolean. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadBoolean(CATBoolean& ioBoolean, const char iReservedLabel[] = "");

  /** @nodoc */
  void ReadListOfBoolean(CATBoolean* ioBooleanArray, const CATLONG32 iNbBooleans, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// UChar...
//-----------------------------------------------------------------------------

 /**
  *  Writes an unsigned char.
  * @param iUChar
  * The unsigned char to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteUChar(const unsigned char iUChar, const char iReservedLabel[] = "");

 /**
  *  Reads an unsigned char.
  * @param ioUChar
  * The read char. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadUChar(unsigned char& ioUChar, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of unsigned chars.
  * @param iUCharArray
  * The array of unsigned chars to write.
  * @param iNbCells
  * The count of unsigned chars to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteUChar(const unsigned char* iUCharArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * Reads an array of unsigned chars.
  * @param ioArrayUChar
  * The array of unsigned chars to write.
  * @param iNbCells
  * The size of <tt>ioArrayUChar</tt>. If the the count of UChars to read is greater than <tt>iNbCells</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadUChar(unsigned char* ioArrayUChar, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// Short...
//-----------------------------------------------------------------------------

 /**
  * Writes a short integer.
  * @param iShort
  * The short to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteShort(const short iShort, const char iReservedLabel[] = "");

 /**
  * Reads a short integer.
  * @param ioShort
  * The read short integer. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadShort(short& ioShort, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of short integers.
  * @param iShortArray
  * The array of shorts to write.
  * @param iNbCells
  * The count of shorts to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteShort(const short* iShortArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

  /** @nodoc */
  void WriteListOfShort(const short* iShortArray, const CATLONG32 iNbShorts, const char iReservedLabel[] = "");

 /**
  * Reads an array of short integers.
  * @param ioArrayShort
  * The array of short integers to write.
  * @param iNbCells
  * The size of <tt>ioArrayShort</tt>. If the the count of short integers to read is greater than <tt>iNbCells</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadShort(short* ioArrayShort, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

  /** @nodoc */
  void ReadListOfShort(short* ioShortArray, const CATLONG32 iNbShorts, const char iReservedLabel[] = "");
  
//-----------------------------------------------------------------------------
// UShort...
//-----------------------------------------------------------------------------

 /**
  * Writes an unsigned short integer.
  * @param iUShort
  * The unsigned short to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteUShort(const unsigned short iUShort, const char iReservedLabel[] = "");

 /**
  * Reads an unsigned short integer.
  * @param ioUShort
  * The read unsigned short integer.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadUShort(unsigned short& ioUShort, const char iReservedLabel[] = "");


  
//-----------------------------------------------------------------------------
// CATULONG64 ...
//-----------------------------------------------------------------------------

 /**
  * Writes an unsigned LONG64.
  * @param iULONG64
  * The unsigned LONG 64 to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULONG64(const CATULONG64 iULONG64, const char iReservedLabel[] = "");

 /**
  * Reads an unsigned LONG64..
  * @param ioULONG64
  * The read unsigned LONG 64 to read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULONG64(CATULONG64 & ioULONG64, const char iReservedLabel[] = "");

  
//-----------------------------------------------------------------------------
// CATULONG32 ...
//-----------------------------------------------------------------------------

 /**
  * Writes an unsigned LONG32.
  * @param iULONG32
  * The unsigned LONG 32 to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULONG32_Scalable(const CATLONG32 iNbCells, const CATULONG32 toadd[],  const char iReservedLabel[] = "");

 /**
  * Reads an unsigned LONG32..
  * @param ioULONG32
  * The read unsigned LONG 32 to read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULONG32_Scalable(const CATLONG32 iNbCells, CATULONG32 * toadd, const char iReservedLabel[] = "");
  

//-----------------------------------------------------------------------------
// CATLONG32 ...
//-----------------------------------------------------------------------------

 /**
  * Writes a signed LONG32.
  * @param iLONG32
  *   The signed LONG 32 to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteLONG32_Scalable(const CATLONG32 iNbCells, const CATLONG32 toadd[], const char iReservedLabel[] = "");

 /**
  * Reads a signed LONG32..
  * @param ioULONG32
  * The read signed LONG 32 to read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadLONG32_Scalable(const CATLONG32 iNbCells, CATLONG32  * toadd, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATLONG64 ...
//-----------------------------------------------------------------------------

/**
  * Writes a signed LONG64.
  * @param iLONG64
  *   The signed LONG 64 to write. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void  WriteLONG64_Scalable(const CATLONG32 iNbCells, const CATLONG64 toadd[], size_t & oNbByteToWrite, const CATBoolean iIsWrite = TRUE,
                             const char iReservedLabel[] = "" );
  void  WriteTagDifferenceAsCATULONG64_Scalable(const CATULONG32 iReferenceTag, const CATULONG32 iTargetTag);
  void  ScalableBytesCount(const CATULONG32      iReferenceTag ,
                           const CATULONG32      iTargetTag    ,
                                 size_t        & oNbByteToWrite,
                                 unsigned char & oHeaderByte   ,
                                 CATULONG32    & oRelativeTag  );
  void  WriteScalableBytes(const CATULONG32 & iRelativeTag,  const unsigned char iHeaderByte, const unsigned char iNbBytesToWrite) ;
/**
  * Reads a signed LONG64..
  * @param ioULONG64
  * The read signed LONG 64 to read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadLONG64_Scalable(const CATLONG32 iNbCells, CATLONG64  * toadd,  const char iReservedLabel[] = "" ); 
  void ReadTagDifferenceAsLONG64_Scalable(CATLONG64 & oTagDifference) ;
  void ReadTagFromTagDifference(CATULONG32 & iReferenceTag, CATULONG32 & oTag) ;
 //-----------------------------------------------------------------------------
// Long...
//-----------------------------------------------------------------------------

 /**
  * Writes a CATLONG32 integer.
  * @param iLong
  * The CATLONG32 to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteLong(const CATLONG32 iLong, const char iReservedLabel[] = "");
  
 /**
  * Reads a CATLONG32 integer.
  * @param ioLong
  * The read CATLONG32 integer.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadLong(CATLONG32& ioLong, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of CATLONG32 integers.
  * @param iLongArray
  * The array of longs to write.
  * @param iNbCells
  * The count of longs to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteLong(const CATLONG32* iLongArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * Reads a CATLONG32 integer.
  * @param ioLong
  * The read CATLONG32 integer.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadLong(CATLONG32* ioArrayLong, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// ULong...
//-----------------------------------------------------------------------------

 /**
  * Writes an CATULONG32  integer.
  * @param iULong
  * The CATULONG32  to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULong(const CATULONG32  iULong, const char iReservedLabel[] = "");

 /**
  * Reads an CATULONG32  integer.
  * @param ioULong
  * The read unsigned short integer.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULong(CATULONG32& ioULong, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of CATULONG32  integers.
  * @param iULongArray
  * The array of CATULONG32s to write.
  * @param iNbCells
  * The count of CATULONG32s to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULong(const CATULONG32* iULongArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * Reads an array of CATULONG32  integers.
  * @param ioArrayULong
  * The array of CATLONG32 integers to write.
  * @param iNbCells
  * The size of <tt>ioArrayULong</tt>. If the the count of CATLONG32 integers to read is greater than <tt>iNbCells</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULong(CATULONG32* ioArrayULong, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

  void OpenWriteULong(size_t& whereHeaderBegin, const char iReservedLabel[] = "");
  
  void CloseWriteULong(const size_t whereHeaderBegin, const CATULONG32  value);
  
  void OpenCloseReadULong(CATULONG32& toadd, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// ULongWithSign...
//-----------------------------------------------------------------------------

 /**
  * @nodoc
  * Writes a CATULONG32 integer with an associated sign.
  * @param iULong
  * The CATULONG32 to write.
  * @param iSign
  * The associated sign : 0 or 1.
  * @param iopNbWrittenBytes
  * Filled with the number of byte(s) actually written.
  * @param iDumpTrace
  * debug
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULongWithSign(const CATULONG32  iULong,
                                short       iSign ,
                                int       * iopNbWrittenBytes,
                                CATBoolean  iDumpTrace,
                                CATULONG32* ipBaseTag,
                          const char        iReservedLabel[] = "");

 /**
  * @nodoc
  * Reads a CATULONG32 integer with an associated sign.
  * @param ioULong
  * The read CATULONG32.
  * @param ioSign
  * The associated sign : 0 or 1.
  * @param iopNbReadBytes
  * Filled with the number of byte(s) actually read.
  * @param iDumpTrace
  * debug
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULongWithSign(      CATULONG32& ioULong,
                               short     & ioSign ,
                               int       * iopNbReadBytes,
                               CATBoolean  iDumpTrace,
                               CATULONG32* ipBaseTag,
                         const char        iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// ULongWithSignWithInfo...
//-----------------------------------------------------------------------------

 /**
  * @nodoc
  * Writes a CATULONG32 integer with an associated sign and an associated information 0 or 1.
  * @param iULong
  * The CATULONG32 to write.
  * @param iSign
  * The associated sign : 0 or 1.
  * @param iInfo_0_or_1
  * The associated information : 0 or 1.
  * @param iopNbWrittenBytes
  * Filled with the number of byte(s) actually written.
  * @param iDumpTrace
  * debug
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULongWithSignWithInfo(const CATULONG32 iULong, short iSign, short iInfo_0_or_1, int* iopNbWrittenBytes,
                                        CATBoolean iDumpTrace, CATULONG32* ipBaseTag, const char iReservedLabel[] = "");

 /**
  * @nodoc
  * Reads a CATULONG32 integer with an associated sign and an associated information 0 or 1.
  * @param ioULong
  * The read CATULONG32.
  * @param ioSign
  * The associated sign : 0 or 1.
  * @param ioInfo_0_or_1
  * The associated information : 0 or 1.
  * @param iopNbReadBytes
  * Filled with the number of byte(s) actually read.
  * @param iDumpTrace
  * debug
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadULongWithSignWithInfo(CATULONG32& ioULong, short& ioSign, short& ioInfo_0_or_1, int* iopNbReadBytes,
                                 CATBoolean iDumpTrace, CATULONG32* ipBaseTag, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// Double...
//-----------------------------------------------------------------------------

 /**
  * Writes a double.
  * @param iDouble
  * The double to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteDouble(const double iDouble, const char iReservedLabel[] = "");

 /**
  * Reads a double.
  * @param ioDouble
  * The read double.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadDouble(double& ioDouble, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of doubles.
  * @param iDoubleArray
  * The array of doubles to write.
  * @param iNbCells
  * The count of doubles to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteDouble(const double* iDoubleArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * Reads an array of doubles.
  * @param ioArrayDouble
  * The array of doubles to write.
  * @param iNbCells
  * The size of <tt>ioArrayDouble</tt>. If the the count of doubles to read is greater than <tt>iNbCells</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadDouble(double* ioArrayDouble, const CATLONG32 iNbCells, const char iReservedLabel[] = "");
 
//-----------------------------------------------------------------------------
// Float...
//-----------------------------------------------------------------------------

 /**
  * Writes a float.
  * @param iFloat
  * The float to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteFloat(const float iFloat, const char iReservedLabel[] = "");

 /**
  * Reads a float.
  * @param ioFloat
  * The read float.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadFloat(float& ioFloat, const char iReservedLabel[] = "");

 /**
  * Writes a sequence of floats.
  * @param iFloatArray
  * The array of floats to write.
  * @param iNbCells
  * The count of floats to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteFloat(const float* iFloatArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  *    Reads an array of floats.
  * @param ioArrayFloat
  * The array of floats to write.
  * @param iNbCells
  * The size of <tt>ioArrayFloat</tt>. If the the count of floats to read is greater than <tt>iNbCells</tt>,
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadFloat(float* ioArrayFloat, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// String...
//-----------------------------------------------------------------------------

 /**
  * Writes a string.
  * @param iString
  * The string to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteString(const char* iString, const char iReservedLabel[] = "");

 /**
  * Reads a string.
  * @param ioString
  * The read string.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadString(char*& ioString, const char iReservedLabel[] = "");

  void ReadStringMemBook(const size_t sizeInput, char*& ioString, size_t& ioSizeMemBook, const char iReservedLabel[] = "");
  
//-----------------------------------------------------------------------------
// CATMathBox...
//-----------------------------------------------------------------------------

 /**
  * Writes a CATMathBox.
  * @param iBox
  * The box to write. The box is written with floats, precision can be lost. 
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteBox(const CATMathBox&, const char iReservedLabel[] = "");

 /**
  * Reads a CATMathBox.
  * @param ioBox
  * The read box.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadBox(CATMathBox& ioBox, const char iReservedLabel[] = "");

  void WriteAdvancedBox(const CATMathAdvancedBox &, const char iReservedLabel[] = "");
  void ReadAdvancedBox(CATMathAdvancedBox &, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMathPoint...
//-----------------------------------------------------------------------------
 
  void WritePoint(const CATMathPoint&, const char iReservedLabel[] = "");
 
  void ReadPoint(CATMathPoint& ioPoint, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMathPointf...
//-----------------------------------------------------------------------------
 
  void WritePointf(const CATMathPointf&, const char iReservedLabel[] = "");
 
  void ReadPointf(CATMathPointf& ioPoint, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMathVector2D...
//-----------------------------------------------------------------------------

  void WriteVector2D(const CATMathVector2D&, const char iReservedLabel[] = "");
 
  void ReadVector2D(CATMathVector2D& ioVector2D, const char iReservedLabel[] = "");
  
//-----------------------------------------------------------------------------
// CATMathVector...
//-----------------------------------------------------------------------------
 
  void WriteVector(const CATMathVector&, const char iReservedLabel[] = "");
 
  void ReadVector(CATMathVector& ioVector, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMathVectorf...
//-----------------------------------------------------------------------------
 
  void WriteVectorf(const CATMathVectorf&, const char iReservedLabel[] = "");
 
  void ReadVectorf(CATMathVectorf& ioVector, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMath3x3Matrix...
//-----------------------------------------------------------------------------
 
  void Write3x3Matrix(const CATMath3x3Matrix&, const char iReservedLabel[] = "");
 
  void Read3x3Matrix(CATMath3x3Matrix& ioMatrix, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATMathTransformation...
//-----------------------------------------------------------------------------
 
  void WriteTransformation(const CATMathTransformation&, const char iReservedLabel[] = "");
 
  void ReadTransformation(CATMathTransformation& ioTransfo, const char iReservedLabel[] = "");
  
//-----------------------------------------------------------------------------
// CATMathPlane...
//-----------------------------------------------------------------------------
 
  void WritePlane(const CATMathPlane&, const char iReservedLabel[] = "");
 
  void ReadPlane(CATMathPlane& ioPlane, const char iReservedLabel[] = "");
   
//-----------------------------------------------------------------------------
// CATMathAxis...
//-----------------------------------------------------------------------------
  
  void WriteAxis(const CATMathAxis&, const char iReservedLabel[] = "");
 
  void ReadAxis(CATMathAxis& ioAxis, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATUuid...
//-----------------------------------------------------------------------------
  
  void WriteCATUuid(const CATUuid&iid, const char iReservedLabel[] = "");
 
  void ReadCATUuid(CATUuid& iid, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// GUID...
//-----------------------------------------------------------------------------

  void WriteUID(const GUID&iid, const char iReservedLabel[] = "");
  
  void ReadUID(GUID& iid, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// CATSoftwareConfiguration...
//-----------------------------------------------------------------------------
 
  void WriteConfig(const CATSoftwareConfiguration& iConfig, const char iReservedLabel[] = "");
 
  void ReadConfig(CATSoftwareConfiguration& ioConfig, const char iReservedLabel[] = "");

  /*@nodoc @nocgmitf*/
  void ReadConfig(CATSoftwareConfiguration& ioConfig, CATBoolean iForceOpenConfig, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// Orientations...
//-----------------------------------------------------------------------------

 /**
  * @nodoc
  * Writes a sequence of Orientations as Shorts into a sequence of 2bit patterns.
  * The orientations must have a value in {-1, 0, 1, 2 }
  * @param iOriAsShortArray
  * The array of shorts to write.
  * @param iNbCells
  * The count of shorts to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteOrientations(const short* iOriAsShortArray, const CATLONG32 iNbCells, CATBoolean iOnly1s, const char iReservedLabel[] = "");

 /**
  * @nodoc
  * Reads a sequence of 2bit patterns into an array of Orientations as Shorts.
  * The orientations must have a value in {-1, 0, 1, 2 }
  * @param ioOriAsShortArray
  * The array of short integers to write.
  * @param iNbCells
  * The size of <tt>ioArrayShort</tt>.
  * nothing is read.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void ReadOrientations(short* ioOriAsShortArray, const CATLONG32 iNbCells, CATBoolean iOnly1s, const char iReservedLabel[] = "");

  
//-----------------------------------------------------------------------------
// CATUnicodeString...
//-----------------------------------------------------------------------------

  /**
  *  Outputs a  <tt>UnicodeString</tt>.
  */
  void WriteUnicode (const CATUnicodeString& iStr, const char iReservedLabel[] = "");;
  /**
  *  Inputs a  <tt>UnicodeString</tt>.
  */
  void ReadUnicode (CATUnicodeString& oStr, const char iReservedLabel[] = "");
 
  
//-----------------------------------------------------------------------------
// CATICGMObject...
//-----------------------------------------------------------------------------
    
  void WriteGeometryV5(CATICGMObject      **  geometry, 
                       const CATLONG32        iNbGeometry,
                       const char             iReservedLabel[] = "",
                       CATCGMStreamVersion    iForceVersion = CatCGMStream_UnknownVersion);
  
  void ReadGeometryV5(CATICGMObject** geometry, const CATLONG32 iNbGeometry, const char iReservedLabel[] = "");

//-----------------------------------------------------------------------------
// ByAddress...
//-----------------------------------------------------------------------------
 /**
  * @nodoc
  * Writes a sequence of doubles.
  * @param iDoubleArray
  * The array of doubles to write.
  * @param iNbCells
  * The count of doubles to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteDoubleByAddress(const double* iDoubleArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 
#ifdef CATMathStreamImplUnusedByAddress
 /**
  * @nodoc
  * Writes a sequence of unsigned chars.
  * @param iUCharArray
  * The array of unsigned chars to write.
  * @param iNbCells
  * The count of unsigned chars to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteUCharByAddress(const unsigned char* iUCharArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");  

 /**
  * @nodoc
  * Writes a sequence of short integers.
  * @param iShortArray
  * The array of shorts to write.
  * @param iNbCells
  * The count of shorts to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteShortByAddress(const short* iShortArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * @nodoc
  * Writes a sequence of CATLONG32 integers.
  * @param iLongArray
  * The array of longs to write.
  * @param iNbCells
  * The count of longs to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteLongByAddress(const CATLONG32* iLongArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");

 /**
  * @nodoc
  * Writes a sequence of CATULONG32  integers.
  * @param iULongArray
  * The array of CATULONG32s to write.
  * @param iNbCells
  * The count of CATULONG32s to write.
  * @param iReservedLabel
  * Reserved for future use (do not change the default value)
  */
  void WriteULongByAddress(const CATULONG32* iULongArray, const CATLONG32 iNbCells, const char iReservedLabel[] = "");
 
#endif
 

//-----------------------------------------------------------------------------
// Big/Little Endian Conversion...
//-----------------------------------------------------------------------------

  void SetConversion(unsigned char);
  
  INLINE unsigned char GetConversion() const;
  
//-----------------------------------------------------------------------------
// Version...
//-----------------------------------------------------------------------------

  INLINE CATBoolean IsOlderThanCXR4GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR5GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR6GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR7GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR8GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR9GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR10GAFormat() const;

  INLINE CATBoolean IsOlderThanCXR11GAFormat() const;
  void SetVersionNumber(CATCGMStreamVersion iCATCGMVersionDefinition);
  
  CATBoolean IsCSVActivated (CATULONG32 iCSVNumber) const;
  void       SetCSV (CATULONG32 iCSVNumber);
  CATULONG32  GetCSV ();
//-----------------------------------------------------------------------------
// Checks...
//-----------------------------------------------------------------------------
  
  INLINE int TemporaryCheckLinks(int mustActivate);

  void ThrowOnReadingTooFar(char* ifile, int iline) const;
  
  void InvalidValue(char* ifile, int iline) const;
   
  void InvalidForStreamReadOnly() const;
   
  void InvalidForStreamWriteOnly() const;
  
  static void CheckOperatingSystemIsOkay(short forceThrow = 0);
  
  virtual void CheckLinksWrittenError() const;
  
  virtual void CheckLinksReadError() const;

//-----------------------------------------------------------------------------
// Areas...
//-----------------------------------------------------------------------------

  HRESULT GetNumberOfArea(size_t& oGlobalLengthInBytes, CATULONG32& oNumberOfArea);
  
  HRESULT GetValueOfArea(const CATULONG32         iNumberOfArea,
                         size_t*                  ioAreaLengthInBytes,
                         const unsigned char**    ioAreaAddress);

//-----------------------------------------------------------------------------
// Attributes...
//-----------------------------------------------------------------------------
  
  INLINE short IsContainingAttributes()  const;
  
  void DefineIfContainingAttributes(const short iSet = 1);


//-----------------------------------------------------------------------------
// Debug Direct Streaming
//-----------------------------------------------------------------------------
  
  INLINE short IsDelayedCleanedBuffer()  const;
  
  INLINE void DefineDelayedCleanedBuffer();

  
//-----------------------------------------------------------------------------
// CGMReplay...
//-----------------------------------------------------------------------------

  void SetDedicatedToReplay(CATExtCGMReplay* iReplay);
  
  INLINE CATExtCGMReplay* IsDedicatedToReplay() const;


//-----------------------------------------------------------------------------
// PlayBack...
//-----------------------------------------------------------------------------

  void SetDedicatedToPlayBack(CATechSet* iPlayBack);
  
  INLINE CATechSet* IsDedicatedToPlayBack() const;



//-----------------------------------------------------------------------------
// MemoryBytes...
//-----------------------------------------------------------------------------

  virtual size_t GetStaticMemoryBytes() const;

  virtual size_t GetDynamicMemoryBytes() const;   


  //-----------------------------------------------------------------------------
  // CATSoftwareConfiguration...
  //-----------------------------------------------------------------------------
  static CATBoolean IsOpenConfig(const CATSoftwareConfiguration & iConfig);


//-----------------------------------------------------------------------------
// Dump...
//-----------------------------------------------------------------------------
  
  void BeginLabel(CATLONG32& currentLevel, const char iReservedLabel[] = "");
  
  void EndLabel(const CATLONG32 currentLevel, const char iReservedLabel[] = "");
  
  INLINE int DumpIsActive() const;
  
  CATBoolean DumpXMLFormat() const;
  
  CATBoolean SetDumpActiveMode(CATBoolean iMode);

  void DumpComment(const char iLabelReserved[] = "", int iShift = 0);
  
  void DumpCommentBegin(const char iLabelReserved[] = "", int iBlankLine = 0);
  
  void DumpCommentEnd(const char* ipLabelReserved = NULL);
  
  void DumpStatistics(ostream& iOutput);

  static CATBoolean  GetDedicatedForNaNObjects( CATLISTV(CATBaseUnknown_var) & oNaNObjects ,
                                                CATListPV                    & oNaNAttributes,
                                                CATLISTV(CATBaseUnknown_var) & oSuspiciousObjects);

  static CATBoolean  IsDedicatedForNaNObjects( );
  static void        SetDedicatedForNaNObjects( CATBoolean iSetDedicatedForNaNObjects );
  static void        PushNaN();

  static CATBaseUnknown *  _CurrentObject;
  static void           *  _CurrentAttribute;

  static size_t            _CurrentAttributeStartPosition;
  static size_t            _CurrentAttributeLength;


#ifdef NurbsCompactOptimPR
  static void InitPoolThread();
  static void CleanPoolThread();
#endif 




  INLINE CATCGMStreamType GetAccesType() const;
  
  INLINE CATCGMStreamStorage GetStorageType() const;

  // CATCGMBinaryStream
  INLINE void SetBinaryStream(CATCGMBinaryStream * iStream, const CATCGMStreamType& iAcces, size_t iSizeStream = 0);
  INLINE CATCGMBinaryStream * GetBinaryStream() const;

  //-----------------------------------------------------------------------------
  //
  // CompositeManagement ...
  //
  //     Initially introduced as more flexible and new opened data structure of CGMReplay
  //          new internal file convention with *.zip.CGMReplay 
  //          default option of 2012Spring DataFormat Structure (14 07 2012)
  //
  //     BootSingleVersion is a mandatory prerequisite for this new option
  //
  //-----------------------------------------------------------------------------
 
  // V2 (Replay-PlayBack Integration)

  void                   SetMetaDescriptor(CATGMAdapter *iBootAttribute);
  INLINE CATGMAdapter *  HasMetaDescriptor() const;


  // V1  (Replay initial)
  void SetDedicatedCompositeAttribute(CATechAttribute *iBootAttribute);

  void SetUnderCompositeManagement(CATechSet* iCompositeManagement, CATechAttribute *iBootAttribute);

  INLINE CATechSet       * IsUnderCompositeManagement() const;
  INLINE CATechAttribute * HasCompositeBootAttribute() const;

  INLINE void       CheckCompositeManagementAtOpen();
  INLINE void       ForceCompositeManagementAtOpen();
 


protected :

  // restricted CATCGM_STREAM
  INLINE CATBoolean IsContiguousReadMemory(void* & oBuffer,  size_t & oSizeBuffer);

  enum ObjectOperation { NotSpecified = 10, StreamObject = 11,  UnstreamObject = 12, ExternalWeakLinks = 13 };

  enum OperationStatus { ExpectingLinksCount = 20, ProcessingLinks = 21, LinksCompleted = 22 };

  // In case the stream is prepared to object streaming or unstreaming,
  // those functions ensure that linked objects have been written or read
  // (called are made prior to any write or read of non-object information)
  
  INLINE void CheckLinksWritten() const;
  
  INLINE void CheckLinksRead() const;
   
  virtual int NumberOfAttributesToStream(); 

  CATMathStream*            _pItf;

  static CATULONG32         _StaticSessionId;

  static CATLONG32          _OperatingSystemIsOkay;

  ObjectOperation           _ObjectOperation;
  OperationStatus           _OperationStatus;

  CATULONG32                _ObjectTag;
  int                       _ObjectType;

  CATULONG32                _PreviousObjectTag;
  int                       _PreviousObjectType;
  
  CATULONG32                _LatestStreamedObjectTag;
  CATULONG32                _LatestStreamedDeltaObjectTag;
  int                       _LatestStreamedDeltaSignObjectTag;
  
  CATULONG32                _NbSameDeltaAndSignObjectTags;
  
  CATULONG32                _SetObjectTag;
  int                       _SetObjectType;
  CATULONG32                _SetObjectIndex;
  
  int                       _MaxLinksCountInHeader;
  
  CATULONG32                _ObjectLinksCountData;
  
  
  CATCGMHashTableWithAssoc* _pTabMapTagsToSizes;
  
  CATListOfInt*             _pListMapIndexToSizes;
  
  CATCGMHashTableWithAssoc* _pTabMapCGMTypesToULong32s;
  
  short*                    _pTabMapULong32sToCGMTypes;

#ifdef NurbsCompactOptimPR
  static CATMathPoolThread*        _Pool;
#endif 
 
  void*                     _pNurbsSurfaceBuffer;   // for perfos

  CATMathStreamStats*       _pStatistics;
  
  CATMathStreamDump*        _pDump;



private :


 /**
  *  Depreciated ( <= V5R5  historical version ) 
  */
  void OpenWriteObjectHeader_V5R5(size_t& whereHeaderBegin, const CATCGMHeaderObjectStream&   iHeader, const char iReservedLabel[] = "");
  void CloseWriteHeaderData_V5R5(const size_t whereHeaderBegin);
  void CloseWriteHeaderContainer_V5R5(const size_t whereHeaderBegin);
  void CloseWriteHeaderDataContainer_V5R5(const size_t whereHeaderBegin);
  CATBoolean ReadHeaderObjectAt_V5R5(size_t iCurIdx, CATCGMHeaderObjectStream& oHeader,
                                     size_t& oNextIdx,
                                     size_t& oBeginInsideIdx,
                                     size_t& oAfterInsideIdx);
  void PositionHeaderObjectAt_V5R5(size_t iCurIdx,
                                   size_t* oNextIdx,
                                   short* oType,
                                   size_t* oDataSize,
                                   CATULONG32* oTag);
  void WriteHeaderUserAttrRef_V5R5();
  void ReadHeaderUserAttrRef_V5R5();



 /**
  *  P.E.C :  SmallHeader
  */
  void OpenWriteObjectHeader_SmallHeader(size_t& whereHeaderBegin, const CATCGMHeaderObjectStream&   iHeader, const char iReservedLabel[] = "");
  CATBoolean ReadHeaderObjectAt_SmallHeader(size_t iCurIdx, CATCGMHeaderObjectStream& oHeader,
                                size_t& oNextIdx,
                                size_t& oBeginInsideIdx,
                                size_t& oAfterInsideIdx,
                                CATULONG32 iReferenceTag);
   void  CloseWriteHeaderData_SmallHeader(CATCGMHeaderObjectStream&   iHeader, const size_t where);
   void  CloseWriteHeaderContainer_SmallHeader(const size_t where);
   void  CloseWriteHeaderDataContainer_SmallHeader(const size_t where);
 

   /**
   *  DefaultInit
   */
   void DefaultInit(const   CATCGMStreamType iDefaultAcces);



  void WriteCGMHeaderStream(const CGMHeaderStream& iHeader, const char iReservedLabel[] = "");

 /**
  * @nodoc 
  * @return
  * The result of the test.
  * <br><b>Legal values</b>:
  * <tt>TRUE</tt> if Direct Address has been done,
  * <tt>FALSE</tt> otherwise.
  */
  CATBoolean NeedContinousLength(size_t              iBytesNeeded, 
                                 const    CATBoolean iEnableByAddress  = FALSE,
                                 unsigned char*      iForDirectAddress = NULL);

  unsigned char* SeekPreviousBuffer(const size_t iWhere,
                                    const size_t iBytesLength);
  
  INLINE CATBoolean LoadBufferFromDirectStreamIfNeeded(size_t iIndexToRead, size_t iSizeOfData);
  
  CATBoolean LoadBufferFromDirectStream(size_t iIndexToRead, size_t iSizeOfData);

  // Global Identification
  CATULONG32          _SessionId;
  //CATCGMStreamVersion _VersionNumber;
  CATULONG32          _CSVersion;

  // Little-Big Endian conversion needed
  struct CATCGStr
  {
    unsigned int _CheckLinks             : 1;     
    unsigned int _Attributes             : 1;
    unsigned int _EnableByAddress        : 1; 
    unsigned int _AutoCheck_MlcBB        : 1;  // AutoCheck IR 097819 ,  Incomplete data Customisation Management

    unsigned int _DelayedCleanedBuffer   : 1;     

    unsigned int _CheckCompositeManagementAtOpen   : 1;     

    unsigned int _ForceCompositeManagementAtOpen   : 1;     
  }
  CGStr;

  const CATCGMStreamControl   StrControl;

  CATCGMStreamType    _acces;
  CATCGMStreamStorage _storage;

  // Storage Type
  ostream*            _ostream;
  istream*            _istream;
  const char*         _pFileName;
  CATStream*          _pDirectStream;  
  CATCGMBinaryStream *  _pBinaryStream;

  CATBoolean          _IsBinaryStream;

  // Allocated Buffers
  CATMathStreamBlocs* _pFirstBuffer; 

  // Current Buffer
  unsigned char*      _pCurrentBuffer;
  size_t              _CurrentWriteIndex;
  size_t              _CurrentReadIndex;

  size_t              _CurrentBufferLength_or_InputFileLength; 
  size_t              _WrittenDataLength_or_InputFileLength;
  size_t              _CurrentBufferStartWriteIndex;
  
  size_t              _DirectStreamCurrentBufferSize;
  size_t              _DirectStreamReadIndexMin;
  size_t              _DirectStreamReadIndexMax;

  const short         _LevelOpenClose;
    
  CATExtCGMReplay*    _pDedicatedToReplay;

  //
  CATGMAdapter *      _pMetaDescriptor;
 
  CATechSet*          _pPlayBack;

  CATechSet*          _pCompositeManagement;
  CATechAttribute*    _pCompositeAttribute;

private:
  // jkj - Flag to identify MProc is using stream.
  CATBoolean          _UnderMProc;

  // hcn - Flag to identify multiple format management.
#define CATStackDepth 16 

  static CATBoolean    _DumpChangeControl();

   // For solution of Single .. CATCGMSingleStreamControl
  CATBoolean            _SingleStreamControl;
  CATCGMStreamControl   _TheStreamControl;

   // For analysis
  CATBoolean           _MultiFormat;
  struct CATStackMultiFormat
  {
    int                    _Allocated;
    int                    _Used;

    CATCGMStreamControl  * _Array;
    CATCGMStreamControl    _Static[CATStackDepth];

    CATBoolean           * _ArrayBoolean;
    CATBoolean             _StaticBoolean[CATStackDepth];
  } _StackMultiFormat;

  void PushStreamControl(const size_t iPosition);
  void PopStreamControl(const size_t iPosition);

  INLINE short PushLevelControl(const size_t iPosition);
  INLINE short PopLevelControl(const size_t iPosition);

  // .. DumpChangeControl
  void PushDumpChangeControl(const size_t iPosition);
  void PopDumpChangeControl(const size_t iPosition);


  void TrueSetStrControl(const CATCGMStreamControl&  iStrControl);


public:
  // jkj - Determine if this stream is used my MProc.
  CATBoolean IsUnderMProc() const { return _UnderMProc; }
  // jkj - Set to TRUE if this stream is used my MProc.
  void SetUnderMProc( CATBoolean iUnderMProc) { _UnderMProc = iUnderMProc; }

  // SingleStreamControl
  void       SetSingleStreamControl(const CATCGMStreamControl&  iStrControl);   
  CATBoolean IsSingleStreamControl(CATCGMStreamControl & oCopy) const;

  // hcn - Flag to identify multiple format management.
  CATBoolean IsMultiFormat() const { return _MultiFormat; }
  // hcn - Flag to identify multiple format management.
  void SetMultiFormat( CATBoolean iMultiFormat);   

private:

   void CATMathStreamThrowAbend() const;

//  static CATTrace*    _pCATTraceCGMStream;//-AAD20140918
  
  static int         _ToControlGoodNumber;
  
  static CATLISTV(CATBaseUnknown_var)  _NaNObjects;
  static CATListPV                     _NaNAttributes;

  friend class CATMathStreamDump;
  friend class CATMathStreamDumpImpl;
  
  friend class CATMathStreamBlocs;
  friend class CATCGMStream;
  friend class CATCGMStreamCoverageInteger;

  friend class CATCGM_STREAM;
 
public :

  static CATLISTV(CATBaseUnknown_var)  _SuspiciousObjects;

  INLINE int  IsSmallHeader();
  INLINE void SetSmallHeader();

  INLINE int  IsScalableInteger();
  INLINE void SetScalableInteger();

  INLINE int  IsRelativeTagValue();
  INLINE void SetRelativeTagValue();

  INLINE int  IsObfuscation2009();
  INLINE void SetObfuscation2009();

  INLINE int  IsFixNbLinked();
  INLINE void SetFixNbLinked();

  INLINE int  IsRelativeTagObject();
  INLINE void SetRelativeTagObject();

  INLINE int  IsNurbsCompact();
  INLINE void SetNurbsCompact();

  INLINE int  IsPOEC();
  INLINE void SetPOEC();

  INLINE int  IsEdgeCompact();
  INLINE void SetEdgeCompact();

  INLINE int  IsLoopCompact();
  INLINE void SetLoopCompact();

  INLINE int  IsAxisValue();
  INLINE void SetAxisValue();

  INLINE int  IsKnotVector();
  INLINE void SetKnotVector();

  INLINE int  IsShellCompact();
  INLINE void SetShellCompact();

  INLINE int  IsEdgeCurve();
  INLINE void SetEdgeCurve();

  INLINE int  IsLimitCompact();
  INLINE void SetLimitCompact();

  INLINE int  IsSingleLoad();
  INLINE void SetSingleLoad();

  INLINE int  IsNeutralEndian();
  INLINE void SetNeutralEndian();

  INLINE int  IsFaceCompact();

  INLINE int  IsLoopCompact2011();

  INLINE int  IsPSplineCompact();
  INLINE void SetPSplineCompact();

  INLINE int  IsNurbsCompact2011();
  INLINE void SetNurbsCompact2011();

  INLINE int  IsLimitCompact2012Spring();
  INLINE void SetLimitCompact2012Spring();

  INLINE int  IsCompactCoreAttribute() const; 
  INLINE void SetCompactCoreAttribute();

  INLINE int  IsPNurbsCompact();
  INLINE void SetPNurbsCompact();

  INLINE int  IsKnotVector2012();
  INLINE void SetKnotVector2012();

  INLINE int  IsPlaneCompact();
  INLINE void SetPlaneCompact();

  INLINE int  IsNurbsCompact2015();
  INLINE void SetNurbsCompact2015();


  INLINE void ResetCoreStream();

//#ifdef NurbsCompactOptimPR
  INLINE void* GetNurbsSurfaceBuffer();
  INLINE void  SetNurbsSurfaceBuffer(void * ipNurbsSurfaceBuffer);
  //#endif 

  INLINE void GetStrControl(CATCGMStreamControl & oCopy) const;
  void SetStrControl(const CATCGMStreamControl&  iStrControl);





private :

  /**
   * @nodoc
   */
   CATMathStreamImpl(const CATMathStreamImpl &iCopy);

  /**
   * @nodoc
   */
   CATMathStreamImpl& operator=(const CATMathStreamImpl &iCopy);
 
   friend class CATCGMStreamCGMImpl;


public :

    void CloseWriteEndOfFile();  

};

//-----------------------------------------------------------------------------
// GetImpl
//-----------------------------------------------------------------------------
INLINE void* CATMathStreamImpl::GetItf()
{
  return (void*)_pItf;
}

//-----------------------------------------------------------------------------
// GetLength 
//-----------------------------------------------------------------------------
INLINE size_t CATMathStreamImpl::GetLength() const
{
  return _WrittenDataLength_or_InputFileLength;
}

//-----------------------------------------------------------------------------
// GetCurrentPosition 
//-----------------------------------------------------------------------------
INLINE size_t CATMathStreamImpl::GetCurrentPosition() const
{
  //return _CurrentReadIndex;

  // On veut une methode utilisable en ecriture ET en lecture
  if ((_acces == CatCGMStreamReadOnly) || (_acces == CatCGMStreamReadWrite))
    return _CurrentReadIndex;
  else if (_acces == CatCGMStreamWriteOnly)
    return _WrittenDataLength_or_InputFileLength;
  else
    CATThrowForNullPointerReturnValue(0);
}

//-----------------------------------------------------------------------------
// SetCurrentPosition 
//-----------------------------------------------------------------------------
INLINE void CATMathStreamImpl::SetCurrentPosition(size_t iIndex) 
{
  if ((_acces == CatCGMStreamReadOnly) || (_acces == CatCGMStreamReadWrite))
    _CurrentReadIndex = iIndex ;
  else
    CATThrowForNullPointer();
}

//-----------------------------------------------------------------------------
// Advance 
//-----------------------------------------------------------------------------
INLINE void CATMathStreamImpl::Advance( size_t siz )
{
  if ( _acces == CatCGMStreamWriteOnly ) InvalidForStreamWriteOnly();

  _CurrentReadIndex += siz;
}

//-----------------------------------------------------------------------------
// Reset 
//-----------------------------------------------------------------------------
INLINE void CATMathStreamImpl::Reset()
{
  _CurrentReadIndex = 0;
}

//-----------------------------------------------------------------------------
// Reset 
//-----------------------------------------------------------------------------

INLINE short CATMathStreamImpl::PushLevelControl(const size_t iPosition)
{
  if ( _DumpChangeControl() ) PushDumpChangeControl(iPosition);
  if ( _MultiFormat       ) PushStreamControl(iPosition);
  short level = (*(short *)&_LevelOpenClose)++;
  return level;
}
INLINE short CATMathStreamImpl::PopLevelControl(const size_t iPosition)
{
  short level = --(*(short *)&_LevelOpenClose);
  if ( _MultiFormat       ) PopStreamControl(iPosition);
  if ( _DumpChangeControl() ) PopDumpChangeControl(iPosition);
  return level;
}

 

// GetVersionNumber
//-----------------------------------------------------------------------------
INLINE CATCGMStreamVersion CATMathStreamImpl::GetVersionNumber() const
{
  return StrControl._VersionNumber;
}
 
INLINE int CATMathStreamImpl::IsSmallHeader()
{ return StrControl.IsSmallHeader();}
INLINE void CATMathStreamImpl::SetSmallHeader()
{ CATCGMStreamControl copy(StrControl); copy.SetSmallHeader(); TrueSetStrControl(copy); }


INLINE int CATMathStreamImpl::IsScalableInteger()
{ return StrControl.IsScalableInteger();}
INLINE void CATMathStreamImpl::SetScalableInteger()
{ CATCGMStreamControl copy(StrControl); copy.SetScalableInteger(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsRelativeTagValue()
{ return StrControl.IsRelativeTagValue();}
INLINE void CATMathStreamImpl::SetRelativeTagValue()
{ CATCGMStreamControl copy(StrControl); copy.SetRelativeTagValue(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsObfuscation2009()
{ return StrControl.IsObfuscation2009();}
INLINE void CATMathStreamImpl::SetObfuscation2009()
{ CATCGMStreamControl copy(StrControl); copy.SetObfuscation2009(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsFixNbLinked()
{ return StrControl.IsFixNbLinked();}
INLINE void CATMathStreamImpl::SetFixNbLinked()
{ CATCGMStreamControl copy(StrControl); copy.SetFixNbLinked(); TrueSetStrControl(copy); }
 
INLINE int CATMathStreamImpl::IsRelativeTagObject()
{ return StrControl.IsRelativeTagObject();}
INLINE void CATMathStreamImpl::SetRelativeTagObject()
{ CATCGMStreamControl copy(StrControl); copy.SetRelativeTagObject(); TrueSetStrControl(copy); }
 
INLINE int CATMathStreamImpl::IsNurbsCompact()
{ return StrControl.IsNurbsCompact();}
INLINE void CATMathStreamImpl::SetNurbsCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetNurbsCompact(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsPOEC()
{ return StrControl.IsPOEC();}
INLINE void CATMathStreamImpl::SetPOEC()
{ CATCGMStreamControl copy(StrControl); copy.SetPOEC(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsEdgeCompact()
{ return StrControl.IsEdgeCompact();}
INLINE void CATMathStreamImpl::SetEdgeCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetEdgeCompact(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsLoopCompact()
{ return StrControl.IsLoopCompact();}
INLINE void CATMathStreamImpl::SetLoopCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetLoopCompact(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsAxisValue()
{ return StrControl.IsAxisValue();}
INLINE void CATMathStreamImpl::SetAxisValue()
{ CATCGMStreamControl copy(StrControl); copy.SetAxisValue(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsKnotVector()
{ return StrControl.IsKnotVector();}
INLINE void CATMathStreamImpl::SetKnotVector()
{ CATCGMStreamControl copy(StrControl); copy.SetKnotVector(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsShellCompact()
{ return StrControl.IsShellCompact();}
INLINE void CATMathStreamImpl::SetShellCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetShellCompact(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsEdgeCurve()
{ return StrControl.IsEdgeCurve();}
INLINE void CATMathStreamImpl::SetEdgeCurve()
{ CATCGMStreamControl copy(StrControl); copy.SetEdgeCurve(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsLimitCompact()
{ return StrControl.IsLimitCompact();}
INLINE void CATMathStreamImpl::SetLimitCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetLimitCompact(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsSingleLoad()
{ return StrControl.IsSingleLoad();}
INLINE void CATMathStreamImpl::SetSingleLoad()
{ CATCGMStreamControl copy(StrControl); copy.SetSingleLoad(); TrueSetStrControl(copy); }


INLINE int CATMathStreamImpl::IsNeutralEndian()
{ return StrControl.IsNeutralEndian();}
INLINE void CATMathStreamImpl::SetNeutralEndian()
{ CATCGMStreamControl copy(StrControl); copy.SetNeutralEndian(); TrueSetStrControl(copy); }


INLINE int CATMathStreamImpl::IsFaceCompact()
{ return StrControl.IsFaceCompact();}

INLINE int CATMathStreamImpl::IsLoopCompact2011()
{ return StrControl.IsLoopCompact2011();}

INLINE int CATMathStreamImpl::IsPSplineCompact()
{ return StrControl.IsPSplineCompact();}
INLINE void CATMathStreamImpl::SetPSplineCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetPSplineCompact(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsNurbsCompact2011()
{ return StrControl.IsNurbsCompact2011();}
INLINE void CATMathStreamImpl::SetNurbsCompact2011()
{ CATCGMStreamControl copy(StrControl); copy.SetNurbsCompact2011(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsLimitCompact2012Spring()
{ return StrControl.IsLimitCompact2012Spring();}
INLINE void CATMathStreamImpl::SetLimitCompact2012Spring()
{ CATCGMStreamControl copy(StrControl); copy.SetLimitCompact2012Spring(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsCompactCoreAttribute() const
{ return StrControl.IsCompactCoreAttribute();}
INLINE void CATMathStreamImpl::SetCompactCoreAttribute()
{ CATCGMStreamControl copy(StrControl); copy.SetCompactCoreAttribute(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsPNurbsCompact()
{ return StrControl.IsPNurbsCompact();}
INLINE void CATMathStreamImpl::SetPNurbsCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetPNurbsCompact(); TrueSetStrControl(copy); }

INLINE int CATMathStreamImpl::IsKnotVector2012()
{ return StrControl.IsKnotVector2012();}
INLINE void CATMathStreamImpl::SetKnotVector2012()
{ CATCGMStreamControl copy(StrControl); copy.SetKnotVector2012(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsPlaneCompact()
{ return StrControl.IsPlaneCompact();}
INLINE void CATMathStreamImpl::SetPlaneCompact()
{ CATCGMStreamControl copy(StrControl); copy.SetPlaneCompact(); TrueSetStrControl(copy); }
 

INLINE int CATMathStreamImpl::IsNurbsCompact2015()
{ return StrControl.IsNurbsCompact2015();}
INLINE void CATMathStreamImpl::SetNurbsCompact2015()
{ CATCGMStreamControl copy(StrControl); copy.SetNurbsCompact2015(); TrueSetStrControl(copy); }


INLINE void CATMathStreamImpl::GetStrControl(CATCGMStreamControl & oCopy) const
{ oCopy = StrControl; }
 




//#ifdef NurbsCompactOptimPR
INLINE void* CATMathStreamImpl::GetNurbsSurfaceBuffer()
{
  return _pNurbsSurfaceBuffer;
}

INLINE void CATMathStreamImpl::SetNurbsSurfaceBuffer(void * ipNurbsSurfaceBuffer)
{
  _pNurbsSurfaceBuffer = ipNurbsSurfaceBuffer;
}
//#endif 




//-----------------------------------------------------------------------------
// GetConversion 
//-----------------------------------------------------------------------------
INLINE unsigned char CATMathStreamImpl::GetConversion() const
{
  //return StrControl._EndianConversion ? TRUE : FALSE;
  return StrControl.IsEndianConversion() ? TRUE : FALSE;
}

//-----------------------------------------------------------------------------
// IsOlderThanCXR4GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR4GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R4GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR5GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR5GAFormat() const
{   return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R5GA);}

//-----------------------------------------------------------------------------
// IsOlderThanCXR6GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR6GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R6GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR7GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR7GAFormat() const
{ return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R7GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR8GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR8GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R8GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR9GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR9GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R9GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR10GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR10GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R10GA); }

//-----------------------------------------------------------------------------
// IsOlderThanCXR11GAFormat
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsOlderThanCXR11GAFormat() const
{  return CATCGMStreamIsStrictlyOlderThan(StrControl._VersionNumber,CatCGMStream_V5R11GA); }

//-----------------------------------------------------------------------------
// TemporaryCheckLinks
//-----------------------------------------------------------------------------
INLINE int CATMathStreamImpl::TemporaryCheckLinks(int mustActivate)
{
  int result = CGStr._CheckLinks ? 1 : 0;
  CGStr._CheckLinks = mustActivate ? 1 : 0;
  return result;
}

//-----------------------------------------------------------------------------
// IsContainingAttributes
//-----------------------------------------------------------------------------
INLINE short CATMathStreamImpl::IsContainingAttributes() const
{
  return CGStr._Attributes ? 1 : 0;
}

//-----------------------------------------------------------------------------
// IsDedicatedToReplay
//-----------------------------------------------------------------------------
INLINE CATExtCGMReplay* CATMathStreamImpl::IsDedicatedToReplay() const
{
  return _pDedicatedToReplay;
}

//-----------------------------------------------------------------------------
// IsDedicatedToPlayBack
//-----------------------------------------------------------------------------
INLINE CATechSet* CATMathStreamImpl::IsDedicatedToPlayBack() const
{
  return _pPlayBack;
}


//-----------------------------------------------------------------------------------------
// IsUnderCompositeManagement ;
//     initially introduced as more flexible and new opened data structure of CGMReplay
//     new internal file convention with *.zip.CGMReplay 
//          default option of 2012Spring DataFormat Structure (14 07 2012)
//-----------------------------------------------------------------------------------------
INLINE CATechSet* CATMathStreamImpl::IsUnderCompositeManagement() const
{ return _pCompositeManagement; }

INLINE CATechAttribute* CATMathStreamImpl::HasCompositeBootAttribute() const
{ return _pCompositeAttribute; }
 

//-----------------------------------------------------------------------------
// CheckCompositeManagementAtOpen
//-----------------------------------------------------------------------------

INLINE void CATMathStreamImpl::CheckCompositeManagementAtOpen()  
{
  CGStr._CheckCompositeManagementAtOpen = 1;
}


INLINE void CATMathStreamImpl::ForceCompositeManagementAtOpen()  
{
  CGStr._ForceCompositeManagementAtOpen = 1;
}



//-----------------------------------------------------------------------------
// DumpIsActive
//-----------------------------------------------------------------------------
INLINE int CATMathStreamImpl::DumpIsActive() const
{
  return _pDump ? 1 : 0;
}

//-----------------------------------------------------------------------------
// CheckLinksWritten
//-----------------------------------------------------------------------------
INLINE void CATMathStreamImpl::CheckLinksWritten() const
{
  if ( (_ObjectOperation == NotSpecified  ) || (_ObjectOperation == ExternalWeakLinks) ) return;
  if (  (_OperationStatus != LinksCompleted) &&  CGStr._CheckLinks )  CheckLinksWrittenError();
}

//-----------------------------------------------------------------------------
// CheckLinksRead
//-----------------------------------------------------------------------------
INLINE void CATMathStreamImpl::CheckLinksRead() const
{
  if ( (_ObjectOperation == NotSpecified  ) || (_ObjectOperation == ExternalWeakLinks) ) return;
  if ( (_OperationStatus != LinksCompleted) && CGStr._CheckLinks ) CheckLinksReadError();
}

//-----------------------------------------------------------------------------
// GetAccesType
//-----------------------------------------------------------------------------
INLINE CATCGMStreamType CATMathStreamImpl::GetAccesType() const
{
  return _acces;
}

//-----------------------------------------------------------------------------
// GetStorageType
//-----------------------------------------------------------------------------
INLINE CATCGMStreamStorage CATMathStreamImpl::GetStorageType() const
{
  return _storage;
}

//-----------------------------------------------------------------------------
// DelayedCleanedBuffer
//-----------------------------------------------------------------------------

INLINE short CATMathStreamImpl::IsDelayedCleanedBuffer()  const 
{
  return CGStr._DelayedCleanedBuffer ? 1 : 0;
}

INLINE void CATMathStreamImpl::DefineDelayedCleanedBuffer() 
{
  CGStr._DelayedCleanedBuffer = 1;
}

INLINE CATGMAdapter *  CATMathStreamImpl::HasMetaDescriptor() const
{
  return _pMetaDescriptor;
}

//-----------------------------------------------------------------------------
// LoadBufferFromDirectStreamIfNeeded
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::LoadBufferFromDirectStreamIfNeeded(size_t iIndexToRead, size_t iSizeOfData)

{
  if ((!_pDirectStream) && (!_istream) && (!_IsBinaryStream))
    return TRUE;

  if ((iIndexToRead >= _DirectStreamReadIndexMin) &&
      ((iIndexToRead + iSizeOfData - 1) <= _DirectStreamReadIndexMax))
    return TRUE;

  return LoadBufferFromDirectStream(iIndexToRead, iSizeOfData);
}


//-----------------------------------------------------------------------------
  // restricted CATCGM_STREAM
//-----------------------------------------------------------------------------
INLINE CATBoolean CATMathStreamImpl::IsContiguousReadMemory(void* & oBuffer,  size_t & oSizeBuffer)
{
  oBuffer = 0;  oSizeBuffer=0;
  if (  _acces != CatCGMStreamReadOnly ) return FALSE;
  if (  !_pCurrentBuffer ) return FALSE;
  oBuffer = _pCurrentBuffer;  oSizeBuffer=_CurrentBufferLength_or_InputFileLength;
  return TRUE;
}


//-----------------------------------------------------------------------------
// CATCGMStreamIsNewerThanOrEqualTo / Clean V5R20 
//-----------------------------------------------------------------------------
INLINE ExportedByCATMathStream CATBoolean CATCGMStreamIsNewerThanOrEqualTo(const CATCGMStreamVersion first, const CATCGMStreamVersion second)
{ return ( (int)first >= (int)second ) ? TRUE : FALSE; }
 

// CATCGMBinaryStream
INLINE void CATMathStreamImpl::SetBinaryStream(CATCGMBinaryStream * iStream, const CATCGMStreamType& iAcces, size_t iSizeStream)
{
  _pBinaryStream = iStream;
  _IsBinaryStream = TRUE;

  if(iAcces == CatCGMStreamReadOnly)
  {
    _pCurrentBuffer   = (unsigned char*)NULL;
    _CurrentBufferLength_or_InputFileLength  = iSizeStream;
    _WrittenDataLength_or_InputFileLength = iSizeStream;
  }
}

INLINE CATCGMBinaryStream * CATMathStreamImpl::GetBinaryStream() const
{
  return _pBinaryStream;
}

#endif

