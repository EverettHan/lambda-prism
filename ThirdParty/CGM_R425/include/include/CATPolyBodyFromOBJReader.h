// COPYRIGHT DASSAULT SYSTEMES 2011, ALL RIGHTS RESERVED.
//===================================================================
//
// CATPolyBodyFromOBJReader.h
//
//===================================================================
// June 2011 Creation: ndo
//===================================================================
#ifndef CATPolyBodyFromOBJReader_h
#define CATPolyBodyFromOBJReader_h

#include "PolyBodyTools.h"
#include "CATErrorDef.h" // HRESULT.

class CATUnicodeString;
class CATPolyBody;


/**
* A service that reads an OBJ file and creates a CATPolyBody.
*/
class ExportedByPolyBodyTools CATPolyBodyFromOBJReader
{

public:

  /**
   * Reads an OBJ file and create a CATPolyBody with the data.
   * @param iFileName
   *   The name of the input file.
   * @param oPolyBody
   *   The output CATPolyBody constructed from the data in the OBJ file. 
   *   The CATPolyBody must be released.
   */
  static HRESULT Read (const CATUnicodeString& iFileName, CATPolyBody*& oPolyBody);

private:

};

#endif
