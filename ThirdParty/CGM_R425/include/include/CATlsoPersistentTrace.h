/* -*-C++-*- */

#ifndef CATlsoPersistentTrace_H
#define CATlsoPersistentTrace_H
/*  
=============================================================================

RESPONSABLE  : V Bouvier
               
=============================================================================
*/

#include "CATPersistentCell.h"
#include "ListPOfCATPersistentCells.h"
#include "ListPOfCATCell.h"
// #include "CATlsoProjectPilot.h"
#include "CATDebugPersistentAttribute.h"
#include "CATCGMOutput.h"

class CATPersistentBody;
class CATPersistentExtTopOperator;
class CAT3DCustomRep;

//-----------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------
ExportedByPersistentCell void CATlsoPCellDump(CATPersistentCell * iPCell, ListPOfCATCell * iRepCellList=NULL);

ExportedByPersistentCell void CATlsoPCellConstr(CATPersistentCell * iPCell);
ExportedByPersistentCell void CATlsoPCellDestr(CATPersistentCell * iPCell);

ExportedByPersistentCell void CATlsoPCellJournalItem(ListPOfCATPersistentCells & iInputPCellList, ListPOfCATPersistentCells & iOutputPCellList);
ExportedByPersistentCell void CATlsoPCellSetRep(CATPersistentCell * iPCell, CATPersistentBody * iPBody, ListPOfCATCell & iRepCellList, const CATAutoBaseThreadContext &iThreadContext, CATListOfInt * iTypeList=NULL);

ExportedByPersistentCell CATBoolean IsPCellTraceMode();

ExportedByPersistentCell void CATlsoPTraceStart(CATPersistentExtTopOperator * iOpe);
ExportedByPersistentCell void CATlsoPTraceEnd(CATPersistentExtTopOperator * iOpe);

ExportedByPersistentCell int CATlsoPCellTraceGetCell(int iPTag);

class CATlsoPersistentTrace
{
public:
  //@nocgmitf
  static void DumpPCell(CATPersistentCell * iPCell, ListPOfCATCell * iRepCellList);

  static void CATlsoPCellConstr(CATPersistentCell * iPCell);
  static void CATlsoPCellDestr(CATPersistentCell * iPCell);

  static void CATlsoPCellJournalItem(ListPOfCATPersistentCells & iInputPCellList, ListPOfCATPersistentCells & iOutputPCellList);
  static void CATlsoPCellSetRep(CATPersistentCell * iPCell, CATPersistentBody * iPBody, ListPOfCATCell & iRepCellList, const CATAutoBaseThreadContext &iThreadContext, CATListOfInt * iTypeList);

  static void DumpPCellFromFile(int iPCellTag, CATCGMOutput & os);
  static int CATlsoPCellTraceGetCell(int iPTag);

  static CATCGMOutput * GetOutput();
  static void CloseOutput();
  static void InitOutput();
};

#endif
