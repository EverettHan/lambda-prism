#ifndef CATGMLiveKeepTopFollower_H
#define CATGMLiveKeepTopFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "CATGMLiveContextualFeatureFollower.h"
#include "ListPOfCATPersistentFaces.h"

class CATlsoAdvancedStampData;

class ExportedByPersistentCell CATGMLiveKeepTopFollower : public CATGMLiveContextualFeatureFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveKeepTopFollower(CATlsoAdvancedStampData   & iAdvancedStampData,
                           CATPersistentBody         & iInputPBody,
                           CATPersistentCellInfra    & iInfra,
                           ListPOfCATPersistentFaces & iToFollowPFaceList);

 //FOR UNSTREAM ONLY
  CATGMLiveKeepTopFollower(CATPersistentCellInfra         &iInfra);

  // Destructor
  ~CATGMLiveKeepTopFollower();

  INLINE CATGMLiveKeepTopFollower * GetAsKeepTopFollower();
  INLINE CATlsoAdvancedStampData  * GetAdvancedStampData() const;

  INLINE void GetToFollowPFaceList(ListPOfCATPersistentFaces & oToFollowPFaceList) const;

  virtual void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  virtual void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
  virtual void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const;

private:
  CATlsoAdvancedStampData * _AdvancedStampData;
  CATBoolean                _AdvancedStampDataOwner;
  ListPOfCATPersistentFaces _ToFollowPFaceList;

};

INLINE CATGMLiveKeepTopFollower * CATGMLiveKeepTopFollower::GetAsKeepTopFollower()
{
  return this;
}

INLINE CATlsoAdvancedStampData * CATGMLiveKeepTopFollower::GetAdvancedStampData() const
{
  return _AdvancedStampData;
}

INLINE void CATGMLiveKeepTopFollower::GetToFollowPFaceList(ListPOfCATPersistentFaces & oToFollowPFaceList) const
{
  oToFollowPFaceList.Append(_ToFollowPFaceList);
}

#endif

