// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyPointPrinter.h
//
//===================================================================
// December 2009  Creation: NDO
//===================================================================
#ifndef CATPolyPointPrinter_H
#define CATPolyPointPrinter_H

#include "PolyFunctions.h"
#include "CATErrorDef.h"

class CATIPolyPoint;
class CATCGMOutput;


/**
 * Streams a CATIPolyPoint instance to CATCGMOutput.
 */
class ExportedByPolyFunctions CATPolyPointPrinter
{

public:

  CATPolyPointPrinter () {}
  ~CATPolyPointPrinter () {}

public:

  static void Print (const CATIPolyPoint& curve, CATCGMOutput& stream);

};

#endif
