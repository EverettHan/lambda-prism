/**
* @COPYRIGHT DASSAULT SYSTEMES 2009
*/
//=============================================================================
// Utility macros for multiple code sequence definition. May be used several time in same source 
//=============================================================================
// 
// Usage:
// -----
//  // (MultipleDefineMacroBy1 must be provided by user code)
//  #define MultipleDefineMacroBy1(Num)\
//   macro instructions using argument Num
//  #include CATMathMultipleDefineMacro.h
//  #undef MultipleDefineMacroBy1
// // (define occurences number 000 to 099)
// MultipleDefineMacroBy100(0)
// // (define occurences numer 100 to 199)
// MultipleDefineMacroBy100(1)
// 
//  #define MultipleDefineMacroBy1(Num)\
//   other macro instructions using argument Num
//  #include CATMathMultipleDefineMacro.h
//  #undef MultipleDefineMacroBy1
// // (define occurences number 000 to 999)
// MultipleDefineMacroBy1000(1)
// 
// Caution:
// -------
// in macro MultipleDefineMacroBy1, Num may have leading 0, as in 07 for instance,
// and thus not be seen by compiler as decimal integer value;
// use a large enough prefix to avoid error, for instance
// #define MultipleDefineMacroBy1(Num)\
//  if (10000+Index==100##Num) CallMethod##Num();
// if macro used from 00 to 99
//=============================================================================
// 29/06/09 NLD Creation (MultipleDefineMacroBy10, MultipleDefineMacroBy100, MultipleDefineMacroBy1000)
//=============================================================================
#ifndef MultipleDefineMacroBy1
 #define MultipleDefineMacroBy10 // 
#endif
// for definition of 10 occurences from ##Num##0 to ##Num##9
#ifdef MultipleDefineMacroBy10
 #undef MultipleDefineMacroBy10
#endif
#define MultipleDefineMacroBy10(Num)\
 MultipleDefineMacroBy1(##Num##0)\
 MultipleDefineMacroBy1(##Num##1)\
 MultipleDefineMacroBy1(##Num##2)\
 MultipleDefineMacroBy1(##Num##3)\
 MultipleDefineMacroBy1(##Num##4)\
 MultipleDefineMacroBy1(##Num##5)\
 MultipleDefineMacroBy1(##Num##6)\
 MultipleDefineMacroBy1(##Num##7)\
 MultipleDefineMacroBy1(##Num##8)\
 MultipleDefineMacroBy1(##Num##9)
// for definition of 100 occurences from ##Num##00 to ##Num##99
#ifdef MultipleDefineMacroBy100
 #undef MultipleDefineMacroBy100
#endif
#define MultipleDefineMacroBy100(Num)\
 MultipleDefineMacroBy10(##Num##0)\
 MultipleDefineMacroBy10(##Num##1)\
 MultipleDefineMacroBy10(##Num##2)\
 MultipleDefineMacroBy10(##Num##3)\
 MultipleDefineMacroBy10(##Num##4)\
 MultipleDefineMacroBy10(##Num##5)\
 MultipleDefineMacroBy10(##Num##6)\
 MultipleDefineMacroBy10(##Num##7)\
 MultipleDefineMacroBy10(##Num##8)\
 MultipleDefineMacroBy10(##Num##9)
// for definition of 1000 occurences from ##Num##000 to ##Num##999
#ifdef MultipleDefineMacroBy1000
 #undef MultipleDefineMacroBy1000
#endif
#define MultipleDefineMacroBy1000(Num)\
 MultipleDefineMacroBy100(##Num##0)\
 MultipleDefineMacroBy100(##Num##1)\
 MultipleDefineMacroBy100(##Num##2)\
 MultipleDefineMacroBy100(##Num##3)\
 MultipleDefineMacroBy100(##Num##4)\
 MultipleDefineMacroBy100(##Num##5)\
 MultipleDefineMacroBy100(##Num##6)\
 MultipleDefineMacroBy100(##Num##7)\
 MultipleDefineMacroBy100(##Num##8)\
 MultipleDefineMacroBy100(##Num##9)
