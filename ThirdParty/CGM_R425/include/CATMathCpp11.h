#ifndef CATMathCpp11_h
#define CATMathCpp11_h

// Q48 11/03/19: no need to include this file (PTO)
//#include "CATOSDefs.h" // the definition of the OS flag

#include "CATIAV5Level.h" // the definition of the TCK level

// --------------------------------------------------------------
// Simple file to define or not whether we can use C++11 features
// --------------------------------------------------------------

#define MATH_CPP11 // by default, yes

#if defined(_AIX_SOURCE) && defined(CATIAV5R29) && !defined(__ibmxl__)
#undef MATH_CPP11
#endif

//#if defined(_WINDOWS_SOURCE) //|| defined(_LINUX_SOURCE) && defined(CATIAR419) || defined(_IOS_SOURCE) && defined(CATIAR420) || defined(_ANDROID_SOURCE) && defined(CATIAR420) || defined(_DARWIN_SOURCE) && defined(CATIAR420) || defined(_EMSCRIPTEN_SOURCE)
//#define GEO_CPP11
//#endif


// R1Y 21/01/21: Replaced "register" with either "MATHregister" (in the Mathematics framework) or "OLDregister" (in AdvancedMathematics,
//               GeometricObjects, GeometricObjectsCGM, and GeometricOperators) for removing the "register" keyword.
#define MATHregister
#define OLDregister

#endif // CATMathCpp11_h
