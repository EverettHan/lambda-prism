#ifndef CATExtTopGeometricalMapping_H
#define CATExtTopGeometricalMapping_H

#include "ExportedByCATTopologicalObjects.h"
#include "CATExtTopOperator.h"
#include "CATIACGMLevel.h"

class  ExportedByCATTopologicalObjects CATExtTopGeometricalMapping : public CATExtTopOperator
{
public:
  CATExtTopGeometricalMapping();
  ~CATExtTopGeometricalMapping();

  CATCGMNewClassArrayDeclare; // Pool allocation
  
protected:
  // Polyhedral body Management 
  virtual CATBoolean Is_PolyInputs_Allowed();
  //virtual CATBoolean Is_MixedPolyExactInputs_Allowed();
  //virtual int RunPolyOperator();
};

#endif 
