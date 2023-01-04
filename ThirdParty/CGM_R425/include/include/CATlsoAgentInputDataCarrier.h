/*VB7 August 2013*/
#ifndef CATlsoAgentInputDataCarrier_H
#define CATlsoAgentInputDataCarrier_H

#include "CATCGMNewArray.h"
#include "CATPersistentCell.h"
#include "CATCellManifold.h"
#include "ListPOfCATCellManifold.h"
#include "CATErrorDef.h"
#include "CATBoolean.h"
#include "CATMathTransformation.h"
#include "ListPOfCATPersistentFaces.h"
#include "CATSysDeletePtrList.h"
#include "CATCGMHashTableWithAssoc.h"
#include "CATCGMJournalList.h"
#include "CATLISTP_CATMathTransformation.h"
#include "CATListOfShort.h"
#include "ListPOfCATPersistentBodies.h"

class CATCGMHashTableWithAssoc;
class CATFace;
class CATMathTransformation;
class CATLiveBody;
class CATPersistentCellInfra;
class CATCGMJournalList;
class CATCellManifoldsManager;
class CATHVertex;
class CATPersistentExtTopOperator;


class ExportedByPersistentCell CATlsoAgentInputDataCarrier
{
public:
  CATCGMNewClassArrayDeclare;      // Pool allocation

  // Constructor
  CATlsoAgentInputDataCarrier();
  CATlsoAgentInputDataCarrier(const CATPersistentExtTopOperator * iOwnerOperator);
  CATlsoAgentInputDataCarrier(const CATlsoAgentInputDataCarrier & iAgentInputDataCarrier);

  // Destructor
  virtual ~CATlsoAgentInputDataCarrier();

  INLINE void SetDuplicationMode(CATBoolean iDuplicationMode);
  INLINE CATBoolean GetDuplicationMode() const;

  INLINE void SetPersistentFaceToTransfo(CATCGMHashTableWithAssoc * iFaceToTransfo);
  INLINE CATCGMHashTableWithAssoc * GetPersistentFaceToTransfo() const;

  INLINE void SetInstanceTransformationList(CATLISTP(CATMathTransformation) & iInstanceTransformationList);
  INLINE CATLISTP(CATMathTransformation) * GetInstanceTransformationList() const;
  
  INLINE void SetInstanceNumberList(CATListOfShort & iInstanceNumberList);
  INLINE CATListOfShort * GetInstanceNumberList() const;
  
  INLINE void SetIsOffset(CATBoolean iIsOffset);
  INLINE CATBoolean GetIsOffset() const;

  INLINE void SetShellMode(CATBoolean iShellMode);
  INLINE CATBoolean GetShellMode() const;

  HRESULT SetPersistentFaceToOffsetValue(ListPOfCATPersistentFaces &iInputPersistentFaceList, CATListOfDouble &iOffSetValues1, CATListOfDouble &iOffSetValues2);
  INLINE void SetPersistentFaceToOffsetValue(CATCGMHashTableWithAssoc * iFaceToOffsetValue);
  INLINE CATCGMHashTableWithAssoc * GetPersistentFaceToOffsetValue() const;
  INLINE void SetShellJournal(CATCGMJournalList * iShellJournal);
  INLINE CATCGMJournalList * GetShellJournal() const;

  INLINE void SetForbidDMCreationFromDatumManifoldCarrier(CATBoolean iForbidDMCreationFromDatumManifoldCarrier);
  INLINE CATBoolean GetForbidDMCreationFromDatumManifoldCarrier() const;

  INLINE void SetDeclarativeOpeMode(CATBoolean iDeclarativeOpeMode);
  INLINE CATBoolean GetDeclarativeOpeMode() const; 

  INLINE void SetGlobalTransformation(CATMathTransformation & iGlobalTransformation);
  INLINE CATMathTransformation * GetGlobalTransformation() const;

  INLINE void SetJournalForTransfo(CATCGMJournalList * iJournalForTransfo);
  INLINE CATCGMJournalList * GetJournalForTransfo() const;

  INLINE void SetAllowedDanglingCMList(ListPOfCATCellManifold & iAllowedDanglingCMList);
  INLINE void GetAllowedDanglingCMList(ListPOfCATCellManifold & oAllowedDanglingCMList) const;
  INLINE void AppendAllowedDanglingCMList(ListPOfCATCellManifold & iAllowedDanglingCMList);

  INLINE void SetUpdated(CATBoolean iUpdated);
  INLINE CATBoolean IsUpdated() const;

  INLINE void SetLocalBuild(CATBoolean iVal) { _LocalBuild = iVal; }
  CATBoolean  GetLocalBuild() const { return _LocalBuild; }

