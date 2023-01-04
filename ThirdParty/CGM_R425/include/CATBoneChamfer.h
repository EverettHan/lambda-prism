#ifndef CATBoneChamfer_h
#define CATBoneChamfer_h

// COPYRIGHT DASSAULT SYSTEMES  2009

#include "CATBoneManifold.h"
#include "CATTopDefine.h"

class CATLiveBody;

#include "YI00IMPL.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByYI00IMPL IID IID_CATBoneChamfer ;
#else
extern "C" const IID IID_CATBoneChamfer ;
#endif

//TODO: Do away with enum, since we assume that short equivalents of CATDynTypeChamfer & CATLiveTypeChamfer are same
//TODO: Update CATLiveTypeChamfer if CATDynTypeChamfer is modified 
enum CATLiveTypeChamfer
{
CATLiveTypeChamferd1d2,
CATLiveTypeChamfera1a2,
CATLiveTypeChamferd1a1,
CATLiveTypeChamferd1a2,
CATLiveTypeChamfera1d2,
CATLiveTypeChamferd2a2,
CATLiveTypeChamferda1,
CATLiveTypeChamferda2,
CATLiveTypeChamferApproxd1d2,
CATLiveTypeChamferApproxd1a1
};


class ExportedByYI00IMPL CATBoneChamfer : public CATBoneManifold
{
  CATDeclareInterface;

public:

  virtual void Set(const ListPOfCATCellManifold &iRepresentation,
                   const ListPOfCATCellManifold &iRefFaces1, 
                   const ListPOfCATCellManifold &iRefFaces2, 
                   const CATLiveTypeChamfer   iTypeSpec,
                   const double        iLeftValue,
                   const double        iRightValue) = 0;

  virtual void GetDoubleValues ( double &oLeftValue, double &oRightValue ) const = 0;
  virtual void GetSupport  (ListPOfCATCellManifold &oReferenceFaces1, ListPOfCATCellManifold &oReferenceFaces2) const = 0;
  virtual CATLiveTypeChamfer GetChamferType() const = 0;
  virtual double GetMaxDistanceValue() const = 0;

};
  
CATDeclareHandler(CATBoneChamfer,CATContextualManifold);

#endif
