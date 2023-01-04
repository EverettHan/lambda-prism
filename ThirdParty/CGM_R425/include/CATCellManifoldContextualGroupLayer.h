#ifndef CATCellManifoldContextualGroupLayer_h
#define CATCellManifoldContextualGroupLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATMathPoint.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATCellManifoldContextualGroupLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldContextualGroupLayer,CATCellManifoldGroupLayer);

  CATCellManifoldContextualGroupLayer(); // Default constructr is mandatory
  virtual ~CATCellManifoldContextualGroupLayer();

  virtual CATBoolean IsHierarchichal();
   virtual CATBoolean IsContextual();

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

private:
};
#endif

