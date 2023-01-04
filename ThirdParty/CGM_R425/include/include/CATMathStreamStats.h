#ifndef CATMathStreamStats_h_
#define CATMathStreamStats_h_
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
#include  <stdio.h>
#include  <stdlib.h>
#include  <stddef.h>
 

struct CATMathStreamStats
{
  size_t MaxStreamIndex;

  size_t NbObjects;
  size_t NbNOTStreamedObjects;

  size_t NbStreamHeaders;
  size_t SizeOfStreamHeaders;

  size_t NbObjectHeaders;
  size_t SizeOfObjectHeaders;

  size_t NbAttrHeaders;
  size_t SizeOfAttrHeaders;

  size_t NbLinkedObjectLists;
  size_t SizeOfLinkedObjectLists;

  size_t NbUChars;
  size_t SizeOfUChars;

  size_t NbShorts;
  size_t SizeOfShorts;

  size_t NbUShorts;
  size_t SizeOfUShorts;

  size_t NbLongs;
  size_t SizeOfLongs;

  size_t NbLongs64;
  size_t SizeOfLongs64;

  size_t NbULongs;
  size_t SizeOfULongs;

  size_t NbULongs64;
  size_t SizeOfULongs64;

  size_t NbULongWithSigns;
  size_t SizeOfULongWithSigns;

  size_t NbULong64WithSigns;
  size_t SizeOfULong64WithSigns;

  size_t NbULongWithSignWithInfos;
  size_t SizeOfULongWithSignWithInfos;

  size_t NbFloats;
  size_t SizeOfFloats;

  size_t NbDoubles;
  size_t SizeOfDoubles;

  size_t NbStrings;
  size_t SizeOfStrings;

  size_t DirectStreamBufferSizeDefault;
  size_t DirectStreamBufferSizeAllocatedMin;
  size_t DirectStreamBufferSizeAllocatedMax;
  size_t DirectStreamBufferSizeReadMin;
  size_t DirectStreamBufferSizeReadMax;

  size_t DirectStreamBufferNbCalls;
  size_t DirectStreamBufferNbAllocs;
  size_t DirectStreamBufferNbDesallocs;
  size_t DirectStreamBufferLastCallIndex;
  size_t DirectStreamBufferLastCallMaxReadIndex;
  size_t DirectStreamBufferPrevNbReadHeaderObjectAt;

  size_t DirectStreamBufferNbReads;
  size_t DirectStreamBufferSizeRead;

  size_t DirectStreamBufferNbCGMObj;
  size_t DirectStreamBufferNbCGMObjWithReads;
  CATListOfInt* pDirectStreamBufferListCGMObjReadIndex;
  size_t DirectStreamBufferTotalCGMObjStreamRange;

  size_t DirectStreamBufferNbCGMObjStreamRangeOverSize;
  size_t DirectStreamBufferNbCGMObjUnstreamedLinked;

  size_t DirectStreamBufferNbCGMObjWithoutOrderedStr;

  int    DirectStreamBufferHeaderStatsPerCGMObject;
};

 
#endif
