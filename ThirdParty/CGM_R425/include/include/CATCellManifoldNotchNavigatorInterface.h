// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2016
// ................................
//
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldNotchNavigatorInterface_H
#define CATCellManifoldNotchNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldExtrusionNavigatorInterface.h"

#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"

// Note: this class has to remain an interface class
// do not introduce any data members in this class

class ExportedByCATGMModelInterfaces CATCellManifoldNotchNavigatorInterface : public CATCellManifoldExtrusionNavigatorInterface
{
public:
  typedef enum 
  {
    UnknownType    = 0,
    PlanarPerpendicular         = 1,
    Rounded             = 2
  }
  EndWallType;

  // Constructor
  CATCellManifoldNotchNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldNotchNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATCellManifoldNotchNavigatorInterface* GetAsNotchNavigatorInterface();

  // queries specific to Notch navigators
  virtual HRESULT IsBlind(CATBoolean &oIsBlind) const=0;  
  //virtual HRESULT HasOpenWall(CATBoolean &oHasOpenWall) const=0;  
    virtual HRESULT GetEndWallType(EndWallType & oType) const=0;
    virtual HRESULT GetLength(double & oLength) const=0;
    virtual HRESULT GetWidth(double & oWidth) const=0;

  virtual void Dump(CATCGMOutput& Output);
protected:
};

#endif
