// COPYRIGHT DASSAULT SYSTEMES 2012, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyDiagnosisPrinter.h
//
//===================================================================
// January 2012  Creation: NDO
//===================================================================
#ifndef CATPolyBodyDiagnosisPrinter_h
#define CATPolyBodyDiagnosisPrinter_h

#include "PolyBodyTools.h"
#include "CATPolyBodyDiagnosis.h"
#include "CATPolyBodyGeoDiagnosis.h"

// System
#include "CATErrorDef.h"
#include "CATUnicodeString.h"


class CATPolyBody;
class CATCGMOutput;


/**
 * Streams a CATPolyBodyDiagnosis instance to CATCGMOutput.
 */
class ExportedByPolyBodyTools CATPolyBodyDiagnosisPrinter
{

public:

  CATPolyBodyDiagnosisPrinter () {}
  ~CATPolyBodyDiagnosisPrinter () {}

public:

  /**
   * Prints iPolyBody stats, and CATPolyBodyDiagnosis errors
   */
  static void Print (const CATPolyBody& iPolyBody, CATCGMOutput& stream);

  /**
  * Prints all CATPolyBodyDiagnosis and CATPolyBodyGeoDiagnosis errors
  */
  static void PrintAllErrors(const CATPolyBody& iPolyBody, CATCGMOutput& stream);

  static CATUnicodeString GetStringFromError(CATPolyBodyDiagnosis::Error error);
  static CATUnicodeString GetStringFromErrors(int errors);
  static CATUnicodeString GetStringFromGeoError(CATPolyBodyGeoDiagnosis::Error error);
  static CATUnicodeString GetStringFromGeoErrors(int errors);
  static CATUnicodeString ListOfAllErrors(const CATPolyBody& iPolyBody);
};

#endif
