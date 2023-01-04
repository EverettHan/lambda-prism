/* -*-C++-*- */

#ifndef CATlsoActivateUtilities_H
#define CATlsoActivateUtilities_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier

W28 2019
=============================================================================
*/

#include "CATPersistentCell.h"

class CATPersistentCellInfra;
class CATPersistentBody;
class CATBody;

class ExportedByPersistentCell CATlsoActivateUtilities
{
public:
  //@nocgmitf
  static void TranfertActivate(CATPersistentCellInfra & iPersistentInfra, CATPersistentBody & iInputPBody, CATPersistentBody & iOutputPBody);
  //@nocgmitf
  static void TranfertActivate(CATBody & iInputBody, CATBody & iOutputBody);


};

#endif
