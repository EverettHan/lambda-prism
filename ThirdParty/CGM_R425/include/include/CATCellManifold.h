#ifndef CATCellManifold_h
#define CATCellManifold_h

// COPYRIGHT DASSAULT SYSTEMES  2007

#include "CATGeometry.h"


class CATDeclarativeManifold;
class CATCell;
#include "ListPOfCATCell.h"


#include "CATGMModelInterfaces.h"
#ifndef LOCAL_DEFINITION_FOR_IID
extern ExportedByCATGMModelInterfaces IID IID_CATCellManifold ;
#else
extern "C" const IID IID_CATCellManifold ;
#endif


class ExportedByCATGMModelInterfaces CATCellManifold : public CATGeometry
{
  CATDeclareInterface;

public:

  virtual CATBoolean Contains(const CATCell* iCell) const=0; 
  virtual void GetCells(ListPOfCATCell &ioCells) const=0; // NB: Append Cells to ioCells List 
  virtual CATDeclarativeManifold* GetOwner() const=0;
  virtual int GetDimension() const=0;
};
  
CATDeclareHandler(CATCellManifold,CATGeometry);

#endif
