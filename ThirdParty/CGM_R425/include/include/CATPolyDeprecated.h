// COPYRIGHT DASSAULT SYSTEMES 2016, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyDeprecated.h
//
//===================================================================
//
// Usage notes: Macros for deprecated methods.
// For example:
// POLY_DEPRECATED("Bad call!", HRESULT MyDeprecatedMethod());
//
//===================================================================
//
// February 2016  Creation: JXO
//===================================================================


#ifndef CATPolyDeprecated_H
#define CATPolyDeprecated_H

#if defined(_MSC_VER) && (_MSC_VER >= 1500)
# define POLY_DEPRECATED(msg, decl) __declspec(deprecated(msg)) decl
#elif defined (__GNUC__)
/* CPT - # define POLY_DEPRECATED(msg, decl) decl __attribute__ ((deprecated)) */
#define POLY_DEPRECATED(msg, decl) decl
#else
# define POLY_DEPRECATED(msg, decl) decl
#endif

#endif

