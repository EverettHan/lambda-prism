// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Primitives Container -- | Data Family Level |
// --------------------------------------------------------------------------------------//

#ifndef CATGMLiveExtrusionPrimitivesContainer_H
#define CATGMLiveExtrusionPrimitivesContainer_H

#include "CATGMModelInterfaces.h"
#include "ListPOfCATGMLiveExtrusionPrimitive.h"
#include "CATDRepSeedsContainer.h"

class ExportedByCATGMModelInterfaces CATGMLiveExtrusionPrimitivesContainer: public CATDRepSeedsContainer
{
public: 
  CATGMLiveExtrusionPrimitivesContainer(); 
  virtual ~CATGMLiveExtrusionPrimitivesContainer();

  void AddExtrusionPrimitive(CATGMLiveExtrusionPrimitive *iExtrusionPrimitive);
  void RmvExtrusionPrimitive(CATGMLiveExtrusionPrimitive *iExtrusionPrimitive);
  void GetExtrusionPrimitives(ListPOfCATGMLiveExtrusionPrimitive &oExtrusionPrimitives);
  CATBoolean GetRecogIsDone(HRESULT& oHR);
  void       SetRecogIsDone(HRESULT  iHR);

private:
  ListPOfCATGMLiveExtrusionPrimitive _ExtrusionPrimitives;
  CATBoolean _RecogDone;
  HRESULT    _HR_Recog;
};


#endif

