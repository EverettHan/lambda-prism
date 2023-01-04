#ifndef CATCellManifoldGroupLayer_h
#define CATCellManifoldGroupLayer_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATCGMStreamAttribute.h"
#include "CATGMModelInterfaces.h"
#include "ListPOfCATCellManifoldGroupNavigator.h"
#include "CATLiveBody.h"

class ExportedByCATGMModelInterfaces CATCellManifoldGroupLayer : public CATCGMStreamAttribute
{
public:
  CATCGMDeclareAttribute (CATCellManifoldGroupLayer,CATCGMStreamAttribute);

  CATCellManifoldGroupLayer(); 
  virtual ~CATCellManifoldGroupLayer();

  virtual CATBoolean IsHierarchichal()=0;
  virtual CATBoolean IsContextual()=0;

  virtual CATBoolean GetSplitterMode();

  //VB7 - 06 - 30 - 2016 - for SHM/CRT layers
  //
  //
  //
  virtual CATBoolean AllowLostOfTypeIfBodyDimensionKept();

  //
  //
  //
  virtual CATBoolean AllowDegeneratedRepWithContexts();


  //For CellManifoldGroup Duplication
  virtual CATBoolean AllowDuplication();

  virtual HRESULT IsCellManifoldGroupMergeAllowed(CATBoolean iWithCellManifoldBelongingToAnOtherGroup);
  
  //VB7 - 04 - 25 - 2017 - for SHM layers
  virtual CATBoolean AllowContextFollowingThroughVertices();

  //VB7 - 05 - 02 - 2017 - thread layer
  virtual CATBoolean AllowGroupContextUpdate();

  void DumpNoEndLine(CATCGMOutput& iWhereToWrite) const; 
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  virtual HRESULT CreateGroupNavigators(CATLiveBody* iLiveBody, CATTopData& iTopData, ListPOfCATCellManifoldGroupNavigator &oNavigatorList);
 
};
#endif

