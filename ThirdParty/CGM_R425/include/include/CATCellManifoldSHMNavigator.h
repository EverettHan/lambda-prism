#ifndef CATCellManifoldSHMNavigator_H
#define CATCellManifoldSHMNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "ListPOfCATEdge.h"

class ExportedByCATGMModelInterfaces CATCellManifoldSHMNavigator : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldSHMNavigator();

  // Destructor
  virtual ~CATCellManifoldSHMNavigator();

  HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual CATCellManifoldSHMNavigator * GetAsSHMNavigator();

  virtual HRESULT GetTopBottom(CATLISTP(CATCellManifold) & oTopCMList, CATLISTP(CATCellManifold) & oBottomCMList) = 0;
  virtual HRESULT GetLateral(CATLISTP(CATCellManifold) & oLateralCMList) = 0;
  virtual CATBoolean IsReferenceWall();

  // list des cellManifold solidaires des faces top/bottom
  virtual HRESULT GetTopBottomAnchorFaces(CATLISTP(CATCellManifold) & oListOfCellManifold);
  
  virtual HRESULT GetLateralLonesomeEdges(CATLISTP(CATEdge) & oLateralEdgesList)=0;
  virtual HRESULT GetLinkedEdges(CATEdge* &ioTopEdge, CATEdge* &ioBottomEdge, CATEdge* &ioLateralBorderEdge1, CATEdge* &ioLateralBorderEdge2)=0;

protected:
  void Dump(CATCGMOutput& Output);

};


#endif
