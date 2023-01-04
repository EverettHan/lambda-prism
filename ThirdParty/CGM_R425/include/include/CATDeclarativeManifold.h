#ifndef CATDeclarativeManifold_h
#define CATDeclarativeManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATManifold.h"
//#include "ListPOfCATManifoldParameter.h"

#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATDeclarativeManifold ;
#else
extern "C" const IID IID_CATDeclarativeManifold ;
#endif

class CATDatumManifold;
class CATEvaluableManifold;
class CATSubdivisionManifold;
class CATPlaneManifold;
class CATCylinderManifold;
class CATSphereManifold;
class CATConeManifold;
class CATTorusManifold;
class CATContextualManifold;
class CATBoneManifold;
class CATBoneFillet;
class CATJointFillet;
class CATJointChamfer;
class CATBoneChamfer;
class CATDraftManifold;
class CATButtonManifold;
class CATJointManifold;

class ExportedByCATGMModelInterfaces CATDeclarativeManifold : public CATManifold
{
  CATDeclareInterface;

public:

  virtual CATDatumManifold*              GetAsDatumManifold()              = 0;
  virtual CATEvaluableManifold*          GetAsEvaluableManifold()          = 0;
  virtual CATSubdivisionManifold*        GetAsSubdivisionManifold()        = 0;
  virtual CATPlaneManifold*              GetAsPlaneManifold()              = 0;
  virtual CATCylinderManifold*           GetAsCylinderManifold()           = 0;
  virtual CATSphereManifold*             GetAsSphereManifold()             = 0;
  virtual CATConeManifold*               GetAsConeManifold()               = 0;
  virtual CATTorusManifold*              GetAsTorusManifold()              = 0;
  virtual CATContextualManifold*         GetAsContextualManifold()         = 0;
  virtual CATBoneManifold*               GetAsBoneManifold()               = 0;
  virtual CATBoneFillet*                 GetAsBoneFillet()                 = 0;
  virtual CATJointFillet*                GetAsJointFillet()                = 0;
  virtual CATBoneChamfer*                GetAsBoneChamfer()                = 0;
  virtual CATDraftManifold*              GetAsDraftManifold()              = 0;
  virtual CATButtonManifold*             GetAsButtonManifold()             = 0;
  virtual CATJointChamfer*               GetAsJointChamfer()               = 0;
  virtual CATJointManifold*              GetAsJointManifold()              = 0;

  // Deprecated - Use GetCellManifoldRep()
  virtual void GetRep(ListPOfCATCellManifold &oReps) const=0;

//protected:
//  virtual HRESULT GenerateParameters (CATTopData * iTopData, ListPOfCATManifoldParameter &oManifoldParameters)=0;
};
  
CATDeclareHandler(CATDeclarativeManifold, CATManifold);

// ------------------------------------------------------------------------
// CATGetDeclarativeReference
// Get the DeclarativeReference. For example, a Nurbs has a not extrapolated Nurbs as reference.
// If there is no DeclarativeReference, return NULL
// ------------------------------------------------------------------------
ExportedByCATGMModelInterfaces CATGeometry *CATPGMGetDeclarativeReference(CATGeometry *ipGeometry);

#endif