  CATBody * GetInputBody() const;
  CATPersistentBody * GetInputPersistentBody() const;
  void GetAllInputPersistentBody(ListPOfCATPersistentBodies & oPersistentBodyList) const;
  //INLINE void SetOwnerOperator(CATPersistentExtTopOperator * iOwnerOperator);
  //INLINE CATPersistentExtTopOperator * GetOwnerOperator();

  INLINE CATBoolean RightOperator(const CATPersistentExtTopOperator * iOpe) const;
  INLINE CATBoolean EmptyOperator() const;

  CATMathTransformation * GetTransfo(CATPersistentFace * iFace) const;

  CATListOfDouble       * GetOffsetValues(CATPersistentFace * iPFace) const;

  const CATPersistentExtTopOperator * GetOperatorForCheckBeforeRematch();

private:

  //Transformface
  CATCGMHashTableWithAssoc * _PersistentFaceToTransfo;
  CATBoolean                 _DuplicationMode;
  CATLISTP(CATMathTransformation) * _InstanceTransformationList;
  CATListOfShort                  * _InstanceNumberList;

  //Offset (thicknessFace)
  CATBoolean                 _IsOffset;
  CATBoolean                _ShellMode;
  CATCGMHashTableWithAssoc * _PersistentFaceToOffsetValue;
  CATCGMJournalList        * _ShellJournal;
  CATBoolean                 _LocalBuild;

  // DeclarativeOper
  CATBoolean     _ForbidDMCreationFromDatumManifoldCarrier;
  CATBoolean     _DeclarativeOpeMode;

  CATBoolean     _Updated;

  CATMathTransformation * _GlobalTransformation;
  CATCGMJournalList     * _JournalForTransfo;

  ListPOfCATCellManifold _AllowedDanglingCMList;

  const CATPersistentExtTopOperator * _OwnerOperator;
};

INLINE void CATlsoAgentInputDataCarrier::SetDuplicationMode(CATBoolean iDuplicationMode) {
  _DuplicationMode = iDuplicationMode; }
INLINE CATBoolean CATlsoAgentInputDataCarrier::GetDuplicationMode() const {
  return _DuplicationMode; }

INLINE void CATlsoAgentInputDataCarrier::SetPersistentFaceToTransfo(CATCGMHashTableWithAssoc * iFaceToTransfo) {
  if(_PersistentFaceToTransfo)
  {
    int ind = 0;
    for(ind = 0; ind < _PersistentFaceToTransfo->Size(); ind++ )
    {
      CATMathTransformation * curTransfo = (CATMathTransformation*)(_PersistentFaceToTransfo->GetAssoc(ind));
      CATSysDeletePtr(curTransfo);
    }
    CATSysDeletePtr(_PersistentFaceToTransfo);
  }
  _PersistentFaceToTransfo = iFaceToTransfo; }

INLINE CATCGMHashTableWithAssoc * CATlsoAgentInputDataCarrier::GetPersistentFaceToTransfo() const {
  return _PersistentFaceToTransfo; }

INLINE void CATlsoAgentInputDataCarrier::SetInstanceTransformationList(CATLISTP(CATMathTransformation) & iInstanceTransformationList) {
  if(!_InstanceTransformationList)
  {
    _InstanceTransformationList = new CATLISTP(CATMathTransformation)();
  }
  else
    CATSysDeletePtr(_InstanceTransformationList);
  if (_InstanceTransformationList)
    _InstanceTransformationList->Append(iInstanceTransformationList);
}

INLINE void CATlsoAgentInputDataCarrier::SetInstanceNumberList(CATListOfShort & iInstanceNumberList) {
  if(!_InstanceNumberList)
  {
    _InstanceNumberList = new CATListOfShort();
  }
  else
    CATSysDeletePtr(_InstanceNumberList);
  
  if (_InstanceNumberList)
    _InstanceNumberList->Append(iInstanceNumberList);
}

INLINE CATLISTP(CATMathTransformation) * CATlsoAgentInputDataCarrier::GetInstanceTransformationList() const {
  return _InstanceTransformationList;
}

INLINE CATListOfShort * CATlsoAgentInputDataCarrier::GetInstanceNumberList() const {
  return _InstanceNumberList;
}

INLINE void CATlsoAgentInputDataCarrier::SetIsOffset(CATBoolean iIsOffset) {
  _IsOffset = iIsOffset; }
INLINE CATBoolean CATlsoAgentInputDataCarrier::GetIsOffset() const {
  return _IsOffset; }

