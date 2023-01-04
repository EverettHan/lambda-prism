#ifndef CATTransfoCellDC_h
#define CATTransfoCellDC_h
/*-*-C++-*-*/
//==========================================================================
// COPYRIGHT DASSAULT SYSTEMES 2011
//==========================================================================
//
//  Drawer collector qui a une CATMathTransformation
//  associe une hashtable de CATFace. 
//
//==========================================================================


#include "ExportedByCATTopologicalObjects.h"

#include "CATDrawerCollector.h"
#include "CATBoolean.h"

class CATMathTransformation;
class CATFace;
class CATCell;

class ExportedByCATTopologicalObjects CATTransfoCellDC : public CATDrawerCollector
{

public :
 
  CATTransfoCellDC(int iExpectedSize = 0);
  virtual ~CATTransfoCellDC();

  void CreateDrawer(CATMathTransformation * iElem, int iDrawerSize = 0);
  void Insert(CATMathTransformation * iElem, CATCell * iAssoc);
  CATBoolean Contains(CATMathTransformation * iElem);
  CATMathTransformation * GetItem(int iPos);
  

};
#endif
