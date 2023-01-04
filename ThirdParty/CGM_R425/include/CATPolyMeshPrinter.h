// COPYRIGHT DASSAULT SYSTEMES 2008, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMeshPrinter.h
//
//===================================================================
// February 2008  Creation: NDO
//===================================================================
#ifndef CATPolyMeshPrinter_H
#define CATPolyMeshPrinter_H

#include "PolyFunctions.h"
#include "CATErrorDef.h"

class CATIPolyMesh;
class CATCGMOutput;


/**
 * Streams a CATIPolyMesh instance to CATCGMOutput.
 */
class ExportedByPolyFunctions CATPolyMeshPrinter
{

public:

  CATPolyMeshPrinter () {}
  ~CATPolyMeshPrinter () {}

public:

  static void Print (const CATIPolyMesh& mesh, CATCGMOutput& stream);

};

#endif
