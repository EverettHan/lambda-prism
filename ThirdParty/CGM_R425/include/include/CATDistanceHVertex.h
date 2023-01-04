#ifndef CATDistanceHVertex_h
#define CATDistanceHVertex_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATHVertex.h"
#include "CATMathDef.h"
#include "CATTopDefine.h"
#include "CATHEdge.h"
#include "CATHVertex.h"

#include "CATGMModelInterfaces.h"
#include "ExportedByCATTopologicalObjects.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTopologicalObjects IID IID_CATDistanceHVertex ;
#else
extern "C" const IID IID_CATDistanceHVertex ;
#endif

class ExportedByCATTopologicalObjects CATDistanceHVertex : public CATHVertex
{
  CATDeclareInterface;

public:

  virtual CATLength GetLength() const = 0;
  virtual CATOrientation GetUserOrientation() const = 0;
  virtual CATHEdge* GetHEdge() const = 0;
  virtual CATHVertex* GetReferenceHVertex() const = 0;

  //------------------------
  // Do not use
  //------------------------
  virtual HRESULT Set(CATHEdge& iHEdge, const double iRatio, const CATOrientation iUserOrientation, CATHVertex* iRefHVertex) = 0;
  virtual HRESULT SetLength(const CATLength iLength) = 0;

};
  
CATDeclareHandler(CATDistanceHVertex,CATHVertex);

#endif
