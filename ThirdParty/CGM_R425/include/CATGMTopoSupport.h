//===================================================================
// COPYRIGHT 3DS 2014/01/15
//===================================================================
// Header definition of class CATGMTopoSupport
//===================================================================


//===================================================================
//  2014/01/15 Creation: JUZ
//===================================================================
#ifndef CATGMTopoSupport_H
#define CATGMTopoSupport_H

#include "CATCDMBaseInterfaces.h" // export
#include "CATGMSupport.h"
#include "CATErrorDef.h"
#include "CATSysBoolean.h"
#include "ListPOfCATCellManifold.h" 
#include "CATListOfCATCells.h"
#include "ListPOfCATBody.h"
#include "CATListOfInt.h"
#include "CATListOfCATGeometries.h"

class CATBody;
class CDMLabelContract;
class CATMathPoint;
class CATGeometry;
class CATLISTV(CATBaseUnknown_var);

class ExportedByCATCDMBaseInterfaces CATGMTopoSupport: public CATGMSupport
{
public:
  // Lifecycle
  virtual ~CATGMTopoSupport();

  // Get the iNumber-th geometric support
  // Note: lists of cells (or cell_manifolds) and bodies have same size, elements are paired 
  virtual HRESULT GetCellManifoldsSupport( CATLISTP(CATCellManifold) & oCellManifoldsList, CATLISTP(CATBody) & oBodiesList) = 0;
  virtual HRESULT GetGeometrySupport( CATGeometry*& oGeometry, CATBody*& Body, CDMLabelContract & oContract) = 0;

  // oOrientationList[i] contain the factor to be applied to topological cell oCellsList[i] or oGeomsList[i] orientation for it to be stable in domain oDomains[i]
  // when support is a use cell, then oOrientationList[i]==1 and oDomains[i]==NULL for each i.
  virtual HRESULT GetPointedObjectsAsGeometries(CATListPtrCATGeometry & oGeomsList, CATLISTP(CATBody) & oBodiesList, CATListOfInt* oOrientationList = 0, CATLISTP(CATGeometry)* oDomains = 0)=0 ;
  virtual HRESULT GetCellsSupport( CATListPtrCATCell & oCellsList, CATLISTP(CATBody) & oBodiesList,  CATListOfInt* oOrientationList = 0, CATLISTP(CATGeometry)* oDomains = 0) = 0;
  
  
  // Use Cell / fix body
  virtual HRESULT IsFixedCDMSupport(CATBoolean& oIsFixedCDMSupport) = 0;

protected:
  CATGMTopoSupport();

private:
  // The copy constructor and the equal operator must not be implemented
  CATGMTopoSupport (CATGMTopoSupport &);
  CATGMTopoSupport& operator=(CATGMTopoSupport&);

};

//-----------------------------------------------------------------------
#endif
