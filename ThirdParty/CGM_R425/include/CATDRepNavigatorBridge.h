#ifndef CATDRepNavigatorBridge_H
#define CATDRepNavigatorBridge_H

#include "CATGMModelInterfaces.h"
#include "ListPOfCATCell.h"
#include "CATTopData.h"
#include "CATErrorDef.h"

class CATEdge;
class CATVertex;
class CATLiveBody;

class ExportedByCATGMModelInterfaces CATDRepNavigatorBridge
{
public : 
  CATDRepNavigatorBridge();
  virtual ~CATDRepNavigatorBridge();

  virtual HRESULT GetRepresentative(const ListPOfCATCell & iPacketEdges, CATEdge *& oRepresentative)=0;
  virtual HRESULT GetRepresentative(CATEdge * iEdge, CATEdge *& oRepresentative)=0;
  virtual HRESULT GetPacketExtremities(CATEdge * iEdge, CATVertex *& oStartVertex, CATVertex *& oEndVertex)=0;
  virtual HRESULT GetPacket(CATEdge * iEdge, ListPOfCATCell & oPacketEdges)=0;

};

ExportedByCATGMModelInterfaces CATDRepNavigatorBridge *CATCreateDRepNavigatorBridge(const CATTopData &iData, CATLiveBody* iLiveBody);


#endif
