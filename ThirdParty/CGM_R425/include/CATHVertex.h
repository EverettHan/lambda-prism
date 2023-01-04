#ifndef CATHVertex_h
#define CATHVertex_h

// COPYRIGHT DASSAULT SYSTEMES  2012

#include "CATHGeometry.h"

#include "CATGMModelInterfaces.h"


#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATHVertex ;
#else
extern "C" const IID IID_CATHVertex ;
#endif

class ExportedByCATGMModelInterfaces CATHVertex : public CATHGeometry
{
  CATDeclareInterface;

public:

  virtual HRESULT GetPosition(CATMathPoint &oPosition) const = 0;
  virtual CATBoolean HasSimilarTypeAndContext(CATHVertex* iHVertex) const = 0;
  virtual void SetPosition(const CATMathPoint &iPosition) = 0;

};
  
CATDeclareHandler(CATHVertex,CATHGeometry);

#endif
