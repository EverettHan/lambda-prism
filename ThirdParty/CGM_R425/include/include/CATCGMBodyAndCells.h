#ifndef CATCGMBodyAndCells_h
#define CATCGMBodyAndCells_h

#include "CATGMModelInterfaces.h"
#include "CATListOfCATCells.h"

class CATBody;

class ExportedByCATGMModelInterfaces CATCGMBodyAndCells
{
public : 
  CATCGMBodyAndCells();
  virtual ~CATCGMBodyAndCells();

  void SetBodyAndCells(CATBody * ipBody, const CATListPtrCATCell & iCells);

  void AddCell(CATCell * ipCell);
  void AddCells(CATListPtrCATCell & iCells);
  CATBody * GetBody() const;
  CATListPtrCATCell & GetCells();
private :
  CATCGMBodyAndCells(const CATCGMBodyAndCells &);

  CATBody * _pBody;
  CATListPtrCATCell _Cells;
};

//#include "CATLISTPP_Clean.h"
//#include "CATLISTPP_PublicInterface.h"
//#include "CATLISTPP_Declare.h"
//#undef CATCOLLEC_ExportedBy
//#define CATCOLLEC_ExportedBy ExportedByCATGMModelInterfaces
//CATLISTP_DECLARE(CATCGMBodyAndCells);

#endif
