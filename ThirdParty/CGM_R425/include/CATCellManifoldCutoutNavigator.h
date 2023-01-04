#ifndef CATCellManifoldCutoutNavigator_H
#define CATCellManifoldCutoutNavigator_H

#include "CATPersistentCell.h"

#include "CATCellManifoldCutoutNavigatorInterface.h"
#include "CATCellManifoldGroupNavigator.h"
#include "CATDRepNavigator.h"
#include "CATCutoutManifoldAttribute.h"
#include "ListPOfCATCellManifold.h"
#include "ListPOfCATCellManifoldGroup.h"

class CATLiveBody;
class CATCellManifold;
class CATCellManifoldGroup;

class ExportedByPersistentCell CATCellManifoldCutoutNavigator : public CATCellManifoldCutoutNavigatorInterface
{
public:

  // Constructor
  CATCellManifoldCutoutNavigator();
  CATCellManifoldCutoutNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldCutoutNavigator(CATDRepNavigator * iDrepNavigator, CATCellManifoldGroup * iNetworkGroup);
  CATCellManifoldCutoutNavigator(CATCellManifoldCutoutNavigator *iCutoutNavigator);

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  // Attribute Declaration
  CATCGMDeclareManifoldNavigator(CATCellManifoldCutoutNavigator, CATCellManifoldCutoutNavigatorInterface);
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Destructor
  virtual ~CATCellManifoldCutoutNavigator();

  CATCellManifoldCutoutNavigator * GetAsCutoutNavigator();

  //Interface methods
  virtual HRESULT GetNetworkGroup(CATCellManifoldGroup *& oNetworkGroup) const;

  virtual HRESULT GetAllCellManifolds(ListPOfCATCellManifold & oCellManifolds) const;
  virtual HRESULT GetCutoutSupports(ListPOfCATCellManifold oCutoutSupports[2]) const;

  INLINE virtual CATLiveBody& GetLiveBody() const;

  //-------------------------------------------------
  //   Stream / Unstream 
  //-------------------------------------------------
  void Stream(CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr, CATGeoFactory * iFactory);


protected:

  void Init(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);
  void GetCutoutManifoldAttribute(CATCutoutManifoldAttribute *& oCutoutAttr);

private:

  CATLiveBody * _LiveBody;
  CATCellManifoldGroup * _NetworkGroup;
  CATCutoutManifoldAttribute * _CutoutAttr;
};

INLINE CATLiveBody& CATCellManifoldCutoutNavigator::GetLiveBody() const
{
  return *_LiveBody;
}

// ---------------------------------------
// CATCreateCellManifoldCutoutNavigator
// ---------------------------------------
ExportedByPersistentCell CATCellManifoldCutoutNavigator * CATCreateCellManifoldCutoutNavigator(CATLiveBody * iLiveBody, CATCellManifoldGroup * iNetworkGroup);

#endif
