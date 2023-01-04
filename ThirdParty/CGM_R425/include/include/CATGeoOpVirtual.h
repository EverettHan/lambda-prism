#ifndef CATGeoOpVirtual_h
#define CATGeoOpVirtual_h

#include "CATGeoOpCpp11.h" // define whether or not we're using C++11

// --------------------------------------------------------------
// Some useful macros to use C++11 keywords
// --------------------------------------------------------------

#ifdef GEO_CPP11

#define CATGEOOverride override
#define CATGEOFinal final

#else

#define CATGEOOverride
#define CATGEOFinal

#endif

#endif // CATGeoOpVirtual_h
