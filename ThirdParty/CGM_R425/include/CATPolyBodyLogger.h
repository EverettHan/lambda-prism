// COPYRIGHT DASSAULT SYSTEMES 2015, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyLogger.h
// Internal use only, don't use
//===================================================================
//
// November 2015  Creation: JXO
//===================================================================
#ifndef CATPolyBodyLogger_H
#define CATPolyBodyLogger_H

#include "PolyMODEL.h"
#include "CATPolyBody.h"

/** Declaration of the function called inside Constructor */
typedef void CATPolyBodyConstructorLoggerDec(const CATPolyBody & iBody);
/** Declaration of the function called inside Release */
typedef void CATPolyBodyReleaseLoggerDec(const CATPolyBody & iBody, const int referencecount);

/**
 * Internal use only, don't use
 */
class ExportedByPolyMODEL CATPolyBodyLogger
{
public:
  static CATPolyBodyConstructorLoggerDec * s_Constructor;
  static CATPolyBodyReleaseLoggerDec * s_Release;

private:
  CATPolyBodyLogger();
  ~CATPolyBodyLogger();
};

#endif
