// COPYRIGHT DASSAULT SYSTEMES 2020
//=============================================================================
//
// CATExtTopMaxIsoMoveCalculator 
//  Extensible operator for CATTopMaxIsoMoveCalculator
//
//
//=============================================================================
//  June 2020  Creation                                                 DLR6
//=============================================================================

#ifndef CATExtTopMaxIsoMoveCalculator_H
#define CATExtTopMaxIsoMoveCalculator_H


class CATGeoFactory;
class CATTopData;

#include "CATTopMaxIsoMoveCalculator.h"

#include "CATExtTopOperator.h"

class ExportedByCATTopologicalObjects CATExtTopMaxIsoMoveCalculator : public CATExtTopOperator
{
  friend class CATTopMaxIsoMoveCalculator;

public:
  CATCGMNewClassArrayDeclare;

  CATExtTopMaxIsoMoveCalculator();
  ~CATExtTopMaxIsoMoveCalculator();

  void GetMaxReferenceDisplacements(
    double    * opMaxDeplPos, double    * opMaxDeplNeg);

  // Creates the CATExtCGMReplay object
  CATExtCGMReplay* IsRecordableExt(short & LevelOfRuntime, short &VersionOfStream);

  // Return operator name
  const CATString* GetOperatorId() const;

  static void LoadInOutput(
    CATCGMStream               &Str,
    CATGeoFactory           *  &iFactory,
    CATTopData                 &iData,
    CATBodyFreezeMode          &iFreezeMode,
    CATListPtrCATICGMObject    &ioInputCopy,
    CATListPtrCATICGMObject    &ioInputNoCopy,
    CATBody                 *  &ioOutputBody,
    CATListPtrCATICGMObject    &ioInputNeutral,
    double                     &ioAxis_X,
    double                     &ioAxis_Y,
    double                     &ioAxis_Z);

private:
  static  CATString   _OperatorId;

          double      _refMaxIsoDeplPos;
          double      _refMaxIsoDeplNeg;

protected:

  void RequireDefinitionOfInputAndOutputObjects();

  // Stream inputs of operator. Exact counterpart of CATLoadxxx function
  void WriteInputExt(CATCGMStream & Str);

  ////  // Stream outputs. Exact counterpart of ValidateOutput
  ////  void WriteOutputExt(CATCGMStream & ioStream);

  // Stream outputs of a topological operator. Exact counterpart of ReadTopOutput
  void WriteTopOutputExt(CATCGMStream & Str);

  ////  // Dump inputs of operator
  ////  // (Implementation in CATTopOperator dumps versioning level and the value of some generic options, like warning mode, ...)
  ////  void DumpExt(CATCGMOutput & os);

  ////  // Dump reference outputs of a topological operator
  ////  void DumpTopOutputExt(CATTopCheckJournal * iEquivalent, CATCGMOutput& os);

  ////  // Check inputs for invalidities (the inputs are not valid objects, eg. an edge with a gap too large) or inconsistencies (the inputs may be valid but are inconsistent wrt. the other inputs, eg. a   list of edges to fillet that does not belong to the input body);
  ////  CATCGMOperator::CATCheckDiagnostic CheckInputExt(CATCGMOutput & os);

  ////  // Dump outputs of operator
  ////  void DumpOutputExt(CATCGMOutput & os);

  // Unstream reference outputs of a topological operator. Exact counterpart of WriteTopOutput
  CATTopCheckJournal* ReadTopOutputExt(CATCGMStream & Str);

  // Unstream reference outputs
  CATBoolean ReadReferenceOutput(CATCGMStream &Str);

  ////  // Compares outputs of a topological operator with the ones unstreamed by ReadTopOutput. (Implementation in CATTopOperator performs body-mapping and journal-mapping between reference and result)
  ////  CATBoolean ValidateTopOutputExt(CATTopCheckJournal * iEquivalent, CATCGMOutput& os);

  // Check outputs for invalidities
  CATCGMOperator::CATCheckDiagnostic CheckOutputExt(CATCGMOutput & os);

  // Unstream reference outputs and compares to current results. Exact counterpart of WriteOutput
  CATBoolean ValidateOutputExt(CATCGMStream& ioStream, CATCGMOutput & os, int VersionNumber = 1);

};

#endif //CATExtTopMaxIsoMoveCalculator_H
