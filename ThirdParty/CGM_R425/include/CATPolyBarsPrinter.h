// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBarsPrinter.h
//
//===================================================================
// February 2008  Creation: NDO
//===================================================================
#ifndef CATPolyBarsPrinter_H
#define CATPolyBarsPrinter_H

#include "PolyFunctions.h"
#include "CATErrorDef.h"

class CATPolyBars;
class CATCGMOutput;


/**
 * Streams a CATPolyBars instance to CATCGMOutput.
 */
class ExportedByPolyFunctions CATPolyBarsPrinter
{

public:

  CATPolyBarsPrinter () {}
  ~CATPolyBarsPrinter () {}

public:

  static void Print (const CATPolyBars& bars, CATCGMOutput& stream);

};

#endif
