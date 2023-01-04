#ifndef CATCellManifoldCRTNavigator_H
#define CATCellManifoldCRTNavigator_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h"
#include "CATMathDef.h"
#include "CATErrorDef.h"

class ExportedByCATGMModelInterfaces CATCellManifoldCRTNavigator : public CATCellManifoldGroupNavigator
{
public:

  CATCellManifoldCRTNavigator(); 

  virtual ~CATCellManifoldCRTNavigator();

  virtual CATCellManifoldCRTNavigator* GetAsCRTNavigator();

  virtual void GetTopBottomRep(ListPOfCATCellManifold oRep[2]) const;

  virtual CATPositiveLength GetThickness() const; 

};


#endif
