#ifndef CATAdvancedStampManifoldGroupAttribute_h
#define CATAdvancedStampManifoldGroupAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2018
// VB7

#include "CATCGMNewArray.h"
#include "CATPersistentCell.h"
#include "CATManifoldGroupAttribute.h"

class ExportedByPersistentCell CATAdvancedStampManifoldGroupAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATAdvancedStampManifoldGroupAttribute,CATManifoldAttribute);

  CATAdvancedStampManifoldGroupAttribute(double iFilletRadius, CATBoolean iFilletRepresentation);

  CATAdvancedStampManifoldGroupAttribute(); // Default constructor is mandatory
  virtual ~CATAdvancedStampManifoldGroupAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  //Get
  double GetFilletRadius() const;
  CATBoolean GetFilletRepresentation() const;

  INLINE CATAdvancedStampManifoldGroupAttribute *GetAsAdvancedStampManifoldGroupAttribute();

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* CreateImageAttribute(const CATLISTP(CATCellManifoldGroup) &iParentGroups, const CATCellManifoldGroup &iImageCellManifoldGroup, CATCellManifoldsManager &iCellManifoldsManager) const;

  virtual CATCellManifoldGroupNavigator * CreateGroupNavigator(CATLiveBody * iLiveBody, const CATTopData & iTopData, CATCellManifoldGroup * iGroup) const;

  virtual CATBoolean IsEquivalentTo(const CATManifoldAttribute &iOtherManifoldAttribute, CATGeoFactory * iFactory) const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

protected:

private:

  double     _FilletRadius;
  CATBoolean _FilletRepresentation;

};

INLINE CATAdvancedStampManifoldGroupAttribute *CATAdvancedStampManifoldGroupAttribute::GetAsAdvancedStampManifoldGroupAttribute() {
  return this; }
#endif
