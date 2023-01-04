#ifndef CATMathStreamBlocs_h_
#define CATMathStreamBlocs_h_
//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2002
//
//  INTERDICTION D'INCLURE DANS HEADER CAA
//
//  HEADER IMPLEMENTATION : PERMETTRE EVOLUTION VUE IMPLEMENTATIVE
//
//=============================================================================
// Jan. 03 Stream direct avec CATStream                                   HCN
// Dec. 03 GetDirectUnstreamBuffer(...), SetDirectUnstreamBuffer(...),
//         GetNbDirectUnstreamBuffers(...), GetMaxNbDirectUnstreamBuffers()
//         Gestion des CATMathDirectUnstreamBuffer                        HCN
// Mar. 04 _LatestStreamedObjectTag,
//         _PreviousObjectTag, _PreviousObjectType,
//         _SetObjectTag, _SetObjectType,
//         _pTabMapTagsToSizes,
//         _MaxLinksCountInHeader, _ObjectLinksCountData,
//         pour avoir equivalent CATMathStream.h R14 sur R13 er R12       HCN
// Apr. 04  struct CATMathStreamStats et _pStatistics,
//         pour avoir equivalent CATMathStream.h R14 sur R13 er R12,
//          _LatestStreamedDeltaObjectTag
//          _LatestStreamedDeltaSignObjectTag
//          _NbSameDeltaAndSignObjectTags,
//          _pTabMapCGMTypesToULong32s, _pTabMapULong32sToCGMTypes        HCN
// May. 04 _SetObjectIndex, _NoSizeInObjectHeader
//         _pListMapIndexToSizes                                          HCN
// Jun. 04 Mise a jour des Stats : je rajoute un champs dans la structure
//         CATMathStreamStats                                             MNA
// Jun. 04 BitStream                                                      HCN
// Mar. 05 DirectStreamBuffer***     dans CATMathStreamStats,
//         #define CATCGM_UNSTREAM_STATS_MIN_TRACES                       HCN
// Apr. 05 Suppression dans CATMathStreamBlocs de :
//           CATMathStreamStats* _pStatistics,
//           _LatestStreamedObjectTag,
//           _LatestStreamedDeltaObjectTag,
//           _LatestStreamedDeltaSignObjectTag,
//           _NbSameDeltaAndSignObjectTags,
//           _PreviousObjectTag,
//           _PreviousObjectType,
//           _SetObjectTag,
//           _SetObjectType,
//           _MaxLinksCountInHeader,
//           _ObjectLinksCountData,
//           _SetObjectIndex,
//           _NoSizeInObjectHeader,
//           _pTabMapTagsToSizes,
//           _pListMapIndexToSizes,
//           _pTabMapCGMTypesToULong32s,
//           _pTabMapULong32sToCGMTypes                                   HCN
//         Migration de CATMathStream\CATCGMStream vers la classe
//           d'implementation CATMathStreamImpl\CATCGMStreamImpl          HCN
//=============================================================================

#include "ExportedByCATMathStream.h"
#include "CATCGMNewArray.h"
#include "CATBoolean.h"
#include "CATDataType.h"
#include "CATListOfInt.h"
#include "CATMathStreamImpl.h"
#include "CATMathStreamStats.h"

#include  <stdio.h>
#include  <stdlib.h>
#include  <stddef.h>



/** @c++ansi fbq 2004-08-05.10:18:26 [Replace forward declaration by #include <iosfwd.h>] **/
#ifdef _CAT_ANSI_STREAMS
#include <iosfwd.h>
#else
class ostream;
#endif
class CATMathStreamBuffer;
struct CATMathDirectUnstreamBuffer;
class CATCGMHashTableWithAssoc;

// A commenter
// #define CATCGM_UNSTREAM_STATS_MIN_TRACES
// #define CATCGM_UNSTREAM_STATS_TRACES
// #define CATCGM_STREAM_REORDER_OBJECTS_TRACES

#ifdef CATCGM_UNSTREAM_STATS_TRACES
  #define CATCGM_UNSTREAM_STATS_MIN_TRACES
#endif
 

class ExportedByCATMathStream CATMathStreamBlocs
{
public:
  CATCGMNewClassArrayDeclare;
  
protected :
  
  CATMathStreamBlocs(CATMathStreamImpl &iStream); 
  ~CATMathStreamBlocs();
  
