#ifndef CATGMAdvancedStampFollower_H
#define CATGMAdvancedStampFollower_H

#include "CATGMLiveGroupFollower.h"

class CATCellManifoldGroup;
class CATlsoAdvancedStampInputData;
class CATAdvancedStampNavigator;
class CATPersistentCellInfra;

class ExportedByPersistentCell CATGMAdvancedStampFollower : public CATGMLiveGroupFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMAdvancedStampFollower(
    CATCellManifoldGroup           &iNetworkGroup,
    CATPersistentBody              &iInitialBodyWithGroup,
    CATPersistentCellInfra         &iInfra);

  //Copy constructor
  CATGMAdvancedStampFollower(CATGMAdvancedStampFollower & iFollower);


  //FOR UNSTREAM ONLY
  CATGMAdvancedStampFollower(CATPersistentCellInfra         &iInfra);
  ~CATGMAdvancedStampFollower();

  virtual void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const;
  virtual void GetCellManifoldsInInputBody(ListPOfCATCellManifold &iInputCellManifolds) const;

  CATlsoAdvancedStampInputData * GenerateTargetAdvancedStampInputData(CATPersistentCellInfra & iInfra, int iNumOperatorID);

  CATAdvancedStampNavigator * GetAdvancedStampNavigator();
  void SetAdvancedStampNavigator(CATAdvancedStampNavigator * iAdvancedStampNavigator);

  CATPersistentBody * GetNewInputShapePBody();
  void SetNewInputShapePBody(CATPersistentBody * iNewInputShapePBody);

  INLINE CATGMAdvancedStampFollower *GetAsAdvancedStampFollower();

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

  virtual void StreamCATCellManifoldNavigator(CATCellManifoldGroupNavigator *_Navigator, CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  virtual CATCellManifoldGroupNavigator *UnStreamCATCellManifoldNavigator(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:
  virtual CATCellManifoldGroupLayer *GetLayer() const;

protected:
  
private:
  CATBoolean _EditionMode;

  CATPersistentBody * _NewInputShapePBody;

private:
  CATPersistentBody * GetInputShapePBody(CATPersistentCellInfra & iInfra);

};

INLINE CATGMAdvancedStampFollower * CATGMAdvancedStampFollower::GetAsAdvancedStampFollower()
{
  return this;
}
#endif
