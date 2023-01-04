// -----------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Recognition Primitives Container -- | Generic Level |
// -----------------------------------------------------------------------------------//

#ifndef CATDRepSeedsContainer_H
#define CATDRepSeedsContainer_H

#include "CATGMModelInterfaces.h"
#include "ListPOfCATDRepSeed.h"
#include "CATBoolean.h"

class CATGMLiveFilletPiecesContainer;
class CATGMLiveExtrusionPrimitivesContainer;
class CATGMLiveDraftPiecesContainer;

class ExportedByCATGMModelInterfaces CATDRepSeedsContainer
{
public: 
  CATDRepSeedsContainer(); 
  virtual ~CATDRepSeedsContainer();

  virtual CATGMLiveFilletPiecesContainer * GetAsFilletPiecesContainer();
  virtual CATGMLiveExtrusionPrimitivesContainer * GetAsExtrusionPrimitivesContainer();
  virtual CATGMLiveDraftPiecesContainer * GetAsDraftPiecesContainer();

  void AddRecogPrimitive(CATDRepSeed *iRecogPrimitive);
  void GetRecogPrimitives(ListPOfCATDRepSeed &oRecogPrimitives);
  void DeleteRecogPrimitive(CATDRepSeed *ioRecogPrimitive);

private:
  ListPOfCATDRepSeed _RecogPrimitives;
};


#endif

