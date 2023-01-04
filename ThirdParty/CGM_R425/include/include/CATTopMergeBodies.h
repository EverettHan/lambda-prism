#ifndef CATTopMergeBodies_H
#define CATTopMergeBodies_H
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 19 12 2000  Creation pour supprimer CATTopBodyTools.h
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATTopData.h"
#include "ListPOfCATBody.h"
#include "CATBoolean.h"

class CATGeoFactory;
class CATBody;


ExportedByCATTopologicalObjects void CATTopMergeBodies(CATGeoFactory      *   iFactory,
                                                       const CATLISTP(CATBody) & iList,
                                                       CATBody            * & oBody,
                                                       CATBoolean             iFreezeOn,
                                                       const CATTopData     & iTopData);

#endif
