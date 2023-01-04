// COPYRIGHT DASSAULT SYSTEMES 1998
//===========================================================================
//
// CATMathConvertDeclare
//
//===========================================================================
// Usage notes:
//    macros de conversion efficaces sous Intel PENTIUM...
//===========================================================================

#ifndef CATMathConvertDeclare_h
#define CATMathConvertDeclare_h

#ifdef WIN32

//    conversion double iDOUBLE -> CATLONG32 oLONG a 10 ^ -6 pres
//    en relatif
//    suppose iDOUBLE >= 0. et legalement convertible sans
//    overflow
//    coute 13 fois moins cher que le ftol standard...

//    poids fort dans le 2e mot de CATMemDou
//    oLONG &= 1048575      recueille la mantisse
//    oLONG |= 1048576      recueille le bit cache
//    oLONG <<= -CATExpos   ne teste pas l' overflow
//    oLONG >>= CATExpos    cas le + frequent

   //register CATLONG32  CATExpos; // PKC 19/02/2020 register obsolete, je vire, ce code sert-il encore? 
   CATLONG32 CATExpos;
   double    CATMemDou;

//    pas de blanc entre CATMathConvertDoubleToLong et (

#define CATMathConvertDoubleToLong( iDOUBLE, oLONG )            \
   CATMemDou = iDOUBLE;                                         \
   oLONG = * ( ( CATLONG32  * ) ( &CATMemDou ) + 1 );             \
   CATExpos = 1043 - ( oLONG >> 20 );                           \
   oLONG &= 1048575;                                            \
   oLONG |= 1048576;                                            \
                                                                \
   if ( CATExpos < 0 )                                          \
      {                                                         \
      if ( CATExpos <= -32 )   oLONG = 0;                       \
      else                     oLONG <<= -CATExpos;             \
      }                                                         \
   else                                                         \
      {                                                         \
      if ( CATExpos >= 32 )    oLONG = 0;                       \
      else                     oLONG >>= CATExpos;              \
      }
#else

// Sinon UNIX

#define CATMathConvertDoubleToLong( iDOUBLE, oLONG )            \
   oLONG = (CATLONG32 ) (iDOUBLE);
#endif
#endif
