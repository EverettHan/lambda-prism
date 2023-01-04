#ifndef CATDRepGroupThreadLayer_h
#define CATDRepGroupThreadLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATTechnologicalLayer.h"
#include "CATMathPoint.h"

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATDRepGroupThreadLayer : public CATTechnologicalLayer
{
public:
  CATCGMDeclareAttribute (CATDRepGroupThreadLayer, CATTechnologicalLayer);

  CATDRepGroupThreadLayer(); // Default constructr is mandatory
  virtual ~CATDRepGroupThreadLayer();

  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();

  //For CellManifoldGroup Duplication - VB7 W28-2016
  virtual CATBoolean AllowDuplication();

  //For thread on pattern - VB7 W18-2017
  virtual CATBoolean AllowGroupContextUpdate();

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

private:
};


#endif

