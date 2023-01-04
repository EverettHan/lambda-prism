#ifndef CATRatioHVertex_h
#define CATRatioHVertex_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATHVertex.h"
#include "CATHEdge.h"
#include "CATTopDefine.h"
#include "ExportedByCATTopologicalObjects.h"


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATTopologicalObjects IID IID_CATRatioHVertex ;
#else
extern "C" const IID IID_CATRatioHVertex ;
#endif

class ExportedByCATTopologicalObjects CATRatioHVertex : public CATHVertex
{
  CATDeclareInterface;

public:
  
  virtual double GetRatio() const = 0;
  virtual CATOrientation GetUserOrientation() const = 0;
  virtual CATHEdge* GetHEdge() const = 0;
  virtual CATHVertex* GetReferenceHVertex() const = 0;

  //------------------------
  // Do not use
  //------------------------
  virtual HRESULT Set(CATHEdge& iHEdge, const double iRatio, const CATOrientation iUserOrientation, CATHVertex* iRefHVertex) = 0;
  virtual HRESULT SetRatio(const double iRatio) = 0;
  
};
  
CATDeclareHandler(CATRatioHVertex,CATHVertex);

#endif
