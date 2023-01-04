#ifndef CATCellManifoldCRTGlueNavigator_H
#define CATCellManifoldCRTGlueNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathAxis.h"
#include "CATMathLine.h"
#include "CATMathConstant.h"

class ExportedByCATGMModelInterfaces CATCellManifoldCRTGlueNavigator : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldCRTGlueNavigator(); 

  // Destructor
  virtual ~CATCellManifoldCRTGlueNavigator();

  virtual CATCellManifoldCRTGlueNavigator* GetAsCRTGlueNavigator();

  virtual HRESULT GetGlueGroup(CATCellManifoldGroup*& oGlueGroup)=0;

  virtual HRESULT GetSourceWallGroupAxis(CATCellManifoldGroup*& oSourceWallGroup, CATMathAxis& oSourceAxis)=0;

  virtual HRESULT GetTargetWallGroupAxis(CATCellManifoldGroup*& oTargetWallGroup, CATMathAxis& oTargetAxis)=0;

  virtual CATBoolean HasOptionalAngle(CATMathLine& oLine1, CATMathLine& oLine2, CATAngle& oAngle)=0;

  virtual CATBoolean HasOptionalDistance1(CATMathLine& oLine1, CATMathLine& oLine2, double& oDistance)=0;

  virtual CATBoolean HasOptionalDistance2(CATMathLine& oLine1, CATMathLine& oLine2, double& oDistance)=0;

protected:
  void Dump(CATCGMOutput& Output);

};


#endif
