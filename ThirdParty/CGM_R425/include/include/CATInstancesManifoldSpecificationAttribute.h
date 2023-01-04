#ifndef CATInstancesManifoldSpecificationAttribute_h
#define CATInstancesManifoldSpecificationAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2013
// VB7

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "CATPersistentCell.h"
#include "CATListOfShort.h"
#include "CATManifoldGroupAttribute.h"

class ExportedByPersistentCell CATInstancesManifoldSpecificationAttribute : public CATManifoldGroupAttribute
{
public:
  CATCGMDeclareAttribute (CATInstancesManifoldSpecificationAttribute,CATManifoldAttribute);

  CATInstancesManifoldSpecificationAttribute(); // Default constructor is mandatory
  CATInstancesManifoldSpecificationAttribute(short iNbInstances);
  virtual ~CATInstancesManifoldSpecificationAttribute();
  void Init();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  INLINE CATInstancesManifoldSpecificationAttribute *GetAsInstancesManifoldSpecificationAttribute();
  INLINE short GetNumberOfInstances() const;
  
  virtual void GetLinksCGM(CATLISTP(CATICGMObject) &oLinks,
                           CATCGMLinkType           iLinkType,
                           CATRCOLL(int)*           oSharedStatus,
                           CATLISTV(CATString)*     oLinksString);

  virtual CATManifoldAttribute* CreateImageManifoldAttribute(CATLiveBody &iLiveBody, CATLISTP(CATManifoldAttribute) &iParentManifoldAttributes ) const;
  virtual CATManifoldAttribute* Clone(CATCloneManager& iCloneManager) const;
  virtual void Move3D(CATTransfoManager& iTransfoManager);
  virtual void GetColor(int &oR, int &oG, int &oB) const;
  virtual HRESULT GenerateParameters (CATTopData * iTopData, CATCellManifoldGroupCGM * iGroup, ListPOfCATManifoldParameter &oManifoldParameters) const;
  virtual void Stream(CATCGMStream & ioStream) const;
  virtual void UnStream(CATCGMStream& ioStream);
  virtual void Dump(CATCGMOutput& iWhereToWrite) const; 

protected : 
  //For unstream only
  void SetNumberOfInstances(short iNumberInstances);

private:

  // Nombre d'instances
  short _NbInstances;

};

INLINE CATInstancesManifoldSpecificationAttribute *CATInstancesManifoldSpecificationAttribute::GetAsInstancesManifoldSpecificationAttribute() {
  return this; }

INLINE short CATInstancesManifoldSpecificationAttribute::GetNumberOfInstances() const {
  return _NbInstances; }
INLINE void CATInstancesManifoldSpecificationAttribute::SetNumberOfInstances(short iNumberInstances)  {
  _NbInstances=iNumberInstances; }

#endif

