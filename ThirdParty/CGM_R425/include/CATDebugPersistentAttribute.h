#ifndef CATDebugPersistentAttribute_h
#define CATDebugPersistentAttribute_h

// COPYRIGHT DASSAULT SYSTEMES  2016

#include "CATCGMNewArray.h"
#include "CATManifoldAttribute.h"
#include "PersistentCell.h"
#include "CATHashTableWithIntAssoc.h"

class ExportedByPersistentCell CATDebugPersistentAttribute : public CATCGMAttribute
{
public:
  CATCGMDeclareAttribute (CATDebugPersistentAttribute,CATCGMAttribute);

  CATDebugPersistentAttribute(); // Default constructor is mandatory

  virtual ~CATDebugPersistentAttribute();
  CATCGMNewClassArrayDeclare;      // Pool allocation

  void GetPCellTagList(CATListOfInt & oPCellTagList);
  void AppendPCellTag(int iPCellTag, int iBodyTag);
  void GetBodyTagList(CATListOfInt & oBodyTagList);

  virtual void Dump( CATCGMOutput & os );

protected :

  

private:
  CATListOfInt _PCellTagList;
  CATListOfInt _BodyTagList;//parallel to _PCellTagList
};

#endif

