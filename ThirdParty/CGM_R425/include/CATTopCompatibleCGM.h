/*
 * @COPYRIGHT DASSAULT SYSTEMES 2007
 */

 /* -*-C++-*- */

#ifndef __CATTopCompatibleCGM_H__
#define __CATTopCompatibleCGM_H__

// COPYRIGHT DASSAULT SYSTEMES 2007

//===========================================================================
// Operator for compatible boolean union of two bodies.
//===========================================================================

#include "CATExtTopMultiResult.h"
#include "ExportedByCATTopologicalObjects.h"
#include "CATDisco3DDebug.h"


class CATGeoFactory;
class CATTopData;
class CATBody;
class CATDomain;
class CATShell;
class CATWire;
class CATVertex;
class CATCell;
class CATCGMHashTableWithAssoc;
class CATCGMHashTable;
class CATTopBooleanOperator;
class CATTopMultiResult;
// class CATListPV;

#undef LOAD__NEW_FACTO_FOR_BETTER_TAGS
//#define LOAD__NEW_FACTO_FOR_BETTER_TAGS   // by DLR6 : creation of new, clean factory for better tags when re-recording ODT

#ifdef LOAD__NEW_FACTO_FOR_BETTER_TAGS
// Creation of new factory for better tags in case of re-record // by DLR6
#include "CATGenericScanMacros_Protected.h"
#include "CATCGMContainerMngt.h"
#include "CATCloneManager.h"
#include "CATCGMTopologyImpl.h"
#include "CATBodyName.h" // for CATBodyPutName/CATBodyGetName
#endif // LOAD__NEW_FACTO_FOR_BETTER_TAGS


//U29@310718 : - separation des stream version entre writeinput et writeout
//               car les deux n'ont aucun lien.
//             - Definition par une macro pour controler les ecritures en dures...
#define CompatibleCGM_STREAMVERSION_WriteInput  7
#define CompatibleCGM_STREAMVERSION_WriteOutput 5

// Use environment variables to force these modes on, to translate cases
CATBoolean ExportedByCATTopologicalObjects Force_SuppressMode();
CATBoolean ExportedByCATTopologicalObjects Force_VolumeJournalling();

class ExportedByCATTopologicalObjects CATTopCompatibleCGM : public CATExtTopMultiResult
{
  friend class CATTopCompatibleImpl;
  friend class CATTopCompatibleNewTopo;
public:

  //=================
  // Constructor
  //=================
  CATTopCompatibleCGM(CATGeoFactory * iFactory,
                      CATTopData    * iTopData,
                      CATLISTP(CATBody) * iBodyList,
                      CATTopMultiResult * iOperator);

  //=================	
  // Destructor
  //=================
  virtual ~CATTopCompatibleCGM();

  //-------------------------------------------------------------------------------------------------------
  // Surcharge du new/delete
  //-------------------------------------------------------------------------------------------------------
  CATCGMNewClassArrayDeclare;

  //========================================================
  // GetResult: returns the resulting body
  //========================================================
  virtual CATBody * GetResult();
  virtual CATBody * GetResult(CATCGMJournalList* iJournal);

  virtual CATBoolean IsVoBSupported();


  void SetNonManifoldAuthorized(int iNonManifoldAuthorized);
  void SetAllCellsJournalExpected(int iAllCellsExected);
  void SetOldSubdivide(int iOld);

  int  GetNonManifoldAuthorized();
  int  GetAllCellsJournalExpected();
  
  virtual void SetSuppressMode(int yes_or_no = 1); 
  virtual int  GetSuppressMode() const;

  virtual void       SetVolumeJournalMode(CATBoolean iVolumeJournalMode);
  virtual CATBoolean GetVolumeJournalMode() const;

  CATLISTP(CATBody)* GetBodyList();
  int  GetCompatibleCalls() const;
  int  GetCompatibleKOs() const;

  //=========================
  //  Imprint
  //=========================
  virtual void SetImprintFollowUpMode(CATBoolean iImprintFollowUpMode);
  virtual CATBoolean GetImprintFollowUpMode() const;
  CATBoolean ValidateVolumeJournal(CATCGMOutput& os);
  CATUnicodeString GetObjString( const CATICGMObject* ipIObj);
  //=========================
  // methods for CGM Replay 
  //=========================
  static const CATString* GetDefaultOperatorId() { return &_OperatorId; }


protected:


  const  CATString* GetOperatorId();
  //=================
  // Internal service
  //=================
  void Clear();

  void CheckInput();

  CATBody* CompatibleForBodyList(CATTopBooleanOperator* iOp, CATLISTP(CATBody)* iBodyList);

  //========================================================
  // MakeReport.
  //========================================================
  void MakeReport();

  int                RunOperator();


private:

  //================================
  // Member data.
  //================================

  int                 _NBodiesDone; // For Debug

  CATLONG32           _RunNumber;  // Number of times Run has been called.
  int                 _InsertedLocalJournal;

  int                 _NonManifoldAuthorized; // ==0 : Non manifold output body is not authorized.
                                              // !=0 : Non manifold output body is authorized.
  int                 _AllCellsExpected; // ==0 : Non manifold output body is not authorized.
                                              // !=0 : Non manifold output body is authorized.
  CATBoolean          _VolumeJournalExpected; // 0 = no follow up of journals, 1 = follow up of journals

  CATCGMJournalList * _LocalJournal;

  CATCGMJournalList * _CompletedJournal; //celltrack
  CATBoolean          _imprintFollowUpMode;

  int                 _FirstAfterRun;
  int                 _OldSubdivide;
  CATLISTP(CATBody) * _BodyList;

  CATLONG32           _nbCompatibleCalls;
  CATLONG32           _nbCompatibleKOs;
 
  void BuildValidDomains(CATBody*& BodyToRepair);

  CATLISTP(CATBody) * _FailedBodyList;

  int                 _SuppressMode;
  static CATString    _OperatorId; // For CGM replay.



  //============================================================
  // Methodes et donnees pour la stabilisation des orientations)
  //============================================================

  void StabilizeOrientation();
  CATBoolean  StabilizeShellsOrientation(CATShell * iShell, CATBody * iOutputBody);
  CATBoolean  StabilizeWiresOrientation(CATWire  * iWire, CATBody * iOutputBody);
  void EditOrientationTables(CATCGMHashTableWithAssoc ** oOutputCells, CATCGMHashTable ** oOutputDomains, CATListPV * ioListOfCGMJournalList);
  void RetrieveChildrenCells(CATListPV * iListOfCGMJournalList,
                             CATCell * iParentCell, CATLISTP(CATGeometry) & ioChildren);


  //=========================
  //  Debug of multi-bodies compatible
  //=====
  //  Not meant to be visible nor usable for customers !!
  //=========================

#ifdef CATDisco3DDebug_ON
public:
  void FOR_DEBUG_ForceFantomRun() { _RunNumber = 1; };
#endif // CATDisco3DDebug_ON

};

#endif
