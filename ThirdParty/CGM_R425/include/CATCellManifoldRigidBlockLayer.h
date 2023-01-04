#ifndef CATCellManifoldRigidBlockLayer_h
#define CATCellManifoldRigidBlockLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCellManifoldGroupLayer.h"
#include "CATMathPoint.h"

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATCellManifoldRigidBlockLayer : public CATCellManifoldGroupLayer
{
public:
  CATCGMDeclareAttribute (CATCellManifoldRigidBlockLayer,CATCellManifoldGroupLayer);

  CATCellManifoldRigidBlockLayer(); // Default constructr is mandatory
  virtual ~CATCellManifoldRigidBlockLayer();

  virtual CATBoolean IsHierarchichal();
  virtual CATBoolean IsContextual();
  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

private:
};
#endif

