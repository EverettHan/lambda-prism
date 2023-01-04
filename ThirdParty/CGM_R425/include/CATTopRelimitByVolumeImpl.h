#ifndef CATTopRelimitByVolumeImpl_h
#define CATTopRelimitByVolumeImpl_h

#include "CATTopRelimitByVolume.h"
#include "ExportedByCATTopologicalObjects.h"

class CATGeoFactory;
class CATTopData;
class CATExtTopOperator;

class ExportedByCATTopologicalObjects CATTopRelimitByVolumeImpl : public CATTopRelimitByVolume
{
public:

  CATTopRelimitByVolumeImpl(CATGeoFactory * iFactory, CATTopData * iTopData, CATExtTopOperator * iExtensible = NULL);

  virtual ~CATTopRelimitByVolumeImpl();

  //===========================================
  // Methodes de parametrisation de l'operateur
  //===========================================

  virtual CATBoolean GetCheckJournal() const;
  virtual CATLONG32 GetSelectionType() const;

  virtual void SetCheckJournal(CATBoolean iCheckMode);
  virtual void SetSelectionType(CATLONG32 iSelectionType);
  virtual void SetComputationOfBoundary(CATBoolean iBoundary);
  virtual void  SetJournalMode(CATLONG32 iMode);

  //======================================
  // Methodes specifiques a CATTopOperator
  //======================================

  virtual int Run();
  virtual int RunOperator();
  
  virtual CATBody * GetResult(CATCGMJournalList * ioJournal);

  //===========================================
  // Fast Update Services
  //===========================================
 /**
  * @return [out, IUnknown#Release]
  */
  virtual CATTopRelimitByVolumeContextForFastRun * GetTopRelimitByVolumeContextForFastRun(CATBoolean iGetOnly = FALSE);

  //===========================================
  // Methods to access extensible parameters
  //===========================================

  void SetBodyToRelimit(CATBody * iBodyToRelimit);
  void SetSolidBody(CATBody * iSolidBody);
  CATBody * GetBodyToRelimit();
  CATBody * GetSolidBody();
  void SetOneRunOnly(CATBoolean iOneRunOnly);

  //================================
  // CGMReplay
  //================================

public:

  static const CATString *GetDefaultOperatorId() { return &_OperatorId; }

protected:

  const  CATString  *GetOperatorId();
  CATExtCGMReplay   *IsRecordable(short &LevelOfRuntime, short &VersionOfStream);
  void               RequireDefinitionOfInputAndOutputObjects();
  void               WriteInput(CATCGMStream &ioStream);
  void               WriteTopOutput(CATCGMStream &ioStream);
  CATBoolean         ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);
  CATCheckDiagnostic CheckOutput(CATCGMOutput &os);

  static CATString   _OperatorId;
};

#endif