INLINE void CATlsoAgentInputDataCarrier::SetShellMode(CATBoolean iShellMode) {
  _ShellMode = iShellMode; }
INLINE CATBoolean CATlsoAgentInputDataCarrier::GetShellMode() const {
  return _ShellMode; }

INLINE void CATlsoAgentInputDataCarrier::SetPersistentFaceToOffsetValue(CATCGMHashTableWithAssoc * iFaceToOffsetValue) {
  _PersistentFaceToOffsetValue = iFaceToOffsetValue; }
INLINE CATCGMHashTableWithAssoc * CATlsoAgentInputDataCarrier::GetPersistentFaceToOffsetValue() const {
  return _PersistentFaceToOffsetValue; }


INLINE void CATlsoAgentInputDataCarrier::SetShellJournal(CATCGMJournalList * iShellJournal) {
  if(_ShellJournal)
    CATSysDeletePtr(_ShellJournal);
  _ShellJournal = iShellJournal; }

INLINE CATCGMJournalList * CATlsoAgentInputDataCarrier::GetShellJournal() const {
  return _ShellJournal; }

INLINE void CATlsoAgentInputDataCarrier::SetForbidDMCreationFromDatumManifoldCarrier(CATBoolean iForbidDMCreationFromDatumManifoldCarrier) {
  _ForbidDMCreationFromDatumManifoldCarrier = iForbidDMCreationFromDatumManifoldCarrier; }
INLINE CATBoolean CATlsoAgentInputDataCarrier::GetForbidDMCreationFromDatumManifoldCarrier() const {
  return _ForbidDMCreationFromDatumManifoldCarrier; }

INLINE void CATlsoAgentInputDataCarrier::SetDeclarativeOpeMode(CATBoolean iDeclarativeOpeMode) {
  _DeclarativeOpeMode = iDeclarativeOpeMode; }
INLINE CATBoolean CATlsoAgentInputDataCarrier::GetDeclarativeOpeMode() const {
  return _DeclarativeOpeMode; }

INLINE void CATlsoAgentInputDataCarrier::SetGlobalTransformation(CATMathTransformation & iGlobalTransformation) {
  if(_GlobalTransformation)
    *_GlobalTransformation = iGlobalTransformation;
  else
    _GlobalTransformation = new CATMathTransformation(iGlobalTransformation); }
INLINE CATMathTransformation * CATlsoAgentInputDataCarrier::GetGlobalTransformation() const {
  return _GlobalTransformation; }

INLINE void CATlsoAgentInputDataCarrier::SetJournalForTransfo(CATCGMJournalList * iJournalForTransfo) {
  _JournalForTransfo = iJournalForTransfo; }

INLINE CATCGMJournalList * CATlsoAgentInputDataCarrier::GetJournalForTransfo() const {
  return _JournalForTransfo; }

INLINE void CATlsoAgentInputDataCarrier::SetAllowedDanglingCMList(ListPOfCATCellManifold & iAllowedDanglingCMList) {
  _AllowedDanglingCMList = iAllowedDanglingCMList; }

INLINE void CATlsoAgentInputDataCarrier::AppendAllowedDanglingCMList(ListPOfCATCellManifold & iAllowedDanglingCMList) {
  _AllowedDanglingCMList.Append(iAllowedDanglingCMList);
  _AllowedDanglingCMList.RemoveDuplicates();}

INLINE void CATlsoAgentInputDataCarrier::GetAllowedDanglingCMList(ListPOfCATCellManifold & oAllowedDanglingCMList)  const{
  oAllowedDanglingCMList = _AllowedDanglingCMList; }

/*INLINE void CATlsoAgentInputDataCarrier::SetOwnerOperator(CATPersistentExtTopOperator * iOwnerOperator) {
  _OwnerOperator = iOwnerOperator; }

INLINE CATPersistentExtTopOperator * CATlsoAgentInputDataCarrier::GetOwnerOperator() {
  return _OwnerOperator; }*/

INLINE CATBoolean CATlsoAgentInputDataCarrier::RightOperator(const CATPersistentExtTopOperator * iOpe) const {
  return iOpe==_OwnerOperator; }

INLINE CATBoolean CATlsoAgentInputDataCarrier::EmptyOperator() const
{
  CATBoolean emptyOperator = FALSE;
  if(!_OwnerOperator)
    emptyOperator = TRUE;
  return emptyOperator;
}

INLINE void CATlsoAgentInputDataCarrier::SetUpdated(CATBoolean iUpdated) {
  _Updated = iUpdated; }

INLINE CATBoolean CATlsoAgentInputDataCarrier::IsUpdated() const {
  return _Updated; }

#endif


