/* -*-c++-*- */
#ifndef CGMHeaderStream_h_
#define CGMHeaderStream_h_
// COPYRIGHT DASSAULT SYSTEMES  1999

//=============================================================================
// Mar. 04 CATCGMObjectHeaderMinSize                                      HCN
// May. 04 CATCGMObjectHeaderDataSizeMax                                  HCN
//=============================================================================

#include "ExportedByCATMathStream.h"
#include "BigLittle.h"
#include <string.h> /* memset */
#include "CATMathInline.h"

//====================================================
//    NT/UNIX Marker & its length
//====================================================
extern ExportedByCATMathStream unsigned char CGMEndianMarker;
#define       CGMEndianMarkerLgth     1


//====================================================
//     Anti-Corruption Marker
//====================================================
#define       CGMICODHD             179

//====================================================
//   Header generique d'object
//====================================================

#define CATCGMObjectHeaderBaseSize        5
#define CATCGMObjectHeaderAverageSize     13

#define CATCGMObjectHeaderBaseSizeCompact 4

// Taille maximale dans les headers d'objet
#define CATCGMObjectHeaderDataSizeMax 0xFFFF

struct CATCGMHeaderBitsStream
{
#if defined ( _ENDIAN_LITTLE )
// #ifdef _WINDOWS_SOURCE
  unsigned char   HasTag       : 1;
  unsigned char   HasData      : 1;
  unsigned char   HasContainer : 1;
  unsigned char   hascolor     : 1;
  unsigned char   Explicit     : 1;
  unsigned char   HasExtraBits : 1;
  unsigned char   noshow       : 1;
  unsigned char   Infinite     : 1;
#else
  unsigned char   Infinite     : 1;
  unsigned char   noshow       : 1;
  unsigned char   HasExtraBits : 1;
  unsigned char   Explicit     : 1;
  unsigned char   hascolor     : 1;  
  unsigned char   HasContainer : 1;
  unsigned char   HasData      : 1;
  unsigned char   HasTag       : 1;
#endif
};


struct CATCGMHeaderColorsStream
{
  unsigned char   red   : 4;
  unsigned char   green : 4;
  unsigned char   blue  : 4;
  unsigned char   alpha : 4;
};



struct CATCGMHeaderExtraBits
{
#if defined ( _ENDIAN_LITTLE )
// #ifdef _WINDOWS_SOURCE
  unsigned char touched       : 1;  // duplication necessaire pour le partage ... 
  unsigned char IsFrozen      : 1;  // Gel permanent 
  unsigned char IsPersistent  : 1;  // Marquage Feature 
  unsigned char IsSmallerThan255Bytes : 1;  // Marquage Feature 
  unsigned char NotYetDefined : 4;   
#else
  unsigned char NotYetDefined : 4;   
  unsigned char IsSmallerThan255Bytes : 1;  // Marquage Feature 
  unsigned char IsPersistent  : 1;  // Marquage Feature 
  unsigned char IsFrozen      : 1;  // Gel permanent 
  unsigned char touched       : 1;  // duplication necessaire pour le partage ... 
#endif
};



struct CATCGMHeaderObjectStream 
{
  INLINE CATCGMHeaderObjectStream() { memset(this,0,sizeof(CATCGMHeaderObjectStream) ); }

  union
  {
    CATCGMHeaderBitsStream Value;
    unsigned char          CharBits;
  }
  Bits;

  short         Type;
  CATULONG32    Tag;
  CATLONG64     RelativeTag;
  CATULONG32    ContainerSize;
  CATULONG32    DataSize;

  union
  {
    CATCGMHeaderColorsStream  Value;
    short                     ShortColors;
  }
  Colors;

  union
  {
    CATCGMHeaderExtraBits  Value;
    unsigned char          CharBits;
  }
  ExtraBits;

};

//====================================================
//   Header for each Object
//====================================================
struct CATCGMAttrHeaderStream 
{
  INLINE CATCGMAttrHeaderStream() { memset(this,0,sizeof(CATCGMAttrHeaderStream) ); }

    INLINE CATCGMAttrHeaderStream(CATULONG32 iTag, short iType, short iIcod, CATULONG32 iContainerSize )
      : Tag(iTag)
      , Type(iType)
      , Icod(iIcod)
      , ContainerSize(iContainerSize)
    { }

  CATULONG32    Tag ;
  short           Type ;

  short           Icod ;
  CATULONG32    ContainerSize ;
};

//====================================================
// UseFull Information for UserAttrRef
//====================================================
struct CATCGMHeaderUserAttrRef
{
  INLINE CATCGMHeaderUserAttrRef() { HasAttributes = 0; }

  short HasAttributes;   
};

#endif
