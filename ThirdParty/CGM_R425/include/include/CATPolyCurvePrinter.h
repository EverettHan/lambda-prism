// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyCurvePrinter.h
//
//===================================================================
// September 2008  Creation: NDO
//===================================================================
#ifndef CATPolyCurvePrinter_H
#define CATPolyCurvePrinter_H

#include "PolyFunctions.h"
#include "CATErrorDef.h"

class CATIPolyCurve;
class CATCGMOutput;


/**
 * Streams a CATIPolyCurve instance to CATCGMOutput.
 */
class ExportedByPolyFunctions CATPolyCurvePrinter
{

public:

  CATPolyCurvePrinter () {}
  ~CATPolyCurvePrinter () {}

public:

  static void Print (const CATIPolyCurve& curve, CATCGMOutput& stream);

};

#endif
