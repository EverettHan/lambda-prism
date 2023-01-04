#ifndef CATCellManifoldCRTBendNavigator_H
#define CATCellManifoldCRTBendNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldCRTNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATErrorDef.h"
#include "CATMathAxis.h"

class CATWBExpression;
class CATWBFactory;

class ExportedByCATGMModelInterfaces CATCellManifoldCRTBendNavigator : public CATCellManifoldCRTNavigator
{
public:

  // Constructor
  CATCellManifoldCRTBendNavigator(); 

  // Destructor
  virtual ~CATCellManifoldCRTBendNavigator();

  virtual CATCellManifoldCRTBendNavigator* GetAsCRTBendNavigator();

  HRESULT GetNetworkGroup(CATCellManifoldGroup*& oNetworkGroup);

  virtual HRESULT GetBendGroup(CATCellManifoldGroup*& oBendGroup)=0;

  virtual HRESULT GetFirstWallGroupAxis(CATCellManifoldGroup*& oFirstWallGroup, CATMathAxis& oFirstAxis)=0;

  virtual HRESULT GetSecondWallGroupAxis(CATCellManifoldGroup*& oSecondWallGroup, CATMathAxis& oSecondAxis)=0;

  virtual CATWBExpression* CreateAltitudeLaw(CATWBFactory* iFactory)=0;

  virtual CATBoolean WithoutTopology();


protected:
  void Dump(CATCGMOutput& Output);

};


#endif
