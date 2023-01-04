#ifndef CATBoneFillet_h
#define CATBoneFillet_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATBoneManifold.h"
#include "ListPOfCATJointFillet.h"
#include "ListPOfCATManifoldLocalRadius.h"
#include "CATTopDefine.h"
#include "CATMathDef.h"
#include "CATMathConstant.h"
#include "CATFilletDefine.h"
#include "CATSoftwareConfiguration.h"

class CATLiveBody;
class CATHVertex;
class CATManifoldLocalRadius;

#include "YI00IMPL.h"

#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATBoneFillet ;
#else
extern "C" const IID IID_CATBoneFillet ;
#endif

class ExportedByYI00IMPL CATBoneFillet : public CATBoneManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   const ListPOfCATCellManifold  iLeftAndRightSupport[2], 
                   const CATPositiveLength       iRadius) = 0;

  virtual CATManifoldLocalRadius* SetLocalRadius(CATHVertex* iLocation, const CATPositiveLength iRadius, CATAngle* iAngle=NULL, const CATULONG32 iId=0) = 0;
  virtual void SetLocalRadius(CATManifoldLocalRadius* iLocalRadius) = 0;
  virtual void SetRadius(const CATPositiveLength iRadius) = 0;
  virtual void SetFilletRadiusType(CATFilletRadiusType iRadiusType) = 0;
  virtual void SetFilletSectionType(CATFilletSectionType iProfile) = 0;
  virtual void SetFilletShapeParameter(double iParameter) = 0;
  virtual void SetSupport(const ListPOfCATCellManifold iLeftAndRightSupport[2]) = 0;

  virtual CATPositiveLength    GetRadius() const = 0;
  virtual void                 GetJoint(CATLiveBody              *iContextLiveBody, 
                                        ListPOfCATCellManifold    oStartAndEndJointRep[2], 
                                        CATSoftwareConfiguration *iConfig=NULL) const = 0;
  virtual void                 GetJoint(CATLiveBody *iContextLiveBody, ListPOfCATJointFillet &oStartAndEndJoint) const = 0;
  virtual CATFilletType        GetFilletType() const = 0;
  virtual CATFilletRadiusType  GetFilletRadiusType() const = 0;
  virtual CATFilletSectionType GetFilletSectionType() const = 0;
  virtual double               GetFilletShapeParameter() const = 0;
  virtual void                 GetLocalRadius(ListPOfCATManifoldLocalRadius& oLocalRadii) const = 0;


};
  
CATDeclareHandler(CATBoneFillet,CATContextualManifold);

#endif
