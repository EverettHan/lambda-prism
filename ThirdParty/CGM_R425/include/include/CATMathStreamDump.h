#ifndef CATMathStreamDump_h
#define CATMathStreamDump_h

//=============================================================================
// Jul. 02 Portage 64 bits                                               HCN
// Feb. 04 DumpCommentxxx(...),
//         Read/WriteBoolean(...),
//         Read/WriteCATUuid(...),
//         Read/WriteObjectHeader(...),
//         Read/WriteHeaderUserAttrRef(...),
//         Read/WriteAttrHeader(...),
//         Read/WriteHeaderUserAttrRef(...),
//         Read/WriteAttrHeader(...),
//         CloseRead/WriteHeader(...),
//         DumpStatistics(...),
//         Read/WriteULongWithSign(...),
//         DumpUCharInBinary(...),
//         _Active, SetActiveMode(...)                                    HCN
// Mar. 04 _NbNOTStreamedObjects,
//         PositionHeaderObjectAt(...)                                    HCN
// Apr. 04 Open/CloseWriteULong(...),
//         Arguments nombre d'octets dans Write/ReadDouble(...),
//         Parametre iStreamedCGMType pour Write/ReadObjectHeader(...)    HCN
// May. 04 Parametres iNbBytesToxxx pour Read/WriteCATUuid(...)           HCN
// Jun. 04 _XMLFormat, SetXMLFormat(...),
//         Parametres pMethodName pour Read/WriteDouble(...)              HCN
// Jun. 04 Ajout des methodes Read/WriteLong64/ULong64(...)               MNA
// Jul. 04 Write/ReadLong64(..., ...iRowLength, ...iNbRows, ...);         HCN
// Apr. 05 Migration de CATMathStream\CATCGMStream vers la classe
//           d'implementation CATMathStreamImpl\CATCGMStreamImpl          HCN
// Jul. 09 Suppression du StreamCompact                                   VUC
//=============================================================================

#include "CATMathematics.h"
#include "CATDataType.h"
#include "ExportedByCATMathStream.h"

struct CGMHeaderStream;

/** @nodoc */
class CATMathBox;
class CATMathPoint;
class CATMathPointf;
class CATMathVector2D;
class CATMathVector;
class CATMathVectorf;
class CATMath3x3Matrix;
class CATMathTransformation;
class CATMathAxis;
class CATMathPlane;
/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATTrace;
class CATMathStreamImpl;
class CATRawCollPV;
class CATMathAdvancedBox;


class ExportedByCATMathStream CATMathStreamDump 
{
public:

  CATMathStreamDump() {};
  virtual ~CATMathStreamDump() {};

  virtual CATBoolean SetActiveMode(CATBoolean iActive) = 0 ;

  virtual CATBoolean SetXMLFormat(CATBoolean iXMLFormat) = 0 ;

  virtual CATBoolean IsXMLFormat() = 0 ;

  virtual void WriteUChar  (const unsigned char iUChar, const char iReservedLabel[] ) = 0 ;
  virtual void WriteUChar  (const unsigned char* iUCharArray, const CATLONG32 iNbCell, const char iReservedLabel[]  ) = 0 ;

  virtual void WriteShort  (const short iShort, int iNbBytesToWrite, CATBoolean iAsULongWithSign, const char iReservedLabel[] ) = 0 ;
  virtual void WriteUShort  (const unsigned short iUShort, const char iReservedLabel[] ) = 0 ;

