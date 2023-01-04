// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2014
// ................................
//
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldSlotNavigatorInterface_H
#define CATCellManifoldSlotNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldExtrusionNavigatorInterface.h"

#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"

// Note: this class has to remain an interface class
// do not introduce any data members in this class

class ExportedByCATGMModelInterfaces CATCellManifoldSlotNavigatorInterface : public CATCellManifoldExtrusionNavigatorInterface
{
public:
  // Constructor
  CATCellManifoldSlotNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldSlotNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATCellManifoldSlotNavigatorInterface* GetAsSlotNavigatorInterface();

  // queries specific to Slot navigators
  virtual HRESULT IsBlind                         (CATBoolean &oIsBlind)    const=0;  
  virtual HRESULT GetSlotWidth                    (double     &oWidth)      const=0; 
  virtual HRESULT GetSlotLength                   (double     &oLength)     const=0; // if round slot, length is the distance between the the two cylinder axis
  virtual HRESULT GetDepth(double & oDepth) const=0;

  virtual void Dump(CATCGMOutput& Output);
protected:
};

#endif
