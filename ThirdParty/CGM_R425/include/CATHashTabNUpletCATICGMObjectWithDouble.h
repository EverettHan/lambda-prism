#ifndef CATHashTabNUpletCATICGMObjectWithDouble_H
#define CATHashTabNUpletCATICGMObjectWithDouble_H

// COPYRIGHT DASSAULT SYSTEMES  2014
/**
* @CAA2Level L1 ????
* @CAA2Usage U1 ???? 
*/

#include "ExportedByGeometricObjects.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMNewArray.h"
#include "CATThrowForNullPointer.h"

class CATNUpletOfCATICGMObject;



/**
*  Hash Tab of NUpletOf CATICGMObject with double value as associated value.
*/

class  ExportedByGeometricObjects CATHashTabNUpletCATICGMObjectWithDouble : public  CATCGMHashTableWithAssoc
{
public:
  CATHashTabNUpletCATICGMObjectWithDouble(int iEstimatedSize = 0);
  ~CATHashTabNUpletCATICGMObjectWithDouble();
  CATCGMNewClassArrayDeclare;
  
  int									Insert(CATNUpletOfCATICGMObject* pioNUpletOfCATICGMObject, double* ipAssocValue) ;
  int									LocateItem(CATNUpletOfCATICGMObject* ipElem, double** oppAssocValue) const;
  CATNUpletOfCATICGMObject*	GetItemAndAssoc(int iPos, double** oppAssocValue) const;
  double*							GetAssoc(int iPos);
};

#endif
