//______________________________________________________________________
// P REISS   03/04
// macro CATLEADING1BIT.h
// cas log ( iDim ) a valeurs privilegiees < 4096 = algo L0 actif ici
// cas iDim a valeurs equiprobables = boucle (test bit de gauche, shl 1)
//     (non programme ici, voir Arith/SourUlla)
//
// logarithme en base 2 de iDim, en nombre de bits, dans [0,31]
// valeur = K   sur iDim = ( 2^K, 2^(K+1) - 1 )
//              pour K = 0 a 31
// iDim nul ->  valeur = 0
//*** utilisation: pour adresser _TableN et _TableT
// silla iDim, silla oVal,
//   Label = un identificateur different pour chaque appel

#if defined(_SIMUL) || !defined(_WINDOWS_SOURCE)
#define LEADING1BIT( iDim, oVal, Label )    \
  {                                         \
  if ( iDim )                               \
    {                                       \
    silla Edx = iDim;                       \
    oVal = 0x1F;                            \
    while ( !(Edx & 0xFF000000) )           \
      {                                     \
      Edx <<= 8;                            \
      oVal -= 8;                            \
      }                                     \
    while ( Edx >= 0 )                      \
      {                                     \
      Edx += Edx;                           \
      oVal--;                               \
      }                                     \
    }                                       \
  else oVal = 0;                            \
  }
#else
#ifdef _WIN64
// asm 64 bits

#include "CATLeading1Bit64.h"

#define LEADING1BIT( iDim, oVal, Label )    \
  oVal = CATLeading1Bit64 ( iDim, 0xFFFFFFFF00000000 );
#else
// asm Pentium4
// shr de Label7 teste bit suivant
// "mov eax,0x17" possible a la place de "lea eax,DWORD PTR[eax-8]"
// branche A##Label##4 defavorisee, car plus rare:
//   1 test  en moins pour [   1, 0xC] bits significatifs ( iDim < 4096 )
//   0 test  en moins pour [ 0xD,0x10] bits significatifs
//   2 tests en plus  pour [0x11,0x20] bits significatifs ( iDim > 65535 )

#define LEADING1BIT( iDim, oVal, Label )    \
  {                                         \
  __asm                                     \
    {                                       \
    __asm mov     edx,iDim                  \
    __asm test    edx,0xFFFFFF00            \
    __asm jne     A##Label##2               \
    __asm shl     edx,0x18                  \
    __asm mov     eax,7                     \
  __asm A##Label##1:                        \
    __asm test    edx,0xF0000000            \
    __asm jne     A##Label##5               \
    __asm shl     edx,4                     \
    __asm lea     eax,DWORD PTR[eax-4]      \
    __asm test    edx,0xC0000000            \
    __asm mov     ecx,-1                    \
    __asm jne     A##Label##6               \
    __asm shl     edx,2                     \
    __asm lea     eax,DWORD PTR[eax-2]      \
    __asm jmp     A##Label##6               \
                                            \
  __asm A##Label##2:                        \
    __asm test    edx,0xFFFFF000            \
    __asm jne     A##Label##3               \
    __asm shl     edx,0x14                  \
    __asm mov     eax,0xB                   \
    __asm jmp     A##Label##5               \
  __asm A##Label##3:                        \
    __asm test    edx,0xFFFF0000            \
    __asm jne     A##Label##4               \
    __asm shl     edx,0x10                  \
    __asm mov     eax,0xF                   \
    __asm jmp     A##Label##5               \
  __asm A##Label##4:                        \
    __asm test    edx,0xFF000000            \
    __asm mov     eax,0x1F                  \
    __asm jne     A##Label##1               \
    __asm shl     edx,8                     \
    __asm lea     eax,DWORD PTR[eax-8]      \
    __asm jmp     A##Label##1               \
                                            \
  __asm A##Label##5:                        \
    __asm test    edx,0xC0000000            \
    __asm mov     ecx,-1                    \
    __asm jne     A##Label##6               \
    __asm shl     edx,2                     \
    __asm lea     eax,DWORD PTR[eax-2]      \
  __asm A##Label##6:                        \
    __asm mov     edx,0                     \
    __asm cmovns  edx,ecx                   \
    __asm add     eax,edx                   \
    __asm mov     oVal,eax                  \
    }                                       \
  }
#endif
#endif
