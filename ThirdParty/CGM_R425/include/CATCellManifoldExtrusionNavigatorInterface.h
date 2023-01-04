// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2012
// ................................
//
// ST5: Feature recognition -- Extrusion Navigator Interface -- | Generic navigator level |
// ----------------------------------------------------------------------------------------------//


#ifndef CATCellManifoldExtrusionNavigatorInterface_H
#define CATCellManifoldExtrusionNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h" 
#include "CATExtrusionType.h"
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"


class CATCellManifoldExtrusionNavigator;
class CATCellManifoldGroup;
class CATCellManifold;
class CATMathVector;

// Note: this class has to remain an interface class
// do not introduce any data members in this class

class ExportedByCATGMModelInterfaces CATCellManifoldExtrusionNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:
  // Constructor
  CATCellManifoldExtrusionNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldExtrusionNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldExtrusionNavigatorInterface * GetAsExtrusionNavigatorInterface();

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const=0;

  // Returns Extrusion specifications
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const=0;
  virtual HRESULT GetExtrusionType(CATExtrusionType & oType) const=0;
  virtual HRESULT GetExtrusionDirection(CATMathVector & oDir) const=0; 
  virtual HRESULT GetExtrusionFaces(ListPOfCATCellManifold & oCMFaces) const=0; 
  virtual HRESULT GetExtrusionSupports(ListPOfCATCellManifold & oCMFaces) const=0; 
  virtual HRESULT GetExtrusionEnds(ListPOfCATCellManifold & oCMFaces) const=0;
  virtual HRESULT GetExtrusionExits(ListPOfCATCellManifold & oCMFaces) const=0;

  virtual HRESULT GetExtrusionSupportDeco(ListPOfCATCellManifold & oCMFaces) const=0; 
  virtual HRESULT GetExtrusionEndDeco(ListPOfCATCellManifold & oCMFaces) const=0;
  virtual HRESULT GetDepth(double & oDepth) const=0;
  
  // Returns all Extrusion CellManifolds
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const=0;

  // Right now this data makes sense only for holes and pads and pockets
  // The rest of the features will return an empty list
  virtual HRESULT GetTransitionFaces(ListPOfCATCellManifold & oCMFaces) const=0;

  // Checks if CellManifold belongs to Extrusion: 0=No, 1=Yes 
  virtual CATBoolean BelongsToExtrusion(CATCellManifold * iCM) const=0;

  virtual CATLiveBody& GetLiveBody() const = 0;

  virtual void Dump(CATCGMOutput& Output);
protected:
};


#endif
