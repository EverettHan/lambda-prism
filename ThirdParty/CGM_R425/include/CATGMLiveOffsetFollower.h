#ifndef CATGMLiveOffsetFollower_H
#define CATGMLiveOffsetFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "CATGMLiveHierarchicalGroupFollower.h"
#include "CATDataType.h"
#include "CATMathTransformation.h"
#include "CATCGMJournalList.h"
#include "ListPOfListPOfCATCell.h"
#include "ListPOfCATCellManifold.h"
#include "CATCollec.h"
#include "ListPOfCATDeclarativeManifold.h"
#include "CATListOfDouble.h"


class CATCellManifoldGroup;
class CATLISTP(CATCellManifoldGroup);
class CATPersistentBody;
class CATBody;
class CATPersistentCellInfra;
class CATLiveBody;
class CATCGMHashTableWithAssoc;
class CATCellManifoldHashTableWithAttributeAssoc;
class CATCellManifoldOffsetNavigator;



class ExportedByPersistentCell CATGMLiveOffsetFollower : public CATGMLiveHierarchicalGroupFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveOffsetFollower(CATCellManifoldGroup           &iNetworkGroup, 
    CATCellManifoldGroup           &iOffsetGroup,
    short                          &iSkinNumber,
    CATPersistentBody              &iOffsetedBody,
    CATPersistentCellInfra         &iInfra);
  //FOR UNSTREAM ONLY
  CATGMLiveOffsetFollower(CATPersistentCellInfra         &iInfra);


  // Destructor
  ~CATGMLiveOffsetFollower();

  // Cast 
  INLINE virtual CATGMLiveOffsetFollower *GetAsOffsetFollower();
  virtual void GetCellManifoldsInInputBody(ListPOfCATCellManifold &iInputCellManifolds) const;

  INLINE short GetSkinNumber() const;

  INLINE void SetListOfCreatedOffsetValue(double iOffsetValue);
  INLINE void GetListOfCreatedOffsetValue(CATListOfDouble & oOffsetValueList);

  CATCellManifoldOffsetNavigator * GetOffsetNavigator() const;
  void SetOffsetNavigator(CATCellManifoldOffsetNavigator * iOffsetNavigator);

  virtual void SetSpecificValue(CATManifoldAttribute * iAttr, int iIndex);

  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);

  virtual void StreamCATCellManifoldNavigator(CATCellManifoldGroupNavigator *_Navigator, CATCGMStream& ioStr, CATGeoFactory * iFactory) const;
  virtual CATCellManifoldGroupNavigator *UnStreamCATCellManifoldNavigator(CATCGMStream& ioStr, CATGeoFactory * iFactory);

protected:
  virtual CATCellManifoldGroupLayer *GetLayer() const;
  virtual CATManifoldAttribute *CreateManifoldAttribute(CATCellManifold *iCellManifold) const;
private:
  short    _SkinNumberToFollow;
  CATListOfDouble _CreatedOffsetValue; //parallel with _ListOfCMReference and _CreatedCellsPointingOnCMReference
};
INLINE short CATGMLiveOffsetFollower::GetSkinNumber() const
{
  return _SkinNumberToFollow;
}
INLINE CATGMLiveOffsetFollower* CATGMLiveOffsetFollower::GetAsOffsetFollower()
{
  return this;
}

INLINE void CATGMLiveOffsetFollower::SetListOfCreatedOffsetValue(double iOffsetValue)
{
  _CreatedOffsetValue.Append(iOffsetValue);
}

INLINE void CATGMLiveOffsetFollower::GetListOfCreatedOffsetValue(CATListOfDouble & oOffsetValueList)
{
  oOffsetValueList = _CreatedOffsetValue;
}
#endif

