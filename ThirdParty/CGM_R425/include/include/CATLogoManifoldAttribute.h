// --------------------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2015
// ................................
//
// JNF: Feature recognition -- Logo Attribute -- | Generic level attribute |
// --------------------------------------------------------------------------------------//


#ifndef CATLogoManifoldAttribute_H
#define CATLogoManifoldAttribute_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATMathInline.h"
#include "ListPOfCATFace.h" 
#include "CATMathDirection.h"
#include "ListPOfCATCellManifold.h"

class CATCloneManager;
class CATTransfoManager;
class CATSurface;
class CATCurve;
class CATCellManifold;
class CATCell;
class CATSoftwareConfiguration;

class ExportedByPersistentCell CATLogoManifoldAttribute : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATLogoManifoldAttribute, CATManifoldAttribute);

  CATLogoManifoldAttribute(); 
  CATLogoManifoldAttribute(CATSoftwareConfiguration * iConfig, ListPOfCATCellManifold & iLogoManifolds, ListPOfCATCellManifold & iSupportManifolds); 
  virtual ~CATLogoManifoldAttribute();

  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;

  virtual CATCellManifoldGroupNavigator* CreateGroupNavigator(CATLiveBody* iLiveBody, const CATTopData& iTopData, CATCellManifoldGroup* iGroup) const;

  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream); 
  virtual void Dump(CATCGMOutput& iWhereToWrite) const;

  virtual CATBoolean AreSpecificDatasImagesEqualToParents(CATCellManifoldGroupCarrier * iCellManifoldGroupCarrier)const;

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;
  virtual CATBoolean CompareFaceLists(const ListPOfCATFace &iThisFaceList, const ListPOfCATFace &iOtherFaceList) const;

  INLINE virtual short GetStreamVersion() const;
  INLINE virtual void  SetStreamVersion(short & iVersion);

  INLINE virtual CATLogoManifoldAttribute *GetAsLogoManifoldAttribute();
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

  CATBoolean SupportsSizeAndHeight() const;
  double GetSize(CATLiveBody const & iLiveBody) const;
  double GetHeight(CATLiveBody const & iLiveBody) const;

protected:
  virtual CATManifoldAttribute *CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, 
                                                    const CATCellManifoldGroup           &iImageCellManifoldGroup, 
                                                    CATCellManifoldsManager &iCellManifoldsManager) const;
  short            _StreamVersion; // Version du stream
  ListPOfCATCellManifold  _LogoManifolds;
  ListPOfCATCellManifold  _SupportManifolds;

  CATSoftwareConfiguration * GetConfig() const;
  void ComputeSizeAndHeight(CATLiveBody const & iLiveBody) const;

private:
  CATSoftwareConfiguration * _Config;

  // Cached data (not streamed)
  mutable double _Size;
  mutable double _Height;

  short CompareCells(const CATCell *iRefCell, const CATCell *iResultCell) const;
};

INLINE short CATLogoManifoldAttribute::GetStreamVersion() const
{
  return _StreamVersion;
}

INLINE void CATLogoManifoldAttribute::SetStreamVersion(short & iVersion)
{
  _StreamVersion = iVersion;
}

INLINE CATLogoManifoldAttribute * CATLogoManifoldAttribute::GetAsLogoManifoldAttribute() 
{
  return this;
}

#endif

