#ifndef CATGMLiveBoneFollower_H
#define CATGMLiveBoneFollower_H

#include "CATCGMNewArray.h"
#include "PersistentCell.h"
#include "CATBoolean.h"
#include "CATGMLiveContextualFeatureFollower.h"

#include "ListPOfCATPersistentEdges.h"

class CATBoneFillet;
class CATPersistentBody;
class CATBody;
class CATPersistentCellInfra;
class CATContextualManifold;
class CATBoneManifold;
class CATCGMStream;
class CATGeoFactory;
class CATFace;

class ExportedByPersistentCell CATGMLiveBoneFollower : public CATGMLiveContextualFeatureFollower 
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATGMLiveBoneFollower(           CATContextualManifold          &iBoneToFollow, 
                                   CATPersistentBody              &iFilletedBody,
                                   CATPersistentCellInfra         &iInfra,
                                   ListPOfCATPersistentEdges      &iEdgesToFillet,
                                   CATPersistentBody              &iBodyWithoutFillet);
  
 //FOR UNSTREAL ONLY
 CATGMLiveBoneFollower(CATPersistentCellInfra         &iInfra);

  // Destructor
  ~CATGMLiveBoneFollower();
  void SetManualPropagation(CATBoolean iIsPropagManual);

  //static CATBoolean AreEqual(const CATGMLiveBoneFollower &iFollower1, const CATGMLiveBoneFollower &iFollower2);

  virtual HRESULT Merge(CATGMLiveContextualFeatureFollower& iFollower);

  CATBoneManifold& GetBoneManifold() const;
  CATContextualManifold & GetContextualManifold() const;
  void GetEdgesToFillet(ListPOfCATPersistentEdges &oEdgesToFillet) const;
  void GetSuperEdgesToFillet(ListPOfCATPersistentEdges &oEdgesToFillet) const;
  void SetSuperEdgesToFillet(ListPOfCATPersistentEdges &iEdgesToFillet);
  void GetFilletedPFaces(ListPOfCATPersistentFaces &oFilletedFaces) const;
  void SetFilletedPFaces(ListPOfCATPersistentFaces &iFilletedFaces);
  void AppendFilletedPFaces(CATPersistentFace *iPFace);
  CATBoolean IsPropagationManual() const;
  CATBoolean HasFullScar() const;

  virtual CATGMLiveBoneFollower*    GetAsBoneFollower();
  void Stream(CATCGMStream& ioStr,CATGeoFactory * iFactory) const;
  void UnStream(CATCGMStream& ioStr,CATGeoFactory * iFactory);
  void GetDeclarativeManifoldsInInputBody(ListPOfCATDeclarativeManifold &iInputDeclarativeManifolds) const;

  INLINE void       SetScarState(int iScarState);


private:
  CATContextualManifold    *_BoneToFollow;
  ListPOfCATPersistentEdges _EdgesToFillet;
  ListPOfCATPersistentEdges _SuperEdgesToFillet;
  CATBoolean                _PropagManual;
  ListPOfCATPersistentFaces _FilletedPFaces;

  //VB7
  int                       _ScarState;
};


//int operator != (const CATGMLiveBoneFollower &iFollower1, const CATGMLiveBoneFollower &iFollower2);
//int operator == (const CATGMLiveBoneFollower &iFollower1, const CATGMLiveBoneFollower &iFollower2);

INLINE void CATGMLiveBoneFollower::SetScarState(int iScarState) {
  _ScarState = iScarState; }

#endif

