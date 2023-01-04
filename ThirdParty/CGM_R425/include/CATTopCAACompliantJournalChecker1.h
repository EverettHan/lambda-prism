//=============================================================================
// COPYRIGHT DASSAULT SYSTEMES 2009
#ifndef CATTopCAACompliantJournalChecker1_H_
#define CATTopCAACompliantJournalChecker1_H_
//=============================================================================
// COPYRIGHT     : DASSAULT SYSTEMES 2009
//
//									Boolean Operator For Manifolder Compatible : 
// DESCRIPTION   : Interface to  clean journal from completed journal to standard journal
//
// Avril 2009      : Creation                                            R.LOJA
//
//============================================================================

#include "ExportedByCATTopologicalObjects.h"
#include "CATCGMVirtual.h"
//#include "CATCGMNewArray.h"
#include "CATTopOperator.h"
#include "CAATopCheckForPartType.h"

//class CATGeoFactory;
class CATBody;
//class CATTopData;


  //TRUE if iCell is a bordering cell of inBody
 ExportedByCATTopologicalObjects 
   CATBoolean IsABordingCell(CATCell* iCell, CATBody* inBody);
  
#endif
