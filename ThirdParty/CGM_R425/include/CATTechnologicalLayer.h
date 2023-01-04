#ifndef CATTechnologicalLayer_h
#define CATTechnologicalLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"


#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATTechnologicalLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATTechnologicalLayer, CATCellManifoldGroupLayer);

  CATTechnologicalLayer(); // Default constructr is mandatory
  virtual ~CATTechnologicalLayer();

  virtual CATBoolean IsHierarchichal()=0;
  virtual CATBoolean IsContextual()=0;

  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

};


#endif

