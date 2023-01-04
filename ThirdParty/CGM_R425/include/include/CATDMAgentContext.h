#ifndef CATDMAgentContext_H
#define CATDMAgentContext_H

#include "CATPersistentCell.h"
#include "ListPOfCATLiveBody.h"
#include "CATCGMHashTable.h"
#include "CATMathInline.h"
#include "CATDeclarativeManifold.h"
#include "ListPOfCATDeclarativeManifold.h"

class CATBody;
class CATPersistentCellInfra;
class CATVariationalPatternParameters;
class CATDeclarativeOperatorsBridge;

class ExportedByPersistentCell CATDMAgentContext
{
public:
  //CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructors
  CATDMAgentContext(ListPOfCATLiveBody * iLivificationInputLiveBodyList,
                    CATBody            * iOutputBody);
  
  // Destructor
  ~CATDMAgentContext();


  CATBoolean AllInputDomainsInOutput();
  CATBoolean DuplicationMode();
  void SetDuplicationMode();
  INLINE void AppendModifiedCells(ListPOfCATCell &iCells);
  INLINE ListPOfCATCell GetModifiedCells();

  INLINE void SetLiveInfra(CATPersistentCellInfra * iLiveInfra);
  INLINE CATPersistentCellInfra * GetLiveInfra();

  INLINE void SetIsFullDomainMove(CATBoolean iIsFullDomainMove);
  INLINE CATBoolean GetIsFullDomainMove();

  INLINE void SetIsLastRun(CATBoolean iIsLastRun);
  INLINE CATBoolean GetIsLastRun();

  INLINE void SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet);
  INLINE CATBoolean GetIsCalledByRedoFillet();


  INLINE void SetIsCalledByLiveOperator(CATBoolean iIsCalledByLiveOperator);
  INLINE CATBoolean GetIsCalledByLiveOperator();

  INLINE void SetDeclarativeOperatorsBridge(CATDeclarativeOperatorsBridge * iDeclarativeOperatorsBridge);
  INLINE CATDeclarativeOperatorsBridge * GetDeclarativeOperatorsBridge();
  INLINE void SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds);
  INLINE CATLiveBody *GetOriginalBodyForKeepManifolds();

  ListPOfCATLiveBody * _LivificationInputLiveBodyList;
  CATLiveBody *_OriginalBodyForKeepManifolds;
  CATBody            * _OutputBody;

  CATCGMHashTable  * _liveInputDMHT;
  CATCGMHashTable  * _liveInputCMHT;
  CATLISTP(CATDomain) _outDomList;
  CATLISTP(CATDomain) _newOutDomList;
  CATLISTP(CATDomain) _inputDomNotInOutputList;

  void SetVariationalPatternParameters(CATVariationalPatternParameters * iVariationalPatternParameters);
  CATVariationalPatternParameters * GetVariationalPatternParameters();

private : 
    void Init();

    CATBoolean _AllInputDomainsInOutput;
    CATBoolean _DuplicationMode;
    ListPOfCATCell _ModifiedCells;

    CATPersistentCellInfra * _LiveInfra;

    CATVariationalPatternParameters * _VariationalPatternParameters;

    CATBoolean _IsFullDomainMove;
    CATBoolean _IsLastRun;
    CATBoolean _IsCalledByRedoFillet;
    CATBoolean _IsCalledByLiveOperator;
    CATDeclarativeOperatorsBridge * _DeclarativeOperatorsBridge;

};

INLINE void CATDMAgentContext::AppendModifiedCells(ListPOfCATCell &iCells)
{
  _ModifiedCells.Append(iCells);
}
INLINE ListPOfCATCell CATDMAgentContext::GetModifiedCells()
{
  return _ModifiedCells;
}
INLINE void CATDMAgentContext::SetLiveInfra(CATPersistentCellInfra * iLiveInfra)
{
  _LiveInfra = iLiveInfra;
}
INLINE CATPersistentCellInfra * CATDMAgentContext::GetLiveInfra()
{
  return _LiveInfra;
}
INLINE void CATDMAgentContext::SetIsFullDomainMove(CATBoolean iIsFullDomainMove)
{
  _IsFullDomainMove = iIsFullDomainMove;
}
INLINE CATBoolean CATDMAgentContext::GetIsFullDomainMove()
{
  return _IsFullDomainMove;
}
INLINE void CATDMAgentContext::SetIsLastRun(CATBoolean iIsLastRun)
{
  _IsLastRun = iIsLastRun;
}
INLINE CATBoolean CATDMAgentContext::GetIsLastRun()
{
  return _IsLastRun;
}
INLINE void CATDMAgentContext::SetIsCalledByRedoFillet(CATBoolean iIsCalledByRedoFillet)
{
  _IsCalledByRedoFillet = iIsCalledByRedoFillet;
}
INLINE CATBoolean CATDMAgentContext::GetIsCalledByRedoFillet()
{
  return _IsCalledByRedoFillet;
}
INLINE void CATDMAgentContext::SetIsCalledByLiveOperator(CATBoolean iIsCalledByLiveOperator)
{
  _IsCalledByLiveOperator = iIsCalledByLiveOperator;
}
INLINE CATBoolean CATDMAgentContext::GetIsCalledByLiveOperator()
{
  return _IsCalledByLiveOperator;
}
INLINE void CATDMAgentContext::SetDeclarativeOperatorsBridge(CATDeclarativeOperatorsBridge * iDeclarativeOperatorsBridge)
{
  _DeclarativeOperatorsBridge = iDeclarativeOperatorsBridge;
}
INLINE CATDeclarativeOperatorsBridge * CATDMAgentContext::GetDeclarativeOperatorsBridge()
{
  return _DeclarativeOperatorsBridge;
}
INLINE void CATDMAgentContext::SetOriginalBodyForKeepManifolds(CATLiveBody *iOriginalBodyForKeepManifolds)
{
  _OriginalBodyForKeepManifolds=iOriginalBodyForKeepManifolds;
}
INLINE CATLiveBody *CATDMAgentContext::GetOriginalBodyForKeepManifolds()
{
  return _OriginalBodyForKeepManifolds;
}
#endif
