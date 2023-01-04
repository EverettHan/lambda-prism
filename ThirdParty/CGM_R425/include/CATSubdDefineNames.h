// COPYRIGHT DASSAULT SYSTEMES 1996
//=============================================================================
//
// CATSubdDefineNames :
// ensemble de macros permettant de declarer des collections d'objets
// independamment de l'implementation physiques choisie 
//
//=============================================================================
// Usage notes:
//
//=============================================================================
// Oct. 96  Creation                          I. Chauvigne, X. Dupont, L. Laloy
//=============================================================================
#ifndef CATSubdDefineNames_H
#define CATSubdDefineNames_H

#define CATSubdQuote(arg) #arg

#define CATSubdArray(Suffix) CATSubdArray##Suffix
#define CATSubdArrayP(Suffix) CATSubdArray##Suffix##P

//#define CATSubdIncludeArray(Suffix) CATSubdQuote(CATSubdArray##Suffix.h)
//#define CATSubdIncludeArrayP(Suffix) CATSubdQuote(CATSubdArray##Suffix##P.h)

#endif


