#ifndef CATManifoldAttributeSample_h
#define CATManifoldAttributeSample_h

// COPYRIGHT DASSAULT SYSTEMES  2007
#include "CATIACGMLevel.h"
#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATMathPoint.h"

// Do not delete: may be used in customer files

class CATGeometry;
class CATCloneManager;
class CATTransfoManager;

#include "CATGMModelInterfaces.h"
class ExportedByCATGMModelInterfaces CATManifoldAttributeSample : public CATManifoldAttribute
{
public:
  CATCGMDeclareAttribute (CATManifoldAttributeSample,CATManifoldAttribute);

  CATManifoldAttributeSample(); // Default constructr is mandatory
  CATManifoldAttributeSample(CATMathPoint &iCenter);
  virtual ~CATManifoldAttributeSample();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, 
    CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;

  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

  void GetCenter(CATMathPoint &oCenter) const;

  virtual CATManifoldAttributeSample *GetAsManifoldAttributeSample()const;
  virtual CATBoolean HaveSameType(CATManifoldAttribute &iOtherManifoldAttribute)const;

private:
  CATMathPoint _Center;

};
#endif

