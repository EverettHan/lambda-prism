#ifndef CATMathVirtual_h
#define CATMathVirtual_h

#include "CATMathCpp11.h" // define whether or not we're using C++11

// --------------------------------------------------------------
// Some useful macros to use C++11 keywords
// --------------------------------------------------------------

#ifdef MATH_CPP11

#define CATMathOverride override
#define CATMathFinal final

#else

#define CATMathOverride
#define CATMathFinal

#endif

#endif // CATMathVirtual_h