  void Clear();
  
  CATBoolean AllocateNewBuffer(size_t           iAtLeastBufferLength,
                               const CATBoolean iEnableLargerBuffer,       // FALSE
                               const CATBoolean iEnableByAddress,          // FALSE
                               unsigned char   *iForDirectAddress,         // NULL
                               CATBoolean       iForNeedContinousLength,   // FALSE
                               CATBoolean       iForInitialisation     );  // FALSE

  int GetDirectUnstreamBuffer(size_t          iIndexToRead,
                              size_t          iSizeOfData,
                              unsigned char*& iopDirectStreamCurrentBuffer,
                              size_t&         ioDirectStreamCurrentBufferSize,
                              size_t&         ioDirectStreamReadIndexMin,
                              size_t&         ioDirectStreamReadIndexMax);

  unsigned char* GetDirectUnstreamBuffer(int iBufferIdx);

  int SetDirectUnstreamBuffer(unsigned char* iopDirectStreamCurrentBuffer,
                              size_t         ioDirectStreamCurrentBufferSize,
                              size_t         ioDirectStreamReadIndexMin,
                              size_t         ioDirectStreamReadIndexMax);

  static int GetMaxNbDirectUnstreamBuffers();

  unsigned char* SeekPreviousBuffer(const size_t iWhere, const size_t iBytesLength);
  
  CATBoolean IsEqualTo(const CATMathStreamImpl* iCompare) const;
  
  void GetMemoryCopy(const size_t iSizeBuffer, void* iBuffer, size_t &ioSizeCopied);
  
  HRESULT GetNumberOfArea(size_t &oGlobalLengthInBytes, CATULONG32  &oNumberOfArea);
  
  HRESULT GetValueOfArea(const CATULONG32  iNumberOfArea, size_t * ioAreaLengthInBytes, const unsigned char  *  * ioAreaAddress);

  CATMathStreamBuffer* TryCATCGMemBook(size_t iRequiredSize);
  HRESULT GetBufferMemoryInfos(size_t &oCGMDataLengthInBytes, CATULONG32  &oNumberOfArea, size_t &oAllocatedLengthInBytes);
  void UpdateCurrentBufferOpenHeaderCount();
  void UpdateSoughtBufferOpenHeaderCount();
  void WriteBufferToDisk(CATMathStreamBuffer*& iopBuffer);
  void WriteBuffersWithoutOpenHeadersToDisk(CATBoolean iWriteLastBloc = FALSE);

  void CloseReadSynchroZero();
  void CloseWriteSynchroZero();
  void CloseWriteEffectiveWrite(ostream *ioFile, FILE *oFileC);
  
  //VUC:2010-02-01 store the underlying catstream current position as the starting one for this CATCGMStream
  void SetDirectStreamStartPosition();

  void CheckSumBuffer(size_t iBeginIndex, size_t iEndIndex, CATULONG64 &oCheckSumResult);
  HRESULT ModifyDataAt(size_t iWhere, size_t NbBytes, unsigned char* iData);
private :

  static CATULONG32            _IDs;
  static CATULONG32            _DirectUnstreamBufferIDs;
  static CATULONG32            _NbWriten;

  CATULONG32                   _ID;
  size_t                       _DirectStreamWrittenBytes;

  CATMathStreamBuffer*         _pCurrentBuffer;
  CATMathStreamBuffer*         _pSoughtBuffer;

  unsigned char*               _pBitStreamBuffer;
  size_t                       _BitStreamNbStoredBits;
  size_t                       _BitStreamNbStreamedBytes;

  CATMathDirectUnstreamBuffer* _pTabUnstreamBuffers;
  int                          _NbUnstreamBuffers;
  int                          _CurrentUnstreamBufferIdx;
  int                          _LastUnstreamBufferFlushedIdx;

  CATMathStreamImpl&           _Stream;
  CATMathStreamBuffer*         _FirstBuffer; 

  CATULONG64                   _DirectStreamStartPos;

  friend class CATMathStreamImpl;
  friend class CATCGMStream;
  friend class CATCGMStreamCGMImpl;
};

extern void MathInStreamFileAccessRead(const char *iFileName) ;
extern void MathInStreamFileAccessWrite(const char *iFileName) ;



#endif
