#ifndef CATGMLiveGroupFollower_H
#define CATGMLiveGroupFollower_H


#include "CATGMLiveContextualFeatureFollower.h"
#include "ListPOfCATCellManifold.h"
#include "PersistentCell.h"

class CATCellManifoldGroup;
class CATCellManifoldGroupNavigator;
class CATGeoFactory;
class CATCGMStream;
class CATCellManifoldGroupLayer;
class CATManifoldAttribute;

class ExportedByPersistentCell CATGMLiveGroupFollower : public CATGMLiveContextualFeatureFollower 
{
protected:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveGroupFollower(CATCellManifoldGroup           &iNetworkGroup,
    CATPersistentBody              &iInitialBodyWithGroup,
    CATPersistentCellInfra         &iInfra);

  //Copy constructor
  CATGMLiveGroupFollower(CATGMLiveGroupFollower & iFollower);

public:
  //FOR UNSTREAM ONLY
CATGMLiveGroupFollower(CATPersistentCellInfra         &iInfra);
  ~CATGMLiveGroupFollower();

  INLINE CATGMLiveGroupFollower *GetAsGroupFollower();
  INLINE CATCellManifoldGroup * GetNetworkCMGroup() const;

  virtual void GetCellManifoldsInInputBody(ListPOfCATCellManifold &iInputCellManifolds) const =0;

   void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
   void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
   virtual void StreamCATCellManifoldNavigator(CATCellManifoldGroupNavigator *_Navigator, CATCGMStream& ioStr, CATGeoFactory * iFactory) const =0;
   virtual CATCellManifoldGroupNavigator *UnStreamCATCellManifoldNavigator(CATCGMStream& ioStr, CATGeoFactory * iFactory)=0;

protected:
  INLINE void SetNetworkCMGroup(CATCellManifoldGroup *iNetWorkGroup);//FOR UNSTREAM ONLY
  INLINE CATCellManifoldGroupNavigator *GetNavigator() const;
  INLINE void SetNavigator(CATCellManifoldGroupNavigator * iOffsetNavigator);
  virtual CATCellManifoldGroupLayer *GetLayer() const =0 ;

private:
  CATCellManifoldGroup     *_NetworkGroupToFollow;
  CATCellManifoldGroupNavigator * _Navigator;
  CATBoolean               _NavigatorOwner;

  // Pour le debug
  int _DebugTag;
};

INLINE CATCellManifoldGroup* CATGMLiveGroupFollower::GetNetworkCMGroup() const
{
  return _NetworkGroupToFollow;
}

INLINE CATCellManifoldGroupNavigator *CATGMLiveGroupFollower::GetNavigator() const
{
  return _Navigator;
}

INLINE void CATGMLiveGroupFollower::SetNetworkCMGroup(CATCellManifoldGroup *iNetWorkGroup) //FOR OLD UNSTREAM ONLY
{
  if(!_NetworkGroupToFollow)
    _NetworkGroupToFollow=iNetWorkGroup;
}

INLINE void CATGMLiveGroupFollower::SetNavigator(CATCellManifoldGroupNavigator * iGroupNavigator)
{
  _Navigator=iGroupNavigator;
}

INLINE CATGMLiveGroupFollower *CATGMLiveGroupFollower::GetAsGroupFollower()
{
  return this;
}
#endif

