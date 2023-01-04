/* -*-C++-*- */

#ifndef CATlsoHTMLTrace_H
#define CATlsoHTMLTrace_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier
               
=============================================================================
*/

#include "CATPersistentCell.h"
#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATCell.h"
//#include "CATlsoProjectPilot.h"
#include "CATCGMOutput.h"

class CATPersistentBody;
class CATPersistentExtTopOperator;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
ExportedByPersistentCell void CATlsoHTMLInitCOUT(CATPersistentExtTopOperator * iOpe);
ExportedByPersistentCell void CATlsoHTMLEndCOUT(CATPersistentExtTopOperator * iOpe);


class CATlsoHTMLTrace
{
public:
  //@nocgmitf
  static void InitCOUT(CATPersistentExtTopOperator * iOpe);
  static void EndCOUT(CATPersistentExtTopOperator * iOpe);

};

#endif
