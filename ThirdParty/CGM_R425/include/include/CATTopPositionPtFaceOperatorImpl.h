#ifndef CATTopPositionPtFaceOperatorImpl_h
#define CATTopPositionPtFaceOperatorImpl_h

// COPYRIGHT DASSAULT SYSTEMES  2009

// Interface en  Protected Pour Methodes Particulieres
//
//---------------------------------------------------------------------------
// Aout2009 JSX Ajout IsOnBoundary
// 18/04/11 NLD Utilisation de CATCGMOperatorDebug pour instrumentation perfos
//---------------------------------------------------------------------------

#include "CATTopPositionPtFaceOperator.h"
#include "ExportedByCATTopologicalObjects.h"

#include "CATBoolean.h"
#include "CATCGMOperatorDebug.h"

class CATGeoFactory;
class CATSoftwareConfiguration;
class CATEdge;
class CATSurParam;
class CATTopPositionPtFaceOperatorImpl : public CATTopPositionPtFaceOperator
  {
  CATCGMVirtualDeclareClass(CATTopPositionPtFaceOperatorImpl);
  public :
  virtual void SetLockCrvEq(CATBoolean      iLockCrvEquation);
  virtual void IsOnBoundary(const CATSurParam & iParam, CATFace * iFace, CATEdge *& oEdge);
  virtual void SetSurParams(int             iNbPoints,
                            CATSurParam *    iPoints);

  virtual void SetToleranceOnBoundary(double iTol);

  CATCGMOperatorDebugDeclareRun(CATTopPositionPtFaceOperatorImpl,CATTopPositionPtFaceOperator);
  virtual int RunOperator();

  virtual void WriteInput(CATCGMStream  & Str);
  CATExtCGMReplay  *IsRecordable(short &LevelOfRuntime, short &VersionOfStream);
  void  RequireDefinitionOfInputAndOutputObjects();
  const  CATString  *GetOperatorId();
  CATBoolean ValidateTopOutput(CATTopCheckJournal* iEquivalent,CATCGMOutput& os);
  void WriteOutput(CATCGMStream &Str);
  CATBoolean ReadReferenceOutput(CATCGMStream &Str);
  void Dump( CATCGMOutput& os );
  void DumpOutput(CATCGMOutput& os);
  void DumpOutput(CATCGMStream &Str, CATCGMOutput &os, int VersionNumber);
  CATBoolean ValidateOutput( CATCGMStream &Str,CATCGMOutput &os,int VersionNumber);
  CATCGMOperator::CATCheckDiagnostic  CheckOutput(CATCGMOutput &os);

  virtual CATLocation   GetOneResult();
  virtual const CATLocation*    GetResults() const;

     /** @nodoc */
  CATTopPositionPtFaceOperatorImpl(CATGeoFactory*     iContainer, CATTopData * iData, CATExtTopOperator* iExtensible=NULL);
  virtual ~CATTopPositionPtFaceOperatorImpl();



  protected :

    CATTopPositionPtFaceOperatorImpl() {;};

  };

ExportedByCATTopologicalObjects CATTopPositionPtFaceOperatorImpl * GetProtectedPositionTopPtFaceOperator(CATTopPositionPtFaceOperator *Ope);


#endif
