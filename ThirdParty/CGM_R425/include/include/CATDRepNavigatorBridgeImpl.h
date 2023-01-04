#ifndef CATDRepNavigatorBridgeImpl_H
#define CATDRepNavigatorBridgeImpl_H

#include "CATPersistentCell.h"
#include "CATDRepNavigatorBridge.h"

class CATDRepNavigator;

class ExportedByPersistentCell CATDRepNavigatorBridgeImpl : public CATDRepNavigatorBridge
{
public : 
  CATDRepNavigatorBridgeImpl(const CATTopData &iData, CATLiveBody* iLiveBody);
  virtual ~CATDRepNavigatorBridgeImpl();

  virtual HRESULT GetRepresentative(const ListPOfCATCell & iPacketEdges, CATEdge *& oRepresentative);
  virtual HRESULT GetRepresentative(CATEdge * iEdge, CATEdge *& oRepresentative);
  virtual HRESULT GetPacketExtremities(CATEdge * iEdge, CATVertex *& oStartVertex, CATVertex *& oEndVertex);
  virtual HRESULT GetPacket(CATEdge * iEdge, ListPOfCATCell & oPacketEdges);

private : 
  CATDRepNavigator * _CATDRepNavigator;

};


#endif
