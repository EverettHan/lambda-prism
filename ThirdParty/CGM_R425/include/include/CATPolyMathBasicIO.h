// COPYRIGHT DASSAULT SYSTEMES 2007, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyMathBasicIO.h
//
//===================================================================
//
// Usage notes:
//
//===================================================================
//
// Sep 2007 Creation: ndo
//===================================================================
#ifndef CATPolyMathBasicIO_h
#define CATPolyMathBasicIO_h

#include "PolyMathUtils.h"
#include "CATErrorDef.h"

class CATUnicodeString;
class CATPolyMathTriangleSurface;


class ExportedByPolyMathUtils CATPolyMathBasicIO
{

public :

  // Write the Bezier patch at a uniform discretization at the given level.
  static HRESULT WriteInOBJFile (const CATUnicodeString& iFileName, 
                                 const CATPolyMathTriangleSurface& iPatch, const int iLevel = 7);

  // Generic method writing a tessellation in an OBJ file.
  static HRESULT WriteInOBJFile (const CATUnicodeString& iFileName,
                                 const int nbVertices, const float* coords,  
                                 const int nbTriangles, const unsigned int* triangles);

};

#endif
