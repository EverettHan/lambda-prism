// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W04 2018
// ----------------------------------------------------------------------------//

#ifndef CATDRepLabelAssoc_H
#define CATDRepLabelAssoc_H

#include "CATGMModelInterfaces.h"
#include "CATCGMVirtual.h"
#include "CATBoolean.h"
#include "ListPOfCATDRepLabel.h"

class CATCGMStream;
class CATCGMOutput;

typedef enum  {
  CATDRepLabelAssocModification = 0,
  CATDRepLabelAssocAbsorption = 1,
  CATDRepLabelAssocSubdivision = 2,
  CATDRepLabelAssocDeletion = 3
} CATDRepLabelAssocType;


class ExportedByCATGMModelInterfaces CATDRepLabelAssoc : public CATCGMVirtual
{
public: 
  CATDRepLabelAssoc(); 
  virtual ~CATDRepLabelAssoc();

  virtual CATBoolean IsEqual(CATDRepLabelAssoc * iDRepLabelAssoc)=0;

  virtual void Dump(CATCGMOutput& os)=0;

  virtual CATDRepLabelAssocType GetType()=0;

  virtual void GetParentDRepLabelList(ListPOfCATDRepLabel & oParentDRepLabelList)=0;

  virtual void GetChildrenDRepLabelList(ListPOfCATDRepLabel & oChildrenDRepLabelList)=0;

};

#endif

