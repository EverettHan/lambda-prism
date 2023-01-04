#ifndef CATTopSplitEdge_H
#define CATTopSplitEdge_H
//---------------------------------------------------------------------------------------------------------
// COPYRIGHT DASSAULT SYSTEMES  2000
// 19 12 2000  Creation pour supprimer CATTopBodyTools.h
// Oct. 02     Parametre iRemoveFromFactory
//---------------------------------------------------------------------------------------------------------
#include "ExportedByCATTopologicalObjects.h"
#include "CATTopOperator.h"
#include "CATTopData.h"
#include "CATTopDefine.h"
#include "CATBoolean.h"

#include "CATSetOfCrvParams.h"

class CATGeoFactory;
class CATBody;
class CATEdge;
class CATCGMJournalList;
class CATVertex;


ExportedByCATTopologicalObjects void CATTopSplitEdge(CATGeoFactory*            iFactory,
                                                     CATBody*                  iBody, 
                                                     CATEdge*                  iEdge,
                                                     const CATSetOfCrvParams&  iSetOfBreaks, 
                                                     CATBody*&                 oBody,
                                                     const CATTopData&         iTopData,
                                                     CATBoolean                iFreezeOn,
                                                     CATVertex**               ioCreatedVtx,
                                                     CATEdge**                 ioCreatedEdges,
                                                     CATBoolean                iRemoveFromFactory = FALSE);


#endif
