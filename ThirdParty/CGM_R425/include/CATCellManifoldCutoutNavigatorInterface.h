/* -*-C++-*- */
#ifndef CATCellManifoldCutoutNavigatorInterface_H
#define CATCellManifoldCutoutNavigatorInterface_H
// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2013
// ----------------------------------------------------------------------------------------------//
#include "CATCellManifoldGroupNavigator.h"
#include "CATGMModelInterfaces.h"

class CATLiveBody;
class CATCellManifoldGroup;

class ExportedByCATGMModelInterfaces CATCellManifoldCutoutNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldCutoutNavigatorInterface();

  // Destructor
  virtual ~CATCellManifoldCutoutNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldCutoutNavigatorInterface * GetAsCutoutNavigatorInterface();

  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const = 0;

  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const = 0;
  virtual HRESULT GetCutoutSupports(ListPOfCATCellManifold oCutoutSupports[2]) const = 0;

  virtual CATLiveBody& GetLiveBody() const = 0;

protected:
  void Dump(CATCGMOutput& Output);
};

#endif
