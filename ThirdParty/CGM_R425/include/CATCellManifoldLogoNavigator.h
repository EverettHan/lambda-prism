// ----------------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2015
// ................................
//
// JNF: Feature recognition -- Logo Navigator Implementation -- | Generic navigator level |
// ----------------------------------------------------------------------------------------------//

#ifndef CATCellManifoldLogoNavigator_H
#define CATCellManifoldLogoNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldLogoNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATLogoManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;

class ExportedByPersistentCell CATCellManifoldLogoNavigator : public CATCellManifoldLogoNavigatorInterface
{
public:

  // Constructor
  CATCellManifoldLogoNavigator(); 
  CATCellManifoldLogoNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup); 
  CATCellManifoldLogoNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup); 
  CATCellManifoldLogoNavigator(CATCellManifoldLogoNavigator *iLogoNavigator); 

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATCellManifoldLogoNavigator, CATCellManifoldLogoNavigatorInterface);
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldLogoNavigator();

  CATCellManifoldLogoNavigator * GetAsLogoNavigator();

  //Interface methods
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetDeclarativeType(CATDeclarativeType &oType) const;
  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
  virtual HRESULT GetSize(double & oSize) const;
  virtual HRESULT GetHeight(double & oHeight) const;

  virtual CATBoolean BelongsToLogo(CATCellManifold * iCM) const;

  INLINE virtual CATLiveBody& GetLiveBody() const;

  //-------------------------------------------------
  //   Stream / Unstream 
  //-------------------------------------------------

  // @nocgmitf
  //-------------------------------------------------------------------------------------------------
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);


protected:

  void Init(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  void GetLogoManifoldAttribute(CATLogoManifoldAttribute *& oLogoAttr);

private:

  CATLiveBody * _LiveBody;
  CATCellManifoldGroup * _NetworkGroup;
  CATLogoManifoldAttribute * _LogoAttr;
};

INLINE CATLiveBody& CATCellManifoldLogoNavigator::GetLiveBody() const
{
  return *_LiveBody;
}

// ---------------------------------------
// CATCreateCellManifoldLogoNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldLogoNavigator * CATCreateCellManifoldLogoNavigator(CATLiveBody          * iLiveBody,
																									 CATCellManifoldGroup * iNetworkGroup); 

#endif