  virtual void WriteShort  (const short* iShortArray, const CATLONG32 iNbCell, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;

  virtual void WriteLong   (const CATLONG32 iLong, int iNbBytesToWrite, CATBoolean iAsULongWithSign, const char iReservedLabel[] ) = 0 ;
  virtual void WriteLong   (const CATLONG32* iLongArray, const CATLONG32 iNbCell, int iNbBytesToWrite, CATBoolean iAsULongWithSign, const char iReservedLabel[] ) = 0 ;

  virtual void WriteULong  (const CATULONG32  iULong, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;
  virtual void WriteULong  (const CATULONG32 * iULongArray, const CATLONG32 iNbCell, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;

  virtual void WriteLong64 (const CATLONG64 iLong, int iNbBytesToWrite, CATBoolean iAsULongWithSign, const char iReservedLabel[] ) = 0 ;
  virtual void WriteLong64 (const CATLONG64* iLongArray, const CATLONG32 iNbCell, int iNbBytesToWrite, CATBoolean iAsULongWithSign, const char iReservedLabel[] ) = 0 ;

  virtual void WriteLong64 (const CATLONG64* iLongArray, const CATLONG32 iRowLength, const CATLONG32 iNbRows, const char iReservedLabel[]) = 0 ;

  virtual void WriteULong64(const CATULONG64  iULong, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;

  virtual void WriteDouble (const double iDouble, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;
  virtual void WriteDouble (const double* iDoubleArray, const CATLONG32 iNbCell, int iNbBytesToWrite, const char* pMethodName, const char iReservedLabel[] ) = 0 ;

  virtual void WriteFloat  (const float iFloat, const char iReservedLabel[] ) = 0 ;
  virtual void WriteFloat  (const float* iFloatArray, const CATLONG32 iNbCell, const char iReservedLabel[] ) = 0 ;

  virtual void WriteString (const char* iString, const char iReservedLabel[] ) = 0 ;

  virtual void ReadUChar   (unsigned char& ioUChar, const char iReservedLabel[] ) = 0 ;
  virtual void ReadUChar   (unsigned char* ioArrayUChar, const CATLONG32 iNbCell, const char iReservedLabel[]  ) = 0 ;

  virtual void ReadShort   (short& ioShort, int iNbBytesToRead, CATBoolean iAsULongWithSign, const char iReservedLabel[] )     = 0 ;
  virtual void ReadUShort  (unsigned short& ioUShort, const char iReservedLabel[] )     = 0 ;

  virtual void ReadShort   (short* ioArrayShort, const CATLONG32 iNbCell, int iNbBytesToRead, const char iReservedLabel[] )     = 0 ;

  virtual void ReadLong    (CATLONG32& ioLong, int iNbBytesToRead, CATBoolean iAsULongWithSign, const char iReservedLabel[] )     = 0 ;
  virtual void ReadLong    (CATLONG32* ioArrayLong, const CATLONG32 iNbCell, int iNbBytesToRead, CATBoolean iAsULongWithSign, const char iReservedLabel[] )     = 0 ;

  virtual void ReadULong   (CATULONG32 & ioULong, int iNbBytesToRead, const char iReservedLabel[] ) = 0 ;
  virtual void ReadULong   (CATULONG32 * ioArrayULong , const CATLONG32 iNbCell, int iNbBytesToRead, const char iReservedLabel[] ) = 0 ;

  virtual void ReadLong64  (CATLONG64& ioLong, int iNbBytesToRead, CATBoolean iAsULongWithSign, const char iReservedLabel[] )     = 0 ;
  virtual void ReadLong64  (CATLONG64* ioArrayLong, const CATLONG32 iNbCell, int iNbBytesToRead, CATBoolean iAsULongWithSign, const char iReservedLabel[] )     = 0 ;

  virtual void ReadLong64  (const CATLONG64* iLongArray, const CATLONG32 iRowLength, const CATLONG32 iNbRows, const char iReservedLabel[]) = 0 ;

  virtual void ReadULong64 (CATULONG64 & ioULong, int iNbBytesToRead, const char iReservedLabel[] ) = 0 ;

  virtual void ReadDouble  (double& ioDouble, int iNbBytesToRead, const char iReservedLabel[] )  = 0 ;
  virtual void ReadDouble  (double* ioArrayDouble, const CATLONG32 iNbCell, int iNbBytesToRead, const char* pMethodName, const char iReservedLabel[] )  = 0 ;

  virtual void ReadFloat   (float& ioFloat, const char iReservedLabel[] )  = 0 ;
  virtual void ReadFloat   (float* ioArrayFloat, const CATLONG32 iNbCell, const char iReservedLabel[] )  = 0 ;

  virtual void ReadString  (char*& ioString, const char iReservedLabel[] )   = 0 ;

  virtual void WriteULongWithSign(const CATULONG32  iULong, short iSign, short* ipInfo_0_or_1, int iNbBytesToWrite, CATULONG32 iFirstObjectTag, const char iReservedLabel[] ) = 0 ;
  virtual void ReadULongWithSign(const CATULONG32  iULong, short iSign, short* ipInfo_0_or_1, int iNbBytesToRead, CATULONG32 iFirstObjectTag, const char iReservedLabel[] ) = 0 ;

  virtual void WriteBox (const CATMathBox&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadBox  (CATMathBox& ioBox, const char iReservedLabel[] ) = 0 ;
 
  virtual void WriteAdvancedBox(const CATMathAdvancedBox &iBox, const char iReservedLabel[]) = 0 ;
  virtual void ReadAdvancedBox(CATMathAdvancedBox &oBox, const char iReservedLabel[]) = 0 ;
 
  virtual void WriteStream (const CATMathStreamImpl& iToWrite, const char iReservedLabel[] ) = 0 ;
  virtual void ReadStream  (CATMathStreamImpl& iToRead, size_t iLengthToRead, const char iReservedLabel[] ) = 0 ;
  
  virtual void WritePoint (const CATMathPoint&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadPoint  (CATMathPoint& ioPoint, const char iReservedLabel[] ) = 0 ;

  virtual void WritePointf (const CATMathPointf&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadPointf  (CATMathPointf& ioPoint, const char iReservedLabel[] ) = 0 ;
  
  virtual void WriteVector2D (const CATMathVector2D&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadVector2D  (CATMathVector2D& ioVector2D, const char iReservedLabel[] ) = 0 ;
  
  virtual void WriteVector (const CATMathVector&, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;
  virtual void ReadVector  (CATMathVector& ioVector, int iNbBytesToRead, const char iReservedLabel[] ) = 0 ;
  
  virtual void WriteVectorf (const CATMathVectorf&, int iNbBytesToWrite, const char iReservedLabel[] ) = 0 ;
  virtual void ReadVectorf  (CATMathVectorf& ioVector, int iNbBytesToRead, const char iReservedLabel[] ) = 0 ;

  virtual void Write3x3Matrix (const CATMath3x3Matrix&, const char iReservedLabel[] ) = 0 ;
  virtual void Read3x3Matrix  (CATMath3x3Matrix& ioMatrix, const char iReservedLabel[] ) = 0 ;

  virtual void WriteTransformation (const CATMathTransformation&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadTransformation  (CATMathTransformation& ioTransfo, const char iReservedLabel[] ) = 0 ;

  virtual void WritePlane (const CATMathPlane&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadPlane  (CATMathPlane& ioPlane, const char iReservedLabel[] ) = 0 ;
  
  virtual void WriteAxis (const CATMathAxis&, const char iReservedLabel[] ) = 0 ;
  virtual void ReadAxis  (CATMathAxis& ioAxis, const char iReservedLabel[] ) = 0 ;

  virtual void BeginLabel(CATLONG32 &currentLevel, const char iReservedLabel[] ) = 0 ;
  virtual void EndLabel(const CATLONG32 currentLevel, const char iReservedLabel[] ) = 0 ;

  virtual void WriteUID(const GUID&iid, const char iReservedLabel[]) = 0 ;
  virtual void ReadUID(GUID& iid, const char iReservedLabel[]) = 0 ;

  virtual void OpenWriteStreamHeader(size_t &where, short &level, const short withEndianFormat) = 0 ; 
  virtual void CloseWriteStreamHeader(const size_t where, short level, size_t DataLength) = 0 ;

  virtual void WriteULongAt  (const CATULONG32  Value , const size_t Address, const char iReservedLabel[] ) = 0 ;

  virtual void OpenWriteULong(size_t &where, const char iReservedLabel[]) = 0 ; 
  virtual void CloseWriteULong(const size_t where, const CATULONG32 value) = 0 ; 

  virtual void WriteBoolean(const CATBoolean ioBoolean, const char iReservedLabel[] ) = 0 ;
  virtual void ReadBoolean (CATBoolean& ioBoolean, const char iReservedLabel[]  ) = 0 ;

  virtual void WriteCATUuid(const CATUuid& iid, int iNbBytesToWrite, const char iReservedLabel[]) = 0 ;
  virtual void ReadCATUuid(CATUuid& iid, int iNbBytesToRead, const char iReservedLabel[]) = 0 ;

  virtual void WriteObjectHeader(const size_t&                   iWriteIndex,
                         const CATCGMHeaderObjectStream& iHeader,
                         const unsigned char&            iMaskH1,
                         const unsigned char&            iMaskH2,
                         const short                     iStreamedCGMType,
                         size_t                          ilHeader,
                         const char                      iReservedLabel[]) = 0 ;

  virtual void ReadObjectHeader(const size_t&                   iReadIndex,
                        const CATCGMHeaderObjectStream& iHeader,
                        const unsigned char&            iMaskH1,
                        const unsigned char&            iMaskH2,
                        const short                     iStreamedCGMType,
                        size_t                          ilHeader,
                        CATULONG32*                     ipLinksCount,
                        const char                      iReservedLabel[]) = 0 ;

  virtual void WriteHeaderUserAttrRef(const char ipHeader[2], const char iReservedLabel[]) = 0 ;
  virtual void ReadHeaderUserAttrRef(const char ipHeader[2], const char iReservedLabel[]) = 0 ;

  virtual void WriteAttrHeader(const CATCGMAttrHeaderStream& iHeader, const char iReservedLabel[]) = 0 ;
  virtual void ReadAttrHeader(const CATCGMAttrHeaderStream& iHeader, const char iReservedLabel[]) = 0 ;

  virtual void CloseWriteHeader(const size_t& iLength, CATULONG32* ipLinksCount, const char iReservedLabel[]) = 0 ;
  virtual void CloseReadHeader(const size_t& iLength, CATULONG32* ipLinksCount, const char iReservedLabel[]) = 0 ;

  virtual void PositionHeaderObjectAt(const size_t& iIndex, const char iReservedLabel[]) = 0 ;

  virtual void DumpUCharInBinary(const unsigned char& iUChar) = 0 ;

  virtual void DumpComment(const char iReservedLabel[], int iShift) = 0 ;
  virtual void DumpCommentBegin(const char iReservedLabel[], size_t iStreamIndex, int iBlankLine) = 0 ;
  virtual void DumpCommentEnd(const char* ipReservedLabel, size_t iStreamIndex) = 0 ;

  virtual void DumpStatistics() = 0 ;
 

};


#endif
