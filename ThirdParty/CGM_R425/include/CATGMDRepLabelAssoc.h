// ----------------------------------------------------------------------------//
// COPYRIGHT DASSAULT SYSTEMES 2018
// ................................
//
// VB7
// ----------------------------------------------------------------------------//
//==========================================================
// !!!!!!!!!!!!!!!!!!!!!!DO NOT USE!!!!!!!!!!!!!!!!!!!!!!!!!
//==========================================================
// WORK IN PROGRESS VB7 W05 2018


#ifndef CATGMDRepLabelAssoc_H
#define CATGMDRepLabelAssoc_H

#include "PersistentCell.h"
#include "CATCGMNewArray.h"
#include "ListPOfCATDRepLabel.h"
#include "CATDRepLabelAssoc.h"
#include "ListPOfCATBody.h"

class CATCGMOutput;
class CATCGMStream;

//@nocgmitf
class ExportedByPersistentCell CATGMDRepLabelAssoc : public CATDRepLabelAssoc
{
public:

  CATCGMNewClassArrayDeclare;      // Pool allocation

  //Constructor
  CATGMDRepLabelAssoc(ListPOfCATDRepLabel & iParentsDRepLabelList, ListPOfCATDRepLabel & iChildrenDRepLabelList, CATDRepLabelAssocType iType);
  CATGMDRepLabelAssoc(CATGMDRepLabelAssoc & iDRepLabelAssoc);

  //Destructor
  virtual ~CATGMDRepLabelAssoc();

  virtual void Dump(CATCGMOutput& os);

  CATBoolean IsEqual(CATDRepLabelAssoc * iDRepLabelAssoc);

  //Get methods
  CATDRepLabelAssocType GetType();
  void GetParentDRepLabelList(ListPOfCATDRepLabel & oParentDRepLabelList);
  void GetChildrenDRepLabelList(ListPOfCATDRepLabel & oChildrenDRepLabelList);

  CATBoolean LocateParent(CATDRepLabel * iDRepLabel);

         void                  Stream(CATCGMStream & ioStream) const;
  static CATGMDRepLabelAssoc * UnStream(CATCGMStream & ioStr);

private:
  ListPOfCATDRepLabel  * _ParentsDRepLabelList;
  ListPOfCATDRepLabel  * _ChildrenDRepLabelList;
  CATDRepLabelAssocType  _Type;
};

#endif
