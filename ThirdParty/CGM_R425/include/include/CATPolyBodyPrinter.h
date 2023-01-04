//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2007
//=============================================================================
//
// CATPolyBodyPrinter
//
//=============================================================================
// 2007-07-19   BPG: New.
//=============================================================================
#ifndef CATPolyBodyPrinter_H
#define CATPolyBodyPrinter_H

#include "CATBoolean.h"
#include "CATErrorDef.h"

#include "CATPolyMacroTopologyFwd.h"
#include "PolyMODEL.h"

//
class CATCGMOutput;


/**
 * Streams a CATPolyBody instance to CATCGMOutput.
 */
class ExportedByPolyMODEL CATPolyBodyPrinter
{
public:
  CATPolyBodyPrinter();
  ~CATPolyBodyPrinter();

public:
  inline void SetOutputStream(CATCGMOutput &iOutputStream);

public:
  inline void DoPrintFaces(CATBoolean iValue);
  inline void DoPrintEdges(CATBoolean iValue);
  inline void DoPrintVertices(CATBoolean iValue);

  inline void DoPrintSurfaces(CATBoolean iValue);
  inline void DoPrintCurves(CATBoolean iValue);
  inline void DoPrintPoints(CATBoolean iValue);

  inline void DoPrintPointers(CATBoolean iValue);

public:
  HRESULT Print(CATPolyBody &iBody);

protected:
  CATCGMOutput *_OutputStream;

  CATBoolean _PrintFacesP;
  CATBoolean _PrintEdgesP;
  CATBoolean _PrintVerticesP;

  CATBoolean _PrintSurfacesP;
  CATBoolean _PrintCurvesP;
  CATBoolean _PrintPointsP;

  CATBoolean _PrintPointers;
};

// ----------------------------------------------------------------------------

inline void
CATPolyBodyPrinter::SetOutputStream(CATCGMOutput &iOutputStream)
{
  _OutputStream = & iOutputStream;
}

//

inline void
CATPolyBodyPrinter::DoPrintFaces(CATBoolean iValue)
{
  _PrintFacesP = iValue;
}

inline void
CATPolyBodyPrinter::DoPrintEdges(CATBoolean iValue)
{
  _PrintEdgesP = iValue;
}

inline void
CATPolyBodyPrinter::DoPrintVertices(CATBoolean iValue)
{
  _PrintVerticesP = iValue;
}

inline void
CATPolyBodyPrinter::DoPrintSurfaces(CATBoolean iValue)
{
  _PrintSurfacesP = iValue;
}

inline void
CATPolyBodyPrinter::DoPrintCurves(CATBoolean iValue)
{
  _PrintCurvesP = iValue;
}

inline void CATPolyBodyPrinter::DoPrintPoints(CATBoolean iValue)
{
  _PrintPointsP=iValue;
}

inline void CATPolyBodyPrinter::DoPrintPointers(CATBoolean iValue)
{
  _PrintPointers=iValue;
}

#endif // !CATPolyBodyPrinter_H
