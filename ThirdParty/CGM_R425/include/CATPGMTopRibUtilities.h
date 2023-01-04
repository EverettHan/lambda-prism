#ifndef CATPGMTopRibUtilities_h_
#define CATPGMTopRibUtilities_h_

// COPYRIGHT DASSAULT SYSTEMES 2006

#include "CATGMOperatorsInterfaces.h"

class CATCGMJournalList;
class CATEdge;
class CATTopData;



//------------------------------------------------------------------------------
// Utilise le journal apres decoupe pour savoir ce 
// que sont devenues les entrees utilsateur
//------------------------------------------------------------------------------
ExportedByCATGMOperatorsInterfaces void CATPGMFollowEdgeAndRatio(
  CATTopData *iTopData,
  CATEdge *iEdgeToFollow,
  double iRatio,
  CATCGMJournalList &iPrivateEdgesJournal,
  CATEdge *&oEdge,
  double &oRatio);

#endif /* CATPGMTopRibUtilities_h_ */
