// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2015
// ................................
//
// JNF: Feature recognition -- Logo Navigator Interface -- | Generic navigator level |
// ----------------------------------------------------------------------------------------------//


#ifndef CATCellManifoldLogoNavigatorInterface_H
#define CATCellManifoldLogoNavigatorInterface_H

#include "CATGMModelInterfaces.h"
#include "CATCellManifoldGroupNavigator.h"
#include "ListPOfCATCellManifold.h" 
#include "CATBoolean.h"
#include "CATMathConstant.h"
#include "CATErrorDef.h"

class CATCellManifoldLogoNavigator;
class CATCellManifoldGroup;
class CATCellManifold;


class ExportedByCATGMModelInterfaces CATCellManifoldLogoNavigatorInterface : public CATCellManifoldGroupNavigator
{
public:

  // Constructor
  CATCellManifoldLogoNavigatorInterface(); 

  // Destructor
  virtual ~CATCellManifoldLogoNavigatorInterface();

  //------------------------
  // Surcharge du new/delete
  //------------------------
  CATCGMNewClassArrayDeclare;      // Pool allocation

  CATCellManifoldLogoNavigatorInterface * GetAsLogoNavigatorInterface();

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const = 0;

  // Returns Logo specifications
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const = 0;
  
  // Returns all Logo CellManifolds
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const = 0;

  // HRESULT is S_FALSE if Size and Height are not available (because not supported by StreamVersion
  // of Logo attribute)
  virtual HRESULT GetSize(double & oSize) const = 0;
  virtual HRESULT GetHeight(double & oHeight) const = 0;

  // Checks if CellManifold belongs to Logo: 0 = No, 1 = Yes 
  virtual CATBoolean BelongsToLogo(CATCellManifold * iCM) const = 0;

  virtual CATLiveBody& GetLiveBody() const = 0;

  // Logo parameters
  //virtual HRESULT GetParameters() const;
protected:
  void Dump(CATCGMOutput& Output);
};

#endif
