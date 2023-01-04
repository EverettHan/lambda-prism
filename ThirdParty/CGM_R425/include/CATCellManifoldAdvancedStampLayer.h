#ifndef CATCellManifoldAdvancedStampLayer_h
#define CATCellManifoldAdvancedStampLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2017

#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATGMModelInterfaces.h"

class ExportedByCATGMModelInterfaces CATCellManifoldAdvancedStampLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldAdvancedStampLayer,CATCellManifoldGroupLayer);

  CATCellManifoldAdvancedStampLayer(); // Default constructr is mandatory
  virtual ~CATCellManifoldAdvancedStampLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

private:
};
#endif

